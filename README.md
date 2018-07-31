
## starcore_for_go v0.5

The library is written in golang, which supports go language to call other scripting languages such as python, java, ruby, c#, etc.And, also support use go language to write shared libraries for other scripting languages.

It supports android, windows and linux platforms

Change at 2018/07/22
--------

suppor ios
--------

- build script example,

```
rm -rf libstar_go.a

export PATH="/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/:/usr/local/bin:/usr/bin:/bin:$PATH"  

arch=("i386" "x86_64" "arm64" "armv7");

for s in ${arch[@]}; do
  echo "build for $s"

  export GOOS=darwin
  export CGO_ENABLED=1
  if [ "$s" == "armv7" ]; then
    export CFLAGS="-arch $s -miphoneos-version-min=6.0 -isysroot "$(xcrun -sdk iphoneos --show-sdk-path)
    export CC=/usr/local/go/misc/ios/clangwrap.sh
    export GOARCH=arm
    export GOARM=7
  elif [ "$s" == "i386" ]; then
    export CFLAGS="-arch $s -miphoneos-version-min=6.0 -isysroot "$(xcrun -sdk iphonesimulator --show-sdk-path)
    export CC="clang $CFLAGS"
    export GOARCH=386
  elif [ "$s" == "x86_64" ]; then
    export CFLAGS="-arch $s -miphoneos-version-min=6.0 -isysroot "$(xcrun -sdk iphonesimulator --show-sdk-path)
    export CC="clang $CFLAGS"
    export GOARCH=amd64
  elif [ "$s" == "arm64" ]; then
    export CFLAGS="-arch $s -miphoneos-version-min=6.0 -isysroot "$(xcrun -sdk iphoneos --show-sdk-path)
    export CC="clang $CFLAGS"
    export GOARCH=arm64
  fi

  go build -tags='ios' -buildmode=c-archive -o libstar_go.a
  
  mkdir $s
  cp ./libstar_go.a $s
  rm -rf ./libstar_go.a
 
done

lipo -create ./i386/libstar_go.a ./x86_64/libstar_go.a ./armv7/libstar_go.a ./arm64/libstar_go.a -o libstar_go.a

rm -rf ./i386
rm -rf ./x86_64
rm -rf ./armv7
rm -rf ./arm64

lipo -info libstar_go.a
```

*note: if the ios static library will be used with starcore, the output library name should be :libstar_go.a*


Change at 2018/05/12
--------

## New Post: [Go Extension for Android](https://srplab.github.io/go/2018/05/11/go_extension_for_android.html)


Install:
--------

```sh
 $ go get github.com/srplab/starcore_for_go/stargo
```

Example:
--------

```go
package main

import "fmt"
import "github.com/srplab/starcore_for_go/stargo"

func main() {
	Service := stargo.InitSimple("test", "123", 0, 0)
	SrvGroup := Service.Get("_ServiceGroup").(*stargo.StarSrvGroup)
	Service.CheckPassword(false)

	SrvGroup.InitRaw("python36", Service)
	python := Service.ImportRawContext("python", "", false, "")

	python.Call("import", "tensorflow")
	tf := python.GetObject("tensorflow")

	a := tf.Call("constant", 5, map[string]interface{}{"name": "input_a"})
	b := tf.Call("constant", 3, map[string]interface{}{"name": "input_b"})

	fmt.Println(a)
	fmt.Println(b)

	c := tf.Call("multiply", a, b, map[string]interface{}{"name": "mul_c"})
	d := tf.Call("add", a, b, map[string]interface{}{"name": "add_d"})

	fmt.Println(c)
	fmt.Println(d)

	e := tf.Call("add", c, d, map[string]interface{}{"name": "add_e"})
	fmt.Println(e)

	sess := tf.CallObject("Session")
	fmt.Println(sess)

	r := sess.Call("run", e)
	fmt.Println(r)
}
```

Capture output from other scripts:
--------

Register CallBack function, as follow

```go
package main

import "fmt"
import "github.com/srplab/starcore_for_go/stargo"

func MsgCallBack(ServiceGroupID uint32, uMsg uint32, wParam interface{}, lParam interface{}) (IsProcessed bool, Result interface{}) {
	if uMsg == stargo.MSG_VSDISPMSG || uMsg == stargo.MSG_VSDISPLUAMSG || uMsg == stargo.MSG_DISPMSG || uMsg == stargo.MSG_DISPLUAMSG {
		fmt.Println(wParam)
	} else {
		fmt.Println(ServiceGroupID, uMsg, wParam, lParam)
	}
	return false, 0
}

func main() {
	Service := stargo.InitSimple("test", "123", 0, 0)
	SrvGroup := Service.Get("_ServiceGroup").(*stargo.StarSrvGroup)
	Service.CheckPassword(false)

	stargo.RegMsgCallBack_P(MsgCallBack)

    ...
}
```

Develop extension modules:
--------

Set the callback function in the initialization function

- Call "RegScriptInitCallBack_P" to register the function which will be called when the module is loaded.
- Call "RegAttachRawContextCallBack_P" to register function which will be called when other scripts call AttachRawContext function of cle.
- Call "RegScriptTermCallBack_P" to register the function which will be called when the module is unloaded.

```go
func init() {
	stargo.RegAttachRawContextCallBack_P(func(ContextName string) interface{} {
		if ContextName == "gofunc" {
			return func(v1 string, v2 float32) string {
				stargo.Println(v1)
				stargo.Println(v2)
				return "hello fro go"
			}
		}
		return nil
	})

	stargo.RegScriptTermCallBack_P(func() {
		stargo.Println("go script engine exit...")
	})

	stargo.RegScriptInitCallBack_P(func(SrvGroup *stargo.StarSrvGroup, Service *stargo.StarService) {
		stargo.Println("go script engine init...")

		/*--GoObject can be called from other script */
		s := Service.New("GoObject")
		s.RegScriptProc_P("PrintHello", func(CleGroup *stargo.StarSrvGroup, CleService *stargo.StarService, CleObject *stargo.StarObject, Paras []interface{}) interface{} {
			stargo.Println(Paras)
			return []interface{}{"return from go", 345.4}
		})
	})
}
```

### Build to share library

- Linux

```sh
 $ go build -buildmode=c-shared -o star_go.so
```

- Windows

```sh
 $ go build -buildmode=c-shared -o star_go.so
```

- Android

the work is tested with android-ndk-r12b

first, create toolchain

```sh
/Users/srplab/android/android-sdk-macosx/android-ndk-r12b/build/tools/make-standalone-toolchain.sh --install-dir=android-toolchain.x86_64 --arch=x86_64
/Users/srplab/android/android-sdk-macosx/android-ndk-r12b/build/tools/make-standalone-toolchain.sh --install-dir=android-toolchain.x86 --arch=x86
/Users/srplab/android/android-sdk-macosx/android-ndk-r12b/build/tools/make-standalone-toolchain.sh --install-dir=android-toolchain.arm64 --arch=arm64
/Users/srplab/android/android-sdk-macosx/android-ndk-r12b/build/tools/make-standalone-toolchain.sh --install-dir=android-toolchain.arm --arch=arm
```

compile script example

```sh
# compiled with android-ndk-r12b

GO="/usr/local/go/bin/go"

arch=("x86" "x86_64" "arm64" "arm");

for s in ${arch[@]}; do
  echo "build for $s"

  export GOOS=android
  export CGO_ENABLED=1

  if [ "$s" == "arm" ]; then
    export NDK_TOOLCHAIN=/Users/srplab/Desktop/ndk_toolchain/android-toolchain.arm
    export CC=$NDK_TOOLCHAIN/bin/arm-linux-androideabi-gcc
    export GOARCH=arm
    export GOARM=7
  elif [ "$s" == "x86" ]; then
    export NDK_TOOLCHAIN=/Users/srplab/Desktop/ndk_toolchain/android-toolchain.x86
    export CC=$NDK_TOOLCHAIN/bin/i686-linux-android-gcc
    export GOARCH=386
  elif [ "$s" == "x86_64" ]; then
    export NDK_TOOLCHAIN=/Users/srplab/Desktop/ndk_toolchain/android-toolchain.x86_64
    export CC=$NDK_TOOLCHAIN/bin/x86_64-linux-android-gcc
    export GOARCH=amd64
  elif [ "$s" == "arm64" ]; then
    export NDK_TOOLCHAIN=/Users/srplab/Desktop/ndk_toolchain/android-toolchain.arm64
    export CC=$NDK_TOOLCHAIN/bin/aarch64-linux-android-gcc
    export GOARCH=arm64
  fi

  $GO build -buildmode=c-shared -o libstar_go.so
  
  mkdir $s
  cp ./libstar_go.so $s
  rm -rf ./libstar_go.so
 
done

```


### Use the share library, 

use "_DoFile" function of cle to load the share library,  
example on android


```java
package com.example.srplab.testgo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import com.srplab.www.starcore.*;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        /*----init starcore----*/
        StarCoreFactoryPath.StarCoreCoreLibraryPath = this.getApplicationInfo().nativeLibraryDir;
        StarCoreFactoryPath.StarCoreShareLibraryPath = this.getApplicationInfo().nativeLibraryDir;
        StarCoreFactoryPath.StarCoreOperationPath = "/data/data/"+getPackageName()+"/files";

        final StarCoreFactory starcore= StarCoreFactory.GetFactory();
        StarServiceClass Service=starcore._InitSimple("test","123",0,0);
        starcore._RegMsgCallBack_P(new StarMsgCallBackInterface() {
            public Object Invoke(int ServiceGroupID, int uMes, Object wParam, Object lParam) {
                if (uMes == starcore._GetInt("MSG_VSDISPMSG") || uMes == starcore._GetInt("MSG_VSDISPLUAMSG")) {
                    System.out.println((String) wParam);
                }
                if (uMes == starcore._GetInt("MSG_DISPMSG") || uMes == starcore._GetInt("MSG_DISPLUAMSG")) {
                    System.out.println("++++++++++++++++" + (String) wParam);
                }
                return null;
            }
        });
        StarSrvGroupClass SrvGroup = (StarSrvGroupClass)Service._Get("_ServiceGroup");
        Service._CheckPassword(false);

        Object[] result = Service._DoFile("",this.getApplicationInfo().nativeLibraryDir+"/libgo_.so","");
        System.out.println(result);

        System.out.println(Service._Get("GoObject"));
        StarObjectClass GoObject = (StarObjectClass)Service._GetObject("GoObject");
        System.out.println(GoObject);
        System.out.println(GoObject._Call("PrintHello","------------1",234.56));
    }
}
```

API Interface:
--------

```
supported functions: V0.5.0,  test for go version 1.10

stargo:
    InitSimple
    InitSimpleEx
    InitCore
    GetSrvGroup
    ModuleExit
    ModuleClear

    RegMsgCallBack_P     : func(ServiceGroupID uint32, uMsg uint32, wParam interface{}, lParam interface{}) (IsProcessed bool, Result interface{})
    RegDispatchRequest_P : func()
    SRPDispatch
    SRPLock
    SRPUnLock
    SetRegisterCode
    IsRegistered
    SetLocale
    GetLocale
    Version
    GetScriptIndex
    SetScript
    DetachCurrentThread
    CoreHandle


StarSrvGroup:
    CreateService
    GetService
    ClearService
    NewParaPkg   : []interface{}, map[string]inteface{}->dictflag set, []int8/uint8->binary buf []int16/32/... ->
    NewBinBuf
    NewSXml
    IsObject
    IsParaPkg
    IsBinBuf
    IsSXml
    GetServicePath
    SetServicePath
    ServicePathIsSet
    GetCurrentPath
    ImportService
    ClearServiceEx
    RunScript
    RunScriptEx
    DoFile
    DoFileEx
    SetClientPort
    SetTelnetPort
    SetOutputPort
    SetWebServerPort
    InitRaw
    LoadRawModule
    GetLastError
    GetLastErrorInfo
    SUnLockGC
    GetCorePath
    GetUserPath
    GetLocalIP
    GetLocalIPEx
    GetObjectNum
    ActiveScriptInterface
    PreCompile

StarService:
    Get          : "_Name"  "_ServiceGroup"
    GetObject
    GetObjectEx
    New
    RunScript
    RunScriptEx
    DoFile
    DoFileEx
    IsServiceRegistered
    CheckPassword
    LoadRawModule
    NewRawProxy
    ImportRawContext
    ImportRawObject
    GetLastError
    GetLastErrorInfo

StarParaPkg:
    GetNumber
    Get         : int value(index)
    GetBool
    GetInt
    GetInt64
    GetString
    GetDouble
    GetObject
    GetParaPkg
    GetBinBuf

    Clear
    AppendFrom
    Set
    Build
    Free
    Dispose
    ReleaseOwner
    AsDict
    IsDict
    FromJSon
    ToJSon

StarBinBuf :
    GetOffset

    Init
    Clear
    SaveToFile
    SaveToFile
    Read
    Write
    Free
    ReleaseOwner
    Dispose

StarSXml :
    LoadFromFile
    LoadFromBuf
    LoadFromBufEx
    SaveToFile
    SaveToBuf
    GetStandalone
    GetVersion
    GetEncoding
    FindElement
    FindElementEx
    FirstElement
    NextElement
    ParentElement
    GetElement
    GetElementEx
    GetNs
    GetNsValue
    FindAttribute
    FirstAttribute
    NextAttribute
    GetAttributeName
    GetAttributeValue
    GetSingleText
    FirstText
    NextText
    GetText
    SetDeclaration
    RemoveDeclaration

StarObject :
    Get   : "_Service"  "_Class"  "_ID"  "_Name"
    GetBool
    GetInt
    GetInt64
    GetString
    GetDouble
    GetObject
    GetParaPkg
    GetBinBuf

    Set   : "_Name"
    Call
    CallBool
    CallInt
    CallInt64
    CallString
    CallDouble
    CallObject
    CallParaPkg
    CallBinBuf

    New
    Free
    Dispose
    RawToParaPkg
    DeferFree
    IsInFree
    GetSourceScript
    GetRefEx
    GetRefInfo
    IsValid
    GetLastError
    GetLastErrorInfo
    RegScriptProc_P      :  func(CleGroup *StarSrvGroup,CleService *StarService,CleObject *StarObject,Paras []interface{}) interface{}
    ReleaseOwnerEx
    IsSLock
    AttachRawObject

note:

1)  As for how to use these functions, please refer to the interface manual and programming guide

2)  Conversion of variable types :
go                                ->       other script

bool                                               bool
int8,uint8,int16,uint16,int32,uint32               int
int,uint                                           int or int64
float32,float64                                    double
string                                             string
map[string]interface{}                             parapkg dict
[]bool                                             parapkg(bool)
[]int8,[]uint8                                     binbuf
[]int16,[]uint16,[]int32,[]uint32   parapkg(int)
[]int,[]uint                                       parapkg(int/int64)
[]int64,[]uint64                                   parapkg(int64)
[]float32,[]float64                                parapkg(double)
[]string                                           parapkg(string)
others                                             cle object (raw)

3)  function can be called from other scripts
struct methods : the input or output parameter must be types defined above or interface{} / []interface{}
lambda functions

4)  stargo.RegAttachRawContextCallBack_P is used to return go object when other scripts call Service._ImportRawContext

5)  stargo.RegScriptTermCallBack_P is used before go share library unloaded

6)  stargo.RegScriptInitCallBack_P is used after go share library loaded

7)  stargo.Println/Printf/Print should be used instead of fmt.Println/Printf/Print

```



More Info:
--------

For more information about use how to use cle's APIs, please refer to 

[common language extension_programmer's guide_en.pdf](https://github.com/srplab/starcore_for_android/blob/master/docs/common%20language%20extension_programmer's%20guide_en.pdf)

and,

[common language extension_interface for script_en.pdf](https://github.com/srplab/starcore_for_android/blob/master/docs/common%20language%20extension_interface%20for%20script_en.pdf)

For more examples, please refer to 

[srplab.github.io](https://srplab.github.io)
