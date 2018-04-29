package stargo

/*
#cgo windows CFLAGS: -I./include
#cgo windows LDFLAGS: -L./windows.static -lvsopenapi_c_stub -lws2_32 -lrpcrt4

#cgo linux,!android CFLAGS: -I./include -DENV_LINUX -DENV_M64
#cgo linux,!android LDFLAGS: -L./linux.static -lvsopenapi_c_stub -ldl

#cgo android,arm  CFLAGS: -Wno-macro-redefined -I./include -DENV_ANDROID -DENV_M32
#cgo android,arm LDFLAGS: -L./android.static/armv7 -lvsopenapi_c_stub -ldl

#cgo android,arm64  CFLAGS: -Wno-macro-redefined -I./include -DENV_ANDROID -DENV_M64
#cgo android,arm64 LDFLAGS: -L./android.static/arm64 -lvsopenapi_c_stub -ldl

#cgo android,386  CFLAGS: -Wno-macro-redefined -I./include -DENV_ANDROID -DENV_M32
#cgo android,386 LDFLAGS: -L./android.static/x86 -lvsopenapi_c_stub -ldl

#cgo android,amd64  CFLAGS: -Wno-macro-redefined -I./include -DENV_ANDROID -DENV_M64
#cgo android,amd64 LDFLAGS: -L./android.static/x86_64 -lvsopenapi_c_stub -ldl

//darwin

#include "vsopenapi_c.h"
#include "vsopenapi_c_stub.h"
#include "stargo_native.h"
*/
import "C"

import (
	"fmt"
	"reflect"
	"runtime"
	"strings"
	"sync"
	"unsafe"
)

/*-----------------------------------------------------------------------
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

-------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/*--constant
/*-----------------------------------------------------------------------*/
var MSG_APPEVENT uint32 = C.MSG_APPEVENT
var MSG_VSDISPMSG uint32 = C.MSG_VSDISPMSG
var MSG_VSDISPLUAMSG uint32 = C.MSG_VSDISPLUAMSG
var MSG_DISPMSG uint32 = C.MSG_DISPMSG
var MSG_DISPLUAMSG uint32 = C.MSG_DISPLUAMSG
var MSG_EXIT uint32 = C.MSG_EXIT
var MSG_HYPERLINK uint32 = C.MSG_HYPERLINK
var MSG_SETMANAGERCAPTION uint32 = C.MSG_SETMANAGERCAPTION
var MSG_ONTELNETSTRING_PREEXECUTE uint32 = C.MSG_ONTELNETSTRING_PREEXECUTE
var MSG_ONTELNETSTRING uint32 = C.MSG_ONTELNETSTRING

var GO_TYPE_NONE int = 0
var GO_TYPE_BOOL int = 1
var GO_TYPE_INT8 int = 2
var GO_TYPE_UINT8 int = 3
var GO_TYPE_INT16 int = 4
var GO_TYPE_UINT16 int = 5
var GO_TYPE_INT32 int = 6
var GO_TYPE_UINT32 int = 7
var GO_TYPE_INT int = 8
var GO_TYPE_UINT int = 9
var GO_TYPE_FLOAT32 int = 10
var GO_TYPE_FLOAT64 int = 11
var GO_TYPE_STRING int = 12
var GO_TYPE_INT64 int = 13
var GO_TYPE_UINT64 int = 14

var GO_TYPE_BOOL_SLICE int = 21
var GO_TYPE_INT8_SLICE int = 22
var GO_TYPE_UINT8_SLICE int = 23
var GO_TYPE_INT16_SLICE int = 24
var GO_TYPE_UINT16_SLICE int = 25
var GO_TYPE_INT32_SLICE int = 26
var GO_TYPE_UINT32_SLICE int = 27
var GO_TYPE_INT_SLICE int = 28
var GO_TYPE_UINT_SLICE int = 29
var GO_TYPE_FLOAT32_SLICE int = 20
var GO_TYPE_FLOAT64_SLICE int = 21
var GO_TYPE_STRING_SLICE int = 22
var GO_TYPE_INT64_SLICE int = 23
var GO_TYPE_UINT64_SLICE int = 24

var GO_TYPE_INTERFACE int = 0 /*--GO_TYPE_NONE */
var GO_TYPE_INTERFACE_SLICE int = 32

var GO_TYPE_STAROBJECT int = 41
var GO_TYPE_STARPARAPKG int = 42
var GO_TYPE_STARBINBUF int = 43
var GO_TYPE_STARSXML int = 44

/*-----------------------------------------------------------------------*/
/*--global variable
/*-----------------------------------------------------------------------*/
var g_MsgCallBack func(ServiceGroupID uint32, uMsg uint32, wParam interface{}, lParam interface{}) (IsProcessed bool, Result interface{}) = nil
var g_DispatchRequestCallBack func() = nil
var g_AttachRawContextCallBack func(ContextName string) interface{} = nil
var g_ScriptTermCallBack func() = nil
var g_ScriptInitCallBack func(SrvGroup *StarSrvGroup, Service *StarService) = nil

/*-----------------------------------------------------------------------*/
/*--weak reference table
/*-----------------------------------------------------------------------*/
/*
> If an object is reference only be a unsafe.Pointer, will this object be
> collected?
Yes.
*/

type _StarCore_WeakTableItem struct {
	RefCount uint

	ObjType int
	ObjData unsafe.Pointer //weak reference   or

	SObjData interface{} //strong reference
}

var g_WeakTable_RefCount C.VS_UWORD = 0
var g_WeakTable map[C.VS_UWORD]*_StarCore_WeakTableItem = nil
var WeakTableMutexInitFlag bool = false
var WeakTableMutex *sync.Mutex

/*---create new weak reference--*/
func NewGoObjectRef(ObjData interface{}, RefCount C.VS_UWORD) C.VS_UWORD {
	WeakTableMutex.Lock()
	if g_WeakTable == nil {
		g_WeakTable = make(map[C.VS_UWORD]*_StarCore_WeakTableItem)
	}
	if RefCount != 0 {
		olditem, ok := g_WeakTable[RefCount]
		if ok {
			olditem.RefCount = olditem.RefCount + 1
			WeakTableMutex.Unlock()
			return RefCount
		}
	}
	item := new(_StarCore_WeakTableItem)
	item.RefCount = 0
	switch ObjData.(type) {
	case *StarSrvGroup:
		item.ObjData = (unsafe.Pointer)(ObjData.(*StarSrvGroup))
		item.ObjType = OBJECTTYPE_STARSRVGROUP
	case *StarService:
		item.ObjData = (unsafe.Pointer)(ObjData.(*StarService))
		item.ObjType = OBJECTTYPE_STARSERVICE
	case *StarParaPkg:
		item.ObjData = (unsafe.Pointer)(ObjData.(*StarParaPkg))
		item.ObjType = OBJECTTYPE_STARPARAPKG
	case *StarBinBuf:
		item.ObjData = (unsafe.Pointer)(ObjData.(*StarBinBuf))
		item.ObjType = OBJECTTYPE_STARBINBUF
	case *StarSXml:
		item.ObjData = (unsafe.Pointer)(ObjData.(*StarSXml))
		item.ObjType = OBJECTTYPE_STARSXML
	case *StarObject:
		item.ObjData = (unsafe.Pointer)(ObjData.(*StarObject))
		item.ObjType = OBJECTTYPE_STAROBJECT
	default:
		WeakTableMutex.Unlock()
		panic(fmt.Errorf(
			"weak reference type error",
		))
		return 0
	}
	item.SObjData = nil
	g_WeakTable[g_WeakTable_RefCount] = item
	NewRefCount := g_WeakTable_RefCount
	g_WeakTable_RefCount = g_WeakTable_RefCount + 1
	WeakTableMutex.Unlock()
	return NewRefCount
}

func NewGoObjectRefStrong(ObjData interface{}, RefCount C.VS_UWORD) C.VS_UWORD {
	WeakTableMutex.Lock()
	if g_WeakTable == nil {
		g_WeakTable = make(map[C.VS_UWORD]*_StarCore_WeakTableItem)
	}
	if RefCount != 0 {
		olditem, ok := g_WeakTable[RefCount]
		if ok {
			if olditem.SObjData != nil { /* is strong */
				olditem.RefCount = olditem.RefCount + 1
				WeakTableMutex.Unlock()
				return RefCount
			} else {
				olditem.SObjData = ObjData
				olditem.ObjData = nil
				olditem.RefCount = 0
				WeakTableMutex.Unlock()
				return RefCount
			}
		}
	}
	item := new(_StarCore_WeakTableItem)
	item.RefCount = 0
	item.RefCount = 0
	switch ObjData.(type) {
	case *StarSrvGroup:
		item.ObjType = OBJECTTYPE_STARSRVGROUP
	case *StarService:
		item.ObjType = OBJECTTYPE_STARSERVICE
	case *StarParaPkg:
		item.ObjType = OBJECTTYPE_STARPARAPKG
	case *StarBinBuf:
		item.ObjType = OBJECTTYPE_STARBINBUF
	case *StarSXml:
		item.ObjType = OBJECTTYPE_STARSXML
	case *StarObject:
		item.ObjType = OBJECTTYPE_STAROBJECT
	default:
		item.ObjType = OBJECTTYPE_INTERFACE
		/*
			ref_typ := reflect.TypeOf(v)
			if ref_typ.Kind() == reflect.Ptr && ref_typ.Elem().Kind() == reflect.Struct {
				item.ObjType = OBJECTTYPE_STRUCTPTR
			} else {
				WeakTableMutex.Unlock()
				panic(fmt.Errorf(
					"weak reference type error",
				))
				return 0
			}
		*/
	}
	item.ObjData = nil
	item.SObjData = ObjData
	g_WeakTable[g_WeakTable_RefCount] = item
	NewRefCount := g_WeakTable_RefCount
	g_WeakTable_RefCount = g_WeakTable_RefCount + 1
	WeakTableMutex.Unlock()
	return NewRefCount
}

/*---delete reference--*/
func DeleteGoObjectRef(RefCount C.VS_UWORD) {
	if RefCount == 0 {
		return
	}
	WeakTableMutex.Lock()
	if g_WeakTable == nil {
		g_WeakTable = make(map[C.VS_UWORD]*_StarCore_WeakTableItem)
	}
	olditem, ok := g_WeakTable[RefCount]
	if ok {
		if olditem.RefCount > 0 {
			olditem.RefCount = olditem.RefCount - 1
			WeakTableMutex.Unlock()
			return
		}
		delete(g_WeakTable, RefCount)
		WeakTableMutex.Unlock()
		return
	}
	WeakTableMutex.Unlock()
	return
}

/*---delete reference--*/
func DeleteGoObjectAllRef(RefCount C.VS_UWORD) {
	if RefCount == 0 {
		return
	}
	WeakTableMutex.Lock()
	if g_WeakTable == nil {
		g_WeakTable = make(map[C.VS_UWORD]*_StarCore_WeakTableItem)
	}
	_, ok := g_WeakTable[RefCount]
	if ok {
		delete(g_WeakTable, RefCount)
		WeakTableMutex.Unlock()
		return
	}
	WeakTableMutex.Unlock()
	return
}

func RefToGoObject(RefCount C.VS_UWORD) interface{} {
	if RefCount == 0 {
		return nil
	}
	WeakTableMutex.Lock()
	defer WeakTableMutex.Unlock()
	olditem, ok := g_WeakTable[RefCount]
	if ok {
		if olditem.ObjData != nil {
			switch olditem.ObjType {
			case OBJECTTYPE_STARSRVGROUP:
				return (*StarSrvGroup)(olditem.ObjData)
			case OBJECTTYPE_STARSERVICE:
				return (*StarService)(olditem.ObjData)
			case OBJECTTYPE_STARPARAPKG:
				return (*StarParaPkg)(olditem.ObjData)
			case OBJECTTYPE_STARBINBUF:
				return (*StarBinBuf)(olditem.ObjData)
			case OBJECTTYPE_STARSXML:
				return (*StarSXml)(olditem.ObjData)
			case OBJECTTYPE_STAROBJECT:
				return (*StarObject)(olditem.ObjData)
			}
		} else {
			return olditem.SObjData
		}
	}
	return nil
}

/*-----------------------------------------------------------------------*/
type _StarCore_DeferHeader struct {
	ObjData interface{}
	Up      *_StarCore_DeferHeader
	Down    *_StarCore_DeferHeader
}

var TermObjectDeferQueueRoot *_StarCore_DeferHeader = nil
var TermObjectDeferQueueMutexInitFlag bool = false
var TermObjectDeferQueueMutex *sync.Mutex

func TermObjectDefer_Insert(ObjData interface{}) {
	if TermObjectDeferQueueMutexInitFlag == true {
		TermObjectDeferQueueMutex.Lock()
	}
	Buf := new(_StarCore_DeferHeader)
	Buf.ObjData = ObjData
	Buf.Up = nil
	Buf.Down = nil
	if TermObjectDeferQueueRoot == nil {
		TermObjectDeferQueueRoot = Buf
	} else {
		TermObjectDeferQueueRoot.Up = Buf
		Buf.Down = TermObjectDeferQueueRoot
		TermObjectDeferQueueRoot = Buf
	}
	if TermObjectDeferQueueMutexInitFlag == true {
		TermObjectDeferQueueMutex.Unlock()
	}
}

var TermObjectDefer_Free_Tick1 C.VS_UWORD = 0

func TermObjectDefer_Free(FreeAll bool) {
	var MyQueue *_StarCore_DeferHeader
	var count int
	var maxnum int
	var Tick2 C.VS_UWORD
	var LocalTermObjectDeferQueueRoot *_StarCore_DeferHeader

	if FreeAll == true {

		if TermObjectDeferQueueMutexInitFlag == true {
			TermObjectDeferQueueMutex.Lock()
		}
		LocalTermObjectDeferQueueRoot = TermObjectDeferQueueRoot
		TermObjectDeferQueueRoot = nil
		if TermObjectDeferQueueMutexInitFlag == true {
			TermObjectDeferQueueMutex.Unlock()
		}

		for {
			if LocalTermObjectDeferQueueRoot == nil {
				break
			}
			MyQueue = LocalTermObjectDeferQueueRoot
			LocalTermObjectDeferQueueRoot = LocalTermObjectDeferQueueRoot.Down
			_TermObject_Defer(MyQueue.ObjData)
		}
	} else {
		if TermObjectDefer_Free_Tick1 == 0 {
			TermObjectDefer_Free_Tick1 = C.vs_tm_gettickcount()
		}
		Tick2 = C.vs_tm_gettickcount()
		if Tick2 < TermObjectDefer_Free_Tick1 {
			TermObjectDefer_Free_Tick1 = Tick2
			return
		}
		if Tick2-TermObjectDefer_Free_Tick1 < 20 { //100ms
			maxnum = 5
		} else if Tick2-TermObjectDefer_Free_Tick1 < 50 { //100ms
			maxnum = 20
		} else {
			maxnum = 200 //--each second free 10000, then 500ms free 5000, each 100ms free 1000, each 20 is 200
		}

		LocalTermObjectDeferQueueRoot = nil
		if TermObjectDeferQueueMutexInitFlag == true {
			TermObjectDeferQueueMutex.Lock()
		}
		count = 0
		for {
			if TermObjectDeferQueueRoot == nil {
				break
			}
			if count > maxnum {
				break //each 20ms
			}
			MyQueue = TermObjectDeferQueueRoot
			TermObjectDeferQueueRoot = TermObjectDeferQueueRoot.Down
			if TermObjectDeferQueueRoot != nil {
				TermObjectDeferQueueRoot.Up = nil
			}

			MyQueue.Up = nil
			MyQueue.Down = nil

			if LocalTermObjectDeferQueueRoot == nil {
				LocalTermObjectDeferQueueRoot = MyQueue
			} else {
				LocalTermObjectDeferQueueRoot.Up = MyQueue
				MyQueue.Down = LocalTermObjectDeferQueueRoot
				LocalTermObjectDeferQueueRoot = MyQueue
			}
			count = count + 1
		}
		if TermObjectDeferQueueMutexInitFlag == true {
			TermObjectDeferQueueMutex.Unlock()
		}

		for {
			if LocalTermObjectDeferQueueRoot == nil {
				break
			}
			MyQueue = LocalTermObjectDeferQueueRoot
			LocalTermObjectDeferQueueRoot = LocalTermObjectDeferQueueRoot.Down
			_TermObject_Defer(MyQueue.ObjData)
		}
		TermObjectDefer_Free_Tick1 = C.vs_tm_gettickcount()
	}
}

/*-----------------------------------------------------------------------*/
/*----common interface */
const OBJECTTYPE_STARSRVGROUP int = 1
const OBJECTTYPE_STARSERVICE int = 2
const OBJECTTYPE_STARSERVICEITEM int = 3
const OBJECTTYPE_STARPARAPKG int = 4
const OBJECTTYPE_STARQUERYRECORD int = 5
const OBJECTTYPE_STARBINBUF int = 6
const OBJECTTYPE_STARSXML int = 7
const OBJECTTYPE_STARFUNCTIONPARA int = 8
const OBJECTTYPE_STARCOMMINTERFACE int = 9
const OBJECTTYPE_STAROBJECT int = 10
const OBJECTTYPE_STARSTRUCT int = 11
const OBJECTTYPE_STARFUNCTION int = 12
const OBJECTTYPE_STARCALLBACK int = 13

const OBJECTTYPE_STRUCTPTR int = 14
const OBJECTTYPE_INTERFACE int = 15

/*-----------------------------------------------------------------------*/
type StarServiceBody struct {
	ServiceGroupID      C.VS_ULONG
	SRPInterface        unsafe.Pointer
	IsClearedByStarCore C.VS_BOOL
	RefItem             C.VS_UWORD
}

type StarService struct {
	ObjData *StarServiceBody
}

func ToStarService(fdata *StarSrvGroupBody, SRPInterface unsafe.Pointer) *StarService {
	var SRPInterfaceItem *StructOfSRPSrvGroup_SRPInterfaceItem
	var ServiceID C.VS_UUID

	if SRPInterface == nil {
		return nil
	}

	TermObjectDefer_Free(false)

	C.Star_SRPI_GetServiceID(SRPInterface, &ServiceID)
	SRPInterfaceItem = fdata.SRPInterfaceItemRoot
	for {
		if SRPInterfaceItem == nil {
			break
		}
		if C.stargo_uuidisequal(&SRPInterfaceItem.ServiceID, &ServiceID) == C.VS_TRUE {
			break
		}
		SRPInterfaceItem = SRPInterfaceItem.Down
	}
	if SRPInterfaceItem != nil {
		DeleteGoObjectAllRef(SRPInterfaceItem.ServiceObject)
		SRPInterfaceItem.ServiceObject = 0
	} else {
		SRPInterfaceItem = new(StructOfSRPSrvGroup_SRPInterfaceItem)
		if fdata.SRPInterfaceItemRoot == nil {
			fdata.SRPInterfaceItemRoot = SRPInterfaceItem
		} else {
			fdata.SRPInterfaceItemRoot.Up = SRPInterfaceItem
			SRPInterfaceItem.Down = fdata.SRPInterfaceItemRoot
			fdata.SRPInterfaceItemRoot = SRPInterfaceItem
		}
	}

	m_StarServiceBody := new(StarServiceBody)
	m_StarServiceBody.SRPInterface = SRPInterface
	m_StarServiceBody.ServiceGroupID = fdata.ServiceGroupID
	m_StarServiceBody.IsClearedByStarCore = C.VS_FALSE
	s := new(StarService)
	s.ObjData = m_StarServiceBody
	s.ObjData.RefItem = 0
	runtime.SetFinalizer(s, (*StarService).Free)

	SRPInterfaceItem.ServiceObject = NewGoObjectRefStrong(s, 0)
	SRPInterfaceItem.ServiceID = ServiceID
	return s
}

func (s *StarService) String() string {
	Result := C.Star_SRPI_GetServiceName(s.ObjData.SRPInterface)
	if Result == nil {
		return "service not load"
	} else {
		return C.GoString(Result)
	}
}

func (s *StarService) Free() {
	DeleteGoObjectAllRef(s.ObjData.RefItem)

	if s.ObjData.IsClearedByStarCore == C.VS_FALSE && C.StarGo_ModuleInitFlag == C.VS_TRUE {
		TermObjectDefer_Insert(s.ObjData)
	} else {
		_TermObject_Defer(s.ObjData)
	}
}

/*-----------------------------------------------------------------------*/
type StructOfSRPSrvGroup_SRPInterfaceItem struct {
	ServiceID     C.VS_UUID
	ServiceObject C.VS_UWORD /*ref*/
	Up            *StructOfSRPSrvGroup_SRPInterfaceItem
	Down          *StructOfSRPSrvGroup_SRPInterfaceItem
}

type StarSrvGroupBody struct {
	ServiceGroupID       C.VS_ULONG
	BasicSRPInterface    unsafe.Pointer
	SRPInterfaceItemRoot *StructOfSRPSrvGroup_SRPInterfaceItem
	ObjectIndexTree      unsafe.Pointer /* save StructOfObjectRefInSrvGroup */
	RefItem              C.VS_UWORD
}

type StarSrvGroup struct {
	ObjData *StarSrvGroupBody
}

func ToStarSrvGroup(ServiceGroupID C.VS_ULONG, BasicSRPInterface unsafe.Pointer) *StarSrvGroup {
	m_StarSrvGroupBody := new(StarSrvGroupBody)
	m_StarSrvGroupBody.BasicSRPInterface = BasicSRPInterface
	m_StarSrvGroupBody.ServiceGroupID = ServiceGroupID
	m_StarSrvGroupBody.SRPInterfaceItemRoot = nil
	m_StarSrvGroupBody.ObjectIndexTree = C.Star_SRPBasic_CreateIDIndex_Nor(BasicSRPInterface, 0)

	s := new(StarSrvGroup)
	s.ObjData = m_StarSrvGroupBody
	s.ObjData.RefItem = NewGoObjectRef(s, 0)
	runtime.SetFinalizer(s, (*StarSrvGroup).Free)

	C.Star_SRPBasic_RegObjectIDChangeNotify(BasicSRPInterface, (C.VS_ObjectIDChangeNotifyProc)(C.stargo_ObjectIDChangeNotify), (C.VS_UWORD)(s.ObjData.RefItem))
	C.Star_SRPBasic_RegObjectFreeNotify(BasicSRPInterface, (C.VS_ObjectFreeNotifyProc)(C.stargo_ObjectFreeNotify), (C.VS_UWORD)(s.ObjData.RefItem))

	return s
}

func (s *StarSrvGroup) String() string {
	Result := C.Star_SRPBasic_QueryActiveService(s.ObjData.BasicSRPInterface, nil)
	if Result == nil {
		return "service not load"
	} else {
		return C.GoString(Result)
	}
}

func (s *StarSrvGroup) Free() {
	DeleteGoObjectAllRef(s.ObjData.RefItem)

	if C.StarGo_ModuleInitFlag == C.VS_TRUE {
		TermObjectDefer_Insert(s.ObjData)
	} else {
		_TermObject_Defer(s.ObjData)
	}
}

/*-----------------------------------------------------------------------*/
type StarParaPkgBody struct {
	ParaPkg             unsafe.Pointer
	ServiceGroupID      C.VS_ULONG
	FreeFlag            C.VS_BOOL
	IsClearedByStarCore C.VS_BOOL
	RefItem             C.VS_UWORD
}

type StarParaPkg struct {
	ObjData *StarParaPkgBody
}

func ToStarParaPkg(ParaPkg unsafe.Pointer, ServiceGroupID C.VS_ULONG, FreeFlag C.VS_BOOL) *StarParaPkg {

	TermObjectDefer_Free(false)

	m_StarParaPkgBody := new(StarParaPkgBody)
	m_StarParaPkgBody.ParaPkg = ParaPkg
	m_StarParaPkgBody.ServiceGroupID = ServiceGroupID
	m_StarParaPkgBody.FreeFlag = FreeFlag
	m_StarParaPkgBody.IsClearedByStarCore = C.VS_FALSE
	if m_StarParaPkgBody.FreeFlag == C.VS_FALSE {
		C.Star_SRPParaPkg_AddRef(m_StarParaPkgBody.ParaPkg)
		m_StarParaPkgBody.FreeFlag = C.VS_TRUE
	}

	s := new(StarParaPkg)
	s.ObjData = m_StarParaPkgBody
	s.ObjData.RefItem = NewGoObjectRef(s, 0)
	runtime.SetFinalizer(s, (*StarParaPkg).SelfFree)

	C.Star_SRPControl_RegScriptObject(C.StarGo_SRPControlInterface, (C.VS_UWORD)(s.ObjData.RefItem), C.stargo_FreeScriptObject, 0)
	return s
}

func CreateStarParaPkg(BasicSRPInterface unsafe.Pointer) *StarParaPkg {
	var ParaPkg unsafe.Pointer

	TermObjectDefer_Free(false)

	ParaPkg = C.Star_SRPBasic_GetParaPkgInterface(BasicSRPInterface)
	if ParaPkg == C.NULL {
		return nil
	}
	return ToStarParaPkg(ParaPkg, C.Star_SRPBasic_GetServiceGroupID(BasicSRPInterface), C.VS_TRUE)
}

func (s *StarParaPkg) String() string {
	return "parapkg"
}

func (s *StarParaPkg) SelfFree() {
	DeleteGoObjectAllRef(s.ObjData.RefItem)

	if s.ObjData.IsClearedByStarCore == C.VS_FALSE && C.StarGo_ModuleInitFlag == C.VS_TRUE {
		TermObjectDefer_Insert(s.ObjData)
	} else {
		_TermObject_Defer(s.ObjData)
	}
}

/*-----------------------------------------------------------------------*/
type StarBinBufBody struct {
	BinBuf              unsafe.Pointer
	ServiceGroupID      C.VS_ULONG
	FreeFlag            C.VS_BOOL
	IsClearedByStarCore C.VS_BOOL
	RefItem             C.VS_UWORD
}

type StarBinBuf struct {
	ObjData *StarBinBufBody
}

func ToStarBinBuf(BinBuf unsafe.Pointer, ServiceGroupID C.VS_ULONG, FreeFlag C.VS_BOOL) *StarBinBuf {

	TermObjectDefer_Free(false)

	m_StarBinBufBody := new(StarBinBufBody)
	m_StarBinBufBody.BinBuf = BinBuf
	m_StarBinBufBody.ServiceGroupID = ServiceGroupID
	m_StarBinBufBody.FreeFlag = FreeFlag
	m_StarBinBufBody.IsClearedByStarCore = C.VS_FALSE
	if m_StarBinBufBody.FreeFlag == C.VS_FALSE {
		C.Star_SRPBinBuf_AddRef(m_StarBinBufBody.BinBuf)
		m_StarBinBufBody.FreeFlag = C.VS_TRUE
	}

	s := new(StarBinBuf)
	s.ObjData = m_StarBinBufBody
	s.ObjData.RefItem = NewGoObjectRef(s, 0)
	runtime.SetFinalizer(s, (*StarParaPkg).SelfFree)

	C.Star_SRPControl_RegScriptObject(C.StarGo_SRPControlInterface, (C.VS_UWORD)(s.ObjData.RefItem), C.stargo_FreeScriptObject, 0)
	return s
}

func CreateStarBinBuf(BasicSRPInterface unsafe.Pointer) *StarBinBuf {
	var BinBuf unsafe.Pointer

	TermObjectDefer_Free(false)

	BinBuf = C.Star_SRPBasic_GetSRPBinBufInterface(BasicSRPInterface)
	if BinBuf == C.NULL {
		return nil
	}
	return ToStarBinBuf(BinBuf, C.Star_SRPBasic_GetServiceGroupID(BasicSRPInterface), C.VS_TRUE)
}

func (s *StarBinBuf) String() string {
	return "binbuf"
	/*	missing GetName function for v2.5.2
		    if( s.ObjData->BinBuf == nil ){
				return "binbuf";
			}
			return C.GoString(ObjData->BinBuf->GetName());
	*/
}

func (fdata *StarBinBuf) SelfFree() {
	DeleteGoObjectAllRef(fdata.ObjData.RefItem)

	if fdata.ObjData.IsClearedByStarCore == C.VS_FALSE && C.StarGo_ModuleInitFlag == C.VS_TRUE {
		TermObjectDefer_Insert(fdata.ObjData)
	} else {
		_TermObject_Defer(fdata.ObjData)
	}
}

/*-----------------------------------------------------------------------*/
type StarSXmlBody struct {
	SXml                unsafe.Pointer
	ServiceGroupID      C.VS_ULONG
	FreeFlag            C.VS_BOOL
	IsClearedByStarCore C.VS_BOOL
	RefItem             C.VS_UWORD
}

type StarSXml struct {
	ObjData *StarSXmlBody
}

func ToStarSXml(SXml unsafe.Pointer, ServiceGroupID C.VS_ULONG, FreeFlag C.VS_BOOL) *StarSXml {
	m_StarSXmlBody := new(StarSXmlBody)
	m_StarSXmlBody.SXml = SXml
	m_StarSXmlBody.ServiceGroupID = ServiceGroupID
	m_StarSXmlBody.FreeFlag = FreeFlag
	m_StarSXmlBody.IsClearedByStarCore = C.VS_FALSE
	if m_StarSXmlBody.FreeFlag == C.VS_FALSE {
		C.Star_SRPSXML_AddRef(m_StarSXmlBody.SXml)
		m_StarSXmlBody.FreeFlag = C.VS_TRUE
	}

	s := new(StarSXml)
	s.ObjData = m_StarSXmlBody
	s.ObjData.RefItem = NewGoObjectRef(s, 0)
	runtime.SetFinalizer(s, (*StarSXml).SelfFree)

	C.Star_SRPControl_RegScriptObject(C.StarGo_SRPControlInterface, (C.VS_UWORD)(s.ObjData.RefItem), C.stargo_FreeScriptObject, 0)
	return s
}

func CreateStarSXml(BasicSRPInterface unsafe.Pointer) *StarSXml {
	var SXml unsafe.Pointer

	SXml = C.Star_SRPBasic_GetSXMLInterface(BasicSRPInterface)
	if SXml == C.NULL {
		return nil
	}
	return ToStarSXml(SXml, C.Star_SRPBasic_GetServiceGroupID(BasicSRPInterface), C.VS_TRUE)
}

func (s *StarSXml) String() string {
	return "sxml"
}

func (fdata *StarSXml) SelfFree() {
	DeleteGoObjectAllRef(fdata.ObjData.RefItem)

	if fdata.ObjData.IsClearedByStarCore == C.VS_FALSE && C.StarGo_ModuleInitFlag == C.VS_TRUE {
		TermObjectDefer_Insert(fdata.ObjData)
	} else {
		_TermObject_Defer(fdata.ObjData)
	}
}

/*-----------------------------------------------------------------------*/
type StarObjectBody struct {
	ObjectID            C.VS_UUID
	ServiceGroupID      C.VS_ULONG
	NeedFreeFlag        C.VS_BOOL
	IsClearedByStarCore C.VS_BOOL
	RefItem             C.VS_UWORD

	Table map[string]func(CleGroup *StarSrvGroup, CleService *StarService, CleObject *StarObject, Paras []interface{}) interface{}
}

type StarObject struct {
	ObjData *StarObjectBody
}

func ToStarObject(SRPObject unsafe.Pointer, SRPInterface unsafe.Pointer, NeedFreeFlag C.VS_BOOL) *StarObject {
	var ObjectID C.VS_UUID

	TermObjectDefer_Free(false)

	if SRPObject == nil {
		return nil
	}
	C.Star_SRPI_GetID(SRPInterface, SRPObject, &ObjectID)
	RetObject := GoSRPGetObject(C.Star_SRPI_GetServiceGroupID(SRPInterface), &ObjectID)
	if RetObject != nil {
		if NeedFreeFlag == C.VS_TRUE {
			s := fmt.Sprintf("object [%s] to go script set as auto release again", C.GoString(C.Star_SRPI_GetName(SRPInterface, SRPObject)))
			c_s := C.CString(s)
			C.stargo_SRPI_ProcessError(SRPInterface, C.VSFAULT_WARNING, Const_GoString, 0, c_s)
			C.free(unsafe.Pointer(c_s))
		}
		return RetObject
	}
	return _ToStarObject(C.Star_SRPI_GetServiceGroupID(SRPInterface), &ObjectID, NeedFreeFlag)
}

func ToStarObject_Basic(SRPObject unsafe.Pointer, BasicSRPInterface unsafe.Pointer, NeedFreeFlag C.VS_BOOL) *StarObject {
	var ObjectID C.VS_UUID

	TermObjectDefer_Free(false)

	if SRPObject == nil {
		return nil
	}
	C.Star_SRPBasic_GetID(BasicSRPInterface, SRPObject, &ObjectID)
	RetObject := GoSRPGetObject(C.Star_SRPBasic_GetServiceGroupID(BasicSRPInterface), &ObjectID)
	if RetObject != nil {
		if NeedFreeFlag == C.VS_TRUE {
			s := fmt.Sprintf("object [%s] to go script set as auto release again", C.GoString(C.Star_SRPBasic_GetName(BasicSRPInterface, &ObjectID)))
			c_s := C.CString(s)
			C.stargo_SRPBasic_ProcessError(BasicSRPInterface, C.VSFAULT_WARNING, Const_GoString, 0, c_s)
			C.free(unsafe.Pointer(c_s))
		}
		return RetObject
	}
	return _ToStarObject(C.Star_SRPBasic_GetServiceGroupID(BasicSRPInterface), &ObjectID, NeedFreeFlag)
}

func _ToStarObject(ServiceGroupID C.VS_ULONG, ObjectID *C.VS_UUID, NeedFreeFlag C.VS_BOOL) *StarObject {
	m_StarObjectBody := new(StarObjectBody)
	m_StarObjectBody.ServiceGroupID = ServiceGroupID
	m_StarObjectBody.ObjectID = *ObjectID
	m_StarObjectBody.NeedFreeFlag = NeedFreeFlag
	m_StarObjectBody.IsClearedByStarCore = C.VS_FALSE
	m_StarObjectBody.Table = make(map[string]func(CleGroup *StarSrvGroup, CleService *StarService, CleObject *StarObject, Paras []interface{}) interface{})

	s := new(StarObject)
	s.ObjData = m_StarObjectBody
	s.ObjData.RefItem = NewGoObjectRef(s, 0)
	runtime.SetFinalizer(s, (*StarObject).SelfFree)

	SRPInterface := GetSRPServiceInterfaceEx(ServiceGroupID, ObjectID)
	if SRPInterface != C.NULL {
		var SRPObject unsafe.Pointer
		SRPObject = C.Star_SRPI_GetObject(SRPInterface, &s.ObjData.ObjectID)
		if SRPObject != C.NULL {
			if m_StarObjectBody.NeedFreeFlag == C.VS_FALSE {
				C.Star_SRPI_AddRefEx(SRPInterface, SRPObject)
				m_StarObjectBody.NeedFreeFlag = C.VS_TRUE
			}
		}
	}

	GoSRPSetObject(m_StarObjectBody.ServiceGroupID, &m_StarObjectBody.ObjectID, s, C.VS_FALSE)
	C.Star_SRPControl_RegScriptObject(C.StarGo_SRPControlInterface, (C.VS_UWORD)(s.ObjData.RefItem), C.stargo_FreeScriptObject, 0)
	return s
}

func (self *StarObject) String() string {
	var SRPInterface unsafe.Pointer
	var SRPObject unsafe.Pointer

	SRPInterface = GetSRPServiceInterfaceEx(self.ObjData.ServiceGroupID, &self.ObjData.ObjectID)
	if SRPInterface == C.NULL {
		return "unknown"
	}
	SRPObject = C.Star_SRPI_GetObject(SRPInterface, &self.ObjData.ObjectID)
	if SRPObject == C.NULL {
		return "null"
	} else {
		var CharPtr *C.VS_CHAR
		var InterfaceName *C.VS_CHAR

		CharPtr = C.Star_SRPI_GetRawContextType(SRPInterface, SRPObject, &InterfaceName)
		if CharPtr == nil {
			StrName := (*C.VS_CHAR)(C.stargo_ToPointer(C.stargo_SRPI_ScriptCall(SRPInterface, SRPObject, (*C.VS_ULONG)(C.NULL), Const_VS_OBJECTTOSTRINGFUNCNAME, Const_SCRIPTCALL_RETSTRING /*"()s"*/)))
			if StrName != nil {
				return SRPGoSetStr(StrName, false)
			}
			return SRPGoSetStr(C.Star_SRPI_GetName(SRPInterface, SRPObject), false)
		} else {
			var Result string
			StrName := (*C.VS_CHAR)(C.stargo_ToPointer(C.stargo_SRPI_ScriptCall(SRPInterface, SRPObject, (*C.VS_ULONG)(C.NULL), Const_VS_OBJECTTOSTRINGFUNCNAME, Const_SCRIPTCALL_RETSTRING /*"()s"*/)))
			Result = ""
			if StrName != nil {
				Result = fmt.Sprintf("%s[%s:%s]%s", C.GoString(C.Star_SRPI_GetName(SRPInterface, SRPObject)), C.GoString(InterfaceName), C.GoString(CharPtr), C.GoString(StrName))
			} else {
				Result = fmt.Sprintf("%s[%s:%s]", C.GoString(C.Star_SRPI_GetName(SRPInterface, SRPObject)), C.GoString(InterfaceName), C.GoString(CharPtr))
			}
			return Result
		}
	}
}

func (self *StarObject) SelfFree() {
	DeleteGoObjectAllRef(self.ObjData.RefItem)

	if self.ObjData.IsClearedByStarCore == C.VS_FALSE && C.StarGo_ModuleInitFlag == C.VS_TRUE {
		TermObjectDefer_Insert(self.ObjData)
	} else {
		_TermObject_Defer(self.ObjData)
	}
}

/*-----------------------------------------------------------------------*/

func _TermObject_Defer(ObjData interface{}) {
	switch ObjData.(type) {
	case *StarServiceBody:
		{
			var fdata *StarServiceBody

			fdata = ObjData.(*StarServiceBody)
			if fdata.IsClearedByStarCore == C.VS_FALSE {
				if C.StarGo_ModuleInitFlag == C.VS_TRUE && fdata.SRPInterface != C.NULL {
					C.Star_SRPI_Release(fdata.SRPInterface)
					fdata.SRPInterface = nil
				}
				fdata.IsClearedByStarCore = C.VS_TRUE
			}
			if C.StarGo_ModuleInitFlag == C.VS_TRUE && C.StarGo_SRPControlInterface != C.NULL && fdata.RefItem != 0 {
				C.Star_SRPControl_UnRegScriptObject(C.StarGo_SRPControlInterface, (C.VS_UWORD)(fdata.RefItem), (unsafe.Pointer)(C.stargo_FreeScriptObject), 0)
			}
			if fdata.RefItem != 0 {
				DeleteGoObjectAllRef(fdata.RefItem)
				fdata.RefItem = 0
			}
		}

	case *StarSrvGroupBody:
		{
			var fdata *StarSrvGroupBody
			var SRPInterfaceItem *StructOfSRPSrvGroup_SRPInterfaceItem
			var ObjectRefInSrvGroup *C.struct_StructOfObjectRefInSrvGroup
			var QueryRecord C.VS_QUERYRECORD

			fdata = ObjData.(*StarSrvGroupBody)
			if fdata == nil {
				return
			}
			if fdata.BasicSRPInterface != C.NULL && C.StarGo_ModuleInitFlag == C.VS_TRUE {
				if fdata.ObjectIndexTree != C.NULL {
					ObjectRefInSrvGroup = (*C.struct_StructOfObjectRefInSrvGroup)((unsafe.Pointer)(C.Star_SRPBasic_QueryFirstIDKey(fdata.BasicSRPInterface, fdata.ObjectIndexTree, &QueryRecord, (*C.VS_UUID)(C.NULL))))
					for {
						if ObjectRefInSrvGroup == nil {
							break
						}
						DeleteGoObjectAllRef(ObjectRefInSrvGroup.RefItem)
						C.stargo_FreeStructOfObjectRefInSrvGroup(ObjectRefInSrvGroup)
						ObjectRefInSrvGroup = (*C.struct_StructOfObjectRefInSrvGroup)((unsafe.Pointer)(C.Star_SRPBasic_QueryNextIDKey(fdata.BasicSRPInterface, fdata.ObjectIndexTree, &QueryRecord, (*C.VS_UUID)(C.NULL))))
					}
					C.Star_SRPBasic_DestoryIndex(fdata.BasicSRPInterface, fdata.ObjectIndexTree)
					fdata.ObjectIndexTree = nil
				}
				C.Star_SRPBasic_UnRegObjectIDChangeNotify(fdata.BasicSRPInterface, (C.VS_ObjectIDChangeNotifyProc)(C.stargo_ObjectIDChangeNotify), (C.VS_UWORD)(fdata.RefItem))
				C.Star_SRPBasic_UnRegObjectFreeNotify(fdata.BasicSRPInterface, (C.VS_ObjectFreeNotifyProc)(C.stargo_ObjectFreeNotify), (C.VS_UWORD)(fdata.RefItem))

				//--SRPInterfaceItem
				for {
					if fdata.SRPInterfaceItemRoot == nil {
						break
					}
					SRPInterfaceItem = fdata.SRPInterfaceItemRoot
					fdata.SRPInterfaceItemRoot = fdata.SRPInterfaceItemRoot.Down
					DeleteGoObjectAllRef(SRPInterfaceItem.ServiceObject)
				}
				C.Star_SRPBasic_Release(fdata.BasicSRPInterface)
				fdata.BasicSRPInterface = nil
			}

			if fdata.ServiceGroupID != C.VS_INVALID_SERVICEGROUPID {
				GoSRPClearSrvGroupWithID(fdata.ServiceGroupID)
				fdata.ServiceGroupID = C.VS_INVALID_SERVICEGROUPID
			}
			if fdata.RefItem != 0 {
				DeleteGoObjectAllRef(fdata.RefItem)
				fdata.RefItem = 0
			}
		}
	case *StarParaPkg:
		{
			fdata := ObjData.(*StarParaPkgBody)
			if fdata.IsClearedByStarCore == C.VS_FALSE {
				if fdata.FreeFlag == C.VS_TRUE && fdata.ParaPkg != C.NULL {
					if C.StarGo_ModuleInitFlag == C.VS_TRUE {
						C.Star_SRPParaPkg_Release(fdata.ParaPkg)
					}
					fdata.ParaPkg = nil
				}
				fdata.IsClearedByStarCore = C.VS_TRUE
			}
			if C.StarGo_ModuleInitFlag == C.VS_TRUE && C.StarGo_SRPControlInterface != C.NULL && fdata.RefItem != 0 {
				C.Star_SRPControl_UnRegScriptObject(C.StarGo_SRPControlInterface, (C.VS_UWORD)(fdata.RefItem), (unsafe.Pointer)(C.stargo_FreeScriptObject), 0)
			}
			if fdata.RefItem != 0 {
				DeleteGoObjectAllRef(fdata.RefItem)
				fdata.RefItem = 0
			}
		}
	case *StarBinBuf:
		{
			fdata := ObjData.(*StarBinBufBody)
			if fdata.IsClearedByStarCore == C.VS_FALSE {
				if fdata.FreeFlag == C.VS_TRUE && fdata.BinBuf != C.NULL {
					if C.StarGo_ModuleInitFlag == C.VS_TRUE {
						C.Star_SRPBinBuf_Release(fdata.BinBuf)
					}
					fdata.BinBuf = nil
				}
				fdata.IsClearedByStarCore = C.VS_TRUE
			}
			if C.StarGo_ModuleInitFlag == C.VS_TRUE && C.StarGo_SRPControlInterface != C.NULL && fdata.RefItem != 0 {
				C.Star_SRPControl_UnRegScriptObject(C.StarGo_SRPControlInterface, (C.VS_UWORD)(fdata.RefItem), (unsafe.Pointer)(C.stargo_FreeScriptObject), 0)
			}
			if fdata.RefItem != 0 {
				DeleteGoObjectAllRef(fdata.RefItem)
				fdata.RefItem = 0
			}
		}
	case *StarSXml:
		{
			fdata := ObjData.(*StarSXmlBody)
			if fdata.IsClearedByStarCore == C.VS_FALSE {
				if fdata.FreeFlag == C.VS_TRUE && fdata.SXml != C.NULL {
					if C.StarGo_ModuleInitFlag == C.VS_TRUE {
						C.Star_SRPSXML_Release(fdata.SXml)
					}
					fdata.SXml = nil
				}
				fdata.IsClearedByStarCore = C.VS_TRUE
			}
			if C.StarGo_ModuleInitFlag == C.VS_TRUE && C.StarGo_SRPControlInterface != C.NULL && fdata.RefItem != 0 {
				C.Star_SRPControl_UnRegScriptObject(C.StarGo_SRPControlInterface, (C.VS_UWORD)(fdata.RefItem), (unsafe.Pointer)(C.stargo_FreeScriptObject), 0)
			}
			if fdata.RefItem != 0 {
				DeleteGoObjectAllRef(fdata.RefItem)
				fdata.RefItem = 0
			}
		}
	case *StarObject:
		{
			var SRPInterface unsafe.Pointer
			var SRPObject unsafe.Pointer

			self := ObjData.(*StarObjectBody)
			if self.IsClearedByStarCore == C.VS_FALSE {
				if C.StarGo_ModuleInitFlag == C.VS_TRUE {
					GoSRPClearObject(self.ServiceGroupID, &self.ObjectID)

					SRPInterface = GetSRPServiceInterfaceEx(self.ServiceGroupID, &self.ObjectID)
					if SRPInterface != C.NULL {
						C.Star_SRPI_UnRegLuaFuncEx(SRPInterface, SRPObject, (unsafe.Pointer)(C.stargo_SRPObject_ScriptCallBack), (C.VS_UWORD)(self.RefItem))
						SRPObject = C.Star_SRPI_GetObject(SRPInterface, &self.ObjectID)
						if SRPObject != C.NULL {
							if self.NeedFreeFlag == C.VS_TRUE {
								//var ObjectName string = C.GoString(C.Star_SRPI_GetName(SRPInterface, SRPObject))
								if C.Star_SRPI_UnLockGC(SRPInterface, SRPObject) == C.VS_TRUE {
								}
							}
						}
					}
				}
				self.IsClearedByStarCore = C.VS_TRUE
			}
			if C.StarGo_ModuleInitFlag == C.VS_TRUE && C.StarGo_SRPControlInterface != C.NULL && self.RefItem != 0 {
				C.Star_SRPControl_UnRegScriptObject(C.StarGo_SRPControlInterface, (C.VS_UWORD)(self.RefItem), (unsafe.Pointer)(C.stargo_FreeScriptObject), 0)
			}
			if self.RefItem != 0 {
				DeleteGoObjectAllRef(self.RefItem)
				self.RefItem = 0
			}
		}
	default:
		return
	}
	/*
		p0, ok0 := ObjData.(*StarServiceBody)
		if ok0 {
			C.Star_SRPI_Release(p0.SRPInterface)
		}
		p1, ok1 := ObjData.(*StarSrvGroupBody)
		if ok1 {
			C.Star_SRPBasic_Release(p1.BasicSRPInterface)
		}
	*/
}

/*-----------------------------------------------------------------------*/
var EmptyString *C.VS_CHAR
var Const_GoString *C.VS_CHAR
var Const_RootString *C.VS_CHAR
var Const_VS_OBJECTTOSTRINGFUNCNAME *C.VS_CHAR
var Const_SCRIPTCALL_RETSTRING *C.VS_CHAR
var Const_VS_SOURCESCRIPT_GO *C.VS_CHAR

var Const_FILEMODE_WT *C.VS_CHAR
var Const_FILEMODE_WB *C.VS_CHAR
var Const_FILEMODE_RT *C.VS_CHAR
var Const_FILEMODE_RB *C.VS_CHAR

func init() {
	EmptyString = C.CString("")
	Const_GoString = C.CString("go")
	Const_RootString = C.CString("root")
	Const_VS_OBJECTTOSTRINGFUNCNAME = C.CString(C.VS_OBJECTTOSTRINGFUNCNAME)
	Const_SCRIPTCALL_RETSTRING = C.CString("()s")
	Const_VS_SOURCESCRIPT_GO = C.CString("go")
	Const_FILEMODE_WT = C.CString("wt")
	Const_FILEMODE_WB = C.CString("wb")
	Const_FILEMODE_RT = C.CString("rt")
	Const_FILEMODE_RB = C.CString("rb")
}

func TOVS_BOOL(val bool) C.VS_BOOL {
	if val == true {
		return C.VS_TRUE
	}
	return C.VS_FALSE
}

func FROMVS_BOOL(val C.VS_BOOL) bool {
	if val == C.VS_TRUE {
		return true
	} else {
		return false
	}
}

func SRPGoGetInt(Obj interface{}, val *C.VS_UINT32, ProcessFloat bool) bool {
	if Obj == nil {
		return false
	}
	switch Obj.(type) {
	case bool:
		if Obj.(bool) == true {
			(*val) = (C.VS_UINT32)(1)
		} else {
			(*val) = (C.VS_UINT32)(0)
		}
		return true
	case int8:
		(*val) = (C.VS_UINT32)(Obj.(int8))
		return true
	case uint8:
		(*val) = (C.VS_UINT32)(Obj.(uint8))
		return true
	case int16:
		(*val) = (C.VS_UINT32)(Obj.(int16))
		return true
	case uint16:
		(*val) = (C.VS_UINT32)(Obj.(uint16))
		return true
	case int32:
		(*val) = (C.VS_UINT32)(Obj.(int32))
		return true
	case uint32:
		(*val) = (C.VS_UINT32)(Obj.(uint32))
		return true
	case int:
		(*val) = (C.VS_UINT32)(Obj.(int))
		return true
	case uint:
		(*val) = (C.VS_UINT32)(Obj.(uint))
		return true
	case int64:
		(*val) = (C.VS_UINT32)(Obj.(int64))
		return true
	case uint64:
		(*val) = (C.VS_UINT32)(Obj.(uint64))
		return true
	}
	if ProcessFloat == true {
		switch Obj.(type) {
		case float32:
			(*val) = (C.VS_UINT32)(Obj.(float32))
			return true
		case float64:
			(*val) = (C.VS_UINT32)(Obj.(float64))
			return true
		}
	}
	(*val) = 0
	return false
}

func SRPGoToInt(Obj interface{}, ProcessFloat bool) C.VS_UINT32 {
	if Obj == nil {
		return 0
	}
	switch Obj.(type) {
	case bool:
		if Obj.(bool) == true {
			return (C.VS_UINT32)(1)
		} else {
			return (C.VS_UINT32)(0)
		}
	case int8:
		return (C.VS_UINT32)(Obj.(int8))
	case uint8:
		return (C.VS_UINT32)(Obj.(uint8))
	case int16:
		return (C.VS_UINT32)(Obj.(int16))
	case uint16:
		return (C.VS_UINT32)(Obj.(uint16))
	case int32:
		return (C.VS_UINT32)(Obj.(int32))
	case uint32:
		return (C.VS_UINT32)(Obj.(uint32))
	case int:
		return (C.VS_UINT32)(Obj.(int))
	case uint:
		return (C.VS_UINT32)(Obj.(uint))
	case int64:
		return (C.VS_UINT32)(Obj.(int64))
	case uint64:
		return (C.VS_UINT32)(Obj.(uint64))
	}
	if ProcessFloat == true {
		switch Obj.(type) {
		case float32:
			return (C.VS_UINT32)(Obj.(float32))
		case float64:
			return (C.VS_UINT32)(Obj.(float64))
		}
	}
	return 0
}

func SRPGoToInt64(Obj interface{}, ProcessFloat bool) C.VS_UINT64 {
	if Obj == nil {
		return 0
	}
	switch Obj.(type) {
	case bool:
		if Obj.(bool) == true {
			return (C.VS_UINT64)(1)
		} else {
			return (C.VS_UINT64)(0)
		}
	case int8:
		return (C.VS_UINT64)(Obj.(int8))
	case uint8:
		return (C.VS_UINT64)(Obj.(uint8))
	case int16:
		return (C.VS_UINT64)(Obj.(int16))
	case uint16:
		return (C.VS_UINT64)(Obj.(uint16))
	case int32:
		return (C.VS_UINT64)(Obj.(int32))
	case uint32:
		return (C.VS_UINT64)(Obj.(uint32))
	case int:
		return (C.VS_UINT64)(Obj.(int))
	case uint:
		return (C.VS_UINT64)(Obj.(uint))
	case int64:
		return (C.VS_UINT64)(Obj.(int64))
	case uint64:
		return (C.VS_UINT64)(Obj.(uint64))
	}
	if ProcessFloat == true {
		switch Obj.(type) {
		case float32:
			return (C.VS_UINT64)(Obj.(float32))
		case float64:
			return (C.VS_UINT64)(Obj.(float64))
		}
	}
	return 0
}

func SRPGoToLong(Obj interface{}, ProcessFloat bool) C.VS_INT64 {
	if Obj == nil {
		return 0
	}
	switch Obj.(type) {
	case bool:
		if Obj.(bool) == true {
			return (C.VS_INT64)(1)
		} else {
			return (C.VS_INT64)(0)
		}
	case int8:
		return (C.VS_INT64)(Obj.(int8))
	case uint8:
		return (C.VS_INT64)(Obj.(uint8))
	case int16:
		return (C.VS_INT64)(Obj.(int16))
	case uint16:
		return (C.VS_INT64)(Obj.(uint16))
	case int32:
		return (C.VS_INT64)(Obj.(int32))
	case uint32:
		return (C.VS_INT64)(Obj.(uint32))
	case int:
		return (C.VS_INT64)(Obj.(int))
	case uint:
		return (C.VS_INT64)(Obj.(uint))
	case int64:
		return (C.VS_INT64)(Obj.(int64))
	case uint64:
		return (C.VS_INT64)(Obj.(uint64))
	}
	if ProcessFloat == true {
		switch Obj.(type) {
		case float32:
			return (C.VS_INT64)(Obj.(float32))
		case float64:
			return (C.VS_INT64)(Obj.(float64))
		}
	}
	return 0
}

func SRPGoGetFloat(Obj interface{}, Value *C.VS_DOUBLE) bool {
	if Obj == nil {
		return false
	}
	switch Obj.(type) {
	case bool:
		if Obj.(bool) == true {
			(*Value) = (C.VS_DOUBLE)(1)
		} else {
			(*Value) = (C.VS_DOUBLE)(0)
		}
		return true
	case int8:
		(*Value) = (C.VS_DOUBLE)(Obj.(int8))
		return true
	case uint8:
		(*Value) = (C.VS_DOUBLE)(Obj.(uint8))
		return true
	case int16:
		(*Value) = (C.VS_DOUBLE)(Obj.(int16))
		return true
	case uint16:
		(*Value) = (C.VS_DOUBLE)(Obj.(uint16))
		return true
	case int32:
		(*Value) = (C.VS_DOUBLE)(Obj.(int32))
		return true
	case uint32:
		(*Value) = (C.VS_DOUBLE)(Obj.(uint32))
		return true
	case int:
		(*Value) = (C.VS_DOUBLE)(Obj.(int))
		return true
	case uint:
		(*Value) = (C.VS_DOUBLE)(Obj.(uint))
		return true
	case int64:
		(*Value) = (C.VS_DOUBLE)(Obj.(int64))
		return true
	case uint64:
		(*Value) = (C.VS_DOUBLE)(Obj.(uint64))
		return true
	case float32:
		(*Value) = (C.VS_DOUBLE)(Obj.(float32))
		return true
	case float64:
		(*Value) = (C.VS_DOUBLE)(Obj.(float64))
		return true
	}
	(*Value) = 0.0
	return false
}

func SRPGoToFloat(Obj interface{}) C.VS_DOUBLE {
	if Obj == nil {
		return 0.0
	}
	switch Obj.(type) {
	case bool:
		if Obj.(bool) == true {
			return (C.VS_DOUBLE)(1)
		} else {
			return (C.VS_DOUBLE)(0)
		}
	case int8:
		return (C.VS_DOUBLE)(Obj.(int8))
	case uint8:
		return (C.VS_DOUBLE)(Obj.(uint8))
	case int16:
		return (C.VS_DOUBLE)(Obj.(int16))
	case uint16:
		return (C.VS_DOUBLE)(Obj.(uint16))
	case int32:
		return (C.VS_DOUBLE)(Obj.(int32))
	case uint32:
		return (C.VS_DOUBLE)(Obj.(uint32))
	case int:
		return (C.VS_DOUBLE)(Obj.(int))
	case uint:
		return (C.VS_DOUBLE)(Obj.(uint))
	case int64:
		return (C.VS_DOUBLE)(Obj.(int64))
	case uint64:
		return (C.VS_DOUBLE)(Obj.(uint64))
	case float32:
		return (C.VS_DOUBLE)(Obj.(float32))
	case float64:
		return (C.VS_DOUBLE)(Obj.(float64))
	}
	return 0.0
}

func SRPGoIsString(Obj interface{}) bool {
	if Obj == nil {
		return false
	}
	if _, ok := Obj.(string); ok {
		return true
	}
	return false
}

/*-----------------------------------------------------------------------*/

func GoPrintError(AlarmLevel C.VS_INT32, Info *C.VS_CHAR) {
	if C.StarGo_SRPControlInterface == nil {
		return
	}
	C.stargo_SRPControl_ProcessError(C.StarGo_SRPControlInterface, AlarmLevel, Const_GoString, 0, Info)
}

/*-----------------------------------------------------------------------*/
func SRPGoSetStr(Value *C.VS_CHAR, FromAnsi bool) string {
	var CharPtr *C.VS_CHAR

	if Value == nil {
		return ""
	}
	if FromAnsi == true {
		CharPtr = C.Star_SRPCS_AnsiToUTF8(C.StarGo_SRPCoreShellInterface, Value, -1)
		if CharPtr == nil {
			S := C.CString("coding to ansi fail...")
			GoPrintError(C.VSFAULT_WARNING, S)
			C.free((unsafe.Pointer)(S))
			return ""
		}
		Result := C.GoString(CharPtr)
		C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(CharPtr))
		return Result
	}
	return C.GoString(Value)
}

func SRPGoSetStrEx(Value *C.VS_CHAR, StrLen C.VS_INT32, FromAnsi bool) string {
	var CharPtr *C.VS_CHAR

	if Value == nil {
		return ""
	}
	if FromAnsi == true {
		CharPtr = C.Star_SRPCS_AnsiToUTF8(C.StarGo_SRPCoreShellInterface, Value, StrLen)
		if CharPtr == nil {
			return "" /*may be binary buf */
		}
		Result := C.GoString(CharPtr)
		C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(CharPtr))
		return Result
	}
	return C.GoString(Value)
}

func SRPGoGetStr(Obj string, ToAnsi bool) *C.VS_CHAR {
	var CharPtr *C.VS_CHAR

	if ToAnsi == true {
		CharPtr1 := C.CString(Obj)
		CharPtr = C.Star_SRPCS_UTF8ToAnsi(C.StarGo_SRPCoreShellInterface, CharPtr1, -1)
		C.free(unsafe.Pointer(CharPtr1))
	} else {
		CharPtr = C.CString(Obj)
	}
	return CharPtr
}

func SRPGoGetStrEx(Obj string, RetLength *C.VS_INT32, ToAnsi bool) *C.VS_CHAR {
	var CharPtr *C.VS_CHAR

	if RetLength != nil {
		(*RetLength) = 0
	}
	if ToAnsi == true {
		var RetCharLength C.VS_INT32
		CharPtr1 := C.CString(Obj)
		CharPtr = C.Star_SRPCS_UTF8ToAnsiEx(C.StarGo_SRPCoreShellInterface, CharPtr1, (C.VS_INT32)(len(Obj)), &RetCharLength)
		C.free(unsafe.Pointer(CharPtr1))
		if RetLength != nil {
			(*RetLength) = RetCharLength
		}
	} else {
		CharPtr = C.CString(Obj)
		if RetLength != nil {
			(*RetLength) = (C.VS_INT32)(len(Obj))
		}
	}
	return CharPtr
}

func STARGO_SAFERELEASESTR(Obj string, CharPtr *C.VS_CHAR) {
	C.free(unsafe.Pointer(CharPtr))
}

/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

//export GoScriptTerm
func GoScriptTerm() {
	if C.StarGo_ModuleInitFlag == C.VS_FALSE || C.StarGo_SRPControlInterface == nil {
		return
	}

	if g_ScriptTermCallBack != nil {
		g_ScriptTermCallBack()
	}

	GoSRPClearSrvGroup(C.VS_TRUE)

	runtime.GC()

	TermObjectDefer_Free(true)

	if g_MsgCallBack != nil {
		C.stargo_UnRegisterCallBackInfo((unsafe.Pointer)(C.stargo_MsgCallBack), 0)
		g_MsgCallBack = nil
	}
	if g_DispatchRequestCallBack != nil {
		C.Star_SRPControl_UnRegDispatchRequest(C.StarGo_SRPControlInterface, (unsafe.Pointer)(C.stargo_SRPDispatchRequestCallBack), 0)
		g_DispatchRequestCallBack = nil
	}

	VSScript_GoRawContextRefManager_Term()

	g_AttachRawContextCallBack = nil
	g_ScriptTermCallBack = nil
}

//export GoInitFromStarCore
func GoInitFromStarCore() {
	VSScript_GoRawContextRefManager_Init()

	if TermObjectDeferQueueMutexInitFlag == false {
		TermObjectDeferQueueMutexInitFlag = true
		TermObjectDeferQueueMutex = new(sync.Mutex)
	}
	if WeakTableMutexInitFlag == false {
		WeakTableMutexInitFlag = true
		WeakTableMutex = new(sync.Mutex)
	}
}

func InitSimple(In_ServiceName string, In_ServicePass string, ClientPortNumber int, WebPortNumber int, DependService ...string) *StarService {
	if C.stargo_starcore_Load() != 0 {
		panic(fmt.Errorf(
			"starcore init fail",
		))
		return nil
	}
	VSScript_GoRawContextRefManager_Init()

	C.stargo_starcore_Init(C.VS_TRUE, C.VS_FALSE, C.VS_FALSE, C.VS_TRUE, EmptyString, 0, EmptyString, (C.VS_INT32)(ClientPortNumber))
	BasicSRPInterface := C.Star_SRPControl_QueryBasicInterface(C.StarGo_SRPControlInterface, 0)
	ServiceName := C.CString(In_ServiceName)
	defer C.free(unsafe.Pointer(ServiceName))

	ServicePass := C.CString(In_ServicePass)
	defer C.free(unsafe.Pointer(ServicePass))

	for _, num := range DependService {
		DependServiceName := C.CString(num)
		defer C.free(unsafe.Pointer(DependServiceName))

		if C.vs_string_strlen(DependServiceName) != 0 && C.Star_SRPBasic_ImportService(BasicSRPInterface, DependServiceName, C.VS_TRUE) == C.VS_FALSE {
			C.Star_SRPBasic_Release(BasicSRPInterface)
			panic(fmt.Errorf(
				"import depend service [%s] fail", num,
			))
			return nil
		}
	}

	if C.Star_SRPBasic_CreateService(BasicSRPInterface, EmptyString, ServiceName, (*C.VS_UUID)(C.NULL), ServicePass, 5, 10240, 10240, 10240, 10240, 10240) == C.VS_FALSE {
		C.Star_SRPBasic_Release(BasicSRPInterface)
		panic(fmt.Errorf(
			"create service [%s] fail", In_ServiceName,
		))
		return nil
	}
	UserName := C.CString("root")
	defer C.free(unsafe.Pointer(UserName))
	SRPInterface := C.Star_SRPBasic_GetSRPInterface(BasicSRPInterface, ServiceName, UserName, ServicePass)

	if SRPInterface == C.NULL {
		C.Star_SRPBasic_Release(BasicSRPInterface)
		return nil
	}
	if WebPortNumber != 0 {
		C.Star_SRPBasic_SetWebServerPort(BasicSRPInterface, EmptyString, (C.VS_UINT16)(WebPortNumber), 100, 2048)
	}

	if TermObjectDeferQueueMutexInitFlag == false {
		TermObjectDeferQueueMutexInitFlag = true
		TermObjectDeferQueueMutex = new(sync.Mutex)
	}
	if WeakTableMutexInitFlag == false {
		WeakTableMutexInitFlag = true
		WeakTableMutex = new(sync.Mutex)
	}

	SrvGroupVal := GoSRPGetSrvGroup(0, BasicSRPInterface)
	fdata := SrvGroupClass_getstarcoredata(SrvGroupVal)
	ObjectTemp := ToStarService(fdata, SRPInterface)

	C.Star_SRPBasic_Release(BasicSRPInterface)

	return ObjectTemp
}

func InitSimpleEx(ClientPortNumber int, WebPortNumber int, DependService ...string) *StarSrvGroup {
	if C.stargo_starcore_Load() != 0 {
		panic(fmt.Errorf(
			"starcore init fail",
		))
		return nil
	}
	VSScript_GoRawContextRefManager_Init()

	C.stargo_starcore_Init(C.VS_TRUE, C.VS_FALSE, C.VS_FALSE, C.VS_TRUE, EmptyString, 0, EmptyString, (C.VS_INT32)(ClientPortNumber))
	BasicSRPInterface := C.Star_SRPControl_QueryBasicInterface(C.StarGo_SRPControlInterface, 0)

	for _, num := range DependService {
		DependServiceName := C.CString(num)
		defer C.free(unsafe.Pointer(DependServiceName))

		if C.vs_string_strlen(DependServiceName) != 0 && C.Star_SRPBasic_ImportService(BasicSRPInterface, DependServiceName, C.VS_TRUE) == C.VS_FALSE {
			C.Star_SRPBasic_Release(BasicSRPInterface)
			panic(fmt.Errorf(
				"import depend service [%s] fail", num,
			))
			return nil
		}
	}

	if WebPortNumber != 0 {
		C.Star_SRPBasic_SetWebServerPort(BasicSRPInterface, EmptyString, (C.VS_UINT16)(WebPortNumber), 100, 2048)
	}

	if TermObjectDeferQueueMutexInitFlag == false {
		TermObjectDeferQueueMutexInitFlag = true
		TermObjectDeferQueueMutex = new(sync.Mutex)
	}
	if WeakTableMutexInitFlag == false {
		WeakTableMutexInitFlag = true
		WeakTableMutex = new(sync.Mutex)
	}
	return GoSRPGetSrvGroup(0, BasicSRPInterface)
	//return ToStarSrvGroup(0, BasicSRPInterface)
}

func InitCore(ServerFlag bool, ShowMenuFlag bool, ShowOutWndFlag bool, SRPPrintFlag bool, DebugInterface string, DebugPortNumber int, ClientInterface string, ClientPortNumber int) int {
	if C.stargo_starcore_Load() != 0 {
		panic(fmt.Errorf(
			"starcore init fail",
		))
		return C.VSINIT_ERROR
	}
	VSScript_GoRawContextRefManager_Init()

	LocalDebugInterface := C.CString(DebugInterface)
	defer C.free(unsafe.Pointer(LocalDebugInterface))

	LocalClientInterface := C.CString(ClientInterface)
	defer C.free(unsafe.Pointer(LocalClientInterface))

	C.stargo_starcore_Init(TOVS_BOOL(ServerFlag), TOVS_BOOL(ShowMenuFlag), TOVS_BOOL(ShowOutWndFlag), TOVS_BOOL(SRPPrintFlag), LocalDebugInterface, (C.VS_INT32)(DebugPortNumber), LocalClientInterface, (C.VS_INT32)(ClientPortNumber))

	if TermObjectDeferQueueMutexInitFlag == false {
		TermObjectDeferQueueMutexInitFlag = true
		TermObjectDeferQueueMutex = new(sync.Mutex)
	}
	if WeakTableMutexInitFlag == false {
		WeakTableMutexInitFlag = true
		WeakTableMutex = new(sync.Mutex)
	}

	if C.StarGo_ModuleInitFlag == C.VS_TRUE {
		return C.VSINIT_OK
	} else {
		panic(fmt.Errorf(
			"starcore init fail",
		))
		return C.VSINIT_ERROR
	}
}

func ModuleExit() {
	var BasicSRPInterface unsafe.Pointer = nil

	if C.StarGo_ModuleInitFlag == C.VS_FALSE {
		return
	}

	TermObjectDefer_Free(true)

	BasicSRPInterface = C.Star_SRPControl_QueryBasicInterface(C.StarGo_SRPControlInterface, 0)
	if C.Star_SRPBasic_IsRootService(BasicSRPInterface) == C.VS_TRUE {
		C.Star_SRPBasic_ClearService(BasicSRPInterface)
		C.Star_SRPBasic_Release(BasicSRPInterface)
		GoSRPClearSrvGroup(C.VS_TRUE)

		if g_MsgCallBack != nil {
			C.stargo_UnRegisterCallBackInfo((unsafe.Pointer)(C.stargo_MsgCallBack), 0)
			g_MsgCallBack = nil
		}
		if g_DispatchRequestCallBack != nil {
			C.Star_SRPControl_UnRegDispatchRequest(C.StarGo_SRPControlInterface, (unsafe.Pointer)(C.stargo_SRPDispatchRequestCallBack), 0)
			g_DispatchRequestCallBack = nil
		}

		C.stargo_starcore_unLoad()
	} else {
		//if dyna service, only term
		C.Star_SRPBasic_Release(BasicSRPInterface)
		C.stargo_Term()
	}

	VSScript_GoRawContextRefManager_Term()

	runtime.GC()

	return
}

func ModuleClear() {
	var BasicSRPInterface unsafe.Pointer = nil

	if C.StarGo_ModuleInitFlag == C.VS_FALSE {
		return
	}

	TermObjectDefer_Free(true)

	BasicSRPInterface = C.Star_SRPControl_QueryBasicInterface(C.StarGo_SRPControlInterface, 0)
	if C.Star_SRPBasic_IsRootService(BasicSRPInterface) == C.VS_TRUE {
		C.Star_SRPBasic_ClearService(BasicSRPInterface)
		C.Star_SRPBasic_Release(BasicSRPInterface)
		GoSRPClearSrvGroup(C.VS_TRUE)

		if g_MsgCallBack != nil {
			C.stargo_UnRegisterCallBackInfo((unsafe.Pointer)(C.stargo_MsgCallBack), 0)
			g_MsgCallBack = nil
		}

		if g_DispatchRequestCallBack != nil {
			C.Star_SRPControl_UnRegDispatchRequest(C.StarGo_SRPControlInterface, (unsafe.Pointer)(C.stargo_SRPDispatchRequestCallBack), 0)
			g_DispatchRequestCallBack = nil
		}

		if C.StarGo_SRPControlInterface != C.NULL {
			C.Star_SRPControl_ClearScriptObject(C.StarGo_SRPControlInterface, (unsafe.Pointer)(C.stargo_FreeScriptObject), 0)
		}

		if C.StarGo_SRPControlInterface != C.NULL {
			for {
				if C.Star_SRPControl_SRPDispatch(C.StarGo_SRPControlInterface, C.VS_FALSE) == C.VS_FALSE {
					break
				}
			}
		}
	} else {
		//if dyna service, only term
		C.Star_SRPBasic_Release(BasicSRPInterface)
		C.stargo_Term()
	}

	runtime.GC()
	return
}

//export GoMsgCallBack
func GoMsgCallBack(ServiceGroupID C.VS_ULONG, uMsg C.VS_ULONG, wParam C.VS_UWORD, lParam C.VS_UWORD, IsProcessed *C.VS_BOOL, Para C.VS_UWORD) (FunctionResult C.VS_UWORD) {
	if g_MsgCallBack == nil {
		return 0
	}
	defer func() {
		if err := recover(); err != nil {
			FunctionResult = 0
			return
		}
	}()
	switch uMsg {
	case C.MSG_VSDISPMSG:
		fallthrough
	case C.MSG_VSDISPLUAMSG:
		fallthrough
	case C.MSG_DISPMSG:
		fallthrough
	case C.MSG_DISPLUAMSG:
		fallthrough
	case C.MSG_EXIT:
		fallthrough
	case C.MSG_HYPERLINK:
		fallthrough
	case C.MSG_SETMANAGERCAPTION:
		//"(IIsI)"
		{
			s, _ := g_MsgCallBack((uint32)(ServiceGroupID), (uint32)(uMsg), SRPGoSetStr((*C.char)(C.stargo_ToPointer(wParam)), true), (uint)(lParam))
			if s {
				(*IsProcessed) = C.VS_TRUE
			} else {
				(*IsProcessed) = C.VS_FALSE
			}
			return (C.VS_UWORD)(0)
		}
	case C.MSG_ONTELNETSTRING:
		//"(IIss)"
		{
			s, _ := g_MsgCallBack((uint32)(ServiceGroupID), (uint32)(uMsg), SRPGoSetStr((*C.char)(C.stargo_ToPointer(wParam)), true), SRPGoSetStr((*C.char)(C.stargo_ToPointer(lParam)), true))
			if s {
				(*IsProcessed) = C.VS_TRUE
			} else {
				(*IsProcessed) = C.VS_FALSE
			}
			return (C.VS_UWORD)(0)
		}
	case C.MSG_ONTELNETSTRING_PREEXECUTE:
		//"(IIss)"
		{
			s, v := g_MsgCallBack((uint32)(ServiceGroupID), (uint32)(uMsg), SRPGoSetStr((*C.char)(C.stargo_ToPointer(wParam)), true), SRPGoSetStr((*C.char)(C.stargo_ToPointer(lParam)), true))
			if s {
				switch v.(type) {
				case string:
					BasicSRPInterface := C.Star_SRPControl_QueryBasicInterface(C.StarGo_SRPControlInterface, ServiceGroupID)
					if BasicSRPInterface != nil {
						RetStr := SRPGoGetStr(v.(string), true)
						if RetStr != nil {
							RetLen := C.vs_string_strlen(RetStr)
							if RetLen == 0 {
								(*IsProcessed) = C.VS_TRUE
							} else {
								(*IsProcessed) = C.VS_FALSE
								if C.vs_string_strcmp((*C.VS_CHAR)(C.stargo_GetUWordPointer(wParam)), RetStr) != 0 {
									C.Star_SRPBasic_Free(BasicSRPInterface, C.stargo_GetUWordPointer(wParam))
									NewStr := (*C.VS_CHAR)(C.Star_SRPBasic_Malloc_Nor(BasicSRPInterface, (C.VS_INT32)(RetLen+1)))
									C.strcpy(NewStr, RetStr)
									C.stargo_SetUWordPointer(wParam, (unsafe.Pointer)(NewStr))
								}
							}
							C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(RetStr))
						} else {
							(*IsProcessed) = C.VS_FALSE
						}
					} else {
						(*IsProcessed) = C.VS_FALSE
					}
					if BasicSRPInterface != C.NULL {
						C.Star_SRPBasic_Release(BasicSRPInterface)
					}
				default:
					(*IsProcessed) = C.VS_FALSE
				}
			} else {
				(*IsProcessed) = C.VS_FALSE
			}
			return (C.VS_UWORD)(0)
		}
	case C.MSG_APPEVENT:
		//"(IIIs)"
		{
			s, _ := g_MsgCallBack((uint32)(ServiceGroupID), (uint32)(uMsg), (uint32)(wParam), SRPGoSetStr((*C.char)(C.stargo_ToPointer(lParam)), true))
			if s {
				(*IsProcessed) = C.VS_TRUE
			} else {
				(*IsProcessed) = C.VS_FALSE
			}
			return (C.VS_UWORD)(0)
		}
	}
	return (C.VS_UWORD)(0)
}

func RegMsgCallBack_P(CallBackProc func(ServiceGroupID uint32, uMsg uint32, wParam interface{}, lParam interface{}) (IsProcessed bool, Result interface{})) {
	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	if CallBackProc == nil {
		if g_MsgCallBack != nil {
			C.stargo_UnRegisterCallBackInfo((unsafe.Pointer)(C.stargo_MsgCallBack), 0)
		}
		g_MsgCallBack = nil
		return
	}
	if g_MsgCallBack == nil {
		C.stargo_RegisterCallBackInfo((unsafe.Pointer)(C.stargo_MsgCallBack), 0)
	}
	g_MsgCallBack = CallBackProc
	return
}

//export GoSRPDispatchRequestCallBack
func GoSRPDispatchRequestCallBack() {
	if g_DispatchRequestCallBack == nil {
		return
	}
	defer func() {
		if err := recover(); err != nil {
			return
		}
	}()
	g_DispatchRequestCallBack()
}

func RegDispatchRequest_P(CallBackProc func()) {
	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	if CallBackProc == nil {
		if g_DispatchRequestCallBack != nil {
			C.Star_SRPControl_UnRegDispatchRequest(C.StarGo_SRPControlInterface, (unsafe.Pointer)(C.stargo_SRPDispatchRequestCallBack), 0)
		}
		g_DispatchRequestCallBack = nil
		return
	}
	if g_DispatchRequestCallBack == nil {
		C.Star_SRPControl_RegDispatchRequest(C.StarGo_SRPControlInterface, (unsafe.Pointer)(C.stargo_SRPDispatchRequestCallBack), 0)
	}
	g_DispatchRequestCallBack = CallBackProc
	return
}

func SRPDispatch(WaitFlag bool) bool {
	var Result C.VS_BOOL

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	if WaitFlag == true {
		Result = C.Star_SRPControl_SRPDispatch(C.StarGo_SRPControlInterface, C.VS_TRUE)
	} else {
		Result = C.Star_SRPControl_SRPDispatch(C.StarGo_SRPControlInterface, C.VS_FALSE)
	}
	if Result == C.VS_TRUE {
		return true
	} else {
		return false
	}
}

func SRPLock() {
	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	C.Star_SRPControl_SRPLock(C.StarGo_SRPControlInterface)
	return
}

func SRPUnLock() {
	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	C.Star_SRPControl_SRPUnLock(C.StarGo_SRPControlInterface)
	return
}

func SetRegisterCode(In_FileName string, Single bool) bool {
	var FileName *C.VS_CHAR
	var Result C.VS_BOOL

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	FileName = SRPGoGetStr(In_FileName, false)
	Result = C.Star_SRPControl_SetRegisterCode(C.StarGo_SRPControlInterface, FileName, TOVS_BOOL(Single))
	STARGO_SAFERELEASESTR(In_FileName, FileName)
	return FROMVS_BOOL(Result)
}

func IsRegistered() bool {
	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	return FROMVS_BOOL(C.Star_SRPControl_IsRegistered(C.StarGo_SRPControlInterface))
}

func SetLocale(In_Lang string) {
	var Lang *C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	Lang = SRPGoGetStr(In_Lang, false)
	C.Star_SRPControl_SetLocale(C.StarGo_SRPControlInterface, Lang)
	STARGO_SAFERELEASESTR(In_Lang, Lang)
	return
}

func GetLocale() string {
	var Lang *C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return ""
	}
	Lang = C.Star_SRPControl_GetLocale(C.StarGo_SRPControlInterface)
	return C.GoString(Lang)
}

func Version() [3]int {
	var IntArray [3]int

	IntArray[0] = C.VS_MAINVERSION
	IntArray[1] = C.VS_SUBVERSION
	IntArray[2] = C.VS_BUILDVERSION
	return IntArray
}

func GetScriptIndex(In_ScriptInterface string) int {
	var ScriptInterface *C.VS_CHAR
	var Index C.VS_INT32

	if C.StarGo_SRPControlInterface == C.NULL {
		return -1
	}
	ScriptInterface = SRPGoGetStr(In_ScriptInterface, false)
	Index = C.Star_SRPControl_GetScriptInterfaceIndex(C.StarGo_SRPControlInterface, ScriptInterface)
	STARGO_SAFERELEASESTR(In_ScriptInterface, ScriptInterface)
	return (int)(Index)
}

func SetScript(In_ScriptInterface string, In_Module string, In_Para string) bool {
	var ScriptInterface *C.VS_CHAR
	var Module *C.VS_CHAR
	var Para *C.VS_CHAR
	var Result C.VS_BOOL

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	ScriptInterface = SRPGoGetStr(In_ScriptInterface, false)
	Module = SRPGoGetStr(In_Module, false)
	Para = SRPGoGetStr(In_Para, false)
	Result = C.Star_SRPControl_SetScriptInterface(C.StarGo_SRPControlInterface, ScriptInterface, Module, Para)
	STARGO_SAFERELEASESTR(In_ScriptInterface, ScriptInterface)
	STARGO_SAFERELEASESTR(In_Module, Module)
	STARGO_SAFERELEASESTR(In_Para, Para)
	return FROMVS_BOOL(Result)
}

func DetachCurrentThread() {
	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	C.Star_SRPControl_DetachCurrentThread(C.StarGo_SRPControlInterface)
	return
}

func CoreHandle() int64 {
	return (int64)(C.stargo_CoreHandle())
}

func GetSrvGroup(ServiceName_GroupID interface{}) *StarSrvGroup {

	TermObjectDefer_Free(false)

	if ServiceName_GroupID != nil {
		if reflect.TypeOf(ServiceName_GroupID).Kind() == reflect.Int {
			ServiceGroupID := ServiceName_GroupID.(int)
			BasicSRPInterface := C.Star_SRPControl_QueryBasicInterface(C.StarGo_SRPControlInterface, (C.VS_ULONG)(ServiceGroupID))
			if BasicSRPInterface == C.NULL {
				return nil
			}
			RetObject := GoSRPGetSrvGroup(0, BasicSRPInterface)
			C.Star_SRPBasic_Release(BasicSRPInterface)
			return RetObject
		} else if reflect.TypeOf(ServiceName_GroupID).Kind() == reflect.String {
			var ActiveServiceName *C.VS_CHAR
			var ServiceID C.VS_UUID

			ServiceName := C.CString(ServiceName_GroupID.(string))
			defer C.free(unsafe.Pointer(ServiceName))

			ServiceGroupID := C.Star_SRPControl_QueryFirstServiceGroup(C.StarGo_SRPControlInterface)
			var BasicSRPInterface unsafe.Pointer = nil
			for {
				if ServiceGroupID == C.VS_INVALID_SERVICEGROUPID {
					break
				}
				BasicSRPInterface = C.Star_SRPControl_QueryBasicInterface(C.StarGo_SRPControlInterface, ServiceGroupID)
				if BasicSRPInterface == C.NULL {
					return nil
				}
				ActiveServiceName = C.Star_SRPBasic_QueryActiveService(BasicSRPInterface, (*C.VS_UUID)(&ServiceID))
				if ActiveServiceName != (*C.VS_CHAR)(C.NULL) && C.vs_string_strcmp(ActiveServiceName, ServiceName) == 0 {
					break
				}
				C.Star_SRPBasic_Release(BasicSRPInterface)
				ServiceGroupID = C.Star_SRPControl_QueryNextServiceGroup(C.StarGo_SRPControlInterface)
			}
			if ServiceGroupID == C.VS_INVALID_SERVICEGROUPID {
				C.Star_SRPBasic_Release(BasicSRPInterface)
				return nil
			}
			RetObject := GoSRPGetSrvGroup(ServiceGroupID, BasicSRPInterface)
			C.Star_SRPBasic_Release(BasicSRPInterface)
			return RetObject
		}
	} else {
		BasicSRPInterface := C.Star_SRPControl_QueryBasicInterface(C.StarGo_SRPControlInterface, 0)
		if BasicSRPInterface == C.NULL {
			return nil
		}
		RetObject := GoSRPGetSrvGroup(0, BasicSRPInterface)
		C.Star_SRPBasic_Release(BasicSRPInterface)
		return RetObject
	}
	return nil
}

func IsSrvGroupClassObject(Obj interface{}) bool {
	if Obj == nil {
		return false
	}
	_, ok := Obj.(*StarSrvGroup)
	return ok
}

func IsStarServiceClassObject(Obj interface{}) bool {
	if Obj == nil {
		return false
	}
	_, ok := Obj.(*StarService)
	return ok
}

func IsStarObjectClassObject(Obj interface{}) bool {
	if Obj == nil {
		return false
	}
	_, ok := Obj.(*StarObject)
	return ok
}

func IsStarParaPkgClassObject(Obj interface{}) bool {
	if Obj == nil {
		return false
	}
	_, ok := Obj.(*StarParaPkg)
	return ok
}

func IsStarBinBufClassObject(Obj interface{}) bool {
	if Obj == nil {
		return false
	}
	_, ok := Obj.(*StarBinBuf)
	return ok
}

func IsStarSXmlClassObject(Obj interface{}) bool {
	if Obj == nil {
		return false
	}
	_, ok := Obj.(*StarSXml)
	return ok
}

func SrvGroupClass_getstarcoredata_byref(Ref C.VS_UWORD) *StarSrvGroupBody {
	s := RefToGoObject(Ref)
	if s == nil {
		return nil
	}
	self, ok := s.(*StarSrvGroup)
	if ok {
		return self.ObjData
	}
	return nil
}

func SrvGroupClass_getstarcoredata(self *StarSrvGroup) *StarSrvGroupBody {
	if self == nil {
		return nil
	}
	return self.ObjData
}

func StarServiceClass_getstarcoredata(self *StarService) *StarServiceBody {
	if self == nil {
		return nil
	}
	return self.ObjData
}

func StarParaPkgClass_getstarcoredata(self *StarParaPkg) *StarParaPkgBody {
	if self == nil {
		return nil
	}
	return self.ObjData
}

func StarBinBufClass_getstarcoredata(self *StarBinBuf) *StarBinBufBody {
	if self == nil {
		return nil
	}
	return self.ObjData
}

func StarSXmlClass_getstarcoredata(self *StarSXml) *StarSXmlBody {
	if self == nil {
		return nil
	}
	return self.ObjData
}

func StarObjectClass_getstarcoredata(self *StarObject) *StarObjectBody {
	if self == nil {
		return nil
	}
	return self.ObjData
}

func GoObjectToSXml(Obj interface{}) unsafe.Pointer {
	var ObjData *StarSXmlBody

	if IsStarSXmlClassObject(Obj) == false {
		return nil
	}
	S, _ := Obj.(*StarSXml)
	ObjData = StarSXmlClass_getstarcoredata(S)
	if ObjData == nil {
		return nil
	}
	return ObjData.SXml
}

func GoObjectToParaPkg(Obj interface{}) unsafe.Pointer {
	var ObjData *StarParaPkgBody

	if IsStarParaPkgClassObject(Obj) == false {
		return nil
	}
	S, _ := Obj.(*StarParaPkg)
	ObjData = StarParaPkgClass_getstarcoredata(S)
	if ObjData == nil {
		return nil
	}
	return ObjData.ParaPkg
}

func GoObjectToBinBuf(Obj interface{}) unsafe.Pointer {
	var ObjData *StarBinBufBody

	if IsStarBinBufClassObject(Obj) == false {
		return nil
	}
	S, _ := Obj.(*StarBinBuf)
	ObjData = StarBinBufClass_getstarcoredata(S)
	if ObjData == nil {
		return nil
	}
	return ObjData.BinBuf
}

func GoObjectToSRPObject(Obj interface{}) unsafe.Pointer {
	var ObjData *StarObjectBody
	var SRPInterface unsafe.Pointer

	if IsStarObjectClassObject(Obj) == false {
		return nil
	}
	S, _ := Obj.(*StarObject)
	ObjData = StarObjectClass_getstarcoredata(S)
	SRPInterface = GetSRPServiceInterfaceEx(ObjData.ServiceGroupID, &ObjData.ObjectID)
	if SRPInterface == nil {
		return nil
	}
	return C.Star_SRPI_GetObject(SRPInterface, &ObjData.ObjectID)
}

func GoObjectToSRPServiceInterface(Obj interface{}) unsafe.Pointer {
	var ObjData *StarServiceBody

	if IsStarServiceClassObject(Obj) == false {
		return nil
	}
	S, _ := Obj.(*StarService)
	ObjData = StarServiceClass_getstarcoredata(S)
	return ObjData.SRPInterface
}

func GoObjectToSRPServiceInterface_byref(Ref C.VS_UWORD) unsafe.Pointer {
	s := RefToGoObject(Ref)
	if s == nil {
		return nil
	}
	self, ok := s.(*StarService)
	if ok {
		return self.ObjData.SRPInterface
	}
	return nil
}

/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------
  ---Global Functions
  -------------------------------------------------------------------------------------------*/

func SrvGroupClass_Data_dtor_before(fdata *StarSrvGroupBody, ClearSrvGroupFlag C.VS_BOOL) {
	var SRPInterfaceItem *StructOfSRPSrvGroup_SRPInterfaceItem
	var ObjectRefInSrvGroup *C.struct_StructOfObjectRefInSrvGroup
	var QueryRecord C.VS_QUERYRECORD

	if fdata.BasicSRPInterface != nil && C.StarGo_ModuleInitFlag == C.VS_TRUE {
		if fdata.ObjectIndexTree != C.NULL {
			ObjectRefInSrvGroup = (*C.struct_StructOfObjectRefInSrvGroup)((unsafe.Pointer)(C.Star_SRPBasic_QueryFirstIDKey(fdata.BasicSRPInterface, fdata.ObjectIndexTree, &QueryRecord, (*C.VS_UUID)(C.NULL))))
			for {
				if ObjectRefInSrvGroup == nil {
					break
				}
				DeleteGoObjectAllRef(ObjectRefInSrvGroup.RefItem)
				C.stargo_FreeStructOfObjectRefInSrvGroup(ObjectRefInSrvGroup)
				ObjectRefInSrvGroup = (*C.struct_StructOfObjectRefInSrvGroup)((unsafe.Pointer)(C.Star_SRPBasic_QueryNextIDKey(fdata.BasicSRPInterface, fdata.ObjectIndexTree, &QueryRecord, (*C.VS_UUID)(C.NULL))))
			}
			if ClearSrvGroupFlag == C.VS_TRUE {
				C.Star_SRPBasic_DestoryIndex(fdata.BasicSRPInterface, fdata.ObjectIndexTree)
				fdata.ObjectIndexTree = nil
			} else {
				C.Star_SRPBasic_DelAllKey(fdata.BasicSRPInterface, fdata.ObjectIndexTree)
			}
		}

		if ClearSrvGroupFlag == C.VS_TRUE {
			C.Star_SRPBasic_UnRegObjectIDChangeNotify(fdata.BasicSRPInterface, (C.VS_ObjectIDChangeNotifyProc)(C.stargo_ObjectIDChangeNotify), (C.VS_UWORD)(fdata.RefItem))
			C.Star_SRPBasic_UnRegObjectFreeNotify(fdata.BasicSRPInterface, (C.VS_ObjectFreeNotifyProc)(C.stargo_ObjectFreeNotify), (C.VS_UWORD)(fdata.RefItem))
		}
		//--SRPInterfaceItem
		for {
			if fdata.SRPInterfaceItemRoot == nil {
				break
			}
			SRPInterfaceItem = fdata.SRPInterfaceItemRoot
			fdata.SRPInterfaceItemRoot = fdata.SRPInterfaceItemRoot.Down
			DeleteGoObjectAllRef(SRPInterfaceItem.ServiceObject)
			//free(SRPInterfaceItem)  by gc
		}
		if ClearSrvGroupFlag == C.VS_TRUE {
			C.Star_SRPBasic_Release(fdata.BasicSRPInterface)
			fdata.BasicSRPInterface = nil
		}
	}
	if ClearSrvGroupFlag == C.VS_TRUE {
		fdata.ServiceGroupID = C.VS_INVALID_SERVICEGROUPID
	}
}

type StructOfGoSrvGroupIndex struct {
	GoSrvGroupObject C.VS_UWORD
	ServiceGroupID   C.VS_ULONG
	Up               *StructOfGoSrvGroupIndex
	Down             *StructOfGoSrvGroupIndex
}

var GoSrvGroupIndexRoot *StructOfGoSrvGroupIndex = nil

func GoSRPGetSrvGroup(ServiceGroupID C.VS_ULONG, BasicSRPInterface unsafe.Pointer) *StarSrvGroup {
	var GoSrvGroupIndex *StructOfGoSrvGroupIndex
	var newobj *StarSrvGroup

	GoSrvGroupIndex = GoSrvGroupIndexRoot
	for {
		if GoSrvGroupIndex == nil {
			break
		}
		if GoSrvGroupIndex.ServiceGroupID == ServiceGroupID {
			break
		}
		GoSrvGroupIndex = GoSrvGroupIndex.Down
	}
	if GoSrvGroupIndex != nil {
		s := RefToGoObject(GoSrvGroupIndex.GoSrvGroupObject)
		Result, _ := s.(*StarSrvGroup)
		return Result
	}
	newobj = ToStarSrvGroup((C.VS_ULONG)(ServiceGroupID), (unsafe.Pointer)(C.Star_SRPBasic_Dup(BasicSRPInterface)))

	GoSrvGroupIndex = new(StructOfGoSrvGroupIndex)
	GoSrvGroupIndex.ServiceGroupID = ServiceGroupID
	GoSrvGroupIndex.GoSrvGroupObject = NewGoObjectRefStrong(newobj, newobj.ObjData.RefItem)
	GoSrvGroupIndex.Up = nil
	GoSrvGroupIndex.Down = nil

	if GoSrvGroupIndexRoot == nil {
		GoSrvGroupIndexRoot = GoSrvGroupIndex
	} else {
		GoSrvGroupIndexRoot.Up = GoSrvGroupIndex
		GoSrvGroupIndex.Down = GoSrvGroupIndexRoot
		GoSrvGroupIndexRoot = GoSrvGroupIndex
	}
	return newobj
}

func GoSRPDeleteSrvGroup(ServiceGroupID C.VS_ULONG) {
	var GoSrvGroupIndex *StructOfGoSrvGroupIndex

	GoSrvGroupIndex = GoSrvGroupIndexRoot
	for {
		if GoSrvGroupIndex == nil {
			break
		}
		if GoSrvGroupIndex.ServiceGroupID == ServiceGroupID {
			break
		}
		GoSrvGroupIndex = GoSrvGroupIndex.Down
	}
	if GoSrvGroupIndex == nil {
		return
	}
	if GoSrvGroupIndex.Up == nil {
		GoSrvGroupIndexRoot = GoSrvGroupIndex.Down
	} else {
		GoSrvGroupIndex.Up.Down = GoSrvGroupIndex.Down
	}
	if GoSrvGroupIndex.Down != nil {
		GoSrvGroupIndex.Down.Up = GoSrvGroupIndex.Up
	}
	DeleteGoObjectAllRef(GoSrvGroupIndex.GoSrvGroupObject)
	//free(GoSrvGroupIndex)  gc
	return
}

func GoSRPGetBasicSRPInterface(ServiceGroupID C.VS_ULONG) unsafe.Pointer {
	var GoSrvGroupIndex *StructOfGoSrvGroupIndex

	GoSrvGroupIndex = GoSrvGroupIndexRoot
	for {
		if GoSrvGroupIndex == nil {
			break
		}
		if GoSrvGroupIndex.ServiceGroupID == ServiceGroupID {
			break
		}
		GoSrvGroupIndex = GoSrvGroupIndex.Down
	}
	if GoSrvGroupIndex == nil {
		return nil
	}

	ObjData, _ := RefToGoObject(GoSrvGroupIndex.GoSrvGroupObject).(*StarSrvGroup)
	if ObjData == nil {
		return nil
	}
	return ObjData.ObjData.BasicSRPInterface
}

func GoSRPQuerySrvGroup(ServiceGroupID C.VS_ULONG) *StarSrvGroup {
	var GoSrvGroupIndex *StructOfGoSrvGroupIndex

	GoSrvGroupIndex = GoSrvGroupIndexRoot
	for {
		if GoSrvGroupIndex == nil {
			break
		}
		if GoSrvGroupIndex.ServiceGroupID == ServiceGroupID {
			break
		}
		GoSrvGroupIndex = GoSrvGroupIndex.Down
	}
	if GoSrvGroupIndex == nil {
		return nil
	}
	Result, _ := RefToGoObject(GoSrvGroupIndex.GoSrvGroupObject).(*StarSrvGroup)
	return Result
}

func GoSRPClearSrvGroup(ClearSrvGroupFlag C.VS_BOOL) {
	var GoSrvGroupIndex *StructOfGoSrvGroupIndex
	var GoSrvGroupIndex1 *StructOfGoSrvGroupIndex
	var ZeroGoSrvGroupIndex *StructOfGoSrvGroupIndex
	var ObjData *StarSrvGroupBody

	ZeroGoSrvGroupIndex = nil
	GoSrvGroupIndex = GoSrvGroupIndexRoot
	for {
		if GoSrvGroupIndex == nil {
			break
		}
		GoSrvGroupIndex1 = GoSrvGroupIndex
		GoSrvGroupIndex = GoSrvGroupIndex.Down
		if ClearSrvGroupFlag == C.VS_TRUE {
			ObjData = SrvGroupClass_getstarcoredata_byref(GoSrvGroupIndex1.GoSrvGroupObject)
			SrvGroupClass_Data_dtor_before(ObjData, ClearSrvGroupFlag)
			DeleteGoObjectAllRef(GoSrvGroupIndex1.GoSrvGroupObject)
			GoSrvGroupIndex1.GoSrvGroupObject = 0
			//free(GoSrvGroupIndex1)   gc
		} else {
			if GoSrvGroupIndex1.ServiceGroupID != 0 {
				ObjData = SrvGroupClass_getstarcoredata_byref(GoSrvGroupIndex1.GoSrvGroupObject)
				SrvGroupClass_Data_dtor_before(ObjData, C.VS_TRUE)
				DeleteGoObjectAllRef(GoSrvGroupIndex1.GoSrvGroupObject)
				GoSrvGroupIndex1.GoSrvGroupObject = 0
				//free(GoSrvGroupIndex1)  gc
			} else {
				ObjData = SrvGroupClass_getstarcoredata_byref(GoSrvGroupIndex1.GoSrvGroupObject)
				SrvGroupClass_Data_dtor_before(ObjData, C.VS_TRUE)
				ZeroGoSrvGroupIndex = GoSrvGroupIndex1
			}
		}
	}
	if ZeroGoSrvGroupIndex != nil {
		ZeroGoSrvGroupIndex.Up = nil
		ZeroGoSrvGroupIndex.Down = nil
	}
	GoSrvGroupIndexRoot = ZeroGoSrvGroupIndex
}

func GoSRPClearSrvGroupWithID(ServiceGroupID C.VS_ULONG) {
	var GoSrvGroupIndex *StructOfGoSrvGroupIndex

	GoSrvGroupIndex = GoSrvGroupIndexRoot
	for {
		if GoSrvGroupIndex == nil {
			break
		}
		if GoSrvGroupIndex.ServiceGroupID == ServiceGroupID {
			break
		}
		GoSrvGroupIndex = GoSrvGroupIndex.Down
	}
	if GoSrvGroupIndex == nil {
		return
	}
	if GoSrvGroupIndex.Up == nil {
		GoSrvGroupIndexRoot = GoSrvGroupIndex.Down
	} else {
		GoSrvGroupIndex.Up.Down = GoSrvGroupIndex.Down
	}
	if GoSrvGroupIndex.Down != nil {
		GoSrvGroupIndex.Down.Up = GoSrvGroupIndex.Up
	}
	DeleteGoObjectAllRef(GoSrvGroupIndex.GoSrvGroupObject)
	//free(GoSrvGroupIndex)  gc
}

func GoSRPSrvGroup_CheckServiceValid(self *StarSrvGroupBody) {
	var SRPInterfaceItem *StructOfSRPSrvGroup_SRPInterfaceItem
	var SRPInterface unsafe.Pointer

	SRPInterfaceItem = self.SRPInterfaceItemRoot
	for {
		if SRPInterfaceItem == nil {
			break
		}
		SRPInterface = GoObjectToSRPServiceInterface_byref(SRPInterfaceItem.ServiceObject)
		if SRPInterface == nil || C.Star_SRPI_IsValid(SRPInterface) == C.VS_FALSE {
			if SRPInterfaceItem.Up == nil {
				self.SRPInterfaceItemRoot = SRPInterfaceItem.Down
			} else {
				SRPInterfaceItem.Up.Down = SRPInterfaceItem.Down
			}
			if SRPInterfaceItem.Down != nil {
				SRPInterfaceItem.Down.Up = SRPInterfaceItem.Up
			}
			DeleteGoObjectAllRef(SRPInterfaceItem.ServiceObject)
			//free(SRPInterfaceItem)  gc
			return
		}
		SRPInterfaceItem = SRPInterfaceItem.Down
	}
}

func GoSRPQueryServiceByServiceID(fdata *StarSrvGroupBody, ServiceID *C.VS_UUID) *StarService {
	var SRPInterfaceItem *StructOfSRPSrvGroup_SRPInterfaceItem

	GoSRPSrvGroup_CheckServiceValid(fdata)
	SRPInterfaceItem = fdata.SRPInterfaceItemRoot
	for {
		if SRPInterfaceItem == nil {
			break
		}
		if C.stargo_uuidisequal(&SRPInterfaceItem.ServiceID, ServiceID) == C.VS_TRUE {
			Result, _ := RefToGoObject(SRPInterfaceItem.ServiceObject).(*StarService)
			return Result
		}
		SRPInterfaceItem = SRPInterfaceItem.Down
	}
	return nil
}

func GoSRPQueryServiceByServiceName(fdata *StarSrvGroupBody, ServiceName *C.VS_CHAR) *StarService {
	var SRPInterfaceItem *StructOfSRPSrvGroup_SRPInterfaceItem
	var SRPInterface unsafe.Pointer

	GoSRPSrvGroup_CheckServiceValid(fdata)
	SRPInterfaceItem = fdata.SRPInterfaceItemRoot
	for {
		if SRPInterfaceItem == nil {
			break
		}
		SRPInterface = GoObjectToSRPServiceInterface_byref(SRPInterfaceItem.ServiceObject)
		if SRPInterface != nil && C.Star_SRPI_IsValid(SRPInterface) == C.VS_TRUE && C.vs_string_strcmp(ServiceName, C.Star_SRPI_GetServiceName(SRPInterface)) == 0 {
			Result, _ := RefToGoObject(SRPInterfaceItem.ServiceObject).(*StarService)
			return Result
		}
		SRPInterfaceItem = SRPInterfaceItem.Down
	}
	return nil
}

func GoSRPSetObject(ServiceGroupID C.VS_ULONG, ObjectID *C.VS_UUID, Object *StarObject, IncreaseRefCount C.VS_BOOL) {
	var ObjectRefInSrvGroup *C.struct_StructOfObjectRefInSrvGroup
	var self *StarSrvGroupBody
	var ObjectTemp *StarSrvGroup

	ObjectTemp = GoSRPQuerySrvGroup(ServiceGroupID)
	if ObjectTemp == nil {
		return
	}
	self = SrvGroupClass_getstarcoredata(ObjectTemp)
	ObjectRefInSrvGroup = (*C.struct_StructOfObjectRefInSrvGroup)((unsafe.Pointer)(C.Star_SRPBasic_FindIDKey(self.BasicSRPInterface, self.ObjectIndexTree, ObjectID)))
	if ObjectRefInSrvGroup == nil {
		ObjectRefInSrvGroup = (*C.struct_StructOfObjectRefInSrvGroup)(C.stargo_MallocStructOfObjectRefInSrvGroup())
		ObjectRefInSrvGroup.RefItem = NewGoObjectRef(Object, 0)
		ObjectRefInSrvGroup.IncreaseRef = C.VS_FALSE
		C.Star_SRPBasic_InsertIDKey(self.BasicSRPInterface, self.ObjectIndexTree, ObjectID, (*C.VS_INT8)((unsafe.Pointer)(ObjectRefInSrvGroup)))
	}
	if IncreaseRefCount == C.VS_TRUE {
		if ObjectRefInSrvGroup.IncreaseRef == C.VS_FALSE {
			ObjectRefInSrvGroup.RefItem = NewGoObjectRefStrong(Object, ObjectRefInSrvGroup.RefItem)
			ObjectRefInSrvGroup.IncreaseRef = C.VS_TRUE
		}
	}
}

func GoSRPSUnlockObject(ServiceGroupID C.VS_ULONG, ObjectID *C.VS_UUID, Object *StarObject) {
	var ObjectRefInSrvGroup *C.struct_StructOfObjectRefInSrvGroup
	var self *StarSrvGroupBody
	var ObjectTemp *StarSrvGroup

	if Object == nil {
		return
	}
	ObjectTemp = GoSRPQuerySrvGroup(ServiceGroupID)
	if ObjectTemp == nil {
		return
	}
	self = SrvGroupClass_getstarcoredata(ObjectTemp)
	ObjectRefInSrvGroup = (*C.struct_StructOfObjectRefInSrvGroup)((unsafe.Pointer)(C.Star_SRPBasic_FindIDKey(self.BasicSRPInterface, self.ObjectIndexTree, ObjectID)))
	if ObjectRefInSrvGroup == nil {
		return /*--not exist--*/
	}
	if ObjectRefInSrvGroup.IncreaseRef == C.VS_TRUE {
		DeleteGoObjectAllRef(ObjectRefInSrvGroup.RefItem)
		ObjectRefInSrvGroup.RefItem = NewGoObjectRef(Object, 0)
		ObjectRefInSrvGroup.IncreaseRef = C.VS_FALSE
	}
}

func GoSRPGetObject(ServiceGroupID C.VS_ULONG, ObjectID *C.VS_UUID) *StarObject {
	var ObjectRefInSrvGroup *C.struct_StructOfObjectRefInSrvGroup
	var self *StarSrvGroupBody
	var ObjectTemp *StarSrvGroup

	ObjectTemp = GoSRPQuerySrvGroup(ServiceGroupID)
	if ObjectTemp == nil {
		return nil
	}
	self = SrvGroupClass_getstarcoredata(ObjectTemp)
	ObjectRefInSrvGroup = (*C.struct_StructOfObjectRefInSrvGroup)((unsafe.Pointer)(C.Star_SRPBasic_FindIDKey(self.BasicSRPInterface, self.ObjectIndexTree, ObjectID)))
	if ObjectRefInSrvGroup == nil {
		return nil
	}
	Result := RefToGoObject(ObjectRefInSrvGroup.RefItem)
	if IsStarObjectClassObject(Result) == false {
		return nil
	}
	return Result.(*StarObject)
}

func GetGoObjectFromSRPObject(SRPObject unsafe.Pointer, SRPInterface unsafe.Pointer) *StarObject {
	var ObjectID C.VS_UUID

	if SRPObject == nil {
		return nil
	}
	C.Star_SRPI_GetID(SRPInterface, SRPObject, &ObjectID)
	return GoSRPGetObject(C.Star_SRPI_GetServiceGroupID(SRPInterface), &ObjectID)
}

func GoSRPIsObjectGlobalRef(ServiceGroupID C.VS_ULONG, ObjectID *C.VS_UUID) bool {
	var ObjectRefInSrvGroup *C.struct_StructOfObjectRefInSrvGroup
	var self *StarSrvGroupBody
	var ObjectTemp *StarSrvGroup

	ObjectTemp = GoSRPQuerySrvGroup(ServiceGroupID)
	if ObjectTemp == nil {
		return false
	}
	self = SrvGroupClass_getstarcoredata(ObjectTemp)
	ObjectRefInSrvGroup = (*C.struct_StructOfObjectRefInSrvGroup)((unsafe.Pointer)(C.Star_SRPBasic_FindIDKey(self.BasicSRPInterface, self.ObjectIndexTree, ObjectID)))
	if ObjectRefInSrvGroup == nil {
		return false
	}
	return FROMVS_BOOL(ObjectRefInSrvGroup.IncreaseRef)
}

func GoSRPClearObject(ServiceGroupID C.VS_ULONG, ObjectID *C.VS_UUID) {
	var ObjectRefInSrvGroup *C.struct_StructOfObjectRefInSrvGroup
	var self *StarSrvGroupBody
	var ObjectTemp *StarSrvGroup

	ObjectTemp = GoSRPQuerySrvGroup(ServiceGroupID)
	if ObjectTemp == nil {
		return
	}
	self = SrvGroupClass_getstarcoredata(ObjectTemp)
	ObjectRefInSrvGroup = (*C.struct_StructOfObjectRefInSrvGroup)((unsafe.Pointer)(C.Star_SRPBasic_FindIDKey(self.BasicSRPInterface, self.ObjectIndexTree, ObjectID)))
	if ObjectRefInSrvGroup != nil {
		DeleteGoObjectAllRef(ObjectRefInSrvGroup.RefItem)
	}
}

func GetSRPServiceInterface(ServiceGroupID C.VS_ULONG, Object unsafe.Pointer) unsafe.Pointer {
	var SRPInterfaceItem *StructOfSRPSrvGroup_SRPInterfaceItem
	var SRPInterface unsafe.Pointer
	var self *StarSrvGroupBody
	var ObjectTemp *StarSrvGroup

	ObjectTemp = GoSRPQuerySrvGroup(ServiceGroupID)
	if ObjectTemp == nil {
		return nil
	}
	self = SrvGroupClass_getstarcoredata(ObjectTemp)
	if self == nil || self.SRPInterfaceItemRoot == nil {
		return nil
	}
	GoSRPSrvGroup_CheckServiceValid(self)
	if self.SRPInterfaceItemRoot == nil {
		return nil
	}
	SRPInterfaceItem = self.SRPInterfaceItemRoot
	for {
		if SRPInterfaceItem == nil {
			break
		}
		SRPInterface = GoObjectToSRPServiceInterface_byref(SRPInterfaceItem.ServiceObject)
		if Object == C.NULL || SRPInterface == C.NULL || (C.Star_SRPI_IsValid(SRPInterface) == C.VS_TRUE && C.Star_SRPI_IsThisService(SRPInterface, Object) == C.VS_TRUE) {
			return SRPInterface
		}
		SRPInterfaceItem = SRPInterfaceItem.Down
	}
	SRPInterface = GoObjectToSRPServiceInterface_byref(self.SRPInterfaceItemRoot.ServiceObject)
	SRPInterface = C.Star_SRPI_GetSRPInterface(SRPInterface, Object)
	ToStarService(self, SRPInterface)
	return SRPInterface
}

func GetSRPServiceInterfaceEx(ServiceGroupID C.VS_ULONG, ObjectID *C.VS_UUID) unsafe.Pointer {
	var SRPInterfaceItem *StructOfSRPSrvGroup_SRPInterfaceItem
	var SRPInterface unsafe.Pointer
	var self *StarSrvGroupBody
	var ObjectTemp *StarSrvGroup

	ObjectTemp = GoSRPQuerySrvGroup(ServiceGroupID)
	if ObjectTemp == nil {
		return nil
	}
	self = SrvGroupClass_getstarcoredata(ObjectTemp)
	if self == nil || self.SRPInterfaceItemRoot == nil {
		return nil
	}
	GoSRPSrvGroup_CheckServiceValid(self)
	if self.SRPInterfaceItemRoot == nil {
		return nil
	}
	SRPInterfaceItem = self.SRPInterfaceItemRoot

	for {
		if SRPInterfaceItem == nil {
			break
		}
		SRPInterface = GoObjectToSRPServiceInterface_byref(SRPInterfaceItem.ServiceObject)
		if ObjectID == nil || SRPInterface == C.NULL || (C.Star_SRPI_IsValid(SRPInterface) == C.VS_TRUE && C.Star_SRPI_IsThisServiceEx(SRPInterface, ObjectID) == C.VS_TRUE) {
			return SRPInterface
		}
		SRPInterfaceItem = SRPInterfaceItem.Down
	}
	SRPInterface = GoObjectToSRPServiceInterface_byref(self.SRPInterfaceItemRoot.ServiceObject)
	SRPInterface = C.Star_SRPI_GetSRPInterfaceEx(SRPInterface, ObjectID)
	ToStarService(self, SRPInterface)
	return SRPInterface
}

func GoSRPQueryServiceForInterface(ServiceGroupID C.VS_ULONG, Interface unsafe.Pointer) *StarService {
	var SRPInterfaceItem *StructOfSRPSrvGroup_SRPInterfaceItem
	var SRPInterface unsafe.Pointer
	var self *StarSrvGroupBody
	var ObjectTemp *StarSrvGroup
	var ServiceID1 C.VS_UUID
	var ServiceID2 C.VS_UUID

	ObjectTemp = GoSRPQuerySrvGroup(ServiceGroupID)
	if ObjectTemp == nil {
		return nil
	}
	self = SrvGroupClass_getstarcoredata(ObjectTemp)
	if self == nil || self.SRPInterfaceItemRoot == nil {
		return nil
	}
	GoSRPSrvGroup_CheckServiceValid(self)
	if self.SRPInterfaceItemRoot == nil {
		return nil
	}
	SRPInterfaceItem = self.SRPInterfaceItemRoot

	for {
		if SRPInterfaceItem == nil {
			break
		}
		SRPInterface = GoObjectToSRPServiceInterface_byref(SRPInterfaceItem.ServiceObject)
		if SRPInterface == C.NULL || C.Star_SRPI_IsValid(SRPInterface) == C.VS_FALSE {
			return nil
		}
		if Interface == nil {
			Result := RefToGoObject(SRPInterfaceItem.ServiceObject)
			if IsStarServiceClassObject(Result) == false {
				return nil
			} else {
				return Result.(*StarService)
			}
		}
		C.Star_SRPI_GetServiceID(SRPInterface, &ServiceID1)
		C.Star_SRPI_GetServiceID(Interface, &ServiceID2)
		if C.stargo_uuidisequal(&ServiceID1, &ServiceID2) == C.VS_TRUE {
			Result := RefToGoObject(SRPInterfaceItem.ServiceObject)
			if IsStarServiceClassObject(Result) == false {
				return nil
			} else {
				return Result.(*StarService)
			}
		}
		SRPInterfaceItem = SRPInterfaceItem.Down
	}
	return ToStarService(self, Interface)
}

func GoSRPQueryService(ServiceGroupID C.VS_ULONG, Object unsafe.Pointer) *StarService {
	var SRPInterfaceItem *StructOfSRPSrvGroup_SRPInterfaceItem
	var SRPInterface unsafe.Pointer
	var self *StarSrvGroupBody
	var ObjectTemp *StarSrvGroup

	ObjectTemp = GoSRPQuerySrvGroup(ServiceGroupID)
	if ObjectTemp == nil {
		return nil
	}
	self = SrvGroupClass_getstarcoredata(ObjectTemp)
	if self == nil || self.SRPInterfaceItemRoot == nil {
		return nil
	}
	GoSRPSrvGroup_CheckServiceValid(self)
	if self.SRPInterfaceItemRoot == nil {
		return nil
	}
	SRPInterfaceItem = self.SRPInterfaceItemRoot

	for {
		if SRPInterfaceItem == nil {
			break
		}
		SRPInterface = GoObjectToSRPServiceInterface_byref(SRPInterfaceItem.ServiceObject)
		if SRPInterface == C.NULL || C.Star_SRPI_IsValid(SRPInterface) == C.VS_FALSE {
			return nil
		}
		if Object == C.NULL || C.Star_SRPI_IsThisService(SRPInterface, Object) == C.VS_TRUE {
			Result := RefToGoObject(SRPInterfaceItem.ServiceObject)
			if IsStarServiceClassObject(Result) == false {
				return nil
			} else {
				return Result.(*StarService)
			}
		}
		SRPInterfaceItem = SRPInterfaceItem.Down
	}
	SRPInterface = GoObjectToSRPServiceInterface_byref(self.SRPInterfaceItemRoot.ServiceObject)
	SRPInterface = C.Star_SRPI_GetSRPInterface(SRPInterface, Object)
	return ToStarService(self, SRPInterface)
}

func GoSRPQueryServiceEx(ServiceGroupID C.VS_ULONG, ObjectID *C.VS_UUID) *StarService {
	var SRPInterfaceItem *StructOfSRPSrvGroup_SRPInterfaceItem
	var SRPInterface unsafe.Pointer
	var self *StarSrvGroupBody
	var ObjectTemp *StarSrvGroup

	ObjectTemp = GoSRPQuerySrvGroup(ServiceGroupID)
	if ObjectTemp == nil {
		return nil
	}
	self = SrvGroupClass_getstarcoredata(ObjectTemp)
	if self == nil || self.SRPInterfaceItemRoot == nil {
		return nil
	}
	GoSRPSrvGroup_CheckServiceValid(self)
	if self.SRPInterfaceItemRoot == nil {
		return nil
	}
	SRPInterfaceItem = self.SRPInterfaceItemRoot

	for {
		if SRPInterfaceItem == nil {
			break
		}
		SRPInterface = GoObjectToSRPServiceInterface_byref(SRPInterfaceItem.ServiceObject)
		if SRPInterface == C.NULL || C.Star_SRPI_IsValid(SRPInterface) == C.VS_FALSE {
			return nil
		}
		if ObjectID == nil || C.Star_SRPI_IsThisServiceEx(SRPInterface, ObjectID) == C.VS_TRUE {
			Result := RefToGoObject(SRPInterfaceItem.ServiceObject)
			if IsStarServiceClassObject(Result) == false {
				return nil
			} else {
				return Result.(*StarService)
			}
		}
		SRPInterfaceItem = SRPInterfaceItem.Down
	}
	SRPInterface = GoObjectToSRPServiceInterface_byref(self.SRPInterfaceItemRoot.ServiceObject)
	SRPInterface = C.Star_SRPI_GetSRPInterfaceEx(SRPInterface, ObjectID)
	return ToStarService(self, SRPInterface)
}

func GoClearStarCoreContext(self interface{}) {
	if IsStarServiceClassObject(self) == true {
		s := self.(*StarService)
		fdata := s.ObjData
		fdata.IsClearedByStarCore = C.VS_TRUE
		if C.StarGo_ModuleInitFlag == C.VS_TRUE {
			if fdata.SRPInterface != C.NULL {
				C.Star_SRPI_Release(fdata.SRPInterface)
			}
			fdata.SRPInterface = C.NULL
		}
		return
	}
	if IsStarParaPkgClassObject(self) == true {
		s := self.(*StarParaPkg)
		fdata := s.ObjData
		fdata.IsClearedByStarCore = C.VS_TRUE
		if fdata.FreeFlag == C.VS_TRUE && fdata.ParaPkg != C.NULL {
			if C.StarGo_ModuleInitFlag == C.VS_TRUE {
				C.Star_SRPParaPkg_Release(fdata.ParaPkg)
			}
			fdata.ParaPkg = C.NULL
		}
		return
	}
	if IsStarBinBufClassObject(self) == true {
		s := self.(*StarBinBuf)
		fdata := s.ObjData
		fdata.IsClearedByStarCore = C.VS_TRUE
		if fdata.FreeFlag == C.VS_TRUE && fdata.BinBuf != C.NULL {
			if C.StarGo_ModuleInitFlag == C.VS_TRUE {
				C.Star_SRPBinBuf_Release(fdata.BinBuf)
			}
		}
		fdata.BinBuf = C.NULL
	}
	if IsStarSXmlClassObject(self) == true {
		s := self.(*StarSXml)
		fdata := s.ObjData
		fdata.IsClearedByStarCore = C.VS_TRUE
		if fdata.FreeFlag == C.VS_TRUE && fdata.SXml != C.NULL {
			if C.StarGo_ModuleInitFlag == C.VS_TRUE {
				C.Star_SRPSXML_Release(fdata.SXml)
			}
		}
		fdata.SXml = C.NULL
	}
	if IsStarObjectClassObject(self) == true {
		s := self.(*StarObject)
		fdata := s.ObjData
		fdata.IsClearedByStarCore = C.VS_TRUE
		GoSRPSUnlockObject(fdata.ServiceGroupID, &fdata.ObjectID, s)
		GoSRPClearObject(fdata.ServiceGroupID, &fdata.ObjectID)
	}
}

//export GoFreeScriptObject
func GoFreeScriptObject(RefItem C.VS_UWORD) {
	Obj := RefToGoObject(RefItem)
	if Obj == nil {
		return
	}
	GoClearStarCoreContext(Obj)
}

//export GoObjectFreeNotify
func GoObjectFreeNotify(Obj unsafe.Pointer, RefItem C.VS_UWORD) {
	var ObjectRefInSrvGroup *C.struct_StructOfObjectRefInSrvGroup
	var ObjData *StarSrvGroupBody
	var ObjectID C.VS_UUID
	var ObjectTemp *StarSrvGroup

	if C.StarGo_ModuleInitFlag == C.VS_FALSE {
		return
	}
	ObjectTemp, _ = RefToGoObject(RefItem).(*StarSrvGroup)
	if ObjectTemp == nil {
		return
	}
	ObjData = SrvGroupClass_getstarcoredata(ObjectTemp)

	C.Star_SRPBasic_GetID(ObjData.BasicSRPInterface, Obj, &ObjectID)
	ObjectRefInSrvGroup = (*C.struct_StructOfObjectRefInSrvGroup)((unsafe.Pointer)(C.Star_SRPBasic_FindIDKey(ObjData.BasicSRPInterface, ObjData.ObjectIndexTree, &ObjectID)))
	if ObjectRefInSrvGroup == nil {
		return
	}
	S := RefToGoObject(ObjectRefInSrvGroup.RefItem)
	if IsStarObjectClassObject(S) == true {
		GoClearStarCoreContext(S)
	}
}

//export GoObjectIDChangeNotify
func GoObjectIDChangeNotify(Obj unsafe.Pointer, Para C.VS_UWORD, NewObjectID *C.VS_UUID) {
	var ObjectRefInSrvGroup *C.struct_StructOfObjectRefInSrvGroup
	var ObjData *StarSrvGroupBody
	var ObjectID C.VS_UUID
	var ObjectTemp *StarSrvGroup

	if C.StarGo_ModuleInitFlag == C.VS_FALSE {
		return
	}
	ObjectTemp, _ = RefToGoObject(Para).(*StarSrvGroup)
	if ObjectTemp == nil {
		return
	}
	ObjData = SrvGroupClass_getstarcoredata(ObjectTemp)
	C.Star_SRPBasic_GetID(ObjData.BasicSRPInterface, Obj, &ObjectID)
	ObjectRefInSrvGroup = (*C.struct_StructOfObjectRefInSrvGroup)((unsafe.Pointer)(C.Star_SRPBasic_DelIDKey(ObjData.BasicSRPInterface, ObjData.ObjectIndexTree, &ObjectID)))
	if ObjectRefInSrvGroup == nil {
		return
	}
	C.Star_SRPBasic_InsertIDKey(ObjData.BasicSRPInterface, ObjData.ObjectIndexTree, NewObjectID, (*C.VS_INT8)((unsafe.Pointer)(ObjectRefInSrvGroup)))
	S := RefToGoObject(ObjectRefInSrvGroup.RefItem)
	if IsStarObjectClassObject(S) == true {
		b, _ := S.(*StarObject)
		self := StarObjectClass_getstarcoredata(b)
		self.ObjectID = (*NewObjectID)
	}
	return
}

/*----------------------------------------------------------------------------*/
/* StarSrvGroup */
/*----------------------------------------------------------------------------*/
func (self *StarSrvGroup) CreateService(In_ServicePath string, In_ServiceName string, In_RootPass string, FrameInterval int, NetPkgSize int, UploadPkgSize int, DownloadPkgSize int, DataUpPkgSize int, DataDownPkgSize int, In_ServiceID string) *StarService {
	var ServicePath *C.VS_CHAR
	var ServiceName *C.VS_CHAR
	var RootPass *C.VS_CHAR
	var ServiceID *C.VS_CHAR
	var ObjectID C.VS_UUID
	var Result C.VS_BOOL

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}

	TermObjectDefer_Free(false)

	ServicePath = SRPGoGetStr(In_ServicePath, true)
	ServiceName = SRPGoGetStr(In_ServiceName, false)
	RootPass = SRPGoGetStr(In_RootPass, false)
	ServiceID = SRPGoGetStr(In_ServiceID, false)

	if ServiceID != nil {
		C.Star_SRPBasic_StringToUuid(self.ObjData.BasicSRPInterface, ServiceID, (*C.VS_UUID)(&ObjectID))
	} else {
		C.stargo_inituuid((*C.VS_UUID)(&ObjectID))
	}
	Result = C.Star_SRPBasic_CreateService(self.ObjData.BasicSRPInterface, ServicePath, ServiceName, &ObjectID, RootPass, (C.VS_INT32)(FrameInterval), (C.VS_INT32)(NetPkgSize), (C.VS_INT32)(UploadPkgSize), (C.VS_INT32)(DownloadPkgSize), (C.VS_INT32)(DataUpPkgSize), (C.VS_INT32)(DataDownPkgSize))
	if Result == C.VS_TRUE {
		var SRPInterface unsafe.Pointer
		C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(ServicePath))
		UserName := C.CString("root")
		defer C.free(unsafe.Pointer(UserName))
		SRPInterface = C.Star_SRPBasic_GetSRPInterface(self.ObjData.BasicSRPInterface, ServiceName, UserName, RootPass)
		STARGO_SAFERELEASESTR(In_ServiceName, ServiceName)
		STARGO_SAFERELEASESTR(In_RootPass, RootPass)
		STARGO_SAFERELEASESTR(In_ServiceID, ServiceID)
		return ToStarService(self.ObjData, SRPInterface)
	}
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(ServicePath))
	STARGO_SAFERELEASESTR(In_ServiceName, ServiceName)
	STARGO_SAFERELEASESTR(In_RootPass, RootPass)
	STARGO_SAFERELEASESTR(In_ServiceID, ServiceID)
	return nil
}

func (self *StarSrvGroup) GetService(username string, userpassword string) *StarService {
	var ObjData *StarSrvGroupBody
	var SRPInterface unsafe.Pointer
	var CharTemp1 *C.VS_CHAR
	var CharTemp2 *C.VS_CHAR
	var ServiceID C.VS_UUID
	var ObjectTemp *StarService

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}

	ObjData = self.ObjData
	CharTemp1 = SRPGoGetStr(username, false)
	CharTemp2 = SRPGoGetStr(userpassword, false)
	if C.Star_SRPBasic_QueryActiveService(ObjData.BasicSRPInterface, &ServiceID) == nil {
		STARGO_SAFERELEASESTR(username, CharTemp1)
		STARGO_SAFERELEASESTR(userpassword, CharTemp2)
		return nil
	}
	ObjectTemp = GoSRPQueryServiceByServiceID(ObjData, &ServiceID)
	if ObjectTemp != nil {
		STARGO_SAFERELEASESTR(username, CharTemp1)
		STARGO_SAFERELEASESTR(userpassword, CharTemp2)
		return ObjectTemp
	}
	SRPInterface = C.Star_SRPBasic_GetSRPInterfaceEx(ObjData.BasicSRPInterface, &ServiceID, CharTemp1, CharTemp2)
	STARGO_SAFERELEASESTR(username, CharTemp1)
	STARGO_SAFERELEASESTR(userpassword, CharTemp2)
	if SRPInterface == nil {
		return nil
	}
	return ToStarService(ObjData, SRPInterface)
}

func (self *StarSrvGroup) ClearService() {
	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}

	TermObjectDefer_Free(false)

	C.Star_SRPBasic_ClearService(self.ObjData.BasicSRPInterface)
	return
}

func (self *StarSrvGroup) NewParaPkg(args ...interface{}) *StarParaPkg {
	var ObjData *StarSrvGroupBody
	var NewParaPkg unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}
	ObjData = SrvGroupClass_getstarcoredata(self)
	NewParaPkg = C.Star_SRPBasic_GetParaPkgInterface(ObjData.BasicSRPInterface)
	if args != nil {
		SRPInterface := GetSRPServiceInterfaceEx(C.Star_SRPBasic_GetServiceGroupID(ObjData.BasicSRPInterface), (*C.VS_UUID)(C.NULL))
		if SRPInterface == nil {
			s := fmt.Sprintf("service must be created")
			c_s := C.CString(s)
			C.stargo_SRPBasic_ProcessError(ObjData.BasicSRPInterface, C.VSFAULT_WARNING, Const_GoString, 0, c_s)
			C.free(unsafe.Pointer(c_s))
		} else {
			if StarParaPkg_FromTuple_Sub(args, NewParaPkg, ObjData.BasicSRPInterface, 0, SRPInterface) == false {
				s := fmt.Sprintf("parameter not supported for starparapkg")
				c_s := C.CString(s)
				C.stargo_SRPBasic_ProcessError(ObjData.BasicSRPInterface, C.VSFAULT_WARNING, Const_GoString, 0, c_s)
				C.free(unsafe.Pointer(c_s))
			}
		}
	}
	return ToStarParaPkg(NewParaPkg, C.Star_SRPBasic_GetServiceGroupID(ObjData.BasicSRPInterface), C.VS_TRUE)
}

func (self *StarSrvGroup) NewBinBuf() *StarBinBuf {
	var ObjData *StarSrvGroupBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}
	ObjData = SrvGroupClass_getstarcoredata(self)
	Result := CreateStarBinBuf(ObjData.BasicSRPInterface)
	return Result
}

func (self *StarSrvGroup) NewSXml() *StarSXml {
	var ObjData *StarSrvGroupBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}
	ObjData = SrvGroupClass_getstarcoredata(self)
	Result := CreateStarSXml(ObjData.BasicSRPInterface)
	return Result
}

func (self *StarSrvGroup) IsObject(Arg interface{}) bool {
	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	return IsStarObjectClassObject(Arg)
}

func (self *StarSrvGroup) IsParaPkg(Arg interface{}) bool {
	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	return IsStarParaPkgClassObject(Arg)
}

func (self *StarSrvGroup) IsBinBuf(Arg interface{}) bool {
	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	return IsStarBinBufClassObject(Arg)
}
func (self *StarSrvGroup) IsSXml(Arg interface{}) bool {
	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	return IsStarSXmlClassObject(Arg)
}

func (self *StarSrvGroup) GetServicePath() string {
	var ObjData *StarSrvGroupBody
	var LocalBuf [512]C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return ""
	}
	ObjData = SrvGroupClass_getstarcoredata(self)
	C.Star_SRPBasic_GetDefaultPath(ObjData.BasicSRPInterface, (*C.VS_CHAR)(&LocalBuf[0]), 512)
	return SRPGoSetStr((*C.VS_CHAR)(&LocalBuf[0]), true)
}

func (self *StarSrvGroup) SetServicePath(Args string) {
	var ObjData *StarSrvGroupBody
	var CharTemp *C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	CharTemp = SRPGoGetStr(Args, true)
	ObjData = SrvGroupClass_getstarcoredata(self)
	C.Star_SRPBasic_SetDefaultPath(ObjData.BasicSRPInterface, CharTemp)
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(CharTemp))
	return
}

func (self *StarSrvGroup) ServicePathIsSet() bool {
	var ObjData *StarSrvGroupBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	ObjData = SrvGroupClass_getstarcoredata(self)
	return FROMVS_BOOL(C.Star_SRPBasic_DefaultPathIsSet(ObjData.BasicSRPInterface))
}

func (self *StarSrvGroup) GetCurrentPath() string {
	var LocalBuf [512]C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return ""
	}
	C.vs_dir_getcwd((*C.VS_CHAR)(&LocalBuf[0]), 512)
	return SRPGoSetStr((*C.VS_CHAR)(&LocalBuf[0]), true)
}

func (self *StarSrvGroup) ImportService(In_ServiceName string, LoadRunModule bool) bool {
	var ObjData *StarSrvGroupBody
	var ServiceName *C.VS_CHAR
	var Result C.VS_BOOL

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	ServiceName = SRPGoGetStr(In_ServiceName, true)
	ObjData = SrvGroupClass_getstarcoredata(self)
	Result = C.Star_SRPBasic_ImportService(ObjData.BasicSRPInterface, ServiceName, TOVS_BOOL(LoadRunModule))
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(ServiceName))
	return FROMVS_BOOL(Result)
}

func (self *StarSrvGroup) ClearServiceEx() {
	var ObjData *StarSrvGroupBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}

	TermObjectDefer_Free(true)

	ObjData = SrvGroupClass_getstarcoredata(self)
	C.Star_SRPBasic_ClearServiceEx(ObjData.BasicSRPInterface)
	return
}

func (self *StarSrvGroup) RunScript(In_ScriptInterface string, In_ScriptBuf string, In_Name string) bool {
	var ObjData *StarSrvGroupBody
	var ScriptInterface *C.VS_CHAR
	var ScriptBuf *C.VS_CHAR
	var ScriptName *C.VS_CHAR
	var RetResult C.VS_BOOL

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	ScriptInterface = SRPGoGetStr(In_ScriptInterface, false)
	ScriptBuf = SRPGoGetStr(In_ScriptBuf, true)
	ScriptName = SRPGoGetStr(In_Name, false)
	ObjData = SrvGroupClass_getstarcoredata(self)
	RetResult = C.Star_SRPBasic_DoBuffer(ObjData.BasicSRPInterface, ScriptInterface, ScriptBuf, (C.VS_INT32)(C.vs_string_strlen(ScriptBuf)), C.VS_FALSE, ScriptName)
	STARGO_SAFERELEASESTR(In_ScriptInterface, ScriptInterface)
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(ScriptBuf))
	STARGO_SAFERELEASESTR(In_Name, ScriptName)
	return FROMVS_BOOL(RetResult)
}

func (self *StarSrvGroup) RunScriptEx(In_ScriptInterface string, BinBuf *StarBinBuf, In_Name string) bool {
	var ObjData *StarSrvGroupBody
	var ScriptInterface *C.VS_CHAR
	var ScriptName *C.VS_CHAR
	var SRPBinBufInterface unsafe.Pointer
	var RetResult C.VS_BOOL

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	ScriptInterface = SRPGoGetStr(In_ScriptInterface, false)
	ScriptName = SRPGoGetStr(In_Name, false)
	ObjData = SrvGroupClass_getstarcoredata(self)
	SRPBinBufInterface = GoObjectToBinBuf(BinBuf)
	if SRPBinBufInterface == nil || C.Star_SRPBinBuf_GetBufPtr(SRPBinBufInterface, 0) == nil {
		STARGO_SAFERELEASESTR(In_ScriptInterface, ScriptInterface)
		STARGO_SAFERELEASESTR(In_Name, ScriptName)
		return false
	}
	RetResult = C.Star_SRPBasic_DoBuffer(ObjData.BasicSRPInterface, ScriptInterface, C.Star_SRPBinBuf_GetBufPtr(SRPBinBufInterface, 0), (C.VS_INT32)(C.Star_SRPBinBuf_GetOffset(SRPBinBufInterface)), C.VS_FALSE, ScriptName)
	STARGO_SAFERELEASESTR(In_ScriptInterface, ScriptInterface)
	STARGO_SAFERELEASESTR(In_Name, ScriptName)
	return FROMVS_BOOL(RetResult)
}

func (self *StarSrvGroup) DoFile(In_ScriptInterface string, In_FileName string) bool {
	return self.DoFileEx(In_ScriptInterface, In_FileName, "")
}

func (self *StarSrvGroup) DoFileEx(In_ScriptInterface string, In_FileName string, In_ModuleName string) bool {
	var ObjData *StarSrvGroupBody
	var ScriptInterface *C.VS_CHAR
	var FileName *C.VS_CHAR
	var ModuleName *C.VS_CHAR
	var Result C.VS_BOOL

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	ScriptInterface = SRPGoGetStr(In_ScriptInterface, false)
	FileName = SRPGoGetStr(In_FileName, true)
	ModuleName = SRPGoGetStr(In_ModuleName, false)
	ObjData = SrvGroupClass_getstarcoredata(self)
	Result = C.Star_SRPBasic_DoFileEx(ObjData.BasicSRPInterface, ScriptInterface, FileName, (**C.VS_CHAR)(C.NULL), (*C.VS_CHAR)(C.NULL), C.VS_FALSE, ModuleName)
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(FileName))
	STARGO_SAFERELEASESTR(In_ScriptInterface, ScriptInterface)
	STARGO_SAFERELEASESTR(In_ModuleName, ModuleName)
	return FROMVS_BOOL(Result)
}

func (self *StarSrvGroup) SetClientPort(LInterface string, Portnumber int) bool {
	var ObjData *StarSrvGroupBody
	var InterfaceValue *C.VS_CHAR
	var RetResult C.VS_BOOL

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	InterfaceValue = SRPGoGetStr(LInterface, false)
	ObjData = SrvGroupClass_getstarcoredata(self)
	RetResult = C.Star_SRPBasic_SetClientPort(ObjData.BasicSRPInterface, InterfaceValue, (C.VS_UINT16)(Portnumber))
	STARGO_SAFERELEASESTR(LInterface, InterfaceValue)
	return FROMVS_BOOL(RetResult)
}

func (self *StarSrvGroup) SetTelnetPort(Portnumber int) bool {
	var ObjData *StarSrvGroupBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	ObjData = SrvGroupClass_getstarcoredata(self)
	return FROMVS_BOOL(C.Star_SRPBasic_SetTelnetPort(ObjData.BasicSRPInterface, (C.VS_UINT16)(Portnumber)))
}

func (self *StarSrvGroup) SetOutputPort(Host string, Portnumber int) bool {
	var ObjData *StarSrvGroupBody
	var InterfaceValue *C.VS_CHAR
	var RetResult C.VS_BOOL

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	InterfaceValue = SRPGoGetStr(Host, false)
	ObjData = SrvGroupClass_getstarcoredata(self)
	RetResult = C.Star_SRPBasic_SetOutputPort(ObjData.BasicSRPInterface, InterfaceValue, (C.VS_UINT16)(Portnumber))
	STARGO_SAFERELEASESTR(Host, InterfaceValue)
	return FROMVS_BOOL(RetResult)
}

func (self *StarSrvGroup) SetWebServerPort(In_Host string, Portnumber int, ConnectionNumber int, PostSize int) bool {
	var ObjData *StarSrvGroupBody
	var Host *C.VS_CHAR
	var RetResult C.VS_BOOL

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	Host = SRPGoGetStr(In_Host, false)
	ObjData = SrvGroupClass_getstarcoredata(self)
	RetResult = C.Star_SRPBasic_SetWebServerPort(ObjData.BasicSRPInterface, Host, (C.VS_UINT16)(Portnumber), (C.VS_INT32)(ConnectionNumber), (C.VS_ULONG)(PostSize))
	STARGO_SAFERELEASESTR(In_Host, Host)
	return FROMVS_BOOL(RetResult)
}

func (self *StarSrvGroup) InitRaw(ScriptInterface string, Service *StarService) bool {
	var ObjData *StarSrvGroupBody
	var SRPInterface unsafe.Pointer
	var In_ScriptInterface *C.VS_CHAR
	var Result C.VS_BOOL

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	ObjData = SrvGroupClass_getstarcoredata(self)
	SRPInterface = GoObjectToSRPServiceInterface(Service)
	if SRPInterface == nil {
		return false
	}
	In_ScriptInterface = SRPGoGetStr(ScriptInterface, false)
	Result = C.Star_SRPBasic_InitRaw(ObjData.BasicSRPInterface, In_ScriptInterface, SRPInterface)
	STARGO_SAFERELEASESTR(ScriptInterface, In_ScriptInterface)
	return FROMVS_BOOL(Result)
}

func (self *StarSrvGroup) LoadRawModule(ScriptInterface string, ModuleName string, FileOrString string, IsString bool) bool {
	var ObjData *StarSrvGroupBody
	var In_ScriptInterface *C.VS_CHAR
	var In_ModuleName *C.VS_CHAR
	var In_FileOrString *C.VS_CHAR
	var Result C.VS_BOOL

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	ObjData = SrvGroupClass_getstarcoredata(self)
	In_ScriptInterface = SRPGoGetStr(ScriptInterface, false)
	In_FileOrString = SRPGoGetStr(FileOrString, true)
	In_ModuleName = SRPGoGetStr(ModuleName, true)
	Result = C.Star_SRPBasic_LoadRawModule(ObjData.BasicSRPInterface, In_ScriptInterface, In_ModuleName, In_FileOrString, TOVS_BOOL(IsString), (**C.VS_CHAR)(C.NULL))
	STARGO_SAFERELEASESTR(ScriptInterface, In_ScriptInterface)
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(In_FileOrString))
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(In_ModuleName))
	return FROMVS_BOOL(Result)
}

func (self *StarSrvGroup) GetLastError() int {
	var ObjData *StarSrvGroupBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = SrvGroupClass_getstarcoredata(self)
	return (int)(C.Star_SRPBasic_GetLastError(ObjData.BasicSRPInterface))
}

func (self *StarSrvGroup) GetLastErrorInfo() string {
	var ObjData *StarSrvGroupBody
	var LineIndex C.VS_UINT32
	var SourceName *C.VS_CHAR
	var TextBuf *C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return ""
	}
	ObjData = SrvGroupClass_getstarcoredata(self)
	TextBuf = C.Star_SRPBasic_GetLastErrorInfo(ObjData.BasicSRPInterface, &LineIndex, &SourceName)
	return fmt.Sprintf("[%s:%d]%s", C.GoString(SourceName), LineIndex, SRPGoSetStr(TextBuf, true))
}

func (self *StarSrvGroup) SUnLockGC() {
	var ObjData *StarSrvGroupBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	ObjData = SrvGroupClass_getstarcoredata(self)
	C.Star_SRPBasic_SUnLockGC(ObjData.BasicSRPInterface)
}

func (self *StarSrvGroup) GetCorePath() string {
	var ObjData *StarSrvGroupBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return ""
	}
	ObjData = SrvGroupClass_getstarcoredata(self)
	return SRPGoSetStr(C.Star_SRPBasic_GetCorePath(ObjData.BasicSRPInterface), true)
}

func (self *StarSrvGroup) GetUserPath() string {
	var ObjData *StarSrvGroupBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return ""
	}
	ObjData = SrvGroupClass_getstarcoredata(self)
	return SRPGoSetStr(C.Star_SRPBasic_GetUserPath(ObjData.BasicSRPInterface), true)
}

func (self *StarSrvGroup) GetLocalIP() string {
	var ObjData *StarSrvGroupBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return "127.0.0.1"
	}
	ObjData = SrvGroupClass_getstarcoredata(self)
	return SRPGoSetStr(C.Star_SRPBasic_GetLocalIP(ObjData.BasicSRPInterface), true)
}

func (self *StarSrvGroup) GetLocalIPEx() []string {
	var ObjData *StarSrvGroupBody
	var SockAddr [64]C.SOCKADDR_IN
	var Number C.VS_INT32
	var RetObject []string

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}
	ObjData = SrvGroupClass_getstarcoredata(self)
	Number = C.Star_SRPBasic_GetLocalIPEx(ObjData.BasicSRPInterface, (*C.SOCKADDR_IN)(&SockAddr[0]), 64)
	if Number == 0 {
		return nil
	}
	RetObject = make([]string, Number)
	for i := 0; i < (int)(Number); i++ {
		RetObject[i] = C.GoString(C.stargo_IPToString((*C.SOCKADDR_IN)(&SockAddr[i])))
	}
	return RetObject
}

func (self *StarSrvGroup) GetObjectNum() int {
	var ObjData *StarSrvGroupBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = SrvGroupClass_getstarcoredata(self)
	return (int)(C.Star_SRPBasic_GetObjectNum(ObjData.BasicSRPInterface))
}

func (self *StarSrvGroup) ActiveScriptInterface(ScriptInterface string) []bool {
	var ObjData *StarSrvGroupBody
	var In_ScriptInterface *C.VS_CHAR
	var Result C.VS_BOOL
	var OnLineScriptFlag C.VS_BOOL
	var tmp []bool

	if C.StarGo_SRPControlInterface == C.NULL {
		tmp = make([]bool, 2)
		tmp[0] = false
		tmp[1] = false
		return tmp
	}
	ObjData = SrvGroupClass_getstarcoredata(self)
	In_ScriptInterface = SRPGoGetStr(ScriptInterface, false)
	if ObjData.BasicSRPInterface == C.NULL {
		tmp = make([]bool, 2)
		tmp[0] = false
		tmp[1] = false
		return tmp
	}
	if In_ScriptInterface == nil || C.strlen(In_ScriptInterface) == 0 {
		tmp = make([]bool, 2)
		tmp[0] = false
		tmp[1] = false
		return tmp
	}
	Control := C.Star_SRPBasic_GetSRPControlInterface(ObjData.BasicSRPInterface)
	Result = C.Star_SRPControl_ActiveScriptInterface(Control, In_ScriptInterface, (*C.VS_BOOL)(&OnLineScriptFlag), C.NULL)
	C.Star_SRPControl_Release(Control)
	tmp = make([]bool, 2)
	tmp[0] = FROMVS_BOOL(Result)
	tmp[1] = FROMVS_BOOL(OnLineScriptFlag)
	return tmp
}

func (self *StarSrvGroup) PreCompile(ScriptInterface string, ScriptBuf string) []interface{} {
	var ObjData *StarSrvGroupBody
	var In_ScriptInterface *C.VS_CHAR
	var In_ScriptBuf *C.VS_CHAR
	var ErrorInfo *C.VS_CHAR
	var Result C.VS_BOOL
	var tmp []interface{}

	if C.StarGo_SRPControlInterface == C.NULL {
		tmp = make([]interface{}, 2)
		tmp[0] = false
		tmp[1] = "call\"_PreCompile\",input para error"
		return tmp
	}
	ObjData = SrvGroupClass_getstarcoredata(self)
	In_ScriptInterface = SRPGoGetStr(ScriptInterface, false)
	In_ScriptBuf = SRPGoGetStr(ScriptBuf, false)
	if ObjData.BasicSRPInterface == C.NULL {
		tmp = make([]interface{}, 2)
		tmp[0] = false
		tmp[1] = "call\"_PreCompile\",input para error"
		STARGO_SAFERELEASESTR(ScriptInterface, In_ScriptInterface)
		STARGO_SAFERELEASESTR(ScriptBuf, In_ScriptBuf)
		return tmp
	}
	if In_ScriptInterface == nil || C.strlen(In_ScriptInterface) == 0 || In_ScriptBuf == nil {
		tmp = make([]interface{}, 2)
		tmp[0] = false
		tmp[1] = "call\"_PreCompile\",input para error"
		STARGO_SAFERELEASESTR(ScriptInterface, In_ScriptInterface)
		STARGO_SAFERELEASESTR(ScriptBuf, In_ScriptBuf)
		return tmp
	}
	Result = C.Star_SRPBasic_PreCompile(ObjData.BasicSRPInterface, In_ScriptInterface, In_ScriptBuf, (C.VS_INT32)(C.vs_string_strlen(In_ScriptBuf)), EmptyString, (**C.VS_CHAR)(&ErrorInfo))
	if ErrorInfo == nil {
		tmp = make([]interface{}, 2)
		tmp[0] = FROMVS_BOOL(Result)
		tmp[1] = ""
		STARGO_SAFERELEASESTR(ScriptInterface, In_ScriptInterface)
		STARGO_SAFERELEASESTR(ScriptBuf, In_ScriptBuf)
		return tmp
	} else {
		tmp = make([]interface{}, 2)
		tmp[0] = FROMVS_BOOL(Result)
		tmp[1] = SRPGoSetStr(ErrorInfo, false)
		STARGO_SAFERELEASESTR(ScriptInterface, In_ScriptInterface)
		STARGO_SAFERELEASESTR(ScriptBuf, In_ScriptBuf)
		return tmp
	}
}

/*------------------------------------------------------------------------------------------------*/
/* StarService */
/*------------------------------------------------------------------------------------------------*/
func (self *StarService) Get(Name string) interface{} {
	var ObjData *StarServiceBody
	var ParaName *C.VS_CHAR
	var HashValue C.VS_ULONG

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}
	ParaName = SRPGoGetStr(Name, false)
	defer C.free((unsafe.Pointer)(ParaName))

	ObjData = StarServiceClass_getstarcoredata(self)
	if ObjData == nil {
		return nil
	}

	TermObjectDefer_Free(false)

	HashValue = C.Star_SRPI_GetHashValue(ObjData.SRPInterface, (unsafe.Pointer)(ParaName), (C.VS_ULONG)(C.vs_string_strlen(ParaName)), 0)
	switch HashValue {
	case 0X64756CF2: //_Name
		if strings.Compare(Name, "_Name") == 0 {
			return SRPGoSetStr(C.Star_SRPI_GetServiceName(ObjData.SRPInterface), false)
		}
	case 0X0D46C9D5: //_ServiceGroup
		if strings.Compare(Name, "_ServiceGroup") == 0 {
			return GoSRPQuerySrvGroup(ObjData.ServiceGroupID)
		}
	}
	return nil
}

func (self *StarService) GetObject(ObjectName string) *StarObject {
	var ObjData *StarServiceBody
	var CharTemp *C.VS_CHAR
	var Object unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}
	CharTemp = SRPGoGetStr(ObjectName, false)
	ObjData = StarServiceClass_getstarcoredata(self)
	if ObjData.SRPInterface == nil {
		STARGO_SAFERELEASESTR(ObjectName, CharTemp)
		return nil
	}
	Object = C.Star_SRPI_GetObjectEx(ObjData.SRPInterface, C.NULL, CharTemp)
	STARGO_SAFERELEASESTR(ObjectName, CharTemp)
	if Object == nil {
		return nil
	}
	return ToStarObject(Object, ObjData.SRPInterface, C.VS_FALSE)
}

func (self *StarService) GetObjectEx(ObjectID string) *StarObject {
	var ObjData *StarServiceBody
	var CharTemp *C.VS_CHAR
	var Object unsafe.Pointer
	var LocalObjectID C.VS_UUID

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}
	CharTemp = SRPGoGetStr(ObjectID, false)
	ObjData = StarServiceClass_getstarcoredata(self)
	if ObjData.SRPInterface == nil {
		STARGO_SAFERELEASESTR(ObjectID, CharTemp)
		return nil
	}
	C.Star_SRPI_StringToUuid(ObjData.SRPInterface, CharTemp, &LocalObjectID)
	STARGO_SAFERELEASESTR(ObjectID, CharTemp)
	Object = C.Star_SRPI_GetObject(ObjData.SRPInterface, &LocalObjectID)
	if Object == nil {
		return nil
	}
	return ToStarObject(Object, ObjData.SRPInterface, C.VS_FALSE)
}

func SRPObject_GetArrayObject(argc C.VS_INT32, args []interface{}, Index C.VS_INT32) interface{} {
	if Index >= argc {
		return nil
	}
	return args[Index]
}

func (self *StarService) New(args ...interface{}) *StarObject {
	var ObjData *StarServiceBody
	var argc C.VS_INT32 = (C.VS_INT32)(len(args))
	var QueueAttrName *C.VS_CHAR
	var AttributeChangeString *C.VS_CHAR
	var ObjectNameString *C.VS_CHAR
	var ObjectTemp interface{}
	var SRPObject unsafe.Pointer
	var SRPParentObject unsafe.Pointer
	var AttributeInfo C.VS_ATTRIBUTEINFO
	var Index C.VS_INT32 = 0
	var i C.VS_INT32
	var AttributeNumber C.VS_INT32

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}
	ObjData = StarServiceClass_getstarcoredata(self)
	if ObjData.SRPInterface == nil {
		return nil
	}
	QueueAttrName = nil
	SRPParentObject = nil
	AttributeChangeString = nil
	ObjectNameString = nil
	ObjectTemp = nil

	if argc == 0 {
		QueueAttrName = nil
		SRPParentObject = nil
	} else {
		ObjectTemp = SRPObject_GetArrayObject(argc, args, Index)
		if ObjectTemp != nil {
			if _, ok := ObjectTemp.(string); ok {
				QueueAttrName = C.CString(ObjectTemp.(string))
				defer C.free((unsafe.Pointer)(QueueAttrName))

				Index++
				ObjectTemp = SRPObject_GetArrayObject(argc, args, Index)
				if ObjectTemp == nil { //no more parameter
					ObjectNameString = QueueAttrName
					QueueAttrName = nil
					SRPParentObject = nil
				} else {
					if IsStarObjectClassObject(ObjectTemp) == true {
						SRPParentObject = GoObjectToSRPObject(ObjectTemp)
						Index++
						ObjectTemp = SRPObject_GetArrayObject(argc, args, Index)
					} else if S, ok := ObjectTemp.(string); ok {
						ObjectNameString = QueueAttrName
						QueueAttrName = nil
						SRPParentObject = nil
						AttributeChangeString = SRPGoGetStr(S, true)
						Index++
						ObjectTemp = nil //end
					} else {
						return nil
					}
				}
			} else if IsStarObjectClassObject(ObjectTemp) == true {
				SRPParentObject = GoObjectToSRPObject(ObjectTemp)
				Index++
				ObjectTemp = SRPObject_GetArrayObject(argc, args, Index)
			} else {
				C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(AttributeChangeString))
				return nil
			}
		} else {
			C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(AttributeChangeString))
			return nil
		}
	}
	if ObjectTemp != nil {
		if S, ok := ObjectTemp.(string); ok {
			ObjectNameString = SRPGoGetStr(S, false)
			Index++
			ObjectTemp = SRPObject_GetArrayObject(argc, args, Index)
			if ObjectTemp == nil { //no more parameter
			} else if S, ok := ObjectTemp.(string); ok {
				AttributeChangeString = SRPGoGetStr(S, true)
			}
		}
	}

	if SRPParentObject == nil {
		SRPObject = C.Star_SRPI_MallocObjectL(ObjData.SRPInterface, (*C.VS_UUID)(C.NULL), 0, C.NULL)
	} else {
		if C.Star_SRPI_IsObject(ObjData.SRPInterface, SRPParentObject) == C.VS_TRUE {
			if QueueAttrName != nil {
				if C.Star_SRPI_GetAttributeInfoEx(ObjData.SRPInterface, C.Star_SRPI_GetClass(ObjData.SRPInterface, SRPParentObject), QueueAttrName, &AttributeInfo) == C.VS_FALSE {
					S := C.CString(fmt.Sprintf("Get Parent Attribute [%s]", C.GoString(QueueAttrName)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(AttributeChangeString))
					return nil
				}
			} else {
				AttributeNumber = C.Star_SRPI_GetAttributeNumber(ObjData.SRPInterface, C.Star_SRPI_GetClass(ObjData.SRPInterface, SRPParentObject))
				i = 0
				for {
					if i >= AttributeNumber {
						break
					}
					C.Star_SRPI_GetAttributeInfo(ObjData.SRPInterface, C.Star_SRPI_GetClass(ObjData.SRPInterface, SRPParentObject), (C.VS_UINT8)(i), &AttributeInfo)
					if AttributeInfo.Type == C.VSTYPE_PTR && AttributeInfo.SyncType == C.VS_TRUE && C.stargo_uuidisvalid(&AttributeInfo.StructID) == C.VS_TRUE {
						break
					}
					i++
				}
				if i >= AttributeNumber {
					S := C.CString("not Found Parent Sync Attribute Queue")
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(AttributeChangeString))
					return nil
				}
			}
			SRPObject = C.Star_SRPI_MallocObject(ObjData.SRPInterface, SRPParentObject, AttributeInfo.AttributeIndex, (*C.VS_UUID)(C.NULL), 0, C.NULL)
		} else {
			SRPObject = C.Star_SRPI_MallocObject(ObjData.SRPInterface, SRPParentObject, 0, (*C.VS_UUID)(C.NULL), 0, C.NULL)
		}
	}
	if SRPObject == nil {
		C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(AttributeChangeString))
		return nil
	}
	C.Star_SRPI_SetSourceScript(ObjData.SRPInterface, SRPObject, C.StarGo_ScriptInterfaceIndex)
	if ObjectNameString != nil && C.vs_string_strlen(ObjectNameString) != 0 {
		C.Star_SRPI_SetName(ObjData.SRPInterface, SRPObject, ObjectNameString)
	}
	if AttributeChangeString != nil && C.vs_string_strlen(AttributeChangeString) != 0 {
		C.Star_SRPI_LuaInitObject(ObjData.SRPInterface, SRPObject, AttributeChangeString)
	}
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(AttributeChangeString))
	return ToStarObject(SRPObject, ObjData.SRPInterface, C.VS_TRUE)
}

func (self *StarService) RunScript(In_ScriptInterface string, In_ScriptBuf string, In_Name string, In_WorkDirectory string) []interface{} {
	var ObjData *StarServiceBody
	var ScriptBuf *C.VS_CHAR
	var Name *C.VS_CHAR
	var WorkDirectory *C.VS_CHAR
	var ErrorInfo *C.VS_CHAR
	var ScriptInterface *C.VS_CHAR
	var Result C.VS_BOOL
	var RetResult []interface{}

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}
	ObjData = StarServiceClass_getstarcoredata(self)
	if ObjData.SRPInterface == nil {
		return nil
	}
	ScriptBuf = SRPGoGetStr(In_ScriptBuf, true)
	if ScriptBuf == nil {
		return nil
	}
	Name = SRPGoGetStr(In_Name, false)
	WorkDirectory = SRPGoGetStr(In_WorkDirectory, true)
	ScriptInterface = SRPGoGetStr(In_ScriptInterface, false)
	Result = C.Star_SRPI_DoBuffer(ObjData.SRPInterface, ScriptInterface, ScriptBuf, (C.VS_INT32)(C.vs_string_strlen(ScriptBuf)), Name, (**C.VS_CHAR)(&ErrorInfo), WorkDirectory, C.VS_FALSE)
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(ScriptBuf))
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(WorkDirectory))
	if Result == C.VS_FALSE {
		RetResult = make([]interface{}, 2)
		RetResult[0] = false
		RetResult[1] = SRPGoSetStr(ErrorInfo, true)
	} else {
		RetResult = make([]interface{}, 2)
		RetResult[0] = true
		RetResult[1] = ""
	}
	STARGO_SAFERELEASESTR(In_Name, Name)
	STARGO_SAFERELEASESTR(In_ScriptInterface, ScriptInterface)
	return RetResult
}

func (self *StarService) RunScriptEx(In_ScriptInterface string, BinBuf *StarBinBuf, In_Name string, In_WorkDirectory string) []interface{} {
	var ObjData *StarServiceBody
	var SRPBinBufInterface unsafe.Pointer
	var Name *C.VS_CHAR
	var WorkDirectory *C.VS_CHAR
	var ErrorInfo *C.VS_CHAR
	var ScriptInterface *C.VS_CHAR
	var Result C.VS_BOOL
	var RetResult []interface{}

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}
	ObjData = StarServiceClass_getstarcoredata(self)
	if ObjData.SRPInterface == nil {
		return nil
	}
	SRPBinBufInterface = GoObjectToBinBuf(BinBuf)
	if SRPBinBufInterface == nil || C.Star_SRPBinBuf_GetBufPtr(SRPBinBufInterface, 0) == nil {
		return nil
	}
	Name = SRPGoGetStr(In_Name, false)
	WorkDirectory = SRPGoGetStr(In_WorkDirectory, true)
	ScriptInterface = SRPGoGetStr(In_ScriptInterface, false)
	Result = C.Star_SRPI_DoBuffer(ObjData.SRPInterface, ScriptInterface, C.Star_SRPBinBuf_GetBufPtr(SRPBinBufInterface, 0), (C.VS_INT32)(C.Star_SRPBinBuf_GetOffset(SRPBinBufInterface)), Name, (**C.VS_CHAR)(&ErrorInfo), WorkDirectory, C.VS_FALSE)
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(WorkDirectory))
	STARGO_SAFERELEASESTR(In_Name, Name)
	STARGO_SAFERELEASESTR(In_ScriptInterface, ScriptInterface)
	if Result == C.VS_FALSE {
		RetResult = make([]interface{}, 2)
		RetResult[0] = false
		RetResult[1] = SRPGoSetStr(ErrorInfo, true)
	} else {
		RetResult = make([]interface{}, 2)
		RetResult[0] = true
		RetResult[1] = ""
	}
	return RetResult
}

func (self *StarService) DoFile(In_ScriptInterface string, In_FileName string, In_WorkDirectory string) []interface{} {
	return self.DoFileEx(In_ScriptInterface, In_FileName, In_WorkDirectory, "")
}

func (self *StarService) DoFileEx(In_ScriptInterface string, In_FileName string, In_WorkDirectory string, In_ModuleName string) []interface{} {
	var ObjData *StarServiceBody
	var FileName *C.VS_CHAR
	var WorkDirectory *C.VS_CHAR
	var ErrorInfo *C.VS_CHAR
	var ScriptInterface *C.VS_CHAR
	var ModuleName *C.VS_CHAR
	var Result C.VS_BOOL
	var RetResult []interface{}

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}
	ObjData = StarServiceClass_getstarcoredata(self)
	if ObjData.SRPInterface == nil {
		return nil
	}
	if len(In_FileName) == 0 {
		return nil
	}
	FileName = SRPGoGetStr(In_FileName, true)
	WorkDirectory = SRPGoGetStr(In_WorkDirectory, true)
	ScriptInterface = SRPGoGetStr(In_ScriptInterface, false)
	ModuleName = SRPGoGetStr(In_ModuleName, false)
	Result = C.Star_SRPI_DoFileEx(ObjData.SRPInterface, ScriptInterface, FileName, (**C.VS_CHAR)(&ErrorInfo), WorkDirectory, C.VS_FALSE, ModuleName)
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(FileName))
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(WorkDirectory))
	STARGO_SAFERELEASESTR(In_ScriptInterface, ScriptInterface)
	STARGO_SAFERELEASESTR(In_ModuleName, ModuleName)
	if Result == C.VS_FALSE {
		RetResult = make([]interface{}, 2)
		RetResult[0] = false
		RetResult[1] = SRPGoSetStr(ErrorInfo, true)
	} else {
		RetResult = make([]interface{}, 2)
		RetResult[0] = true
		RetResult[1] = ""
	}
	return RetResult
}

func (self *StarService) IsServiceRegistered() bool {
	var ObjData *StarServiceBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	ObjData = StarServiceClass_getstarcoredata(self)
	if ObjData.SRPInterface == nil {
		return false
	}
	return FROMVS_BOOL(C.Star_SRPI_IsRegistered(ObjData.SRPInterface))
}

func (self *StarService) CheckPassword(Flag bool) {
	var ObjData *StarServiceBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	ObjData = StarServiceClass_getstarcoredata(self)
	if ObjData.SRPInterface == nil {
		return
	}
	C.Star_SRPI_CheckPassword(ObjData.SRPInterface, TOVS_BOOL(Flag))
}

func (self *StarService) LoadRawModule(ScriptInterface string, ModuleName string, FileOrString string, IsString bool) bool {
	var ObjData *StarServiceBody
	var In_ScriptInterface *C.VS_CHAR
	var In_ModuleName *C.VS_CHAR
	var In_FileOrString *C.VS_CHAR
	var Result C.VS_BOOL

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	ObjData = StarServiceClass_getstarcoredata(self)
	if ObjData.SRPInterface == nil {
		return false
	}
	In_ScriptInterface = SRPGoGetStr(ScriptInterface, false)
	In_FileOrString = SRPGoGetStr(FileOrString, true)
	In_ModuleName = SRPGoGetStr(ModuleName, true)
	Result = C.Star_SRPI_LoadRawModule(ObjData.SRPInterface, In_ScriptInterface, In_ModuleName, In_FileOrString, TOVS_BOOL(IsString), (**C.VS_CHAR)(C.NULL))
	STARGO_SAFERELEASESTR(ScriptInterface, In_ScriptInterface)
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(In_FileOrString))
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(In_ModuleName))
	return FROMVS_BOOL(Result)
}

func (self *StarService) NewRawProxy(ScriptInterface string, AttachObject interface{}, AttachFunction string, ProyInfo string, ProxyType int) *StarObject {
	var ObjData *StarServiceBody
	var In_ScriptInterface *C.VS_CHAR
	var In_ProyInfo *C.VS_CHAR
	var In_AttachFunction *C.VS_CHAR
	var Result unsafe.Pointer
	var SRPObject unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}
	ObjData = StarServiceClass_getstarcoredata(self)
	if ObjData.SRPInterface == nil {
		return nil
	}
	In_ScriptInterface = SRPGoGetStr(ScriptInterface, false)
	In_ProyInfo = SRPGoGetStr(ProyInfo, false)
	In_AttachFunction = SRPGoGetStr(AttachFunction, false)
	if IsStarObjectClassObject(AttachObject) == true {
		SRPObject = GoObjectToSRPObject(AttachObject)
		if SRPObject == nil {
			STARGO_SAFERELEASESTR(ScriptInterface, In_ScriptInterface)
			STARGO_SAFERELEASESTR(ProyInfo, In_ProyInfo)
			STARGO_SAFERELEASESTR(AttachFunction, In_AttachFunction)
			return nil
		}
		Result = C.Star_SRPI_NewRawProxy(ObjData.SRPInterface, In_ScriptInterface, SRPObject, In_AttachFunction, In_ProyInfo, (C.VS_INT32)(ProxyType))
	} else {
		SRPObject = C.Star_SRPI_MallocObjectL(ObjData.SRPInterface, (*C.VS_UUID)(C.NULL), 0, C.NULL)
		VSScript_GoRawContext_WrapObject(ObjData.SRPInterface, C.Star_SRPI_GetServiceGroupID(ObjData.SRPInterface), SRPObject, AttachObject, C.VS_FALSE)
		Result = C.Star_SRPI_NewRawProxy(ObjData.SRPInterface, In_ScriptInterface, SRPObject, In_AttachFunction, In_ProyInfo, (C.VS_INT32)(ProxyType))
		C.Star_SRPI_UnLockGC(ObjData.SRPInterface, SRPObject)
	}
	STARGO_SAFERELEASESTR(ScriptInterface, In_ScriptInterface)
	STARGO_SAFERELEASESTR(ProyInfo, In_ProyInfo)
	STARGO_SAFERELEASESTR(AttachFunction, In_AttachFunction)
	if Result == nil {
		return nil
	}
	return ToStarObject(Result, ObjData.SRPInterface, C.VS_TRUE)
}

func (self *StarService) ImportRawContext(ScriptInterface string, ContextName string, IsClass bool, ContextInfo string) *StarObject {
	var ObjData *StarServiceBody
	var In_ScriptInterface *C.VS_CHAR
	var In_ContextName *C.VS_CHAR
	var In_ContextInfo *C.VS_CHAR
	var Result unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}
	ObjData = StarServiceClass_getstarcoredata(self)
	if ObjData.SRPInterface == nil {
		return nil
	}
	In_ScriptInterface = SRPGoGetStr(ScriptInterface, false)
	In_ContextName = SRPGoGetStr(ContextName, false)
	In_ContextInfo = SRPGoGetStr(ContextInfo, false)
	Result = C.Star_SRPI_ImportRawContext(ObjData.SRPInterface, In_ScriptInterface, In_ContextName, TOVS_BOOL(IsClass), In_ContextInfo)
	STARGO_SAFERELEASESTR(ScriptInterface, In_ScriptInterface)
	STARGO_SAFERELEASESTR(ContextName, In_ContextName)
	STARGO_SAFERELEASESTR(ContextInfo, In_ContextInfo)
	if Result == nil {
		return nil
	}
	return ToStarObject(Result, ObjData.SRPInterface, C.VS_TRUE)
}

func (self *StarService) ImportRawObject(RawObject interface{}, IsClass bool) *StarObject {
	var ObjData *StarServiceBody
	var Result unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}
	ObjData = StarServiceClass_getstarcoredata(self)
	if ObjData.SRPInterface == nil {
		return nil
	}
	Result = VSScript_GoRawContext_WrapObject_Get(ObjData.SRPInterface, C.Star_SRPI_GetServiceGroupID(ObjData.SRPInterface), RawObject, IsClass)
	if Result == nil {
		return nil
	}
	return ToStarObject(Result, ObjData.SRPInterface, C.VS_TRUE)
}

func (self *StarService) GetLastError() int {
	var ObjData *StarServiceBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = StarServiceClass_getstarcoredata(self)
	if ObjData.SRPInterface == nil {
		return 0
	}
	return (int)(C.Star_SRPI_GetLastError(ObjData.SRPInterface))
}

func (self *StarService) GetLastErrorInfo() string {
	var ObjData *StarServiceBody
	var LineIndex C.VS_UINT32
	var SourceName *C.VS_CHAR
	var TextBuf *C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return ""
	}
	ObjData = StarServiceClass_getstarcoredata(self)
	TextBuf = C.Star_SRPI_GetLastErrorInfo(ObjData.SRPInterface, &LineIndex, &SourceName)
	return fmt.Sprintf("[%s:%d]%s", C.GoString(SourceName), LineIndex, SRPGoSetStr(TextBuf, true))
}

/*------------------------------------------------------------------------------------------------*/
/* StarParaPkg */
/*------------------------------------------------------------------------------------------------*/
func StarParaPkg_FromTuple_Sub(tuple []interface{}, ParaPkg unsafe.Pointer, BasicSRPInterface unsafe.Pointer, StartIndex C.VS_INT32, SRPInterface unsafe.Pointer) bool {
	var Index C.VS_INT32

	if StartIndex == 0 && (tuple == nil || len(tuple) == 0) {
		C.Star_SRPParaPkg_Clear(ParaPkg)
		return true
	}
	if StartIndex >= (C.VS_INT32)(len(tuple)) {
		C.Star_SRPParaPkg_Clear(ParaPkg)
		return false
	}
	if len(tuple) == 1 {
		switch tuple[0].(type) {
		case map[string]interface{}:
			/*  as dict */
			m1 := tuple[0].(map[string]interface{})
			s := make([]interface{}, 1)
			var NewParaPkg unsafe.Pointer
			Index = 0
			NewParaPkg = C.Star_SRPBasic_GetParaPkgInterface(BasicSRPInterface)
			for k, n := range m1 {
				cstr := C.CString(k)
				C.Star_SRPParaPkg_InsertStrEx(ParaPkg, Index, cstr, ((C.VS_UINT32)(len(k))))
				C.free(unsafe.Pointer(cstr))

				C.Star_SRPParaPkg_Clear(NewParaPkg)
				s[0] = n
				if StarParaPkg_FromTuple_Sub(s, NewParaPkg, BasicSRPInterface, 0, SRPInterface) == false {
					C.Star_SRPParaPkg_Clear(ParaPkg)
					return false
				}
				C.Star_SRPParaPkg_AppendFrom(ParaPkg, NewParaPkg)
				Index = Index + 2
			}
			C.Star_SRPParaPkg_AsDict(ParaPkg, C.VS_TRUE)
			C.Star_SRPParaPkg_Release(NewParaPkg)
			return true
		}
	}
	Index = 0
	for _, arg := range tuple {
		if Index < StartIndex {
			Index++
			continue
		}
		switch v := arg.(type) {
		case bool:
			C.Star_SRPParaPkg_InsertBool(ParaPkg, Index-StartIndex, TOVS_BOOL(v))
		case int8:
			C.Star_SRPParaPkg_InsertInt(ParaPkg, Index-StartIndex, (C.VS_INT32)(v))
		case int16:
			C.Star_SRPParaPkg_InsertInt(ParaPkg, Index-StartIndex, (C.VS_INT32)(v))
		case int32:
			C.Star_SRPParaPkg_InsertInt(ParaPkg, Index-StartIndex, (C.VS_INT32)(v))
		case int64:
			C.Star_SRPParaPkg_InsertInt64(ParaPkg, Index-StartIndex, (C.VS_INT64)(v))
		case int:
			switch unsafe.Sizeof(int(0)) {
			case 4:
				C.Star_SRPParaPkg_InsertInt(ParaPkg, Index-StartIndex, (C.VS_INT32)(v))
			case 8:
				C.Star_SRPParaPkg_InsertInt64(ParaPkg, Index-StartIndex, (C.VS_INT64)(v))
			}
		case uint8:
			C.Star_SRPParaPkg_InsertInt(ParaPkg, Index-StartIndex, (C.VS_INT32)((C.VS_UINT32)(v)))
		case uint16:
			C.Star_SRPParaPkg_InsertInt(ParaPkg, Index-StartIndex, (C.VS_INT32)((C.VS_UINT32)(v)))
		case uint32:
			C.Star_SRPParaPkg_InsertInt(ParaPkg, Index-StartIndex, (C.VS_INT32)((C.VS_UINT32)(v)))
		case uint64:
			C.Star_SRPParaPkg_InsertInt64(ParaPkg, Index-StartIndex, (C.VS_INT64)((C.VS_UINT64)(v)))
		case uint:
			switch unsafe.Sizeof(uint(0)) {
			case 4:
				C.Star_SRPParaPkg_InsertInt(ParaPkg, Index-StartIndex, (C.VS_INT32)((C.VS_UINT32)(v)))
			case 8:
				C.Star_SRPParaPkg_InsertInt64(ParaPkg, Index-StartIndex, (C.VS_INT64)((C.VS_UINT64)(v)))
			}
		case float32:
			C.Star_SRPParaPkg_InsertFloat(ParaPkg, Index-StartIndex, (C.VS_DOUBLE)((C.VS_FLOAT)(v)))
		case float64:
			C.Star_SRPParaPkg_InsertFloat(ParaPkg, Index-StartIndex, (C.VS_DOUBLE)((C.VS_DOUBLE)(v)))
		case complex64:
			C.Star_SRPParaPkg_Clear(ParaPkg)
			return false
		case complex128:
			C.Star_SRPParaPkg_Clear(ParaPkg)
			return false
		case string:
			cstr := C.CString(v)
			C.Star_SRPParaPkg_InsertStrEx(ParaPkg, Index-StartIndex, cstr, ((C.VS_UINT32)(len(v))))
			C.free(unsafe.Pointer(cstr))
		case *StarBinBuf:
			var SRPBinBufInterface unsafe.Pointer
			SRPBinBufInterface = GoObjectToBinBuf(arg.(*StarBinBuf))
			if SRPBinBufInterface != nil {
				C.Star_SRPParaPkg_InsertBinEx(ParaPkg, Index-StartIndex, C.Star_SRPBinBuf_GetBuf(SRPBinBufInterface), (C.VS_INT32)(C.Star_SRPBinBuf_GetOffset(SRPBinBufInterface)), C.Star_SRPBinBuf_IsFromRaw(SRPBinBufInterface))
			} else {
				C.Star_SRPParaPkg_Clear(ParaPkg)
				return false
			}
		case *StarParaPkg:
			var NewParaPkg unsafe.Pointer
			NewParaPkg = GoObjectToParaPkg(arg.(*StarParaPkg))
			if NewParaPkg != nil {
				C.Star_SRPParaPkg_InsertParaPackage(ParaPkg, Index-StartIndex, NewParaPkg)
			} else {
				C.Star_SRPParaPkg_Clear(ParaPkg)
				return false
			}
		case *StarObject:
			SRPObject := GoObjectToSRPObject(arg.(*StarObject))
			C.Star_SRPParaPkg_InsertObject(ParaPkg, Index-StartIndex, SRPObject)
		case []string:
			val := arg.([]string)
			s := make([]interface{}, len(val))
			for i, v := range val {
				s[i] = v
			}
			var NewParaPkg unsafe.Pointer

			NewParaPkg = C.Star_SRPBasic_GetParaPkgInterface(BasicSRPInterface)
			if StarParaPkg_FromTuple_Sub(s, NewParaPkg, BasicSRPInterface, 0, SRPInterface) == false {
				C.Star_SRPParaPkg_Release(NewParaPkg)
				C.Star_SRPParaPkg_Clear(ParaPkg)
				return false
			}
			C.Star_SRPParaPkg_InsertParaPackage(ParaPkg, Index-StartIndex, NewParaPkg)
			C.Star_SRPParaPkg_Release(NewParaPkg)
		case []int8:
			val := arg.([]int8)
			C.Star_SRPParaPkg_InsertBinEx(ParaPkg, Index-StartIndex, (*C.VS_INT8)((unsafe.Pointer)(&val[0])), (C.VS_INT32)(len(val)), C.VS_TRUE)
		case []byte: /*== uint8*/
			val := arg.([]byte)
			C.Star_SRPParaPkg_InsertBinEx(ParaPkg, Index-StartIndex, (*C.VS_INT8)((unsafe.Pointer)(&val[0])), (C.VS_INT32)(len(val)), C.VS_TRUE)

		case []bool:
			val := arg.([]bool)
			NewParaPkg := C.Star_SRPBasic_GetParaPkgInterface(BasicSRPInterface)
			for i := 0; i < len(val); i++ {
				C.Star_SRPParaPkg_InsertBool(NewParaPkg, (C.VS_INT32)(i), TOVS_BOOL(val[i]))
			}
			C.Star_SRPParaPkg_InsertParaPackage(ParaPkg, Index-StartIndex, NewParaPkg)
			C.Star_SRPParaPkg_Release(NewParaPkg)

		case []int16:
			val := arg.([]int16)
			NewParaPkg := C.Star_SRPBasic_GetParaPkgInterface(BasicSRPInterface)
			for i := 0; i < len(val); i++ {
				C.Star_SRPParaPkg_InsertInt(NewParaPkg, (C.VS_INT32)(i), (C.VS_INT32)(val[i]))
			}
			C.Star_SRPParaPkg_InsertParaPackage(ParaPkg, Index-StartIndex, NewParaPkg)
			C.Star_SRPParaPkg_Release(NewParaPkg)
		case []uint16:
			val := arg.([]uint16)
			NewParaPkg := C.Star_SRPBasic_GetParaPkgInterface(BasicSRPInterface)
			for i := 0; i < len(val); i++ {
				C.Star_SRPParaPkg_InsertInt(NewParaPkg, (C.VS_INT32)(i), (C.VS_INT32)(val[i]))
			}
			C.Star_SRPParaPkg_InsertParaPackage(ParaPkg, Index-StartIndex, NewParaPkg)
			C.Star_SRPParaPkg_Release(NewParaPkg)

		case []int32:
			val := arg.([]int32)
			NewParaPkg := C.Star_SRPBasic_GetParaPkgInterface(BasicSRPInterface)
			for i := 0; i < len(val); i++ {
				C.Star_SRPParaPkg_InsertInt(NewParaPkg, (C.VS_INT32)(i), (C.VS_INT32)(val[i]))
			}
			C.Star_SRPParaPkg_InsertParaPackage(ParaPkg, Index-StartIndex, NewParaPkg)
			C.Star_SRPParaPkg_Release(NewParaPkg)
		case []uint32:
			val := arg.([]uint32)
			NewParaPkg := C.Star_SRPBasic_GetParaPkgInterface(BasicSRPInterface)
			for i := 0; i < len(val); i++ {
				C.Star_SRPParaPkg_InsertInt(NewParaPkg, (C.VS_INT32)(i), (C.VS_INT32)(val[i]))
			}
			C.Star_SRPParaPkg_InsertParaPackage(ParaPkg, Index-StartIndex, NewParaPkg)
			C.Star_SRPParaPkg_Release(NewParaPkg)

		case []int:
			val := arg.([]int)
			NewParaPkg := C.Star_SRPBasic_GetParaPkgInterface(BasicSRPInterface)
			for i := 0; i < len(val); i++ {
				switch unsafe.Sizeof(uint(0)) {
				case 4:
					C.Star_SRPParaPkg_InsertInt(NewParaPkg, (C.VS_INT32)(i), (C.VS_INT32)(val[i]))
				case 8:
					C.Star_SRPParaPkg_InsertInt64(NewParaPkg, (C.VS_INT32)(i), (C.VS_INT64)(val[i]))
				}
			}
			C.Star_SRPParaPkg_InsertParaPackage(ParaPkg, Index-StartIndex, NewParaPkg)
			C.Star_SRPParaPkg_Release(NewParaPkg)
		case []uint:
			val := arg.([]uint)
			NewParaPkg := C.Star_SRPBasic_GetParaPkgInterface(BasicSRPInterface)
			for i := 0; i < len(val); i++ {
				switch unsafe.Sizeof(uint(0)) {
				case 4:
					C.Star_SRPParaPkg_InsertInt(NewParaPkg, (C.VS_INT32)(i), (C.VS_INT32)(val[i]))
				case 8:
					C.Star_SRPParaPkg_InsertInt64(NewParaPkg, (C.VS_INT32)(i), (C.VS_INT64)(val[i]))
				}
			}
			C.Star_SRPParaPkg_InsertParaPackage(ParaPkg, Index-StartIndex, NewParaPkg)
			C.Star_SRPParaPkg_Release(NewParaPkg)

		case []int64:
			val := arg.([]int64)
			NewParaPkg := C.Star_SRPBasic_GetParaPkgInterface(BasicSRPInterface)
			for i := 0; i < len(val); i++ {
				C.Star_SRPParaPkg_InsertInt64(NewParaPkg, (C.VS_INT32)(i), (C.VS_INT64)(val[i]))
			}
			C.Star_SRPParaPkg_InsertParaPackage(ParaPkg, Index-StartIndex, NewParaPkg)
			C.Star_SRPParaPkg_Release(NewParaPkg)
		case []uint64:
			val := arg.([]uint64)
			NewParaPkg := C.Star_SRPBasic_GetParaPkgInterface(BasicSRPInterface)
			for i := 0; i < len(val); i++ {
				C.Star_SRPParaPkg_InsertInt64(NewParaPkg, (C.VS_INT32)(i), (C.VS_INT64)(val[i]))
			}
			C.Star_SRPParaPkg_InsertParaPackage(ParaPkg, Index-StartIndex, NewParaPkg)
			C.Star_SRPParaPkg_Release(NewParaPkg)

		case []float32:
			val := arg.([]float32)
			NewParaPkg := C.Star_SRPBasic_GetParaPkgInterface(BasicSRPInterface)
			for i := 0; i < len(val); i++ {
				C.Star_SRPParaPkg_InsertFloat(NewParaPkg, (C.VS_INT32)(i), (C.VS_DOUBLE)((C.VS_FLOAT)(val[i])))
			}
			C.Star_SRPParaPkg_InsertParaPackage(ParaPkg, Index-StartIndex, NewParaPkg)
			C.Star_SRPParaPkg_Release(NewParaPkg)

		case []float64:
			val := arg.([]float64)
			NewParaPkg := C.Star_SRPBasic_GetParaPkgInterface(BasicSRPInterface)
			for i := 0; i < len(val); i++ {
				C.Star_SRPParaPkg_InsertFloat(NewParaPkg, (C.VS_INT32)(i), (C.VS_DOUBLE)((C.VS_DOUBLE)(val[i])))
			}
			C.Star_SRPParaPkg_InsertParaPackage(ParaPkg, Index-StartIndex, NewParaPkg)
			C.Star_SRPParaPkg_Release(NewParaPkg)

		case []interface{}:
			val := arg.([]interface{})
			var NewParaPkg unsafe.Pointer

			NewParaPkg = C.Star_SRPBasic_GetParaPkgInterface(BasicSRPInterface)
			if StarParaPkg_FromTuple_Sub(val, NewParaPkg, BasicSRPInterface, 0, SRPInterface) == false {
				C.Star_SRPParaPkg_Release(NewParaPkg)
				C.Star_SRPParaPkg_Clear(ParaPkg)
				return false
			}
			C.Star_SRPParaPkg_InsertParaPackage(ParaPkg, Index-StartIndex, NewParaPkg)
			C.Star_SRPParaPkg_Release(NewParaPkg)

		case map[string]interface{}:
			val := arg.(map[string]interface{})
			s := make([]interface{}, 1)
			s[0] = val
			var NewParaPkg unsafe.Pointer

			NewParaPkg = C.Star_SRPBasic_GetParaPkgInterface(BasicSRPInterface)
			if StarParaPkg_FromTuple_Sub(s, NewParaPkg, BasicSRPInterface, 0, SRPInterface) == false {
				C.Star_SRPParaPkg_Release(NewParaPkg)
				C.Star_SRPParaPkg_Clear(ParaPkg)
				return false
			}
			C.Star_SRPParaPkg_InsertParaPackage(ParaPkg, Index-StartIndex, NewParaPkg)
			C.Star_SRPParaPkg_Release(NewParaPkg)

		case nil:
			C.Star_SRPParaPkg_InsertEmpty(ParaPkg, Index-StartIndex)
		default:
			if SRPInterface == nil {
				C.Star_SRPParaPkg_Clear(ParaPkg)
				return false
			} else {
				var NewSRPObject unsafe.Pointer
				NewSRPObject = g_GoRawContextRefManager.GetObject(v, SRPInterface, C.VS_FALSE)
				if NewSRPObject == nil {
					C.Star_SRPParaPkg_Clear(ParaPkg)
					return false
				} else {
					C.Star_SRPParaPkg_InsertObject(ParaPkg, Index-StartIndex, NewSRPObject)
					C.Star_SRPI_DelRefEx(SRPInterface, NewSRPObject)
				}
			}
		}
		Index = Index + 1
	}
	return true
}

func StarParaPkg_ToTuple_Sub(ParaPkg unsafe.Pointer, BasicSRPInterface unsafe.Pointer, StartIndex C.VS_INT32, ToRaw C.VS_BOOL) []interface{} {
	var Index, Number C.VS_INT32
	var RetValue []interface{}
	var SRPBinBufInterface unsafe.Pointer
	var SRPParaPackageInterface unsafe.Pointer
	var Length C.VS_INT32
	var Buf unsafe.Pointer

	Number = C.Star_SRPParaPkg_GetNumber(ParaPkg)
	if Number < StartIndex {
		return nil
	}
	RetValue = make([]interface{}, Number-StartIndex)
	for Index = StartIndex; Index < Number; Index++ {
		switch C.Star_SRPParaPkg_GetType(ParaPkg, Index) {
		case C.SRPPARATYPE_INT:
			RetValue[Index-StartIndex] = (int)(C.Star_SRPParaPkg_GetInt(ParaPkg, Index))
		case C.SRPPARATYPE_INT64:
			RetValue[Index-StartIndex] = (int64)(C.Star_SRPParaPkg_GetInt64(ParaPkg, Index))
		case C.SRPPARATYPE_FLOAT:
			RetValue[Index-StartIndex] = (float64)(C.Star_SRPParaPkg_GetFloat(ParaPkg, Index))
		case C.SRPPARATYPE_CHARPTR:
			{
				var Str *C.VS_CHAR
				var StrLen C.VS_UINT32
				Str = C.Star_SRPParaPkg_GetStrEx(ParaPkg, Index, &StrLen)
				var ttt string = SRPGoSetStrEx(Str, (C.VS_INT32)(StrLen), true)
				if len(ttt) == 0 && StrLen != 0 { //--changed to byte array
					var Temp []byte = make([]byte, StrLen)
					if StrLen != 0 {
						C.memcpy((unsafe.Pointer)(&Temp[0]), (unsafe.Pointer)(Str), (C.size_t)(StrLen))
					}
					RetValue[Index-StartIndex] = Temp
				} else {
					RetValue[Index-StartIndex] = ttt
				}
			}
		case C.SRPPARATYPE_BOOL:
			RetValue[Index-StartIndex] = FROMVS_BOOL(C.Star_SRPParaPkg_GetBool(ParaPkg, Index))
		case C.SRPPARATYPE_BIN:
			{
				var FromRaw C.VS_BOOL
				Buf = (unsafe.Pointer)(C.Star_SRPParaPkg_GetBinEx(ParaPkg, Index, &Length, &FromRaw))
				if ToRaw == C.VS_FALSE {
					if FromRaw == C.VS_FALSE {
						SRPBinBufInterface = C.Star_SRPBasic_GetSRPBinBufInterface(BasicSRPInterface)
						C.Star_SRPBinBuf_Set(SRPBinBufInterface, 0, (C.VS_UINT32)(Length), (*C.VS_INT8)(Buf))
						RetValue[Index-StartIndex] = ToStarBinBuf(SRPBinBufInterface, C.Star_SRPBasic_GetServiceGroupID(BasicSRPInterface), C.VS_TRUE)
					} else {
						var Temp []byte = make([]byte, Length)
						if Length != 0 {
							C.memcpy((unsafe.Pointer)(&Temp[0]), Buf, (C.size_t)(Length))
						}
						RetValue[Index-StartIndex] = Temp
					}
				} else {
					var Temp []byte = make([]byte, Length)
					if Length != 0 {
						C.memcpy((unsafe.Pointer)(&Temp[0]), Buf, (C.size_t)(Length))
					}
					RetValue[Index-StartIndex] = Temp
				}
			}
		case C.SRPPARATYPE_OBJECT:
			{
				var SRPObject unsafe.Pointer = C.Star_SRPParaPkg_GetObject(ParaPkg, Index)
				if SRPObject == nil {
					RetValue[Index-StartIndex] = nil
				} else {
					if ToRaw == C.VS_FALSE {
						RetValue[Index-StartIndex] = ToStarObject(SRPObject, BasicSRPInterface, C.VS_FALSE)
					} else {
						var LocalObjectTemp *StarObject = VSScript_GoRawContext_GetRawObjectEx(BasicSRPInterface, SRPObject)
						if LocalObjectTemp != nil {
							RetValue[Index-StartIndex] = LocalObjectTemp
						} else {
							RetValue[Index-StartIndex] = ToStarObject(SRPObject, BasicSRPInterface, C.VS_FALSE)
						}
					}
				}
			}
		case C.SRPPARATYPE_PARAPKG:
			SRPParaPackageInterface = C.Star_SRPParaPkg_GetParaPackage(ParaPkg, Index)
			if SRPParaPackageInterface == nil {
				RetValue[Index-StartIndex] = nil
			} else {
				if ToRaw == C.VS_FALSE || C.Star_SRPParaPkg_GetScriptRawType(SRPParaPackageInterface) == 0 {
					RetValue[Index-StartIndex] = StarParaPkg_ToTuple_Sub(SRPParaPackageInterface, BasicSRPInterface, 0, ToRaw)
				} else {
					RetValue[Index-StartIndex] = nil /*--not supported */
				}
			}
		default:
			RetValue[Index-StartIndex] = nil
		}
	}
	return RetValue
}

func (self *StarParaPkg) GetNumber() int {
	var ObjData *StarParaPkgBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = StarParaPkgClass_getstarcoredata(self)
	if ObjData == nil {
		return 0
	}
	TermObjectDefer_Free(false)
	return (int)(C.Star_SRPParaPkg_GetNumber(ObjData.ParaPkg))
}

func (self *StarParaPkg) Get(Index int) interface{} {
	var ObjData *StarParaPkgBody
	var BasicSRPInterface unsafe.Pointer
	var SRPBinBufInterface unsafe.Pointer
	var SRPParaPackageInterface unsafe.Pointer
	var Length C.VS_INT32
	var Buf unsafe.Pointer
	var SRPObject unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}
	ObjData = StarParaPkgClass_getstarcoredata(self)
	if ObjData == nil {
		return nil
	}
	TermObjectDefer_Free(false)

	if true {
		switch C.Star_SRPParaPkg_GetType(ObjData.ParaPkg, (C.VS_INT32)(Index)) {
		case C.SRPPARATYPE_BOOL:
			return FROMVS_BOOL(C.Star_SRPParaPkg_GetBool(ObjData.ParaPkg, (C.VS_INT32)(Index)))
		case C.SRPPARATYPE_INT:
			return (int)(C.Star_SRPParaPkg_GetInt(ObjData.ParaPkg, (C.VS_INT32)(Index)))
		case C.SRPPARATYPE_INT64:
			return (int64)(C.Star_SRPParaPkg_GetInt64(ObjData.ParaPkg, (C.VS_INT32)(Index)))
		case C.SRPPARATYPE_FLOAT:
			return (float64)(C.Star_SRPParaPkg_GetFloat(ObjData.ParaPkg, (C.VS_INT32)(Index)))
		case C.SRPPARATYPE_BIN:
			{
				var FromRaw C.VS_BOOL
				BasicSRPInterface = GoSRPGetBasicSRPInterface(ObjData.ServiceGroupID)
				if BasicSRPInterface == nil {
					return nil
				}
				Buf = (unsafe.Pointer)(C.Star_SRPParaPkg_GetBinEx(ObjData.ParaPkg, (C.VS_INT32)(Index), (*C.VS_INT32)(&Length), (*C.VS_BOOL)(&FromRaw)))
				if Buf == nil {
					return nil
				}
				if FromRaw == C.VS_FALSE {
					SRPBinBufInterface = C.Star_SRPBasic_GetSRPBinBufInterface(BasicSRPInterface)
					C.Star_SRPBinBuf_Set(SRPBinBufInterface, 0, (C.VS_UINT32)(Length), (*C.VS_INT8)(Buf))
					return ToStarBinBuf(SRPBinBufInterface, ObjData.ServiceGroupID, C.VS_TRUE)
				} else {
					var Temp []byte = make([]byte, Length)
					if Length != 0 {
						C.memcpy((unsafe.Pointer)(&Temp[0]), (unsafe.Pointer)(Buf), (C.size_t)(Length))
					}
					return Temp
				}
			}
		case C.SRPPARATYPE_CHARPTR:
			{
				var Str *C.VS_CHAR
				var StrLen C.VS_UINT32
				Str = C.Star_SRPParaPkg_GetStrEx(ObjData.ParaPkg, (C.VS_INT32)(Index), (*C.VS_UINT32)(&StrLen))
				ttt := SRPGoSetStrEx(Str, (C.VS_INT32)(StrLen), true)
				if len(ttt) != 0 || StrLen == 0 {
					return ttt
				}
				var Temp []byte = make([]byte, StrLen)
				if StrLen != 0 {
					C.memcpy((unsafe.Pointer)(&Temp[0]), (unsafe.Pointer)(Str), (C.size_t)(StrLen))
				}
				return Temp
			}
		case C.SRPPARATYPE_OBJECT:
			BasicSRPInterface = GoSRPGetBasicSRPInterface(ObjData.ServiceGroupID)
			if BasicSRPInterface == nil {
				return nil
			}
			SRPObject = C.Star_SRPParaPkg_GetObject(ObjData.ParaPkg, (C.VS_INT32)(Index))
			if SRPObject == nil {
				return nil
			}
			return ToStarObject_Basic(SRPObject, BasicSRPInterface, C.VS_FALSE)
		case C.SRPPARATYPE_PARAPKG:
			SRPParaPackageInterface = C.Star_SRPParaPkg_GetParaPackage(ObjData.ParaPkg, (C.VS_INT32)(Index))
			if SRPParaPackageInterface == nil {
				return nil
			}
			C.Star_SRPParaPkg_AddRef(SRPParaPackageInterface)
			return ToStarParaPkg(SRPParaPackageInterface, ObjData.ServiceGroupID, C.VS_TRUE)
		case C.SRPPARATYPE_INVALID:
			return nil
		}
		return nil
	}
	return nil
}

func (self *StarParaPkg) GetBool(Index int) bool {
	S, ok := self.Get(Index).(bool)
	if ok {
		return S
	}
	return false
}

func (self *StarParaPkg) GetInt(Index int) int32 {
	res := self.Get(Index)
	val := SRPGoToInt(res, true)
	return (int32)(val)
}

func (self *StarParaPkg) GetInt64(Index int) int64 {
	res := self.Get(Index)
	val := SRPGoToInt64(res, true)
	return (int64)(val)
}

func (self *StarParaPkg) GetString(Index int) string {
	S, ok := self.Get(Index).(string)
	if ok {
		return S
	}
	return ""
}

func (self *StarParaPkg) GetDouble(Index int) float64 {
	res := self.Get(Index)
	val := SRPGoToFloat(res)
	return (float64)(val)
}

func (self *StarParaPkg) GetObject(Index int) *StarObject {
	S, ok := self.Get(Index).(*StarObject)
	if ok {
		return S
	}
	return nil
}

func (self *StarParaPkg) GetParaPkg(Index int) *StarParaPkg {
	S, ok := self.Get(Index).(*StarParaPkg)
	if ok {
		return S
	}
	return nil
}

func (self *StarParaPkg) GetBinBuf(Index int) *StarBinBuf {
	S, ok := self.Get(Index).(*StarBinBuf)
	if ok {
		return S
	}
	return nil
}

func (self *StarParaPkg) Clear() *StarParaPkg {
	var ObjData *StarParaPkgBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return self
	}
	ObjData = StarParaPkgClass_getstarcoredata(self)
	if ObjData == nil {
		return self
	}
	C.Star_SRPParaPkg_Clear(ObjData.ParaPkg)
	return self
}

func (self *StarParaPkg) AppendFrom(SrcParaPkg *StarParaPkg) bool {
	var ObjData *StarParaPkgBody
	var SrcObjData *StarParaPkgBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	ObjData = StarParaPkgClass_getstarcoredata(self)
	SrcObjData = StarParaPkgClass_getstarcoredata(SrcParaPkg)
	if ObjData == nil || SrcObjData == nil {
		return false
	}
	return FROMVS_BOOL(C.Star_SRPParaPkg_AppendFrom(ObjData.ParaPkg, SrcObjData.ParaPkg))
}

func (self *StarParaPkg) Set(Index int, Value interface{}) *StarParaPkg {
	var ObjData *StarParaPkgBody
	var SRPInterface unsafe.Pointer
	var BasicSRPInterface unsafe.Pointer
	var Number C.VS_INT32

	if C.StarGo_SRPControlInterface == C.NULL {
		return self
	}
	ObjData = StarParaPkgClass_getstarcoredata(self)
	if ObjData == nil {
		return self
	}
	if Value == nil {
		C.Star_SRPParaPkg_InsertEmpty(ObjData.ParaPkg, (C.VS_INT32)(Index))
		return self
	}
	BasicSRPInterface = GoSRPGetBasicSRPInterface(ObjData.ServiceGroupID)
	SRPInterface = GetSRPServiceInterface(ObjData.ServiceGroupID, nil)
	SubPara := make([]interface{}, 1)
	SubPara[0] = Value
	NewParaPkg := C.Star_SRPBasic_GetParaPkgInterface(BasicSRPInterface)
	if StarParaPkg_FromTuple_Sub(SubPara, NewParaPkg, BasicSRPInterface, 0, SRPInterface) == false {
		s := fmt.Sprintf("parameter not supported for starparapkg")
		c_s := C.CString(s)
		C.stargo_SRPI_ProcessError(SRPInterface, C.VSFAULT_WARNING, Const_GoString, 0, c_s)
		C.free(unsafe.Pointer(c_s))
		C.Star_SRPParaPkg_Release(NewParaPkg)
		return self
	}
	Number = C.Star_SRPParaPkg_GetNumber(ObjData.ParaPkg)
	if Number == (C.VS_INT32)(Index) {
		C.Star_SRPParaPkg_AppendFrom(ObjData.ParaPkg, NewParaPkg)
		C.Star_SRPParaPkg_Release(NewParaPkg)
		return self
	} else if Number < (C.VS_INT32)(Index) {
		for i := Number; i < (C.VS_INT32)(Index); i++ {
			C.Star_SRPParaPkg_InsertEmpty(ObjData.ParaPkg, (C.VS_INT32)(i))
		}
		C.Star_SRPParaPkg_AppendFrom(ObjData.ParaPkg, NewParaPkg)
		C.Star_SRPParaPkg_Release(NewParaPkg)
		return self
	} else {
		C.Star_SRPParaPkg_AppendFrom(ObjData.ParaPkg, NewParaPkg)
		C.Star_SRPParaPkg_ExChange(ObjData.ParaPkg, (C.VS_INT32)(Index), Number)
		C.Star_SRPParaPkg_Del(ObjData.ParaPkg, Number)
		C.Star_SRPParaPkg_Release(NewParaPkg)
		return self
	}
}

func (self *StarParaPkg) Build(tuple ...interface{}) *StarParaPkg {
	var ObjData *StarParaPkgBody
	var SRPInterface unsafe.Pointer
	var BasicSRPInterface unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return self
	}
	ObjData = StarParaPkgClass_getstarcoredata(self)
	if ObjData == nil {
		return self
	}
	C.Star_SRPParaPkg_Clear(ObjData.ParaPkg)
	BasicSRPInterface = GoSRPGetBasicSRPInterface(ObjData.ServiceGroupID)
	SRPInterface = GetSRPServiceInterface(ObjData.ServiceGroupID, nil)
	if StarParaPkg_FromTuple_Sub(tuple, ObjData.ParaPkg, BasicSRPInterface, 0, SRPInterface) == false {
		s := fmt.Sprintf("parameter not supported for starparapkg")
		c_s := C.CString(s)
		C.stargo_SRPI_ProcessError(SRPInterface, C.VSFAULT_WARNING, Const_GoString, 0, c_s)
		C.free(unsafe.Pointer(c_s))
		return self
	}
	return self
}

func (self *StarParaPkg) Free() {
	var ObjData *StarParaPkgBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	ObjData = StarParaPkgClass_getstarcoredata(self)
	if ObjData == nil {
		return
	}
	DeleteGoObjectAllRef(ObjData.RefItem)

	_TermObject_Defer(ObjData)
	return
}

func (self *StarParaPkg) Dispose() {
	self.Free()
}

func (self *StarParaPkg) ReleaseOwner() {
	var fdata *StarParaPkgBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	fdata = StarParaPkgClass_getstarcoredata(self)
	if fdata == nil {
		return
	}
	if fdata.IsClearedByStarCore == C.VS_FALSE {
		if fdata.FreeFlag == C.VS_TRUE && fdata.ParaPkg != nil {
			if C.StarGo_ModuleInitFlag == C.VS_TRUE {
				C.Star_SRPParaPkg_ReleaseOwner(fdata.ParaPkg)
			}
		}
		fdata.IsClearedByStarCore = C.VS_TRUE
	}
	if C.StarGo_ModuleInitFlag == C.VS_TRUE && C.StarGo_SRPControlInterface != nil && fdata.RefItem != 0 {
		C.Star_SRPControl_UnRegScriptObject(C.StarGo_SRPControlInterface, (C.VS_UWORD)(fdata.RefItem), (unsafe.Pointer)(C.stargo_FreeScriptObject), 0)
	}
	return
}

func (self *StarParaPkg) AsDict(IsDict bool) *StarParaPkg {
	var fdata *StarParaPkgBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return self
	}
	fdata = StarParaPkgClass_getstarcoredata(self)
	if fdata == nil {
		return self
	}
	C.Star_SRPParaPkg_AsDict(fdata.ParaPkg, TOVS_BOOL(IsDict))
	return self
}

func (self *StarParaPkg) IsDict() bool {
	var fdata *StarParaPkgBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	fdata = StarParaPkgClass_getstarcoredata(self)
	if fdata == nil {
		return false
	}
	return FROMVS_BOOL(C.Star_SRPParaPkg_IsDict(fdata.ParaPkg))
}

func (self *StarParaPkg) FromJSon(Buf string) bool {
	var fdata *StarParaPkgBody
	var Local_Buf *C.VS_CHAR
	var Result C.VS_BOOL

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	fdata = StarParaPkgClass_getstarcoredata(self)
	if fdata == nil {
		return false
	}
	Local_Buf = SRPGoGetStr(Buf, true)
	Result = C.Star_SRPParaPkg_FromJSon(fdata.ParaPkg, Local_Buf)
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(Local_Buf))
	return FROMVS_BOOL(Result)
}

func (self *StarParaPkg) ToJSon() string {
	var fdata *StarParaPkgBody
	var Buf *C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return ""
	}
	fdata = StarParaPkgClass_getstarcoredata(self)
	if fdata == nil {
		return ""
	}
	Buf = C.Star_SRPParaPkg_ToJSon(fdata.ParaPkg)
	if Buf == nil {
		return ""
	}
	return SRPGoSetStr(Buf, true)
}

/*------------------------------------------------------------------------------------------------*/
/* StarBinBuf */
/*------------------------------------------------------------------------------------------------*/
func (self *StarBinBuf) GetOffset() int {
	var ObjData *StarBinBufBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = StarBinBufClass_getstarcoredata(self)
	if ObjData == nil {
		return 0
	}
	TermObjectDefer_Free(false)

	return (int)((uint)(C.Star_SRPBinBuf_GetOffset(ObjData.BinBuf)))
}

func (self *StarBinBuf) Init(BufSize int) {
	var ObjData *StarBinBufBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	ObjData = StarBinBufClass_getstarcoredata(self)
	if ObjData == nil {
		return
	}
	C.Star_SRPBinBuf_Init(ObjData.BinBuf, (C.VS_UINT32)(BufSize))
	return
}

func (self *StarBinBuf) Clear() {
	var ObjData *StarBinBufBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	ObjData = StarBinBufClass_getstarcoredata(self)
	if ObjData == nil {
		return
	}
	C.Star_SRPBinBuf_Clear(ObjData.BinBuf)
	return
}

func (self *StarBinBuf) SaveToFile(In_FileName string, TxtFileFlag bool) bool {
	var ObjData *StarBinBufBody
	var FileName *C.VS_CHAR
	var hFile *C.FILE
	var Length C.VS_INT32
	var Buf *C.VS_INT8

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	ObjData = StarBinBufClass_getstarcoredata(self)
	if ObjData == nil {
		return false
	}
	Buf = C.Star_SRPBinBuf_GetBuf(ObjData.BinBuf)
	Length = (C.VS_INT32)(C.Star_SRPBinBuf_GetOffset(ObjData.BinBuf))
	if Buf == nil || Length == (C.VS_INT32)(0) {
		return false
	}
	FileName = SRPGoGetStr(In_FileName, true)
	if TxtFileFlag == true {
		hFile = C.vs_file_fopen(FileName, Const_FILEMODE_WT)
	} else {
		hFile = C.vs_file_fopen(FileName, Const_FILEMODE_WB)
	}
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(FileName))
	if hFile == nil {
		return false
	}
	if Length != (C.VS_INT32)(0) {
		C.fwrite((unsafe.Pointer)(Buf), 1, (C.size_t)(Length), hFile)
	}
	C.fclose(hFile)
	return true
}

func (self *StarBinBuf) LoadFromFile(In_FileName string, TxtFileFlag bool) bool {
	var ObjData *StarBinBufBody
	var FileName *C.VS_CHAR
	var hFile *C.FILE
	var Length C.VS_INT32
	var Buf *C.VS_INT8
	var Result C.VS_BOOL

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	ObjData = StarBinBufClass_getstarcoredata(self)
	if ObjData == nil {
		return false
	}
	FileName = SRPGoGetStr(In_FileName, true)
	if TxtFileFlag == true {
		hFile = C.vs_file_fopen(FileName, Const_FILEMODE_RT)
	} else {
		hFile = C.vs_file_fopen(FileName, Const_FILEMODE_RB)
	}
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(FileName))
	if hFile == nil {
		return false
	}
	C.fseek(hFile, 0, C.SEEK_END)
	Length = (C.VS_INT32)(C.ftell(hFile))
	C.fseek(hFile, 0, C.SEEK_SET)
	Buf = (*C.VS_INT8)(C.malloc((C.size_t)(Length)))
	Length = (C.VS_INT32)(C.fread((unsafe.Pointer)(Buf), 1, (C.size_t)(Length), hFile))
	C.fclose(hFile)
	C.Star_SRPBinBuf_Clear(ObjData.BinBuf)
	Result = C.Star_SRPBinBuf_Set(ObjData.BinBuf, 0, (C.VS_UINT32)(Length), Buf)
	C.free((unsafe.Pointer)(Buf))
	return FROMVS_BOOL(Result)
}

func (self *StarBinBuf) Read(Buf []byte, Offset int, Length int) int {
	var ObjData *StarBinBufBody
	var Size C.VS_UINT32
	var BufPtr *C.VS_INT8

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = StarBinBufClass_getstarcoredata(self)
	if ObjData == nil {
		return 0
	}
	BufPtr = C.Star_SRPBinBuf_GetBufPtr(ObjData.BinBuf, 0)
	Size = (C.VS_UINT32)(C.Star_SRPBinBuf_GetOffset(ObjData.BinBuf))
	if BufPtr == nil || (C.VS_INT32)(Offset) >= (C.VS_INT32)(Size) {
		return 0
	}
	if Offset+Length > (int)(Size) {
		Length = (int)(Size) - Offset
	}
	C.memcpy((unsafe.Pointer)(&Buf[0]), C.stargo_MovePointer((unsafe.Pointer)(BufPtr), (C.VS_INT32)(Offset)), (C.size_t)(Length))
	return Length
}

func (self *StarBinBuf) Write(Offset int, Buf []byte, Length int) int {
	var ObjData *StarBinBufBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = StarBinBufClass_getstarcoredata(self)
	if ObjData == nil {
		return 0
	}
	C.Star_SRPBinBuf_FromRaw(ObjData.BinBuf, C.VS_TRUE)
	if Length == 0 {
		return 0
	}
	if C.Star_SRPBinBuf_Set(ObjData.BinBuf, (C.VS_UINT32)(Offset), (C.VS_UINT32)(Length), (*C.VS_INT8)((unsafe.Pointer)(&Buf[0]))) == C.VS_FALSE {
		return 0
	}
	return Length
}

func (self *StarBinBuf) Free() {
	var ObjData *StarBinBufBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	ObjData = StarBinBufClass_getstarcoredata(self)
	if ObjData == nil {
		return
	}
	DeleteGoObjectAllRef(ObjData.RefItem)

	_TermObject_Defer(ObjData)
	return
}

func (self *StarBinBuf) ReleaseOwner() {
	var fdata *StarBinBufBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	fdata = StarBinBufClass_getstarcoredata(self)
	if fdata == nil {
		return
	}
	if fdata.IsClearedByStarCore == C.VS_FALSE {
		if fdata.FreeFlag == C.VS_TRUE && fdata.BinBuf != nil {
			if C.StarGo_ModuleInitFlag == C.VS_TRUE {
				C.Star_SRPBinBuf_ReleaseOwner(fdata.BinBuf)
			}
		}
		fdata.IsClearedByStarCore = C.VS_TRUE
	}
	if C.StarGo_ModuleInitFlag == C.VS_TRUE && C.StarGo_SRPControlInterface != nil && fdata.RefItem != 0 {
		C.Star_SRPControl_UnRegScriptObject(C.StarGo_SRPControlInterface, (C.VS_UWORD)(fdata.RefItem), (unsafe.Pointer)(C.stargo_FreeScriptObject), 0)
	}
	return
}

func (self *StarBinBuf) Dispose() {
	self.Free()
}

/*------------------------------------------------------------------------------------------------*/
/* StarSXml */
/*------------------------------------------------------------------------------------------------*/
func (self *StarSXml) LoadFromFile(In_FileName string) []interface{} {
	var ObjData *StarSXmlBody
	var FileName *C.VS_CHAR
	var ErrorInfo *C.VS_CHAR
	var Result C.VS_BOOL
	var RetResult []interface{}

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return nil
	}
	FileName = SRPGoGetStr(In_FileName, true)
	Result = C.Star_SRPSXML_LoadFromFile(ObjData.SXml, FileName, (**C.VS_CHAR)(&ErrorInfo))
	RetResult = make([]interface{}, 2)
	if Result == C.VS_TRUE {
		RetResult[0] = true
		RetResult[1] = ""
	} else {
		if ErrorInfo != nil {
			RetResult[0] = false
			RetResult[1] = SRPGoSetStr(ErrorInfo, true)
		} else {
			RetResult[0] = false
			RetResult[1] = ""
		}
	}
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(FileName))
	return RetResult
}

func (self *StarSXml) LoadFromBuf(BinBuf *StarBinBuf) []interface{} {
	var ObjData *StarSXmlBody
	var ErrorInfo *C.VS_CHAR
	var LocalBinBuf unsafe.Pointer
	var Result C.VS_BOOL
	var RetResult []interface{}

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return nil
	}
	RetResult = make([]interface{}, 2)
	LocalBinBuf = GoObjectToBinBuf(BinBuf)
	if LocalBinBuf == nil {
		RetResult[0] = false
		RetResult[1] = ""
		return RetResult
	}
	Result = C.Star_SRPSXML_LoadFromBuf(ObjData.SXml, C.Star_SRPBinBuf_GetBuf(LocalBinBuf), (**C.VS_CHAR)(&ErrorInfo))
	if Result == C.VS_TRUE {
		RetResult[0] = true
		RetResult[1] = ""
	} else {
		if ErrorInfo != nil {
			RetResult[0] = false
			RetResult[1] = SRPGoSetStr(ErrorInfo, true)
		} else {
			RetResult[0] = false
			RetResult[1] = ""
		}
	}
	return RetResult
}

func (self *StarSXml) LoadFromBufEx(UtfArg string) []interface{} {
	var ObjData *StarSXmlBody
	var Info *C.VS_CHAR
	var ErrorInfo *C.VS_CHAR
	var Result C.VS_BOOL
	var RetResult []interface{}

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return nil
	}
	Info = SRPGoGetStr(UtfArg, false)
	Result = C.Star_SRPSXML_LoadFromBuf(ObjData.SXml, Info, (**C.VS_CHAR)(&ErrorInfo))
	RetResult = make([]interface{}, 2)
	if Result == C.VS_TRUE {
		RetResult[0] = true
		RetResult[1] = ""
	} else {
		if ErrorInfo != nil {
			RetResult[0] = false
			RetResult[1] = SRPGoSetStr(ErrorInfo, true)
		} else {
			RetResult[0] = false
			RetResult[1] = ""
		}
	}
	STARGO_SAFERELEASESTR(UtfArg, Info)
	return RetResult
}

func (self *StarSXml) SaveToFile(In_FileName string) bool {
	var ObjData *StarSXmlBody
	var FileName *C.VS_CHAR
	var Result C.VS_BOOL

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return false
	}
	FileName = SRPGoGetStr(In_FileName, true)
	Result = C.Star_SRPSXML_SaveToFile(ObjData.SXml, FileName)
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(FileName))
	return FROMVS_BOOL(Result)
}

func (self *StarSXml) SaveToBuf(BinBuf *StarBinBuf) bool {
	var ObjData *StarSXmlBody
	var LocalBinBuf unsafe.Pointer
	var Result C.VS_BOOL

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return false
	}
	LocalBinBuf = GoObjectToBinBuf(BinBuf)
	if LocalBinBuf == nil {
		return false
	}
	Result = C.Star_SRPSXML_SaveToBuf(ObjData.SXml, LocalBinBuf)
	return FROMVS_BOOL(Result)
}

func (self *StarSXml) GetStandalone() string {
	var ObjData *StarSXmlBody
	var CharPtr *C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return ""
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return ""
	}
	CharPtr = C.Star_SRPSXML_GetStandalone(ObjData.SXml)
	if CharPtr != nil {
		return SRPGoSetStr(CharPtr, false)
	} else {
		return ""
	}
}

func (self *StarSXml) GetVersion() string {
	var ObjData *StarSXmlBody
	var CharPtr *C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return ""
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return ""
	}
	CharPtr = C.Star_SRPSXML_GetVersion(ObjData.SXml)
	if CharPtr != nil {
		return SRPGoSetStr(CharPtr, false)
	} else {
		return ""
	}
}

func (self *StarSXml) GetEncoding() string {
	var ObjData *StarSXmlBody
	var CharPtr *C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return ""
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return ""
	}
	CharPtr = C.Star_SRPSXML_GetEncoding(ObjData.SXml)
	if CharPtr != nil {
		return SRPGoSetStr(CharPtr, false)
	} else {
		return ""
	}
}

func (self *StarSXml) FindElement(Value string) int64 {
	var ObjData *StarSXmlBody
	var Name *C.VS_CHAR
	var RetValue unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return 0
	}
	Name = SRPGoGetStr(Value, true)
	RetValue = C.Star_SRPSXML_FindElement(ObjData.SXml, Name)
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(Name))
	if RetValue == nil {
		return 0
	} else {
		return (int64)(C.stargo_PointerToInt64(RetValue))
	}
}

func (self *StarSXml) FindElementEx(ParentElement int64, Value string) int64 {
	var ObjData *StarSXmlBody
	var Name *C.VS_CHAR
	var RetValue unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return 0
	}
	Name = SRPGoGetStr(Value, true)
	RetValue = C.Star_SRPSXML_FindElementEx(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(ParentElement)), Name)
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(Name))
	if RetValue == nil {
		return 0
	} else {
		return (int64)(C.stargo_PointerToInt64(RetValue))
	}
}

func (self *StarSXml) FirstElement(ParentElement int64) int64 {
	var ObjData *StarSXmlBody
	var RetValue unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return 0
	}
	RetValue = C.Star_SRPSXML_FirstElement(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(ParentElement)))
	if RetValue == nil {
		return 0
	} else {
		return (int64)(C.stargo_PointerToInt64(RetValue))
	}
}

func (self *StarSXml) NextElement(Element int64) int64 {
	var ObjData *StarSXmlBody
	var RetValue unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return 0
	}
	RetValue = C.Star_SRPSXML_NextElement(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(Element)))
	if RetValue == nil {
		return 0
	} else {
		return (int64)(C.stargo_PointerToInt64(RetValue))
	}
}

func (self *StarSXml) ParentElement(Element int64) int64 {
	var ObjData *StarSXmlBody
	var RetValue unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return 0
	}
	RetValue = C.Star_SRPSXML_ParentElement(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(Element)))
	if RetValue == nil {
		return 0
	} else {
		return (int64)(C.stargo_PointerToInt64(RetValue))
	}
}

func (self *StarSXml) GetElement(Element int64) string {
	var ObjData *StarSXmlBody
	var Value *C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return ""
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return ""
	}
	Value = C.Star_SRPSXML_GetElement(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(Element)))
	if Value == nil {
		return ""
	} else {
		return SRPGoSetStr(Value, true)
	}
}

func (self *StarSXml) GetElementEx(Element int64) string {
	var ObjData *StarSXmlBody
	var Buf [512]C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return ""
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return ""
	}
	C.Star_SRPSXML_GetElementEx(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(Element)), (*C.VS_CHAR)(&Buf[0]), 512)
	return SRPGoSetStr((*C.VS_CHAR)(&Buf[0]), true)
}

func (self *StarSXml) GetNs(Element int64) []interface{} {
	var ObjData *StarSXmlBody
	var Name [128]C.VS_CHAR
	var Value *C.VS_CHAR
	var RetResult []interface{}

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return nil
	}
	RetResult = make([]interface{}, 3)
	if C.Star_SRPSXML_GetNs(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(Element)), (*C.VS_CHAR)(&Name[0]), 128, (**C.VS_CHAR)(&Value)) == C.VS_FALSE {
		RetResult[0] = false
		RetResult[1] = ""
		RetResult[2] = ""
		return RetResult
	}
	if Value == nil {
		RetResult[0] = true
		RetResult[1] = SRPGoSetStr((*C.VS_CHAR)(&Name[0]), true)
		RetResult[2] = ""
	} else {
		RetResult[0] = true
		RetResult[1] = SRPGoSetStr((*C.VS_CHAR)(&Name[0]), true)
		RetResult[2] = SRPGoSetStr(Value, true)
	}
	return RetResult
}

func (self *StarSXml) GetNsValue(Element int64, nsName string) string {
	var ObjData *StarSXmlBody
	var Name *C.VS_CHAR
	var Value *C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return ""
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return ""
	}
	Name = SRPGoGetStr(nsName, true)
	Value = C.Star_SRPSXML_GetNsValue(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(Element)), Name)
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(Name))
	if Value == nil {
		return ""
	} else {
		return SRPGoSetStr(Value, true)
	}
}

func (self *StarSXml) FindAttribute(Element int64, In_Name string) int64 {
	var ObjData *StarSXmlBody
	var Value *C.VS_CHAR
	var RetValue unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return 0
	}
	Value = SRPGoGetStr(In_Name, true)
	RetValue = C.Star_SRPSXML_FindAttribute(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(Element)), Value)
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(Value))
	if RetValue == nil {
		return 0
	} else {
		return (int64)(C.stargo_PointerToInt64(RetValue))
	}
}

func (self *StarSXml) FirstAttribute(Element int64) int64 {
	var ObjData *StarSXmlBody
	var RetValue unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return 0
	}
	RetValue = C.Star_SRPSXML_FirstAttribute(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(Element)))
	if RetValue == nil {
		return 0
	} else {
		return (int64)(C.stargo_PointerToInt64(RetValue))
	}
}

func (self *StarSXml) NextAttribute(Attribute int64) int64 {
	var ObjData *StarSXmlBody
	var RetValue unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return 0
	}
	RetValue = C.Star_SRPSXML_NextAttribute(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(Attribute)))
	if RetValue == nil {
		return 0
	} else {
		return (int64)(C.stargo_PointerToInt64(RetValue))
	}
}

func (self *StarSXml) GetAttributeName(Attribute int64) string {
	var ObjData *StarSXmlBody
	var Value *C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return ""
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return ""
	}
	Value = C.Star_SRPSXML_GetAttributeName(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(Attribute)))
	if Value == nil {
		return ""
	} else {
		return SRPGoSetStr(Value, true)
	}
}

func (self *StarSXml) GetAttributeValue(Attribute int64) string {
	var ObjData *StarSXmlBody
	var Value *C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return ""
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return ""
	}
	Value = C.Star_SRPSXML_GetAttributeValue(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(Attribute)))
	if Value == nil {
		return ""
	} else {
		return SRPGoSetStr(Value, true)
	}
}

func (self *StarSXml) GetSingleText(Element int64) string {
	var ObjData *StarSXmlBody
	var Value *C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return ""
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return ""
	}
	Value = C.Star_SRPSXML_GetSingleText(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(Element)))
	if Value == nil {
		return ""
	} else {
		return SRPGoSetStr(Value, true)
	}
}

func (self *StarSXml) FirstText(Element int64) int64 {
	var ObjData *StarSXmlBody
	var RetValue unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return 0
	}
	RetValue = C.Star_SRPSXML_FirstText(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(Element)))
	if RetValue == nil {
		return 0
	} else {
		return (int64)(C.stargo_PointerToInt64(RetValue))
	}
}

func (self *StarSXml) NextText(Text int64) int64 {
	var ObjData *StarSXmlBody
	var RetValue unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return 0
	}
	RetValue = C.Star_SRPSXML_NextText(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(Text)))
	if RetValue == nil {
		return 0
	} else {
		return (int64)(C.stargo_PointerToInt64(RetValue))
	}
}

func (self *StarSXml) GetText(Text int64) string {
	var ObjData *StarSXmlBody
	var Value *C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return ""
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return ""
	}
	Value = C.Star_SRPSXML_GetText(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(Text)))
	if Value == nil {
		return ""
	} else {
		return SRPGoSetStr(Value, true)
	}
}

func (self *StarSXml) SetDeclaration(In_Version string, In_Encoding string, In_Standalone string) {
	var ObjData *StarSXmlBody
	var Version *C.VS_CHAR
	var Encoding *C.VS_CHAR
	var Standalone *C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return
	}
	Version = SRPGoGetStr(In_Version, false)
	Encoding = SRPGoGetStr(In_Encoding, false)
	Standalone = SRPGoGetStr(In_Standalone, false)
	C.Star_SRPSXML_SetDeclaration(ObjData.SXml, Version, Encoding, Standalone)
	STARGO_SAFERELEASESTR(In_Version, Version)
	STARGO_SAFERELEASESTR(In_Encoding, Encoding)
	STARGO_SAFERELEASESTR(In_Standalone, Standalone)
	return
}

func (self *StarSXml) RemoveDeclaration() {
	var ObjData *StarSXmlBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return
	}
	C.Star_SRPSXML_RemoveDeclaration(ObjData.SXml)
	return
}

func (self *StarSXml) InsertElementBefore(ParentElement int64, Element int64, In_Value string) int64 {
	var ObjData *StarSXmlBody
	var InPtr unsafe.Pointer
	var InPtr2 unsafe.Pointer
	var Value *C.VS_CHAR
	var RetValue unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return 0
	}
	InPtr = C.stargo_ToPointer64((C.VS_INT64)(ParentElement))
	InPtr2 = C.stargo_ToPointer64((C.VS_INT64)(Element))
	Value = SRPGoGetStr(In_Value, true)
	RetValue = C.Star_SRPSXML_InsertElementBefore(ObjData.SXml, InPtr, InPtr2, Value)
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(Value))
	if RetValue == nil {
		return 0
	} else {
		return (int64)(C.stargo_PointerToInt64(RetValue))
	}
}

func (self *StarSXml) InsertElementAfter(ParentElement int64, Element int64, In_Value string) int64 {
	var ObjData *StarSXmlBody
	var InPtr unsafe.Pointer
	var InPtr2 unsafe.Pointer
	var Value *C.VS_CHAR
	var RetValue unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return 0
	}
	InPtr = C.stargo_ToPointer64((C.VS_INT64)(ParentElement))
	InPtr2 = C.stargo_ToPointer64((C.VS_INT64)(Element))
	Value = SRPGoGetStr(In_Value, true)
	RetValue = C.Star_SRPSXML_InsertElementAfter(ObjData.SXml, InPtr, InPtr2, Value)
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(Value))
	if RetValue == nil {
		return 0
	} else {
		return (int64)(C.stargo_PointerToInt64(RetValue))
	}
}

func (self *StarSXml) RemoveElement(Element int64) {
	var ObjData *StarSXmlBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return
	}
	C.Star_SRPSXML_RemoveElement(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(Element)))
	return
}

func (self *StarSXml) SetElement(Element int64, In_Value string) {
	var ObjData *StarSXmlBody
	var Value *C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return
	}
	Value = SRPGoGetStr(In_Value, true)
	C.Star_SRPSXML_SetElement(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(Element)), Value)
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(Value))
	return
}

func (self *StarSXml) SetNs(Element int64, nsName string, nsValue string) {
	var ObjData *StarSXmlBody
	var Name *C.VS_CHAR
	var Value *C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return
	}
	Name = SRPGoGetStr(nsName, true)
	Value = SRPGoGetStr(nsValue, true)
	C.Star_SRPSXML_SetNs(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(Element)), Name, Value)
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(Name))
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(Value))
	return
}

func (self *StarSXml) InsertTextBefore(ParentElement int64, Text int64, In_Value string, CDataFlag bool) int64 {
	var ObjData *StarSXmlBody
	var Value *C.VS_CHAR
	var RetValue unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return 0
	}
	Value = SRPGoGetStr(In_Value, true)
	RetValue = C.Star_SRPSXML_InsertTextBefore(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(ParentElement)), C.stargo_ToPointer64((C.VS_INT64)(Text)), Value, TOVS_BOOL(CDataFlag))
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(Value))
	if RetValue == nil {
		return 0
	} else {
		return (int64)(C.stargo_PointerToInt64(RetValue))
	}
}

func (self *StarSXml) InsertTextAfter(ParentElement int64, Text int64, In_Value string, CDataFlag bool) int64 {
	var ObjData *StarSXmlBody
	var Value *C.VS_CHAR
	var RetValue unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return 0
	}
	Value = SRPGoGetStr(In_Value, true)
	RetValue = C.Star_SRPSXML_InsertTextAfter(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(ParentElement)), C.stargo_ToPointer64((C.VS_INT64)(Text)), Value, TOVS_BOOL(CDataFlag))
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(Value))
	if RetValue == nil {
		return 0
	} else {
		return (int64)(C.stargo_PointerToInt64(RetValue))
	}
}

func (self *StarSXml) RemoveText(Text int64) {
	var ObjData *StarSXmlBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return
	}
	C.Star_SRPSXML_RemoveText(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(Text)))
	return
}

func (self *StarSXml) SetText(Text int64, In_Value string, CDataFlag bool) {
	var ObjData *StarSXmlBody
	var Value *C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return
	}
	Value = SRPGoGetStr(In_Value, true)
	C.Star_SRPSXML_SetText(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(Text)), Value, TOVS_BOOL(CDataFlag))
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(Value))
	return
}

func (self *StarSXml) InsertCommentBefore(ParentElement int64, Comment int64, In_Value string) int64 {
	var ObjData *StarSXmlBody
	var Value *C.VS_CHAR
	var RetValue unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return 0
	}
	Value = SRPGoGetStr(In_Value, true)
	RetValue = C.Star_SRPSXML_InsertCommentBefore(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(ParentElement)), C.stargo_ToPointer64((C.VS_INT64)(Comment)), Value)
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(Value))
	if RetValue == nil {
		return 0
	} else {
		return (int64)(C.stargo_PointerToInt64(RetValue))
	}
}

func (self *StarSXml) InsertCommentAfter(ParentElement int64, Comment int64, In_Value string) int64 {
	var ObjData *StarSXmlBody
	var Value *C.VS_CHAR
	var RetValue unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return 0
	}
	Value = SRPGoGetStr(In_Value, true)
	RetValue = C.Star_SRPSXML_InsertCommentAfter(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(ParentElement)), C.stargo_ToPointer64((C.VS_INT64)(Comment)), Value)
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(Value))
	if RetValue == nil {
		return 0
	} else {
		return (int64)(C.stargo_PointerToInt64(RetValue))
	}
}

func (self *StarSXml) RemoveComment(Comment int64) {
	var ObjData *StarSXmlBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return
	}
	C.Star_SRPSXML_RemoveComment(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(Comment)))
	return
}

func (self *StarSXml) SetComment(Comment int64, In_Value string) {
	var ObjData *StarSXmlBody
	var Value *C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return
	}
	Value = SRPGoGetStr(In_Value, true)
	C.Star_SRPSXML_SetComment(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(Comment)), Value)
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(Value))
	return
}

func (self *StarSXml) SetAttribute(Element int64, In_Name string, In_Value string) {
	var ObjData *StarSXmlBody
	var Name *C.VS_CHAR
	var Value *C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return
	}
	Name = SRPGoGetStr(In_Name, true)
	Value = SRPGoGetStr(In_Value, true)
	C.Star_SRPSXML_SetAttribute(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(Element)), Name, Value)
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(Name))
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(Value))
	return
}

func (self *StarSXml) RemoveAttribute(Element int64, In_Name string) {
	var ObjData *StarSXmlBody
	var Name *C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return
	}
	Name = SRPGoGetStr(In_Name, true)
	C.Star_SRPSXML_RemoveAttribute(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(Element)), Name)
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(Name))
	return
}

func (self *StarSXml) CopyElementBefore(ParentElement int64, Element int64, SrcElement int64) int64 {
	var ObjData *StarSXmlBody
	var RetValue unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return 0
	}
	RetValue = C.Star_SRPSXML_CopyElementBefore(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(ParentElement)), C.stargo_ToPointer64((C.VS_INT64)(Element)), C.stargo_ToPointer64((C.VS_INT64)(SrcElement)))
	if RetValue == nil {
		return 0
	} else {
		return (int64)(C.stargo_PointerToInt64(RetValue))
	}
}

func (self *StarSXml) CopyElementAfter(ParentElement int64, Element int64, SrcElement int64) int64 {
	var ObjData *StarSXmlBody
	var RetValue unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return 0
	}
	RetValue = C.Star_SRPSXML_CopyElementAfter(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(ParentElement)), C.stargo_ToPointer64((C.VS_INT64)(Element)), C.stargo_ToPointer64((C.VS_INT64)(SrcElement)))
	if RetValue == nil {
		return 0
	} else {
		return (int64)(C.stargo_PointerToInt64(RetValue))
	}
}

func (self *StarSXml) CopyChild(DesElement int64, SrcElement int64) bool {
	var ObjData *StarSXmlBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	if ObjData == nil {
		return false
	}
	return FROMVS_BOOL(C.Star_SRPSXML_CopyChild(ObjData.SXml, C.stargo_ToPointer64((C.VS_INT64)(DesElement)), C.stargo_ToPointer64((C.VS_INT64)(SrcElement))))
}

func (self *StarSXml) Dup(SrcSXML *StarSXml) bool {
	var ObjData *StarSXmlBody
	var ObjData1 *StarSXmlBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	ObjData1 = StarSXmlClass_getstarcoredata(SrcSXML)
	if ObjData == nil || ObjData1 == nil {
		return false
	}
	return FROMVS_BOOL(C.Star_SRPSXML_Copy(ObjData.SXml, ObjData1.SXml))
}

func (self *StarSXml) Free() {
	var ObjData *StarSXmlBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	ObjData = StarSXmlClass_getstarcoredata(self)
	DeleteGoObjectAllRef(ObjData.RefItem)

	_TermObject_Defer(ObjData)
	return
}

func (self *StarSXml) ReleaseOwner() {
	var fdata *StarSXmlBody

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	fdata = StarSXmlClass_getstarcoredata(self)
	if fdata.IsClearedByStarCore == C.VS_FALSE {
		if fdata.FreeFlag == C.VS_TRUE && fdata.SXml != nil {
			if C.StarGo_ModuleInitFlag == C.VS_TRUE {
				C.Star_SRPSXML_ReleaseOwner(fdata.SXml)
			}
		}
		fdata.IsClearedByStarCore = C.VS_TRUE
	}
	if C.StarGo_ModuleInitFlag == C.VS_TRUE && C.StarGo_SRPControlInterface != nil && fdata.RefItem != 0 {
		C.Star_SRPControl_UnRegScriptObject(C.StarGo_SRPControlInterface, fdata.RefItem, (unsafe.Pointer)(C.stargo_FreeScriptObject), 0)
	}
	return
}

func (self *StarSXml) Dispose() {
	self.Free()
}

/*------------------------------------------------------------------------------------------------*/
/* StarObject */
/*------------------------------------------------------------------------------------------------*/
type ClassRawContextRefManager struct {
}

var g_GoRawContextRefManager *ClassRawContextRefManager = nil
var g_ClassRawContextRefManager_Root *C.struct_classRawContextRefItem = nil

func (*ClassRawContextRefManager) Alloc(o interface{}, ThisObject unsafe.Pointer, SRPInterface unsafe.Pointer, IsClass C.VS_BOOL) *C.struct_classRawContextRefItem {
	var RefItem *C.struct_classRawContextRefItem

	RefItem = (*C.struct_classRawContextRefItem)(C.stargo_MallocclassRawContextRefItem())
	RefItem.o = NewGoObjectRefStrong(o, 0)
	RefItem.IsClass = IsClass
	C.Star_SRPI_GetID(SRPInterface, ThisObject, &RefItem.ObjectID)
	RefItem.Up = nil
	RefItem.Down = nil
	if g_ClassRawContextRefManager_Root == nil {
		g_ClassRawContextRefManager_Root = RefItem
	} else {
		g_ClassRawContextRefManager_Root.Up = RefItem
		RefItem.Down = g_ClassRawContextRefManager_Root
		g_ClassRawContextRefManager_Root = RefItem
	}
	return RefItem
}

func (*ClassRawContextRefManager) GetObject(o interface{}, SRPInterface unsafe.Pointer, IsClass C.VS_BOOL) unsafe.Pointer {
	var NewObject unsafe.Pointer
	var RefItem *C.struct_classRawContextRefItem
	var ObjectTemp interface{}

	RefItem = g_ClassRawContextRefManager_Root
	for {
		if RefItem == nil {
			break
		}
		ObjectTemp = RefToGoObject(RefItem.o)
		if ObjectTemp == o && RefItem.IsClass == IsClass {
			NewObject = C.Star_SRPI_GetObject(SRPInterface, &RefItem.ObjectID)
			if NewObject == nil {
				break //--create new one
			}
			C.Star_SRPI_AddRefEx(SRPInterface, NewObject)
			return NewObject
		}
		RefItem = RefItem.Down
	}
	//----create new object
	NewObject = C.Star_SRPI_MallocObjectL(SRPInterface, (*C.VS_UUID)(C.NULL), 0, C.NULL)
	VSScript_GoRawContext_WrapObject(SRPInterface, C.Star_SRPI_GetServiceGroupID(SRPInterface), NewObject, o, IsClass)
	return NewObject
}

func (*ClassRawContextRefManager) Free(Item *C.struct_classRawContextRefItem) {
	if Item == nil {
		return
	}
	if Item.Up == nil {
		g_ClassRawContextRefManager_Root = Item.Down
	} else {
		Item.Up.Down = Item.Down
	}
	if Item.Down != nil {
		Item.Down.Up = Item.Up
	}
	DeleteGoObjectAllRef(Item.o)
	C.free((unsafe.Pointer)(Item))
}

func VSScript_GoRawContextRefManager_Init() {
	g_GoRawContextRefManager = new(ClassRawContextRefManager)
}

func VSScript_GoRawContextRefManager_Term() {
	g_GoRawContextRefManager = nil
}

func VSScript_GoRawContext_WrapObject_Get(SRPInterface unsafe.Pointer, ServiceGroupIndex C.VS_ULONG, o interface{}, IsClass bool) unsafe.Pointer {
	return nil
}

func VSScript_GoRawContext_GetRawObjectEx(BasicSRPInterface unsafe.Pointer, ThisObject unsafe.Pointer) *StarObject {
	return nil
}

func LuaTableToGo(ExpectedType int, SRPInterface unsafe.Pointer, Index C.VS_INT32) interface{} {
	var RetVal []interface{}
	var Val interface{}
	var IntTemp, Size C.VS_INT32

	if Index < 0 {
		Index = Index - 1
	}
	Size = 0
	C.Star_SRPI_LuaPushNil(SRPInterface)
	for {
		if C.Star_SRPI_LuaNext(SRPInterface, Index) == 0 {
			break
		}
		switch C.Star_SRPI_LuaType(SRPInterface, -2) {
		case C.VSLUATYPE_INT:
		case C.VSLUATYPE_INT64:
		case C.VSLUATYPE_UWORD:
		case C.VSLUATYPE_NUMBER:
			IntTemp = C.Star_SRPI_LuaToInt(SRPInterface, -2)
			if IntTemp > 0 {
				if IntTemp > Size {
					Size = IntTemp
				}
			} else {
				C.Star_SRPI_LuaPop(SRPInterface, 2)
				return nil
			}
			break
		default:
			C.Star_SRPI_LuaPop(SRPInterface, 2)
			return nil
		}
		C.Star_SRPI_LuaPop(SRPInterface, 1)
	}
	RetVal = make([]interface{}, Size)
	C.Star_SRPI_LuaPushNil(SRPInterface)
	for {
		if C.Star_SRPI_LuaNext(SRPInterface, Index) == 0 {
			break
		}
		switch C.Star_SRPI_LuaType(SRPInterface, -2) {
		case C.VSLUATYPE_INT:
		case C.VSLUATYPE_INT64:
		case C.VSLUATYPE_UWORD:
		case C.VSLUATYPE_NUMBER:
			IntTemp = C.Star_SRPI_LuaToInt(SRPInterface, -2)
			if IntTemp > 0 && IntTemp <= Size {
				var Result C.VS_BOOL
				Val = LuaToGoObject(ExpectedType, SRPInterface, -1, &Result)
				if Result == C.VS_FALSE {
					C.Star_SRPI_LuaPop(SRPInterface, 2)
					return nil
				}
				RetVal[IntTemp-1] = Val
			} else {
				C.Star_SRPI_LuaPop(SRPInterface, 2)
				return nil
			}
		default:
			C.Star_SRPI_LuaPop(SRPInterface, 2)
			return nil
		}
		C.Star_SRPI_LuaPop(SRPInterface, 1)
	}
	return RetVal
}

func GoToLuaTable(SRPInterface unsafe.Pointer, arr_data []interface{}, ToRaw C.VS_BOOL) {
	var num_index C.VS_INT32
	var localobject interface{}

	C.Star_SRPI_LuaNewTable(SRPInterface)
	for num_index = (C.VS_INT32)(0); num_index < (C.VS_INT32)(len(arr_data)); num_index++ {
		C.Star_SRPI_LuaPushInt(SRPInterface, num_index+1)
		localobject = arr_data[num_index]
		GoObjectToLua(SRPInterface, localobject, FROMVS_BOOL(ToRaw))
		if C.Star_SRPI_LuaIsNil(SRPInterface, -1) == C.VS_TRUE {
			C.Star_SRPI_LuaPop(SRPInterface, 3)
			C.Star_SRPI_LuaPushNil(SRPInterface)
			return
		}
		C.Star_SRPI_LuaSetTable(SRPInterface, -3)
	}
	return
}

func GoObjectToLua(SRPInterface unsafe.Pointer, Object interface{}, ToRaw bool) bool {
	switch Object.(type) {
	case bool:
		C.Star_SRPI_LuaPushBool(SRPInterface, TOVS_BOOL(Object.(bool)))
	case int8:
		C.Star_SRPI_LuaPushInt(SRPInterface, (C.VS_INT32)(Object.(int8)))
	case int16:
		C.Star_SRPI_LuaPushInt(SRPInterface, (C.VS_INT32)(Object.(int16)))
	case int32:
		C.Star_SRPI_LuaPushInt(SRPInterface, (C.VS_INT32)(Object.(int32)))
	case int64:
		C.Star_SRPI_LuaPushInt64(SRPInterface, (C.VS_INT64)(Object.(int64)))
	case int:
		switch unsafe.Sizeof(int(0)) {
		case 4:
			C.Star_SRPI_LuaPushInt(SRPInterface, (C.VS_INT32)(Object.(int)))
		case 8:
			C.Star_SRPI_LuaPushInt64(SRPInterface, (C.VS_INT64)(Object.(int)))
		}
	case uint8:
		C.Star_SRPI_LuaPushInt(SRPInterface, (C.VS_INT32)((C.VS_UINT32)(Object.(uint8))))
	case uint16:
		C.Star_SRPI_LuaPushInt(SRPInterface, (C.VS_INT32)((C.VS_UINT32)(Object.(uint16))))
	case uint32:
		C.Star_SRPI_LuaPushInt(SRPInterface, (C.VS_INT32)((C.VS_UINT32)(Object.(uint32))))
	case uint64:
		C.Star_SRPI_LuaPushInt64(SRPInterface, (C.VS_INT64)((C.VS_UINT64)(Object.(uint64))))
	case uint:
		switch unsafe.Sizeof(uint(0)) {
		case 4:
			C.Star_SRPI_LuaPushInt(SRPInterface, (C.VS_INT32)((C.VS_UINT32)(Object.(int))))
		case 8:
			C.Star_SRPI_LuaPushInt64(SRPInterface, (C.VS_INT64)((C.VS_UINT64)(Object.(int))))
		}
	case float32:
		C.Star_SRPI_LuaPushNumber(SRPInterface, (C.VS_DOUBLE)((C.VS_FLOAT)(Object.(float32))))
	case float64:
		C.Star_SRPI_LuaPushNumber(SRPInterface, (C.VS_DOUBLE)((C.VS_DOUBLE)(Object.(float64))))
	case string:
		var CharPtr *C.VS_CHAR
		var StrLen C.VS_INT32

		vt := Object.(string)
		CharPtr = SRPGoGetStrEx(vt, &StrLen, true)
		C.Star_SRPI_LuaPushLString(SRPInterface, CharPtr, (C.VS_UINT32)(StrLen))
		C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(CharPtr))
	case *StarParaPkg:
		var NewParaPkg unsafe.Pointer
		NewParaPkg = GoObjectToParaPkg(Object.(*StarParaPkg))
		if NewParaPkg != nil {
			C.Star_SRPI_LuaPushParaPkg(SRPInterface, NewParaPkg, C.VS_FALSE)
		} else {
			C.Star_SRPI_LuaPushNil(SRPInterface)
			return true
		}
	case *StarBinBuf:
		var SRPBinBufInterface unsafe.Pointer
		SRPBinBufInterface = GoObjectToBinBuf(Object.(*StarBinBuf))
		if SRPBinBufInterface != nil {
			C.Star_SRPI_LuaPushBinBuf(SRPInterface, SRPBinBufInterface, C.VS_FALSE)
		} else {
			C.Star_SRPI_LuaPushNil(SRPInterface)
			return true
		}
	case *StarSXml:
		var SRPSXmlInterface unsafe.Pointer
		SRPSXmlInterface = GoObjectToSXml(Object.(*StarSXml))
		if SRPSXmlInterface != nil {
			C.Star_SRPI_LuaPushSXml(SRPInterface, SRPSXmlInterface, C.VS_FALSE)
		} else {
			C.Star_SRPI_LuaPushNil(SRPInterface)
			return true
		}
	case *StarObject:
		SRPObject := GoObjectToSRPObject(Object.(*StarObject))
		C.Star_SRPI_LuaPushObject(SRPInterface, SRPObject)
	case []string:
		val := Object.([]string)
		s := make([]interface{}, len(val))
		for i, v := range val {
			s[i] = v
		}
		var NewParaPkg unsafe.Pointer
		var BasicSRPInterface unsafe.Pointer

		BasicSRPInterface = C.Star_SRPI_GetBasicInterface(SRPInterface)
		NewParaPkg = C.Star_SRPI_GetParaPkgInterface(SRPInterface)
		if StarParaPkg_FromTuple_Sub(s, NewParaPkg, BasicSRPInterface, 0, SRPInterface) == false {
			C.Star_SRPParaPkg_Release(NewParaPkg)
			C.Star_SRPI_LuaPushNil(SRPInterface)
			return true
		}
		C.Star_SRPI_LuaPushParaPkg(SRPInterface, NewParaPkg, C.VS_TRUE)
	case []int8:
		var BinBuf unsafe.Pointer
		val := Object.([]int8)
		BinBuf = C.Star_SRPI_GetSRPBinBufInterface(SRPInterface)
		C.Star_SRPBinBuf_Set(BinBuf, 0, (C.VS_UINT32)(len(val)), (*C.VS_INT8)((unsafe.Pointer)(&val[0])))
		C.Star_SRPBinBuf_FromRaw(BinBuf, C.VS_TRUE)
		C.Star_SRPI_LuaPushBinBuf(SRPInterface, BinBuf, C.VS_TRUE)
	case []byte: /*== uint8*/
		var BinBuf unsafe.Pointer
		val := Object.([]byte)
		BinBuf = C.Star_SRPI_GetSRPBinBufInterface(SRPInterface)
		C.Star_SRPBinBuf_Set(BinBuf, 0, (C.VS_UINT32)(len(val)), (*C.VS_INT8)((unsafe.Pointer)(&val[0])))
		C.Star_SRPBinBuf_FromRaw(BinBuf, C.VS_TRUE)
		C.Star_SRPI_LuaPushBinBuf(SRPInterface, BinBuf, C.VS_TRUE)

	case []bool:
		val := Object.([]bool)
		NewParaPkg := C.Star_SRPI_GetParaPkgInterface(SRPInterface)
		for i := 0; i < len(val); i++ {
			C.Star_SRPParaPkg_InsertBool(NewParaPkg, (C.VS_INT32)(i), TOVS_BOOL(val[i]))
		}
		C.Star_SRPI_LuaPushParaPkg(SRPInterface, NewParaPkg, C.VS_TRUE)

	case []int16:
		val := Object.([]int16)
		NewParaPkg := C.Star_SRPI_GetParaPkgInterface(SRPInterface)
		for i := 0; i < len(val); i++ {
			C.Star_SRPParaPkg_InsertInt(NewParaPkg, (C.VS_INT32)(i), (C.VS_INT32)(val[i]))
		}
		C.Star_SRPI_LuaPushParaPkg(SRPInterface, NewParaPkg, C.VS_TRUE)

	case []uint16:
		val := Object.([]uint16)
		NewParaPkg := C.Star_SRPI_GetParaPkgInterface(SRPInterface)
		for i := 0; i < len(val); i++ {
			C.Star_SRPParaPkg_InsertInt(NewParaPkg, (C.VS_INT32)(i), (C.VS_INT32)(val[i]))
		}
		C.Star_SRPI_LuaPushParaPkg(SRPInterface, NewParaPkg, C.VS_TRUE)

	case []int32:
		val := Object.([]int32)
		NewParaPkg := C.Star_SRPI_GetParaPkgInterface(SRPInterface)
		for i := 0; i < len(val); i++ {
			C.Star_SRPParaPkg_InsertInt(NewParaPkg, (C.VS_INT32)(i), (C.VS_INT32)(val[i]))
		}
		C.Star_SRPI_LuaPushParaPkg(SRPInterface, NewParaPkg, C.VS_TRUE)

	case []uint32:
		val := Object.([]uint32)
		NewParaPkg := C.Star_SRPI_GetParaPkgInterface(SRPInterface)
		for i := 0; i < len(val); i++ {
			C.Star_SRPParaPkg_InsertInt(NewParaPkg, (C.VS_INT32)(i), (C.VS_INT32)(val[i]))
		}
		C.Star_SRPI_LuaPushParaPkg(SRPInterface, NewParaPkg, C.VS_TRUE)

	case []int:
		val := Object.([]int)
		NewParaPkg := C.Star_SRPI_GetParaPkgInterface(SRPInterface)
		for i := 0; i < len(val); i++ {
			switch unsafe.Sizeof(uint(0)) {
			case 4:
				C.Star_SRPParaPkg_InsertInt(NewParaPkg, (C.VS_INT32)(i), (C.VS_INT32)(val[i]))
			case 8:
				C.Star_SRPParaPkg_InsertInt64(NewParaPkg, (C.VS_INT32)(i), (C.VS_INT64)(val[i]))
			}
		}
		C.Star_SRPI_LuaPushParaPkg(SRPInterface, NewParaPkg, C.VS_TRUE)

	case []uint:
		val := Object.([]uint)
		NewParaPkg := C.Star_SRPI_GetParaPkgInterface(SRPInterface)
		for i := 0; i < len(val); i++ {
			switch unsafe.Sizeof(uint(0)) {
			case 4:
				C.Star_SRPParaPkg_InsertInt(NewParaPkg, (C.VS_INT32)(i), (C.VS_INT32)(val[i]))
			case 8:
				C.Star_SRPParaPkg_InsertInt64(NewParaPkg, (C.VS_INT32)(i), (C.VS_INT64)(val[i]))
			}
		}
		C.Star_SRPI_LuaPushParaPkg(SRPInterface, NewParaPkg, C.VS_TRUE)

	case []int64:
		val := Object.([]int64)
		NewParaPkg := C.Star_SRPI_GetParaPkgInterface(SRPInterface)
		for i := 0; i < len(val); i++ {
			C.Star_SRPParaPkg_InsertInt64(NewParaPkg, (C.VS_INT32)(i), (C.VS_INT64)(val[i]))
		}
		C.Star_SRPI_LuaPushParaPkg(SRPInterface, NewParaPkg, C.VS_TRUE)

	case []uint64:
		val := Object.([]uint64)
		NewParaPkg := C.Star_SRPI_GetParaPkgInterface(SRPInterface)
		for i := 0; i < len(val); i++ {
			C.Star_SRPParaPkg_InsertInt64(NewParaPkg, (C.VS_INT32)(i), (C.VS_INT64)(val[i]))
		}
		C.Star_SRPI_LuaPushParaPkg(SRPInterface, NewParaPkg, C.VS_TRUE)

	case []float32:
		val := Object.([]float32)
		NewParaPkg := C.Star_SRPI_GetParaPkgInterface(SRPInterface)
		for i := 0; i < len(val); i++ {
			C.Star_SRPParaPkg_InsertFloat(NewParaPkg, (C.VS_INT32)(i), (C.VS_DOUBLE)((C.VS_FLOAT)(val[i])))
		}
		C.Star_SRPI_LuaPushParaPkg(SRPInterface, NewParaPkg, C.VS_TRUE)

	case []float64:
		val := Object.([]float64)
		NewParaPkg := C.Star_SRPI_GetParaPkgInterface(SRPInterface)
		for i := 0; i < len(val); i++ {
			C.Star_SRPParaPkg_InsertFloat(NewParaPkg, (C.VS_INT32)(i), (C.VS_DOUBLE)((C.VS_DOUBLE)(val[i])))
		}
		C.Star_SRPI_LuaPushParaPkg(SRPInterface, NewParaPkg, C.VS_TRUE)

	case []interface{}:
		val := Object.([]interface{})
		var NewParaPkg unsafe.Pointer
		var BasicSRPInterface unsafe.Pointer

		BasicSRPInterface = C.Star_SRPI_GetBasicInterface(SRPInterface)
		NewParaPkg = C.Star_SRPI_GetParaPkgInterface(SRPInterface)
		if StarParaPkg_FromTuple_Sub(val, NewParaPkg, BasicSRPInterface, 0, SRPInterface) == false {
			C.Star_SRPParaPkg_Release(NewParaPkg)
			C.Star_SRPBasic_Release(BasicSRPInterface)
			C.Star_SRPI_LuaPushNil(SRPInterface)
			return true
		}
		C.Star_SRPBasic_Release(BasicSRPInterface)
		C.Star_SRPI_LuaPushParaPkg(SRPInterface, NewParaPkg, C.VS_TRUE)

	case map[string]interface{}:
		val := Object.(map[string]interface{})
		s := make([]interface{}, 1)
		s[0] = val
		var NewParaPkg unsafe.Pointer
		var BasicSRPInterface unsafe.Pointer

		BasicSRPInterface = C.Star_SRPI_GetBasicInterface(SRPInterface)
		NewParaPkg = C.Star_SRPI_GetParaPkgInterface(SRPInterface)
		if StarParaPkg_FromTuple_Sub(s, NewParaPkg, BasicSRPInterface, 0, SRPInterface) == false {
			C.Star_SRPParaPkg_Release(NewParaPkg)
			C.Star_SRPBasic_Release(BasicSRPInterface)
			C.Star_SRPI_LuaPushNil(SRPInterface)
			return true
		}
		C.Star_SRPBasic_Release(BasicSRPInterface)
		C.Star_SRPI_LuaPushParaPkg(SRPInterface, NewParaPkg, C.VS_TRUE)

	case nil:
		C.Star_SRPI_LuaPushNil(SRPInterface)
	default:
		NewSRPObject := g_GoRawContextRefManager.GetObject(Object, SRPInterface, C.VS_FALSE)
		C.Star_SRPI_LuaPushObject(SRPInterface, NewSRPObject)
		C.Star_SRPI_DelRefEx(SRPInterface, NewSRPObject)
		return true
	}
	return true
}

func LuaToGoObject(ExpectedType int, SRPInterface unsafe.Pointer, Index C.VS_INT32, Result *C.VS_BOOL) interface{} {
	var BasicSRPInterface unsafe.Pointer
	var LuaToJavaResult C.VS_BOOL
	var ObjectTemp interface{}

	(*Result) = C.VS_TRUE
	if ExpectedType == 0 {
		switch C.Star_SRPI_LuaType(SRPInterface, Index) {
		case C.VSLUATYPE_INT:
			return (int32)(C.Star_SRPI_LuaToInt(SRPInterface, Index))
		case C.VSLUATYPE_INT64:
			return (int64)(C.Star_SRPI_LuaToInt64(SRPInterface, Index))
		case C.VSLUATYPE_UWORD:
			return (int)(C.Star_SRPI_LuaToUWord(SRPInterface, Index))
		case C.VSLUATYPE_NUMBER:
			return (float64)(C.Star_SRPI_LuaToNumber(SRPInterface, Index))
		case C.VSLUATYPE_BOOL:
			return FROMVS_BOOL(C.Star_SRPI_LuaToBool(SRPInterface, Index))
		case C.VSLUATYPE_STRING:
			{
				var StringBuf *C.VS_CHAR
				var StringSize C.VS_ULONG

				StringBuf = C.Star_SRPI_LuaToLString(SRPInterface, Index, &StringSize)
				if StringBuf != nil {
					var rrr string = SRPGoSetStrEx(StringBuf, (C.VS_INT32)(StringSize), true)
					if len(rrr) != 0 || StringSize == (C.VS_ULONG)(0) { /*--success or empty string--*/
						return rrr
					}
					var Temp []byte = make([]byte, StringSize)
					if StringSize != 0 {
						C.memcpy((unsafe.Pointer)(&Temp[0]), (unsafe.Pointer)(StringBuf), (C.size_t)(StringSize))
					}
					return Temp
				} else {
					return ""
				}
			}
		case C.VSLUATYPE_TABLE:
			if C.Star_SRPI_LuaTableToParaPkg(SRPInterface, Index, C.NULL, C.VS_TRUE) == C.VS_TRUE {
				return LuaTableToGo(ExpectedType, SRPInterface, Index)
			}
		case C.VSLUATYPE_FUNCTION:
		case C.VSLUATYPE_USERDATA:
		case C.VSLUATYPE_LIGHTUSERDATA:
			return ToStarObject(C.Star_SRPI_LuaToRaw(SRPInterface, Index, C.VS_FALSE), SRPInterface, C.VS_TRUE)
		case C.VSLUATYPE_OBJECT:
			return ToStarObject(C.Star_SRPI_LuaToObject(SRPInterface, Index), SRPInterface, C.VS_FALSE)
		case C.VSLUATYPE_PARAPKG:
			return ToStarParaPkg(C.Star_SRPI_LuaToParaPkg(SRPInterface, Index), C.Star_SRPI_GetServiceGroupID(SRPInterface), C.VS_FALSE)
		case C.VSLUATYPE_BINBUF:
			{
				var BinBuf unsafe.Pointer = C.Star_SRPI_LuaToBinBuf(SRPInterface, Index)
				if C.Star_SRPBinBuf_IsFromRaw(BinBuf) == C.VS_FALSE {
					return ToStarBinBuf(C.Star_SRPI_LuaToBinBuf(SRPInterface, Index), C.Star_SRPI_GetServiceGroupID(SRPInterface), C.VS_FALSE)
				} else {
					var StringBuf *C.VS_INT8 = C.Star_SRPBinBuf_GetBuf(BinBuf)
					var StringSize C.VS_INT32 = (C.VS_INT32)(C.Star_SRPBinBuf_GetOffset(BinBuf))
					if StringSize == 0 {
						var Temp []byte = make([]byte, 0)
						return Temp
					} else {
						var Temp []byte = make([]byte, StringSize)
						C.memcpy((unsafe.Pointer)(&Temp[0]), (unsafe.Pointer)(StringBuf), (C.size_t)(StringSize))
						return Temp
					}
				}
			}
		case C.VSLUATYPE_SXML:
			return ToStarSXml(C.Star_SRPI_LuaToSXml(SRPInterface, Index), C.Star_SRPI_GetServiceGroupID(SRPInterface), C.VS_FALSE)
		case C.VSLUATYPE_NIL:
			return nil
		default:
			(*Result) = C.VS_FALSE
			return nil
		}
	} else {
		switch ExpectedType {
		case GO_TYPE_BOOL:
			return FROMVS_BOOL(C.Star_SRPI_LuaToBool(SRPInterface, Index))
		case GO_TYPE_INT8:
			return (int8)(C.Star_SRPI_LuaToInt(SRPInterface, Index))
		case GO_TYPE_UINT8:
			return (uint8)(C.Star_SRPI_LuaToInt(SRPInterface, Index))
		case GO_TYPE_INT16:
			return (int16)(C.Star_SRPI_LuaToInt(SRPInterface, Index))
		case GO_TYPE_UINT16:
			return (uint16)(C.Star_SRPI_LuaToInt(SRPInterface, Index))
		case GO_TYPE_INT32:
			return (int32)(C.Star_SRPI_LuaToInt(SRPInterface, Index))
		case GO_TYPE_UINT32:
			return (uint16)(C.Star_SRPI_LuaToInt(SRPInterface, Index))
		case GO_TYPE_INT:
			return (int)(C.Star_SRPI_LuaToUWord(SRPInterface, Index))
		case GO_TYPE_UINT:
			return (uint)(C.Star_SRPI_LuaToUWord(SRPInterface, Index))
		case GO_TYPE_INT64:
			return (int64)(C.Star_SRPI_LuaToInt64(SRPInterface, Index))
		case GO_TYPE_UINT64:
			return (uint64)(C.Star_SRPI_LuaToInt64(SRPInterface, Index))
		case GO_TYPE_FLOAT32:
			return (float32)(C.Star_SRPI_LuaToNumber(SRPInterface, Index))
		case GO_TYPE_FLOAT64:
			return (float64)(C.Star_SRPI_LuaToNumber(SRPInterface, Index))
		default:
			if C.Star_SRPI_LuaIsObject(SRPInterface, Index) == C.VS_TRUE {
				var ThisGoRawContext *C.struct_StructOfGoRawContext

				if ExpectedType == GO_TYPE_STAROBJECT {
					return ToStarObject(C.Star_SRPI_LuaToObject(SRPInterface, Index), SRPInterface, C.VS_FALSE)
				}
				ThisGoRawContext = (*C.struct_StructOfGoRawContext)(C.Star_SRPI_GetRawContextBuf(SRPInterface, C.Star_SRPI_LuaToObject(SRPInterface, Index), Const_GoString))
				if ThisGoRawContext != nil {
					if ThisGoRawContext.RefItem == nil || ThisGoRawContext.RefItem.o == 0 {
						return nil
					} else {
						return RefToGoObject(ThisGoRawContext.RefItem.o)
					}
				} else {
					return ToStarObject(C.Star_SRPI_LuaToObject(SRPInterface, Index), SRPInterface, C.VS_FALSE)
				}
			} else if C.Star_SRPI_LuaIsParaPkg(SRPInterface, Index) == C.VS_TRUE {
				var ParaPkg unsafe.Pointer

				ParaPkg = C.Star_SRPI_LuaToParaPkg(SRPInterface, Index)
				if C.Star_SRPParaPkg_GetScriptRawType(ParaPkg) == (C.VS_INT32)(0) {
					if ExpectedType == GO_TYPE_STARPARAPKG {
						return ToStarParaPkg(ParaPkg, C.Star_SRPI_GetServiceGroupID(SRPInterface), C.VS_FALSE)
					} else {
						BasicSRPInterface = C.Star_SRPI_GetBasicInterface(SRPInterface)
						SliceTemp := StarParaPkg_ToTuple_Sub(ParaPkg, BasicSRPInterface, 0, C.VS_TRUE)
						C.Star_SRPBasic_Release(BasicSRPInterface)
						if SliceTemp == nil {
							return SliceTemp
						}
						/*--convert to array--*/
						switch ExpectedType {
						case GO_TYPE_BOOL_SLICE:
							RetValue := make([]bool, len(SliceTemp))
							for i := 0; i < len(SliceTemp); i++ {
								if SRPGoToInt(SliceTemp[i], false) != 0 {
									RetValue[i] = true
								} else {
									RetValue[i] = false
								}
							}
							return RetValue
						case GO_TYPE_INT8_SLICE:
							RetValue := make([]int8, len(SliceTemp))
							for i := 0; i < len(SliceTemp); i++ {
								RetValue[i] = (int8)(SRPGoToInt(SliceTemp[i], true))
							}
							return RetValue
						case GO_TYPE_UINT8_SLICE:
							RetValue := make([]uint8, len(SliceTemp))
							for i := 0; i < len(SliceTemp); i++ {
								RetValue[i] = (uint8)(SRPGoToInt(SliceTemp[i], true))
							}
							return RetValue
						case GO_TYPE_INT16_SLICE:
							RetValue := make([]int16, len(SliceTemp))
							for i := 0; i < len(SliceTemp); i++ {
								RetValue[i] = (int16)(SRPGoToInt(SliceTemp[i], true))
							}
							return RetValue
						case GO_TYPE_UINT16_SLICE:
							RetValue := make([]uint16, len(SliceTemp))
							for i := 0; i < len(SliceTemp); i++ {
								RetValue[i] = (uint16)(SRPGoToInt(SliceTemp[i], true))
							}
							return RetValue
						case GO_TYPE_INT32_SLICE:
							RetValue := make([]int32, len(SliceTemp))
							for i := 0; i < len(SliceTemp); i++ {
								RetValue[i] = (int32)(SRPGoToInt(SliceTemp[i], true))
							}
							return RetValue
						case GO_TYPE_UINT32_SLICE:
							RetValue := make([]uint32, len(SliceTemp))
							for i := 0; i < len(SliceTemp); i++ {
								RetValue[i] = (uint32)(SRPGoToInt(SliceTemp[i], true))
							}
							return RetValue
						case GO_TYPE_INT_SLICE:
							RetValue := make([]int, len(SliceTemp))
							for i := 0; i < len(SliceTemp); i++ {
								RetValue[i] = (int)(SRPGoToInt64(SliceTemp[i], true))
							}
							return RetValue
						case GO_TYPE_UINT_SLICE:
							RetValue := make([]uint, len(SliceTemp))
							for i := 0; i < len(SliceTemp); i++ {
								RetValue[i] = (uint)(SRPGoToInt64(SliceTemp[i], true))
							}
							return RetValue
						case GO_TYPE_FLOAT32_SLICE:
							RetValue := make([]float32, len(SliceTemp))
							for i := 0; i < len(SliceTemp); i++ {
								RetValue[i] = (float32)(SRPGoToFloat(SliceTemp[i]))
							}
							return RetValue
						case GO_TYPE_FLOAT64_SLICE:
							RetValue := make([]float64, len(SliceTemp))
							for i := 0; i < len(SliceTemp); i++ {
								RetValue[i] = (float64)(SRPGoToFloat(SliceTemp[i]))
							}
							return RetValue
						case GO_TYPE_STRING_SLICE:
							RetValue := make([]string, len(SliceTemp))
							for i := 0; i < len(SliceTemp); i++ {
								if t, ok := SliceTemp[i].(string); ok {
									RetValue[i] = t
								} else {
									RetValue[i] = ""
								}
							}
							return RetValue
						case GO_TYPE_INT64_SLICE:
							RetValue := make([]int64, len(SliceTemp))
							for i := 0; i < len(SliceTemp); i++ {
								RetValue[i] = (int64)(SRPGoToInt64(SliceTemp[i], true))
							}
							return RetValue
						case GO_TYPE_UINT64_SLICE:
							RetValue := make([]uint64, len(SliceTemp))
							for i := 0; i < len(SliceTemp); i++ {
								RetValue[i] = (uint64)(SRPGoToInt64(SliceTemp[i], true))
							}
							return RetValue
						case GO_TYPE_INTERFACE_SLICE:
							return SliceTemp
						default:
							(*Result) = C.VS_FALSE
							return nil
						}
					}
				} else {
					return nil /*--not process --*/
				}
			} else if C.Star_SRPI_LuaIsBinBuf(SRPInterface, Index) == C.VS_TRUE {
				var BinBuf unsafe.Pointer

				BinBuf = C.Star_SRPI_LuaToBinBuf(SRPInterface, Index)
				if ExpectedType == GO_TYPE_INT8_SLICE {
					Length := (C.VS_INT32)(C.Star_SRPBinBuf_GetOffset(BinBuf))
					RetValue := make([]int8, Length)
					if Length != 0 {
						C.memcpy((unsafe.Pointer)(&RetValue[0]), (unsafe.Pointer)(C.Star_SRPBinBuf_GetBuf(BinBuf)), (C.size_t)(Length))
					}
					return RetValue
				} else if ExpectedType == GO_TYPE_UINT8_SLICE {
					Length := (C.VS_INT32)(C.Star_SRPBinBuf_GetOffset(BinBuf))
					RetValue := make([]uint8, Length)
					if Length != 0 {
						C.memcpy((unsafe.Pointer)(&RetValue[0]), (unsafe.Pointer)(C.Star_SRPBinBuf_GetBuf(BinBuf)), (C.size_t)(Length))
					}
					return RetValue
				} else {
					return ToStarBinBuf(BinBuf, C.Star_SRPI_GetServiceGroupID(SRPInterface), C.VS_FALSE)
				}
			} else if C.Star_SRPI_LuaIsString(SRPInterface, Index) == C.VS_TRUE {
				var Str *C.VS_CHAR
				var StrLen C.VS_UINT32

				Str = C.Star_SRPI_LuaToLString(SRPInterface, Index, &StrLen)
				if Str == nil {
					StrLen = 0
				}
				if ExpectedType == GO_TYPE_STARBINBUF {
					var BinBuf unsafe.Pointer
					BinBuf = C.Star_SRPI_GetSRPBinBufInterface(SRPInterface)
					if Str != nil {
						C.Star_SRPBinBuf_Set(BinBuf, 0, StrLen, Str)
					}
					return ToStarBinBuf(BinBuf, C.Star_SRPI_GetServiceGroupID(SRPInterface), C.VS_TRUE)
				} else if ExpectedType == GO_TYPE_INT8_SLICE {
					RetValue := make([]int8, StrLen)
					if StrLen != 0 {
						C.memcpy((unsafe.Pointer)(&RetValue[0]), (unsafe.Pointer)(Str), (C.size_t)(StrLen))
					}
					return RetValue
				} else if ExpectedType == GO_TYPE_UINT8_SLICE {
					RetValue := make([]uint8, StrLen)
					if StrLen != 0 {
						C.memcpy((unsafe.Pointer)(&RetValue[0]), (unsafe.Pointer)(Str), (C.size_t)(StrLen))
					}
					return RetValue
				} else {
					//---change to String
					if Str != nil {
						rrr := SRPGoSetStrEx(Str, (C.VS_INT32)(StrLen), true)
						if len(rrr) != 0 || StrLen == 0 {
							return rrr
						}
						RetValue := make([]uint8, StrLen)
						if StrLen != 0 {
							C.memcpy((unsafe.Pointer)(&RetValue[0]), (unsafe.Pointer)(Str), (C.size_t)(StrLen))
						}
						return RetValue
					} else {
						return ""
					}
				}
			} else {
				ObjectTemp = LuaToGoObject(0, SRPInterface, Index, &LuaToJavaResult)
				if LuaToJavaResult == C.VS_FALSE {
					(*Result) = C.VS_FALSE
					return nil
				}
				return ObjectTemp
			}
		}
	}
	(*Result) = C.VS_FALSE
	return nil
}

func SRPObject_AttributeToGoObject(self *StarObjectBody, AttributeIndex C.VS_UINT8, SRPInterface unsafe.Pointer, AttributeType C.VS_UINT8, AttributeLength C.VS_INT32, StructID *C.VS_UUID, BufOffset C.VS_ULONG, Buf uintptr, UseStructObject C.VS_BOOL) interface{} {
	var AtomicStructObject unsafe.Pointer

	switch AttributeType {
	case C.VSTYPE_BOOL:
		return FROMVS_BOOL(*((*C.VS_BOOL)(unsafe.Pointer(Buf + uintptr(BufOffset)))))

	case C.VSTYPE_INT8:
		return (int8)(*((*C.VS_INT8)(unsafe.Pointer(Buf + uintptr(BufOffset)))))

	case C.VSTYPE_UINT8:
		return (uint8)(*((*C.VS_UINT8)(unsafe.Pointer(Buf + uintptr(BufOffset)))))

	case C.VSTYPE_INT16:
		return (int16)(*((*C.VS_INT16)(unsafe.Pointer(Buf + uintptr(BufOffset)))))

	case C.VSTYPE_UINT16:
		return (uint16)(*((*C.VS_UINT16)(unsafe.Pointer(Buf + uintptr(BufOffset)))))

	case C.VSTYPE_INT32:
		return (int32)(*((*C.VS_INT32)(unsafe.Pointer(Buf + uintptr(BufOffset)))))

	case C.VSTYPE_UINT32:
		return (uint32)(*((*C.VS_UINT32)(unsafe.Pointer(Buf + uintptr(BufOffset)))))

	case C.VSTYPE_INT64:
		return (int64)(*((*C.VS_INT64)(unsafe.Pointer(Buf + uintptr(BufOffset)))))

	case C.VSTYPE_FLOAT:
		return (float32)(*((*C.VS_FLOAT)(unsafe.Pointer(Buf + uintptr(BufOffset)))))

	case C.VSTYPE_DOUBLE:
		return (float64)(*((*C.VS_DOUBLE)(unsafe.Pointer(Buf + uintptr(BufOffset)))))

	case C.VSTYPE_LONG:
		return (int32)(*((*C.VS_LONG)(unsafe.Pointer(Buf + uintptr(BufOffset)))))

	case C.VSTYPE_ULONG:
		return (uint32)(*((*C.VS_ULONG)(unsafe.Pointer(Buf + uintptr(BufOffset)))))

	case C.VSTYPE_LONGHEX:
		return (int32)(*((*C.VS_LONG)(unsafe.Pointer(Buf + uintptr(BufOffset)))))

	case C.VSTYPE_ULONGHEX:
		return (uint32)(*((*C.VS_ULONG)(unsafe.Pointer(Buf + uintptr(BufOffset)))))

	case C.VSTYPE_VSTRING:
		if ((*C.VS_VSTRING)(unsafe.Pointer(Buf + uintptr(BufOffset)))).Buf == nil {
			return ""
		} else {
			return SRPGoSetStr(((*C.VS_VSTRING)(unsafe.Pointer(Buf + uintptr(BufOffset)))).Buf, true)
		}

	case C.VSTYPE_STRUCT:
		AtomicStructObject = C.Star_SRPI_GetAtomicObject(SRPInterface, StructID)
		if AtomicStructObject == nil {
			return nil
		}
		{
			var NewObject []interface{}
			var AttributeNumber C.VS_INT32
			var StructAttributeInfo C.VS_ATTRIBUTEINFO

			AttributeNumber = C.Star_SRPI_GetAtomicStructAttributeNumber(SRPInterface, AtomicStructObject)
			NewObject = make([]interface{}, AttributeNumber)
			for i := (C.VS_INT32)(0); i < AttributeNumber; i++ {
				if C.Star_SRPI_GetAtomicStructAttributeInfoEx(SRPInterface, AtomicStructObject, (C.OBJECTATTRIBUTEINDEX)(i), &StructAttributeInfo) == C.VS_TRUE {
					NewObject[i] = SRPObject_AttributeToGoObject(self, StructAttributeInfo.AttributeIndex, SRPInterface, StructAttributeInfo.Type, StructAttributeInfo.Length, &StructAttributeInfo.StructID, (C.VS_ULONG)(StructAttributeInfo.Offset)+BufOffset, (uintptr)(Buf), UseStructObject)
				}
			}
			return NewObject
		}

	case C.VSTYPE_COLOR:
		return (uint32)(*((*C.VS_COLOR)(unsafe.Pointer(Buf + uintptr(BufOffset)))))

	case C.VSTYPE_CHAR:
		if AttributeLength == 1 {
			return (int8)(*((*C.VS_CHAR)(unsafe.Pointer(Buf + uintptr(BufOffset)))))
		} else {
			return SRPGoSetStr((*C.VS_CHAR)(unsafe.Pointer(Buf+uintptr(BufOffset))), true)
		}
	case C.VSTYPE_UUID:
		fallthrough
	case C.VSTYPE_STATICID:
		return SRPGoSetStr(C.Star_SRPI_UuidToString(SRPInterface, (*C.VS_UUID)(unsafe.Pointer(Buf+uintptr(BufOffset)))), false)

	default:
		return nil
	}
}

func SRPObject_GoObjectToAttribute(SRPInterface unsafe.Pointer, AttributeType C.VS_UINT8, AttributeLength C.VS_INT32, StructID *C.VS_UUID, ObjectTemp interface{}, BufOffset C.VS_ULONG, Buf uintptr) bool {
	var UIntValue C.VS_UINT32
	var IntValue C.VS_INT32
	var FloatValue C.VS_DOUBLE
	var CharValue *C.VS_CHAR
	var AtomicStruct unsafe.Pointer
	var AttributeInfo C.VS_ATTRIBUTEINFO

	switch AttributeType {
	case C.VSTYPE_BOOL:
		if S, _ := ObjectTemp.(bool); S == true {
			*((*C.VS_BOOL)(unsafe.Pointer(Buf + uintptr(BufOffset)))) = C.VS_TRUE
		} else {
			*((*C.VS_BOOL)(unsafe.Pointer(Buf + uintptr(BufOffset)))) = C.VS_FALSE
		}
		return true

	case C.VSTYPE_INT8:
		if SRPGoGetInt(ObjectTemp, &UIntValue, false) == false {
			if SRPGoIsString(ObjectTemp) == true {
				var CharPtr *C.VS_CHAR
				s := ObjectTemp.(string)
				CharPtr = SRPGoGetStr(s, false)
				UIntValue = (C.VS_UINT32)(*(*C.VS_CHAR)(CharPtr))
				STARGO_SAFERELEASESTR(s, CharPtr)
			} else {
				return false
			}
		}
		*((*C.VS_INT8)(unsafe.Pointer(Buf + uintptr(BufOffset)))) = (C.VS_INT8)(UIntValue)
		return true

	case C.VSTYPE_UINT8:
		if SRPGoGetInt(ObjectTemp, &UIntValue, true) == false {
			return false
		}
		*((*C.VS_UINT8)(unsafe.Pointer(Buf + uintptr(BufOffset)))) = (C.VS_UINT8)(UIntValue)
		return true

	case C.VSTYPE_INT16:
		if SRPGoGetInt(ObjectTemp, &UIntValue, true) == false {
			return false
		}
		*((*C.VS_INT16)(unsafe.Pointer(Buf + uintptr(BufOffset)))) = (C.VS_INT16)(UIntValue)
		return true

	case C.VSTYPE_UINT16:
		if SRPGoGetInt(ObjectTemp, &UIntValue, true) == false {
			return false
		}
		*((*C.VS_UINT16)(unsafe.Pointer(Buf + uintptr(BufOffset)))) = (C.VS_UINT16)(UIntValue)
		return true

	case C.VSTYPE_INT32:
		if SRPGoGetInt(ObjectTemp, &UIntValue, true) == false {
			return false
		}
		*((*C.VS_INT32)(unsafe.Pointer(Buf + uintptr(BufOffset)))) = (C.VS_INT32)(UIntValue)
		return true

	case C.VSTYPE_UINT32:
		if SRPGoGetInt(ObjectTemp, &UIntValue, true) == false {
			return false
		}
		*((*C.VS_UINT32)(unsafe.Pointer(Buf + uintptr(BufOffset)))) = (C.VS_UINT32)(UIntValue)
		return true

	case C.VSTYPE_INT64:
		*((*C.VS_INT64)(unsafe.Pointer(Buf + uintptr(BufOffset)))) = SRPGoToLong(ObjectTemp, true)
		return true

	case C.VSTYPE_FLOAT:
		if SRPGoGetInt(ObjectTemp, (*C.VS_UINT32)((unsafe.Pointer)(&IntValue)), false) == true {
			*((*C.VS_FLOAT)(unsafe.Pointer(Buf + uintptr(BufOffset)))) = (C.VS_FLOAT)(IntValue)
			return true
		}
		if SRPGoGetFloat(ObjectTemp, &FloatValue) == false {
			return false
		}
		*((*C.VS_FLOAT)(unsafe.Pointer(Buf + uintptr(BufOffset)))) = (C.VS_FLOAT)(FloatValue)
		return true

	case C.VSTYPE_DOUBLE:
		if SRPGoGetInt(ObjectTemp, (*C.VS_UINT32)((unsafe.Pointer)(&IntValue)), false) == true {
			*((*C.VS_DOUBLE)(unsafe.Pointer(Buf + uintptr(BufOffset)))) = (C.VS_DOUBLE)(IntValue)
			return true
		}
		if SRPGoGetFloat(ObjectTemp, &FloatValue) == false {
			return false
		}
		*((*C.VS_DOUBLE)(unsafe.Pointer(Buf + uintptr(BufOffset)))) = (C.VS_DOUBLE)(FloatValue)
		return true

	case C.VSTYPE_LONG:
		if SRPGoGetInt(ObjectTemp, &UIntValue, true) == false {
			return false
		}
		*((*C.VS_LONG)(unsafe.Pointer(Buf + uintptr(BufOffset)))) = (C.VS_LONG)(UIntValue)
		return true

	case C.VSTYPE_ULONG:
		if SRPGoGetInt(ObjectTemp, &UIntValue, true) == false {
			return false
		}
		*((*C.VS_ULONG)(unsafe.Pointer(Buf + uintptr(BufOffset)))) = (C.VS_ULONG)(UIntValue)
		return true

	case C.VSTYPE_LONGHEX:
		if SRPGoGetInt(ObjectTemp, &UIntValue, true) == false {
			return false
		}
		*((*C.VS_LONG)(unsafe.Pointer(Buf + uintptr(BufOffset)))) = (C.VS_LONG)(UIntValue)
		return true

	case C.VSTYPE_ULONGHEX:
		if SRPGoGetInt(ObjectTemp, &UIntValue, true) == false {
			return false
		}
		*((*C.VS_ULONG)(unsafe.Pointer(Buf + uintptr(BufOffset)))) = (C.VS_ULONG)(UIntValue)
		return true

	case C.VSTYPE_VSTRING:
		if S, ok := ObjectTemp.(string); ok {
			CharValue = SRPGoGetStr(S, true)
			if CharValue == nil {
				return false
			}
			C.Star_SRPI_ExpandVStringBufSize(SRPInterface, (*C.VS_VSTRING)(unsafe.Pointer(Buf+uintptr(BufOffset))), (C.VS_ULONG)(C.vs_string_strlen(CharValue)+1))
			C.strcpy((*C.char)(unsafe.Pointer((*C.VS_VSTRING)(unsafe.Pointer(Buf+uintptr(BufOffset))).Buf)), CharValue)
			C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(CharValue))
			return true
		} else {
			return false
		}

	case C.VSTYPE_STRUCT:
		if S, ok := ObjectTemp.([]interface{}); !ok {
			return false
		} else {
			var num_index C.VS_INT32
			var i C.VS_INT32
			var LocalObjectTemp interface{}

			AtomicStruct = C.Star_SRPI_GetAtomicObject(SRPInterface, StructID)
			if AtomicStruct == nil {
				return false
			}
			for num_index = (C.VS_INT32)(0); num_index < (C.VS_INT32)(len(S)); num_index++ {
				i = num_index
				if i >= 0 && i < C.Star_SRPI_GetAtomicStructAttributeNumber(SRPInterface, AtomicStruct) {
					C.Star_SRPI_GetAtomicStructAttributeInfoEx(SRPInterface, AtomicStruct, (C.OBJECTATTRIBUTEINDEX)(i), &AttributeInfo)
					LocalObjectTemp = S[num_index]
					if SRPObject_GoObjectToAttribute(SRPInterface, AttributeInfo.Type, AttributeInfo.Length, nil, LocalObjectTemp, (C.VS_ULONG)(AttributeInfo.Offset)+BufOffset, Buf) == false {
						return false
					}
				}
			}
		}
		return true

	case C.VSTYPE_COLOR:
		if SRPGoGetInt(ObjectTemp, &UIntValue, true) == false {
			return false
		}
		*((*C.VS_COLOR)(unsafe.Pointer(Buf + uintptr(BufOffset)))) = (C.VS_COLOR)(UIntValue)
		return true

	case C.VSTYPE_CHAR:
		if S, ok := ObjectTemp.(string); ok {
			CharValue = SRPGoGetStr(S, true)
			if CharValue == nil {
				return false
			}
			C.strncpy((*C.char)(unsafe.Pointer(Buf+uintptr(BufOffset))), CharValue, (C.size_t)(AttributeLength))
			*((*C.VS_CHAR)(unsafe.Pointer(Buf + uintptr(BufOffset+(C.VS_ULONG)(AttributeLength)-1)))) = 0
			C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(CharValue))
			return true
		} else {
			return false
		}

	case C.VSTYPE_UUID:
	case C.VSTYPE_STATICID:
		if S, ok := ObjectTemp.(string); ok {
			CharValue = SRPGoGetStr(S, false)
			if CharValue == nil {
				return false
			}
			C.Star_SRPI_StringToUuid(SRPInterface, CharValue, (*C.VS_UUID)(unsafe.Pointer(Buf+uintptr(BufOffset))))
			STARGO_SAFERELEASESTR(S, CharValue)
			return true
		} else {
			return false
		}
	}
	return false
}

func (desobject *StarObject) Get(InVar interface{}) interface{} {
	var self *StarObjectBody
	var SRPInterface unsafe.Pointer
	var SRPObject unsafe.Pointer
	var SRPObjectTemp unsafe.Pointer
	var AttributeInfo C.VS_ATTRIBUTEINFO
	var HashValue C.VS_ULONG
	var ParaName *C.VS_CHAR
	var ObjectTemp1 interface{}
	var Name string

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}

	switch v := InVar.(type) {
	case string:
		Name = v
		ParaName = SRPGoGetStr(Name, false)
		defer C.free((unsafe.Pointer)(ParaName))
	case int:
		Name = fmt.Sprintf("\"%d\"", v)
		ParaName = SRPGoGetStr(Name, false)
		defer C.free((unsafe.Pointer)(ParaName))
	default:
		return nil
	}

	self = StarObjectClass_getstarcoredata(desobject)
	SRPInterface = GetSRPServiceInterfaceEx(self.ServiceGroupID, &self.ObjectID)
	if SRPInterface == nil {
		return nil
	}
	SRPObject = C.Star_SRPI_GetObject(SRPInterface, &self.ObjectID)
	if SRPObject == nil {
		return nil
	}

	TermObjectDefer_Free(false)

	if (*C.stargo_GetCharByIndex(ParaName, 0)) == '_' && (*C.stargo_GetCharByIndex(ParaName, 1)) == '_' && (*C.stargo_GetCharByIndex(ParaName, 2)) == '_' {
		//---process object namevalue
		var Type C.VS_UINT8
		var IntValue C.VS_INT32
		var FloatValue C.VS_DOUBLE
		var BoolValue C.VS_BOOL

		Type = C.Star_SRPI_GetNameValueType(SRPInterface, SRPObject, C.stargo_GetCharByIndex(ParaName, 3))
		switch Type {
		case C.SRPPARATYPE_BOOL:
			C.Star_SRPI_GetNameBoolValue(SRPInterface, SRPObject, C.stargo_GetCharByIndex(ParaName, 3), &BoolValue, C.VS_FALSE)
			return FROMVS_BOOL(BoolValue)
		case C.SRPPARATYPE_INT:
			C.Star_SRPI_GetNameIntValue(SRPInterface, SRPObject, C.stargo_GetCharByIndex(ParaName, 3), &IntValue, 0)
			return (int)(IntValue)
		case C.SRPPARATYPE_FLOAT:
			C.Star_SRPI_GetNameFloatValue(SRPInterface, SRPObject, C.stargo_GetCharByIndex(ParaName, 3), &FloatValue, 0)
			return (float64)(FloatValue)
		case C.SRPPARATYPE_CHARPTR:
			return SRPGoSetStr(C.Star_SRPI_GetNameStrValue(SRPInterface, SRPObject, C.stargo_GetCharByIndex(ParaName, 3), EmptyString), true)
		default:
			return nil
		}
	}

	HashValue = C.Star_SRPI_GetHashValue(SRPInterface, (unsafe.Pointer)(ParaName), (C.VS_ULONG)(C.vs_string_strlen(ParaName)), 0)
	switch HashValue {
	case 0XF0F4CCC1: //_Service
		if strings.Compare(Name, "_Service") == 0 {
			GoSRPQueryServiceEx(self.ServiceGroupID, &self.ObjectID)
		}
	case 0XFA037CAB: //_Class
		if strings.Compare(Name, "_Class") == 0 {
			SRPObjectTemp = C.Star_SRPI_GetClass(SRPInterface, SRPObject)
			if SRPObjectTemp == nil {
				return nil
			}
			return ToStarObject(SRPObjectTemp, SRPInterface, C.VS_FALSE)
		}
	case 0X67F0ABC5: //_ID
		if strings.Compare(Name, "_ID") == 0 {
			var IDTemp C.VS_UUID

			C.Star_SRPI_GetID(SRPInterface, SRPObject, &IDTemp)
			return SRPGoSetStr(C.Star_SRPI_UuidToString(SRPInterface, &IDTemp), false)
		}
	case 0X64756CF2: //_Name
		if strings.Compare(Name, "_Name") == 0 {
			return SRPGoSetStr(C.Star_SRPI_GetName(SRPInterface, SRPObject), true)
		}
	}
	//---check if is object's attribute
	if C.Star_SRPI_GetAttributeInfoEx(SRPInterface, C.Star_SRPI_GetClass(SRPInterface, SRPObject), ParaName, &AttributeInfo) == C.VS_TRUE {
		return SRPObject_AttributeToGoObject(self, AttributeInfo.AttributeIndex, SRPInterface, AttributeInfo.Type, AttributeInfo.Length, &AttributeInfo.StructID, (C.VS_ULONG)(AttributeInfo.Offset), (uintptr)(SRPObject), C.VS_TRUE)
	} else {
		C.Star_SRPI_LuaPushObject(SRPInterface, SRPObject)
		C.Star_SRPI_LuaPushString(SRPInterface, ParaName)
		C.Star_SRPI_LuaGetTable(SRPInterface, -2)
		if C.Star_SRPI_LuaIsNil(SRPInterface, -1) == C.VS_FALSE {
			var LuaToJavaResult C.VS_BOOL

			if C.Star_SRPI_LuaIsFunction(SRPInterface, -1) == C.VS_TRUE {
				C.Star_SRPI_LuaPop(SRPInterface, 2)
				return nil
			}
			ObjectTemp1 = LuaToGoObject(0, SRPInterface, -1, &LuaToJavaResult)
			C.Star_SRPI_LuaPop(SRPInterface, 2)
			if LuaToJavaResult == C.VS_FALSE {
				S := C.CString(fmt.Sprintf("Get Object[%s] Attribute [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, SRPObject)), Name))
				GoPrintError(C.VSFAULT_WARNING, S)
				C.free((unsafe.Pointer)(S))
				return nil
			}
			return ObjectTemp1
		}
		C.Star_SRPI_LuaPop(SRPInterface, 2)
	}
	return nil
}

func (self *StarObject) GetBool(InVar interface{}) bool {
	S, ok := self.Get(InVar).(bool)
	if ok {
		return S
	}
	return false
}

func (self *StarObject) GetInt(InVar interface{}) int32 {
	res := self.Get(InVar)
	val := SRPGoToInt(res, true)
	return (int32)(val)
}

func (self *StarObject) GetInt64(InVar interface{}) int64 {
	res := self.Get(InVar)
	val := SRPGoToInt64(res, true)
	return (int64)(val)
}

func (self *StarObject) GetString(InVar interface{}) string {
	S, ok := self.Get(InVar).(string)
	if ok {
		return S
	}
	return ""
}

func (self *StarObject) GetDouble(InVar interface{}) float64 {
	res := self.Get(InVar)
	val := SRPGoToFloat(res)
	return (float64)(val)
}

func (self *StarObject) GetObject(InVar interface{}) *StarObject {
	S, ok := self.Get(InVar).(*StarObject)
	if ok {
		return S
	}
	return nil
}

func (self *StarObject) GetParaPkg(InVar interface{}) *StarParaPkg {
	S, ok := self.Get(InVar).(*StarParaPkg)
	if ok {
		return S
	}
	return nil
}

func (self *StarObject) GetBinBuf(InVar interface{}) *StarBinBuf {
	S, ok := self.Get(InVar).(*StarBinBuf)
	if ok {
		return S
	}
	return nil
}

var ObjectCreate_AttachBuf [64 * 1024]C.VS_INT8

func (desobject *StarObject) Set(InVar interface{}, Para interface{}) {
	var self *StarObjectBody
	var SRPInterface unsafe.Pointer
	var SRPObject unsafe.Pointer
	var AttributeInfo C.VS_ATTRIBUTEINFO
	var HashValue C.VS_ULONG
	var ParaName *C.VS_CHAR
	var Name string

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}

	switch v := InVar.(type) {
	case string:
		Name = v
		ParaName = SRPGoGetStr(Name, false)
		defer C.free((unsafe.Pointer)(ParaName))
	case int:
		Name = fmt.Sprintf("\"%d\"", v)
		ParaName = SRPGoGetStr(Name, false)
		defer C.free((unsafe.Pointer)(ParaName))
	default:
		return
	}

	self = StarObjectClass_getstarcoredata(desobject)
	SRPInterface = GetSRPServiceInterfaceEx(self.ServiceGroupID, &self.ObjectID)
	if SRPInterface == nil {
		return
	}
	SRPObject = C.Star_SRPI_GetObject(SRPInterface, &self.ObjectID)
	if SRPObject == nil {
		return
	}

	TermObjectDefer_Free(false)

	if (*C.stargo_GetCharByIndex(ParaName, 0)) == '_' && (*C.stargo_GetCharByIndex(ParaName, 1)) == '_' && (*C.stargo_GetCharByIndex(ParaName, 2)) == '_' {
		//---process object namevalue
		switch v := Para.(type) {
		case bool:
			C.Star_SRPI_SetNameBoolValue(SRPInterface, SRPObject, C.stargo_GetCharByIndex(ParaName, 3), TOVS_BOOL(v), C.VS_FALSE)
			return
		case int8:
			C.Star_SRPI_SetNameIntValue(SRPInterface, SRPObject, C.stargo_GetCharByIndex(ParaName, 3), (C.VS_INT32)(v), C.VS_FALSE)
			return
		case uint8:
			C.Star_SRPI_SetNameIntValue(SRPInterface, SRPObject, C.stargo_GetCharByIndex(ParaName, 3), (C.VS_INT32)(v), C.VS_FALSE)
			return
		case int16:
			C.Star_SRPI_SetNameIntValue(SRPInterface, SRPObject, C.stargo_GetCharByIndex(ParaName, 3), (C.VS_INT32)(v), C.VS_FALSE)
			return
		case uint16:
			C.Star_SRPI_SetNameIntValue(SRPInterface, SRPObject, C.stargo_GetCharByIndex(ParaName, 3), (C.VS_INT32)(v), C.VS_FALSE)
			return
		case int32:
			C.Star_SRPI_SetNameIntValue(SRPInterface, SRPObject, C.stargo_GetCharByIndex(ParaName, 3), (C.VS_INT32)(v), C.VS_FALSE)
			return
		case uint32:
			C.Star_SRPI_SetNameIntValue(SRPInterface, SRPObject, C.stargo_GetCharByIndex(ParaName, 3), (C.VS_INT32)(v), C.VS_FALSE)
			return
		case int:
			C.Star_SRPI_SetNameIntValue(SRPInterface, SRPObject, C.stargo_GetCharByIndex(ParaName, 3), (C.VS_INT32)(v), C.VS_FALSE)
			return
		case uint:
			C.Star_SRPI_SetNameIntValue(SRPInterface, SRPObject, C.stargo_GetCharByIndex(ParaName, 3), (C.VS_INT32)(v), C.VS_FALSE)
			return
		case int64:
			C.Star_SRPI_SetNameIntValue(SRPInterface, SRPObject, C.stargo_GetCharByIndex(ParaName, 3), (C.VS_INT32)(v), C.VS_FALSE)
			return
		case uint64:
			C.Star_SRPI_SetNameIntValue(SRPInterface, SRPObject, C.stargo_GetCharByIndex(ParaName, 3), (C.VS_INT32)(v), C.VS_FALSE)
			return
		case float32:
			C.Star_SRPI_SetNameFloatValue(SRPInterface, SRPObject, C.stargo_GetCharByIndex(ParaName, 3), (C.VS_DOUBLE)(v), C.VS_FALSE)
			return
		case float64:
			C.Star_SRPI_SetNameFloatValue(SRPInterface, SRPObject, C.stargo_GetCharByIndex(ParaName, 3), (C.VS_DOUBLE)(v), C.VS_FALSE)
			return
		case string:
			cstr := SRPGoGetStr(v, true)
			C.Star_SRPI_SetNameStrValue(SRPInterface, SRPObject, C.stargo_GetCharByIndex(ParaName, 3), cstr, C.VS_FALSE)
			C.Star_SRPCS_FreeBuf(C.StarGo_SRPControlInterface, (unsafe.Pointer)(cstr))
			return
		default:
			return
		}
	}
	HashValue = C.Star_SRPI_GetHashValue(SRPInterface, (unsafe.Pointer)(ParaName), (C.VS_ULONG)(C.vs_string_strlen(ParaName)), 0)
	switch HashValue {
	case 0X64756CF2: //_Name
		if strings.Compare(Name, "_Name") == 0 {
			cstr := C.CString(Name)
			C.Star_SRPI_SetName(SRPInterface, SRPObject, cstr)
			C.free(unsafe.Pointer(cstr))
			return
		}
	}
	if C.Star_SRPI_GetAttributeInfoEx(SRPInterface, C.Star_SRPI_GetClass(SRPInterface, SRPObject), ParaName, &AttributeInfo) == C.VS_TRUE {
		if SRPObject_GoObjectToAttribute(SRPInterface, AttributeInfo.Type, AttributeInfo.Length, &AttributeInfo.StructID, Para, 0, (uintptr)((unsafe.Pointer)(&ObjectCreate_AttachBuf[0]))) == false {
			S := C.CString(fmt.Sprintf("Set Object[%s] Attribute [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, SRPObject)), C.GoString((*C.VS_CHAR)((unsafe.Pointer)(&AttributeInfo.Name[0])))))
			GoPrintError(C.VSFAULT_WARNING, S)
			C.free((unsafe.Pointer)(S))
			return
		}
		C.Star_SRPI_ChangeObject(SRPInterface, SRPObject, AttributeInfo.AttributeIndex, (*C.VS_INT8)(unsafe.Pointer(&ObjectCreate_AttachBuf[0])))
		return
	} else {
		C.Star_SRPI_LuaPushObject(SRPInterface, SRPObject)
		C.Star_SRPI_LuaPushString(SRPInterface, ParaName)
		C.Star_SRPI_LuaGetTable(SRPInterface, -2)
		if C.Star_SRPI_LuaIsNil(SRPInterface, -1) == C.VS_FALSE {
			var DefinedClassID C.VS_UUID

			C.Star_SRPI_LuaGetDefinedClass(SRPInterface, SRPObject, &DefinedClassID)
			if C.Star_SRPI_LuaIsFunction(SRPInterface, -1) == C.VS_FALSE && C.stargo_uuidisequal(&self.ObjectID, &DefinedClassID) == C.VS_TRUE {
				C.Star_SRPI_LuaPop(SRPInterface, 2)
				C.Star_SRPI_LuaPushObject(SRPInterface, SRPObject)
				C.Star_SRPI_LuaPushString(SRPInterface, ParaName)

				if GoObjectToLua(SRPInterface, Para, false) == false {
					S := C.CString(fmt.Sprintf("Set Object[%s] Attribute [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, SRPObject)), Name))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
				}
				C.Star_SRPI_LuaSetTable(SRPInterface, -3)
				C.Star_SRPI_LuaPop(SRPInterface, 1)
				return
			}
		}
		C.Star_SRPI_LuaPop(SRPInterface, 2)

		var RawContextHeader *C.struct_StructOfCommonRawContextHeader = (*C.struct_StructOfCommonRawContextHeader)(C.Star_SRPI_GetRawContextBuf(SRPInterface, SRPObject, EmptyString /*""*/))
		if RawContextHeader == nil || RawContextHeader.IsGlobalSpace == C.VS_FALSE {
			ObjectScriptProc, ok := Para.(func(CleGroup *StarSrvGroup, CleService *StarService, CleObject *StarObject, Paras []interface{}) interface{})
			_, ObjectScriptProc_Exist := self.Table[Name]

			if ok && !ObjectScriptProc_Exist {
				C.Star_SRPI_RegLuaFunc(SRPInterface, SRPObject, ParaName, (unsafe.Pointer)(C.stargo_SRPObject_ScriptCallBack), (C.VS_UWORD)(self.RefItem))
				GoSRPSetObject(self.ServiceGroupID, &self.ObjectID, desobject, C.VS_TRUE)
				self.Table[Name] = ObjectScriptProc
				return
			}
		}

		if C.Star_SRPI_GetRawLuaSetValueFunc(SRPInterface, SRPObject, ParaName, (*C.VS_UWORD)(C.NULL)) != C.NULL ||
			(RawContextHeader != nil && RawContextHeader.IsGlobalSpace == C.VS_TRUE) {
			C.Star_SRPI_LuaPushObject(SRPInterface, SRPObject)
			C.Star_SRPI_LuaPushString(SRPInterface, ParaName)

			if GoObjectToLua(SRPInterface, Para, false) == false {
				S := C.CString(fmt.Sprintf("Set Object[%s] Attribute [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, SRPObject)), Name))
				GoPrintError(C.VSFAULT_WARNING, S)
				C.free((unsafe.Pointer)(S))
			}
			C.Star_SRPI_LuaSetTable(SRPInterface, -3)
			C.Star_SRPI_LuaPop(SRPInterface, 1)
			return
		}
	}
}

func (selfobj *StarObject) Call(FuncName string, Args ...interface{}) interface{} {
	return selfobj.Call_Internal(FuncName, Args)
}

func (self *StarObject) CallBool(FuncName string, Args ...interface{}) bool {
	S, ok := self.Call_Internal(FuncName, Args).(bool)
	if ok {
		return S
	}
	return false
}

func (self *StarObject) CallInt(FuncName string, Args ...interface{}) int32 {
	res := self.Call_Internal(FuncName, Args)
	val := SRPGoToInt(res, true)
	return (int32)(val)
}

func (self *StarObject) CallInt64(FuncName string, Args ...interface{}) int64 {
	res := self.Call_Internal(FuncName, Args)
	val := SRPGoToInt64(res, true)
	return (int64)(val)
}

func (self *StarObject) CallString(FuncName string, Args ...interface{}) string {
	S, ok := self.Call_Internal(FuncName, Args).(string)
	if ok {
		return S
	}
	return ""
}

func (self *StarObject) CallDouble(FuncName string, Args ...interface{}) float64 {
	res := self.Call_Internal(FuncName, Args)
	val := SRPGoToFloat(res)
	return (float64)(val)
}

func (self *StarObject) CallObject(FuncName string, Args ...interface{}) *StarObject {
	S, ok := self.Call_Internal(FuncName, Args).(*StarObject)
	if ok {
		return S
	}
	return nil
}

func (self *StarObject) CallParaPkg(FuncName string, Args ...interface{}) *StarParaPkg {
	S, ok := self.Call_Internal(FuncName, Args).(*StarParaPkg)
	if ok {
		return S
	}
	return nil
}

func (self *StarObject) CallBinBuf(FuncName string, Args ...interface{}) *StarBinBuf {
	S, ok := self.Call_Internal(FuncName, Args).(*StarBinBuf)
	if ok {
		return S
	}
	return nil
}

func (selfobj *StarObject) Call_Internal(FuncName string, Args []interface{}) (FunctionResult interface{}) {
	var SRPInterface unsafe.Pointer
	var self *StarObjectBody
	var argc, i, m, n C.VS_INT32
	var localobject interface{}
	var FunctionName *C.VS_CHAR
	var SRPObject unsafe.Pointer
	var Result C.VS_BOOL

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}
	if Args == nil {
		argc = 0
	} else {
		argc = (C.VS_INT32)(len(Args))
	}

	TermObjectDefer_Free(false)

	self = StarObjectClass_getstarcoredata(selfobj)
	SRPInterface = GetSRPServiceInterfaceEx(self.ServiceGroupID, &self.ObjectID)
	if SRPInterface == nil {
		return nil
	}
	SRPObject = C.Star_SRPI_GetObject(SRPInterface, &self.ObjectID)
	if SRPObject == nil {
		return nil
	}

	n = C.Star_SRPI_LuaGetTop(SRPInterface)
	for i = (C.VS_INT32)(0); i < argc; i++ {
		localobject = Args[i]
		GoObjectToLua(SRPInterface, localobject, false)
	}

	FunctionName = SRPGoGetStr(FuncName, false)
	defer C.free((unsafe.Pointer)(FunctionName))

	defer func() {
		if err := recover(); err != nil {
			S := C.CString(fmt.Sprintf("call function[%s] failed", FuncName))
			GoPrintError(C.VSFAULT_WARNING, S)
			C.free((unsafe.Pointer)(S))
			FunctionResult = nil
			return
		}
	}()

	if C.Star_SRPI_LuaCall(SRPInterface, SRPObject, FunctionName, argc, (C.VS_INT32)(-1)) == C.VS_FALSE {
		m = C.Star_SRPI_LuaGetTop(SRPInterface)
		if m > n {
			C.Star_SRPI_LuaPop(SRPInterface, m-n)
		}
		return nil
	}
	m = C.Star_SRPI_LuaGetTop(SRPInterface)
	if m == n {
		return nil
	} else if m > n {
		if m-n == 1 {
			RetValue := LuaToGoObject(0, SRPInterface, -1, &Result)
			C.Star_SRPI_LuaPop(SRPInterface, m-n)
			return RetValue
		} else {
			RetValue := make([]interface{}, m-n)
			for i = (C.VS_INT32)(0); i < m-n; i++ {
				RetValue[i] = LuaToGoObject(0, SRPInterface, i-(m-n), &Result)
			}
			C.Star_SRPI_LuaPop(SRPInterface, m-n)
			return RetValue
		}
	} else {
		S := C.CString(fmt.Sprintf("call function[%s] failed,lua stack corrupted", FuncName))
		GoPrintError(C.VSFAULT_WARNING, S)
		C.free((unsafe.Pointer)(S))
		return nil
	}
}

func SRPObject_CreateNewObject(SRPInterface unsafe.Pointer, SRPClassObject unsafe.Pointer, Type C.VS_INT32, ObjectID *C.VS_UUID, ClientID C.VS_ULONG, QueueAttrName *C.VS_CHAR, ParentObject unsafe.Pointer, ObjectNameString *C.VS_CHAR, InitString *C.VS_CHAR, InitBuf unsafe.Pointer) unsafe.Pointer {
	var i, AttributeNumber C.VS_INT32
	var AttributeInfo C.VS_ATTRIBUTEINFO
	var NewSRPObject unsafe.Pointer
	var ObjectClassID C.VS_UUID

	C.Star_SRPI_GetID(SRPInterface, SRPClassObject, &ObjectClassID)

	if ParentObject != nil {
		if QueueAttrName != nil {
			if C.Star_SRPI_GetAttributeInfoEx(SRPInterface, C.Star_SRPI_GetClass(SRPInterface, ParentObject), QueueAttrName, &AttributeInfo) == C.VS_FALSE {
				S := C.CString(fmt.Sprintf("Get Parent Attribute [%s]", C.GoString(QueueAttrName)))
				GoPrintError(C.VSFAULT_WARNING, S)
				C.free((unsafe.Pointer)(S))
				return nil
			}
		} else {
			if C.Star_SRPI_IsObject(SRPInterface, ParentObject) == C.VS_TRUE {
				AttributeNumber = C.Star_SRPI_GetAttributeNumber(SRPInterface, C.Star_SRPI_GetClass(SRPInterface, ParentObject))
				for i = (C.VS_INT32)(0); i < AttributeNumber; i++ {
					C.Star_SRPI_GetAttributeInfo(SRPInterface, C.Star_SRPI_GetClass(SRPInterface, ParentObject), (C.OBJECTATTRIBUTEINDEX)(i), &AttributeInfo)
					if AttributeInfo.Type == C.VSTYPE_PTR && AttributeInfo.SyncType == C.VS_TRUE && (C.stargo_uuidisequal(&AttributeInfo.StructID, &ObjectClassID) == C.VS_TRUE || C.Star_SRPI_IsInst(SRPInterface, &AttributeInfo.StructID, SRPClassObject) == C.VS_TRUE) {
						break
					}
				}
				if i >= AttributeNumber {
					for i = (C.VS_INT32)(0); i < AttributeNumber; i++ {
						C.Star_SRPI_GetAttributeInfo(SRPInterface, C.Star_SRPI_GetClass(SRPInterface, ParentObject), (C.OBJECTATTRIBUTEINDEX)(i), &AttributeInfo)
						if AttributeInfo.Type == C.VSTYPE_PTR && AttributeInfo.SyncType == C.VS_TRUE && C.stargo_uuidisvalid(&AttributeInfo.StructID) == C.VS_TRUE {
							break
						}
					}
					if i >= AttributeNumber {
						S := C.CString("not Found Parent Sync Attribute Queue")
						GoPrintError(C.VSFAULT_WARNING, S)
						C.free((unsafe.Pointer)(S))
						return nil
					}
				}
			} else {
				AttributeInfo.AttributeIndex = 0
			}
		}
	}
	NewSRPObject = nil
	if ParentObject != nil {
		NewSRPObject = C.Star_SRPI_IMallocObjectEx(SRPInterface, ObjectID, ParentObject, AttributeInfo.AttributeIndex, &ObjectClassID, (C.VS_PARAPKGPTR)(InitBuf))
	} else {
		NewSRPObject = C.Star_SRPI_IMallocObjectLEx(SRPInterface, ObjectID, &ObjectClassID, (C.VS_PARAPKGPTR)(InitBuf))
	}
	if NewSRPObject != nil {
		C.Star_SRPI_SetSourceScript(SRPInterface, NewSRPObject, C.StarGo_ScriptInterfaceIndex)
		if ObjectNameString != nil && C.strlen(ObjectNameString) != 0 {
			C.Star_SRPI_SetName(SRPInterface, NewSRPObject, ObjectNameString)
		}
		if InitString != nil && C.vs_string_strlen(InitString) != 0 {
			C.Star_SRPI_LuaInitObject(SRPInterface, NewSRPObject, InitString)
		}
	}
	return NewSRPObject
}

func (selfobj *StarObject) New(args ...interface{}) *StarObject {
	var self *StarObjectBody
	var argc C.VS_INT32
	var SRPInterface unsafe.Pointer
	var ObjectTemp interface{}
	var SRPObject, SRPParentObject unsafe.Pointer
	var QueueAttrName, ObjectNameString, AttributeChangeString *C.VS_CHAR
	var Index C.VS_INT32 = 0
	var SkipObjectNameString C.VS_BOOL = C.VS_FALSE

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}

	self = StarObjectClass_getstarcoredata(selfobj)

	QueueAttrName = nil
	SRPParentObject = nil
	AttributeChangeString = nil
	ObjectNameString = nil
	ObjectTemp = nil

	if args == nil {
		argc = 0
	} else {
		argc = (C.VS_INT32)(len(args))
	}

	if argc == 0 {
		QueueAttrName = nil
		SRPParentObject = nil
	} else {
		ObjectTemp = SRPObject_GetArrayObject(argc, args, Index)
		if ObjectTemp != nil {
			if _, ok := ObjectTemp.(string); ok {
				QueueAttrName = C.CString(ObjectTemp.(string))
				defer C.free((unsafe.Pointer)(QueueAttrName))
				Index++
				ObjectTemp = SRPObject_GetArrayObject(argc, args, Index)
				if ObjectTemp == nil { //no more parameter
					ObjectNameString = QueueAttrName
					QueueAttrName = nil
					SRPParentObject = nil
					SkipObjectNameString = C.VS_TRUE
				} else {
					if IsStarObjectClassObject(ObjectTemp) == true {
						SRPParentObject = GoObjectToSRPObject(ObjectTemp)
						Index++
						ObjectTemp = SRPObject_GetArrayObject(argc, args, Index)
					} else if S, ok := ObjectTemp.(string); ok {
						ObjectNameString = QueueAttrName
						QueueAttrName = nil
						SRPParentObject = nil
						AttributeChangeString = SRPGoGetStr(S, true)
						Index++
						SkipObjectNameString = C.VS_TRUE
						ObjectTemp = SRPObject_GetArrayObject(argc, args, Index) //end
					} else {
						return nil
					}
				}
			} else if IsStarObjectClassObject(ObjectTemp) == true {
				SRPParentObject = GoObjectToSRPObject(ObjectTemp)
				Index++
				ObjectTemp = SRPObject_GetArrayObject(argc, args, Index)
			} else {
				return nil
			}
		}
	}
	if ObjectTemp != nil && SkipObjectNameString == C.VS_FALSE {
		if S, ok := ObjectTemp.(string); ok {
			ObjectNameString = SRPGoGetStr(S, false)
			Index++
			ObjectTemp = SRPObject_GetArrayObject(argc, args, Index)
			if ObjectTemp == nil { //no more parameter
			} else if S, ok := ObjectTemp.(string); ok {
				AttributeChangeString = SRPGoGetStr(S, true)
				Index++
				ObjectTemp = SRPObject_GetArrayObject(argc, args, Index) //end
			}
		}
	}

	var InitBuf unsafe.Pointer = nil
	if Index < argc {
		var BasicSRPInterface unsafe.Pointer
		var SRPInterface unsafe.Pointer

		BasicSRPInterface = GoSRPGetBasicSRPInterface(self.ServiceGroupID)
		SRPInterface = GetSRPServiceInterface(self.ServiceGroupID, nil)
		InitBuf = C.Star_SRPBasic_GetParaPkgInterface(BasicSRPInterface)
		StarParaPkg_FromTuple_Sub(args, InitBuf, BasicSRPInterface, Index, SRPInterface)
	}
	SRPInterface = GetSRPServiceInterfaceEx(self.ServiceGroupID, &self.ObjectID)
	if SRPInterface == nil {
		S := C.CString("Get Interface Error")
		GoPrintError(C.VSFAULT_WARNING, S)
		C.free((unsafe.Pointer)(S))
		C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(AttributeChangeString))
		if InitBuf != nil {
			C.Star_SRPParaPkg_Release(InitBuf)
		}
		return nil
	}
	SRPObject = C.Star_SRPI_GetObject(SRPInterface, &self.ObjectID)
	if SRPObject == nil {
		S := C.CString("Get Object Error")
		GoPrintError(C.VSFAULT_WARNING, S)
		C.free((unsafe.Pointer)(S))
		C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(AttributeChangeString))
		if InitBuf != nil {
			C.Star_SRPParaPkg_Release(InitBuf)
		}
		return nil
	}

	RetValue := SRPObject_CreateNewObject(SRPInterface, SRPObject, C.VSALLOCTYPE_LOCAL, (*C.VS_UUID)(C.NULL), 0, QueueAttrName, SRPParentObject, ObjectNameString, AttributeChangeString, InitBuf)
	if RetValue == nil {
		C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(AttributeChangeString))
		if InitBuf != nil {
			C.Star_SRPParaPkg_Release(InitBuf)
		}
		return nil
	}
	C.Star_SRPCS_FreeBuf(C.StarGo_SRPCoreShellInterface, (unsafe.Pointer)(AttributeChangeString))
	if InitBuf != nil {
		C.Star_SRPParaPkg_Release(InitBuf)
	}
	return ToStarObject(RetValue, SRPInterface, C.VS_TRUE)
}

func (selfobj *StarObject) Free() {
	var self *StarObjectBody
	var SRPInterface unsafe.Pointer
	var SRPObject unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	self = StarObjectClass_getstarcoredata(selfobj)
	SRPInterface = GetSRPServiceInterfaceEx(self.ServiceGroupID, &self.ObjectID)
	if SRPInterface == nil {
		return
	}
	SRPObject = C.Star_SRPI_GetObject(SRPInterface, &self.ObjectID)
	if SRPObject == nil {
		return
	}
	C.Star_SRPI_FreeObject(SRPInterface, SRPObject)
	_TermObject_Defer(self)
	return
}

func (selfobj *StarObject) Dispose() {
	var self *StarObjectBody
	var SRPInterface unsafe.Pointer
	var SRPObject unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	self = StarObjectClass_getstarcoredata(selfobj)
	SRPInterface = GetSRPServiceInterfaceEx(self.ServiceGroupID, &self.ObjectID)
	if SRPInterface == nil {
		return
	}
	SRPObject = C.Star_SRPI_GetObject(SRPInterface, &self.ObjectID)
	if SRPObject == nil {
		return
	}
	_TermObject_Defer(self)
	return
}

func (selfobj *StarObject) RawToParaPkg() *StarParaPkg {
	var self *StarObjectBody
	var SRPInterface unsafe.Pointer
	var SRPObject unsafe.Pointer
	var ParaPkg unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}
	self = StarObjectClass_getstarcoredata(selfobj)
	SRPInterface = GetSRPServiceInterfaceEx(self.ServiceGroupID, &self.ObjectID)
	if SRPInterface == nil {
		return nil
	}
	SRPObject = C.Star_SRPI_GetObject(SRPInterface, &self.ObjectID)
	if SRPObject == nil {
		return nil
	}
	ParaPkg = C.Star_SRPI_RawToParaPkg(SRPInterface, SRPObject)
	if ParaPkg == nil {
		return nil
	}
	return ToStarParaPkg(ParaPkg, self.ServiceGroupID, C.VS_FALSE) //--not create by self;
}

func (selfobj *StarObject) DeferFree() {
	var self *StarObjectBody
	var SRPInterface unsafe.Pointer
	var SRPObject unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return
	}
	self = StarObjectClass_getstarcoredata(selfobj)
	SRPInterface = GetSRPServiceInterfaceEx(self.ServiceGroupID, &self.ObjectID)
	if SRPInterface == nil {
		return
	}
	SRPObject = C.Star_SRPI_GetObject(SRPInterface, &self.ObjectID)
	if SRPObject == nil {
		return
	}
	_TermObject_Defer(self)
	C.Star_SRPI_DeferFreeObject(SRPInterface, SRPObject)
	return
}

func (selfobj *StarObject) IsInFree() bool {
	var self *StarObjectBody
	var SRPInterface unsafe.Pointer
	var SRPObject unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	self = StarObjectClass_getstarcoredata(selfobj)
	SRPInterface = GetSRPServiceInterfaceEx(self.ServiceGroupID, &self.ObjectID)
	if SRPInterface == nil {
		return false
	}
	SRPObject = C.Star_SRPI_GetObject(SRPInterface, &self.ObjectID)
	if SRPObject == nil {
		return false
	}
	return FROMVS_BOOL(C.Star_SRPI_IsObjectInFree(SRPInterface, SRPObject))
}

func (selfobj *StarObject) GetSourceScript() int {
	var self *StarObjectBody
	var SRPInterface unsafe.Pointer
	var SRPObject unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return -1
	}
	self = StarObjectClass_getstarcoredata(selfobj)
	SRPInterface = GetSRPServiceInterfaceEx(self.ServiceGroupID, &self.ObjectID)
	if SRPInterface == nil {
		return -1
	}
	SRPObject = C.Star_SRPI_GetObject(SRPInterface, &self.ObjectID)
	if SRPObject == nil {
		return -1
	}
	return (int)(C.Star_SRPI_GetSourceScript(SRPInterface, SRPObject))
}

func (selfobj *StarObject) GetRefEx() int {
	var self *StarObjectBody
	var SRPInterface unsafe.Pointer
	var SRPObject unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	self = StarObjectClass_getstarcoredata(selfobj)
	SRPInterface = GetSRPServiceInterfaceEx(self.ServiceGroupID, &self.ObjectID)
	if SRPInterface == nil {
		return 0
	}
	SRPObject = C.Star_SRPI_GetObject(SRPInterface, &self.ObjectID)
	if SRPObject == nil {
		return 0
	}
	return (int)(C.Star_SRPI_GetRefEx(SRPInterface, SRPObject))
}

func (selfobj *StarObject) GetRefInfo() string {
	var self *StarObjectBody
	var SRPInterface unsafe.Pointer
	var SRPObject unsafe.Pointer
	var CharPtr *C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return ""
	}
	self = StarObjectClass_getstarcoredata(selfobj)
	SRPInterface = GetSRPServiceInterfaceEx(self.ServiceGroupID, &self.ObjectID)
	if SRPInterface == nil {
		return ""
	}
	SRPObject = C.Star_SRPI_GetObject(SRPInterface, &self.ObjectID)
	if SRPObject == nil {
		return ""
	}
	CharPtr = C.Star_SRPI_GetRefInfo(SRPInterface, SRPObject)
	if CharPtr == nil {
		return ""
	}
	return SRPGoSetStr(CharPtr, false)
}

func (selfobj *StarObject) IsValid() bool {
	var self *StarObjectBody
	var SRPInterface unsafe.Pointer
	var SRPObject unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	self = StarObjectClass_getstarcoredata(selfobj)
	SRPInterface = GetSRPServiceInterfaceEx(self.ServiceGroupID, &self.ObjectID)
	if SRPInterface == nil {
		return false
	}
	SRPObject = C.Star_SRPI_GetObject(SRPInterface, &self.ObjectID)
	if SRPObject == nil {
		return false
	}
	return true
}

func (selfobj *StarObject) GetLastError() int {
	var self *StarObjectBody
	var SRPInterface unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return 0
	}
	self = StarObjectClass_getstarcoredata(selfobj)
	SRPInterface = GetSRPServiceInterfaceEx(self.ServiceGroupID, &self.ObjectID)
	if SRPInterface == nil {
		return 0
	}
	return (int)(C.Star_SRPI_GetLastError(SRPInterface))
}

func (selfobj *StarObject) GetLastErrorInfo() string {
	var self *StarObjectBody
	var SRPInterface unsafe.Pointer
	var LineIndex C.VS_UINT32
	var SourceName *C.VS_CHAR
	var TextBuf *C.VS_CHAR

	if C.StarGo_SRPControlInterface == C.NULL {
		return ""
	}
	if C.StarGo_SRPControlInterface == C.NULL {
		return ""
	}
	self = StarObjectClass_getstarcoredata(selfobj)
	SRPInterface = GetSRPServiceInterfaceEx(self.ServiceGroupID, &self.ObjectID)
	if SRPInterface == nil {
		return ""
	}
	TextBuf = C.Star_SRPI_GetLastErrorInfo(SRPInterface, &LineIndex, &SourceName)
	return fmt.Sprintf("[%s:%d]%s", C.GoString(SourceName), LineIndex, SRPGoSetStr(TextBuf, true))
}

func (selfobj *StarObject) RegScriptProc_P(ScriptName string, CallBackProc func(CleGroup *StarSrvGroup, CleService *StarService, CleObject *StarObject, Paras []interface{}) interface{}) {
	selfobj.Set(ScriptName, CallBackProc)
}

func (selfobj *StarObject) ReleaseOwnerEx() bool {
	var self *StarObjectBody
	var SRPInterface unsafe.Pointer
	var SRPObject unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	self = StarObjectClass_getstarcoredata(selfobj)
	SRPInterface = GetSRPServiceInterfaceEx(self.ServiceGroupID, &self.ObjectID)
	if SRPInterface == nil {
		return false
	}
	SRPObject = C.Star_SRPI_GetObject(SRPInterface, &self.ObjectID)
	if SRPObject == nil {
		return false
	}
	if GoSRPIsObjectGlobalRef(self.ServiceGroupID, &self.ObjectID) == false {
		return false
	}
	return FROMVS_BOOL(C.Star_SRPI_ReleaseOwnerExForScript(SRPInterface, Const_GoString /*"go"*/, SRPObject))
}

func (selfobj *StarObject) IsSLock() bool {
	var self *StarObjectBody
	var SRPInterface unsafe.Pointer
	var SRPObject unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return false
	}
	self = StarObjectClass_getstarcoredata(selfobj)
	SRPInterface = GetSRPServiceInterfaceEx(self.ServiceGroupID, &self.ObjectID)
	if SRPInterface == nil {
		return false
	}
	SRPObject = C.Star_SRPI_GetObject(SRPInterface, &self.ObjectID)
	if SRPObject == nil {
		return false
	}
	return GoSRPIsObjectGlobalRef(self.ServiceGroupID, &self.ObjectID)
}

//export GoSRPObject_ScriptCallBack
func GoSRPObject_ScriptCallBack(L unsafe.Pointer) (FunctionResult C.VS_INT32) {
	var self *StarObjectBody
	var SRPInterface unsafe.Pointer
	var Object unsafe.Pointer
	var ObjectTemp *StarObject
	var ServiceGroupID C.VS_ULONG
	var ScriptName *C.VS_CHAR
	var n, i C.VS_INT32

	ServiceGroupID = C.Star_SRPControl_LuaGetInt(C.StarGo_SRPControlInterface, L, C.Star_SRPControl_LuaUpValueIndex(C.StarGo_SRPControlInterface, L, 1))
	ObjectTemp, _ = RefToGoObject(C.Star_SRPControl_LuaGetUWord(C.StarGo_SRPControlInterface, L, C.Star_SRPControl_LuaUpValueIndex(C.StarGo_SRPControlInterface, L, 2))).(*StarObject)
	if ObjectTemp == nil {
		return 0
	}
	self = StarObjectClass_getstarcoredata(ObjectTemp)
	SRPInterface = GetSRPServiceInterface(ServiceGroupID, C.NULL)
	if SRPInterface == nil {
		return 0
	}
	ScriptName = C.Star_SRPI_LuaToString(SRPInterface, C.Star_SRPI_LuaUpValueIndex(SRPInterface, 3))
	Object = C.Star_SRPI_LuaToObject(SRPInterface, 1)

	SRPInterface = GetSRPServiceInterface(ServiceGroupID, Object)
	if SRPInterface == nil {
		return 0
	}
	if C.Star_SRPI_IsRemoteCall(SRPInterface, Object) == C.VS_TRUE {
		C.Star_SRPI_SetRetCode(SRPInterface, Object, C.VSRCALL_PARAERROR)
	}
	//---create parameter
	if C.Star_SRPI_LuaGetTop(SRPInterface) == 0 {
		S := C.CString(fmt.Sprintf("Call Object[%s] GoFunction [%s] Error Parameter Number ", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), C.GoString(ScriptName)))
		GoPrintError(C.VSFAULT_WARNING, S)
		C.free((unsafe.Pointer)(S))
		return 0
	}
	n = C.Star_SRPI_LuaGetTop(SRPInterface) - 1
	InterfaceCallObj, ok := self.Table[C.GoString(ScriptName)]
	if ok {
		var ObjectTemp2 interface{}
		var LuaToJavaResult C.VS_BOOL
		ScriptParaArray := make([]interface{}, n)
		for i = (C.VS_INT32)(0); i < n; i++ {
			ObjectTemp2 = LuaToGoObject(0, SRPInterface, i+2, &LuaToJavaResult)
			if LuaToJavaResult == C.VS_FALSE {
				S := C.CString(fmt.Sprintf("Call Object[%s] GoFunction [%s] Error,Parameter[%d] failed", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), C.GoString(ScriptName), i))
				GoPrintError(C.VSFAULT_WARNING, S)
				C.free((unsafe.Pointer)(S))
				return 0
			}
			ScriptParaArray[i] = ObjectTemp2
		}
		defer func() {
			if err := recover(); err != nil {
				S := C.CString(fmt.Sprintf("Call Object[%s] GoFunction [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), C.GoString(ScriptName)))
				GoPrintError(C.VSFAULT_WARNING, S)
				C.free((unsafe.Pointer)(S))
				FunctionResult = 0
				return
			}
		}()

		StarSrvGroup_ObjectTemp := GoSRPQuerySrvGroup(ServiceGroupID)
		StarService_ObjectTemp := GoSRPQueryService(ServiceGroupID, Object)
		if StarSrvGroup_ObjectTemp == nil || StarService_ObjectTemp == nil {
			return 0
		}
		RetValue := InterfaceCallObj(StarSrvGroup_ObjectTemp, StarService_ObjectTemp, ObjectTemp, ScriptParaArray)
		C.Star_SRPI_SetRetCode(SRPInterface, Object, C.VSRCALL_OK)
		if RetValue == nil {
			return 0
		} else {
			n = C.Star_SRPI_LuaGetTop(SRPInterface)
			GoObjectToLua(SRPInterface, RetValue, false)
			return C.Star_SRPI_LuaGetTop(SRPInterface) - n
		}
	}
	return 0
}

func (selfobj *StarObject) AttachRawObject(NewObject interface{}, IsClass bool /*is ignored*/) *StarObject {
	var self *StarObjectBody
	var SRPInterface unsafe.Pointer
	var SRPObject unsafe.Pointer

	if C.StarGo_SRPControlInterface == C.NULL {
		return nil
	}
	self = StarObjectClass_getstarcoredata(selfobj)
	SRPInterface = GetSRPServiceInterfaceEx(self.ServiceGroupID, &self.ObjectID)
	if SRPInterface == nil {
		return nil
	}
	SRPObject = C.Star_SRPI_GetObject(SRPInterface, &self.ObjectID)
	if SRPObject == nil {
		return nil
	}
	if VSScript_GoRawContext_WrapObject(SRPInterface, self.ServiceGroupID, SRPObject, NewObject, TOVS_BOOL(IsClass)) == C.VS_TRUE {
		return selfobj
	} else {
		return nil
	}
}

func VSScript_GoRawContext_WrapObject(SRPInterface unsafe.Pointer, ServiceGroupIndex C.VS_ULONG, Object unsafe.Pointer, o interface{}, IsClass C.VS_BOOL) C.VS_BOOL {
	var GoRawContext C.struct_StructOfGoRawContext
	var GoRawContextPtr *C.struct_StructOfGoRawContext

	if o == nil {
		return C.VS_FALSE
	}
	/*
		ref_typ := reflect.TypeOf(o)
		if ref_typ.Kind() != reflect.Ptr || ref_typ.Elem().Kind() != reflect.Struct {
			S := C.CString("wrapobject failed, Object is not struct pointer")
			GoPrintError(C.VSFAULT_WARNING, S)
			C.free((unsafe.Pointer)(S))
			return C.VS_FALSE
		}
	*/
	GoRawContextPtr = (*C.struct_StructOfGoRawContext)(C.Star_SRPI_GetRawContextBuf(SRPInterface, Object, Const_GoString /*"go"*/))
	if GoRawContextPtr == nil {
		C.memset((unsafe.Pointer)(&GoRawContext), 0, (C.size_t)(C.stargo_SizeOfStructOfGoRawContext()))
		GoRawContext.ContextHeader.IsGlobalSpace = C.VS_FALSE
		GoRawContext.RefItem = g_GoRawContextRefManager.Alloc(o, Object, SRPInterface, IsClass)
		GoRawContext.ContextHeader.IsClass = IsClass
		GoRawContext.Para = (*C.struct_StructOfGoRawContext_Para)(C.stargo_MallocStructOfGoRawContext_Para())
		GoRawContext.Para.object = Object
		GoRawContext.Para.ServiceGroupIndex = ServiceGroupIndex
		C.Star_SRPI_CreateRawContextBuf(SRPInterface, Object, Const_GoString /*"go"*/, (*C.VS_INT8)((unsafe.Pointer)(&GoRawContext)), C.stargo_SizeOfStructOfGoRawContext())
		//---need hook script general functions
		C.Star_SRPI_RegLuaFunc(SRPInterface, Object, (*C.VS_CHAR)(C.NULL), (unsafe.Pointer)(C.stargo_VSScript_GoRawContext_GeneralFunction), C.stargo_PointerToUWord((unsafe.Pointer)(GoRawContext.Para)))
		C.Star_SRPI_RegLuaFuncFilter(SRPInterface, Object, (C.VS_LuaFuncFilterProc)(C.stargo_VSScript_GoRawContext_LuaFuncFilter), C.stargo_PointerToUWord((unsafe.Pointer)(GoRawContext.Para)))
		C.Star_SRPI_RegLuaGetValueFunc(SRPInterface, Object, (C.VS_LuaGetValueProc)(C.stargo_VSScript_GoRawContext_RegGetValue), C.stargo_PointerToUWord((unsafe.Pointer)(GoRawContext.Para)))
		C.Star_SRPI_RegRawLuaSetValueFunc(SRPInterface, Object, (C.VS_LuaSetValueProc)(C.stargo_VSScript_GoRawContext_RegSetValue), C.stargo_PointerToUWord((unsafe.Pointer)(GoRawContext.Para)))
		C.Star_SRPI_RegNewFunctionCallBack(SRPInterface, Object, (C.VS_NewFunctionCallBackProc)(C.stargo_VSScript_GoRawContext_NewFunctionCallBack), C.stargo_PointerToUWord((unsafe.Pointer)(GoRawContext.Para)))
	} else {
		if GoRawContextPtr.RefItem != nil {
			g_GoRawContextRefManager.Free(GoRawContextPtr.RefItem)
		}
		GoRawContextPtr.RefItem = g_GoRawContextRefManager.Alloc(o, Object, SRPInterface, IsClass)
		GoRawContextPtr.ContextHeader.IsGlobalSpace = C.VS_FALSE
		GoRawContextPtr.ContextHeader.IsClass = IsClass
	}
	return C.VS_TRUE
}

//export GoRawContext_LuaFuncFilter
func GoRawContext_LuaFuncFilter(object unsafe.Pointer, ForWhichObject unsafe.Pointer, FuncName *C.VS_CHAR, Para C.VS_UWORD) C.VS_BOOL {
	var SRPInterface unsafe.Pointer
	var GoRawContext *C.struct_StructOfGoRawContext
	var GoRawContext_Para *C.struct_StructOfGoRawContext_Para
	var GoFuncName string
	var thisobject interface{}

	GoRawContext_Para = (*C.struct_StructOfGoRawContext_Para)(C.stargo_ToPointer(Para))
	SRPInterface = GetSRPServiceInterface(GoRawContext_Para.ServiceGroupIndex, object)
	if SRPInterface == nil {
		S := C.CString("call RawFunction failed, may be InitRaw for go is not called.")
		GoPrintError(C.VSFAULT_WARNING, S)
		C.free((unsafe.Pointer)(S))
		return C.VS_FALSE
	}
	//BasicSRPInterface = GoSRPGetBasicSRPInterface(C.Star_SRPI_GetServiceGroupID(SRPInterface))
	GoRawContext = (*C.struct_StructOfGoRawContext)(C.Star_SRPI_GetRawContextBuf(SRPInterface, GoRawContext_Para.object, Const_GoString /*"go"*/))
	if GoRawContext == nil {
		return C.VS_FALSE
	}
	if GoRawContext.ContextHeader.IsGlobalSpace == C.VS_TRUE {
		return C.VS_FALSE
	}
	GoFuncName = C.GoString(FuncName)
	if (*FuncName) == '_' && strings.Compare(C.VS_OBJECTTOSTRINGFUNCNAME, GoFuncName) == 0 {
		return C.VS_TRUE
	}
	thisobject = RefToGoObject(GoRawContext.RefItem.o)
	if thisobject == nil {
		return C.VS_FALSE
	}

	//---method of object
	switch thisobject.(type) {
	default:
		ref_typ := reflect.TypeOf(thisobject)
		if ref_typ.Kind() == reflect.Ptr && ref_typ.Elem().Kind() == reflect.Struct {
			if (*FuncName) < 'A' || (*FuncName) > 'Z' { /*--private value--*/
				return C.VS_FALSE
			}
			v := reflect.ValueOf(thisobject).MethodByName(GoFuncName)
			if !v.IsValid() {
				return C.VS_FALSE
			}
			return C.VS_TRUE
		} else if ref_typ.Kind() == reflect.Func {
			v := reflect.ValueOf(thisobject)
			if !v.IsValid() {
				return C.VS_FALSE
			}
			return C.VS_TRUE
		} else {
			return C.VS_FALSE
		}
	}
	return C.VS_FALSE
}

func VSScript_GoRawContext_ReturnValue(Object interface{}, BasicSRPInterface unsafe.Pointer, SRPInterface unsafe.Pointer) C.VS_INT32 {
	if Object == nil {
		C.Star_SRPI_LuaPushNil(SRPInterface)
		return 1
	}
	switch Object.(type) {
	case bool, int8, uint8, int16, uint16, int32, uint32, int64, uint64, int, uint, string, float32, float64:
		GoObjectToLua(SRPInterface, Object, true)
		return 1
	case []int8, []uint8:
		GoObjectToLua(SRPInterface, Object, true)
		return 1
	case *StarParaPkg, *StarBinBuf, *StarSXml, *StarObject:
		return 1
	}
	var NewSRPObject unsafe.Pointer
	NewSRPObject = g_GoRawContextRefManager.GetObject(Object, SRPInterface, C.VS_FALSE)
	C.Star_SRPI_LuaPushObject(SRPInterface, NewSRPObject)
	C.Star_SRPI_DelRefEx(SRPInterface, NewSRPObject)
	return 1
}

func GoRawContext_GeneralFunction_ToType(in reflect.Type) int {
	switch in.Kind() {
	case reflect.Bool:
		return GO_TYPE_BOOL
	case reflect.Int:
		return GO_TYPE_INT
	case reflect.Int8:
		return GO_TYPE_INT8
	case reflect.Int16:
		return GO_TYPE_INT16
	case reflect.Int32:
		return GO_TYPE_INT32
	case reflect.Int64:
		return GO_TYPE_INT64
	case reflect.Uint:
		return GO_TYPE_UINT

	case reflect.Uint8:
		return GO_TYPE_UINT8
	case reflect.Uint16:
		return GO_TYPE_UINT16
	case reflect.Uint32:
		return GO_TYPE_UINT32
	case reflect.Uint64:
		return GO_TYPE_UINT64

	case reflect.Float32:
		return GO_TYPE_FLOAT32
	case reflect.Float64:
		return GO_TYPE_FLOAT64

	case reflect.Interface:
		return GO_TYPE_INTERFACE
	case reflect.String:
		return GO_TYPE_STRING
	case reflect.Slice:
		switch in.Elem().Kind() {
		case reflect.Bool:
			return GO_TYPE_BOOL_SLICE
		case reflect.Int:
			return GO_TYPE_INT_SLICE
		case reflect.Int8:
			return GO_TYPE_INT8_SLICE
		case reflect.Int16:
			return GO_TYPE_INT16_SLICE
		case reflect.Int32:
			return GO_TYPE_INT32_SLICE
		case reflect.Int64:
			return GO_TYPE_INT64_SLICE
		case reflect.Uint:
			return GO_TYPE_UINT_SLICE

		case reflect.Uint8:
			return GO_TYPE_UINT8_SLICE
		case reflect.Uint16:
			return GO_TYPE_UINT16_SLICE
		case reflect.Uint32:
			return GO_TYPE_UINT32_SLICE
		case reflect.Uint64:
			return GO_TYPE_UINT64_SLICE

		case reflect.Float32:
			return GO_TYPE_FLOAT32_SLICE
		case reflect.Float64:
			return GO_TYPE_FLOAT64_SLICE

		case reflect.Interface:
			return GO_TYPE_INTERFACE_SLICE
		case reflect.String:
			return GO_TYPE_STRING_SLICE
		default:
			return GO_TYPE_INTERFACE_SLICE
		}
	default:
		return GO_TYPE_NONE
	}
}

//export GoRawContext_GeneralFunction
func GoRawContext_GeneralFunction(L unsafe.Pointer) (FunctionResult C.VS_INT32) {
	var SRPInterface unsafe.Pointer
	var ClassGoRawContext, GoRawContext *C.struct_StructOfGoRawContext
	var GoRawContext_Para *C.struct_StructOfGoRawContext_Para
	var ClassObject unsafe.Pointer
	var ScriptName *C.VS_CHAR
	var GoScriptName string
	var ServiceGroupID C.VS_ULONG
	var SRPObject, ForWhichClassObject unsafe.Pointer
	var BasicSRPInterface unsafe.Pointer
	var n, i int
	var LuaToGoResult C.VS_BOOL
	var CallPara []reflect.Value

	ServiceGroupID = C.Star_SRPControl_LuaGetInt(C.StarGo_SRPControlInterface, L, C.Star_SRPControl_LuaUpValueIndex(C.StarGo_SRPControlInterface, L, 1))
	SRPInterface = GetSRPServiceInterface(ServiceGroupID, C.NULL)
	if SRPInterface == nil {
		S := C.CString("call RawFunction failed, may be InitRaw for go is not called.")
		GoPrintError(C.VSFAULT_WARNING, S)
		C.free((unsafe.Pointer)(S))
		return 0
	}
	BasicSRPInterface = GoSRPGetBasicSRPInterface(ServiceGroupID)
	ScriptName = C.Star_SRPI_LuaToString(SRPInterface, C.Star_SRPI_LuaUpValueIndex(SRPInterface, 3))
	GoScriptName = C.GoString(ScriptName)
	GoRawContext_Para = (*C.struct_StructOfGoRawContext_Para)(C.stargo_ToPointer(C.Star_SRPI_LuaToUWord(SRPInterface, C.Star_SRPI_LuaUpValueIndex(SRPInterface, 2))))
	ClassObject = GoRawContext_Para.object
	ClassGoRawContext = (*C.struct_StructOfGoRawContext)(C.Star_SRPI_GetRawContextBuf(SRPInterface, ClassObject, Const_GoString /*"go"*/))
	if ClassGoRawContext == nil {
		return 0
	}
	SRPObject = C.Star_SRPI_LuaToObject(SRPInterface, 1)
	if SRPObject == nil {
		S := C.CString(fmt.Sprintf("call raw go object function [%s] failed, should use [lua::object:%s(...)]", GoScriptName, GoScriptName))
		GoPrintError(C.VSFAULT_WARNING, S)
		C.free((unsafe.Pointer)(S))
		return 0
	}
	ForWhichClassObject = SRPObject
	GoRawContext = (*C.struct_StructOfGoRawContext)(C.Star_SRPI_GetRawContextBuf(SRPInterface, ForWhichClassObject, Const_GoString /*"go"*/))
	for {
		if GoRawContext != nil {
			break
		}
		ForWhichClassObject = C.Star_SRPI_GetClass(SRPInterface, ForWhichClassObject)
		if ForWhichClassObject == nil {
			break
		}
		GoRawContext = (*C.struct_StructOfGoRawContext)(C.Star_SRPI_GetRawContextBuf(SRPInterface, ForWhichClassObject, Const_GoString /*"go"*/))
	}
	if C.Star_SRPI_IsRemoteCall(SRPInterface, SRPObject) == C.VS_TRUE {
		C.Star_SRPI_SetRetCode(SRPInterface, SRPObject, C.VSRCALL_PARAERROR)
	}

	if GoRawContext.ContextHeader.IsGlobalSpace == C.VS_TRUE {
		return 0
	}
	//---------------------------------------------------------------------------------------------------------------
	thisobject := RefToGoObject(GoRawContext.RefItem.o)
	if thisobject == nil {
		return 0 /* object is released*/
	}
	if C.Star_SRPI_LuaGetTop(SRPInterface) == 0 {
		S := C.CString(fmt.Sprintf("Call Object[%s] JavaFunction [%s] Error Parameter Number", C.GoString(C.Star_SRPI_GetName(SRPInterface, SRPObject)), GoScriptName))
		GoPrintError(C.VSFAULT_WARNING, S)
		C.free((unsafe.Pointer)(S))
		return 0
	}
	/*-----------VS_OBJECTTOSTRINGFUNCNAME------------*/
	if (*ScriptName) == '_' && strings.Compare(GoScriptName, C.VS_OBJECTTOSTRINGFUNCNAME) == 0 {
		if GoRawContext.ContextHeader.IsClass == C.VS_TRUE { //--class does not support tostring
			return 0
		}
		RetValue := fmt.Sprint(thisobject)
		C.Star_SRPI_SetRetCode(SRPInterface, SRPObject, C.VSRCALL_OK)
		VSScript_GoRawContext_ReturnValue(RetValue, BasicSRPInterface, SRPInterface)
		return 1
	}
	//---method of object
	var v reflect.Value

	switch thisobject.(type) {
	default:
		ref_typ := reflect.TypeOf(thisobject)
		if ref_typ.Kind() == reflect.Ptr && ref_typ.Elem().Kind() == reflect.Struct {
			if (*ScriptName) < 'A' || (*ScriptName) > 'Z' { /*--private value--*/
				S := C.CString(fmt.Sprintf("Call Object[%s] GoFunction [%s] Error, Private Function", C.GoString(C.Star_SRPI_GetName(SRPInterface, SRPObject)), GoScriptName))
				GoPrintError(C.VSFAULT_WARNING, S)
				C.free((unsafe.Pointer)(S))
				return 0
			} else {
				v = reflect.ValueOf(thisobject).MethodByName(GoScriptName)
				if !v.IsValid() {
					return 0
				}
			}
		} else if ref_typ.Kind() == reflect.Func {
			v = reflect.ValueOf(thisobject)
			if !v.IsValid() {
				return 0
			}
		} else {
			S := C.CString(fmt.Sprintf("Call Object[%s] GoFunction [%s] Error, Not Found", C.GoString(C.Star_SRPI_GetName(SRPInterface, SRPObject)), GoScriptName))
			GoPrintError(C.VSFAULT_WARNING, S)
			C.free((unsafe.Pointer)(S))
			return 0
		}
	}

	n = (int)(C.Star_SRPI_LuaGetTop(SRPInterface) - 1)
	FuncParamNum := v.Type().NumIn()

	if n == FuncParamNum {
		CallPara = make([]reflect.Value, n)
		for i = 0; i < n; i++ {
			pt := v.Type().In(i)
			s := LuaToGoObject(GoRawContext_GeneralFunction_ToType(pt), SRPInterface, (C.VS_INT32)(i+2), &LuaToGoResult)
			if LuaToGoResult == C.VS_FALSE {
				S := C.CString(fmt.Sprintf("Call Object[%s] GoFunction [%s] Error Parameter [%d]", C.GoString(C.Star_SRPI_GetName(SRPInterface, SRPObject)), GoScriptName, i))
				GoPrintError(C.VSFAULT_WARNING, S)
				C.free((unsafe.Pointer)(S))
				return 0
			}
			CallPara[i] = reflect.ValueOf(s)
		}
	} else if n > FuncParamNum && FuncParamNum-1 >= 0 {
		pt := v.Type().In(FuncParamNum - 1) /*--last parameter--*/
		if pt.Kind() == reflect.Slice {     /*pt.Kind() == reflect.Slice  pt.Elem().Kind() */
			CallPara = make([]reflect.Value, FuncParamNum)
			for i = 0; i < FuncParamNum-1; i++ {
				pt := v.Type().In(i)
				s := LuaToGoObject(GoRawContext_GeneralFunction_ToType(pt), SRPInterface, (C.VS_INT32)(i+2), &LuaToGoResult)
				if LuaToGoResult == C.VS_FALSE {
					S := C.CString(fmt.Sprintf("Call Object[%s] GoFunction [%s] Error Parameter [%d]", C.GoString(C.Star_SRPI_GetName(SRPInterface, SRPObject)), GoScriptName, i))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return 0
				}
				CallPara[i] = reflect.ValueOf(s)
			}
			/*--process last parameter--*/
			var LastValResult bool = true
			switch pt.Elem().Kind() {
			case reflect.Bool:
				lastval := make([]bool, n-FuncParamNum+1)
				for i = FuncParamNum - 1; i < n; i++ {
					s, _ := LuaToGoObject(GO_TYPE_BOOL, SRPInterface, (C.VS_INT32)(i+2), &LuaToGoResult).(bool)
					if LuaToGoResult == C.VS_FALSE {
						LastValResult = false
						break
					}
					lastval[i-FuncParamNum+1] = s
				}
				CallPara[FuncParamNum-1] = reflect.ValueOf(lastval)
			case reflect.Int:
				lastval := make([]int, n-FuncParamNum+1)
				for i = FuncParamNum - 1; i < n; i++ {
					s, _ := LuaToGoObject(GO_TYPE_INT, SRPInterface, (C.VS_INT32)(i+2), &LuaToGoResult).(int)
					if LuaToGoResult == C.VS_FALSE {
						LastValResult = false
						break
					}
					lastval[i-FuncParamNum+1] = s
				}
				CallPara[FuncParamNum-1] = reflect.ValueOf(lastval)
			case reflect.Int8:
				lastval := make([]int8, n-FuncParamNum+1)
				for i = FuncParamNum - 1; i < n; i++ {
					s, _ := LuaToGoObject(GO_TYPE_INT8, SRPInterface, (C.VS_INT32)(i+2), &LuaToGoResult).(int8)
					if LuaToGoResult == C.VS_FALSE {
						LastValResult = false
						break
					}
					lastval[i-FuncParamNum+1] = s
				}
				CallPara[FuncParamNum-1] = reflect.ValueOf(lastval)
			case reflect.Int16:
				lastval := make([]int16, n-FuncParamNum+1)
				for i = FuncParamNum - 1; i < n; i++ {
					s, _ := LuaToGoObject(GO_TYPE_INT16, SRPInterface, (C.VS_INT32)(i+2), &LuaToGoResult).(int16)
					if LuaToGoResult == C.VS_FALSE {
						LastValResult = false
						break
					}
					lastval[i-FuncParamNum+1] = s
				}
				CallPara[FuncParamNum-1] = reflect.ValueOf(lastval)
			case reflect.Int32:
				lastval := make([]int32, n-FuncParamNum+1)
				for i = FuncParamNum - 1; i < n; i++ {
					s, _ := LuaToGoObject(GO_TYPE_INT32, SRPInterface, (C.VS_INT32)(i+2), &LuaToGoResult).(int32)
					if LuaToGoResult == C.VS_FALSE {
						LastValResult = false
						break
					}
					lastval[i-FuncParamNum+1] = s
				}
				CallPara[FuncParamNum-1] = reflect.ValueOf(lastval)
			case reflect.Int64:
				lastval := make([]int64, n-FuncParamNum+1)
				for i = FuncParamNum - 1; i < n; i++ {
					s, _ := LuaToGoObject(GO_TYPE_INT64, SRPInterface, (C.VS_INT32)(i+2), &LuaToGoResult).(int64)
					if LuaToGoResult == C.VS_FALSE {
						LastValResult = false
						break
					}
					lastval[i-FuncParamNum+1] = s
				}
				CallPara[FuncParamNum-1] = reflect.ValueOf(lastval)
			case reflect.Uint:
				lastval := make([]uint, n-FuncParamNum+1)
				for i = FuncParamNum - 1; i < n; i++ {
					s, _ := LuaToGoObject(GO_TYPE_UINT, SRPInterface, (C.VS_INT32)(i+2), &LuaToGoResult).(uint)
					if LuaToGoResult == C.VS_FALSE {
						LastValResult = false
						break
					}
					lastval[i-FuncParamNum+1] = s
				}
				CallPara[FuncParamNum-1] = reflect.ValueOf(lastval)
			case reflect.Uint8:
				lastval := make([]uint8, n-FuncParamNum+1)
				for i = FuncParamNum - 1; i < n; i++ {
					s, _ := LuaToGoObject(GO_TYPE_UINT8, SRPInterface, (C.VS_INT32)(i+2), &LuaToGoResult).(uint8)
					if LuaToGoResult == C.VS_FALSE {
						LastValResult = false
						break
					}
					lastval[i-FuncParamNum+1] = s
				}
				CallPara[FuncParamNum-1] = reflect.ValueOf(lastval)
			case reflect.Uint16:
				lastval := make([]uint16, n-FuncParamNum+1)
				for i = FuncParamNum - 1; i < n; i++ {
					s, _ := LuaToGoObject(GO_TYPE_UINT16, SRPInterface, (C.VS_INT32)(i+2), &LuaToGoResult).(uint16)
					if LuaToGoResult == C.VS_FALSE {
						LastValResult = false
						break
					}
					lastval[i-FuncParamNum+1] = s
				}
				CallPara[FuncParamNum-1] = reflect.ValueOf(lastval)
			case reflect.Uint32:
				lastval := make([]uint32, n-FuncParamNum+1)
				for i = FuncParamNum - 1; i < n; i++ {
					s, _ := LuaToGoObject(GO_TYPE_UINT32, SRPInterface, (C.VS_INT32)(i+2), &LuaToGoResult).(uint32)
					if LuaToGoResult == C.VS_FALSE {
						LastValResult = false
						break
					}
					lastval[i-FuncParamNum+1] = s
				}
				CallPara[FuncParamNum-1] = reflect.ValueOf(lastval)
			case reflect.Uint64:
				lastval := make([]uint64, n-FuncParamNum+1)
				for i = FuncParamNum - 1; i < n; i++ {
					s, _ := LuaToGoObject(GO_TYPE_UINT64, SRPInterface, (C.VS_INT32)(i+2), &LuaToGoResult).(uint64)
					if LuaToGoResult == C.VS_FALSE {
						LastValResult = false
						break
					}
					lastval[i-FuncParamNum+1] = s
				}
				CallPara[FuncParamNum-1] = reflect.ValueOf(lastval)
			case reflect.Float32:
				lastval := make([]float32, n-FuncParamNum+1)
				for i = FuncParamNum - 1; i < n; i++ {
					s, _ := LuaToGoObject(GO_TYPE_FLOAT32, SRPInterface, (C.VS_INT32)(i+2), &LuaToGoResult).(float32)
					if LuaToGoResult == C.VS_FALSE {
						LastValResult = false
						break
					}
					lastval[i-FuncParamNum+1] = s
				}
				CallPara[FuncParamNum-1] = reflect.ValueOf(lastval)
			case reflect.Float64:
				lastval := make([]float64, n-FuncParamNum+1)
				for i = FuncParamNum - 1; i < n; i++ {
					s, _ := LuaToGoObject(GO_TYPE_FLOAT64, SRPInterface, (C.VS_INT32)(i+2), &LuaToGoResult).(float64)
					if LuaToGoResult == C.VS_FALSE {
						LastValResult = false
						break
					}
					lastval[i-FuncParamNum+1] = s
				}
				CallPara[FuncParamNum-1] = reflect.ValueOf(lastval)
			case reflect.Interface:
				lastval := make([]interface{}, n-FuncParamNum+1)
				for i = FuncParamNum - 1; i < n; i++ {
					s := LuaToGoObject(GO_TYPE_INTERFACE, SRPInterface, (C.VS_INT32)(i+2), &LuaToGoResult)
					if LuaToGoResult == C.VS_FALSE {
						LastValResult = false
						break
					}
					lastval[i-FuncParamNum+1] = s
				}
				CallPara[FuncParamNum-1] = reflect.ValueOf(lastval)
			case reflect.String:
				lastval := make([]string, n-FuncParamNum+1)
				for i = FuncParamNum - 1; i < n; i++ {
					s, _ := LuaToGoObject(GO_TYPE_STRING, SRPInterface, (C.VS_INT32)(i+2), &LuaToGoResult).(string)
					if LuaToGoResult == C.VS_FALSE {
						LastValResult = false
						break
					}
					lastval[i-FuncParamNum+1] = s
				}
				CallPara[FuncParamNum-1] = reflect.ValueOf(lastval)
			default:
				LastValResult = false
			}
			if LastValResult == false {
				S := C.CString(fmt.Sprintf("Call Object[%s] GoFunction [%s] Error Parameter [%d]", C.GoString(C.Star_SRPI_GetName(SRPInterface, SRPObject)), GoScriptName, FuncParamNum-1))
				GoPrintError(C.VSFAULT_WARNING, S)
				C.free((unsafe.Pointer)(S))
				return 0
			}
		} else {
			S := C.CString(fmt.Sprintf("Call Object[%s] GoFunction [%s] Error Parameter Number", C.GoString(C.Star_SRPI_GetName(SRPInterface, SRPObject)), GoScriptName))
			GoPrintError(C.VSFAULT_WARNING, S)
			C.free((unsafe.Pointer)(S))
			return 0
		}
	} else if n == FuncParamNum-1 && FuncParamNum-2 >= 0 {
		pt := v.Type().In(FuncParamNum - 2)
		if pt.Kind() == reflect.Slice { //can accept nil
			CallPara = make([]reflect.Value, FuncParamNum)
			CallPara[FuncParamNum-1] = reflect.ValueOf(nil)
		} else {
			S := C.CString(fmt.Sprintf("Call Object[%s] GoFunction [%s] Error Parameter Number", C.GoString(C.Star_SRPI_GetName(SRPInterface, SRPObject)), GoScriptName))
			GoPrintError(C.VSFAULT_WARNING, S)
			C.free((unsafe.Pointer)(S))
			return 0
		}
	} else {
		S := C.CString(fmt.Sprintf("Call Object[%s] GoFunction [%s] Error Parameter Number", C.GoString(C.Star_SRPI_GetName(SRPInterface, SRPObject)), GoScriptName))
		GoPrintError(C.VSFAULT_WARNING, S)
		C.free((unsafe.Pointer)(S))
		return 0
	}
	/*--convert input parameter--*/
	defer func() {
		if err := recover(); err != nil {
			GS := fmt.Sprintf("Call Object[%s] GoFunction [%s] Error [%s]", C.GoString(C.Star_SRPI_GetName(SRPInterface, SRPObject)), GoScriptName, fmt.Sprint(err))
			S := C.CString(GS)
			GoPrintError(C.VSFAULT_WARNING, S)
			C.free((unsafe.Pointer)(S))
			FunctionResult = 0
			return
		}
	}()

	RetValue := v.Call(CallPara)

	if len(RetValue) <= 0 {
		C.Star_SRPI_SetRetCode(SRPInterface, SRPObject, C.VSRCALL_OK)
		return 0
	} else if len(RetValue) == 1 {
		VSScript_GoRawContext_ReturnValue(RetValue[0].Interface(), BasicSRPInterface, SRPInterface)
		C.Star_SRPI_SetRetCode(SRPInterface, SRPObject, C.VSRCALL_OK)
		return 1
	} else {
		S := make([]interface{}, len(RetValue), len(RetValue))
		for i, v := range RetValue {
			S[i] = v.Interface()
		}
		VSScript_GoRawContext_ReturnValue(S, BasicSRPInterface, SRPInterface)
		C.Star_SRPI_SetRetCode(SRPInterface, SRPObject, C.VSRCALL_OK)
		return 1
	}
	return 0
}

var TypeNameBuf [256]C.VS_CHAR

//export GoVSScript_GetRawContextType
func GoVSScript_GetRawContextType(Para C.VS_UWORD, ServiceGroupIndex C.VS_ULONG, object unsafe.Pointer) *C.VS_CHAR {
	var SRPInterface unsafe.Pointer
	var GoRawContext *C.struct_StructOfGoRawContext
	var ClassName *C.VS_CHAR

	SRPInterface = GetSRPServiceInterface(ServiceGroupIndex, object)
	if SRPInterface == nil {
		S := C.CString("call RawFunction failed, may be InitRaw for go is not called.")
		GoPrintError(C.VSFAULT_WARNING, S)
		C.free((unsafe.Pointer)(S))
		return (*C.VS_CHAR)(C.NULL)
	}
	GoRawContext = (*C.struct_StructOfGoRawContext)(C.Star_SRPI_GetRawContextBuf(SRPInterface, object, Const_GoString /*"go"*/))
	if GoRawContext == nil {
		return (*C.VS_CHAR)(C.NULL)
	}
	if GoRawContext.ContextHeader.IsGlobalSpace == C.VS_TRUE || GoRawContext.RefItem == nil || GoRawContext.RefItem.o == 0 {
		cstr := C.CString("global")
		C.strcpy((*C.VS_CHAR)((unsafe.Pointer)(&TypeNameBuf[0])), cstr)
		C.free(unsafe.Pointer(cstr))
		return (*C.VS_CHAR)((unsafe.Pointer)(&TypeNameBuf[0]))
	}
	thisobject := RefToGoObject(GoRawContext.RefItem.o)
	typ := reflect.TypeOf(thisobject)
	s := fmt.Sprint(typ)
	ClassName = SRPGoGetStr(s, false)
	C.strncpy((*C.VS_CHAR)((unsafe.Pointer)(&TypeNameBuf[0])), ClassName, 256)
	*C.stargo_GetCharByIndex((*C.VS_CHAR)((unsafe.Pointer)(&TypeNameBuf[0])), 255) = 0
	STARGO_SAFERELEASESTR(s, ClassName)
	return (*C.VS_CHAR)((unsafe.Pointer)(&TypeNameBuf[0]))
}

//export GoRawContext_RegGetValue
func GoRawContext_RegGetValue(Object unsafe.Pointer, ForWhichObject unsafe.Pointer, Name *C.VS_CHAR, Para C.VS_UWORD, GetAllRawAttributeFlag C.VS_BOOL) (FunctionResult C.VS_BOOL) {
	var BasicSRPInterface unsafe.Pointer
	var SRPInterface unsafe.Pointer
	var GoRawContext, WhichObjectGoRawContext *C.struct_StructOfGoRawContext
	var GoRawContext_Para *C.struct_StructOfGoRawContext_Para
	var ForWhichClassObject unsafe.Pointer
	var GoName string

	GoRawContext_Para = (*C.struct_StructOfGoRawContext_Para)(C.stargo_ToPointer(Para))
	SRPInterface = GetSRPServiceInterface(GoRawContext_Para.ServiceGroupIndex, Object)
	if SRPInterface == nil {
		cstr := C.CString("call RawFunction failed, may be InitRaw for go is not called.")
		GoPrintError(C.VSFAULT_WARNING, cstr)
		C.free((unsafe.Pointer)(cstr))
		return C.VS_FALSE
	}
	BasicSRPInterface = GoSRPGetBasicSRPInterface(C.Star_SRPI_GetServiceGroupID(SRPInterface))
	GoRawContext = (*C.struct_StructOfGoRawContext)(C.Star_SRPI_GetRawContextBuf(SRPInterface, GoRawContext_Para.object, Const_GoString /*"go"*/))
	if GoRawContext == nil {
		return C.VS_FALSE
	}
	if GoRawContext.ContextHeader.IsGlobalSpace == C.VS_TRUE {
		return C.VS_FALSE
	}
	ForWhichClassObject = ForWhichObject
	WhichObjectGoRawContext = (*C.struct_StructOfGoRawContext)(C.Star_SRPI_GetRawContextBuf(SRPInterface, ForWhichClassObject, Const_GoString /*"go"*/))
	for {
		if WhichObjectGoRawContext != nil {
			break
		}
		ForWhichClassObject = C.Star_SRPI_GetClass(SRPInterface, ForWhichClassObject)
		if ForWhichClassObject == nil {
			break
		}
		WhichObjectGoRawContext = (*C.struct_StructOfGoRawContext)(C.Star_SRPI_GetRawContextBuf(SRPInterface, ForWhichClassObject, Const_GoString /*"go"*/))
	}
	if WhichObjectGoRawContext != GoRawContext {
		return C.VS_FALSE
	}
	GoName = C.GoString(Name)
	if (*Name) == '_' && strings.Compare(C.VS_OBJECTTOSTRINGFUNCNAME, GoName) == 0 {
		return C.VS_FALSE
	}
	thisobject := RefToGoObject(GoRawContext.RefItem.o)
	if thisobject == nil {
		return C.VS_FALSE
	}

	defer func() {
		if err := recover(); err != nil {
			GS := fmt.Sprintf("Call Object[%s] GoFunction [%s] Error [%s]", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName, fmt.Sprint(err))
			S := C.CString(GS)
			GoPrintError(C.VSFAULT_WARNING, S)
			C.free((unsafe.Pointer)(S))
			FunctionResult = C.VS_FALSE
			return
		}
	}()

	//---Name is Index
	if (*Name) == '"' && GoRawContext.ContextHeader.IsClass == C.VS_FALSE {
		var ArrayIndex int = (int)(C.atoi(C.stargo_GetCharByIndex(Name, 1)))
		ref_typ := reflect.TypeOf(thisobject)
		if ref_typ.Kind() == reflect.Slice {
			switch ref_typ.Elem().Kind() {
			case reflect.Bool:
				RawO := thisobject.([]bool)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					VSScript_GoRawContext_ReturnValue(RawO[ArrayIndex], BasicSRPInterface, SRPInterface)
					return C.VS_TRUE
				}
			case reflect.Int:
				RawO := thisobject.([]int)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					VSScript_GoRawContext_ReturnValue(RawO[ArrayIndex], BasicSRPInterface, SRPInterface)
					return C.VS_TRUE
				}
			case reflect.Int8:
				RawO := thisobject.([]int8)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					VSScript_GoRawContext_ReturnValue(RawO[ArrayIndex], BasicSRPInterface, SRPInterface)
					return C.VS_TRUE
				}
			case reflect.Int16:
				RawO := thisobject.([]int16)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					VSScript_GoRawContext_ReturnValue(RawO[ArrayIndex], BasicSRPInterface, SRPInterface)
					return C.VS_TRUE
				}
			case reflect.Int32:
				RawO := thisobject.([]int32)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					VSScript_GoRawContext_ReturnValue(RawO[ArrayIndex], BasicSRPInterface, SRPInterface)
					return C.VS_TRUE
				}
			case reflect.Int64:
				RawO := thisobject.([]int64)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					VSScript_GoRawContext_ReturnValue(RawO[ArrayIndex], BasicSRPInterface, SRPInterface)
					return C.VS_TRUE
				}
			case reflect.Uint:
				RawO := thisobject.([]uint)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					VSScript_GoRawContext_ReturnValue(RawO[ArrayIndex], BasicSRPInterface, SRPInterface)
					return C.VS_TRUE
				}
			case reflect.Uint8:
				RawO := thisobject.([]uint8)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					VSScript_GoRawContext_ReturnValue(RawO[ArrayIndex], BasicSRPInterface, SRPInterface)
					return C.VS_TRUE
				}
			case reflect.Uint16:
				RawO := thisobject.([]uint16)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					VSScript_GoRawContext_ReturnValue(RawO[ArrayIndex], BasicSRPInterface, SRPInterface)
					return C.VS_TRUE
				}
			case reflect.Uint32:
				RawO := thisobject.([]uint32)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					VSScript_GoRawContext_ReturnValue(RawO[ArrayIndex], BasicSRPInterface, SRPInterface)
					return C.VS_TRUE
				}
			case reflect.Uint64:
				RawO := thisobject.([]uint64)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					VSScript_GoRawContext_ReturnValue(RawO[ArrayIndex], BasicSRPInterface, SRPInterface)
					return C.VS_TRUE
				}
			case reflect.Float32:
				RawO := thisobject.([]float32)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					VSScript_GoRawContext_ReturnValue(RawO[ArrayIndex], BasicSRPInterface, SRPInterface)
					return C.VS_TRUE
				}
			case reflect.Float64:
				RawO := thisobject.([]float64)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					VSScript_GoRawContext_ReturnValue(RawO[ArrayIndex], BasicSRPInterface, SRPInterface)
					return C.VS_TRUE
				}
			case reflect.Interface:
				RawO := thisobject.([]interface{})
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					VSScript_GoRawContext_ReturnValue(RawO[ArrayIndex], BasicSRPInterface, SRPInterface)
					return C.VS_TRUE
				}
			case reflect.String:
				RawO := thisobject.([]string)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					VSScript_GoRawContext_ReturnValue(RawO[ArrayIndex], BasicSRPInterface, SRPInterface)
					return C.VS_TRUE
				}
			}
		}
		S := C.CString(fmt.Sprintf("array index[%d] is not supported", ArrayIndex))
		GoPrintError(C.VSFAULT_WARNING, S)
		C.free((unsafe.Pointer)(S))
		return C.VS_FALSE
	}
	if (*Name) == 'l' && strings.Compare(GoName, "length") == 0 && GoRawContext.ContextHeader.IsClass == C.VS_FALSE {
		ref_typ := reflect.TypeOf(thisobject)
		if ref_typ.Kind() == reflect.Slice {
			switch ref_typ.Elem().Kind() {
			case reflect.Bool:
				RawO := thisobject.([]bool)
				C.Star_SRPI_LuaPushInt(SRPInterface, (C.VS_INT32)(len(RawO)))
				return C.VS_TRUE
			case reflect.Int:
				RawO := thisobject.([]int)
				C.Star_SRPI_LuaPushInt(SRPInterface, (C.VS_INT32)(len(RawO)))
				return C.VS_TRUE
			case reflect.Int8:
				RawO := thisobject.([]int8)
				C.Star_SRPI_LuaPushInt(SRPInterface, (C.VS_INT32)(len(RawO)))
				return C.VS_TRUE
			case reflect.Int16:
				RawO := thisobject.([]int16)
				C.Star_SRPI_LuaPushInt(SRPInterface, (C.VS_INT32)(len(RawO)))
				return C.VS_TRUE
			case reflect.Int32:
				RawO := thisobject.([]int32)
				C.Star_SRPI_LuaPushInt(SRPInterface, (C.VS_INT32)(len(RawO)))
				return C.VS_TRUE
			case reflect.Int64:
				RawO := thisobject.([]int64)
				C.Star_SRPI_LuaPushInt(SRPInterface, (C.VS_INT32)(len(RawO)))
				return C.VS_TRUE
			case reflect.Uint:
				RawO := thisobject.([]uint)
				C.Star_SRPI_LuaPushInt(SRPInterface, (C.VS_INT32)(len(RawO)))
				return C.VS_TRUE
			case reflect.Uint8:
				RawO := thisobject.([]uint8)
				C.Star_SRPI_LuaPushInt(SRPInterface, (C.VS_INT32)(len(RawO)))
				return C.VS_TRUE
			case reflect.Uint16:
				RawO := thisobject.([]uint16)
				C.Star_SRPI_LuaPushInt(SRPInterface, (C.VS_INT32)(len(RawO)))
				return C.VS_TRUE
			case reflect.Uint32:
				RawO := thisobject.([]uint32)
				C.Star_SRPI_LuaPushInt(SRPInterface, (C.VS_INT32)(len(RawO)))
				return C.VS_TRUE
			case reflect.Uint64:
				RawO := thisobject.([]uint64)
				C.Star_SRPI_LuaPushInt(SRPInterface, (C.VS_INT32)(len(RawO)))
				return C.VS_TRUE
			case reflect.Float32:
				RawO := thisobject.([]float32)
				C.Star_SRPI_LuaPushInt(SRPInterface, (C.VS_INT32)(len(RawO)))
				return C.VS_TRUE
			case reflect.Float64:
				RawO := thisobject.([]float64)
				C.Star_SRPI_LuaPushInt(SRPInterface, (C.VS_INT32)(len(RawO)))
				return C.VS_TRUE
			case reflect.Interface:
				RawO := thisobject.([]interface{})
				C.Star_SRPI_LuaPushInt(SRPInterface, (C.VS_INT32)(len(RawO)))
				return C.VS_TRUE
			case reflect.String:
				RawO := thisobject.([]string)
				C.Star_SRPI_LuaPushInt(SRPInterface, (C.VS_INT32)(len(RawO)))
				return C.VS_TRUE
			}
		}
		S := C.CString("array length is not supported")
		GoPrintError(C.VSFAULT_WARNING, S)
		C.free((unsafe.Pointer)(S))
		return C.VS_FALSE
	}
	/*---map--*/
	switch thisobject.(type) {
	case map[string]interface{}:
		S, mExist := thisobject.(map[string]interface{})[GoName]
		if mExist {
			VSScript_GoRawContext_ReturnValue(S, BasicSRPInterface, SRPInterface)
			return C.VS_TRUE
		} else {
			C.Star_SRPI_LuaPushNil(SRPInterface)
			return C.VS_TRUE
		}
	default:
		ref_typ := reflect.TypeOf(thisobject)
		if ref_typ.Kind() == reflect.Ptr && ref_typ.Elem().Kind() == reflect.Struct {
			if (*Name) < 'A' || (*Name) > 'Z' { /*--private value--*/
				return C.VS_FALSE
			}
			v := reflect.ValueOf(thisobject).Elem().FieldByName(GoName)
			if !v.IsValid() {
				return C.VS_FALSE
			}
			VSScript_GoRawContext_ReturnValue(v.Interface(), BasicSRPInterface, SRPInterface)
			return C.VS_TRUE
		} else {
			return C.VS_FALSE
		}
	}

	return C.VS_FALSE
}

//export GoRawContext_RegSetValue
func GoRawContext_RegSetValue(Object unsafe.Pointer, ForWhichObject unsafe.Pointer, Name *C.VS_CHAR, Index C.VS_INT32, Para C.VS_UWORD) (FunctionResult C.VS_BOOL) {
	var SRPInterface unsafe.Pointer
	var GoRawContext *C.struct_StructOfGoRawContext
	var GoRawContext_Para *C.struct_StructOfGoRawContext_Para
	var LuaToJavaResult C.VS_BOOL
	var GoName string

	if Index == C.VS_SETVALUE_INVALIDINDEX {
		return C.VS_TRUE
	}
	GoRawContext_Para = (*C.struct_StructOfGoRawContext_Para)(C.stargo_ToPointer(Para))
	SRPInterface = GetSRPServiceInterface(GoRawContext_Para.ServiceGroupIndex, Object)
	if SRPInterface == nil {
		cstr := C.CString("call RawFunction failed, may be InitRaw for go is not called.")
		GoPrintError(C.VSFAULT_WARNING, cstr)
		C.free((unsafe.Pointer)(cstr))
		return C.VS_FALSE
	}
	if C.strchr(Name, '.') != nil {
		cstr := C.CString(fmt.Sprintf("call RawFunction failed, attribute[%s] can not be set.", Name))
		GoPrintError(C.VSFAULT_WARNING, cstr)
		C.free((unsafe.Pointer)(cstr))
		return C.VS_FALSE
	}
	//BasicSRPInterface = GoSRPGetBasicSRPInterface(C.Star_SRPI_GetServiceGroupID(SRPInterface))
	GoRawContext = (*C.struct_StructOfGoRawContext)(C.Star_SRPI_GetRawContextBuf(SRPInterface, GoRawContext_Para.object, Const_GoString /*"go"*/))
	if GoRawContext == nil {
		return C.VS_FALSE
	}
	if GoRawContext.ContextHeader.IsGlobalSpace == C.VS_TRUE {
		return C.VS_FALSE
	}
	GoName = C.GoString(Name)

	thisobject := RefToGoObject(GoRawContext.RefItem.o)
	if thisobject == nil {
		return C.VS_FALSE
	}

	defer func() {
		if err := recover(); err != nil {
			GS := fmt.Sprintf("Set Object[%s] Value [%s] Error [%s]", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName, fmt.Sprint(err))
			S := C.CString(GS)
			GoPrintError(C.VSFAULT_WARNING, S)
			C.free((unsafe.Pointer)(S))
			FunctionResult = C.VS_FALSE
			return
		}
	}()

	//---Name is Index
	if (*Name) == '"' && GoRawContext.ContextHeader.IsClass == C.VS_FALSE {
		var ArrayIndex int = (int)(C.atoi(C.stargo_GetCharByIndex(Name, 1)))
		ref_typ := reflect.TypeOf(thisobject)
		if ref_typ.Kind() == reflect.Slice {
			switch ref_typ.Elem().Kind() {
			case reflect.Bool:
				RawO := thisobject.([]bool)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					S, ok := LuaToGoObject(GO_TYPE_BOOL, SRPInterface, Index, &LuaToJavaResult).(bool)
					if LuaToJavaResult == C.VS_TRUE && ok {
						RawO[ArrayIndex] = S
					} else {
						S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
						GoPrintError(C.VSFAULT_WARNING, S)
						C.free((unsafe.Pointer)(S))
					}
					return C.VS_TRUE
				}
			case reflect.Int:
				RawO := thisobject.([]int)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					S, ok := LuaToGoObject(GO_TYPE_INT, SRPInterface, Index, &LuaToJavaResult).(int)
					if LuaToJavaResult == C.VS_TRUE && ok {
						RawO[ArrayIndex] = S
					} else {
						S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
						GoPrintError(C.VSFAULT_WARNING, S)
						C.free((unsafe.Pointer)(S))
					}
					return C.VS_TRUE
				}
			case reflect.Int8:
				RawO := thisobject.([]int8)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					S, ok := LuaToGoObject(GO_TYPE_INT8, SRPInterface, Index, &LuaToJavaResult).(int8)
					if LuaToJavaResult == C.VS_TRUE && ok {
						RawO[ArrayIndex] = S
					} else {
						S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
						GoPrintError(C.VSFAULT_WARNING, S)
						C.free((unsafe.Pointer)(S))
					}
					return C.VS_TRUE
				}
			case reflect.Int16:
				RawO := thisobject.([]int16)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					S, ok := LuaToGoObject(GO_TYPE_INT16, SRPInterface, Index, &LuaToJavaResult).(int16)
					if LuaToJavaResult == C.VS_TRUE && ok {
						RawO[ArrayIndex] = S
					} else {
						S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
						GoPrintError(C.VSFAULT_WARNING, S)
						C.free((unsafe.Pointer)(S))
					}
					return C.VS_TRUE
				}
			case reflect.Int32:
				RawO := thisobject.([]int32)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					S, ok := LuaToGoObject(GO_TYPE_INT32, SRPInterface, Index, &LuaToJavaResult).(int32)
					if LuaToJavaResult == C.VS_TRUE && ok {
						RawO[ArrayIndex] = S
					} else {
						S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
						GoPrintError(C.VSFAULT_WARNING, S)
						C.free((unsafe.Pointer)(S))
					}
					return C.VS_TRUE
				}
			case reflect.Int64:
				RawO := thisobject.([]int64)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					S, ok := LuaToGoObject(GO_TYPE_INT64, SRPInterface, Index, &LuaToJavaResult).(int64)
					if LuaToJavaResult == C.VS_TRUE && ok {
						RawO[ArrayIndex] = S
					} else {
						S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
						GoPrintError(C.VSFAULT_WARNING, S)
						C.free((unsafe.Pointer)(S))
					}
					return C.VS_TRUE
				}
			case reflect.Uint:
				RawO := thisobject.([]uint)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					S, ok := LuaToGoObject(GO_TYPE_UINT, SRPInterface, Index, &LuaToJavaResult).(uint)
					if LuaToJavaResult == C.VS_TRUE && ok {
						RawO[ArrayIndex] = S
					} else {
						S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
						GoPrintError(C.VSFAULT_WARNING, S)
						C.free((unsafe.Pointer)(S))
					}
					return C.VS_TRUE
				}
			case reflect.Uint8:
				RawO := thisobject.([]uint8)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					S, ok := LuaToGoObject(GO_TYPE_UINT8, SRPInterface, Index, &LuaToJavaResult).(uint8)
					if LuaToJavaResult == C.VS_TRUE && ok {
						RawO[ArrayIndex] = S
					} else {
						S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
						GoPrintError(C.VSFAULT_WARNING, S)
						C.free((unsafe.Pointer)(S))
					}
					return C.VS_TRUE
				}
			case reflect.Uint16:
				RawO := thisobject.([]uint16)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					S, ok := LuaToGoObject(GO_TYPE_UINT16, SRPInterface, Index, &LuaToJavaResult).(uint16)
					if LuaToJavaResult == C.VS_TRUE && ok {
						RawO[ArrayIndex] = S
					} else {
						S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
						GoPrintError(C.VSFAULT_WARNING, S)
						C.free((unsafe.Pointer)(S))
					}
					return C.VS_TRUE
				}
			case reflect.Uint32:
				RawO := thisobject.([]uint32)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					S, ok := LuaToGoObject(GO_TYPE_UINT32, SRPInterface, Index, &LuaToJavaResult).(uint32)
					if LuaToJavaResult == C.VS_TRUE && ok {
						RawO[ArrayIndex] = S
					} else {
						S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
						GoPrintError(C.VSFAULT_WARNING, S)
						C.free((unsafe.Pointer)(S))
					}
					return C.VS_TRUE
				}
			case reflect.Uint64:
				RawO := thisobject.([]uint64)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					S, ok := LuaToGoObject(GO_TYPE_UINT64, SRPInterface, Index, &LuaToJavaResult).(uint64)
					if LuaToJavaResult == C.VS_TRUE && ok {
						RawO[ArrayIndex] = S
					} else {
						S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
						GoPrintError(C.VSFAULT_WARNING, S)
						C.free((unsafe.Pointer)(S))
					}
					return C.VS_TRUE
				}
			case reflect.Float32:
				RawO := thisobject.([]float32)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					S, ok := LuaToGoObject(GO_TYPE_FLOAT32, SRPInterface, Index, &LuaToJavaResult).(float32)
					if LuaToJavaResult == C.VS_TRUE && ok {
						RawO[ArrayIndex] = S
					} else {
						S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
						GoPrintError(C.VSFAULT_WARNING, S)
						C.free((unsafe.Pointer)(S))
					}
					return C.VS_TRUE
				}
			case reflect.Float64:
				RawO := thisobject.([]float64)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					S, ok := LuaToGoObject(GO_TYPE_FLOAT64, SRPInterface, Index, &LuaToJavaResult).(float64)
					if LuaToJavaResult == C.VS_TRUE && ok {
						RawO[ArrayIndex] = S
					} else {
						S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
						GoPrintError(C.VSFAULT_WARNING, S)
						C.free((unsafe.Pointer)(S))
					}
					return C.VS_TRUE
				}
			case reflect.Interface:
				RawO := thisobject.([]interface{})
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					S := LuaToGoObject(GO_TYPE_INTERFACE, SRPInterface, Index, &LuaToJavaResult)
					if LuaToJavaResult == C.VS_TRUE {
						RawO[ArrayIndex] = S
					} else {
						S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
						GoPrintError(C.VSFAULT_WARNING, S)
						C.free((unsafe.Pointer)(S))
					}
					return C.VS_TRUE
				}
			case reflect.String:
				RawO := thisobject.([]string)
				if ArrayIndex >= len(RawO) {
					S := C.CString(fmt.Sprintf("array index[%d] greater than size [%d]", ArrayIndex, len(RawO)))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
					return C.VS_FALSE
				} else {
					S, ok := LuaToGoObject(GO_TYPE_STRING, SRPInterface, Index, &LuaToJavaResult).(string)
					if LuaToJavaResult == C.VS_TRUE && ok {
						RawO[ArrayIndex] = S
					} else {
						S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
						GoPrintError(C.VSFAULT_WARNING, S)
						C.free((unsafe.Pointer)(S))
					}
					return C.VS_TRUE
				}
			}
		}
		S := C.CString(fmt.Sprintf("array index[%d] is not supported", ArrayIndex))
		GoPrintError(C.VSFAULT_WARNING, S)
		C.free((unsafe.Pointer)(S))
		return C.VS_FALSE
	}
	/*---map--*/
	switch thisobject.(type) {
	case map[string]interface{}:
		M := thisobject.(map[string]interface{})
		S := LuaToGoObject(GO_TYPE_INTERFACE, SRPInterface, Index, &LuaToJavaResult)
		if LuaToJavaResult == C.VS_TRUE {
			M[GoName] = S
		} else {
			S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
			GoPrintError(C.VSFAULT_WARNING, S)
			C.free((unsafe.Pointer)(S))
		}
		return C.VS_TRUE
	default:
		ref_typ := reflect.TypeOf(thisobject)
		if ref_typ.Kind() == reflect.Ptr && ref_typ.Elem().Kind() == reflect.Struct {
			if (*Name) < 'A' || (*Name) > 'Z' { /*--private value--*/
				return C.VS_FALSE
			}
			v := reflect.ValueOf(thisobject).Elem().FieldByName(GoName)
			if !v.IsValid() {
				return C.VS_FALSE
			}
			switch v.Type().Kind() {
			case reflect.Bool:
				S, ok := LuaToGoObject(GO_TYPE_BOOL, SRPInterface, Index, &LuaToJavaResult).(bool)
				if LuaToJavaResult == C.VS_TRUE && ok {
					v.SetBool(S)
				} else {
					S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
				}
			case reflect.Int:
				S, ok := LuaToGoObject(GO_TYPE_INT, SRPInterface, Index, &LuaToJavaResult).(int)
				if LuaToJavaResult == C.VS_TRUE && ok {
					v.SetInt((int64)(S))
				} else {
					S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
				}
			case reflect.Int8:
				S, ok := LuaToGoObject(GO_TYPE_INT8, SRPInterface, Index, &LuaToJavaResult).(int8)
				if LuaToJavaResult == C.VS_TRUE && ok {
					v.SetInt((int64)(S))
				} else {
					S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
				}
			case reflect.Int16:
				S, ok := LuaToGoObject(GO_TYPE_INT16, SRPInterface, Index, &LuaToJavaResult).(int16)
				if LuaToJavaResult == C.VS_TRUE && ok {
					v.SetInt((int64)(S))
				} else {
					S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
				}
			case reflect.Int32:
				S, ok := LuaToGoObject(GO_TYPE_INT32, SRPInterface, Index, &LuaToJavaResult).(int32)
				if LuaToJavaResult == C.VS_TRUE && ok {
					v.SetInt((int64)(S))
				} else {
					S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
				}
			case reflect.Int64:
				S, ok := LuaToGoObject(GO_TYPE_INT64, SRPInterface, Index, &LuaToJavaResult).(int64)
				if LuaToJavaResult == C.VS_TRUE && ok {
					v.SetInt(S)
				} else {
					S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
				}
			case reflect.Uint:
				S, ok := LuaToGoObject(GO_TYPE_UINT, SRPInterface, Index, &LuaToJavaResult).(uint)
				if LuaToJavaResult == C.VS_TRUE && ok {
					v.SetUint((uint64)(S))
				} else {
					S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
				}

			case reflect.Uint8:
				S, ok := LuaToGoObject(GO_TYPE_UINT8, SRPInterface, Index, &LuaToJavaResult).(uint8)
				if LuaToJavaResult == C.VS_TRUE && ok {
					v.SetUint((uint64)(S))
				} else {
					S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
				}
			case reflect.Uint16:
				S, ok := LuaToGoObject(GO_TYPE_UINT16, SRPInterface, Index, &LuaToJavaResult).(uint16)
				if LuaToJavaResult == C.VS_TRUE && ok {
					v.SetUint((uint64)(S))
				} else {
					S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
				}
			case reflect.Uint32:
				S, ok := LuaToGoObject(GO_TYPE_UINT32, SRPInterface, Index, &LuaToJavaResult).(uint32)
				if LuaToJavaResult == C.VS_TRUE && ok {
					v.SetUint((uint64)(S))
				} else {
					S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
				}
			case reflect.Uint64:
				S, ok := LuaToGoObject(GO_TYPE_UINT64, SRPInterface, Index, &LuaToJavaResult).(uint64)
				if LuaToJavaResult == C.VS_TRUE && ok {
					v.SetUint((uint64)(S))
				} else {
					S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
				}
			case reflect.Float32:
				S, ok := LuaToGoObject(GO_TYPE_FLOAT32, SRPInterface, Index, &LuaToJavaResult).(float32)
				if LuaToJavaResult == C.VS_TRUE && ok {
					v.SetFloat((float64)(S))
				} else {
					S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
				}
			case reflect.Float64:
				S, ok := LuaToGoObject(GO_TYPE_FLOAT64, SRPInterface, Index, &LuaToJavaResult).(float64)
				if LuaToJavaResult == C.VS_TRUE && ok {
					v.SetFloat(S)
				} else {
					S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
				}
				/*
					case reflect.Interface:
						S := LuaToGoObject(GO_TYPE_BOOL, SRPInterface, Index, &LuaToJavaResult)
						if LuaToJavaResult == C.VS_TRUE {
							v.S(S)
						} else {
							S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
							GoPrintError(C.VSFAULT_WARNING, S)
							C.free((unsafe.Pointer)(S))
						}
				*/
			case reflect.String:
				S, ok := LuaToGoObject(GO_TYPE_STRING, SRPInterface, Index, &LuaToJavaResult).(string)
				if LuaToJavaResult == C.VS_TRUE && ok {
					v.SetString(S)
				} else {
					S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
					GoPrintError(C.VSFAULT_WARNING, S)
					C.free((unsafe.Pointer)(S))
				}
			default:
				S := C.CString(fmt.Sprintf("Set Object[%s] Value [%s] Error", C.GoString(C.Star_SRPI_GetName(SRPInterface, Object)), GoName))
				GoPrintError(C.VSFAULT_WARNING, S)
				C.free((unsafe.Pointer)(S))
			}
			return C.VS_TRUE
		} else {
			return C.VS_FALSE
		}
	}
	return C.VS_FALSE
}

//export GoVSScript_RawToParaPkg
func GoVSScript_RawToParaPkg(Para C.VS_UWORD, ServiceGroupIndex C.VS_ULONG, Object unsafe.Pointer) C.VS_PARAPKGPTR {
	var SRPInterface unsafe.Pointer
	var ParaPkg unsafe.Pointer
	var GoRawContext *C.struct_StructOfGoRawContext

	SRPInterface = GetSRPServiceInterface(ServiceGroupIndex, Object)
	if SRPInterface == nil {
		cstr := C.CString("call RawFunction failed, may be InitRaw for go is not called.")
		GoPrintError(C.VSFAULT_WARNING, cstr)
		C.free((unsafe.Pointer)(cstr))
		return (C.VS_PARAPKGPTR)(C.NULL)
	}
	GoRawContext = (*C.struct_StructOfGoRawContext)(C.Star_SRPI_GetRawContextBuf(SRPInterface, Object, Const_GoString /*"go"*/))
	if GoRawContext == nil {
		return (C.VS_PARAPKGPTR)(C.NULL)
	}
	if GoRawContext.ContextHeader.IsGlobalSpace == C.VS_TRUE || GoRawContext.RefItem == nil || GoRawContext.RefItem.o == 0 {
		return (C.VS_PARAPKGPTR)(C.NULL)
	}
	thisobject := RefToGoObject(GoRawContext.RefItem.o)
	switch thisobject.(type) {
	case []bool, []int8, []uint8, []int16, []uint16, []int, []uint, []int32, []uint32, []float32, []float64, []string, []interface{}, map[string]interface{}:
		var n C.VS_INT32 = C.Star_SRPI_LuaGetTop(SRPInterface)

		GoObjectToLua(SRPInterface, thisobject, true)
		var m C.VS_INT32 = C.Star_SRPI_LuaGetTop(SRPInterface)
		if (m - n) == 0 {
			return (C.VS_PARAPKGPTR)(C.NULL)
		}
		if (m-n) > 1 || C.Star_SRPI_LuaIsParaPkg(SRPInterface, -1) == C.VS_FALSE {
			C.Star_SRPI_LuaPop(SRPInterface, m-n)
			return (C.VS_PARAPKGPTR)(C.NULL)
		}
		ParaPkg = C.Star_SRPI_LuaToParaPkg(SRPInterface, -1)
		C.Star_SRPParaPkg_AddRef(ParaPkg)
		C.Star_SRPI_LuaPop(SRPInterface, 1)
		C.Star_SRPParaPkg_ReleaseOwner(ParaPkg)
		return (C.VS_PARAPKGPTR)(ParaPkg)
	}
	return (C.VS_PARAPKGPTR)(C.NULL)
}

func RegScriptTermCallBack_P(CallBackProc func()) {
	g_ScriptTermCallBack = CallBackProc
}

//var g_AttachRawContextCallBack func(ContextName string) interface{} = nil
func RegAttachRawContextCallBack_P(CallBackProc func(ContextName string) interface{}) {
	g_AttachRawContextCallBack = CallBackProc
	return
}

func RegScriptInitCallBack_P(CallBackProc func(SrvGroup *StarSrvGroup, Service *StarService)) {
	g_ScriptInitCallBack = CallBackProc
}

//export GoVSScript_AttachRawContext
func GoVSScript_AttachRawContext(Para C.VS_UWORD, ServiceGroupIndex C.VS_ULONG, object unsafe.Pointer, ContextName *C.VS_CHAR, IsClass C.VS_BOOL, ContextInfo *C.VS_CHAR) C.VS_BOOL {
	var SRPInterface unsafe.Pointer
	var GoRawContext C.struct_StructOfGoRawContext
	var GoRawContextPtr *C.struct_StructOfGoRawContext
	var thisobject interface{} = nil

	SRPInterface = GetSRPServiceInterface(ServiceGroupIndex, object)
	if SRPInterface == nil {
		cstr := C.CString("call RawFunction failed, may be InitRaw for go is not called.")
		GoPrintError(C.VSFAULT_WARNING, cstr)
		C.free((unsafe.Pointer)(cstr))
		return C.VS_FALSE
	}
	if ContextName == nil || (*ContextName) == 0 {
		cstr := C.CString("go does not support AttachRawContext with ContextName == NULL")
		GoPrintError(C.VSFAULT_WARNING, cstr)
		C.free((unsafe.Pointer)(cstr))
		return C.VS_FALSE
	} else {
		if g_AttachRawContextCallBack != nil {
			thisobject = g_AttachRawContextCallBack(C.GoString(ContextName))
		}
		if thisobject == nil {
			return C.VS_FALSE
		}
		switch thisobject.(type) {
		case int8, uint8, bool, int16, uint16, int32, uint32, int, uint, int64, uint64, float32, float64, string, complex64, complex128:
			/*--simple types--*/
			return C.VS_FALSE
		default:
			ref_typ := reflect.TypeOf(thisobject)
			if ref_typ.Kind() == reflect.Array || ref_typ.Kind() == reflect.Struct || ref_typ.Kind() == reflect.UnsafePointer {
				return C.VS_FALSE
			}
		}
		C.memset((unsafe.Pointer)(&GoRawContext), 0, (C.size_t)(C.stargo_SizeOfStructOfGoRawContext()))
		GoRawContext.ContextHeader.IsGlobalSpace = C.VS_FALSE
		GoRawContext.RefItem = g_GoRawContextRefManager.Alloc(thisobject, object, SRPInterface, IsClass)
		GoRawContext.ContextHeader.IsClass = IsClass
		GoRawContext.Para = (*C.struct_StructOfGoRawContext_Para)(C.stargo_MallocStructOfGoRawContext_Para())
		GoRawContext.Para.object = object
		GoRawContext.Para.ServiceGroupIndex = ServiceGroupIndex

		GoRawContextPtr = (*C.struct_StructOfGoRawContext)(C.Star_SRPI_GetRawContextBuf(SRPInterface, object, Const_GoString /*"go"*/))
		if GoRawContextPtr != nil {
			GoRawContext.ContextHeader.ClassObjectID = GoRawContextPtr.ContextHeader.ClassObjectID
		} else {
			C.stargo_inituuid(&GoRawContext.ContextHeader.ClassObjectID)
		}

		C.Star_SRPI_CreateRawContextBuf(SRPInterface, object, Const_GoString /*"go"*/, (*C.VS_INT8)((unsafe.Pointer)(&GoRawContext)), C.stargo_SizeOfStructOfGoRawContext())
		//---need hook script general functions
		C.Star_SRPI_RegLuaFunc(SRPInterface, object, (*C.VS_CHAR)(C.NULL), (unsafe.Pointer)(C.stargo_VSScript_GoRawContext_GeneralFunction), C.stargo_PointerToUWord((unsafe.Pointer)(GoRawContext.Para)))
		C.Star_SRPI_RegLuaFuncFilter(SRPInterface, object, (C.VS_LuaFuncFilterProc)(C.stargo_VSScript_GoRawContext_LuaFuncFilter), C.stargo_PointerToUWord((unsafe.Pointer)(GoRawContext.Para)))
		C.Star_SRPI_RegLuaGetValueFunc(SRPInterface, object, (C.VS_LuaGetValueProc)(C.stargo_VSScript_GoRawContext_RegGetValue), C.stargo_PointerToUWord((unsafe.Pointer)(GoRawContext.Para)))
		C.Star_SRPI_RegRawLuaSetValueFunc(SRPInterface, object, (C.VS_LuaSetValueProc)(C.stargo_VSScript_GoRawContext_RegSetValue), C.stargo_PointerToUWord((unsafe.Pointer)(GoRawContext.Para)))
		C.Star_SRPI_RegNewFunctionCallBack(SRPInterface, object, (C.VS_NewFunctionCallBackProc)(C.stargo_VSScript_GoRawContext_NewFunctionCallBack), C.stargo_PointerToUWord((unsafe.Pointer)(GoRawContext.Para)))

		return C.VS_TRUE
	}
}

//export GoVSScript_InitRaw
func GoVSScript_InitRaw(Para C.VS_UWORD, BasicSRPInterface unsafe.Pointer, SRPInterface unsafe.Pointer) C.VS_BOOL {
	var GroupObjData *StarSrvGroupBody
	var SrvGroup *StarSrvGroup
	var Service *StarService
	var ServiceID C.VS_UUID

	SrvGroup = GoSRPQuerySrvGroup(C.Star_SRPBasic_GetServiceGroupID(BasicSRPInterface))
	if SrvGroup == nil {
		SrvGroup = GoSRPGetSrvGroup(C.Star_SRPBasic_GetServiceGroupID(BasicSRPInterface), BasicSRPInterface)
	}
	GroupObjData = SrvGroupClass_getstarcoredata(SrvGroup)
	C.Star_SRPI_GetServiceID(SRPInterface, &ServiceID)
	Service = GoSRPQueryServiceByServiceID(GroupObjData, &ServiceID)
	if Service == nil {
		C.Star_SRPI_AddRef(SRPInterface)
		Service = ToStarService(GroupObjData, SRPInterface)
		if g_ScriptInitCallBack != nil {
			g_ScriptInitCallBack(SrvGroup, Service)
		}
	}
	return C.VS_TRUE
}

/*----------------------------------------------------------------------------*/
func Println(a ...interface{}) (n int, err error) {
	if C.StarGo_ModuleLoadFromStarcore == C.VS_FALSE {
		return fmt.Println(a)
	} else {
		cstr := C.CString(fmt.Sprintln(a))
		C.Star_SRPControl_SRPLock(C.StarGo_SRPControlInterface)
		C.stargo_SRPControl_ProcessError(C.StarGo_SRPControlInterface, C.VSFAULT_INDICATION, Const_GoString, 0, cstr)
		C.Star_SRPControl_SRPUnLock(C.StarGo_SRPControlInterface)
		C.free((unsafe.Pointer)(cstr))
		return 0, nil
	}
}

func Printf(format string, a ...interface{}) (n int, err error) {
	if C.StarGo_ModuleLoadFromStarcore == C.VS_FALSE {
		return fmt.Printf(format, a)
	} else {
		cstr := C.CString(fmt.Sprintf(format, a))
		C.Star_SRPControl_SRPLock(C.StarGo_SRPControlInterface)
		C.stargo_SRPControl_ProcessError(C.StarGo_SRPControlInterface, C.VSFAULT_INDICATION, Const_GoString, 0, cstr)
		C.Star_SRPControl_SRPUnLock(C.StarGo_SRPControlInterface)
		C.free((unsafe.Pointer)(cstr))
		return 0, nil
	}
}

func Print(a ...interface{}) (n int, err error) {
	if C.StarGo_ModuleLoadFromStarcore == C.VS_FALSE {
		return fmt.Print(a)
	} else {
		cstr := C.CString(fmt.Sprint(a))
		C.Star_SRPControl_SRPLock(C.StarGo_SRPControlInterface)
		C.stargo_SRPControl_ProcessError(C.StarGo_SRPControlInterface, C.VSFAULT_INDICATION, Const_GoString, 0, cstr)
		C.Star_SRPControl_SRPUnLock(C.StarGo_SRPControlInterface)
		C.free((unsafe.Pointer)(cstr))
		return 0, nil
	}
}
