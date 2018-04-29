#ifndef _STAR_GO_H
#define _STAR_GO_H 1

struct StructOfObjectRefInSrvGroup{
	VS_UWORD RefItem;
	VS_BOOL IncreaseRef;  /*if == VS_FALSE, then use weak global ref, otherwise, use global ref */
};
struct StructOfObjectRefInSrvGroup *stargo_MallocStructOfObjectRefInSrvGroup();
void stargo_FreeStructOfObjectRefInSrvGroup(struct StructOfObjectRefInSrvGroup *Val);

struct classRawContextRefItem{
	VS_UWORD o;
	VS_UUID  ObjectID;
	VS_BOOL IsClass;	
	struct classRawContextRefItem *Up;
	struct classRawContextRefItem *Down;
};

struct StructOfGoRawContext_Para{
	VS_ULONG ServiceGroupIndex;
	void *object;
};


struct StructOfGoRawContext{
	struct StructOfCommonRawContextHeader ContextHeader;
	struct classRawContextRefItem *RefItem;
	struct StructOfGoRawContext_Para *Para;	
};

VS_INT32 stargo_SizeOfStructOfGoRawContext();
struct classRawContextRefItem *stargo_MallocclassRawContextRefItem();
struct StructOfGoRawContext_Para *stargo_MallocStructOfGoRawContext_Para();


extern void *StarGo_SRPControlInterface;
extern void *StarGo_SRPCoreShellInterface;
extern VS_INT32 StarGo_ScriptInterfaceIndex;

extern VS_BOOL StarGo_ModuleInitFlag;
extern VS_BOOL StarGo_ModuleLoadFromStarcore;

extern VS_CHAR  StarGo_g_ShareLibraryPath[];
extern VS_CHAR  StarGo_g_CoreLibraryPath[];
extern VS_CHAR  StarGo_g_CoreOperationPath[];

VS_ULONG stargo_starcore_Load();
void stargo_starcore_unLoad();
VS_INT64 stargo_CoreHandle();

VS_ULONG stargo_starcore_Init(VS_BOOL ServerFlag, VS_BOOL ShowMenuFlag,VS_BOOL ShowOutWndFlag, VS_BOOL SRPPrintFlag, VS_CHAR *DebugInterface, VS_INT32 DebugPortNumber, VS_CHAR *ClientInterface, VS_INT32 ClientPortNumber);

void stargo_inituuid(VS_UUID *u);
VS_BOOL stargo_uuidisequal(VS_UUID *u1,VS_UUID *u2);
VS_BOOL stargo_uuidisvalid(VS_UUID *u);

void *stargo_MovePointer(void *In,VS_INT32 Step);

VS_UWORD stargo_MsgCallBack( VS_ULONG ServiceGroupID, VS_ULONG uMsg, VS_UWORD wParam, VS_UWORD lParam, VS_BOOL *IsProcessed, VS_UWORD Para );
void stargo_RegisterCallBackInfo( void* MsgCallBackProc, VS_UWORD MsgCallBackPara );
void stargo_UnRegisterCallBackInfo( void* MsgCallBackProc, VS_UWORD MsgCallBackPara );

void stargo_SRPDispatchRequestCallBack(VS_UWORD Para);

void stargo_Term( );
void stargo_TermEx( );

void *stargo_ToPointer64(VS_INT64 in);
void *stargo_ToPointer(VS_UWORD in);
void *stargo_GetUWordPointer(VS_UWORD in);  /*--get pointer saved in VS_UWORD--*/
void stargo_SetUWordPointer(VS_UWORD in,void *ptr);  /*--set pointer to be saved in VS_UWORD--*/
VS_CHAR *stargo_IPToString(SOCKADDR_IN *ip);
VS_INT64 stargo_PointerToInt64(void *Ptr);
VS_UWORD stargo_PointerToUWord(void *Ptr);
VS_CHAR *stargo_GetCharByIndex(VS_CHAR *Ptr,VS_INT32 Index);

void stargo_SRPI_ProcessError(void *c_this,VS_INT32 AlarmLevel,const VS_CHAR *SourceName,VS_INT32 LineIndex,const VS_CHAR *Info);
void stargo_SRPBasic_ProcessError(void *c_this,VS_INT32 AlarmLevel,const VS_CHAR *SourceName,VS_INT32 LineIndex,const VS_CHAR *Info);
void stargo_SRPControl_ProcessError(void *c_this,VS_INT32 AlarmLevel,const VS_CHAR *SourceName,VS_INT32 LineIndex,const VS_CHAR *Info);

/*---only support no parameter--*/
VS_UWORD stargo_SRPI_ScriptCall(void *c_this,void *Object,VS_ULONG *RetCode,const VS_CHAR *FunctionName,const VS_CHAR *TypeSet);


void stargo_FreeScriptObject(VS_UWORD Para, VS_UWORD ScriptObject);
void stargo_ObjectIDChangeNotify(void *Object,VS_UWORD Para,VS_UUID *NewObjectID);
void stargo_ObjectFreeNotify(void *Object,VS_UWORD Para);
VS_INT32 stargo_SRPObject_ScriptCallBack( void *L );

//--not complete
VS_INT32 stargo_VSScript_GoRawContext_GeneralFunction(void *L);
VS_BOOL stargo_VSScript_GoRawContext_LuaFuncFilter(void *object, void *ForWhichObject, VS_CHAR *FuncName, VS_UWORD Para);
VS_BOOL stargo_VSScript_GoRawContext_RegGetValue(void *Object, void *ForWhichObject, VS_CHAR *Name, VS_UWORD Para, VS_BOOL GetAllRawAttributeFlag);
VS_BOOL stargo_VSScript_GoRawContext_RegSetValue(void *Object, void *ForWhichObject, VS_CHAR *Name, VS_INT32 Index, VS_UWORD Para);
void stargo_VSScript_GoRawContext_NewFunctionCallBack(void *Object, void *DesObject, VS_CHAR *FuncName, VS_UWORD Para);



#endif /* !_STAR_GO_H */

