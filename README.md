# Common Language Extension (CLE) 

Portability is an issue we must consider when developing applications. The most portable language is ansi c. However, due to the lack of functional libraries, applications are not easy to write and need to take a long time to market. An alternative is to use a scripting language, such as python, ruby, or lua. With the help of CLE middleware, these scripting languages can run on most platforms such as windows, windows 10, ios, android, linux.

CLE is a middleware to support mixed programming of multiple languages. Any language of c/c++, lua, python, c#, java can access most classes, functions, variables, or modules of other languages directly, which makes existing code or libraries to be reused easily. Developers can write code using the favorite language and then use them in other applications written with different languages. CLE is simple, which is a single core share library with libraries corresponding to each script language.

We recommend that developers write primary logic in a scripting language, and GUI or device-specific parts in the platform-dependent language. Not only ensure application portability, but also take advantage of the platform SDK. Using scripting language may result in a little large about the size of installation packages and a slightly decrease in performance, but these should not be a problem as hardware performance improves and storage increases
 

### It's major features are listed below:

- Supporting multiple platforms. CLE supports windows xp, windows 7, windows 8, linux x86, android, ios, windows 10
- Supporting multiple script languages. CLE supports c/c++, lua, python, java, c#,ruby
- Integrated two-way bridge between scripts. Any language of the c/c++, lua, python, java, c# can access most classes, functions, methods, or modules of another language directly.
- Providing unified interface to multiple script language.


## starcore_for_go v0.5

The library is written in golang, which supports go language to call other scripting languages such as python, java, ruby, c#, etc.And, also support use go language to write shared libraries for other scripting languages.

It supports android, windows and linux platforms

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

```sh
 $ gomobile build -target=android/arm

 And the extract libgo_.so from the .apk package
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


More Info:
--------

For more information about use how to use cle's APIs, please refer to 

[common language extension_programmer's guide_en.pdf](https://github.com/srplab/starcore_for_android/blob/master/docs/common%20language%20extension_programmer's%20guide_en.pdf)

and,

[common language extension_interface for script_en.pdf](https://github.com/srplab/starcore_for_android/blob/master/docs/common%20language%20extension_interface%20for%20script_en.pdf)

For more examples, please refer to 

[srplab.github.io](https://srplab.github.io)
