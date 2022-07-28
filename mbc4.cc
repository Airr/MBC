// *********************************************************************
//   Created with MBC (V) 4.0-Beta4 (2022/07/26)Ported to OSX by Armando Rivera
//   Ported from BCX32 BASIC To C/C++ Translator (V) 5.12
//   BCX (c) 1999 - 2018 by Kevin Diggins
//   LinuxBC (c) 2009 by Mike Henning 
//   MBC (c) 2009 - 2018 by Armando Rivera
// *********************************************************************
//   Translated for compiling with the g++ Compiler
//   g++ -Wformat -D_FORTIFY_SOURCE=2 -Wno-write-strings $FILE$.cc -ldl -o $FILE$
// *********************************************************************
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <setjmp.h>
#include <time.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dlfcn.h>


// ***************************************************
// Compiler Defines
// ***************************************************
  #define C_EXPORT extern "C"
  #define C_IMPORT extern "C"

#ifndef stat
  #define lstat stat
#endif
#ifndef _fcloseall
  #define _fcloseall _fcloseall
#endif
#ifndef HWND
  #define HWND GHWND
#endif
#ifndef MAX_PATH
  #define MAX_PATH 2048
#endif
#ifndef CALLBACK
  #define CALLBACK
#endif
typedef unsigned int HINSTANCE;
typedef void* LPVOID;
typedef char* PCHAR;
typedef unsigned char BYTE;
typedef unsigned int  UINT;
typedef unsigned char UCHAR;
typedef unsigned char* PUCHAR;
typedef unsigned long ULONG;
typedef unsigned long* ULONG_PTR;
typedef unsigned long DWORD;

#ifndef TRUE
  #define TRUE 1
#endif

#ifndef FALSE
  #define FALSE 0
#endif
#define BOOL bool

// ***************************************************

typedef long (*CPP_FARPROC)(char *);


// *************************************************
//            User Defined Constants
// *************************************************

#define Version "4.0-Beta4 (2022/07/26)"
#define __BCX__ 1
#define vt_VarMin 2
#define vt_VarMax vt_VARIANT 
#define fprintf ReDirectFPrint 
#define MaxElements 128
#define MaxTypes 512
#define MaxLocalVars 512
#define MaxGlobalVars 4096
#define MaxLib 64
#define c_SglQt 39
#define c_DblQt 34
#define c_LPar 40
#define c_RPar 41
#define c_Komma 44
#define c_LtBkt 91
#define c_RtBkt 93
#define BCX_STR_RUNTIME "Runtime Functions"
#define BCX_STR_MAIN_PROG "Main Program"
#define BCX_STR_SYS_VARS "System Variables"
#define BCX_STR_STD_MACROS "Standard Macros"
#define BCX_STR_STD_PROTOS "Standard Prototypes"
#define BCX_STR_USR_PROCS "User Subs and Functions"
#define BCX_STR_USR_VARS "User Global Variables"
#define BCX_STR_USR_PROTOS "User Prototypes"
#define BCX_STR_USR_CONST "User Defined Constants"
#define BCX_STR_USR_TYPES "User Defined Types, Classes (CPP Mode), And Unions"
#define FUNCTIONPARSE_CLASS struct _FUNCTIONPARSE*
#define VarTypes "%$#!@¦"
#define ARGTYPE_CLASS struct _ARGTYPE*
#define PROTOSTORE_CLASS struct _PROTOSTORE*
#define ELEMENT_CLASS struct _ELEMENT*
#define USERTYPEDEFS_CLASS struct _USERTYPEDEFS*
#define VARINFO_CLASS struct _VARINFO*
#define VARCODE_CLASS struct _VARCODE*
#define iMatchLft(A,B) iMatch (A ,B ,0)
#define iMatchWrd(A,B) iMatch (A ,B ,1)
#define iMatchRgt(A,B) iMatch (A ,B ,2)
// *************************************************
//        User's GLOBAL ENUM blocks
// *************************************************

enum
  {
    vt_UNKNOWN,
    vt_STRLIT,
    vt_INTEGER,
    vt_SINGLE,
    vt_DOUBLE,
    vt_LDOUBLE,
    VT_LLONG,
    vt_STRVAR,
    vt_DECFUNC,
    vt_NUMBER,
    vt_FILEPTR,
    vt_UDT,
    vt_STRUCT,
    vt_UNION,
    vt_BOOL,
    vt_CHAR,
    vt_LPSTRPTR,
    vt_PCHAR,
    vt_CHARPTR,
    vt_VOID,
    vt_LONG,
    vt_DWORD,
    vt_FARPROC,
    vt_LPBYTE,
    vt_LRESULT,
    vt_BYTE,
    vt_SHORT,
    vt_USHORT,
    vt_UINT,
    vt_ULONG,
    vt_HWND,
    vt_HDC,
    vt_COLORREF,
    vt_HANDLE,
    vt_HINSTANCE,
    vt_WNDCLASSEX,
    vt_HFONT,
    vt_VARIANT
  };


enum
  {
    mt_ProcessSetCommand,
    mt_FuncSubDecC_Dec,
    mt_FuncSubDecC_Dec2,
    mt_Opts,
    mt_Opts2,
    mt_Opts3,
    mt_OverLoad,
    mt_OverLoad2,
    mt_FuncSubx1,
    mt_FuncSubx2
  };



// *************************************************
//   User Defined Types, Classes (CPP Mode), And Unions
// *************************************************

typedef struct _functionParse
{
  int     NumArgs;
  int     CommaPos[128];
}functionParse, *LPFUNCTIONPARSE;


typedef struct _ARGTYPE
{
  char Arg[2048];
  int     ArgType;
}ARGTYPE, *LPARGTYPE;


typedef struct _ProtoStore
{
   char  Prototype[2048];
   char  Condition[512];
   int  CondLevel;
}ProtoStore, *LPPROTOSTORE;


typedef struct _Element
{
   int  ElementType;
   int  ElementID;
   int  ElementDynaPtr;
   char  ElementName[64];
}Element, *LPELEMENT;


typedef struct _UserTypeDefs
{
   int  TypeofDef;
   int  EleCnt;
   struct _Element  Elements[MaxElements];
   char  VarName[64];
}UserTypeDefs, *LPUSERTYPEDEFS;


typedef struct _VarInfo
{
   int  VarLine;
   int  VarType;
   int  VarDef;
   int  VarPntr;
   int  VarSF;
   int  VarExtn;
   int  VarCondLevel;
   int  VarEmitFlag;
   int  VarConstant;
   char  VarName[64];
   char  VarDim[128];
   char  VarModule[300];
   char  VarCondDef[128];
}VarInfo, *LPVARINFO;


typedef struct _VARCODE
{
   int  VarNo;
   int  Method;
   int  IsPtrFlag;
  char Header[2048];
  char Proto[2048];
  char Functype[2048];
  char StaticOut[2048];
  char Token[2048];
  char AsToken[2048];
}VARCODE, *LPVARCODE;


// *************************************************
//                System Variables
// *************************************************

char    TAB [2]={9,0};   // Horz Tab
char    LF  [2]={10,0};  // Line Feed
char    ESC [2]={27,0};  // Escape
char    SPC [2]={32,0};  // Space
char    DQ  [2]={34,0};  // Double-Quote
char    DDQ [3]={34,34,0}; // Double-Double-Quote
char    CRLF[3]={13,10,0}; // Carr Rtn & Line Feed
char    *AR_fgets_retval;

// *************************************************
//            User Global Variables
// *************************************************

static PCHAR   *G_argv;
static int     G_argc;
static int     NoRT;
static int     ByrefCnt;
static char    CurLine[65535];
static int     gLinesWritten;
static int     LoopLocalCnt;
static int     GlobalVarCnt;
static int     TypeDefsCnt;
static int     LocalVarCnt;
static int     LocalDynArrCount;
static int     LocalDynaCnt;
static int     GlobalDynaCnt;
static int     ModuleNdx;
static int     FPtrNdx;
static int     SplitCnt;
static int     SplitCur;
static char    SrcTmp[65535];
static int     StartNdx;
static int     ExitNdx;
static VARCODE VarCode;
static int     UmQt;
static char    LD_FLAGS[65535];
static char    Accelerator[65535];
static char    CallType[65535];
static int     CaseFlag;
static char    CaseVar[65535];
static char    Cmd[65535];
static char    Compiler[65535];
static char    CmdLineConst[65535];
static char    CmdLineFileOut[65535];
static int     CurrentFuncType;
static char    DimType[65535];
static int     DllCnt;
static int     LoadLibsCnt;
static float   Elapsed;
static int     EndOfProgram;
static int     EntryCnt;
static int     ErrFile;
static char    szFile[65535];
static char    Filnam[65535];
static int     ForceMainToFunc;
static char    Funcname[65535];
static char    Handl[65535];
static int     HFileCnt;
static char    HFile[65535];
static int     InConditional;
static char    InIfDef[65535];
static int     Indent;
static int     InFunc;
static int     InMain;
static int     IsCallBack;
static int     TurboSize;
static int     UseCProto;
static int     InTypeDef;
static int     IsAuto;
static int     NoTypeDeclare;
static int     IsDim;
static int     IsExported;
static int     IsRegister;
static int     IsStatic;
static int     IsStdFunc;
static int     IsLocal;
static int     IsRaw;
static int     IsApple;
static int     KillCFile;
static char    Keyword1[65535];
static int     LastCmd;
static int     LinesRead;
static char    Linker[65535];
static char    Lookup[65535];
static int     MakeDLL;
static int     Ndx;
static int     NoMain;
static int     NoDllMain;
static int     OkayToSend;
static char    Op[65535];
static int     OptionBase;
static char    OutfileClone[65535];
static int     PassOne;
static int     ProtoCnt;
static int     Pusher;
static int     Quiet;
static int     ReDirect;
static FILE   *SaveOutfileNum;
static char    Scoot[65535];
static int     ShowStatus;
static int     SrcCnt;
static int     SrcFlag;
static int     TrcFlag;
static int     TestForBcxIni;
static char    FileIn[65535];
static char    FileOut[65535];
static char    FileErr[65535];
static char    T[65535];
static int     Test;
static int     Statements;
static int     TestState;
static char    Tipe[65535];
static int     TranslateSlash;
static int     UseCpp;
static int     UseFlag;
static int     InNameSpace;
static int     Use_Virtual;
static char    vproc[65535];
static int     UseStdCall;
static int     UseLCaseTbl;
static char    Var[65535];
static int     XitCount;
static char    Z[65535];
static char    ConstLastDef[65535];
static int     Use_AnsiToWide;
static int     Use_Asc;
static int     Use_AppExeName;
static int     Use_AppExePath;
static int     Use_Boolstr;
static int     Use_Bor;
static int     Use_Band;
static int     Use_Bnot;
static int     Use_BcxSplitPath;
static int     Use_Bin;
static int     Use_Bin2dec;
static int     Use_Osx;
static int     Use_Cvd;
static int     Use_Cvld;
static int     Use_Cvi;
static int     Use_Cvl;
static int     Use_Cvs;
static int     Use_Chr;
static int     Use_Cdbl;
static int     Use_Cldbl;
static int     Use_Csng;
static int     Use_Clear;
static int     Use_Cbool;
static int     Use_Cint;
static int     Use_Clng;
static int     Use_Cls;
static int     Use_Color;
static int     Use_Command;
static int     Use_ContainedIn;
static int     Use_Console;
static int     Use_CopyFile;
static int     Use_Static;
static int     Use_Crlf;
static int     Use_Curdir;
static int     Use_Del;
static int     Use_Download;
static int     Use_Dynacall;
static int     Use_DynamicA;
static int     Use_Embed;
static int     Use_Enclose;
static int     Use_Environ;
static int     Use_EnumFile;
static int     Use_Eof;
static int     Use_Exist;
static int     Use_ExitCode;
static int     Use_Extract;
static int     Use_LoadFile;
static int     Use_FillArray;
static int     Use_Findfirst;
static int     Use_Findnext;
static int     Use_FindInType;
static int     Use_Fint;
static int     Use_Fix;
static int     Use_FileLocked;
static int     Use_Frac;
static int     Use_Fracl;
static int     Use_Freefile;
static int     Use_Get;
static int     Use_GetCh;
static int     Use_GenFree;
static int     Use_Gosub;
static int     Use_Gtk;
static int     Use_Glib;
static int     Use_Hex;
static int     Use_Hex2Dec;
static int     Use_Iif;
static int     Use_Imod;
static int     Use_Inkey;
static int     Use_InkeyD;
static int     Use_Ins;
static int     Use_Instr;
static int     Use_Inchr;
static int     Use_Isptr;
static int     Use_iReplace;
static int     Use_IRemove;
static int     Use_Instrrev;
static int     Use_Join;
static int     Use_Keypress;
static int     Use_Lcase;
static int     Use_Ldouble;
static int     Use_Left;
static int     Use_Like;
static int     Use_Lineinput;
static int     Use_Loc;
static int     Use_Locate;
static int     Use_Lof;
static int     Use_Lpad;
static int     Use_Ltrim;
static int     Use_Mcase;
static int     Use_Mid;
static int     Use_Midstr;
static int     Use_Mkd;
static int     Use_Mkld;
static int     Use_Mki;
static int     Use_Mkl;
static int     Use_Mks;
static int     Use_Min;
static int     Use_Max;
static int     Use_Now;
static int     Use_Numqsortdint;
static int     Use_Numqsortaint;
static int     Use_Numqsortdfloat;
static int     Use_Numqsortafloat;
static int     Use_Numqsortddouble;
static int     Use_Numqsortadouble;
static int     Use_Idxqsort;
static int     Use_IdxqsortSt;
static int     Use_PtrqsortSt;
static int     Use_Oct;
static int     Use_Overloaded;
static int     Use_OSVersion;
static int     Use_Pause;
static int     Use_PeekStr;
static int     Use_Put;
static int     Use_QBColor;
static int     Use_Randomize;
static int     Use_Rec;
static int     Use_RecCount;
static int     Use_Remain;
static int     Use_Remove;
static int     Use_Repeat;
static int     Use_Replace;
static int     Use_Reverse;
static int     Use_Right;
static int     Use_Rpad;
static int     Use_Rnd;
static int     Use_Exp;
static int     Use_Retain;
static int     Use_Round;
static int     Use_Rtrim;
static int     Use_Run;
static int     Use_Scan;
static int     Use_Inputbuffer;
static int     Use_SearchPath;
static int     Use_StrUpLow;
static int     Use_Shell;
static int     Use_Sgn;
static int     Use_SingleFile;
static int     Use_Space;
static int     Use_Split;
static int     Use_DSplit;
static int     Use_StartupCode;
static int     Use_Stristr;
static int     Use_StrStr;
static int     Use_Str;
static int     Use_Strl;
static int     Use_Str_Cmp;
static int     Use_Strim;
static int     Use_String;
static int     Use_Strptr;
static int     Use_Strqsorta;
static int     Use_Strqsortd;
static int     Use_Strtoken;
static int     Use_DynStrqsorta;
static int     Use_DynStrqsortd;
static int     Use_Swap;
static int     Use_Sysdir;
static int     Use_SysStr;
static int     Use_sziif;
static int     Use_Tally;
static int     Use_Tempdir;
static int     Use_TempFileName;
static int     Use_Threads;
static int     Use_Time;
static int     Use_Timer;
static int     Use_Trim;
static int     Use_Turbo;
static int     Use_Ubound;
static int     Use_Ucase;
static int     Use_Using;
static int     Use_VChr;
static int     Use_Verify;
static int     Use_Val;
static int     Use_Vall;
static int     Use_WideToAnsi;
static int     Use_Wx;
static int     Use_WxC;
static int     Use_Ctor;
static int     Use_Instat;
static int     Use_Socket;
static int     Use_IOS;
static int     Use_RegEx;
static int     Use_BEL;
static int     Use_BS;
static int     Use_CR;
static int     Use_DDQ;
static int     Use_DQ;
static int     Use_EOF;
static int     Use_ESC;
static int     Use_FF;
static int     Use_LF;
static int     Use_NUL;
static int     Use_SPC;
static int     Use_TAB;
static int     Use_VT;
static char    prcFile[65535];
static char    udtFile[65535];
static char    datFile[65535];
static char    cstFile[65535];
static char    ovrFile[65535];
static char    hdrFile[65535];
static char    setFile[65535];
static char    enuFile[65535];
static char    *szTmp;
static char    *Src;
static char    *AbortSrc;
static char    *WarnMsg;
static char    *RmLibs;
static FILE   *SourceFile;
static FILE   *FP2;
static FILE   *FP3;
static FILE   *FP4;
static FILE   *FP5;
static FILE   *FP6;
static FILE   *FP7;
static FILE   *FP8;
static FILE   *FP9;
static FILE   *FP11;
static FILE   *Outfile;
static FILE   *FP1;
static int     DoCountLines;
static FILE   *FP10;
static FILE   *ResIn;
static FILE   *ResOut;
static FILE   *UserResIn;
static FILE   *fpErr;
static FILE   *fpHFile;
static FILE   *FP68;
static FILE   *fpdef;
static int     SFPOINTER;
static int     WithCnt;
static char    ByrefVars[1024][65535];
static int     LoopLocalVar[256];
static int     BaseTypeDefsCnt[16];
static char    Modules[256][65535];
static int     ModuleLineNos[256];
static FILE   *FPtr[256];
static char    Stk[4096][65535];
static ProtoStore ProtoType[1024];
static char    SrcStk[128][65535];
static char    SplitStk[128][65535];
static char    CaseStk[256][65535];
static int     CaseElseFlag[256];
static char    Entry[256][65535];
static char    Xit[256][65535];
static char    LocalDynArrName[256][65535];
static char    GlobalDynaStr[256][65535];
static char    DynaStr[256][65535];
static char    StartSub[32][65535];
static char    ExitSub[32][65535];
static char    Library[MaxLib][65535];
static int     GlobalVarHash[MaxGlobalVars];
static VarInfo GlobalVars[MaxGlobalVars];
static VarInfo LocalVars[MaxLocalVars];
static UserTypeDefs TypeDefs[MaxTypes];
static char    DllDecl[800][512];
static char    Loadlibs[128][512];
static char    HFiles[128][65535];
static char    TypeName[16][65535];
static char    WithVar[8][65535];



// *************************************************
//               Standard Macros
// *************************************************

#define FDRV   2
#define FPATH  4
#define FNAME  8
#define FEXT  16
#define BAND &
#define BOR |
#define imod(a,b)((a)%(b))
#define VAL(a)(double)atof(a)


// *************************************************
//               Standard Prototypes
// *************************************************

int     str_cmp(char*, char*);
int     EoF (FILE*);
void    cls(void);
void    locate (int,int,int=1,int=12);
void    midstr (char*, int, int, char *);
char*   BCX_TmpStr(size_t);
char*   sziif (bool,char*,char*);
char*   TempFileName (char*,char*);
char*   AppExePath (void);
char*   AppExeName (void);
char*   lcase (char*);
char*   ucase (char*);
char*   mid (char*, int, int=-1);
char*   ltrim (char*,char=32);
char*   rtrim (char*,char=32);
char*   trim (char*);
char*   strim   (char*);
char*   left (char*,int);
char*   right (char*,int);
char*   rpad (char*,int,int=32);
char*   lpad (char*,int,int=32);
char*   stringx (int,int);
char*   extract (char*,char*);
char*   remain (char*,char*);
char*   command (int=-1);
char*   replace (char*,char*,char*);
char*   iReplace (char*,char*,char*);
void    Shell (char *);
char*   space (int a);
char*   str (double);
char*   curdir (void);
char*   tempdir (void);
char*   Environ (char*);
char*   _strupr_(char *);
char*   _strlwr_(char *);
char*   BcxSplitPath (char *, int);
void    _splitpath_(const char* path, char* drv, char* dir, char* name, char* ext);
char*   StrToken (char*,char*,int);
char*   RemoveStr (char*,char*);
char*   IRemoveStr (char*,char*);
char*   join (int, ... );
char*   enc (char*, int=0, int=0);
char*   chr(int,int=0,int=0,int=0,int=0,int=0,int=0,int=0,int=0,int=0);
char*   vchr (int,...);
int     InstrRev (char*,char*,int=0,int=0);
int     instr_b(char*,char*,int=0,int=0);
char    *MakeLCaseTbl(void);
char    *_stristr_(char*,char*);
char    *_strstr_(char*,char*);
int     inchr (char*,char*);
int     tally (char*,char*,int=0);
BOOL    Exist   (char*);
char*   ins (char *S, int i, char *a);
char*   del (char*,int,int);
DWORD   lof (char*);
double  Round (double,int);
float   rnd (void);
double  _MIN_ (double,double);
double  _MAX_ (double,double);
int     containedin(char * ,char **,int=0);

// *************************************************
//               User Prototypes
// *************************************************

int     main (int, PCHAR* );
void    EmitCmdLineConst (void);
void    EmitCompilerDefines (void);
void    MakeFreeGlobals (void);
void    ProcessSetCommand (int);
int     Directives (void);
int     SubVarType (int);
char    * PrintWriteFormat (int);
void    EmitInputCode (void);
void    EmitFileInputCode (void);
void    AddFuncs (void);
int     CheckLocal (char *, int* );
int     CheckGlobal (char *, int* );
int     CheckType (char *);
void    ExportInternalConst (void);
int     RestrictedWords (char *);
int     DataType (char *);
void    CloseAll (void);
char    * Clean (char *);
void    RemoveAll (char* ,char* ,int=0);
void    Warning (char* ,int=0);
PCHAR   GetVarTypeName (int);
int     HashNumber (char *);
void    AddLibrary (char *);
void    RemoveLibrary (char *);
void    EmitLibs (void);
void    AddGlobal (char* ,int,int,char* ,int,int,int,int,int=0);
void    AddLocal (char* ,int,int,char* ,int,int,int,int=0);
int     IsNumber (char *);
int     IsNumberEx (char *);
void    StripTabs (void);
void    PushFileIO (void);
void    PopFileIO (void);
int     Inset (char *, char *);
void    CheckParQuotes (void);
void    ClearIfThenStacks (void);
int     IsQuoted (char *);
void    PostProcess (void);
void    XParse (char *);
void    TokenSubstitutions (void);
void    JoinStrings (int, int);
void    Transforms (void);
void    Parse (char *);
void    FuncSubDecs1 (char *);
void    RemEmptyTokens (void);
void    FuncSubDecs2 (char *, int);
void    FuncSubDecs3 (VARCODE* );
void    AddTypeDefs (char *, int);
int     DefsID (char *);
void    GetTypeInfo (char *, int* , int* , int* );
void    AddTypedefElement (int, int, char *, char *, int);
char    * GetElement (int, int* , int* , int);
int     GetElementInfo (int* , int* , char *);
void    HandleNonsense (void);
void    ValidVar (char *);
void    PointerFix (void);
void    DimDynaString (char *, int, int);
int     SubFuncTest (void);
int     DimSubFunc (int);
void    Emit (void);
void    Abort (char *);
void    BumpDown (void);
void    BumpUp (void);
int     BraceCount (char *);
char*   BracketHandler (char *, int);
void    Push (char *);
void    Pop (char *);
void    EmitEpilog (void);
void    EmitProlog (void);
void    DeclareVariables (void);
int     GetNumArgs (int,int* =NULL);
void    GetVarCode (VARCODE* );
void    AddProtos (void);
void    RunTimeFunctions (void);
int     JoinLines (char *);
void    StripCode (char *);
void    ProcSingleLineIf (int* );
int     SplitLines (char *);
int     iMatch (char *, char *, int);
int     iMatchNQ (char *, char *);
int     SpecialCaseHandler (char *);
void    FastLexer (char* ,char* ,char* ,int=1);
void    InsertTokens (int, int, ...);
void    EmitExportDef (char *);
char    * GetArg (int, functionParse* );
int     SepFuncArgs (int, functionParse* , int);
PCHAR   MakeDecProto (functionParse* );
void    AsmUnknownStructs (int);
void    EmitIfCond (char *);
void    PrintGlobal (int, int, char *, char *, char *, char *);
void    ReDirectFPrint (FILE*, char *, ...);
int     IsReservedWord (char *);
int     GetAsPos (void);
void    FreeGlobals (void);


// *************************************************
//            User Global Initialized Arrays
// *************************************************


// *************************************************
//              User GLOBAL SET Statements
// *************************************************

static char* VarTypeLookup[]=
{
  "int","int","char *","double","float","FILE *","long double"
};

static char VarConst[2][8]=
{
  "",
  "const "
};

static char VarStorage[6][18]=
{
  "static ",
  "extern ",
  "",
  "static volatile ",
  "extern volatile ",
  "volatile "
};

static char* ReservedWord[]=
{
  "IF",
  "ELSEIF",
  "THEN",
  "ELSE",
  "AND",
  "OR",
  "NOT",
  "BOR",
  "BAND",
  "XOR",
  ""
};


// *******************************************************************************
// Developer Guidelines
// *******************************************************************************
// Code should be written in BCX Basic. If it can not be written in BCX Basic for
// some reason or results in code that seems too inefficient then this may be a
// cue that a new Basic function is needed.
// * All KEYWORDS should be capitalized
// * Use two space indentation
// * Use spaces not tabs
// * Record all notes in reverse chronological order
// * And most importantly....Have fun!
// ******************************************************************************************
// This section is used to communicate to-do 's, changes, ideas, suggestions, etc.
// ******************************************************************************************
// -------------------------------------------
// 2022-07-26 Armando Rivera
// After a LONG time away....
//   * Changed max size of szTmp$, Src$, and AbortSrc$ (65535)to avoid potential buffer overflows
//   * Changed max size of WarnMsg$ (65536) to avoid potential buffer overflow
//   * Removed the "register" decorator from EOF function to comply with C++17 standard
//   * The above addressed warnings thrown by C++17, which is the standard on modern Linux.
//   * Removed cdecl/stdcall from "Declare Function" (dynamic linking), since cdecl is the standard on *nix systems
// -------------------------------------------
// 2018-12-12 Armando Rivera
//   * Changed BcxRegEx function to REGMATCH
//   * Changed BcxRegEx keyword to REGMATCH
//   * Added $MODULE as alias to $INCLUDE to support external modules.  ** MUST BE AT TOP OF MAIN SOURCE FILE **
//   * Added $LDFLAGS directive to support external modules
// -------------------------------------------
// -------------------------------------------
// 2016-02-15 Armando Rivera
// -------------------------------------------
//   * Changed default string size to 65K from 
//     2k, which was limiting.
//   * Updated output of PRINT command, eliminating
//     leading spaces from numbers.
// -------------------------------------------
// 2015-07-03 Armando Rivera
// -------------------------------------------
//   * Changed $OSX flag to use Cocoa instead of Carbon in MacOS
//     This is in preparation of the new custom libcocoa library
//     that I'm currently creating that will allow mbc
//     to create 64bit GUI applications in OSX
// -------------------------------------------
// 2013-06-26 Armando Rivera
// -------------------------------------------
//   * Added BcxRegex keyword, based on Posix Regex in Libc
//   * Broke up main source file into files containing Runtime, Declarations, etc.
//   * Added BYTE type
// 
// -------------------------------------------
// 2013-06-17 Armando Rivera
// -------------------------------------------
//   * Tweaked HEX$ so that it will emit 2-digit hex numbers
//   * Added PUCHAR (unsigned char*) typedef
// -------------------------------------------
// 2011-03-11 Armando Rivera
// -------------------------------------------
//   * Added Wayne's suggestion to support Reference Variables as return types.
// 
// -------------------------------------------
// 2011-03-10 Armando Rivera
// -------------------------------------------
//   * Ported $PROJECT directive from ConsoleBC.  This doesn't emit the RTL yet, but it's a start.
//     It's the first step towards re-writing the RT code to leverage CPP/WX.
// 
//   * Fixed bug where BCX_TmpStr sometimes wasn't emitted when returning a string from a function
// 
//   * Added Named Enum support.  Syntax:
//       myenum AS ENUM
//       …
//       END ENUM
// 
//       This required moving the Enum emit code to before the User Prototype emit code
//       to allow passing the named enum to user defined functions.
// 
// -------------------------------------------
// 2011-01-23 Armando Rivera
// -------------------------------------------
//   * Initial Beta1 Release
// 
//   * Fixed bug in INPUT statement to remove trailing newlines (James Fuller)
// 
//   * Removed COLOR statements to avoid terminal output issues with redirected
//     translator output (James Fuller)
// 
//   * Added CONST keyword when declaring variables (Global, Local, and as Function/Sub parameters)
//     At the moment, this is experimental (meaning I haven't fully tested it) but it seems to work
// 
//   * Added PRIVATE keyword for CPP classes
// -------------------------------------------
// 2010/12/21  Armando Rivera
// -------------------------------------------
//   * Cleaned up code emission so that unneeded defines/global vars are not emitted
// 
//   * Added new $IOS directive, which is MAC ONLY, to compile source for iDevices (iPhone/iTouch/AppleTV2)
//     At this point in time, running binaries built this way requires a jailbroken iDevice.
//     This is experimental, and for console apps only for now.
//     A simple console example is in the Examples/IOS folder
// -------------------------------------------
// 2010/12/11  Armando Rivera
// -------------------------------------------
//  * Add new Socket keywords: BcxSocket, BcxSocketSend, BcxSocketRead, and BcxSocketClose
//   See the BcxSocket.bas demo in the Examples/Socket folder for info.
// 
//  * Added kbhit() , which doesn't exist outside of Windows
//   This is a custom sub which emulates what kbhit() does
// 
//  * Changed the conditional emission of term.h to only be emitted when
//   Use_Keypress is TRUE (InKey)
// 
// -------------------------------------------
// 2010/12/01  Armando Rivera
// -------------------------------------------
//  * Changed wxApp emission to use BCXPLITHPATH$, per James Fuller's suggestion.
// 
//  * Added support for Abstract Classes (gcc doesn't have the INTERFACE keyword)
// 
//   Example:
//    Class MyAbstractClass
//     public
// 
//      virtual sub Proc1() = 0
//      Virtual sub Proc2()=0
//      virtual function Proc3(a$,b$) as integer = 0
// 
//    End Class
// -------------------------------------------
// 2010/11/30  Armando Rivera
// -------------------------------------------
//  * Removed $CLASS/$ENDCLASS $NAMESPACE/$ENDNAMESPACE
//   Using either will emit a message stating that they have been replaced.
// 
//  * Addded NAMESPACE / END NAMESPACE
//   This allows creating methods within the NAMESPACE like so:
// 
//   $CPP
//   $NOMAIN
//   $EXECON
//   '==============================================================================
//   NAMESPACE Dlg_01
//    Sub DoIt()
//     Print "Dlg_01"
//    End Sub
// 
//    Function GetString$(A$) as string
//     function = "The String you Passed Was: " + enc$(A$)
//    end function
//   END NAMESPACE
//   '==============================================================================
//   Function main(argc as INTEGER, argv as PCHAR ptr) as INTEGER
//    Print "James"
//    Dlg_01::DoIt()
//    print Dlg_01::GetString$("Hello, World!")
//   End Function
// 
//   * If using $WX, the #define for Clear() will not be emitted due to conflict
//     with Classes that have that method defined
// 
//   * Made the inclusion of "term.h" conditional based on whether $WX/$WXC
//     is used.  "term.h" is required for the implementation of
//     the PAUSE keyword in CONSOLE apps.
// 
// -------------------------------------------
// 2010/11/25  Armando Rivera
// -------------------------------------------
//   * Changed code so that in $CPP mode, the case of the emitted
//     .cpp filename is preserved (James Fuller bug report)
// 
// -------------------------------------------
// 2010/11/24  Armando Rivera
// -------------------------------------------
//   * Minor change in StripCode() to correct
//     possible overflow issue under 64bit Linux (James Fuller bug report)
// 
//   * Added $WXC Directive to support WX Console-Based Apps
//     Using this switch, neither a wxApp or the IMPLEMENT_APP() macro are
//     auto added to the translated source (James Fuller request)
// -------------------------------------------
// 2010/11/20  Armando Rivera
// -------------------------------------------
//  * Changed $DLL directive so that it would generate *nix Shared Libraries.
//  * Added $DLL support to $EXECON
//  * Added required flags to LD_FLAGS$ for creating *nix Shared Libraries
//   Example:
//    $dll
//    $execon
// 
//    function printdemo() export
//     print "This was called from a Dynamic Library"
//    end function
// 
//   Note that this is currently only useful for creating shared libraries
//   for **OTHER** languages; it won't work with MBC created apps because of
//   duplicate naming conflicts.
// 
// -------------------------------------------
// 2010/11/18  Armando Rivera
// -------------------------------------------
//   * Removed "-Os" compiler optimization flag from $EXECON for fastest tranlator compliation
//     during Alpha testing stage.
// 
//     This will be re-added when translator is not longer in Alpha status
// 
//   * Added USE_CTOR global as flag for supporting Constructor/Destructor syntax
// 
//   * Added "USING" keyword for CONSTRUCTOR/DESTRUCTOR methods.  It is used like this:
// 
//       CONSTRUCTOR MainWin::MainWin(title as wxString, winStyle as long) USING wxFrame( 0, -1, title, wxPoint(50,50), wxSize(490,296), winStyle )
// 
//     Which will emit:
// 
//       MainWin::MainWin (wxString title, long winStyle)
//       : wxFrame( 0, -1, title, wxPoint(50,50), wxSize(490,296), winStyle )
//       {
// 
//   * Added code to extract and emit derived class methods
// 
// -------------------------------------------
// 2010/11/17  Armando Rivera
// -------------------------------------------
//   * Added new CLASS / END CLASS / PUBLIC / PROTECTED / CONSTRUCTOR / DESTRUCTOR keywords.
//     These additions flesh out Basic-Like C++ CLASS support, superceding $CLASS/$ENDCLASS,
//     and now allows syntax like the following:
// 
//         $CPP
//         $NOMAIN
//         $execon
// 
//         class MyClass
// 
//          protected
//           first as string
//           secnd$
//           third%
// 
//          public
//           type ATest
//            a as PCHAR
//            b as long
//            c as single
//            d as float
//           end type
// 
//          Constructor MyClass(a$, b)
//          Destructor MyClass()
//         end class
// 
//         FUNCTION main(argc as INTEGER, argv as PCHAR ptr) as INTEGER
//           RAW theClass as MyClass PTR
// 
//           theClass = new MyClass("Hello", 12)
// 
//           print (char*)theClass->ATest.a
//           print theClass->ATest.b
//         END FUNCTION
// 
//         Constructor MyClass::MyClass(a$,b)
//           ATest.a = a$
//           ATest.b = b
//         END Constructor
//         '
//         Destructor MyClass::~MyClass()
// 
//         END Destructor
// 
// -------------------------------------------
// 2010/11/12  Armando Rivera
// -------------------------------------------
//   * Added code that (mostly) eliminates the need for a trailing ";" in $class/$endclass
// 
//   * Added code to allow the use of "SUB" in $class/$endclass.  It just substitutes "void" for "sub"
//     at this point.
// 
//   * Fixed "THIS" keyword code so that it emits a lowercase "this".  Linux/OSX aren't affected
//     by this breaking COM statements. :-P  Thanks to JCFULLER for the tip!
// 
//   * For $CPP mode, added typedefs for std::string (CSTRING) and std::fstream (CFILE)
//     These are direct replacements for STRING and FILE, and allows the full use of each
//     C++ object/class.
// 
//     So instead of "dim mystring as string", for example, you would do "dim mystring as CSTRING".
//     You would then have access to all of std::string's methods like .replace, .substr, .compare, etc.
// 
//     I'm considering doing the same with the other toolkit directives ($OSX, $GTK, etc) but we'll see...
// 
//   * Added "inherits" in $CPP mode so that subclassing can be done like so:
// 
//     $class MyClass inherits AnotherClass
// 
//   * For $WX mode, added code to automatically emit the required derived wxApp class.
//    Note that it will be named the same as your sourcefile (minus the extension), and you MUST provide
//    a "FUNCTION ::OnInit() as bool" for it:
// 
//     FUNCTION TestApp::OnInit() as bool
//      <initialize app here>
//     END FUNCTION
// 
//   * For $WX mode, made "$NOMAIN" the default, so no need to pass that directive
// 
//   * Colorized some of the compiler output text.  Just because I can.
// 
//   * Back-ported Wayne's changes to "WITH" to allow the use of "->" syntax
// 
//   * TODO:
//       Finish off the $class/$endclass code to allow full basic syntax for method and variable
//       declarations.
// 
//       Remove ALL remaining WIN32 related code and ifdefs.
//       No need for that stuff under Linux/OSX, the Windows version of BCX can handle all
//       of the Windows stuff one might need.
// 
//       Other stuff I can't remember right now…..
// -------------------------------------------
// 2010/03/31  Armando Rivera
// Beginning with this version of the console compiler,
// the goal is to have a 100% unified code-base, because
// I'm fracking tired of trying to maintain separate builds
// for different Operating Systems.
// -------------------------------------------
// 
//   * Added $OSX, $GTK¸$GLIB and $WX Directives
//     (Use_Osx, Use_Wx, Use_Gtk, Use_Glib and LD_FLAGS$ Globals added)
// 
//     $OSX will automatically enable Carbon GUI support, and if $EXECON is invoked
//     will also build a Universal Binary with 32bit and 64bit support
// 
//     $GTK will automatically enable GTK/GLIB support, and if $EXECON is invoked
//     will build the executable linking in libgtk and it's support libraries.
// 
//     $GLIB will automatically enable >GLIB ONLY< support, and if $EXECON is invoked
//     will build the executable linking in libglib and it's support libraries.
// 
//     $WX will automatically enable wxWidgets with $CPP set to "TRUE", and if $EXECON
//     is invoked will build the executable linking in libwx and it's support libraries
// 
//     This is, in part, in preparation for moving the GTK support from the core of the
//     LinuxBC translator to an external library which will be linked in as required.  This
//     will GREATLY simplify maintenence of the translator core once the lib  is ready.
// 
//   * Changed alls instances of byte* to UCHAR* in SWAP() Function
// 
//   * Added internal return values for PUT/GET to get rid of ALL compiler warnings.
// 
//   * Updated runtime functions calling PUT()/GET()/fread()/fwrite  so that they
//     will not trigger compiler warnings
// 
//   * Reworked the way functions declared using C_DECLARE with the LIB and ALIAS keywords
//     are emitted.  This is so that you can dynamically load functions from a shared
//     library at runtime via dlopen/dlsym.
// 
//     The syntax is:
//     C_DECLARE FUNCTION <YOUR FUNCTION NAME> LIB <shared library> ALIAS <quoted name of actual function (<parameters>) AS <return type>
// 
//     For example:
//     C_DECLARE FUNCTION b64encode LIB "libglib-2.0.so" ALIAS "g_base64_encode" (txt AS char*, length AS integer) AS string
//     C_DECLARE FUNCTION g_base64_decode LIB "libglib-2.0.so" ALIAS "g_base64_decode" (txt AS char*, length AS INTEGER PTR) AS string
// 
//     NOTE that the ALIAS is the actual name of the function you want to call from the shared library.
//     This is so you avoid redeclaration errors if you attempt to link to a library (libm is a good example)
//     that is already compile-time linked with g++.
// 
//     NOTE 2: There is currently no checking whether the function was loaded without error.  It is on the TODO list.
// 
//   * Changed compiler invocation to include -Wformat and -D_FORTIFY_SOURCE=2 (Ubuntu Standard)
// 
//   * Fixed User Include File handling in order to support mixed case filenames
// 
//   * Updated the CURDIR$, TEMPDIR$, AND SHELL code to eliminate warnings emitted when compiling on
//     a system that has "_FORTIFY_SOURCE=2" enabled by default in GCC/G++ (Ubuntu)
// 
//   * Fixed a potential overflow problem with LINE INPUT that would also cause G++ to emit
//      warnings as above.
// 
//   *Re-coded the $RESOURCE directive and the GETRESOURCE$ function to allow
//    linking of Resources under Linux/Unix.  Using $RESOURCE generates a #define
//    allowing you to reference the embedded resource using an arbitrary IDENTIFIER.
// 
//   For example:
// 
//     DIRECTIVE    FILE    IDENTIFIER
//     -------------------------------
//     $RESOURCE "file.txt"  "myres"
// 
// 
//   Note that you reference the resource using the identifier you passed as the
//   SECOND parameter to the $RESOURCE directive, minus the quotes.
// 
//   "file.txt" above can be any arbitrary file on one's system
// 
//   At the moment, the resource is returned as a string with the GETRESOURCE$ function.
//   *****************************************************************************************************
//   ** YOU WILL HAVE TO ENSURE THAT A BUFFER WITH ENOUGH SPACE TO HOLD THE RESOURCE HAS BEEN ALLOCATED **
//   *****************************************************************************************************
//   To aid in this, a constant is automatically created with the size of the resource.  It will have the
//   name you specified as the second parameter to $RESOURCE, with _SIZE appended.
//   Using the example above, the constant would be defined as: myres_SIZE
// 
// 
//   You should be able to manually cast the reference *itself* to what you require, since it is
//   merely a pointer to the location of the resource itself.
// 
//   The resource will be converted to an object file, named using the filename provided with ".o" apppended.
//   "file.txt" will be converted to "file.txt.o" in the above example, which can then be linked
//   to the final executable via $EXECON "file.txt.o" or $EXEGUI "file.txt.o"
// 
//   * Tweaked $GUI directive and GUI keyword so that one can use the directive without
//   having all of the support for BCX_* form objects automatically added to one's app.
// 
//   This is usefull when using GtkBuilder or Glade to build the user interface.
// 
// -------------------------------------------
// 2010-01-17 Armando Rivera
// -------------------------------------------
//   modified the $CLASS/$ENDCLASS directives to allow creation and inheritance of C++ Classes
// 
//   modified the Function/Sub prototype emitter so that it would not emit prototypes
//     for C++ Class Methods, which are supposed to be prototyped within the Class itself
// 
//   made the inclusion of <term.h> conditional based on whether UseCPP is true/false
//     it will not be included if UseCpp is "true" because some C++ toolkits (wxWidgets)
//     throw a "redefined" error when it's included
// 
// -------------------------------------------
// 2010-01-15 Armando Rivera
// -------------------------------------------
//   per wmhalsdorf's recommendation, modified SplitLines and Emit procs to support
//     C++ Method syntax (CLASSNAME::METHOD) [see Yahoo group Message #40282]
// 
// -------------------------------------------
// 2010-01-10 Armando Rivera
// -------------------------------------------
//   changed $CPP directive to output lowercase filenames
// 
// -------------------------------------------
// 2009-10-18 Armando Rivera
// -------------------------------------------
//   added Carbon.h as a default include, to support Carbon/CoreFoundation calls
//   added Carbon framework to $execon section
//   removed TRUE and FALSE defines, which are now provided by Carbon.h
//   changed Handle$ to Handl$ to resolve conflict with Carbon.h
// 
// -------------------------------------------
// 2009-10-13 Armando Rivera
// -------------------------------------------
//   added typedef for "byte" type (typedef unsigned char byte;)
// 

// *************************************************
//                 Runtime Functions
// *************************************************

char *BCX_TmpStr (size_t Bites)
{
  static int   StrCnt;
  static char *StrFunc[512];
  StrCnt=((StrCnt+1) &511);
    #if defined BCX_MAX_VAR_SIZE
  if(Bites*sizeof(char)>BCX_MAX_VAR_SIZE)
  {
  printf("Buffer Overflow caught in BCX_TmpStr - requested space of %d EXCEEDS %d\n",(int)(Bites*sizeof(char)),BCX_MAX_VAR_SIZE);
  abort();
  }
  #endif
  StrFunc[StrCnt]=(char*)realloc(StrFunc[StrCnt],Bites + 128);
  return (char*)memset(StrFunc[StrCnt],0,Bites+128);
}


int str_cmp (char *a, char *b)
{
  int counter=0;
  for(;;)
   {
    if((a[counter]^b[counter]))
     {
      if((UINT) a[counter]>= (UINT) b[counter])
      return  1;
      return -1;
     }
    if(!a[counter]) return 0;
    counter++;
   }
}


int EoF (FILE* stream)
{
  int c, status = ((c = fgetc(stream)) == EOF);
  ungetc(c,stream);
  return status;
}


char *left (char *S, int length)
{
  int tmplen = strlen(S);
  if(length<1) return BCX_TmpStr(1);
  if(length<tmplen) tmplen=length;
  char *strtmp = BCX_TmpStr(tmplen);
  return (char*)memcpy(strtmp,S,tmplen);
}


char *right (char *S, int length)
{
  int tmplen = strlen(S);
  char *BCX_RetStr = BCX_TmpStr(tmplen);
  tmplen -= length;
  if (tmplen<0) tmplen = 0;
  return strcpy(BCX_RetStr, &S[tmplen]);
}


char *rpad (char *a, int L, int c)
{
  char *strtmp;
  int s = strlen(a);
  if((L-s)<1) return a;
  strtmp=BCX_TmpStr(L);
  strcpy(strtmp,a);
  memset(&strtmp[s],c,(L-s));
  return strtmp;
}


char *lpad (char *a, int L, int c)
{
  char *strtmp;
  L=L-strlen(a);
  if(L<1) return a;
  strtmp = BCX_TmpStr(L);
  memset(strtmp,c,L);
  return strcat(strtmp,a);
}


char *mid (char *S, int start, int length)
{
  char *strtmp;
  int tmplen = strlen(S);
  if(start>tmplen||start<1) return BCX_TmpStr(1);
  if (length<0 || length>(tmplen-start)+1)
    length = (tmplen-start)+1;
  strtmp = BCX_TmpStr(length);
  return (char*)memcpy(strtmp,&S[start-1],length);
}


char *trim (char *S)
{
  while(*S==32 || *S==9 || *S==10 || *S==11 || *S==13)
    S++;
  int i = strlen(S);
  while( i>0 && (S[i-1]==32 || S[i-1]==9 || S[i-1]==10
             || S[i-1]==11 || S[i-1]==13))
    i--;
  char *strtmp=BCX_TmpStr(i);
  return (char*)memcpy(strtmp,S,i);
}


char *ltrim (char *S, char c)
{
  if(S[0]==0) return S;
  while((*S==32 || *S==c) && *S !=0) S++;
  char *strtmp = BCX_TmpStr(strlen(S));
  return strcpy(strtmp,S);
}


char *rtrim (char *S,char c)
{
  if(S[0]==0) return S;
  int i = strlen(S);
  while(i>0 && (S[i-1]==c || S[i-1]==32))
    i--;
  char *strtmp = BCX_TmpStr(i);
  return (char*)memcpy(strtmp,S,i);
}


char *strim (char *src)
{
  char *strtmp = BCX_TmpStr(strlen(src));
  char *dst = strtmp;
  while (isspace((unsigned char)*src)) src++;
  do
  {
    while (*src && !isspace((unsigned char)*src)) *dst++ = *src++;
    if (*src)
      {
        *dst++ = *src++;
        while (isspace((unsigned char)*src)) src++;
      }
  } while (*src);
  if (isspace((unsigned char)*(--dst))) *dst = 0;
  return strtmp;
}


char *command (int nArg)
 {
 int i = 0;
 char *retstr=BCX_TmpStr(1);
 if(nArg < i) // return entire commandline
    {
      retstr = BCX_TmpStr(G_argc * 2048);
      for(i=1; i < G_argc; i++)
         {
         strcat(retstr, G_argv[i]);
         strcat(retstr, SPC);
         }
    }
 else if(nArg < G_argc)
    {
      retstr = BCX_TmpStr(strlen(G_argv[nArg]) + 1);
      strcpy(retstr, G_argv[nArg]);
    }
 return retstr;
}


char *extract (char *mane, char *match)
{
  char *a;
  char *strtmp = BCX_TmpStr(strlen(mane));
  if(*match!=0)
    {
      a=_strstr_(mane,match);
      if(a) return (char*)memcpy(strtmp,mane,a-mane);
    }
  return strcpy(strtmp,mane);
}


char *remain (char *mane, char *mat)
{
  char *p = strstr(mane,mat);
  if(p)
  {
    p+=(strlen(mat));
    return p;
  }
  return mane;
}


char *replace (char *src, char *pat, char *rep)
{
  size_t patsz, repsz, tmpsz, delta;
  char *strtmp, *p, *q, *r;
  if (!pat || !*pat)
   {
     strtmp = BCX_TmpStr(strlen(src));
     if (!strtmp) return NULL;
     return strcpy(strtmp, src);
   }
  repsz = strlen(rep);
  patsz = strlen(pat);
  for (tmpsz=0, p=src; (q=_strstr_(p,pat))!=0; p=q+patsz)
   tmpsz += (size_t) (q - p) + repsz;
   tmpsz += strlen(p);
   strtmp = BCX_TmpStr(tmpsz);
   if (!strtmp) return NULL;
    for (r=strtmp,p=src; (q=_strstr_(p,pat))!=0;p=q+patsz)
     {
       delta = (size_t) (q-p);
       memcpy(r,p,delta); r += delta;
       strcpy(r,rep);      r += repsz;
     }
  strcpy(r,p);
  return strtmp;
}


char *ucase (char *S)
{
  char *strtmp = BCX_TmpStr(strlen(S));
  return _strupr_(strcpy(strtmp,S));
}


char *lcase (char *S)
{
  char *strtmp = BCX_TmpStr(strlen(S));
  return _strlwr_(strcpy(strtmp,S));
}


char *RemoveStr (char *a, char *b)
{
  char *strtmp, *p, *d;
  int  tmplen;
  strtmp = d = BCX_TmpStr(strlen(a));
  if(!b || !*b) return strcpy(strtmp,a);
  p=_strstr_(a,b); tmplen = strlen(b);
  while(p)
   {
     memcpy(d,a,p-a);
     d+= (p-a);
     a=p+tmplen;
     p=_strstr_(a,b);
   }
  strcpy(d,a);
  return strtmp;
}


char *IRemoveStr (char *a, char *b)
{
  char *strtmp, *p, *d;
  int  tmplen;
  strtmp = d = BCX_TmpStr(strlen(a));
  if(!b || !*b) return strcpy(strtmp,a);
  p=_stristr_(a,b); tmplen = strlen(b);
  while(p)
   {
     memcpy(d,a,p-a);
     d+= (p-a);
     a=p+tmplen;
     p=_stristr_(a,b);
   }
  strcpy(d,a);
  return strtmp;
}


char *ins (char *S, int i, char *a)
{
  int j = strlen(S);
  if(i<1 || i>j+1) return S;
  char *strtmp = BCX_TmpStr(j + strlen(a));
  memcpy(strtmp,S,--i);
  strcpy(&strtmp[i],a);
  return strcat(strtmp,&S[i]);
}


char *del (char *S, int i, int j)
{
  int ln = strlen(S);
  if(i<1 || i>ln) return S;
  char *strtmp = BCX_TmpStr(ln);
  memcpy(strtmp,S,--i);
  return strcat(strtmp,&S[i+j]);
}


char *str (double d)
{
  char *strtmp = BCX_TmpStr(16);
  sprintf(strtmp,"% .15G",d);
  return strtmp;
}


char *curdir (void)
{
  char *strtmp = BCX_TmpStr(2048);
  char *res=getcwd(strtmp, 1024);
  return strtmp;
}


char *tempdir (void)
{
  char *strtmp = BCX_TmpStr(2048);
  if(!Exist("/tmp/mbc.compiler")) {
    mkdir ("/tmp/mbc.compiler",0755);
  }
  strcpy(strtmp,"/tmp/mbc.compiler");
  return strtmp;
}


char *stringx (int count, int a)
{
  if(count<1) return BCX_TmpStr(1);
  char *strtmp = BCX_TmpStr(count);
  return (char*)memset(strtmp,a,count);
}


void Shell (char *cmd)
{
  int res=system(cmd);
}


char *space (int count)
{
  if(count<1) return BCX_TmpStr(1);
  char *strtmp = BCX_TmpStr(count);
  return (char*)memset(strtmp,32,count);
}


char *enc (char *A, int L, int R)
{
  char *BCX_RetStr = BCX_TmpStr(strlen(A)+3);
  if(L==0) L=34;
  if(R==0) R=L;
  sprintf(BCX_RetStr,"%c%s%c%s",L,A,R,"");
  return BCX_RetStr;
}


char *chr (int a,int b,int c,int d,int e,int f,int g,int h,int i,int j)
{
  char *strtmp = BCX_TmpStr(11);
  strtmp[0]  = a;
  strtmp[1]  = b;
  strtmp[2]  = c;
  strtmp[3]  = d;
  strtmp[4]  = e;
  strtmp[5]  = f;
  strtmp[6]  = g;
  strtmp[7]  = h;
  strtmp[8]  = i;
  strtmp[9]  = j;
  strtmp[10] = 0;
  return strtmp;
}


char *vchr(int charcount, ...)
{
  int c = 0, i = charcount;
  char *s_ = BCX_TmpStr(charcount + 1);
  va_list marker;
  s_[i] = 0;
  va_start(marker, charcount);
  while(i-- > 0) s_[c++] = va_arg(marker,int);
  va_end(marker);
  return s_;
}


char * join(int n, ...)
{
  int i = n, tmplen = 0;
  char *strtmp, *s_;

  va_list marker;
  va_start(marker, n); // Initialize variable arguments
  while(i-- > 0)
  {
    s_ = va_arg(marker, char *);
    if(s_) tmplen += strlen(s_);
  }
  strtmp = BCX_TmpStr(tmplen);
  va_end(marker); // Reset variable arguments
  i = n;
  va_start(marker, n); // Initialize variable arguments
  while(i-- > 0)
  {
    s_ = va_arg(marker, char *);
    if(s_) strcat(strtmp, s_);
  }
  va_end(marker); // Reset variable arguments
  return strtmp;
}


char* Environ(char *S)
{
  char *strtmp, *tmp;

  tmp = getenv(S);
  if(tmp != NULL) {
    strtmp = BCX_TmpStr(strlen(tmp)+1);
    return strcpy(strtmp, tmp);
  }
  return BCX_TmpStr(1);
}


char *AppExePath (void)
{
  char fullpath[MAX_PATH];
  int length;
  length = readlink("/proc/self/exe", fullpath, MAX_PATH);
  if(length < 1) return BCX_TmpStr(1);

  fullpath[length] = 0;
  return BcxSplitPath(fullpath, FDRV|FPATH);
}


char *AppExeName (void)
{
  return BcxSplitPath(G_argv[0], FNAME|FEXT);
}


char * TempFileName (char *dr, char *prefix)
{
  static unsigned int count;
  char *f, *tmpstr = BCX_TmpStr(MAX_PATH);
  int  i, length;

  if(!count) srand(time(0));

  if(dr) strcpy(tmpstr, dr);
  length = strlen(tmpstr);
  if(length && (tmpstr[length-1] != '\\' && tmpstr[length-1] != '/'))
      tmpstr[length++] = '/';
  if(prefix) strcpy(&tmpstr[length], prefix);
  f = &tmpstr[strlen(tmpstr)];

  do {
      count++;
      for(i=0; i<5; i+=1)
        {
          do {
            f[i]=(char)(rnd()*122);
          }while((f[i]<65)||(f[i]>90&&f[i]<97));
        }
        snprintf(&f[5],3,"%x", count);
    } while (Exist(tmpstr));

  return tmpstr;
}


int InstrRev (char *s, char *p, int os, int sens)
{
 int sl, pl, ox;
 int (*cmp)(const char *, const char *, size_t );

 if (!s || !p)  return 0;
 sl  = strlen(s); pl  = strlen(p);
 if (os > sl || sl == 0 || pl == 0 || (ox = sl - pl) < 0)
   return 0;

 if (os <= 0)  
   os = ox ;
 else if(os >= pl)
   os = os - pl ;
 else
   return 0;

 cmp = (sens ? strncasecmp : strncmp);
 do { if (cmp(s + os , p, pl) == 0)
       return os+1;
    } while (os--);
 return 0;
}


int instr_b(char* mane,char* match,int offset,int sensflag)
{
  char *s;
  if (!mane || !match || ! *match || offset>(int)strlen(mane)) return 0;
  if (sensflag)
    s = _stristr_(offset>0 ? mane+offset-1 : mane,match);
  else
    s = _strstr_(offset>0 ? mane+offset-1 : mane,match);
  return s ? (int)(s-mane)+1 : 0;
}


char  *MakeLCaseTbl (void)
{
  static char tbl[256];
  if(!tbl['a'])
    {
      int i; for (i=0; i < 256; i++)
        tbl[i] = (char)(int)tolower(i);
    }
  return tbl;
}


char *_stristr_(char *String, char *Pattern)
{
  int   mi=-1;
  char *LowCase = MakeLCaseTbl();
  while(Pattern[++mi])
   {
     if(String[mi]==0) return 0;
     if(LowCase[(unsigned char)String[mi]]!=LowCase[(unsigned char)Pattern[mi]])
       { String++; mi=-1; }
   }
  return String;
}


char *_strstr_(char *String, char *Pattern)
{
  int   mi=-1;
  while(Pattern[++mi])
   {
     if(String[mi]==0) return 0;
     if(String[mi]!=Pattern[mi])
       { String++; mi=-1; }
   }
  return String;
}


int inchr (char *A, char *B)
{
  char* C=A;
  while(*C)
    {
      if(*C==*B) return C-A+1;
      C++;
    }
  return 0;
}


double Round (double n, int d)
{
  return (floor((n)*pow(10.0,(d))+0.5)/pow(10.0,(d)));
}


bool Exist (char *szFilePath)
{
  int retstat;
  struct stat sb;
  retstat = stat(szFilePath, &sb);
  if(retstat != -1)
    return TRUE;
  return FALSE;
}


int tally (char *szLine, char *szChar, int sensflag)
{
  if(!*szChar) return 0;
  int   mlen = strlen(szChar);
  int  iCount = 0;
  char *p = (sensflag == 0 ? _strstr_(szLine, szChar) : _stristr_(szLine, szChar));
  while (p)
  {
    iCount++;
    p+=mlen;
 p = (sensflag == 0 ? _strstr_(p, szChar) : _stristr_(p, szChar));
  }
  return iCount;
}


float rnd (void)
{
  return (float)rand()/RAND_MAX;
}


double _MAX_ (double a, double b)
{
  if(a>b)
  return a;
  return b;
}


double _MIN_ (double a, double b)
{
  if(a<b)
  return a;
  return b;
}


void locate (int row,int col,int show,int shape)
{
  printf("%c%s%u%s%u%s",27,"[",row,";",col,"H");
  // find cursor size/shape function!
}


void cls (void)
{
  printf("%s%s%s%s",ESC,"[2J",ESC,"[H");
}


void midstr (char *src, int st, int length, char *rep)
{
  int srclen = strlen(src);
  if(st>srclen++ || st<1) return;
  int replen = strlen(rep);
  if(replen < length || length==-1) length=replen;
  if((st+length) > srclen) length=srclen-st;
  memcpy(&src[st-1],rep,length);
}


DWORD lof (char *FileName)
{

  int retstat;
  struct stat sb;
  retstat = stat(FileName, &sb);
  if(retstat != -1)
    return sb.st_size;
  return 0;
}


char * sziif (bool i, char *a, char *b)
{
  if(i) return a;
  return b;
}


char *BcxSplitPath (char *FPath, int mask)
{
  if(!FPath) return BCX_TmpStr(1);
  char *BCX_RetStr=BCX_TmpStr(strlen(FPath));
  char tmp[MAX_PATH*4];
  _splitpath_(FPath,tmp,&tmp[MAX_PATH],&tmp[MAX_PATH*2],&tmp[MAX_PATH*3]);
  if(mask & FDRV) strcat(BCX_RetStr,tmp);
  if(mask & FPATH)strcat(BCX_RetStr,&tmp[MAX_PATH]);
  if(mask & FNAME)strcat(BCX_RetStr,&tmp[MAX_PATH*2]);
  if(mask & FEXT) strcat(BCX_RetStr,&tmp[MAX_PATH*3]);
  return BCX_RetStr;
}


 void _splitpath_(const char* path, char* drv, char* dir, char* name, char* ext)
 {
     const char* pend; /* end of processed string */
     const char* p;   /* search pointer */
     const char* s;   /* copy pointer */
 
     /* extract drive name */
     if (path[0] && path[1]==':') {
         if (drv) {
             *drv++ = *path++;
             *drv++ = *path++;
             *drv = 0;
         }
     } else if (drv)
         *drv = 0;
 
     /* search for end of string or stream separator */
     for(pend=path; *pend && *pend!=':'; )
         pend++;
 
     /* search for begin of file extension */
     for(p=pend; p > path && *--p != '\\' && *p!='/'; )
         if (*p == '.') {
             pend = p;
             break;
         }
 
     if (ext)
     {
         s=pend;
         do{ *ext++ = *s; } while(*s++);
     }
     /* search for end of directory name */
     for(p=pend; p > path; )
         if (*--p == '\\' || *p == '/') {
             p++;
             break;
         }
 
     if (name) {
         for(s=p; s<pend; )
             *name++ = *s++;
 
         *name = 0;
     }
 
     if (dir) {
         for(s=path; s<p; )
             *dir++ = *s++;
 
         *dir = 0;
     }
 }

char *_strupr_(char *string)
{
   char *s;

   if (string)
   {
      for(s = string; *s; ++s)
         *s = toupper(*s);
   }
   return string;
}

char *_strlwr_(char *string)
{
    char *s;

    if (string)
    {
       for (s = string; *s; ++s)
           *s = tolower(*s);
    }
    return string;
}

char * StrToken (char *Source, char *TokenChar, int n)
{
  char *BCX_RetStr={0};
  char *RetVal;
  char *Copy;
  int   Posn=0;
  int   Find=0;
  int   LenSrc=strlen(Source);
  RetVal=(char*)calloc(LenSrc+1,1);
  Copy=Source;
  if(tally(Source,TokenChar)==0)
    {
      BCX_RetStr=BCX_TmpStr(1);
      if(RetVal)free(RetVal);
      return BCX_RetStr;
    }
  if(n==1)
    {
      BCX_RetStr=BCX_TmpStr(LenSrc);
      strcpy(BCX_RetStr,(char*)extract(Source,TokenChar));
      if(RetVal)free(RetVal);
      return BCX_RetStr;
    }
  if(n>tally(Source,TokenChar)+1)
    {
      BCX_RetStr=BCX_TmpStr(1);
      if(RetVal)free(RetVal);
      return BCX_RetStr;
    }
  while(*Copy)
    {
      if(*Copy==TokenChar[0]) Find++;
      if(Find==n) break;
      Copy++;
      Posn++;
    }
  if(n==tally(Source,TokenChar)+1)
    {
      Posn=LenSrc;
      Copy=Source+Posn;
      while(*Copy&&Source[Posn]!=TokenChar[0])
        {
          Posn--;
          Copy--;
        }
    }
  strcpy(RetVal,(char*)mid(Source,1,Posn));
  strcpy(RetVal,(char*)mid(RetVal,InstrRev(RetVal,TokenChar)));
  BCX_RetStr=BCX_TmpStr(LenSrc);
  strcpy(BCX_RetStr,(char*)RemoveStr(RetVal,TokenChar));
  if(RetVal)free(RetVal);
  return BCX_RetStr;
}


char *iReplace (char *src, char *pat, char *rep)
{
  size_t patsz, repsz, tmpsz, delta;
  char *strtmp, *p, *q, *r;
  if (!pat || !*pat)
   {
     strtmp = BCX_TmpStr(strlen(src));
     if (!strtmp) return NULL;
     return strcpy(strtmp, src);
   }
  repsz = strlen(rep);
  patsz = strlen(pat);
  for (tmpsz=0, p=src;(q=_stristr_(p,pat))!=0; p=q+patsz)
    tmpsz += (size_t) (q - p) + repsz;
    tmpsz += strlen(p);
    strtmp = BCX_TmpStr(tmpsz);
    if (!strtmp) return NULL;
    for (r=strtmp,p=src;(q=_stristr_(p,pat))!=0;p=q+patsz)
     {
       delta = (size_t) (q-p);
       memcpy(r,p,delta); r += delta;
       strcpy(r,rep);      r += repsz;
     }
  strcpy(r,p);
  return strtmp;
}


int containedin(char * Token,char **Contain ,int c)
  {
    int i=0;
    while(Contain[i][0])
      {
        if(0 == ((c == 0 || c == 2) ? strcmp(Contain[i],Token) : strcasecmp(Contain[i],Token)))
          {
            return ((c < 2) ? 0 : i);
          }
        i++;
      }
    return -1;
  }



// ************************************
//       User Subs and Functions
// ************************************


int main (int argc, PCHAR* argv)
{
  G_argc=argc;
  G_argv=argv;
  szTmp=(char*)calloc(256+65535,1);
  Src=(char*)calloc(256+65535,1);
  AbortSrc=(char*)calloc(256+65535,1);
  WarnMsg=(char*)calloc(256+65535+1,1);
  RmLibs=(char*)calloc(256+32767,1);
  static   int  bitz;
  memset(&bitz,0,sizeof(bitz));
  ProtoCnt=0;
  TranslateSlash=TRUE;
  OkayToSend=TRUE;
  Use_SingleFile=TRUE;
  Use_StartupCode=FALSE;
  StartNdx=0;
  Use_ExitCode=FALSE;
  ExitNdx=0;
  *HFile=0;
  *CmdLineFileOut=0;
  *RmLibs=0;
  InMain=TRUE;
  TestState=FALSE;
  *CmdLineConst=0;
  bitz=sizeof(long)*8;
  if(command(-1)[0]==0)
    {
 #if defined (__APPLE__)
      printf("%s\n","MBC4:  Ported to Mac OSX by Armando Rivera (c) 2009-2018");
 #else
      printf("%s\n","MBC4: Based on Linux BCX by Mike Henning (c) 2009");
      printf("%s%s\n","(c) 2009-2018 Armando Rivera with additional code (c) 2009 John Jacques",LF);
 #endif
      printf("%s%s%s","Version ",Version,"  Compiled with ");
// FP3
#if defined __BCPLUSPLUS__// OUTFILE
      printf("%s\n","Borland C++");
#elif defined __BORLANDC__
      printf("%s\n","Borland C");
#elif defined __POCC__
      printf("%s\n","Pelles C");
#elif defined __GNUG__
      printf("%s\n","GNU G++");
#else
      printf("%s\n","Unknown");
#endif  // Main
      if(bitz==64)
        {
          printf("\n");
          printf("%s\n","********************");
          printf("%s\n","** 64 BIT VERSION **");
          printf("%s%s\n","********************",LF);
        }
      printf("%s%s%s\n"," Usage: ",AppExeName()," infile [.bas] [options]");
      printf("%s\n"," [-c] Generate C++ Compatible code");
      printf("%s%s%s\n"," [-d] DEFINE a constant ... ex. ",AppExeName()," MyFile -D:MyConst[=SomeValue]");
      printf("%s\n"," [-e] Write ERRORS to BCX.ERR file");
      printf("%s%s%s\n"," [-f] Output FILENAME... ex. ",AppExeName()," MyFile -f:/MyFiles/MyFile.c");
      printf("%s\n"," [-k] KILL the generated BCX generated 'C' file");
      printf("%s\n"," [-o] OUTPUT a copy of the generated C file to STDOUT");
      printf("%s\n"," [-q] QUIET - No output to screen during translation");
      printf("%s\n"," [-s] Show STATUS of translation by line number");
      printf("%s\n"," [-w] Enable WARNINGS during translation");
      printf("%s%s%s\n"," [-t] TURBO Mode ON w/optional size ... ex. ",AppExeName()," MyFile -t[:1024]");
      printf("%s\n"," [-u] Turn UNICODE Support ON");
      FreeGlobals();
      fflush(stdout);
      exit(0);
    }
  Quiet=FALSE;
    {int i;
  for(i=2; i<=argc-1; i+=1)
    {
      if(instr_b(lcase(argv[i]),"-f"))
        {
          strcpy(CmdLineFileOut,mid(argv[i],4));
        }
      if(instr_b(lcase(argv[i]),"-d"))
        {
          strcpy(CmdLineConst, join(3,CmdLineConst,mid(argv[i],4),chr(1)));
        }
      if(str_cmp(lcase(argv[i]),"-c")==0)
        {
          UseCpp=TRUE;
        }
      if(str_cmp(lcase(argv[i]),"-e")==0)
        {
          ErrFile=TRUE;
        }
      if(str_cmp(lcase(argv[i]),"-q")==0)
        {
          Quiet=TRUE;
        }
      if(str_cmp(lcase(argv[i]),"-k")==0)
        {
          KillCFile=TRUE;
        }
      if(str_cmp(lcase(argv[i]),"-o")==0)
        {
          ReDirect=TRUE;
        }
      if(str_cmp(lcase(argv[i]),"-s")==0)
        {
          ShowStatus=TRUE;
        }
      if(str_cmp(lcase(argv[i]),"-w")==0)
        {
          TestState=TRUE;
        }
      if(instr_b(lcase(argv[i]),"-t"))
        {
          Use_Turbo=TRUE;
          TurboSize=VAL(mid(argv[i],4));
          if(TurboSize!=0)
            {
              if((TurboSize&(TurboSize-1))!=0)
                {
                  TurboSize=512;
                  Warning("Invalid $Turbo size - defaulting to 512");
                }
            }
          else
            {
              TurboSize=512;
            }
        }
    }
    }
  if(ShowStatus)
    {
      cls();
    }
  if(!Quiet)
    {
      cls();
      printf("%s%s\n","MBC Version ",Version);
 #if defined (__APPLE__)
      IsApple=TRUE;
      printf("%s%s\n","MBC4:  Ported to Mac OSX by Armando Rivera (c) 2009-2018",LF);
 #else
      printf("%s\n","MBC4: Based on Linux BCX by Mike Henning (c) 2009");
      printf("%s%s\n","(c) 2009-2018 Armando Rivera with additional code (c) 2009 John Jacques",LF);
 #endif
      if(bitz==64)
        {
          printf("\n");
          printf("%s\n","********************");
          printf("%s\n","** 64 BIT VERSION **");
          printf("%s%s\n","********************",LF);
        }
    }
  if(inchr(command(1),"."))
    {
      strcpy(Cmd,command(1));
    }
  else
    {
      if(Exist(join(2,command(1),".bas")))
        {
          strcpy(Cmd, join(2,command(1),".bas"));
        }
      else if(Exist(join(2,command(1),".BAS")))
        {
          strcpy(Cmd, join(2,command(1),".BAS"));
        }
    }
  if(!Exist(Cmd))
    {
      printf("\n");
      printf("%s%s\n","FILE NOT FOUND: ",command(1));
      FreeGlobals();
      fflush(stdout);
      exit(0);
    }
  strcpy(FileIn,Cmd);
  if(CmdLineFileOut[0]==0)
    {
      strcpy(FileOut, join(2,left(Cmd,InstrRev(Cmd,".",0)-1),".cc"));
    }
  else
    {
      strcpy(FileOut,CmdLineFileOut);
    }
  strcpy(FileErr, join(2,left(Cmd,InstrRev(Cmd,".",0)-1),".ERR"));
  if(Exist(FileErr))
    {
      remove (FileErr);
    }
  strcpy(prcFile,TempFileName(tempdir(),"prc"));
  strcpy(udtFile,TempFileName(tempdir(),"udt"));
  strcpy(datFile,TempFileName(tempdir(),"dat"));
  strcpy(cstFile,TempFileName(tempdir(),"cst"));
  strcpy(ovrFile,TempFileName(tempdir(),"ovr"));
  strcpy(hdrFile,TempFileName(tempdir(),"hdr"));
  strcpy(setFile,TempFileName(tempdir(),"set"));
  strcpy(enuFile,TempFileName(tempdir(),"enu"));
  if((SourceFile=fopen(FileIn,"r"))==0)
   {
     fprintf(stderr,"Can't open file %s\n",FileIn);
     exit(1);
   }
  if((FP2=fopen(FileOut,"w"))==0)
   {
     fprintf(stderr,"Can't open file %s\n",FileOut);
     exit(1);
   }
  Outfile=FP2;
  if((FP3=fopen(prcFile,"w"))==0)
   {
     fprintf(stderr,"Can't open file %s\n",prcFile);
     exit(1);
   }
  if((FP4=fopen(udtFile,"w"))==0)
   {
     fprintf(stderr,"Can't open file %s\n",udtFile);
     exit(1);
   }
  if((FP5=fopen(datFile,"w"))==0)
   {
     fprintf(stderr,"Can't open file %s\n",datFile);
     exit(1);
   }
  if((FP6=fopen(cstFile,"w"))==0)
   {
     fprintf(stderr,"Can't open file %s\n",cstFile);
     exit(1);
   }
  if((FP7=fopen(hdrFile,"w"))==0)
   {
     fprintf(stderr,"Can't open file %s\n",hdrFile);
     exit(1);
   }
  if((FP8=fopen(ovrFile,"w"))==0)
   {
     fprintf(stderr,"Can't open file %s\n",ovrFile);
     exit(1);
   }
  if((FP9=fopen(setFile,"w"))==0)
   {
     fprintf(stderr,"Can't open file %s\n",setFile);
     exit(1);
   }
  if((FP11=fopen(enuFile,"w"))==0)
   {
     fprintf(stderr,"Can't open file %s\n",enuFile);
     exit(1);
   }
  ModuleNdx=1;
  strcpy(Modules[ModuleNdx],FileIn);
  ModuleLineNos[ModuleNdx]=0;
  EmitProlog();
  ClearIfThenStacks();
  EmitCmdLineConst();
  AddGlobal("G_argv",vt_PCHAR,0,"",1,0,0,0);
  AddGlobal("G_argc",vt_INTEGER,0,"",0,0,0,0);

READSRCLINE:;
  while(!EoF(SourceFile)||SplitCnt)
    {
      if(SplitCnt==0)
        {
          Src[0]=0;
          AR_fgets_retval=fgets(Src,65535,SourceFile);
          if(Src[strlen(Src)-1]==10)Src[strlen(Src)-1]=0;
          ModuleLineNos[ModuleNdx]++;
          StripCode(Src);
          if(*Src==0)
            {
              continue;
            }
          if(JoinLines(Src)==1)
            {
              continue;
            }
          if(inchr(Src,"["))
            {
              BracketHandler(Src,0);
            }
          if(SplitLines(Src))
            {
              strcpy(Src,SplitStk[++SplitCur]);
            }
        }
      else
        {
          strcpy(Src,SplitStk[++SplitCur]);
        }
      if(SplitCur==SplitCnt)
        {
          SplitCur=SplitCnt=0;
        }
      if(*Src==0)
        {
          continue;
        }
      strcpy(AbortSrc,Src);
      if(TrcFlag&&InFunc)
        {
          if(!iMatchLft(Src,"$trace"))
            {
              if(!iMatchLft(Src,"end ")&&instr_b(Src,"FUNCTION",0,1)==0)
                {
                  fprintf(Outfile,"%s%s%s%s%s%s\n","// [",trim(Modules[ModuleNdx])," - ",trim(str(ModuleLineNos[ModuleNdx])),"] ",Src);
                  strcpy(Z,trim(Modules[ModuleNdx]));
                  strcpy(Z,replace(Z,"\\","\\\\"));
                  strcpy(Z, join(5," ",Z," - ",str(ModuleLineNos[ModuleNdx])," \\n"));
                  strcpy(Z, join(3,"printf(",enc(Z),");"));
                  fprintf(Outfile,"%s\n",Z);
                }
            }
        }
      if(SrcFlag)
        {
          if(!iMatchLft(Src,"$sourc")&&*Src!=33)
            {
              fprintf(Outfile,"%s%s%s%s%s%s\n","// [",trim(Modules[ModuleNdx])," - ",trim(str(ModuleLineNos[ModuleNdx])),"] ",Src);
            }
        }
      if(ShowStatus)
        {
          locate (2,1,0);
          printf("%s%s%s%d\n","Processing Module: ",trim(Modules[ModuleNdx])," - Line:",(int)ModuleLineNos[ModuleNdx]);
        }
      if(Src[0]==33)
        {
          Src[0]=32;
          fprintf(Outfile,"%s\n",Src);
          *Src=0;
        }
      if(*Src==0)
        {
          continue;
        }
      int     di;
      di=Directives();
      if(di==0)
        {
          goto READNEXTLINE;
        }
      if(di==1)
        {
          goto READSRCLINE;
        }
      if(iMatchLft(Src,"set "))
        {
          ProcessSetCommand(0);
        }
      if(iMatchLft(Src,"sharedset "))
        {
          ProcessSetCommand(1);
        }
      PassOne=TRUE;
      CheckParQuotes();
      if(SpecialCaseHandler(Src))
        {
          continue;
        }
      Parse(Src);
      PassOne=FALSE;
      if(Ndx)
        {
          Emit();
        }

READNEXTLINE:;
    }
  if(CmdLineConst[0]>0)
    {
      strcpy(Src, join(2,"CONST ",CmdLineConst));
      Parse(Src);
      Emit();
      *CmdLineConst=0;
    }
  if(TestForBcxIni==FALSE)
    {
      TestForBcxIni=TRUE;
      strcpy(szFile, join(2,curdir(),"\\bcx.ini"));
      if(!Exist(szFile))
        {
          strcpy(szFile, join(2,AppExePath(),"bcx.ini"));
        }
      if(Exist(szFile))
        {
          PushFileIO();
          if((SourceFile=fopen(szFile,"r"))==0)
           {
             fprintf(stderr,"Can't open file %s\n",szFile);
             exit(1);
           }
          strcpy(Modules[++ModuleNdx],szFile);
          ModuleLineNos[ModuleNdx]=0;
          goto READSRCLINE;
        }
    }
  fflush(Outfile);
  if(FPtrNdx)
    {
      PopFileIO();
      goto READSRCLINE;
    }
  if(Use_GenFree&&GlobalDynaCnt)
    {
      MakeFreeGlobals();
    }
  ExportInternalConst();
  EmitEpilog();
  CloseAll();
  AddProtos();
  DeclareVariables();
  AddFuncs();
  CloseAll();
  if(UseCpp&&str_cmp(CmdLineFileOut,"")==0)
    {
      strcpy(szTmp, join(2,extract(FileOut,"."),".cpp"));
      remove (szTmp);
      rename (FileOut,szTmp);
      strcpy(FileOut,szTmp);
    }
  if(Use_Osx&&str_cmp(CmdLineFileOut,"")==0)
    {
      strcpy(szTmp, join(2,extract(FileOut,"."),".mm"));
      remove (szTmp);
      rename (FileOut,szTmp);
      strcpy(FileOut,szTmp);
    }
  if((FP1=fopen(FileOut,"r"))==0)
   {
     fprintf(stderr,"Can't open file %s\n",FileOut);
     exit(1);
   }
  if((FP2=fopen(hdrFile,"r"))==0)
   {
     fprintf(stderr,"Can't open file %s\n",hdrFile);
     exit(1);
   }
  if((FP3=fopen("$temp$","w"))==0)
   {
     fprintf(stderr,"Can't open file %s\n","$temp$");
     exit(1);
   }
  DoCountLines=TRUE;
  fprintf(FP3,"%s\n","// *********************************************************************");
  fprintf(FP3,"%s%s%s\n","//   Created with MBC (V) ",Version,"Ported to OSX by Armando Rivera");
  fprintf(FP3,"%s\n","//   Ported from BCX32 BASIC To C/C++ Translator (V) 5.12");
  fprintf(FP3,"%s\n","//   BCX (c) 1999 - 2018 by Kevin Diggins");
  fprintf(FP3,"%s\n","//   LinuxBC (c) 2009 by Mike Henning ");
  fprintf(FP3,"%s\n","//   MBC (c) 2009 - 2018 by Armando Rivera");
  fprintf(FP3,"%s\n","// *********************************************************************");
  fprintf(FP3,"%s\n","//   Translated for compiling with the g++ Compiler");
  if(UseCpp)
    {
      fprintf(FP3,"%s\n","//   g++ -Wformat -D_FORTIFY_SOURCE=2 -Wno-write-strings $FILE$.cpp -ldl -o $FILE$");
    }
  else
    {
      fprintf(FP3,"%s\n","//   g++ -Wformat -D_FORTIFY_SOURCE=2 -Wno-write-strings $FILE$.cc -ldl -o $FILE$");
    }
  fprintf(FP3,"%s\n","// *********************************************************************");
  if(NoRT==FALSE)
    {
      if(Use_Osx)
        {
          fprintf(FP3,"%s\n","#import <Cocoa/Cocoa.h>");
        }
      /*****2010-11-24AddedWxCFORWXCONSOLEApps-AIR*****/;
      if(Use_Wx||Use_WxC)
        {
          fprintf(FP3,"%s\n","// WXWIDGETS HEADER FILES //");
          fprintf(FP3,"%s\n","#include <wx/wx.h>");
          fprintf(FP3,"%s\n","#include <wx/process.h>");
          fprintf(FP3,"%s\n","#include <wx/txtstrm.h>");
          fprintf(FP3,"%s\n","#include <wx/msgdlg.h>");
          fprintf(FP3,"%s\n","#include <wx/stdpaths.h>");
          fprintf(FP3,"%s\n","#include <wx/event.h>");
          fprintf(FP3,"%s\n","// ******************* //");
          fprintf(FP3,"%s\n","");
        }
      if(Use_Gtk)
        {
          fprintf(FP3,"%s\n","#include <gtk/gtk.h>");
        }
      if(Use_Glib)
        {
          fprintf(FP3,"%s\n","#include <glib.h>");
        }
      fprintf(FP3,"%s\n","#include <stdbool.h>");
      fprintf(FP3,"%s\n","#include <ctype.h>");
      fprintf(FP3,"%s\n","#include <math.h>");
      fprintf(FP3,"%s\n","#include <stdio.h>");
      fprintf(FP3,"%s\n","#include <iostream>");
      fprintf(FP3,"%s\n","#include <fstream>");
      fprintf(FP3,"%s\n","#include <string.h>");
      fprintf(FP3,"%s\n","#include <stddef.h>");
      fprintf(FP3,"%s\n","#include <stdlib.h>");
      fprintf(FP3,"%s\n","#include <setjmp.h>");
      fprintf(FP3,"%s\n","#include <time.h>");
      fprintf(FP3,"%s\n","#include <stdarg.h>");
      fprintf(FP3,"%s\n","#include <dirent.h>");
      fprintf(FP3,"%s\n","#include <sys/types.h>");
      fprintf(FP3,"%s\n","#include <sys/stat.h>");
      fprintf(FP3,"%s\n","#include <sys/wait.h>");
      fprintf(FP3,"%s\n","#include <unistd.h>");
      fprintf(FP3,"%s\n","#include <dlfcn.h>");
 #if defined (__APPLE__)
      fprintf(FP3,"%s\n","#include <libproc.h>");
 #endif
      if(UseCpp)
        {
          fprintf(FP3,"%s\n","#include <iostream>");
          fprintf(FP3,"%s\n","#include <fstream>");
        }
      if(Use_Instat)
        {
          Use_Keypress=TRUE;
          fprintf(FP3,"%s\n","#include <fcntl.h>");
        }
      if(Use_Keypress)
        {
          fprintf(FP3,"%s\n","#include <term.h>");
        }
      if(Use_Socket)
        {
          fprintf(FP3,"%s\n","#include <sys/socket.h>");
          fprintf(FP3,"%s\n","#include <netinet/in.h>");
          fprintf(FP3,"%s\n","#include <netdb.h>");
          fprintf(FP3,"%s\n","#include <errno.h>");
          fprintf(FP3,"%s\n","#include <arpa/inet.h>");
        }
      if(Use_RegEx)
        {
          fprintf(FP3,"%s\n","#include <regex.h>");
        }
      fprintf(FP3,"%s\n","");
      EmitCompilerDefines();
    }
  while(!EoF(FP2))
    {
      Z[0]=0;
      AR_fgets_retval=fgets(Z,65535,FP2);
      if(Z[strlen(Z)-1]==10)Z[strlen(Z)-1]=0;
      fprintf(FP3,"%s\n",Z);
    }
  char Lastlyne[2048];
  *Lastlyne=0;
  while(!EoF(FP1))
    {
      static int     bMainOut=0;
      Z[0]=0;
      AR_fgets_retval=fgets(Z,65535,FP1);
      if(Z[strlen(Z)-1]==10)Z[strlen(Z)-1]=0;
      if(iMatchLft(Lastlyne,"#if"))
        {
          if(iMatchLft(Z,"#endif"))
            {
              *Lastlyne=0;
              continue;
            }
          else
            {
              fprintf(FP3,"%s\n",Lastlyne);
            }
        }
      strcpy(Lastlyne,Z);
      if(iMatchLft(Lastlyne,"#if"))
        {
          continue;
        }
      fprintf(FP3,"%s\n",Z);
      if(bMainOut)
        {
          continue;
        }
      if(str_cmp(left(ltrim(Z),8),"int main")==0)
        {
          while(str_cmp(trim(Z),"{")!=0)
            {
              Z[0]=0;
              AR_fgets_retval=fgets(Z,65535,FP1);
              if(Z[strlen(Z)-1]==10)Z[strlen(Z)-1]=0;
              fprintf(FP3,"%s\n",Z);
            }
          if(Use_StartupCode)
            {
              fprintf(FP3,"%s%s\n",Scoot,"int BCX_SUCode = BCX_StartupCode_();  // execute user's startup code");
            }
          if(Use_ExitCode)
            {
              fprintf(FP3,"%s%s\n",Scoot,"int BCX_EXCode = BCX_ExitCode_();     // Prepare for user's exit code");
            }
          bMainOut++;
        }
    }
  DoCountLines=FALSE;
  CloseAll();
  remove (hdrFile);
  remove (FileOut);
  rename ("$temp$",FileOut);
  if(ShowStatus)
    {
      locate (2,1,1);
    }
  if(!Quiet)
    {
      LinesRead+=(ModuleLineNos[1]);
      Elapsed=Round((float)clock()/(float)CLOCKS_PER_SEC,2);
      printf("%s%d%s%d%s","[Lines In:",(int)LinesRead,"] [Lines Out:",(int)gLinesWritten,"] ");
      printf("%s%d%s%.7G%s\n","[Statements:",(int)Statements,"] [Time:",(float)Elapsed," sec's]");
      strcpy(Z, join(4,"BCX translated ",RemoveStr(FileIn," ")," to ",RemoveStr(FileOut," ")));
      printf("%s\n",Z);
    }
  PostProcess();
  if(WarnMsg[0]>0)
    {
      printf("%s%s%s\n","Warnings! :",CRLF,WarnMsg);
    }
  if(KillCFile)
    {
      remove (FileOut);
    }
  FreeGlobals();
  return 0;
}


void EmitCmdLineConst (void)
{
  if(CmdLineConst[0]>0)
    {
      static   FILE*   Ftmp;
      fprintf(FP7,"%s\n","");
      fprintf(FP7,"%s\n","// ***************************************************");
      fprintf(FP7,"%s\n","// Commandline Defines");
      fprintf(FP7,"%s\n","// ***************************************************");
      fprintf(FP7,"%s\n","");
      Ftmp=FP6;
      FP6=FP7;
        {int i;
      for(i=1; i<=tally(CmdLineConst,chr(1)); i+=1)
        {
          strcpy(Src,StrToken(CmdLineConst,chr(1),i));
          if(Src[0]==0)
            {
              break;
            }
          strcpy(Src, join(2,"CONST ",Src));
          Parse(Src);
          Emit();
        }
        }
      *CmdLineConst=0;
      FP6=Ftmp;
      fprintf(FP7,"%s\n","");
    }
}


void EmitCompilerDefines (void)
{
  fprintf(FP3,"%s\n","");
  fprintf(FP3,"%s\n","// ***************************************************");
  fprintf(FP3,"%s\n","// Compiler Defines");
  fprintf(FP3,"%s\n","// ***************************************************");
  fprintf(FP3,"%s%s\n","  #define C_EXPORT extern ",enc("C"));
  fprintf(FP3,"%s%s\n","  #define C_IMPORT extern ",enc("C"));
  fprintf(FP3,"%s\n","");
  fprintf(FP3,"%s\n","#ifndef stat");
  fprintf(FP3,"%s\n","  #define lstat stat");
  fprintf(FP3,"%s\n","#endif");
  fprintf(FP3,"%s\n","#ifndef _fcloseall");
  fprintf(FP3,"%s\n","  #define _fcloseall _fcloseall");
  fprintf(FP3,"%s\n","#endif");
  fprintf(FP3,"%s\n","#ifndef HWND");
  fprintf(FP3,"%s\n","  #define HWND GHWND");
  fprintf(FP3,"%s\n","#endif");
  fprintf(FP3,"%s\n","#ifndef MAX_PATH");
  fprintf(FP3,"%s\n","  #define MAX_PATH 2048");
  fprintf(FP3,"%s\n","#endif");
  fprintf(FP3,"%s\n","#ifndef CALLBACK");
  fprintf(FP3,"%s\n","  #define CALLBACK");
  fprintf(FP3,"%s\n","#endif");
  fprintf(FP3,"%s\n","typedef unsigned int HINSTANCE;");
  fprintf(FP3,"%s\n","typedef void* LPVOID;");
  fprintf(FP3,"%s\n","typedef char* PCHAR;");
  fprintf(FP3,"%s\n","typedef unsigned char BYTE;");
  fprintf(FP3,"%s\n","typedef unsigned int  UINT;");
  fprintf(FP3,"%s\n","typedef unsigned char UCHAR;");
  fprintf(FP3,"%s\n","typedef unsigned char* PUCHAR;");
  fprintf(FP3,"%s\n","typedef unsigned long ULONG;");
  fprintf(FP3,"%s\n","typedef unsigned long* ULONG_PTR;");
  fprintf(FP3,"%s\n","typedef unsigned long DWORD;");
  fprintf(FP3,"%s\n","");
  fprintf(FP3,"%s\n","#ifndef TRUE");
  fprintf(FP3,"%s\n","  #define TRUE 1");
  fprintf(FP3,"%s\n","#endif");
  fprintf(FP3,"%s\n","");
  fprintf(FP3,"%s\n","#ifndef FALSE");
  fprintf(FP3,"%s\n","  #define FALSE 0");
  fprintf(FP3,"%s\n","#endif");
  if(!Use_Osx)
    {
      fprintf(FP3,"%s\n","#define BOOL bool");
    }
  fprintf(FP3,"%s\n","");
  if(UseCpp)
    {
      fprintf(FP3,"%s\n","#define println(a)  (std::cout << a << std::endl)");
      fprintf(FP3,"%s\n","  typedef std::string CSTRING;");
      fprintf(FP3,"%s\n","  typedef std::fstream CFILE;");
    }
}


void MakeFreeGlobals (void)
{
  strcpy(Src,"SUB FreeGlobals");
  PassOne=1;
  Parse(Src);
  Emit();
  while(GlobalDynaCnt)
    {
      fprintf(Outfile,"%s%s\n","  ",GlobalDynaStr[GlobalDynaCnt]);
      GlobalDynaCnt--;
    }
  strcpy(Src,"END SUB");
  PassOne=1;
  Parse(Src);
  Emit();
}


void ProcessSetCommand (int GS)
{
  int     i;
  int     ii;
  int     j;
  int     SetString=0;
  char CVar[2048];
  int     vt;
  static  FILE   *SaveFP;
  memset(&SaveFP,0,sizeof(SaveFP));
  SaveFP=Outfile;
  if(!InFunc)
    {
      Outfile=FP9;
    }
  if(inchr(Src,"$")&&tally(Src,"[")>1)
    {
      strcpy(Src,strim(Src));
      strcpy(Src,IRemoveStr(Src,"as string"));
      strcpy(Src,IRemoveStr(Src,"as char"));
      strcat(Src," AS char");
    }
  strcat(Src,"=");
  PassOne=1;
  Parse(Src);
  *Tipe=0;
  for(i=1; i<=Ndx; i+=1)
    {
      if(iMatchWrd(Stk[i],"as"))
        {
          strcpy(Tipe,Stk[i+1]);
          *Stk[i]=0;
          *Stk[i+1]=0;
          break;
        }
    }
  if(Tipe[0]==0)
    {
      strcpy(szTmp,Stk[2]);
      SetString=DataType(Stk[2]);
      j=SetString;
      VarCode.Method=mt_ProcessSetCommand;
      strcpy(VarCode.Token,szTmp);
      VarCode.VarNo=j;
      GetVarCode( &VarCode);
      if(GS)
        {
          fprintf(Outfile,"%s%s",Scoot,RemoveStr(VarCode.StaticOut,"static "));
        }
      else
        {
          fprintf(Outfile,"%s%s",Scoot,VarCode.StaticOut);
        }
       char  lszTmp[65535];
      *lszTmp=0;
      strcpy(CVar,Clean(Stk[2]));
      ValidVar(CVar);
      vt=DataType(Stk[2]);
      for(i=3; i<=Ndx; i+=1)
        {
          strcat(lszTmp,Stk[i]);
        }
      if(vt==vt_STRVAR&&str_cmp(lszTmp,"")!=0)
        {
          strcat(lszTmp,"[65535]");
        }
      if(!InFunc)
        {
          AddGlobal(CVar,vt,0,lszTmp,0,0,0,1);
        }
      else
        {
          AddLocal(CVar,vt,0,lszTmp,0,0,1);
        }
    }
  else
    {
      strcpy(CVar,Clean(Stk[2]));
      if(GS)
        {
          fprintf(Outfile,"%s%s%s%s",Scoot,Tipe," ",CVar);
        }
      else
        {
          fprintf(Outfile,"%s%s%s%s%s",Scoot,"static ",Tipe," ",CVar);
        }
      char DimType[2048];
      int     IsPointer;
      int     id;
      strcpy(DimType,RemoveStr(Tipe,"*"));
      GetTypeInfo(Tipe, &IsPointer, &id, &vt);
      if(vt==vt_STRVAR)
        {
          strcat(DimType,"[65535]");
        }
      if(!InFunc)
        {
          AddGlobal(CVar,vt,id,DimType,IsPointer,0,0,1);
        }
      else
        {
          AddLocal(CVar,vt,id,DimType,IsPointer,0,1);
        }
    }
  i=2;
  j=0;
  for(;;)
    {
      i++;
      if(str_cmp(Stk[i],"=")==0)
        {
          j=1;
        }
      if(SetString==vt_STRVAR&&j==1)
        {
          fprintf(Outfile,"%s","[65535]=");
        }
      else
        {
          fprintf(Outfile,"%s",Stk[i]);
        }
      if(str_cmp(Stk[i],"=")==0)
        {
          break;
        }
      if(i==Ndx)
        {
          break;
        }
    }
  fprintf(Outfile,"%s\n","");
  fprintf(Outfile,"%s\n","{");
  while(!EoF(SourceFile))
    {
      Src[0]=0;
      AR_fgets_retval=fgets(Src,65535,SourceFile);
      if(Src[strlen(Src)-1]==10)Src[strlen(Src)-1]=0;
      ModuleLineNos[ModuleNdx]++;
      StripCode(Src);
      if(JoinLines(Src)==1)
        {
          continue;
        }
      PassOne=TRUE;
      XParse(Src);
      PassOne=FALSE;
      TokenSubstitutions();
      if(iMatchLft(Src,"end "))
        {
          break;
        }
      if(strlen(Src))
        {
          fprintf(Outfile,"%s","  ");
          for(ii=1; ii<=Ndx; ii+=1)
            {
              fprintf(Outfile,"%s",Clean(Stk[ii]));
            }
          fprintf(Outfile,"%s\n","");
        }
    }
  fprintf(Outfile,"%s\n","};\n");
  *Src=0;
  Outfile=SaveFP;
}


int Directives (void)
{
  char lszTmp[2048];
  int     i;
  char COutputFile[2048];
  if(*Src==35||*Src==36)
    {
      strcpy(Z,rtrim(lcase(left(Src,6))));
      for(;;)
      {
        if(str_cmp(Z,"$proje")==0)
          {
            NoRT=TRUE;
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$accel")==0)
          {
            XParse(Src);
            strcpy(Accelerator,RemoveStr(Stk[2],DQ));
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$bcxve")==0)
          {
            strcpy(Src,trim(mid(Src,12)));
            strcpy(Src,RemoveStr(Src,DQ));
            if(str_cmp(lcase(Version),lcase(Src))==-1)
              {
                Abort(join(10,CRLF,"Your Translator needs updating.",CRLF,"This program ",enc(Modules[ModuleNdx])," requires BCX Version: ",Src," or later.",CRLF,CRLF));
              }
            else
              {
                printf("%s\n","");
                printf("%s%s\n","Program written for BCX Version ",Src);
                printf("%s\n","");
              }
            return 0;
          }
        if(str_cmp(Z,"$compi")==0)
          {
            PassOne=1;
            XParse(Src);
            PassOne=0;
            strcpy(Compiler,Stk[2]);
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$execo")==0)
          {
            static char SrcExt[2048];
            memset(&SrcExt,0,sizeof(SrcExt));
            PassOne=1;
            XParse(Src);
            PassOne=0;
            XitCount++;
            if(UseCpp)
              {
                strcpy(SrcExt,".cpp");
              }
            else if(Use_Osx)
              {
                strcpy(SrcExt,".mm");
              }
            else
              {
                strcpy(SrcExt,".cc");
              }
            if(MakeDLL)
              {
                strcpy(Xit[XitCount], join(7,"g++  -Wformat -D_FORTIFY_SOURCE=2 -Wno-write-strings $FILE$",SrcExt," -ldl ",LD_FLAGS,SPC,Stk[2]," -o lib$FILE$.so"));
                *SrcExt=0;
                *Src=0;
                return 0;
              }
            if(Use_IOS)
              {
                static char IOS_COMPILER[2048];
                memset(&IOS_COMPILER,0,sizeof(IOS_COMPILER));
                strcpy(IOS_COMPILER,"/Developer/Platforms/iPhoneOS.platform/Developer/usr/bin/g++");
                if(strlen(Stk[2])>0)
                  {
                    strcpy(Xit[XitCount], join(8,IOS_COMPILER,"  -Wformat -D_FORTIFY_SOURCE=2 -Wno-write-strings $FILE$",SrcExt," -ldl ",LD_FLAGS,SPC,Stk[2]," -o $FILE$"));
                  }
                else
                  {
                    strcpy(Xit[XitCount], join(6,IOS_COMPILER,"  -Wformat -D_FORTIFY_SOURCE=2 -Wno-write-strings $FILE$",SrcExt," -ldl ",LD_FLAGS," -o $FILE$"));
                  }
                *SrcExt=0;
                *Src=0;
                return 0;
              }
            if(strlen(Stk[2])>0)
              {
                strcpy(Xit[XitCount], join(7,"g++  -Wformat -D_FORTIFY_SOURCE=2 -Wno-write-strings $FILE$",SrcExt," -ldl ",LD_FLAGS,SPC,Stk[2]," -o $FILE$"));
              }
            else
              {
                strcpy(Xit[XitCount], join(5,"g++  -Wformat -D_FORTIFY_SOURCE=2 -Wno-write-strings $FILE$",SrcExt," -ldl ",LD_FLAGS," -o $FILE$"));
              }
            *SrcExt=0;
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$exest")==0)
          {
            PassOne=1;
            XParse(Src);
            PassOne=0;
            XitCount++;
            if(IsApple)
              {
                strcpy(Xit[XitCount],"strip $FILE$");
              }
            else
              {
                strcpy(Xit[XitCount],"strip -s -R .comment -R .note -R .note.ABI-tag $FILE$");
              }
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$genfr")==0)
          {
            Use_GenFree=TRUE;
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$osx")==0)
          {
            Use_Osx=TRUE;
            strcpy(LD_FLAGS,join(2,LD_FLAGS," -fobjc-arc -framework Cocoa"));
            return 0;
          }
        if(str_cmp(Z,"$ios")==0)
          {
 #if !defined __APPLE__
            Abort(join(3,CRLF,"The $IOS Directive REQUIRES an Apple OSX Operating System",CRLF));
 #endif
            Use_IOS=TRUE;
            PassOne=1;
            XParse(Src);
            PassOne=0;
            strcpy(LD_FLAGS,join(2,LD_FLAGS," -arch armv6 -arch armv7 -mthumb -isysroot /Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS4.2.sdk -framework Foundation -framework CoreFoundation"));
            return 0;
          }
        if(str_cmp(Z,"$gtk")==0)
          {
            Use_Gtk=TRUE;
            strcpy(LD_FLAGS,join(2,LD_FLAGS," $(pkg-config --libs --cflags gtk+-2.0)"));
            return 0;
          }
        if(str_cmp(Z,"$ldfla")==0)
          {
            strcpy(LD_FLAGS,join(2,LD_FLAGS,remain(Src," ")));
            return 0;
            /*****2010-11-24AddedWxCFORWXCONSOLEApps-AIR*****/;
            break;
          }
        if(str_cmp(Z,"$wxc")==0)
          {
            Use_WxC=UseCpp=NoMain=TRUE;
            strcpy(LD_FLAGS,join(2,LD_FLAGS," $(wx-config --libs --cppflags)"));
            return 0;
          }
        if(str_cmp(Z,"$wx")==0)
          {
            Use_Wx=UseCpp=NoMain=TRUE;
            strcpy(LD_FLAGS,join(2,LD_FLAGS," $(wx-config --libs --cppflags)"));
            return 0;
          }
        if(str_cmp(Z,"$glib")==0)
          {
            Use_Glib=TRUE;
            strcpy(LD_FLAGS,join(2,LD_FLAGS," $(pkg-config --libs --cflags glib-2.0)"));
            return 0;
          }
        if(str_cmp(Z,"$noini")==0)
          {
            *Src=0;
            TestForBcxIni=TRUE;
            return 0;
          }
        if(str_cmp(Z,"$linke")==0)
          {
            PassOne=1;
            XParse(Src);
            PassOne=0;
            strcpy(Linker,Stk[2]);
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$onexi")==0)
          {
            PassOne=1;
            XParse(Src);
            PassOne=0;
            XitCount++;
            strcpy(Xit[XitCount],Stk[2]);
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$onent")==0)
          {
            PassOne=1;
            XParse(Src);
            PassOne=0;
            EntryCnt++;
            strcpy(Entry[EntryCnt],Stk[2]);
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$pack")==0 ||  str_cmp(Z,"$pack(")==0)
          {
            strcpy(Src,mid(Src,6));
            fprintf(FP4,"%s%s\n","#pragma pack ",ltrim(Src));
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$nodll")==0)
          {
            NoDllMain=TRUE;
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$pelle")==0)
          {
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$stdca")==0)
          {
            UseStdCall=TRUE;
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$iprin")==0)
          {
            if(instr_b(lcase(Src),"_on"))
              {
                TranslateSlash=TRUE;
              }
            else
              {
                TranslateSlash=FALSE;
              }
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$nomai")==0)
          {
            NoMain=TRUE;
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$test")==0)
          {
            TestState=!TestState;
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$typed")==0)
          {
            fprintf(FP7,"%s%s%s\n","typedef ",remain(Src," "),";");
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$resou")==0)
          {
            static char resAlias[2048];
            memset(&resAlias,0,sizeof(resAlias));
            static char resFile[2048];
            memset(&resFile,0,sizeof(resFile));
            Use_Embed=TRUE;
            PassOne=1;
            XParse(Src);
            PassOne=0;
            EntryCnt++;
            strcpy(Entry[EntryCnt], join(5,"ld -r -b binary ",Stk[2]," -o ",Stk[2],".o"));
            strcpy(Stk[2],replace(Stk[2],".","_"));
            strcpy(resFile,RemoveStr(Stk[2],DQ));
            strcpy(resAlias,RemoveStr(Stk[3],DQ));
            AddGlobal(join(3,"_binary_",resFile,"_start"),vt_INTEGER,0,"",0,0,1,0);
            AddGlobal(join(3,"_binary_",resFile,"_size"),vt_INTEGER,0,"",0,0,1,0);
            strcpy(Src, join(5,"CONST ",resAlias,"= &_binary_",resFile,"_start"));
            Parse(Src);
            Emit();
            strcpy(Src, join(5,"CONST ",resAlias,"_SIZE = (int)&_binary_",resFile,"_size"));
            Parse(Src);
            Emit();
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$turbo")==0)
          {
            strcpy(Src,ltrim(mid(Src,7)));
            if(*Src!=0)
              {
                TurboSize=VAL(Src);
                if((TurboSize&(TurboSize-1))!=0)
                  {
                    TurboSize=512;
                    Warning("Invalid $Turbo size - defaulting to 512");
                  }
              }
            else
              {
                TurboSize=512;
              }
            Use_Turbo=TRUE;
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$sourc")==0)
          {
            SrcFlag=!SrcFlag;
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$fssta")==0)
          {
            Use_Static=!Use_Static;
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$trace")==0)
          {
            TrcFlag=!TrcFlag;
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$inclu")==0 ||  str_cmp(Z,"$modul")==0)
          {
            char orgfileName[2048];
            strcpy(szFile,trim(RemoveStr(mid(Src,9),DQ)));
            strcpy(orgfileName,szFile);
            if(str_cmp(left(szFile,1),"<")==0)
              {
                strcpy(szFile,mid(szFile,2,strlen(szFile)-2));
                strcpy(szFile, join(2,Environ("BCXLIB"),szFile));
              }
            if(!Exist(szFile))
              {
                strcpy(szFile,BcxSplitPath(szFile,FNAME|FEXT));
                strcpy(szFile, join(2,BcxSplitPath(FileIn,FDRV|FPATH),szFile));
              }
            if(!Exist(szFile))
              {
                Abort(join(2,"Unable to locate ",orgfileName));
              }
            PushFileIO();
            if((SourceFile=fopen(szFile,"r"))==0)
             {
               fprintf(stderr,"Can't open file %s\n",szFile);
               exit(1);
             }
            strcpy(Modules[++ModuleNdx],szFile);
            ModuleLineNos[ModuleNdx]=0;
            return 1;
          }
        if(str_cmp(Z,"$try")==0)
          {
            fprintf(Outfile,"%s\n","try {");
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$throw")==0)
          {
            strcpy(szTmp,mid(Src,8));
            if(szTmp[0]==0)
              {
                strcpy(szTmp,enc("An Exception has occured!"));
              }
            fprintf(Outfile,"%s%s%s%s\n",Scoot,"throw ",szTmp,";");
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$catch")==0)
          {
            strcpy(szTmp,mid(Src,8));
            if(szTmp[0]==0)
              {
                strcpy(szTmp,"char *str");
              }
            fprintf(Outfile,"%s\n","}");
            fprintf(Outfile,"%s%s%s\n","catch (",szTmp,")");
            fprintf(Outfile,"%s\n","{");
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$endtr")==0)
          {
            fprintf(Outfile,"%s\n","}");
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$endna")==0)
          {
            InNameSpace--;
            BumpDown();
            fprintf(Outfile,"%s%s\n",Scoot,"}");
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$names")==0)
          {
            Abort("$NAMESPACE/$ENDNAMESPACE have been removed from this version.  Use NAMESPACE / END NAMESPACE instead.");
            break;
          }
        if(str_cmp(Z,"$usena")==0)
          {
            UseCpp=TRUE;
            strcpy(szTmp,mid(Src,inchr(Src," ")+1));
            if(str_cmp(right(trim(szTmp),1),";")!=0)
              {
                fprintf(Outfile,"%s%s%s\n","using namespace ",szTmp,";");
              }
            else
              {
                fprintf(Outfile,"%s%s\n","using namespace ",szTmp);
              }
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$class")==0)
          {
            Abort("$CLASS has been removed from this version.  Use CLASS instead.");
            return 0;
          }
        if(str_cmp(Z,"$inter")==0)
          {
            static int     BeenHere;
            UseCpp=TRUE;
            strcpy(szTmp,remain(Src,SPC));
            if(!BeenHere)
              {
                BeenHere++;
                fprintf(FP4,"%s\n","#ifndef __cplusplus");
                fprintf(FP4,"%s\n","  #error A C++ compiler is required");
                fprintf(FP4,"%s\n","#endif");
              }
            fprintf(FP4,"%s%s%s\n","interface ",szTmp," {");
            for(;;)
              {
                if(EoF(SourceFile))
                  {
                    Abort("$Interface Without $EndInterface");
                  }
                Src[0]=0;
                AR_fgets_retval=fgets(Src,65535,SourceFile);
                if(Src[strlen(Src)-1]==10)Src[strlen(Src)-1]=0;
                ModuleLineNos[ModuleNdx]++;
                if(iMatchLft(ltrim(Src),"$endinterface"))
                  {
                    break;
                  }
                fprintf(FP4,"%s\n",Src);
              }
            fprintf(FP4,"%s%s%s\n","}",trim(join(2,Src,13)),";");
            return 0;
          }
        if(str_cmp(Z,"$comme")==0)
          {
            *Src=0;
            for(;;)
              {
                if(EoF(SourceFile))
                  {
                    Abort("Unbalanced $Comment");
                  }
                Src[0]=0;
                AR_fgets_retval=fgets(Src,65535,SourceFile);
                if(Src[strlen(Src)-1]==10)Src[strlen(Src)-1]=0;
                ModuleLineNos[ModuleNdx]++;
                StripTabs();
                if(iMatchLft(ltrim(Src),"$comment"))
                  {
                    break;
                  }
                fprintf(Outfile,"%s%s\n","// ",Src);
              }
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$ccode")==0)
          {
            *Src=0;
            for(;;)
              {
                if(EoF(SourceFile))
                  {
                    Abort("Unbalanced $Ccode");
                  }
                Src[0]=0;
                AR_fgets_retval=fgets(Src,65535,SourceFile);
                if(Src[strlen(Src)-1]==10)Src[strlen(Src)-1]=0;
                ModuleLineNos[ModuleNdx]++;
                StripTabs();
                if(iMatchLft(ltrim(Src),"$ccode"))
                  {
                    if(SrcFlag)
                      {
                        fprintf(Outfile,"%s%s%s%s%s\n","// [",trim(Modules[ModuleNdx])," - ",trim(str(ModuleLineNos[ModuleNdx])),"] End of $CCODE Block");
                      }
                    break;
                  }
                fprintf(Outfile,"%s\n",rtrim(Src));
              }
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$cprot")==0)
          {
            FastLexer(Src,SPC,"!");
            if(iMatchWrd(Stk[2],"!"))
              {
                ProtoCnt++;
                strcpy(ProtoType[ProtoCnt].Prototype,remain(Src,"!"));
                *ProtoType[ProtoCnt].Condition=0;
                ProtoType[ProtoCnt].CondLevel=0;
              }
            else
              {
                i=iMatchNQ(Src,"function");
                if(i==0)
                  {
                    i=iMatchNQ(Src,"sub");
                  }
                if(i)
                  {
                    strcpy(Src, join(2,"c_declare ",mid(Src,i)));
                  }
                else
                  {
                    i=iMatchNQ(Src,"$cproto");
                    strcpy(Src, join(2,"c_declare function ",mid(Src,i+7)));
                  }
                UseCProto=TRUE;
                return 2;
              }
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$heade")==0)
          {
            *Src=0;
            fprintf(FP7,"%s\n","// ***************************************************");
            fprintf(FP7,"%s\n","");
            for(;;)
              {
                if(EoF(SourceFile))
                  {
                    Abort("Unbalanced $Header");
                  }
                Src[0]=0;
                AR_fgets_retval=fgets(Src,65535,SourceFile);
                if(Src[strlen(Src)-1]==10)Src[strlen(Src)-1]=0;
                ModuleLineNos[ModuleNdx]++;
                StripTabs();
                strcpy(Src,trim(Src));
                if(iMatchLft(Src,"$heade"))
                  {
                    break;
                  }
                fprintf(FP7,"%s\n",Src);
              }
            *Src=0;
            fprintf(FP7,"%s\n","");
            return 0;
          }
        if(str_cmp(Z,"$asm")==0)
          {
            if(!iMatchLft(Src,"$asm"))
              {
                Abort(join(2,"Unknown metastatement: ",Src));
              }
            *Src=0;
            for(;;)
              {
                if(EoF(SourceFile))
                  {
                    Abort("Unbalanced $Asm");
                  }
                Src[0]=0;
                AR_fgets_retval=fgets(Src,65535,SourceFile);
                if(Src[strlen(Src)-1]==10)Src[strlen(Src)-1]=0;
                ModuleLineNos[ModuleNdx]++;
                if(SrcFlag)
                  {
                    fprintf(Outfile,"%s%s\n","// ",Src);
                  }
                StripTabs();
                strcpy(Src,trim(Src));
                static int     meta_asm_loop;
                memset(&meta_asm_loop,0,sizeof(meta_asm_loop));
                static   bool  meta_asm_comment_present;
                memset(&meta_asm_comment_present,0,sizeof(meta_asm_comment_present));
                static int     Src_Len;
                memset(&Src_Len,0,sizeof(Src_Len));
                Src_Len=strlen(Src);
                meta_asm_comment_present=FALSE;
                for(meta_asm_loop=0; meta_asm_loop<=Src_Len; meta_asm_loop+=1)
                  {
                    if(Src[meta_asm_loop]==39||Src[meta_asm_loop]==59)
                      {
                        strcpy(lszTmp,right(Src,Src_Len-meta_asm_loop-1));
                        Src[meta_asm_loop]=0;
                        meta_asm_comment_present=TRUE;
                        break;
                      }
                  }
                strcpy(Src,trim(Src));
                if(iMatchLft(Src,"$asm"))
                  {
                    break;
                  }
                strcpy(Src,replace(Src,"$","0x"));
                strcpy(Src,iReplace(Src,"&h","0x"));
                if(Src[0]!=0)
                  {
                    strcpy(Src, join(3,"_asm(",enc(Src),chr(1)));
                    if(meta_asm_comment_present)
                      {
                        strcpy(Src, join(4,Src,TAB,"//",lszTmp));
                      }
                    strcpy(SrcTmp,Src);
                    fprintf(Outfile,"%s\n","#if !defined( __POCC__ ) && !defined (__cplusplus )");
                    strcpy(Src,replace(Src,chr(1),")"));
                    fprintf(Outfile,"%s\n",Src);
                    fprintf(Outfile,"%s\n","#else");
                    strcpy(SrcTmp,replace(SrcTmp,"_asm(","__asm{"));
                    strcpy(SrcTmp,replace(SrcTmp,chr(1),"}"));
                    fprintf(Outfile,"%s\n",RemoveStr(SrcTmp,DQ));
                    fprintf(Outfile,"%s\n","#endif");
                  }
              }
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"#inclu")==0)
          {
            strcpy(Src,RemoveStr(lcase(Src),"#include"));
            strcpy(Src,trim(Src));
            fprintf(FP7,"%s%s\n","#include ",Src);
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$libra")==0)
          {
            strcpy(Src,replace(Src,"\\","\\\\"));
            strcpy(Src,RemoveStr(lcase(Src),"$library"));
            strcpy(Src,trim(Src));
            AddLibrary(Src);
            *Src=0;
            return 0;
          }
        if(str_cmp(Z,"$nolib")==0)
          {
            strcpy(Src,replace(Src,"\\","\\\\"));
            strcpy(Src,RemoveStr(lcase(Src),"$nolibrary"));
            RemoveLibrary(Src);
            *Src=0;
            return 0;
          }
        break;
      }
    }
  return 2;
}


int SubVarType (int TokenNum)
{
  int     k;
  int     j=0;
  k=CheckLocal(Stk[TokenNum], &j);
  if(k==vt_CHAR)
    {
      if(*LocalVars[j].VarDim!=91&&LocalVars[j].VarPntr==0)
        {
          k=vt_INTEGER;
        }
    }
  else if(k==vt_UNKNOWN)
    {
      k=CheckGlobal(Stk[TokenNum], &j);
      if(k==vt_CHAR)
        {
          if(*GlobalVars[j].VarDim!=91&&GlobalVars[j].VarPntr==0)
            {
              k=vt_INTEGER;
            }
        }
    }
  j=(UCHAR)*(right(Stk[TokenNum],1));
  for(;;)
  {
    if(k==vt_STRVAR||k==vt_CHAR)
      {
        if(j!=36)
          {
            strcat(Stk[TokenNum],"$");
          }
        break;
      }
    if(k==vt_INTEGER)
      {
        if(j!=37)
          {
            strcat(Stk[TokenNum],"%");
          }
        break;
      }
    if(k==vt_SINGLE)
      {
        if(j!=33)
          {
            strcat(Stk[TokenNum],"!");
          }
        break;
      }
    if(k==vt_DOUBLE)
      {
        if(j!=35)
          {
            strcat(Stk[TokenNum],"#");
          }
        break;
      }
    if(k==vt_LDOUBLE)
      {
        if(j!=166)
          {
            strcat(Stk[TokenNum],"¦");
          }
      }
    break;
  }
  return k;
}


char * PrintWriteFormat (int DoWrite)
{
  char *BCX_RetStr={0};
   ARGTYPE  Stak[128];
  char Frmat[2048];
  char Arg[2048];
  char *ZZ;
  ZZ=(char*)calloc(256+65535,1);
  char Cast[2048];
  int     NewLineFlag=0;
  int     Argcount=0;
  int     i=0;
  int     j=0;
  int     k=0;
  *Frmat=0;
  *Arg=0;
  *ZZ=0;
  if(str_cmp(Stk[Ndx],";")==0)
    {
      NewLineFlag=TRUE;
      Ndx--;
    }
  if(Ndx==1)
    {
      goto PRINTWRITELABEL;
    }
  Stak[1].ArgType=-1;
  j=2;
  while(j<=Ndx)
    {
      if(str_cmp(Clean(Stk[j]),"BCX_DynaCall")!=0)
        {
          i=SubVarType(j);
          if(Stak[Argcount+1].ArgType==-1)
            {
              if(i==vt_CHAR||i==vt_STRVAR||i==vt_INTEGER||i==vt_SINGLE||i==vt_DOUBLE||i==vt_LDOUBLE)
                {
                  Stak[Argcount+1].ArgType=i;
                }
            }
          if(str_cmp(Stk[j],"(")==0)
            {
              i=0;
              for(;;)
                {
                  if(str_cmp(Stk[j],"(")==0)
                    {
                      i++;
                    }
                  if(str_cmp(Stk[j],")")==0)
                    {
                      i--;
                    }
                  strcat(Arg,Stk[j]);
                  j++;
                  if(i<=0||j>=Ndx)
                    {
                      break;
                    }
                }
            }
          if(str_cmp(Stk[j],"[")==0)
            {
              i=0;
              for(;;)
                {
                  if(str_cmp(Stk[j],"[")==0)
                    {
                      i++;
                    }
                  if(str_cmp(Stk[j],"]")==0)
                    {
                      i--;
                    }
                  strcat(Arg,Stk[j]);
                  j++;
                  if(str_cmp(Stk[j],"[")==0 && i==0)
                    {
                      continue;
                    }
                  if(i<=0||j>=Ndx)
                    {
                      break;
                    }
                }
            }
          if(str_cmp(Stk[j],";")==0 ||  str_cmp(Stk[j],",")==0 ||  str_cmp(Stk[j],"&")==0)
            {
              Argcount++;
              strcpy(Stak[Argcount].Arg,Arg);
              Stak[Argcount+1].ArgType=-1;
              *Arg=0;
              j++;
            }
          else
            {
              strcat(Arg,Stk[j]);
              j++;
            }
        }
      else
        {
          strcat(Arg,Stk[j]);
          j++;
        }
    }
  Argcount++;
  strcpy(Stak[Argcount].Arg,Arg);
  *Arg=0;
  for(i=1; i<=Argcount; i+=1)
    {
      j=Stak[i].ArgType;
      if(j==-1)
        {
          strcpy(ZZ,extract(Stak[i].Arg,"("));
          j=DataType(ZZ);
        }
      for(;;)
      {
        if(j==vt_STRLIT||j==vt_STRVAR||j==vt_CHAR)
          {
            if(DoWrite)
              {
                strcpy(Frmat, join(7,Frmat,"\\",DQ,"%s","\\",DQ,","));
              }
            else
              {
                strcat(Frmat,"%s");
              }
            if(str_cmp(left(ZZ,12),"BCX_DynaCall")==0)
              {
                strcpy(Arg, join(3,Arg,",(char*)",Stak[i].Arg));
              }
            else
              {
                strcpy(Arg, join(3,Arg,",",Stak[i].Arg));
              }
            break;
          }
        if(j==vt_INTEGER||j==vt_DECFUNC)
          {
            if(DoWrite)
              {
                strcpy(Frmat, join(3,Frmat,"%d",","));
              }
            else
              {
                strcat(Frmat,"%d");
              }
            strcpy(Arg, join(3,Arg,",(int)",Stak[i].Arg));
            break;
          }
        if(j==vt_SINGLE)
          {
            if(DoWrite)
              {
                strcpy(Frmat, join(3,Frmat,"%.7G",","));
              }
            else
              {
                strcat(Frmat,"%.7G");
              }
            strcpy(Arg, join(3,Arg,",(float)",Stak[i].Arg));
            break;
          }
        if(j==vt_DOUBLE||j==vt_NUMBER)
          {
            if(DoWrite)
              {
                strcpy(Frmat, join(3,Frmat,"%.15G",","));
              }
            else
              {
                strcat(Frmat,"%.15G");
              }
            strcpy(Arg, join(3,Arg,",(double)",Stak[i].Arg));
            break;
          }
        if(j==vt_LDOUBLE)
          {
            if(DoWrite)
              {
                strcpy(Frmat, join(3,Frmat,"%.19LG",","));
              }
            else
              {
                strcat(Frmat,"%.19LG");
              }
            strcpy(Arg, join(3,Arg,",(LDOUBLE)",Stak[i].Arg));
            break;
          }
          // case else
          {
            if((UCHAR)*(Stak[i].Arg)==40)
              {
                *ZZ=0;
                strcat(Arg,",");
                for(;;)
                  {
                    k=instr_b(Stak[i].Arg,")");
                    strcpy(Cast,mid(Stak[i].Arg,1,k));
                    strcpy(Stak[i].Arg,trim(mid(Stak[i].Arg,k+1)));
                    strcpy(Cast,iReplace(Cast,"char*","char *"));
                    strcpy(Cast,iReplace(Cast,"integer","int"));
                    strcpy(Cast,iReplace(Cast,"single","float"));
                    strcpy(Cast,iReplace(Cast,"ldouble","LDOUBLE"));
                    if(ZZ[0]==0)
                      {
                        if(str_cmp(Cast,"(char *)")==0 ||  str_cmp(Cast,"(int)")==0 ||  str_cmp(Cast,"(float)")==0 ||  str_cmp(Cast,"(double)")==0 ||  str_cmp(Cast,"(LDOUBLE)")==0)
                          {
                            strcpy(ZZ,Cast);
                          }
                        else
                          {
                            strcpy(ZZ,"(double)");
                            strcpy(Cast, join(2,ZZ,Cast));
                          }
                        RemoveAll(ZZ,"()");
                        strcpy(ZZ,iReplace(ZZ,"char *","%s"));
                        strcpy(ZZ,iReplace(ZZ,"int","%d"));
                        strcpy(ZZ,iReplace(ZZ,"float","%.7G"));
                        strcpy(ZZ,iReplace(ZZ,"ldouble","%.19LG"));
                        strcpy(ZZ,iReplace(ZZ,"double","%.15G"));
                      }
                    strcat(Arg,Cast);
                    if(!((UCHAR)*(Stak[i].Arg)==40))
                      {
                        break;
                      }
                  }
                strcat(Arg,Stak[i].Arg);
                strcat(Frmat,ZZ);
                if(DoWrite)
                  {
                    strcat(Frmat,",");
                  }
              }
            else
              {
                if(DoWrite)
                  {
                    strcpy(Frmat, join(3,Frmat,"%G",","));
                  }
                else
                  {
                    strcat(Frmat,"%G");
                    strcpy(Arg, join(3,Arg,",(float)",Stak[i].Arg));
                  }
              }
          }
        break;
      }
    }
  if(DoWrite)
    {
      strcpy(Frmat,left(Frmat,strlen(Frmat)-1));
    }

PRINTWRITELABEL:;
  if(NewLineFlag==0)
    {
      strcat(Frmat,"\\n");
    }
  BCX_RetStr=join(4,"printf(",enc(Frmat),Clean(Arg),");");
  if(ZZ)free(ZZ);
  return BCX_RetStr;
}


void EmitInputCode (void)
{
  int     Argcount=0;
  int     VarCnt=0;
  int     i=0;
  int     j=0;
  int     l=0;
  char Arg[2048];
  char Tmp[2048];
  char Frmat[2048];
  static char Stak[128][2048];
  memset(&Stak,0,sizeof(Stak));
  char Y[2048];
  char *ZZ;
  ZZ=(char*)calloc(256+65535,1);
  Use_Inputbuffer=TRUE;
  Use_Scan=TRUE;
  Use_Split=TRUE;
  Use_Remove=TRUE;
  Use_StrStr=TRUE;
  Use_Mid=TRUE;
  Use_Left=TRUE;
  Use_Instr=TRUE;
  Use_Stristr=TRUE;
  UseLCaseTbl=TRUE;
  UseFlag=TRUE;
  Use_Lineinput=TRUE;
  *Arg=0;
  *ZZ=0;
  *Frmat=0;
  strcpy(Tmp, join(7,DQ,",",DQ,",",DQ," ",DQ));
  if(DataType(Stk[2])==vt_STRLIT)
    {
      fprintf(Outfile,"%s%s%s%s\n",Scoot,"printf(",Clean(Stk[2]),");");
    }
  if(DataType(Stk[2])==vt_STRLIT)
    {
      j=4;
    }
  else
    {
      j=2;
    }
  l=j;
  while(j<=Ndx)
    {
      if(j==l)
        {
          i=SubVarType(j);
        }
      if(str_cmp(Stk[j],",")==0)
        {
          l=j+1;
        }
      strcat(ZZ,Stk[j]);
      j++;
    }
  FastLexer(ZZ,"",",");
  j=1;
  while(j<=Ndx)
    {
      if(str_cmp(Stk[j],",")==0)
        {
          Argcount++;
          strcpy(Stak[Argcount],Arg);
          *Arg=0;
          j++;
        }
      else
        {
          strcat(Arg,Stk[j]);
          j++;
          if(j<Ndx)
            {
              if(str_cmp(Stk[j],"[")==0)
                {
                  i=0;
                  for(;;)
                    {

DOAGAIN:;
                      if(str_cmp(Stk[j],"[")==0)
                        {
                          i++;
                        }
                      if(str_cmp(Stk[j],"]")==0)
                        {
                          i--;
                        }
                      strcat(Arg,Stk[j]);
                      j++;
                      if(str_cmp(Stk[j],"[")==0 && i==0)
                        {
                          goto DOAGAIN;
                        }
                      if(i<=0||j>=Ndx)
                        {
                          break;
                        }
                    }
                }
            }
        }
    }
  Argcount++;
  strcpy(Stak[Argcount],Arg);
  *Arg=0;
  for(i=1; i<=Argcount; i+=1)
    {
      strcpy(Y,Stak[i]);
      j=DataType(Y);
      for(;;)
      {
        if(j==vt_STRVAR)
          {
            strcat(Frmat,"%s");
            strcpy(Arg, join(3,Arg,",",Clean(Stak[i])));
            fprintf(Outfile,"%s%s%s%s\n",Scoot,"*",trim(Clean(Stak[i])),"=0;");
            VarCnt++;
            break;
          }
        if(j==vt_INTEGER)
          {
            strcat(Frmat,"%d");
            strcpy(Arg, join(3,Arg,",&",Clean(Stak[i])));
            fprintf(Outfile,"%s%s%s\n",Scoot,Clean(Stak[i]),"=0;");
            VarCnt++;
            break;
          }
        if(j==vt_SINGLE)
          {
            strcat(Frmat,"%g");
            strcpy(Arg, join(3,Arg,",&",Clean(Stak[i])));
            fprintf(Outfile,"%s%s%s\n",Scoot,Clean(Stak[i]),"=0;");
            VarCnt++;
            break;
          }
        if(j==vt_DOUBLE)
          {
            strcat(Frmat,"%lG");
            strcpy(Arg, join(3,Arg,",&",Clean(Stak[i])));
            fprintf(Outfile,"%s%s%s\n",Scoot,Clean(Stak[i]),"=0;");
            VarCnt++;
            break;
          }
        if(j==vt_LDOUBLE)
          {
            strcat(Frmat,"%lG");
            strcpy(Arg, join(3,Arg,",&",Clean(Stak[i])));
            fprintf(Outfile,"%s%s%s\n",Scoot,Clean(Stak[i]),"=0;");
            VarCnt++;
            break;
          }
          // case else
          {
            strcat(Frmat,"%d");
            strcpy(Arg, join(3,Arg,",&",Clean(Stak[i])));
            fprintf(Outfile,"%s%s%s\n",Scoot,Clean(Stak[i]),"=0;");
            VarCnt++;
          }
        break;
      }
    }
  fprintf(Outfile,"%s%s\n",Scoot,"AR_fgets_retval=fgets(InputBuffer,sizeof(InputBuffer),stdin);");
  fprintf(Outfile,"%s%s\n",Scoot,"InputBuffer[strlen(InputBuffer)-1]=0;");
  fprintf(Outfile,"%s%s%s%s%s\n",Scoot,"ScanError = scan(InputBuffer,",enc(Frmat),Arg,");\n");
  fprintf(Outfile,"%s%s\n",Scoot,"*InputBuffer=0;");
  if(ZZ)free(ZZ);
}


void EmitFileInputCode (void)
{
  int     Argcount=0;
  int     VarCnt=0;
  int     i;
  int     j;
  char Arg[2048];
  char Frmat[2048];
  char FHandle[2048];
  char Y[2048];
  char *ZZ;
  ZZ=(char*)calloc(256+65535,1);
  static char Stak[128][2048];
  memset(&Stak,0,sizeof(Stak));
  *Arg=0;
  *Frmat=0;
  *ZZ=0;
  *FHandle=0;
  Use_Inputbuffer=TRUE;
  Use_Scan=TRUE;
  Use_Split=TRUE;
  Use_Remove=TRUE;
  Use_StrStr=TRUE;
  Use_Mid=TRUE;
  Use_Left=TRUE;
  Use_Instr=TRUE;
  Use_Stristr=TRUE;
  UseLCaseTbl=TRUE;
  i=4;
  for(j=2; j<=Ndx; j+=1)
    {
      if(*Stk[j]==44)
        {
          i=j+1;
          break;
        }
      strcat(FHandle,Stk[j]);
    }
  for(j=i; j<=Ndx; j+=1)
    {
      if(j==i)
        {
          SubVarType(j);
        }
      if(str_cmp(Stk[j],",")==0)
        {
          SubVarType(j+1);
        }
      strcat(ZZ,Stk[j]);
    }
  FastLexer(ZZ,"",",");
  j=1;
  while(j<=Ndx)
    {
      if(str_cmp(Stk[j],",")==0)
        {
          Argcount++;
          strcpy(Stak[Argcount],Arg);
          *Arg=0;
          j++;
        }
      else
        {
          strcat(Arg,Stk[j]);
          j++;
          if(j<Ndx)
            {
              if(str_cmp(Stk[j],"[")==0)
                {
                  i=0;
                  for(;;)
                    {

DOAGAIN:;
                      if(str_cmp(Stk[j],"[")==0)
                        {
                          i++;
                        }
                      if(str_cmp(Stk[j],"]")==0)
                        {
                          i--;
                        }
                      strcat(Arg,Stk[j]);
                      j++;
                      if(str_cmp(Stk[j],"[")==0 && i==0)
                        {
                          goto DOAGAIN;
                        }
                      if(i<=0||j>=Ndx)
                        {
                          break;
                        }
                    }
                }
            }
        }
    }
  Argcount++;
  strcpy(Stak[Argcount],Arg);
  *Arg=0;
  for(i=1; i<=Argcount; i+=1)
    {
      strcpy(Y,Stak[i]);
      j=DataType(Y);
      for(;;)
      {
        if(j==vt_STRVAR)
          {
            strcat(Frmat,"%s");
            strcpy(Arg, join(3,Arg,",",Clean(Stak[i])));
            fprintf(Outfile,"%s%s%s%s\n",Scoot,"*",trim(Clean(Stak[i])),"=0;");
            VarCnt++;
            break;
          }
        if(j==vt_INTEGER)
          {
            strcat(Frmat,"%d");
            strcpy(Arg, join(3,Arg,",&",Clean(Stak[i])));
            fprintf(Outfile,"%s%s%s\n",Scoot,Clean(Stak[i]),"=0;");
            VarCnt++;
            break;
          }
        if(j==vt_SINGLE)
          {
            strcat(Frmat,"%g");
            strcpy(Arg, join(3,Arg,",&",Clean(Stak[i])));
            fprintf(Outfile,"%s%s%s\n",Scoot,Clean(Stak[i]),"=0;");
            VarCnt++;
            break;
          }
        if(j==vt_DOUBLE)
          {
            strcat(Frmat,"%lG");
            strcpy(Arg, join(3,Arg,",&",Clean(Stak[i])));
            fprintf(Outfile,"%s%s%s\n",Scoot,Clean(Stak[i]),"=0;");
            VarCnt++;
            break;
          }
        if(j==vt_LDOUBLE)
          {
            strcat(Frmat,"%lG");
            strcpy(Arg, join(3,Arg,",&",Clean(Stak[i])));
            fprintf(Outfile,"%s%s%s\n",Scoot,Clean(Stak[i]),"=0;");
            VarCnt++;
            break;
          }
          // case else
          {
            strcat(Frmat,"%d");
            strcpy(Arg, join(3,Arg,",&",Clean(Stak[i])));
            fprintf(Outfile,"%s%s%s\n",Scoot,Clean(Stak[i]),"=0;");
            VarCnt++;
          }
        break;
      }
    }
  fprintf(Outfile,"%s%s%s%s\n",Scoot,"AR_fgets_retval=fgets(InputBuffer,65535,",FHandle,");");
  fprintf(Outfile,"%s%s\n",Scoot,"if(InputBuffer[strlen(InputBuffer)-1]== 10)");
  fprintf(Outfile,"%s%s\n",Scoot,"   InputBuffer[strlen(InputBuffer)-1]=0;");
  fprintf(Outfile,"%s%s%s%s%s\n",Scoot,"ScanError = scan(InputBuffer,",enc(Frmat),Arg,");\n");
  fprintf(Outfile,"%s%s\n",Scoot,"*InputBuffer=0;");
  if(ZZ)free(ZZ);
}


void AddFuncs (void)
{
  char *ZZ;
  ZZ=(char*)calloc(256+65535,1);
  char Last[2048];
  *Last=0;
  CloseAll();
  if((FP1=fopen(prcFile,"r"))==0)
   {
     fprintf(stderr,"Can't open file %s\n",prcFile);
     exit(1);
   }
  if((Outfile=fopen(FileOut,"a"))==0)
   {
     fprintf(stderr,"Can't open file %s\n",FileOut);
     exit(1);
   }
  if(ProtoType[1].Prototype[0]>0)
    {
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","// ************************************");
      fprintf(Outfile,"%s%s\n","//       ",BCX_STR_USR_PROCS);
      fprintf(Outfile,"%s\n","// ************************************");
      fprintf(Outfile,"%s\n","\n");
    }
  while(!EoF(FP1))
    {
      ZZ[0]=0;
      AR_fgets_retval=fgets(ZZ,65535,FP1);
      if(ZZ[strlen(ZZ)-1]==10)ZZ[strlen(ZZ)-1]=0;
      if(instr_b(ZZ,"DefWindowProc"))
        {
          if(instr_b(Last,"return ")||instr_b(Last,"CallWindowProc")||instr_b(Last,"DefWindowProc")||instr_b(Last,"DefMDIChildProc")||instr_b(Last,"DefFrameProc"))
            {
              *Last=0;
              continue;
            }
        }
      fprintf(Outfile,"%s\n",ZZ);
      if(str_cmp(left(ZZ,2),"//")!=0)
        {
          strcpy(Last,ZZ);
        }
    }
  CloseAll();
  remove (prcFile);
  remove (udtFile);
  remove (datFile);
  remove (cstFile);
  remove (ovrFile);
  remove (setFile);
  remove (enuFile);
  if(ZZ)free(ZZ);
}


int CheckLocal (char *ZZ, int* varidx)
{
  char TT[2048];
  if(LocalVarCnt)
    {
      strcpy(TT,Clean(ZZ));
      RemoveAll(TT," &*()",1);
      if(instr_b(TT,"["))
        {
          strcpy(TT,left(TT,instr_b(TT,"[")-1));
        }
        {int i;
      for(i=1; i<=LocalVarCnt; i+=1)
        {
          if(str_cmp(TT,LocalVars[i].VarName)==0)
            {
              (*varidx)=i;
              return LocalVars[i].VarType;
            }
        }
        }
    }
  return vt_UNKNOWN;
}


int CheckGlobal (char *ZZ, int* varidx)
{
  int     hn;
  int     s;
  char TT[2048];
  strcpy(TT,Clean(ZZ));
  RemoveAll(TT," &*()",1);
  if(instr_b(TT,"["))
    {
      strcpy(TT,left(TT,instr_b(TT,"[")-1));
    }
  hn=HashNumber(TT);
  while(GlobalVarHash[hn])
    {
      s=GlobalVarHash[hn];
      if(str_cmp(TT,GlobalVars[s].VarName)==0)
        {
          (*varidx)=s;
          return GlobalVars[s].VarType;
        }
      hn=imod(hn+1,MaxGlobalVars);
    }
  return vt_UNKNOWN;
}


int CheckType (char *ZZ)
{
  char Keyword[2048];
  int     varid=0;
  int     i;
  strcpy(Keyword,lcase(ZZ));
  for(;;)
  {
    if(str_cmp(Keyword,"int")==0)
      {
        return vt_INTEGER;
      }
    if(str_cmp(Keyword,"string")==0)
      {
        return vt_STRVAR;
      }
    if(str_cmp(Keyword,"char")==0)
      {
        return vt_CHAR;
      }
    if(str_cmp(Keyword,"pchar")==0)
      {
        return vt_PCHAR;
      }
    if(str_cmp(Keyword,"byte")==0)
      {
        return vt_BYTE;
      }
    if(str_cmp(Keyword,"double")==0)
      {
        return vt_DOUBLE;
      }
    if(str_cmp(Keyword,"ldouble")==0)
      {
        return vt_LDOUBLE;
      }
    if(str_cmp(Keyword,"file")==0)
      {
        return vt_FILEPTR;
      }
    if(str_cmp(Keyword,"float")==0)
      {
        return vt_SINGLE;
      }
    if(str_cmp(Keyword,"bool")==0 ||  str_cmp(Keyword,"boolean")==0)
      {
        return vt_BOOL;
      }
    if(str_cmp(Keyword,"long")==0)
      {
        return vt_LONG;
      }
    if(str_cmp(Keyword,"dword")==0)
      {
        return vt_DWORD;
      }
    if(str_cmp(Keyword,"farproc")==0)
      {
        return vt_FARPROC;
      }
    if(str_cmp(Keyword,"void")==0)
      {
        return vt_VOID;
      }
    if(str_cmp(Keyword,"lpbyte")==0)
      {
        return vt_LPBYTE;
      }
    if(str_cmp(Keyword,"lresult")==0)
      {
        return vt_LRESULT;
      }
    if(str_cmp(Keyword,"short")==0)
      {
        return vt_SHORT;
      }
    if(str_cmp(Keyword,"ushort")==0)
      {
        return vt_USHORT;
      }
    if(str_cmp(Keyword,"uint")==0)
      {
        return vt_UINT;
      }
    if(str_cmp(Keyword,"ulong")==0)
      {
        return vt_ULONG;
      }
    if(str_cmp(Keyword,"colorref")==0)
      {
        return vt_COLORREF;
      }
    if(str_cmp(Keyword,"handle")==0)
      {
        return vt_HANDLE;
      }
    if(str_cmp(Keyword,"hdc")==0)
      {
        return vt_HDC;
      }
    if(str_cmp(Keyword,"variant")==0)
      {
        return vt_VARIANT;
      }
    break;
  }
  i=CheckLocal(ZZ, &varid);
  if(i==vt_UNKNOWN)
    {
      i=DefsID(ZZ);
      if(i)
        {
          return TypeDefs[i].TypeofDef;
        }
    }
  else
    {
      return i;
    }
  return CheckGlobal(ZZ, &varid);
}


void ExportInternalConst (void)
{
  if(Use_FillArray)
    {
      strcpy(Src,"CONST vt_INTEGER =  2");
      PassOne=1;
      Parse(Src);
      Emit();
      strcpy(Src,"CONST vt_SINGLE  =  3");
      PassOne=1;
      Parse(Src);
      Emit();
      strcpy(Src,"CONST vt_DOUBLE  =  4");
      PassOne=1;
      Parse(Src);
      Emit();
      strcpy(Src,"CONST vt_LDOUBLE  =  5");
      PassOne=1;
      Parse(Src);
      Emit();
    }
}


int RestrictedWords (char *ZZ)
{
  if(str_cmp(ZZ,"CmdLine")==0)
    {
      return 1;
    }
  if(str_cmp(ZZ,"CmdShow")==0)
    {
      return 1;
    }
  if(str_cmp(ZZ,"hInst")==0)
    {
      return 1;
    }
  if(str_cmp(ZZ,"hPrev")==0)
    {
      return 1;
    }
  if(str_cmp(ZZ,"hWnd")==0)
    {
      return 1;
    }
  if(str_cmp(ZZ,"lParam")==0)
    {
      return 1;
    }
  if(str_cmp(ZZ,"Msg")==0)
    {
      return 1;
    }
  if(str_cmp(ZZ,"wParam")==0)
    {
      return 1;
    }
  if(str_cmp(ZZ,"vt_INTEGER")==0)
    {
      return 1;
    }
  if(str_cmp(ZZ,"vt_SINGLE")==0)
    {
      return 1;
    }
  if(str_cmp(ZZ,"vt_DOUBLE")==0)
    {
      return 1;
    }
  if(str_cmp(ZZ,"vt_LDOUBLE")==0)
    {
      return 1;
    }
  return 0;
}


int DataType (char *ZZ)
{
  char Keyword[2048];
  int     i;
  if(ZZ[0]==34)
    {
      return vt_STRLIT;
    }
  if(inchr(ZZ,"$"))
    {
      return vt_STRVAR;
    }
  if(IsNumber(ZZ))
    {
      return vt_NUMBER;
    }
  i=DefsID(ZZ);
  if(i)
    {
      return TypeDefs[i].TypeofDef;
    }
  strcpy(Keyword,lcase(ZZ));
  if(str_cmp(Keyword,"strlen")==0)
    {
      return vt_DECFUNC;
    }
  if(str_cmp(Keyword,"instr")==0)
    {
      return vt_DECFUNC;
    }
  if(str_cmp(Keyword,"inchr")==0)
    {
      return vt_DECFUNC;
    }
  if(str_cmp(Keyword,"sizeof")==0)
    {
      return vt_DECFUNC;
    }
  if(str_cmp(Keyword,"tally")==0)
    {
      return vt_DECFUNC;
    }
  if(str_cmp(Keyword,"band")==0)
    {
      return vt_DECFUNC;
    }
  if(str_cmp(Keyword,"bor")==0)
    {
      return vt_DECFUNC;
    }
  if(str_cmp(Keyword,"lof")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"pos")==0)
    {
      return vt_DECFUNC;
    }
  if(str_cmp(Keyword,"qbcolor")==0)
    {
      return vt_DECFUNC;
    }
  if(str_cmp(Keyword,"split")==0)
    {
      return vt_DECFUNC;
    }
  if(str_cmp(Keyword,"dsplit")==0)
    {
      return vt_DECFUNC;
    }
  if(str_cmp(Keyword,"sgn")==0)
    {
      return vt_DECFUNC;
    }
  if(str_cmp(Keyword,"timer")==0)
    {
      return vt_SINGLE;
    }
  if(str_cmp(Keyword,"keypress()")==0)
    {
      return vt_DECFUNC;
    }
  if(str_cmp(Keyword,"getattr")==0)
    {
      return vt_DECFUNC;
    }
  if(str_cmp(Keyword,"fix")==0)
    {
      return vt_DECFUNC;
    }
  if(str_cmp(Keyword,"instrrev")==0)
    {
      return vt_DECFUNC;
    }
  if(str_cmp(Keyword,"kbhit")==0)
    {
      return vt_DECFUNC;
    }
  if(str_cmp(Keyword,"exp")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"expl")==0)
    {
      return vt_LDOUBLE;
    }
  if(str_cmp(Keyword,"sinh")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"cosh")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"tanh")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"asinh")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"acosh")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"atanh")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"round")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"val")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"vall")==0)
    {
      return vt_LDOUBLE;
    }
  if(str_cmp(Keyword,"iif")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"bin2dec")==0)
    {
      return vt_INTEGER;
    }
  if(str_cmp(Keyword,"hex2dec")==0)
    {
      return vt_INTEGER;
    }
  if(str_cmp(Keyword,"rnd")==0)
    {
      return vt_SINGLE;
    }
  if(str_cmp(Keyword,"frac")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"fracl")==0)
    {
      return vt_LDOUBLE;
    }
  if(str_cmp(Keyword,"asin")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"asinl")==0)
    {
      return vt_LDOUBLE;
    }
  if(str_cmp(Keyword,"hypot")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"hypotl")==0)
    {
      return vt_LDOUBLE;
    }
  if(str_cmp(Keyword,"log")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"logl")==0)
    {
      return vt_LDOUBLE;
    }
  if(str_cmp(Keyword,"log10")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"log10l")==0)
    {
      return vt_LDOUBLE;
    }
  if(str_cmp(Keyword,"acos")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"acosl")==0)
    {
      return vt_LDOUBLE;
    }
  if(str_cmp(Keyword,"atan")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"atanl")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"sin")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"sinl")==0)
    {
      return vt_LDOUBLE;
    }
  if(str_cmp(Keyword,"cos")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"cosl")==0)
    {
      return vt_LDOUBLE;
    }
  if(str_cmp(Keyword,"tan")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"tanl")==0)
    {
      return vt_LDOUBLE;
    }
  if(str_cmp(Keyword,"pow")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"powl")==0)
    {
      return vt_LDOUBLE;
    }
  if(str_cmp(Keyword,"sqrt")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"sqrtl")==0)
    {
      return vt_LDOUBLE;
    }
  if(str_cmp(Keyword,"min")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"max")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"exist")==0)
    {
      return vt_DECFUNC;
    }
  if(str_cmp(Keyword,"abs")==0)
    {
      return vt_DOUBLE;
    }
  if(str_cmp(Keyword,"absl")==0)
    {
      return vt_LDOUBLE;
    }
  if(str_cmp(Keyword,"freefile")==0)
    {
      return vt_FILEPTR;
    }
  if(str_cmp(Keyword,"fint")==0)
    {
      return vt_INTEGER;
    }
  if(inchr(ZZ,"%"))
    {
      return vt_INTEGER;
    }
  if(inchr(ZZ,"!"))
    {
      return vt_SINGLE;
    }
  if(inchr(ZZ,"#"))
    {
      return vt_DOUBLE;
    }
  if(inchr(ZZ,"^"))
    {
      return vt_DOUBLE;
    }
  if(inchr(ZZ,"¦"))
    {
      return vt_LDOUBLE;
    }
  if(iMatchRgt(ZZ,"@"))
    {
      return vt_FILEPTR;
    }
  if(inchr(ZZ," "))
    {
      return vt_UDT;
    }
  if(isalpha(*ZZ))
    {
      return vt_INTEGER;
    }
  return vt_UNKNOWN;
}


void CloseAll (void)
{
 #if defined (__APPLE__)
  if(SourceFile)
   {
     fclose(SourceFile);
     SourceFile=NULL;
   }
  if(FP2)
   {
     fclose(FP2);
     FP2=NULL;
   }
  if(FP3)
   {
     fclose(FP3);
     FP3=NULL;
   }
  if(FP4)
   {
     fclose(FP4);
     FP4=NULL;
   }
  if(FP5)
   {
     fclose(FP5);
     FP5=NULL;
   }
  if(FP6)
   {
     fclose(FP6);
     FP6=NULL;
   }
  if(FP7)
   {
     fclose(FP7);
     FP7=NULL;
   }
  if(FP8)
   {
     fclose(FP8);
     FP8=NULL;
   }
  if(FP9)
   {
     fclose(FP9);
     FP9=NULL;
   }
  if(FP10)
   {
     fclose(FP10);
     FP10=NULL;
   }
  if(FP11)
   {
     fclose(FP11);
     FP11=NULL;
   }
  if(Outfile)
   {
     fclose(Outfile);
     Outfile=NULL;
   }
  if(FP1)
   {
     fclose(FP1);
     FP1=NULL;
   }
  if(ResIn)
   {
     fclose(ResIn);
     ResIn=NULL;
   }
  if(ResOut)
   {
     fclose(ResOut);
     ResOut=NULL;
   }
  if(UserResIn)
   {
     fclose(UserResIn);
     UserResIn=NULL;
   }
  if(fpErr)
   {
     fclose(fpErr);
     fpErr=NULL;
   }
  if(fpHFile)
   {
     fclose(fpHFile);
     fpHFile=NULL;
   }
  if(FP68)
   {
     fclose(FP68);
     FP68=NULL;
   }
  if(fpdef)
   {
     fclose(fpdef);
     fpdef=NULL;
   }
  if(SaveOutfileNum)
   {
     fclose(SaveOutfileNum);
     SaveOutfileNum=NULL;
   }
 #else
  fcloseall();
 #endif
}


char * Clean (char *ZZ)
{
  char *BCX_RetStr={0};
  char Tmp[2048];
  if(inchr(ZZ,"%"))
    {
      if(str_cmp(trim(ZZ),"%")==0)
        {
          BCX_RetStr=BCX_TmpStr(strlen(" % "));
          strcpy(BCX_RetStr," % ");
          return BCX_RetStr;
        }
    }
  if(iMatchNQ(ZZ,"!="))
    {
      BCX_RetStr=BCX_TmpStr(strlen(ZZ));
      strcpy(BCX_RetStr,ZZ);
      return BCX_RetStr;
    }
  strcpy(Tmp,ZZ);
  RemoveAll(Tmp,"%$#!@¦",1);
  BCX_RetStr=BCX_TmpStr(strlen(Tmp));
  strcpy(BCX_RetStr,Tmp);
  return BCX_RetStr;
}


void RemoveAll (char * Arg,char * MatchChars,int qtflag)
{
   PCHAR  C=Arg;
   PCHAR  pmc;
  while(*Arg)
    {
      if(qtflag)
        {
          if(*Arg==34)
            {
              *(C++)=*Arg;
              while(*(++Arg)!=34)
                {
                  *(C++)=*Arg;
                  if(*Arg==0)
                    {
                      return;
                    }
                }
              *(C++)=*(Arg++);
              continue;
            }
        }
      pmc=MatchChars;
      while(*pmc)
        {
          if(*(pmc++)==*Arg)
            {
              goto SKIP;
            }
        }
      *(C++)=*Arg;

SKIP:;
      Arg++;
    }
  *C=0;
}


void Warning (char * ZZ,int WarnLvl)
{
  static  FILE   *fErr;
  memset(&fErr,0,sizeof(fErr));
  if(WarnLvl)
    {
      strcpy(WarnMsg, join(7,WarnMsg," Line",str(ModuleLineNos[ModuleNdx])," in Module: ",trim(Modules[ModuleNdx])," - ",ZZ));
    }
  else
    {
      strcat(WarnMsg,ZZ);
    }
  strcat(WarnMsg,CRLF);
  if(ErrFile)
    {
      if((fErr=fopen(FileErr,"a"))==0)
       {
         fprintf(stderr,"Can't open file %s\n",FileErr);
         exit(1);
       }
      fprintf(fErr,"%s%s\n","WARNING ",ZZ);
      if(fErr)
       {
         fclose(fErr);
         fErr=NULL;
       }
    }
}


PCHAR GetVarTypeName (int i)
{
  static char A[2048];
  for(;;)
  {
    if(i==vt_INTEGER)
      {
        strcpy(A,"int");
        break;
      }
    if(i==vt_STRVAR)
      {
        strcpy(A,"char *");
        break;
      }
    if(i==vt_STRLIT)
      {
        strcpy(A,"STRLIT");
        break;
      }
    if(i==vt_UNKNOWN)
      {
        strcpy(A,"UNKNOWN");
        break;
      }
    if(i==vt_SINGLE)
      {
        strcpy(A,"float");
        break;
      }
    if(i==vt_DOUBLE)
      {
        strcpy(A,"double");
        break;
      }
    if(i==vt_LDOUBLE)
      {
        strcpy(A,"LDOUBLE");
        break;
      }
    if(i==vt_DECFUNC)
      {
        strcpy(A,"DECFUNC");
        break;
      }
    if(i==vt_NUMBER)
      {
        strcpy(A,"NUMBER");
        break;
      }
    if(i==vt_FILEPTR)
      {
        strcpy(A,"FILE*");
        break;
      }
    if(i==vt_UDT)
      {
        strcpy(A,"struct");
        break;
      }
    if(i==vt_STRUCT)
      {
        strcpy(A,"struct");
        break;
      }
    if(i==vt_UNION)
      {
        strcpy(A,"union");
        break;
      }
    if(i==vt_BOOL)
      {
        strcpy(A,"bool");
        break;
      }
    if(i==vt_CHAR)
      {
        strcpy(A,"char");
        break;
      }
    if(i==vt_CHARPTR)
      {
        strcpy(A,"char");
        break;
      }
    if(i==vt_PCHAR)
      {
        strcpy(A,"PCHAR");
        break;
      }
    if(i==vt_VOID)
      {
        strcpy(A,"void");
        break;
      }
    if(i==vt_LONG)
      {
        strcpy(A,"long");
        break;
      }
    if(i==vt_DWORD)
      {
        strcpy(A,"DWORD");
        break;
      }
    if(i==vt_FARPROC)
      {
        strcpy(A,"FARPROC");
        break;
      }
    if(i==vt_LPBYTE)
      {
        strcpy(A,"LPBYTE");
        break;
      }
    if(i==vt_LRESULT)
      {
        strcpy(A,"LRESULT");
        break;
      }
    if(i==vt_BYTE)
      {
        strcpy(A,"BYTE");
        break;
      }
    if(i==vt_SHORT)
      {
        strcpy(A,"short");
        break;
      }
    if(i==vt_USHORT)
      {
        strcpy(A,"USHORT");
        break;
      }
    if(i==vt_COLORREF)
      {
        strcpy(A,"COLORREF");
        break;
      }
    if(i==vt_UINT)
      {
        strcpy(A,"UINT");
        break;
      }
    if(i==vt_ULONG)
      {
        strcpy(A,"ULONG");
        break;
      }
    if(i==vt_HANDLE)
      {
        strcpy(A,"HANDLE");
        break;
      }
    if(i==vt_HINSTANCE)
      {
        strcpy(A,"HINSTANCE");
        break;
      }
    if(i==vt_HDC)
      {
        strcpy(A,"HDC");
        break;
      }
    if(i==vt_VARIANT)
      {
        strcpy(A,"VARIANT");
        break;
      }
      // case else
      {
        *A=0;
      }
    break;
  }
  return A;
}


int HashNumber (char *HT)
{
   char*  TT;
   ULONG  i=0;
  TT=HT;
  while(*TT)
    {
      i<<=1;
  i ^= *TT;
      TT++;
    }
  return imod(i,MaxGlobalVars);
}


void AddLibrary (char *LibName)
{
  static int     nTimes;
  static int     nLibNdx;
  memset(&nLibNdx,0,sizeof(nLibNdx));
  char TempLibName[2048];
  strcpy(TempLibName,lcase(LibName));
  if(!inchr(TempLibName,DQ)&&!inchr(TempLibName,"<"))
    {
      strcpy(TempLibName,enc(TempLibName,60,62));
    }
  if(nTimes==0)
    {
        {int i;
      for(i=0; i<=MaxLib-1; i+=1)
        {
          *Library[i]=0;
        }
        }
      nTimes++;
      strcpy(Library[0],TempLibName);
      return;
    }
  nLibNdx=0;
  while(Library[nLibNdx][0]!=0)
    {
      if(str_cmp(Library[nLibNdx],TempLibName)==0)
        {
          return;
        }
      nLibNdx++;
    }
  if(nLibNdx<MaxLib-1)
    {
      strcpy(Library[nLibNdx],TempLibName);
    }
}


void RemoveLibrary (char *LibName)
{
  if(!instr_b(RmLibs,LibName,1,1))
    {
      strcpy(RmLibs, join(3,RmLibs,",",lcase(LibName)));
    }
}


void EmitLibs (void)
{
  static int     nTimes;
  static int     nCount;
  char ltmp[2048];
  if(nTimes>0)
    {
      return;
    }
  nTimes++;
  if(Library[0][0]==0)
    {
      return;
    }
  fprintf(FP7,"%s\n","");
  fprintf(FP7,"%s\n","#ifndef LINUXBCX");
  fprintf(FP7,"%s\n","#if !defined( __LCC__ )");
    {int i;
  for(i=0; i<=MaxLib-1; i+=1)
    {
      if(Library[i][0]==0&&nCount>0)
        {
          goto NEXTLIB;
        }
      else if(Library[i][0]==0)
        {
          goto NEXTLIB;
        }
      strcpy(ltmp,Library[i]);
      RemoveAll(ltmp,join(2,"<>",DQ));
      if(instr_b(RmLibs,ltmp))
        {
          continue;
        }
      if(nCount==0)
        {
          nCount++;
          fprintf(FP7,"%s\n","// *************************************************");
          fprintf(FP7,"%s\n","// Instruct Linker to Search Object/Import Libraries");
          fprintf(FP7,"%s\n","// *************************************************");
        }
      fprintf(FP7,"%s%s%s\n","#pragma comment(lib,",enc(ltmp),")");
    }
    }

NEXTLIB:;
  fprintf(FP7,"%s\n","#else");
  strcat(RmLibs,",<libc.lib>,<kernel32.lib>,<comdlg32.lib>,<user32.lib>,<gdi32.lib>,<advapi32.lib>,<comctl32.lib>,<crtdll.lib>");
    {int i;
  for(i=0; i<=MaxLib-1; i+=1)
    {
      if(Library[i][0]==0&&nCount>0)
        {
          fprintf(FP7,"%s\n","// *************************************************");
          fprintf(FP7,"%s\n","// End of Object/Import Libraries To Search");
          fprintf(FP7,"%s\n","// *************************************************");
          goto LIBEND;
        }
      else if(Library[i][0]==0)
        {
          goto LIBEND;
        }
      if(instr_b(RmLibs,Library[i]))
        {
          continue;
        }
      if(nCount==0)
        {
          nCount++;
          fprintf(FP7,"%s\n","");
          fprintf(FP7,"%s\n","// *************************************************");
          fprintf(FP7,"%s\n","// Instruct Linker to Search Object/Import Libraries");
          fprintf(FP7,"%s\n","// *************************************************");
        }
      fprintf(FP7,"%s%s\n","#pragma lib ",Library[i]);
    }
    }

LIBEND:;
  fprintf(FP7,"%s\n","#endif");
  fprintf(FP7,"%s\n","#endif     // LINUXBCX not defined");
}


void AddGlobal (char * GlobalName,int GlobalType,int GlobalDef,char * GlobalDim,int GlobalPtr,int GlobalFS,int GlobalExtn,int iEmitted,int iConst)
{
  char FirstVar[2048];
  char SecondVar[2048];
  char Warn[2048];
  int     ss;
  int     s;
  if(RestrictedWords(GlobalName)&&TestState)
    {
      strcpy(Warn, join(3,"Restricted Word ",GlobalName," on Line"));
      strcpy(Warn, join(4,Warn,str(ModuleLineNos[ModuleNdx])," in Module: ",trim(Modules[ModuleNdx])));
      Warning(Warn);
    }
  ss=HashNumber(GlobalName);
  while(GlobalVarHash[ss])
    {
      s=GlobalVarHash[ss];
      if(str_cmp(GlobalName,GlobalVars[s].VarName)==0)
        {
          if(InConditional==0||(InConditional>0&&str_cmp(InIfDef,GlobalVars[s].VarCondDef)==0))
            {
              if(GlobalVars[s].VarType!=GlobalType||str_cmp(GlobalDim,GlobalVars[s].VarDim)!=0 || GlobalVars[s].VarDef!=GlobalDef)
                {
                  strcpy(FirstVar, join(11,"Line",str(ModuleLineNos[ModuleNdx])," in Module: ",trim(Modules[ModuleNdx])," : ",GlobalName,GlobalDim," as ",GetVarTypeName(GlobalType)," ",TypeDefs[GlobalDef].VarName));
                  strcpy(SecondVar, join(11,"Line",str(GlobalVars[s].VarLine)," in Module: ",GlobalVars[s].VarModule," : ",GlobalName,GlobalVars[s].VarDim," as ",GetVarTypeName(GlobalVars[s].VarType)," ",TypeDefs[GlobalVars[s].VarDef].VarName));
                  strcpy(Warn, join(4,"Two Variables ",FirstVar," previously defined at ",SecondVar));
                  Warning(Warn);
                }
              return;
            }
        }
      ss=imod(ss+1,MaxGlobalVars);
    }
  GlobalVarCnt++;
  if(GlobalVarCnt==MaxGlobalVars)
    {
      Abort("Maximum Global Variables reached.");
    }
  strcpy(GlobalVars[GlobalVarCnt].VarName,GlobalName);
  GlobalVars[GlobalVarCnt].VarType=GlobalType;
  GlobalVars[GlobalVarCnt].VarDef=GlobalDef;
  strcpy(GlobalVars[GlobalVarCnt].VarDim,GlobalDim);
  GlobalVars[GlobalVarCnt].VarLine=ModuleLineNos[ModuleNdx];
  GlobalVars[GlobalVarCnt].VarPntr=GlobalPtr;
  GlobalVars[GlobalVarCnt].VarSF=GlobalFS;
  GlobalVars[GlobalVarCnt].VarEmitFlag=iEmitted;
  strcpy(GlobalVars[GlobalVarCnt].VarModule,trim(Modules[ModuleNdx]));
  GlobalVars[GlobalVarCnt].VarExtn=GlobalExtn;
  GlobalVars[GlobalVarCnt].VarCondLevel=InConditional;
  GlobalVars[GlobalVarCnt].VarConstant=iConst;
  strcpy(GlobalVars[GlobalVarCnt].VarCondDef,InIfDef);
  GlobalVarHash[ss]=GlobalVarCnt;
}


void AddLocal (char * LocalName,int LocalType,int LocalDef,char * LocalDim,int LocalPtr,int LocalFS,int iEmitted,int iConst)
{
  int     varid=0;
  char FirstVar[2048];
  char SecondVar[2048];
  char Warn[2048];
  int     s;
  if(LocalVarCnt&&TestState)
    {
      if(CheckGlobal(LocalName, &varid)!=vt_UNKNOWN)
        {
          if(LocalDef)
            {
              strcpy(FirstVar, join(9,"Line",str(ModuleLineNos[ModuleNdx])," in Module: ",trim(Modules[ModuleNdx])," : ",LocalName,LocalDim," as ",TypeDefs[LocalDef].VarName));
            }
          else
            {
              strcpy(FirstVar, join(9,"Line",str(ModuleLineNos[ModuleNdx])," in Module: ",trim(Modules[ModuleNdx])," : ",LocalName,LocalDim," as ",GetVarTypeName(LocalType)));
            }
          if(GlobalVars[varid].VarDef)
            {
              strcpy(SecondVar, join(9,"Line",str(GlobalVars[varid].VarLine)," in Module: ",GlobalVars[varid].VarModule," : ",LocalName,GlobalVars[varid].VarDim," as ",TypeDefs[GlobalVars[varid].VarDef].VarName));
            }
          else
            {
              strcpy(SecondVar, join(9,"Line",str(GlobalVars[varid].VarLine)," in Module: ",GlobalVars[varid].VarModule," : ",LocalName,GlobalVars[varid].VarDim," as ",GetVarTypeName(GlobalVars[varid].VarType)));
            }
          strcpy(Warn, join(5,"Local Variable ",FirstVar,CRLF,"Has Same Name as Global ",SecondVar));
          Warning(Warn);
        }
      for(s=1; s<=LocalVarCnt; s+=1)
        {
          if(str_cmp(LocalName,LocalVars[s].VarName)==0)
            {
              if(LocalVars[s].VarType!=LocalType||str_cmp(LocalDim,LocalVars[s].VarDim)!=0 || LocalVars[s].VarDef!=LocalDef)
                {
                  strcpy(FirstVar, join(11,"Line",str(ModuleLineNos[ModuleNdx])," in Module: ",trim(Modules[ModuleNdx])," : ",LocalName,LocalDim," as ",GetVarTypeName(LocalType)," ",TypeDefs[LocalDef].VarName));
                  strcpy(SecondVar, join(11,"Line",str(LocalVars[s].VarLine)," in Module: ",LocalVars[s].VarModule," : ",LocalName,LocalVars[s].VarDim," as ",GetVarTypeName(LocalVars[s].VarType)," ",TypeDefs[LocalVars[s].VarDef].VarName));
                  strcpy(Warn, join(4,"Two Variables ",FirstVar," previously defined at ",SecondVar));
                  Warning(Warn);
                }
              return;
            }
        }
    }
  LocalVarCnt++;
  if(LocalVarCnt==MaxLocalVars)
    {
      strcpy(Warn,"Maximum Local Variables reached.");
      Abort(Warn);
    }
  strcpy(LocalVars[LocalVarCnt].VarName,LocalName);
  LocalVars[LocalVarCnt].VarType=LocalType;
  LocalVars[LocalVarCnt].VarDef=LocalDef;
  strcpy(LocalVars[LocalVarCnt].VarDim,LocalDim);
  LocalVars[LocalVarCnt].VarLine=ModuleLineNos[ModuleNdx];
  LocalVars[LocalVarCnt].VarPntr=LocalPtr;
  LocalVars[LocalVarCnt].VarSF=LocalFS;
  LocalVars[LocalVarCnt].VarEmitFlag=iEmitted;
  LocalVars[LocalVarCnt].VarConstant=iConst;
  strcpy(LocalVars[LocalVarCnt].VarModule,trim(Modules[ModuleNdx]));
}


int IsNumber (char *a)
{
  int     i=0;
  if(!*a)
    {
      return FALSE;
    }
  while(a[i])
    {
      if(a[i]>47&&a[i]<58)
        {
          i++;
        }
      else
        {
          return FALSE;
        }
    }
  return TRUE;
}


int IsNumberEx (char *a)
{
  int     i=0;
  if(!*a)
    {
      return FALSE;
    }
  while(a[i])
    {
      if(a[i]>44&&a[i]<58)
        {
          i++;
        }
      else
        {
          return FALSE;
        }
    }
  return TRUE;
}


void StripTabs (void)
{
  int     i=0;
  while(Src[i])
    {
      if(Src[i]==9)
        {
          Src[i]=32;
        }
      i++;
    }
}


void PushFileIO (void)
{
  FPtr[++FPtrNdx]=SourceFile;
}


void PopFileIO (void)
{
  if(FPtrNdx==0)
    {
      return;
    }
  if(SourceFile)
   {
     fclose(SourceFile);
     SourceFile=NULL;
   }
  LinesRead+=(ModuleLineNos[ModuleNdx--]);
  SourceFile=FPtr[FPtrNdx--];
}


int Inset (char *Mane, char *Match)
{
  int     i=-1;
  int     j=-1;
  while(Match[++i])
    {
      while(Mane[++j])
        {
          if(Match[i]==Mane[j])
            {
              return TRUE;
            }
        }
      j=-1;
    }
  return FALSE;
}


void CheckParQuotes (void)
{
  int     CountR=0;
  int     CountS=0;
  int     i=0;
   bool  DoCount=TRUE;
  while(Src[i])
    {
      if(Src[i]==34)
        {
          DoCount=!DoCount;
        }
      if(DoCount)
        {
          if(Src[i]==40)
            {
              CountR++;
            }
          else if(Src[i]==41)
            {
              CountR--;
            }
          else if(Src[i]==91)
            {
              CountS++;
            }
          else if(Src[i]==93)
            {
              CountS--;
            }
        }
      i++;
    }
  if(!DoCount)
    {
      Abort("Unmatched Quotes");
    }
  else if(CountS)
    {
      Abort("Unmatched []");
    }
  else if(CountR)
    {
      Abort("Unmatched ()");
    }
}


void ClearIfThenStacks (void)
{
    {int i;
  for(i=0; i<=127; i+=1)
    {
      *SrcStk[i]=0;
    }
    }
  SrcCnt=0;
}


int IsQuoted (char *ZZ)
{
  if(!iMatchLft(ltrim(ZZ),DQ))
    {
      return 0;
    }
  if(!iMatchRgt(rtrim(ZZ),DQ))
    {
      return 0;
    }
  return TRUE;
}


void PostProcess (void)
{
  int     A;
  if(ReDirect==TRUE)
    {
      if((FP1=fopen(FileOut,"r"))==0)
       {
         fprintf(stderr,"Can't open file %s\n",FileOut);
         exit(1);
       }
      while(!EoF(FP1))
        {
          Z[0]=0;
          AR_fgets_retval=fgets(Z,65535,FP1);
          if(Z[strlen(Z)-1]==10)Z[strlen(Z)-1]=0;
          printf("%s\n",Z);
        }
      CloseAll();
    }
  strcpy(OutfileClone,FileOut);
  for(A=1; A<=EntryCnt; A+=1)
    {
      strcpy(OutfileClone,extract(OutfileClone,"."));
      strcpy(Cmd,RemoveStr(Entry[A],DQ));
      strcpy(Cmd,replace(Cmd,"\\\\","\\"));
      strcpy(Cmd,iReplace(Cmd,"$file$",extract(OutfileClone,".")));
      printf("%s%s\n","Shelling Out To: ",Cmd);
      Shell(Cmd);
    }
  if(Compiler[0]>0)
    {
      strcpy(Compiler,trim(RemoveStr(Compiler,DQ)));
      if(inchr(Compiler," "))
        {
          strcpy(Compiler, join(3,enc(extract(Compiler," "))," ",remain(Compiler," ")));
        }
      else
        {
          strcpy(Compiler,enc(Compiler));
        }
      strcpy(FileOut, join(2,extract(FileOut,"."),".cc"));
      strcpy(Compiler, join(3,Compiler," ",FileOut));
      strcpy(Compiler,iReplace(Compiler,"$FILE$",extract(OutfileClone,".")));
      strcpy(Compiler,replace(Compiler,"\\\\","\\"));
      strcpy(Compiler,replace(Compiler,DDQ,DQ));
      printf("%s%s\n","Shelling Out To: ",Compiler);
      Shell(Compiler);
    }
  if(Linker[0]>0)
    {
      strcpy(Linker,trim(RemoveStr(Linker,DQ)));
      if(inchr(Linker," "))
        {
          strcpy(Linker, join(5,DQ,extract(Linker," "),DQ," ",remain(Linker," ")));
        }
      else
        {
          strcpy(Linker,enc(Linker));
        }
      strcpy(FileOut, join(2,extract(FileOut,"."),".obj"));
      strcpy(Linker, join(3,Linker," ",FileOut));
      strcpy(Linker,iReplace(Linker,"$FILE$",extract(OutfileClone,".")));
      strcpy(Linker,replace(Linker,"\\\\","\\"));
      strcpy(Linker,replace(Linker,DDQ,DQ));
      printf("%s%s\n","Shelling Out To:",Linker);
      Shell(Linker);
    }
  for(A=1; A<=XitCount; A+=1)
    {
      strcpy(FileOut,extract(FileOut,"."));
      strcpy(Cmd,RemoveStr(Xit[A],DQ));
      strcpy(Cmd,iReplace(Cmd,"$FILE$",extract(OutfileClone,".")));
      strcpy(Cmd,replace(Cmd,"\\\\","\\"));
      strcpy(Cmd,replace(Cmd,DDQ,DQ));
      printf("%s%s\n","Shelling Out To: ",Cmd);
      Shell(Cmd);
    }
}


void XParse (char *Arg)
{
  char lszTmp[2048];
  int     j;
  int     i=0;
  int     Gapflag=0;
  int     InIF=0;
  if(str_cmp(trim(Arg),"")==0)
    {
      Ndx=0;
      return;
    }
  i=iMatchNQ(Arg,"&&");
  while(i)
    {
      strcpy(Arg,del(Arg,i,2));
      strcpy(Arg,ins(Arg,i," and "));
      i=iMatchNQ(Arg,"&&");
    }
  FastLexer(Arg,SPC,"=&()[]{}',+-*/<>?;.|:^");
  while(++i<17)
    {
      *Stk[i+Ndx]=0;
    }
  for(i=1; i<=Ndx; i+=1)
    {
      strcpy(Keyword1,lcase(Stk[i]));
      if(Keyword1[1]!=0)
        {
          for(;;)
          {
            if(str_cmp(Keyword1,"and")==0)
              {
                strcpy(Stk[i],"&&");
                break;
              }
            if(str_cmp(Keyword1,"or")==0)
              {
                strcpy(Stk[i],"||");
                break;
              }
            if(str_cmp(Keyword1,"not")==0)
              {
                strcpy(Stk[i],"!");
                break;
              }
            if(str_cmp(Keyword1,"is")==0)
              {
                strcpy(Stk[i],"=");
                break;
              }
            if(str_cmp(Keyword1,"xor")==0)
              {
                strcpy(Stk[i],"xor");
                break;
              }
            if(str_cmp(Keyword1,"if")==0 ||  str_cmp(Keyword1,"iif")==0 ||  str_cmp(Keyword1,"iif$")==0 ||  str_cmp(Keyword1,"case")==0 ||  str_cmp(Keyword1,"elseif")==0 ||  str_cmp(Keyword1,"while")==0)
              {
                InIF=1;
                break;
              }
            if(str_cmp(Keyword1,"then")==0)
              {
                InIF=0;
                break;
              }
            if(str_cmp(Keyword1,"byval")==0)
              {
                *Stk[i]=0;
                Gapflag=TRUE;
                break;
              }
            if(str_cmp(Keyword1,"byref")==0)
              {
                if(!iMatchWrd(Stk[1],"declare")&&!iMatchWrd(Stk[1],"c_declare"))
                  {
                    strcpy(ByrefVars[++ByrefCnt],Stk[i+1]);
                  }
                for(j=i; j<=Ndx; j+=1)
                  {
                    if(str_cmp(Stk[j+1],",")==0 ||  str_cmp(Stk[j+1],")")==0)
                      {
                        strcpy(Stk[j],"PTR");
                        break;
                      }
                    strcpy(Stk[j],Stk[j+1]);
                  }
                break;
              }
              // case else
              {
                if(PassOne)
                  {
                    if(str_cmp(Keyword1,enc(chr(92)))==0)
                      {
                        strcpy(Stk[i],"chr$");
                        InsertTokens(i,3,"(","92",")");
                        i+=(3);
                      }
                    else if(TranslateSlash)
                      {
                        strcpy(Stk[i],replace(Stk[i],"\\","\\\\"));
                      }
                  }
              }
            break;
          }
          if(!InIF)
            {
              if(str_cmp(Stk[i],"&&")==0)
                {
                  strcpy(Stk[i],"BAND");
                }
              else if(str_cmp(Stk[i],"||")==0)
                {
                  strcpy(Stk[i],"BOR");
                }
            }
        }
      else
        {
          for(;;)
          {
            if((UCHAR)*(Keyword1)==38)
              {
                if(i<3||inchr("+&,(=",Stk[i-1]))
                  {
                    strcpy(Stk[i+1], join(2," &",Stk[i+1]));
                    *Stk[i]=0;
                    Gapflag=TRUE;
                  }
                break;
              }
            if((UCHAR)*(Keyword1)==63)
              {
                strcpy(Stk[i],"print");
                break;
              }
            if((UCHAR)*(Keyword1)==45)
              {
                if((UCHAR)*(Stk[i+1])==62)
                  {
                    strcpy(Stk[i], join(2,"->",Stk[i+2]));
                    *Stk[++i]=0;
                    *Stk[++i]=0;
                    Gapflag=TRUE;
                  }
                break;
              }
            if((UCHAR)*(Keyword1)==46)
              {
                if(IsNumber(Stk[i-1]))
                  {
                    strcpy(Stk[i], join(2,Stk[i-1],"."));
                    *Stk[i-1]=0;
                    Gapflag=TRUE;
                  }
                if(!inchr(",)=<>*/+-^",Stk[i+1]))
                  {
                    strcpy(Stk[i], join(2,Stk[i],Stk[i+1]));
                    *Stk[++i]=0;
                    Gapflag=TRUE;
                  }
              }
            break;
          }
        }
    }
  if(Gapflag)
    {
      for(i=1; i<=Ndx; i+=1)
        {
          if(!*Stk[i])
            {
              j=i+1;
              while(!*Stk[j]&&(j<Ndx))
                {
                  j++;
                }
              if(!*Stk[j])
                {
                  break;
                }
              strcpy(Stk[i],Stk[j]);
              *Stk[j]=0;
            }
        }
      Ndx=i-1;
    }
  if(PassOne==1)
    {
      if(InFunc)
        {
          for(i=1; i<=Ndx; i+=1)
            {
              for(j=1; j<=ByrefCnt; j+=1)
                {
                  if(iMatchLft(Stk[i]," &"))
                    {
                      strcpy(lszTmp,Stk[i]+2);
                    }
                  else
                    {
                      strcpy(lszTmp,Stk[i]);
                    }
                  if(str_cmp(Clean(lszTmp),Clean(ByrefVars[j]))==0)
                    {
                      if(i>2)
                        {
                          if(inchr("+-^%*/|&<=>,",Stk[i-2])&&str_cmp(Stk[i-1],"*")==0)
                            {
                              *Stk[i-1]=0;
                            }
                          if(iMatchLft(Stk[i]," &"))
                            {
                              strcpy(Stk[i],Stk[i]+2);
                              break;
                            }
                        }
                      else if(i==2)
                        {
                          if(str_cmp(Stk[i-1],"*")==0)
                            {
                              *Stk[i-1]=0;
                            }
                        }
                      strcpy(Stk[i], join(2,"*",Stk[i]));
                      if(str_cmp(Stk[i-1],"(")!=0 ||  str_cmp(Stk[i+1],")")!=0)
                        {
                          strcpy(Stk[i],enc(Stk[i],40,41));
                        }
                      break;
                    }
                }
            }
        }
    }
  if(iMatchWrd(Stk[1],"dim"))
    {
      if(iMatchWrd(Stk[Ndx-1],"static"))
        {
          strcpy(Stk[1],"static");
          strcpy(Stk[Ndx-1],Stk[Ndx]);
          Ndx--;
        }
    }
  strcpy(Keyword1,lcase(Stk[1]));
  if(InTypeDef)
    {
      if(str_cmp(Keyword1,"end")!=0 &&  str_cmp(Keyword1,"dim")!=0 &&  str_cmp(Keyword1,"declare")!=0 &&  str_cmp(Keyword1,"type")!=0 &&  str_cmp(Keyword1,"union")!=0)
        {
          InsertTokens(0,1,"dim");
        }
    }
  if(!InTypeDef)
    {
      char lsz[2048];
      int     Res=1;
      strcpy(lsz, join(3,SPC,Keyword1,SPC));
      if(iMatchNQ(" dim , local , global , raw , static , shared , dynamic , auto , register , extern ",lsz))
        {
          Res=1;
        }
      strcpy(lsz, join(3,SPC,lcase(Stk[2]),SPC));
      if(iMatchNQ(" dim , local , global , raw , static , shared , dynamic , auto , register , extern ",lsz))
        {
          Res=2;
        }
      if(Res>0)
        {
          i=Ndx;
          while(i>1&&str_cmp(Stk[i],")")!=0)
            {
              if(iMatchWrd(Stk[i],"as"))
                {
                  if(iMatchWrd(Stk[i+1],"function"))
                    {
                      if(i+1==Ndx)
                        {
                          *Stk[i]=0;
                        }
                      *Stk[i+1]=0;
                      InsertTokens(Res,1,"function");
                    }
                  else if(iMatchWrd(Stk[i+1],"sub"))
                    {
                      if(i+1==Ndx)
                        {
                          *Stk[i]=0;
                        }
                      *Stk[i+1]=0;
                      InsertTokens(Res,1,"sub");
                    }
                  RemEmptyTokens();
                  break;
                }
              i--;
            }
        }
    }
  if(InTypeDef||iMatchWrd(Stk[1],"declare")||iMatchWrd(Stk[1],"c_declare"))
    {
      if(iMatchWrd(Stk[2],"sub")||iMatchWrd(Stk[2],"function"))
        {
            {int i;
          for(i=2; i<=Ndx; i+=1)
            {
              if(iMatchLft(Stk[i],"as")&&iMatchWrd(Stk[i+1],"string"))
                {
                  if(*Stk[i+2]!=42)
                    {
                      strcpy(Stk[i+1],"char *");
                    }
                }
            }
            }
        }
    }
}


void TokenSubstitutions (void)
{
  int     A;
  int     CompPtr;
  int     CompToken;
  char Keyword[2048];
  int     a;
  int     i;
  int     j;
  int     Tmp;
  for(i=1; i<=Ndx; i+=1)
    {
      if(iMatchWrd(Stk[i],"as"))
        {
          if(iMatchWrd(Stk[i+1],"string"))
            {
              if(str_cmp(Stk[i+2],"*")==0)
                {
                  strcpy(Stk[i],"[");
                  strcpy(Stk[i+1],Stk[i+3]);
                  strcpy(Stk[i+2],"]");
                  strcpy(Stk[i+3],"as");
                  Ndx++;
                  strcpy(Stk[Ndx],"char");
                  break;
                }
            }
        }
    }
  for(i=1; i<=Ndx; i+=1)
    {
      if(!InFunc)
        {
          if(iMatchWrd(Stk[i],"global"))
            {
              strcpy(Stk[i],"dim");
            }
        }
    }
  A=FALSE;
  for(Tmp=1; Tmp<=Ndx; Tmp+=1)
    {
      if(*Stk[Tmp]==48&&Stk[Tmp][1]!=120&&Stk[Tmp][1]!=108)
        {
          strcpy(Stk[Tmp],ltrim(Stk[Tmp],48));
          if(Stk[Tmp][0]==0)
            {
              strcpy(Stk[Tmp],"0");
            }
        }
      if(iMatchWrd(Stk[Tmp],"xor"))
        {
          strcpy(Stk[Tmp],"^");
        }
      else if(str_cmp(Stk[Tmp],"=")==0 &&  str_cmp(Stk[Tmp+1],">")==0)
        {
          strcpy(Stk[Tmp],">");
          strcpy(Stk[Tmp+1],"=");
        }
      else if(str_cmp(Stk[Tmp],"=")==0 &&  str_cmp(Stk[Tmp+1],"<")==0)
        {
          strcpy(Stk[Tmp],"<");
          strcpy(Stk[Tmp+1],"=");
        }
      else if(str_cmp(Stk[Tmp],"<")==0 &&  str_cmp(Stk[Tmp+1],">")==0)
        {
          strcpy(Stk[Tmp],"!=");
          *Stk[Tmp+1]=0;
          A=TRUE;
        }
      else if(str_cmp(Stk[Tmp],">")==0 &&  str_cmp(Stk[Tmp+1],"<")==0)
        {
          strcpy(Stk[Tmp],"!=");
          *Stk[Tmp+1]=0;
          A=TRUE;
        }
      else if(str_cmp(Stk[Tmp],"!")==0 &&  str_cmp(Stk[Tmp+1],"=")==0)
        {
          strcpy(Stk[Tmp],"!=");
          *Stk[Tmp+1]=0;
          A=TRUE;
        }
    }
  if(A==TRUE)
    {
      RemEmptyTokens();
    }
  CompToken=0;
  for(Tmp=1; Tmp<=Ndx; Tmp+=1)
    {
      A=CheckLocal(Stk[Tmp], &i);
      if(A==vt_UNKNOWN)
        {
          A=CheckGlobal(Stk[Tmp], &i);
        }
      if(A==vt_STRUCT||A==vt_UDT||A==vt_UNION)
        {
          CompToken=1;
        }
      if(iMatchWrd(Stk[Tmp],"int")&&str_cmp(Stk[Tmp+1],"(")==0)
        {
          strcpy(Stk[Tmp],"fint");
        }
      else if(iMatchWrd(Stk[Tmp],"integer"))
        {
          strcpy(Stk[Tmp],"int");
        }
      else if(iMatchWrd(Stk[Tmp],"fint")&&str_cmp(Stk[Tmp+1],")")==0)
        {
          strcpy(Stk[Tmp],"int");
        }
    }
  CompPtr=0;
  for(Tmp=1; Tmp<=Ndx; Tmp+=1)
    {
      strcpy(Keyword,lcase(Stk[Tmp]));
      a=inchr("abcdefghijklmnopqrstuvwxyz",Keyword);
      for(;;)
      {
        if(a==1)
          {
            for(;;)
            {
              if(str_cmp(Keyword,"abs")==0)
                {
                  strcpy(Stk[Tmp],"abs");
                  break;
                }
              if(str_cmp(Keyword,"acos")==0)
                {
                  strcpy(Stk[Tmp],"acos");
                  break;
                }
              if(str_cmp(Keyword,"acosl")==0)
                {
                  strcpy(Stk[Tmp],"acosl");
                  break;
                }
              if(str_cmp(Keyword,"acosh")==0)
                {
                  strcpy(Stk[Tmp],"acosh");
                  break;
                }
              if(str_cmp(Keyword,"appexename$")==0)
                {
                  strcpy(Stk[Tmp],"AppExeName$()");
                  Use_AppExeName=Use_BcxSplitPath=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"appexepath$")==0)
                {
                  strcpy(Stk[Tmp],"AppExePath$()");
                  if(str_cmp(Stk[Tmp+1],"(")==0 &&  str_cmp(Stk[Tmp+2],")")==0)
                    {
                      *Stk[Tmp+1]=0;
                      *Stk[Tmp+2]=0;
                    }
                  Use_AppExePath=Use_BcxSplitPath=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"ansitowide")==0)
                {
                  strcpy(Stk[Tmp],"AnsiToWide");
                  Use_AnsiToWide=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"argc")==0)
                {
                  strcpy(Stk[Tmp],"argc");
                  break;
                }
              if(str_cmp(Keyword,"argv")==0)
                {
                  strcpy(Stk[Tmp],"argv");
                  break;
                }
              if(str_cmp(Keyword,"argv$")==0)
                {
                  strcpy(Stk[Tmp],"argv$");
                  break;
                }
              if(str_cmp(Keyword,"asc")==0)
                {
                  i=0;
                  j=GetNumArgs(Tmp+2, &i);
                  if(*Stk[Tmp+2]==*DQ)
                    {
                      if(j>0||*Stk[Tmp+3]!=41)
                        {
                          strcpy(Stk[Tmp],"asc");
                          Use_Asc=TRUE;
                        }
                      else
                        {
                          if(str_cmp(Stk[Tmp+2],DDQ)==0)
                            {
                              strcpy(Stk[Tmp],"0");
                            }
                          else
                            {
                              strcpy(Stk[Tmp],ltrim(str((UCHAR)*(Stk[Tmp+2]+1))));
                            }
                          *Stk[Tmp+1]=0;
                          *Stk[Tmp+2]=0;
                          *Stk[Tmp+3]=0;
                        }
                    }
                  else
                    {
                      if(j>0)
                        {
                          strcpy(Stk[i],"+");
                        }
                      strcpy(Stk[Tmp],"(UCHAR)*");
                    }
                  break;
                }
              if(str_cmp(Keyword,"asin")==0)
                {
                  strcpy(Stk[Tmp],"asin");
                  break;
                }
              if(str_cmp(Keyword,"asinl")==0)
                {
                  strcpy(Stk[Tmp],"asinl");
                  break;
                }
              if(str_cmp(Keyword,"asinh")==0)
                {
                  strcpy(Stk[Tmp],"asinh");
                  break;
                }
              if(str_cmp(Keyword,"atanh")==0)
                {
                  strcpy(Stk[Tmp],"atanh");
                  break;
                }
              if(str_cmp(Keyword,"atn")==0 ||  str_cmp(Keyword,"atan")==0)
                {
                  strcpy(Stk[Tmp],"atan");
                  break;
                }
              if(str_cmp(Keyword,"atnl")==0 ||  str_cmp(Keyword,"atanl")==0)
                {
                  strcpy(Stk[Tmp],"atanl");
                  break;
                }
              if(str_cmp(Keyword,"auto")==0)
                {
                  if(iMatchWrd(Stk[Tmp+1],"local"))
                    {
                      strcpy(Stk[Tmp],"dim");
                      strcpy(Stk[Tmp+1],"raw");
                    }
                  else
                    {
                      strcpy(Stk[Tmp],"auto");
                    }
                }
              break;
            }
            break;
          }
        if(a==2)
          {
            for(;;)
            {
              if(str_cmp(Keyword,"bcopy")==0)
                {
                  *Stk[1]=0;
                  for(i=Tmp+1; i<=Ndx; i+=1)
                    {
                      if(iMatchWrd(Stk[i],"to"))
                        {
                          break;
                        }
                      strcat(Stk[1],Stk[i]);
                    }
                  *Stk[2]=0;
                  for(i=i+1; i<=Ndx; i+=1)
                    {
                      strcat(Stk[2],Stk[i]);
                    }
                  strcpy(Src, join(7,"memmove(&",Stk[2],",&",Stk[1],",sizeof(",Stk[2],"))"));
                  strcpy(Src,RemoveStr(Src,"&*"));
                  Ndx=0;
                  XParse(Src);
                  break;
                }
              if(str_cmp(Keyword,"bel$")==0)
                {
                  strcpy(Stk[Tmp],"BEL$");
                  Use_BEL=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"bs$")==0)
                {
                  strcpy(Stk[Tmp],"BS$");
                  Use_BS=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"bool")==0 ||  str_cmp(Keyword,"boolean")==0)
                {
                  strcpy(Stk[Tmp],"bool");
                  break;
                }
              if(str_cmp(Keyword,"band")==0)
                {
                  strcpy(Stk[Tmp]," BAND ");
                  Use_Band=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"bnot")==0)
                {
                  strcpy(Stk[Tmp]," BNOT ");
                  Use_Bnot=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"bcx_font")==0)
                {
                  strcpy(Stk[Tmp],ucase(Stk[Tmp]));
                  char tmp[2048];
                  strcpy(tmp,Clean(ucase(Stk[Tmp+1])));
                  for(;;)
                  {
                    if(str_cmp(tmp,".NAME")==0)
                      {
                        strcpy(Stk[Tmp+1],".lf.lfFaceName$");
                        break;
                      }
                    if(str_cmp(tmp,".BOLD")==0)
                      {
                        strcpy(Stk[Tmp+1],".lf.lfWeight");
                        break;
                      }
                    if(str_cmp(tmp,".UNDERLINE")==0)
                      {
                        strcpy(Stk[Tmp+1],".lf.lfUnderline");
                        break;
                      }
                    if(str_cmp(tmp,".STRIKEOUT")==0)
                      {
                        strcpy(Stk[Tmp+1],".lf.lfStrikeOut");
                        break;
                      }
                    if(str_cmp(tmp,".ITALIC")==0)
                      {
                        strcpy(Stk[Tmp+1],".lf.lfItalic");
                        break;
                      }
                    if(str_cmp(tmp,".CHARSET")==0)
                      {
                        strcpy(Stk[Tmp+1],".lf.lfCharSet");
                        break;
                      }
                    if(str_cmp(tmp,".SIZE")==0 ||  str_cmp(tmp,".RGB")==0)
                      {
                        strcpy(Stk[Tmp+1],tmp);
                        break;
                      }
                      // case else
                      {
                        strcpy(Stk[Tmp+1],Clean(Stk[Tmp+1]));
                      }
                    break;
                  }
                  break;
                }
              if(str_cmp(Keyword,"bcxsplitpath$")==0)
                {
                  strcpy(Stk[Tmp],"$$BcxSplitPath$");
                  Use_BcxSplitPath=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"bcxpath$")==0)
                {
                  UseFlag=TRUE;
                  strcpy(Stk[Tmp],"BcxPath$()");
                  if(str_cmp(Stk[Tmp+1],"(")==0 &&  str_cmp(Stk[Tmp+2],")")==0)
                    {
                      *Stk[Tmp+1]=0;
                      *Stk[Tmp+2]=0;
                    }
                  break;
                }
              if(str_cmp(Keyword,"bcxfont")==0)
                {
                  strcpy(Stk[Tmp],"BcxFont");
                  break;
                }
              if(str_cmp(Keyword,"bcxsocket")==0)
                {
                  strcpy(Stk[Tmp],"BcxSocket");
                  Use_Socket=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"bcxsocketsend")==0)
                {
                  strcpy(Stk[Tmp],"BcxSocketSend");
                  break;
                }
              if(str_cmp(Keyword,"bcxsocketread")==0)
                {
                  strcpy(Stk[Tmp],"BcxSocketRead");
                  break;
                }
              if(str_cmp(Keyword,"bcxsocketclose")==0)
                {
                  strcpy(Stk[Tmp],"BcxSocketClose");
                  break;
                }
              if(str_cmp(Keyword,"bcx_thread")==0 ||  str_cmp(Keyword,"bcx_threadwait")==0 ||  str_cmp(Keyword,"bcx_threadsuspend")==0 ||  str_cmp(Keyword,"bcx_threadresume")==0 ||  str_cmp(Keyword,"bcx_threadkill")==0 ||  str_cmp(Keyword,"bcx_threadend")==0)
                {
                  strcpy(Stk[Tmp],ucase(Stk[Tmp]));
                  Use_Threads=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"bin$")==0)
                {
                  strcpy(Stk[Tmp],"$$Bin$");
                  Use_Bin=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"bool$")==0)
                {
                  strcpy(Stk[Tmp],"$$BoolStr$");
                  Use_Boolstr=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"bin2dec")==0)
                {
                  strcpy(Stk[Tmp],"Bin2Dec");
                  Use_Bin2dec=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"boolean")==0)
                {
                  strcpy(Stk[Tmp],"BOOLEAN");
                  break;
                }
              if(str_cmp(Keyword,"bor")==0)
                {
                  strcpy(Stk[Tmp]," BOR ");
                  Use_Bor=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"byte")==0)
                {
                  strcpy(Stk[Tmp],"BYTE");
                }
              break;
            }
            break;
          }
        if(a==3)
          {
            for(;;)
            {
              if(str_cmp(Keyword,"containedin")==0)
                {
                  strcpy(Stk[Tmp],"containedin");
                  Use_ContainedIn=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"copyfile")==0)
                {
                  Use_CopyFile=TRUE;
                  Use_Exist=Use_Lof=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"cr$")==0)
                {
                  strcpy(Stk[Tmp],"CR$");
                  Use_CR=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"close#")==0)
                {
                  strcpy(Stk[Tmp],"close");
                  break;
                }
              if(str_cmp(Keyword,"close")==0)
                {
                  if(str_cmp(left(Stk[Tmp+1],1),"#")==0)
                    {
                      strcpy(Stk[Tmp+1],mid(Stk[Tmp+1],2));
                    }
                  break;
                }
              if(str_cmp(Keyword,"cvd")==0)
                {
                  strcpy(Stk[Tmp],"CVD");
                  Use_Cvd=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"cvi")==0)
                {
                  strcpy(Stk[Tmp],"CVI");
                  Use_Cvi=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"cvl")==0)
                {
                  strcpy(Stk[Tmp],"CVL");
                  Use_Cvl=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"cvld")==0)
                {
                  strcpy(Stk[Tmp],"CVLD");
                  Use_Cvld=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"cvs")==0)
                {
                  strcpy(Stk[Tmp],"CVS");
                  Use_Cvs=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"concat")==0)
                {
                  strcpy(Stk[Tmp],"strcat");
                  break;
                }
              if(str_cmp(Keyword,"chr$")==0)
                {
                  strcpy(Stk[Tmp],"$$chr$");
                  Use_Chr=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"char")==0)
                {
                  strcpy(Stk[Tmp],"char");
                  break;
                }
              if(str_cmp(Keyword,"crlf$")==0)
                {
                  strcpy(Stk[Tmp],"CRLF$");
                  Use_Crlf=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"cbctl")==0)
                {
                  strcpy(Stk[Tmp],"LOWORD(wParam)");
                  break;
                }
              if(str_cmp(Keyword,"cbctlmsg")==0)
                {
                  strcpy(Stk[Tmp],"HIWORD(wParam)");
                  break;
                }
              if(str_cmp(Keyword,"cblparam")==0)
                {
                  strcpy(Stk[Tmp],"lParam");
                  break;
                }
              if(str_cmp(Keyword,"cbmsg")==0)
                {
                  strcpy(Stk[Tmp],"Msg");
                  break;
                }
              if(str_cmp(Keyword,"cbwparam")==0)
                {
                  strcpy(Stk[Tmp],"wParam");
                  break;
                }
              if(str_cmp(Keyword,"cdbl")==0)
                {
                  strcpy(Stk[Tmp],"CDBL");
                  Use_Cdbl=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"chdrive")==0 ||  str_cmp(Keyword,"chdir")==0)
                {
                  strcpy(Stk[Tmp],"chdir");
                  break;
                }
              if(str_cmp(Keyword,"cint")==0)
                {
                  strcpy(Stk[Tmp],"Cint");
                  Use_Cint=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"cldbl")==0)
                {
                  strcpy(Stk[Tmp],"CLDBL");
                  Use_Cldbl=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"clng")==0)
                {
                  strcpy(Stk[Tmp],"CLNG");
                  Use_Clng=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"cls")==0)
                {
                  strcpy(Stk[Tmp],"cls");
                  Use_Cls=Use_ESC=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"color")==0 ||  str_cmp(Keyword,"color_fg")==0 ||  str_cmp(Keyword,"color_bg")==0)
                {
                  strcpy(Stk[Tmp],lcase(Stk[Tmp]));
                  Use_Color=Use_Console=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"command$")==0)
                {
                  Use_Command=Use_SPC=UseFlag=TRUE;
                  strcpy(Stk[Tmp],"command$(-1)");
                  if(str_cmp(Stk[Tmp+1],"(")==0)
                    {
                      strcpy(Stk[Tmp],"command$");
                    }
                  break;
                }
              if(str_cmp(Keyword,"colorref")==0)
                {
                  strcpy(Stk[Tmp],"COLORREF");
                  break;
                }
              if(str_cmp(Keyword,"cos")==0)
                {
                  strcpy(Stk[Tmp],"cos");
                  break;
                }
              if(str_cmp(Keyword,"cosl")==0)
                {
                  strcpy(Stk[Tmp],"cosl");
                  break;
                }
              if(str_cmp(Keyword,"cosh")==0)
                {
                  strcpy(Stk[Tmp],"cosh");
                  break;
                }
              if(str_cmp(Keyword,"cbool")==0)
                {
                  strcpy(Stk[Tmp],"CBOOL");
                  static   struct _functionParse  fp;
                  memset(&fp,0,sizeof(fp));
                  static int     i;
                  memset(&i,0,sizeof(i));
                  static int     t;
                  memset(&t,0,sizeof(t));
                  static int     expos=0;
                  memset(&expos,0,sizeof(expos));
                  if(SepFuncArgs(Tmp+1, &fp,TRUE)==0)
                    {
                      Abort("No argument specified in CBOOL");
                    }
                  for(i=fp.CommaPos[0]; i<=fp.CommaPos[1]; i+=1)
                    {
                      t=inchr("!<>=",Stk[i]);
                      if(t)
                        {
                          if(t<4)
                            {
                              if(str_cmp(Stk[i+1],"=")==0)
                                {
                                  strcpy(Stk[i], join(2,Stk[i],Stk[i+1]));
                                  *Stk[i+1]=0;
                                }
                              else if(t==1&&str_cmp(Stk[i],"!=")!=0)
                                {
                                  continue;
                                }
                            }
                          else
                            {
                              if(str_cmp(Stk[i+1],"=")!=0)
                                {
                                  strcpy(Stk[i],"==");
                                }
                            }
                          expos=i;
                          break;
                        }
                    }
                  t=DataType(Stk[expos-1]);
                  if(t==vt_STRLIT||t==vt_STRVAR)
                    {
                      if(expos)
                        {
                          strcpy(Stk[Tmp+1], join(2,Stk[Tmp+1],"strcmp("));
                          strcpy(Stk[fp.CommaPos[1]], join(3,")",Stk[expos],"0)"));
                          strcpy(Stk[expos],",");
                          *Src=0;
                          for(i=1; i<=Ndx; i+=1)
                            {
                              strcpy(Src, join(3,Src,Stk[i],SPC));
                            }
                          FastLexer(Src," ","(),");
                        }
                    }
                  break;
                }
              if(str_cmp(Keyword,"csng")==0)
                {
                  strcpy(Stk[Tmp],"CSNG");
                  Use_Csng=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"curdir$")==0)
                {
                  strcpy(Stk[Tmp],"curdir$()");
                  if(str_cmp(Stk[Tmp+1],"(")==0 &&  str_cmp(Stk[Tmp+2],")")==0)
                    {
                      *Stk[Tmp+1]=0;
                      *Stk[Tmp+2]=0;
                    }
                  Use_Curdir=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"currency")==0)
                {
                  strcpy(Stk[Tmp],"CURRENCY");
                  break;
                }
              if(str_cmp(Keyword,"c_declare")==0)
                {
                  strcpy(CallType,"__attribute__((cdecl)) ");
                  strcpy(Stk[Tmp],"declare");
                  if(iMatchWrd(Stk[4],"lib"))
                    {
                      NoTypeDeclare=FALSE;
                    }
                  else
                    {
                      NoTypeDeclare=TRUE;
                    }
                }
              break;
            }
            break;
          }
        if(a==4)
          {
            for(;;)
            {
              if(str_cmp(Keyword,"declare")==0)
                {
                  strcpy(CallType,"__attribute__((stdcall)) ");
                  strcpy(Stk[Tmp],"declare");
                  if(!iMatchWrd(Stk[4],"lib"))
                    {
                      NoTypeDeclare=TRUE;
                    }
                  else
                    {
                      NoTypeDeclare=FALSE;
                    }
                  break;
                }
              if(str_cmp(Keyword,"dq$")==0)
                {
                  strcpy(Stk[Tmp],"DQ$");
                  Use_DQ=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"ddq$")==0)
                {
                  strcpy(Stk[Tmp],"DDQ$");
                  Use_DDQ=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"data$")==0)
                {
                  strcpy(Stk[Tmp],"DATA$");
                  break;
                }
              if(str_cmp(Keyword,"date$")==0)
                {
                  strcpy(Stk[Tmp],"$$timef$(12)");
                  Use_Time=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"delete")==0)
                {
                  if(UseCpp==FALSE)
                    {
                      Abort("'DELETE' can only be used with C++");
                    }
                  strcpy(Stk[Tmp],"delete ");
                  break;
                }
              if(str_cmp(Keyword,"del$")==0)
                {
                  strcpy(Stk[Tmp],"del$");
                  Use_Del=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"double")==0)
                {
                  strcpy(Stk[Tmp],"double");
                  break;
                }
              if(str_cmp(Keyword,"download")==0)
                {
                  strcpy(Stk[Tmp],"Download");
                  Use_Download=Use_Dynacall=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"dsplit")==0)
                {
                  strcpy(Stk[Tmp],"DSplit");
                  Use_DSplit=TRUE;
                  Use_Remove=TRUE;
                  Use_StrStr=TRUE;
                  Use_Mid=TRUE;
                  Use_Left=TRUE;
                  Use_Instr=TRUE;
                  Use_Stristr=TRUE;
                  UseLCaseTbl=TRUE;
                  UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"dword")==0)
                {
                  strcpy(Stk[Tmp],"DWORD");
                }
              break;
            }
            break;
          }
        if(a==5)
          {
            for(;;)
            {
              if(str_cmp(Keyword,"extern")==0)
                {
                  strcpy(Stk[Tmp],"extern");
                  break;
                }
              if(str_cmp(Keyword,"enc$")==0)
                {
                  strcpy(Stk[Tmp],"$$enc$");
                  Use_Enclose=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"extract$")==0)
                {
                  strcpy(Stk[Tmp],"$$extract$");
                  Use_Extract=Use_StrStr=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"eof$")==0)
                {
                  strcpy(Stk[Tmp],"EF$");
                  Use_EOF=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"eof")==0)
                {
                  strcpy(Stk[Tmp],"EoF");
                  Use_Eof=UseFlag=TRUE;
                  if(DataType(Stk[Tmp+2])==vt_NUMBER)
                    {
                      strcpy(Stk[Tmp+2], join(2,"FP",Stk[Tmp+2]));
                    }
                  break;
                }
              if(str_cmp(Keyword,"esc$")==0)
                {
                  strcpy(Stk[Tmp],"ESC$");
                  Use_ESC=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"enum")==0)
                {
                  if(Ndx==1||iMatchWrd(Stk[3],"enum"))
                    {
                      Use_EnumFile=TRUE;
                      int     EnumFlag=FALSE;
                      fprintf(FP11,"%s\n","");
                      if(Ndx==1)
                        {
                          fprintf(FP11,"%s\n","enum");
                        }
                      else
                        {
                          fprintf(FP11,"%s%s\n","enum ",Stk[1]);
                        }
                      fprintf(FP11,"%s\n","  {");
                      *Src=0;
                      while(!iMatchLft(Src,"end "))
                        {
                          if(EoF(SourceFile))
                            {
                              Abort("Unbalanced ENUM");
                            }
                          Src[0]=0;
                          AR_fgets_retval=fgets(Src,65535,SourceFile);
                          if(Src[strlen(Src)-1]==10)Src[strlen(Src)-1]=0;
                          ModuleLineNos[ModuleNdx]++;
                          StripCode(Src);
                          if(iMatchLft(Src,"$comme"))
                            {
                              Directives();
                              continue;
                            }
                          strcpy(Src,trim(Src));
                          if(Src[0]==0)
                            {
                              continue;
                            }
                          if(str_cmp(lcase(left(join(2,Src," "),4)),"end ")==0)
                            {
                              break;
                            }
                          else
                            {
                              if(EnumFlag==FALSE)
                                {
                                  EnumFlag=TRUE;
                                }
                              else
                                {
                                  fprintf(FP11,"%s\n",",");
                                }
                            }
                          fprintf(FP11,"%s%s","    ",rtrim(Src));
                        }
                      *Src=0;
                      Ndx=0;
                      fprintf(FP11,"%s\n","");
                      fprintf(FP11,"%s\n","  };\n");
                      return;
                    }
                  strcpy(Stk[1],"enum {");
                  for(j=2; j<=Ndx; j+=1)
                    {
                      strcat(Stk[1],Stk[j]);
                    }
                  strcat(Stk[1],"}");
                  Ndx=1;
                  break;
                }
              if(str_cmp(Keyword,"environ$")==0)
                {
                  strcpy(Stk[Tmp],"Environ$");
                  Use_Environ=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"exist")==0)
                {
                  strcpy(Stk[Tmp],"Exist");
                  Use_Exist=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"exp")==0)
                {
                  strcpy(Stk[Tmp],"Exp");
                  Use_Exp=TRUE;
                }
              break;
            }
            break;
          }
        if(a==6)
          {
            for(;;)
            {
              if(str_cmp(Keyword,"freeglobals")==0)
                {
                  strcpy(Stk[Tmp],"FreeGlobals");
                  break;
                }
              if(str_cmp(Keyword,"ff$")==0)
                {
                  strcpy(Stk[Tmp],"FF$");
                  Use_FF=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"function")==0)
                {
                  if(str_cmp(Stk[Tmp+1],"=")==0)
                    {
                      if(str_cmp(Stk[Tmp+2],DDQ)==0)
                        {
                          strcpy(Stk[Tmp+2],"NUL$");
                        }
                      strcpy(Stk[Tmp],"functionreturn");
                    }
                  break;
                }
              if(str_cmp(Keyword,"false")==0)
                {
                  strcpy(Stk[Tmp],"FALSE");
                  break;
                }
              if(str_cmp(Keyword,"file")==0)
                {
                  strcpy(Stk[Tmp],"FILE");
                  break;
                }
              if(str_cmp(Keyword,"findintype")==0)
                {
                  strcpy(Stk[Tmp],"FindInType");
                  Use_FindInType=TRUE;
                  char StMem[2048];
                  char StName[2048];
                  char VarName[2048];
                  static   struct _functionParse  fp;
                  memset(&fp,0,sizeof(fp));
                  SepFuncArgs(Tmp, &fp,TRUE);
                  strcpy(StMem,remain(Clean(GetArg(2, &fp)),"."));
                  strcpy(VarName,extract(Clean(GetArg(2, &fp)),"."));
                  for(j=fp.CommaPos[1]+1; j<=fp.CommaPos[2]-1; j+=1)
                    {
                      *Stk[j]=0;
                    }
                  if(CheckLocal(VarName, &i)!=vt_UNKNOWN)
                    {
                      strcpy(StName,TypeDefs[LocalVars[i].VarDef].VarName);
                    }
                  else if(CheckGlobal(VarName, &i)!=vt_UNKNOWN)
                    {
                      strcpy(StName,TypeDefs[GlobalVars[i].VarDef].VarName);
                    }
                  j=fp.CommaPos[1]+1;
                  strcpy(Stk[j], join(9,"(char*)",VarName," + offsetof(",StName,",",StMem,"), sizeof(",StName,")"));
                  break;
                }
              if(str_cmp(Keyword,"farproc")==0)
                {
                  strcpy(Stk[Tmp],"FARPROC");
                  break;
                }
              if(str_cmp(Keyword,"fillarray")==0)
                {
                  strcpy(Stk[Tmp],"fillarray");
                  Use_FillArray=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"findfirst$")==0)
                {
                  strcpy(Stk[Tmp],"findfirst$");
                  j=GetNumArgs(Tmp+2);
                  if(j==0)
                    {
                      strcpy(Stk[Ndx],", &FindData)");
                    }
                  Use_Findfirst=Use_Like=TRUE;
                  Use_BcxSplitPath=TRUE;
                  Use_Join=TRUE;
                  UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"findnext$")==0)
                {
                  strcpy(Stk[Tmp],"findnext$");
                  if(str_cmp(Stk[Tmp+1],"(")==0 &&  str_cmp(Stk[Tmp+2],")")==0)
                    {
                      strcpy(Stk[Tmp+1],"(&FindData");
                    }
                  else if(Tmp==Ndx)
                    {
                      Ndx++;
                      strcpy(Stk[Ndx],"(&FindData)");
                    }
                  Use_Findnext=Use_Like=UseFlag=TRUE;
                  Use_Join=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"fint")==0)
                {
                  strcpy(Stk[Tmp],"FINT");
                  Use_Fint=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"fix")==0)
                {
                  strcpy(Stk[Tmp],"FIX");
                  Use_Fix=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"filelocked")==0)
                {
                  strcpy(Stk[Tmp],"FileLocked");
                  Use_FileLocked=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"flush")==0)
                {
                  strcpy(Stk[Tmp],"fflush");
                  break;
                }
              if(str_cmp(Keyword,"frac")==0)
                {
                  strcpy(Stk[Tmp],"FRAC");
                  Use_Frac=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"fracl")==0)
                {
                  strcpy(Stk[Tmp],"FRACL");
                  Use_Fracl=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"freefile")==0)
                {
                  strcpy(Stk[Tmp],"FreeFile()");
                  Use_Freefile=TRUE;
                }
              break;
            }
            break;
          }
        if(a==7)
          {
            for(;;)
            {
              if(str_cmp(Keyword,"getprocaddress")==0)
                {
                  static char GlobalName[2048];
                  memset(&GlobalName,0,sizeof(GlobalName));
                  static int     s;
                  memset(&s,0,sizeof(s));
                  static int     ss;
                  memset(&ss,0,sizeof(ss));
                  static char tempA[2048];
                  memset(&tempA,0,sizeof(tempA));
                  strcpy(GlobalName,Stk[Tmp-2]);
                  ss=HashNumber(GlobalName);
                  while(GlobalVarHash[ss])
                    {
                      s=GlobalVarHash[ss];
                      if(str_cmp(GlobalName,GlobalVars[s].VarName)==0)
                        {
                          strcpy(tempA,TypeDefs[GlobalVars[s].VarDef].VarName);
                          if(GlobalVars[s].VarPntr)
                            {
                              strcat(tempA," *");
                            }
                        }
                      ss=imod(ss+1,MaxGlobalVars);
                    }
                  if(tempA[0]==0)
                    {
                      static char LocalName[2048];
                      memset(&LocalName,0,sizeof(LocalName));
                      strcpy(LocalName,Stk[Tmp-2]);
                      if(LocalVarCnt)
                        {
                            {int i;
                          for(i=1; i<=LocalVarCnt; i+=1)
                            {
                              if(str_cmp(LocalName,LocalVars[i].VarName)==0)
                                {
                                  strcpy(tempA,TypeDefs[LocalVars[i].VarDef].VarName);
                                  if(LocalVars[i].VarPntr)
                                    {
                                      strcat(tempA," *");
                                    }
                                  break;
                                }
                            }
                            }
                        }
                    }
                  if(tempA[0]!=0)
                    {
                      strcpy(Stk[Tmp], join(3,"(",tempA,")dlsym"));
                    }
                  else
                    {
                      strcpy(Stk[Tmp],"dlsym");
                    }
                  break;
                }
              if(str_cmp(Keyword,"getattr")==0)
                {
                  strcpy(Stk[Tmp],"GETATTR");
                  break;
                }
              if(str_cmp(Keyword,"getbvalue")==0)
                {
                  strcpy(Stk[Tmp],"GetBValue");
                  break;
                }
              if(str_cmp(Keyword,"getc")==0)
                {
                  strcpy(Stk[Tmp],"getc");
                  break;
                }
              if(str_cmp(Keyword,"getgvalue")==0)
                {
                  strcpy(Stk[Tmp],"GetGValue");
                  break;
                }
              if(str_cmp(Keyword,"getrvalue")==0)
                {
                  strcpy(Stk[Tmp],"GetRValue");
                  break;
                }
              if(str_cmp(Keyword,"getresource")==0)
                {
                  strcpy(Stk[Tmp],"GetResource");
                  Use_Embed=TRUE;
                }
              break;
            }
            break;
          }
        if(a==8)
          {
            for(;;)
            {
              if(str_cmp(Keyword,"hiword")==0)
                {
                  strcpy(Stk[Tmp],"HIWORD");
                  break;
                }
              if(str_cmp(Keyword,"hex$")==0)
                {
                  strcpy(Stk[Tmp],"hex$");
                  Use_Hex=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"hex2dec")==0)
                {
                  strcpy(Stk[Tmp],"Hex2Dec");
                  Use_Hex2Dec=UseLCaseTbl=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"hibyte")==0)
                {
                  strcpy(Stk[Tmp],"HIBYTE");
                  break;
                }
              if(str_cmp(Keyword,"hide")==0)
                {
                  strcpy(Stk[Tmp],"Hide");
                  break;
                }
              if(str_cmp(Keyword,"hypot")==0)
                {
                  strcpy(Stk[Tmp],"hypot");
                }
              break;
            }
            break;
          }
        if(a==9)
          {
            for(;;)
            {
              if(str_cmp(Keyword,"inherits")==0)
                {
                  strcpy(Stk[Tmp],"inherits");
                  break;
                }
              if(str_cmp(Keyword,"instr")==0)
                {
                  strcpy(Stk[Tmp],"instr_b");
                  Use_Instr=Use_StrStr=TRUE;
                  Use_Stristr=UseLCaseTbl=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"inchr")==0)
                {
                  strcpy(Stk[Tmp],"inchr");
                  Use_Inchr=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"imod")==0)
                {
                  strcpy(Stk[Tmp],"imod");
                  Use_Imod=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"iif")==0)
                {
                  strcpy(Stk[Tmp],"iif");
                  Use_Iif=TRUE;
                  for(i=Tmp+1; i<=Ndx; i+=1)
                    {
                      if(str_cmp(Stk[i],"=")==0)
                        {
                          if(str_cmp(Stk[i-1],"<")!=0 &&  str_cmp(Stk[i-1],">")!=0)
                            {
                              strcpy(Stk[i],"==");
                            }
                        }
                    }
                  break;
                }
              if(str_cmp(Keyword,"iif$")==0)
                {
                  strcpy(Stk[Tmp],"sziif$");
                  Use_sziif=TRUE;
                  for(i=Tmp+1; i<=Ndx; i+=1)
                    {
                      if(str_cmp(Stk[i],"=")==0)
                        {
                          if(str_cmp(Stk[i-1],"<")!=0 &&  str_cmp(Stk[i-1],">")!=0)
                            {
                              strcpy(Stk[i],"==");
                            }
                        }
                    }
                  break;
                }
              if(str_cmp(Keyword,"inkey")==0)
                {
                  Use_InkeyD=TRUE;
                  Use_GetCh=TRUE;
                  UseFlag=TRUE;
                  strcpy(Stk[Tmp],"inkeyd()");
                  if(str_cmp(Stk[Tmp+1],"(")==0 &&  str_cmp(Stk[Tmp+2],")")==0)
                    {
                      *Stk[Tmp+1]=0;
                      *Stk[Tmp+2]=0;
                    }
                  break;
                }
              if(str_cmp(Keyword,"inkey$")==0)
                {
                  Use_Inkey=TRUE;
                  Use_GetCh=TRUE;
                  UseFlag=TRUE;
                  strcpy(Stk[Tmp],"inkey$()");
                  if(str_cmp(Stk[Tmp+1],"(")==0 &&  str_cmp(Stk[Tmp+2],")")==0)
                    {
                      *Stk[Tmp+1]=0;
                      *Stk[Tmp+2]=0;
                    }
                  break;
                }
              if(str_cmp(Keyword,"ins$")==0)
                {
                  strcpy(Stk[Tmp],"ins$");
                  Use_Ins=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"instat")==0)
                {
                  Use_Instat=TRUE;
                  strcpy(Stk[Tmp],"kbhit()");
                  break;
                }
              if(str_cmp(Keyword,"instrrev")==0)
                {
                  strcpy(Stk[Tmp],"InstrRev");
                  Use_Instrrev=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"isptr")==0)
                {
                  strcpy(Stk[Tmp],"IsPtr");
                  Use_Isptr=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"ireplace$")==0)
                {
                  strcpy(Stk[Tmp],"iReplace$");
                  Use_iReplace=Use_Stristr=UseFlag=TRUE;
                  UseLCaseTbl=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"iremove$")==0)
                {
                  strcpy(Stk[Tmp],"IRemoveStr$");
                  Use_IRemove=UseFlag=TRUE;
                  Use_Stristr=UseLCaseTbl=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"iterate")==0)
                {
                  strcpy(Stk[Tmp],"continue");
                }
              break;
            }
            break;
          }
        if(a==10)
          {
            for(;;)
            {
              if(str_cmp(Keyword,"join$")==0)
                {
                  strcpy(Stk[Tmp],"$$join$");
                  Use_Join=UseFlag=TRUE;
                }
              break;
            }
            break;
          }
        if(a==11)
          {
            for(;;)
            {
              if(str_cmp(Keyword,"keypress")==0)
                {
                  strcpy(Stk[Tmp],"keypress()");
                  if(str_cmp(Stk[Tmp+1],"(")==0 &&  str_cmp(Stk[Tmp+2],")")==0)
                    {
                      *Stk[Tmp+1]=0;
                      *Stk[Tmp+2]=0;
                    }
                  Use_Keypress=TRUE;
                  Use_GetCh=TRUE;
                }
              break;
            }
            break;
          }
        if(a==12)
          {
            for(;;)
            {
              if(str_cmp(Keyword,"loadfile$")==0)
                {
                  strcpy(Stk[Tmp],"$$LoadFile$");
                  Use_LoadFile=Use_Get=UseFlag=TRUE;
                  Use_Exist=Use_Lof=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"lf$")==0)
                {
                  strcpy(Stk[Tmp],"LF$");
                  Use_LF=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"line")==0)
                {
                  if(iMatchWrd(Stk[Tmp+1],"input"))
                    {
                      Use_Lineinput=TRUE;
                      strcpy(Stk[Tmp],"lineinput");
                      j=Tmp+4;
                      *Stk[Tmp+1]=0;
                      for(i=Tmp+2; i<=Ndx; i+=1)
                        {
                          if(*Stk[i]==44)
                            {
                              j=i+1;
                              break;
                            }
                          strcpy(Stk[Tmp+1], join(2,Stk[Tmp+1],Stk[i]));
                          *Stk[i]=0;
                        }
                      for(i=j; i<=Ndx; i+=1)
                        {
                          strcpy(Stk[Tmp+2], join(2,Stk[Tmp+2],Stk[i]));
                        }
                    }
                  break;
                }
              if(str_cmp(Keyword,"lcase$")==0)
                {
                  strcpy(Stk[Tmp],"$$lcase$");
                  Use_Lcase=TRUE;
                  Use_StrUpLow=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"ldouble")==0)
                {
                  strcpy(Stk[Tmp],"LDOUBLE");
                  Use_Ldouble=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"left$")==0)
                {
                  strcpy(Stk[Tmp],"$$left$");
                  Use_Left=TRUE;
                  UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"long")==0)
                {
                  strcpy(Stk[Tmp],"long");
                  break;
                }
              if(str_cmp(Keyword,"longlong")==0)
                {
                  strcpy(Stk[Tmp],"LONGLONG");
                  break;
                }
              if(str_cmp(Keyword,"lpbyte")==0)
                {
                  strcpy(Stk[Tmp],"LPBYTE");
                  break;
                }
              if(str_cmp(Keyword,"len")==0)
                {
                  strcpy(Stk[Tmp],"strlen");
                  break;
                }
              if(str_cmp(Keyword,"lprint")==0)
                {
                  strcpy(Stk[Tmp],"lprint");
                  if(Tmp==Ndx)
                    {
                      Ndx++;
                      strcpy(Stk[Ndx],enc(""));
                    }
                  break;
                }
              if(str_cmp(Keyword,"lpad$")==0)
                {
                  strcpy(Stk[Tmp],"$$lpad$");
                  Use_Lpad=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"ltrim$")==0)
                {
                  strcpy(Stk[Tmp],"$$ltrim$");
                  Use_Ltrim=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"lof")==0)
                {
                  strcpy(Stk[Tmp],"lof");
                  if(DataType(Stk[Tmp+2])==vt_NUMBER)
                    {
                      strcpy(Stk[Tmp+2], join(2,"FP",Stk[Tmp+2]));
                    }
                  Use_Lof=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"loadlibrary")==0 ||  str_cmp(Keyword,"load_dll")==0)
                {
                  strcpy(Stk[Tmp],"LoadLibrary");
                  break;
                }
              if(str_cmp(Keyword,"like")==0)
                {
                  strcpy(Stk[Tmp],"like");
                  Use_Like=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"lobyte")==0)
                {
                  strcpy(Stk[Tmp],"LOBYTE");
                  break;
                }
              if(str_cmp(Keyword,"loc")==0)
                {
                  if(DataType(Stk[Tmp+2])==vt_NUMBER)
                    {
                      strcpy(Stk[Tmp+2], join(2,"FP",Stk[Tmp+2]));
                    }
                  strcpy(Stk[Tmp], join(5,"loc(",Stk[Tmp+2],",",Stk[Tmp+2],"len)"));
                  *Stk[Tmp+1]=0;
                  *Stk[Tmp+2]=0;
                  *Stk[Tmp+3]=0;
                  Use_Loc=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"locate")==0)
                {
                  Use_Locate=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"log")==0)
                {
                  strcpy(Stk[Tmp],"log");
                  break;
                }
              if(str_cmp(Keyword,"logl")==0)
                {
                  strcpy(Stk[Tmp],"logl");
                  break;
                }
              if(str_cmp(Keyword,"log10")==0)
                {
                  strcpy(Stk[Tmp],"log10");
                  break;
                }
              if(str_cmp(Keyword,"log10l")==0)
                {
                  strcpy(Stk[Tmp],"log10l");
                  break;
                }
              if(str_cmp(Keyword,"loword")==0)
                {
                  strcpy(Stk[Tmp],"LOWORD");
                  break;
                }
              if(str_cmp(Keyword,"lpstr")==0)
                {
                  strcpy(Stk[Tmp],"PCHAR");
                }
              break;
            }
            break;
          }
        if(a==13)
          {
            for(;;)
            {
              if(str_cmp(Keyword,"mkd$")==0)
                {
                  if(Tmp>2)
                    {
                      if(inchr(Stk[Tmp-2],"$")&&*Stk[Tmp-1]==61)
                        {
                          strcpy(Stk[1], join(2,"memcpy(",Stk[1]));
                          strcpy(Stk[Tmp-1],",");
                          strcpy(Stk[++Ndx],",9)");
                        }
                    }
                  strcpy(Stk[Tmp],"MKD");
                  Use_Mkd=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"mki$")==0)
                {
                  if(Tmp>2)
                    {
                      if(inchr(Stk[Tmp-2],"$")&&*Stk[Tmp-1]==61)
                        {
                          strcpy(Stk[1], join(2,"memcpy(",Stk[1]));
                          strcpy(Stk[Tmp-1],",");
                          strcpy(Stk[++Ndx],",3)");
                        }
                    }
                  strcpy(Stk[Tmp],"MKI");
                  Use_Mki=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"mkl$")==0)
                {
                  if(Tmp>2)
                    {
                      if(inchr(Stk[Tmp-2],"$")&&*Stk[Tmp-1]==61)
                        {
                          strcpy(Stk[1], join(2,"memcpy(",Stk[1]));
                          strcpy(Stk[Tmp-1],",");
                          strcpy(Stk[++Ndx],",5)");
                        }
                    }
                  strcpy(Stk[Tmp],"MKL");
                  Use_Mkl=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"mkld$")==0)
                {
                  if(Tmp>2)
                    {
                      if(inchr(Stk[Tmp-2],"$")&&*Stk[Tmp-1]==61)
                        {
                          strcpy(Stk[1], join(2,"memcpy(",Stk[1]));
                          strcpy(Stk[Tmp-1],",");
                          strcpy(Stk[++Ndx],",11)");
                        }
                    }
                  strcpy(Stk[Tmp],"MKLD");
                  Use_Mkld=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"mks$")==0)
                {
                  if(Tmp>2)
                    {
                      if(inchr(Stk[Tmp-2],"$")&&*Stk[Tmp-1]==61)
                        {
                          strcpy(Stk[1], join(2,"memcpy(",Stk[1]));
                          strcpy(Stk[Tmp-1],",");
                          strcpy(Stk[++Ndx],",5)");
                        }
                    }
                  strcpy(Stk[Tmp],"MKS");
                  Use_Mks=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"mid$")==0)
                {
                  if(Tmp>1)
                    {
                      strcpy(Stk[Tmp],"$$mid$");
                      Use_Mid=UseFlag=TRUE;
                    }
                  else
                    {
                      strcpy(Stk[Tmp],"midstr");
                      Use_Midstr=UseFlag=TRUE;
                    }
                  break;
                }
              if(str_cmp(Keyword,"min")==0)
                {
                  strcpy(Stk[Tmp],"_MIN_");
                  Use_Min=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"main")==0)
                {
                  strcpy(Stk[Tmp],"main");
                  break;
                }
              if(str_cmp(Keyword,"makeintresource")==0)
                {
                  strcpy(Stk[Tmp],"MAKEINTRESOURCE");
                  break;
                }
              if(str_cmp(Keyword,"makelong")==0)
                {
                  strcpy(Stk[Tmp],"MAKELONG");
                  break;
                }
              if(str_cmp(Keyword,"makeword")==0)
                {
                  strcpy(Stk[Tmp],"MAKEWORD");
                  break;
                }
              if(str_cmp(Keyword,"max")==0)
                {
                  strcpy(Stk[Tmp],"_MAX_");
                  Use_Max=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"mcase$")==0)
                {
                  strcpy(Stk[Tmp],"$$mcase$");
                  Use_Mcase=UseFlag=TRUE;
                  Use_StrUpLow=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"mkdir")==0)
                {
                  strcpy(Stk[Tmp],"mkdir");
                  break;
                }
              if(str_cmp(Keyword,"mod")==0)
                {
                  strcpy(Stk[Tmp],"fmod");
                }
              break;
            }
            break;
          }
        if(a==14)
          {
            for(;;)
            {
              if(str_cmp(Keyword,"new")==0)
                {
                  if(iMatchWrd(Stk[Tmp-1],"binary"))
                    {
                      break;
                    }
                  if(UseCpp==FALSE)
                    {
                      Abort("'NEW' can only be used with C++");
                    }
                  strcpy(Stk[Tmp],"new ");
                  break;
                }
              if(str_cmp(Keyword,"nul$")==0)
                {
                  strcpy(Stk[Tmp],"NUL$");
                  Use_NUL=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"null")==0)
                {
                  strcpy(Stk[Tmp],"NULL");
                  break;
                }
              if(str_cmp(Keyword,"now$")==0)
                {
                  strcpy(Stk[Tmp],"now$()");
                  Use_Now=UseFlag=TRUE;
                }
              break;
            }
            break;
          }
        if(a==15)
          {
            for(;;)
            {
              if(str_cmp(Keyword,"open")==0)
                {
                  for(A=Tmp+1; A<=Ndx; A+=1)
                    {
                      if(str_cmp(left(Stk[A],1),"#")==0)
                        {
                          strcpy(Stk[A],mid(Stk[A],2));
                          break;
                        }
                    }
                  break;
                }
              if(str_cmp(Keyword,"oct$")==0)
                {
                  strcpy(Stk[Tmp],"oct$");
                  Use_Oct=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"osversion")==0)
                {
                  strcpy(Stk[Tmp],"OSVersion()");
                  if(str_cmp(Stk[Tmp+1],"(")==0 &&  str_cmp(Stk[Tmp+2],")")==0)
                    {
                      *Stk[Tmp+1]=0;
                      *Stk[Tmp+2]=0;
                    }
                  Use_OSVersion=TRUE;
                }
              break;
            }
            break;
          }
        if(a==16)
          {
            for(;;)
            {
              if(str_cmp(Keyword,"pause")==0)
                {
                  strcpy(Stk[Tmp],"Pause()");
                  if(str_cmp(Stk[Tmp+1],"(")==0 &&  str_cmp(Stk[Tmp+2],")")==0)
                    {
                      *Stk[Tmp+1]=0;
                      *Stk[Tmp+2]=0;
                    }
                  Use_Pause=Use_Keypress=TRUE;
                  Use_GetCh=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"preserve")==0)
                {
                  strcpy(Stk[Tmp],"PRESERVE");
                  break;
                }
              if(str_cmp(Keyword,"print#")==0)
                {
                  strcpy(Stk[Tmp],"fprint");
                  break;
                }
              if(str_cmp(Keyword,"print")==0)
                {
                  if(str_cmp(left(Stk[Tmp+1],1),"#")==0)
                    {
                      strcpy(Stk[Tmp],"fprint");
                      strcpy(Stk[Tmp+1],mid(Stk[Tmp+1],2));
                    }
                  break;
                }
              if(str_cmp(Keyword,"ptr")==0)
                {
                  CompPtr=1;
                  strcpy(Stk[Tmp-1], join(2,Stk[Tmp-1],"*"));
                  *Stk[Tmp]=0;
                  if(Tmp==Ndx)
                    {
                      Ndx--;
                      while(tally(Stk[Ndx],"*")==strlen(Stk[Ndx]))
                        {
                          strcpy(Stk[Ndx-1], join(2,Stk[Ndx-1],Stk[Ndx]));
                          *Stk[Ndx]=0;
                          Ndx--;
                        }
                    }
                  else
                    {
                      i=Tmp-1;
                      while(tally(Stk[i],"*")==strlen(Stk[i]))
                        {
                          strcpy(Stk[i-1], join(2,Stk[i-1],Stk[i]));
                          *Stk[i]=0;
                          i--;
                        }
                    }
                  break;
                }
              if(str_cmp(Keyword,"peek$")==0)
                {
                  strcpy(Stk[Tmp],"$$peekstr$");
                  Use_PeekStr=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"poke")==0)
                {
                  strcpy(Stk[Tmp],"memmove");
                  break;
                }
              if(str_cmp(Keyword,"pow")==0)
                {
                  strcpy(Stk[Tmp],"pow");
                  break;
                }
              if(str_cmp(Keyword,"powl")==0)
                {
                  strcpy(Stk[Tmp],"powl");
                  break;
                }
              if(str_cmp(Keyword,"private")==0)
                {
                  if(UseCpp)
                    {
                      strcpy(Stk[Tmp],"private");
                    }
                  if(iMatchWrd(Stk[Tmp+1],"const"))
                    {
                      strcpy(Stk[Tmp],"enum ");
                      strcpy(Stk[Tmp+1], join(2,Stk[Tmp+2],"{"));
                      Ndx++;
                      strcpy(Stk[Ndx],"}");
                    }
                  break;
                }
              if(str_cmp(Keyword,"public")==0)
                {
                  if(UseCpp)
                    {
                      strcpy(Stk[Tmp],"public");
                    }
                }
              break;
            }
            break;
          }
        if(a==17)
          {
            for(;;)
            {
              if(str_cmp(Keyword,"qbcolor")==0)
                {
                  strcpy(Stk[Tmp],"qbcolor");
                  Use_QBColor=TRUE;
                }
              break;
            }
            break;
          }
        if(a==18)
          {
            for(;;)
            {
              if(str_cmp(Keyword,"regmatch")==0)
                {
                  strcpy(Stk[Tmp],"regmatch");
                  Use_PeekStr=Use_RegEx=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"rewind")==0)
                {
                  strcpy(Stk[Tmp],"rewind");
                  if(DataType(Stk[Tmp+2])==vt_NUMBER)
                    {
                      strcpy(Stk[Tmp+2], join(2,"FP",Stk[Tmp+2]));
                    }
                  break;
                }
              if(str_cmp(Keyword,"remove$")==0)
                {
                  strcpy(Stk[Tmp],"$$RemoveStr$");
                  Use_Remove=Use_StrStr=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"replace$")==0)
                {
                  strcpy(Stk[Tmp],"$$replace$");
                  Use_Replace=Use_StrStr=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"right$")==0)
                {
                  strcpy(Stk[Tmp],"$$right$");
                  Use_Right=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"rename")==0)
                {
                  strcpy(Stk[Tmp],"rename");
                  break;
                }
              if(str_cmp(Keyword,"register")==0)
                {
                  strcpy(Stk[Tmp],"register");
                  break;
                }
              if(str_cmp(Keyword,"randomize")==0)
                {
                  strcpy(Stk[Tmp],"randomize");
                  Use_Randomize=TRUE;
                  Use_Rnd=TRUE;
                  if(Ndx==1)
                    {
                      Use_Timer=TRUE;
                      strcpy(Stk[1],"randomize(timer())");
                    }
                  break;
                }
              if(str_cmp(Keyword,"rec")==0)
                {
                  if(DataType(Stk[Tmp+2])==vt_NUMBER)
                    {
                      strcpy(Stk[Tmp+2], join(2,"FP",Stk[Tmp+2]));
                    }
                  strcpy(Stk[Tmp], join(5,"rec(",Stk[Tmp+2],",",Stk[Tmp+2],"len)"));
                  *Stk[Tmp+1]=0;
                  *Stk[Tmp+2]=0;
                  *Stk[Tmp+3]=0;
                  Use_Rec=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"reccount")==0)
                {
                  char length[2048];
                  if(DataType(Stk[Tmp+2])==vt_NUMBER)
                    {
                      strcpy(Stk[Tmp+2], join(2,"FP",Stk[Tmp+2]));
                    }
                  strcpy(Stk[Tmp],"reccount");
                  strcpy(length, join(2,Stk[Tmp+2],"len)"));
                  for(i=Tmp+1; i<=Ndx; i+=1)
                    {
                      if(*Stk[i]==41)
                        {
                          *Stk[i]=0;
                          break;
                        }
                      strcpy(Stk[Tmp], join(2,Stk[Tmp],Stk[i]));
                      *Stk[i]=0;
                    }
                  strcpy(Stk[Tmp], join(3,Stk[Tmp],",",length));
                  Use_RecCount=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"reclen")==0)
                {
                  strcpy(Stk[Tmp],"reclen");
                  break;
                }
              if(str_cmp(Keyword,"record")==0)
                {
                  strcpy(Stk[Tmp],"record");
                  break;
                }
              if(str_cmp(Keyword,"remain$")==0)
                {
                  strcpy(Stk[Tmp],"$$remain$");
                  Use_Remain=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"retain$")==0)
                {
                  strcpy(Stk[Tmp],"$$Retain$");
                  Use_Retain=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"repeat$")==0)
                {
                  strcpy(Stk[Tmp],"$$repeat$");
                  Use_Repeat=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"reverse$")==0)
                {
                  strcpy(Stk[Tmp],"$$reverse$");
                  Use_Reverse=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"rgb")==0)
                {
                  strcpy(Stk[Tmp],"RGB");
                  break;
                }
              if(str_cmp(Keyword,"rmdir")==0)
                {
                  strcpy(Stk[Tmp],"rmdir");
                  break;
                }
              if(str_cmp(Keyword,"rnd")==0)
                {
                  strcpy(Stk[Tmp],"rnd()");
                  if(str_cmp(Stk[Tmp+1],"(")==0 &&  str_cmp(Stk[Tmp+2],")")==0)
                    {
                      *Stk[Tmp+1]=0;
                      *Stk[Tmp+2]=0;
                    }
                  Use_Rnd=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"round")==0)
                {
                  strcpy(Stk[Tmp],"Round");
                  Use_Round=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"rpad$")==0)
                {
                  strcpy(Stk[Tmp],"$$rpad$");
                  Use_Rpad=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"rtrim$")==0)
                {
                  strcpy(Stk[Tmp],"$$rtrim$");
                  Use_Rtrim=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"run")==0)
                {
                  strcpy(Stk[Tmp],"Run");
                  Use_Run=TRUE;
                }
              break;
            }
            break;
          }
        if(a==19)
          {
            for(;;)
            {
              if(str_cmp(Keyword,"scanerror")==0)
                {
                  strcpy(Stk[Tmp],"ScanError");
                  break;
                }
              if(str_cmp(Keyword,"sprint")==0)
                {
                  strcpy(Stk[Tmp],"sprint");
                  break;
                }
              if(str_cmp(Keyword,"spc$")==0)
                {
                  strcpy(Stk[Tmp],"SPC$");
                  Use_SPC=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"str$")==0)
                {
                  strcpy(Stk[Tmp],"$$str$");
                  Use_Str=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"strl$")==0)
                {
                  strcpy(Stk[Tmp],"$$strl$");
                  Use_Strl=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"searchpath$")==0)
                {
                  strcpy(Stk[Tmp],"$$SEARCHPATH$");
                  Use_SearchPath=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"sizeof")==0)
                {
                  strcpy(Stk[Tmp],"sizeof");
                  break;
                }
              if(str_cmp(Keyword,"setattr")==0)
                {
                  strcpy(Stk[Tmp],"SETATTR");
                  break;
                }
              if(str_cmp(Keyword,"setwindowrtftext")==0)
                {
                  strcpy(Stk[Tmp],"SetWindowRTFText");
                  break;
                }
              if(str_cmp(Keyword,"sgn")==0)
                {
                  strcpy(Stk[Tmp],"sgn");
                  Use_Sgn=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"short")==0)
                {
                  strcpy(Stk[Tmp],"short");
                  break;
                }
              if(str_cmp(Keyword,"shell")==0)
                {
                  Use_Shell=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"show")==0)
                {
                  strcpy(Stk[Tmp],"Show");
                  break;
                }
              if(str_cmp(Keyword,"sin")==0)
                {
                  strcpy(Stk[Tmp],"sin");
                  break;
                }
              if(str_cmp(Keyword,"sinl")==0)
                {
                  strcpy(Stk[Tmp],"sinl");
                  break;
                }
              if(str_cmp(Keyword,"single")==0)
                {
                  strcpy(Stk[Tmp],"float");
                  break;
                }
              if(str_cmp(Keyword,"sinh")==0)
                {
                  strcpy(Stk[Tmp],"sinh");
                  break;
                }
              if(str_cmp(Keyword,"sleep")==0)
                {
                  strcpy(Stk[Tmp],"sleep");
                  break;
                }
              if(str_cmp(Keyword,"space$")==0)
                {
                  strcpy(Stk[Tmp],"$$space$");
                  Use_Space=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"split")==0)
                {
                  strcpy(Stk[Tmp],"Split");
                  Use_Split=UseFlag=TRUE;
                  Use_Remove=TRUE;
                  Use_StrStr=TRUE;
                  Use_Mid=TRUE;
                  Use_Left=TRUE;
                  Use_Instr=TRUE;
                  Use_Stristr=TRUE;
                  UseLCaseTbl=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"splitbarfg")==0)
                {
                  strcpy(Stk[Tmp],"SplitBarFG");
                  break;
                }
              if(str_cmp(Keyword,"splitbarbg")==0)
                {
                  strcpy(Stk[Tmp],"SplitBarBG");
                  break;
                }
              if(str_cmp(Keyword,"sqr")==0 ||  str_cmp(Keyword,"sqrt")==0)
                {
                  strcpy(Stk[Tmp],"sqrt");
                  break;
                }
              if(str_cmp(Keyword,"sqrl")==0 ||  str_cmp(Keyword,"sqrtl")==0)
                {
                  strcpy(Stk[Tmp],"sqrtl");
                  break;
                }
              if(str_cmp(Keyword,"strarray")==0)
                {
                  strcpy(Stk[Tmp],"PCHAR*");
                  break;
                }
              if(str_cmp(Keyword,"strim$")==0)
                {
                  strcpy(Stk[Tmp],"$$strim$");
                  Use_Strim=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"string")==0)
                {
                  strcpy(Stk[Tmp],"string");
                  break;
                }
              if(str_cmp(Keyword,"string$")==0)
                {
                  strcpy(Stk[Tmp],"$$stringx$");
                  Use_String=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"strptr")==0)
                {
                  strcpy(Stk[Tmp],"STRPTR");
                  Use_Strptr=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"strtoken$")==0)
                {
                  strcpy(Stk[Tmp],"StrToken$");
                  Use_Strtoken=Use_Mid=Use_Left=Use_Extract=TRUE;
                  Use_Instr=Use_Instrrev=Use_Stristr=Use_Tally=Use_Remove=TRUE;
                  Use_StrStr=UseLCaseTbl=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"swap")==0)
                {
                  strcpy(Stk[Tmp],"swap");
                  Use_Swap=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"sysdir$")==0)
                {
                  strcpy(Stk[Tmp],"$$sysdir$()");
                  if(str_cmp(Stk[Tmp+1],"(")==0 &&  str_cmp(Stk[Tmp+2],")")==0)
                    {
                      *Stk[Tmp+1]=0;
                      *Stk[Tmp+2]=0;
                    }
                  Use_Sysdir=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"sysstr")==0)
                {
                  strcpy(Stk[Tmp],"SysStr");
                  Use_SysStr=TRUE;
                }
              break;
            }
            break;
          }
        if(a==20)
          {
            for(;;)
            {
              if(str_cmp(Keyword,"tab$")==0)
                {
                  strcpy(Stk[Tmp],"TAB$");
                  Use_TAB=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"true")==0)
                {
                  strcpy(Stk[Tmp],"TRUE");
                  break;
                }
              if(str_cmp(Keyword,"trim$")==0)
                {
                  strcpy(Stk[Tmp],"$$trim$");
                  Use_Trim=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"tally")==0)
                {
                  strcpy(Stk[Tmp],"tally");
                  Use_Tally=UseLCaseTbl=Use_Stristr=Use_StrStr=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"tan")==0)
                {
                  strcpy(Stk[Tmp],"tan");
                  break;
                }
              if(str_cmp(Keyword,"tanh")==0)
                {
                  strcpy(Stk[Tmp],"tanh");
                  break;
                }
              if(str_cmp(Keyword,"tanl")==0)
                {
                  strcpy(Stk[Tmp],"tanl");
                  break;
                }
              if(str_cmp(Keyword,"tempdir$")==0)
                {
                  strcpy(Stk[Tmp],"$$tempdir$()");
                  if(str_cmp(Stk[Tmp+1],"(")==0 &&  str_cmp(Stk[Tmp+2],")")==0)
                    {
                      *Stk[Tmp+1]=0;
                      *Stk[Tmp+2]=0;
                    }
                  Use_Tempdir=UseFlag=Use_Exist=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"tempfilename$")==0)
                {
                  strcpy(Stk[Tmp],"$$TempFileName$");
                  Use_TempFileName=UseFlag=TRUE;
                  Use_Exist=Use_Rnd=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"this")==0)
                {
                  strcpy(Stk[Tmp],"this");
                  if(*Stk[Tmp+1]==46)
                    {
                      strcpy(Stk[Tmp+1], join(2,"->",mid(Stk[Tmp+1],2)));
                    }
                  break;
                }
              if(str_cmp(Keyword,"time$")==0)
                {
                  if(str_cmp(Stk[Tmp+1],"(")!=0)
                    {
                      strcpy(Stk[Tmp],"$$timef$()");
                    }
                  else
                    {
                      strcpy(Stk[Tmp],"$$timef$");
                    }
                  if(str_cmp(Stk[Tmp+1],"(")==0 &&  str_cmp(Stk[Tmp+2],")")==0)
                    {
                      *Stk[Tmp+1]=0;
                      *Stk[Tmp+2]=0;
                    }
                  Use_Time=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"timer")==0)
                {
                  strcpy(Stk[Tmp],"timer()");
                  if(str_cmp(Stk[Tmp+1],"(")==0 &&  str_cmp(Stk[Tmp+2],")")==0)
                    {
                      *Stk[Tmp+1]=0;
                      *Stk[Tmp+2]=0;
                    }
                  Use_Timer=TRUE;
                }
              break;
            }
            break;
          }
        if(a==21)
          {
            for(;;)
            {
              if(str_cmp(Keyword,"uint")==0)
                {
                  strcpy(Stk[Tmp],"UINT");
                  break;
                }
              if(str_cmp(Keyword,"ushort")==0)
                {
                  strcpy(Stk[Tmp],"USHORT");
                  break;
                }
              if(str_cmp(Keyword,"ulong")==0)
                {
                  strcpy(Stk[Tmp],"ULONG");
                  break;
                }
              if(str_cmp(Keyword,"ulonglong")==0)
                {
                  strcpy(Stk[Tmp],"ULONGLONG");
                  break;
                }
              if(str_cmp(Keyword,"ucase$")==0)
                {
                  strcpy(Stk[Tmp],"$$ucase$");
                  Use_Ucase=UseFlag=TRUE;
                  Use_StrUpLow=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"ubound")==0)
                {
                  strcpy(Stk[Tmp],"ubound");
                  Use_Ubound=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"using$")==0)
                {
                  strcpy(Stk[Tmp],"$$Using$");
                  Use_Using=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"using")==0)
                {
                  strcpy(Stk[Tmp],"using");
                }
              break;
            }
            break;
          }
        if(a==22)
          {
            for(;;)
            {
              if(str_cmp(Keyword,"val")==0)
                {
                  strcpy(Stk[Tmp],"VAL");
                  Use_Val=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"vall")==0)
                {
                  strcpy(Stk[Tmp],"VALL");
                  Use_Vall=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"variant")==0)
                {
                  strcpy(Stk[Tmp],"VARIANT");
                  break;
                }
              if(str_cmp(Keyword,"varptr")==0)
                {
                  *Stk[Tmp]=0;
                  break;
                }
              if(str_cmp(Keyword,"vchr$")==0)
                {
                  strcpy(Stk[Tmp],"$$vchr$");
                  Use_VChr=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"virtual")==0)
                {
                  strcpy(Stk[Tmp],"virtual");
                  Use_Virtual=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"vt$")==0)
                {
                  strcpy(Stk[Tmp],"VT$");
                  Use_VT=UseFlag=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"verify")==0)
                {
                  strcpy(Stk[Tmp],"Verify");
                  Use_Verify=Use_Mid=UseFlag=TRUE;
                }
              break;
            }
            break;
          }
        if(a==23)
          {
            for(;;)
            {
              if(str_cmp(Keyword,"widetoansi$")==0)
                {
                  strcpy(Stk[Tmp],"$$WideToAnsi$");
                  Use_WideToAnsi=UseFlag=TRUE;
                }
              break;
            }
          }
        break;
      }
    }
  if(CompPtr==1)
    {
      RemEmptyTokens();
    }
  if(WithCnt)
    {
      for(i=1; i<=Ndx; i+=1)
        {
          if(str_cmp(left(Stk[i],2),"->")==0 || ( str_cmp(left(Stk[i],1),".")==0 && !IsNumber(mid(Stk[i],2,1))))
            {
              if(str_cmp(WithVar[WithCnt],"this")==0)
                {
                  strcpy(Stk[i], join(2,"->",mid(Stk[i],2)));
                }
              if(i==1)
                {
                  strcpy(Stk[i], join(2,WithVar[WithCnt],Stk[i]));
                }
              else
                {
                  if(!IsReservedWord(Stk[i-1]))
                    {
                      if(!(isalpha(Stk[i-1][strlen(Stk[i-1]-1)])||IsNumber(right(Stk[i-1],strlen(Stk[i-1]-1)))))
                        {
                          strcpy(Stk[i], join(2,WithVar[WithCnt],Stk[i]));
                        }
                    }
                  else
                    {
                      strcpy(Stk[i], join(2,WithVar[WithCnt],Stk[i]));
                    }
                }
              while((isalpha(*Stk[i+1])||*Stk[i+1]==46)&&(i<Ndx))
                {
                  i++;
                }
            }
        }
    }
  if(CompToken==1)
    {
      strcpy(Keyword,lcase(Stk[1]));
      for(;;)
      {
        if(str_cmp(Keyword,"dim")==0)
          {
            CompToken=0;
            break;
          }
        if(str_cmp(Keyword,"local")==0)
          {
            CompToken=0;
            break;
          }
        if(str_cmp(Keyword,"global")==0)
          {
            CompToken=0;
            break;
          }
        if(str_cmp(Keyword,"static")==0)
          {
            CompToken=0;
            break;
          }
        if(str_cmp(Keyword,"shared")==0)
          {
            CompToken=0;
            break;
          }
        if(str_cmp(Keyword,"raw")==0)
          {
            CompToken=0;
            break;
          }
        if(str_cmp(Keyword,"dynamic")==0)
          {
            CompToken=0;
            break;
          }
        if(str_cmp(Keyword,"free")==0)
          {
            CompToken=0;
            break;
          }
        if(str_cmp(Keyword,"redim")==0)
          {
            CompToken=0;
            break;
          }
        if(str_cmp(Keyword,"sub")==0)
          {
            CompToken=0;
            break;
          }
        if(str_cmp(Keyword,"function")==0)
          {
            CompToken=0;
            break;
          }
        if(str_cmp(Keyword,"overloaded")==0)
          {
            CompToken=0;
            break;
          }
        if(str_cmp(Keyword,"public")==0)
          {
            CompToken=0;
            break;
          }
        if(str_cmp(Keyword,"declare")==0)
          {
            CompToken=0;
            break;
          }
        if(str_cmp(Keyword,"c_declare")==0)
          {
            CompToken=0;
            break;
          }
        if(str_cmp(Keyword,"auto")==0)
          {
            CompToken=0;
            break;
          }
        if(str_cmp(Keyword,"register")==0)
          {
            CompToken=0;
            break;
          }
        if(str_cmp(Keyword,"extern")==0)
          {
            CompToken=0;
            break;
          }
          // case else
          {
            AsmUnknownStructs(1);
          }
        break;
      }
    }
}


void JoinStrings (int i, int inif)
{
  int     DoJoin=0;
  int     InBrace=0;
  int     OnlyPara=0;
  int     j=0;
  int     l=0;
  int     sj=i;
  char t[2048];
  int     vt;
  while(i<=Ndx)
    {
      strcpy(t,lcase(Stk[i]));
      if(!j&&!OnlyPara&&!InBrace)
        {
          vt=DataType(t);
          if(vt==vt_STRVAR||vt==vt_STRLIT)
            {
              sj=i;
              i++;
              continue;
            }
        }
      for(;;)
      {
        if(str_cmp(t,"&")==0)
          {
            if(OnlyPara)
              {
                break;
              }
            vt=DataType(Stk[i+1]);
            if(vt!=vt_STRVAR&&vt!=vt_STRLIT)
              {
                vt=DataType(Stk[i-1]);
              }
            if(vt==vt_STRVAR||vt==vt_STRLIT)
              {
                j++;
                strcpy(Stk[i],",");
                *t=0;
              }
            break;
          }
        if(str_cmp(t,"[")==0)
          {
            InBrace++;
            break;
          }
        if(str_cmp(t,"]")==0)
          {
            InBrace--;
            break;
          }
        if(str_cmp(t,"(")==0)
          {
            if(str_cmp(Stk[i+1],"*")!=0)
              {
                JoinStrings(i+1,inif);
                l=i-1;
                while(str_cmp(Stk[i],")")!=0)
                  {
                    strcpy(Stk[l], join(3,Stk[l],Stk[i]," "));
                    *Stk[i]=0;
                    i++;
                  }
                strcat(Stk[l],Stk[i]);
                *Stk[i]=0;
              }
            break;
          }
        if(str_cmp(t,")")==0)
          {
            if(j)
              {
                strcpy(Stk[sj], join(4,"join$(",str(j+1),",",Stk[sj]));
                j=sj+1;
                while(j<i)
                  {
                    strcat(Stk[sj],Stk[j]);
                    *Stk[j]=0;
                    j++;
                  }
                strcat(Stk[sj],")");
              }
            return;
          }
        if(str_cmp(t,"||")==0)
          {
            strcpy(Stk[i]," or ");
            DoJoin=TRUE;
            break;
          }
        if(str_cmp(t,"&&")==0)
          {
            strcpy(Stk[i]," and ");
            DoJoin=TRUE;
            break;
          }
        if(str_cmp(t,"then")==0 ||  str_cmp(t,"for")==0)
          {
            DoJoin=TRUE;
            break;
          }
        if(str_cmp(t,"=")==0)
          {
            if(!inif)
              {
                OnlyPara=TRUE;
              }
            else
              {
                DoJoin=TRUE;
              }
            break;
          }
        if(str_cmp(t,"if")==0 ||  str_cmp(t,"elseif")==0 ||  str_cmp(t,"while")==0)
          {
            inif=TRUE;
            sj=i+1;
            break;
          }
        if(str_cmp(t,"sprint")==0 ||  str_cmp(t,"lprint")==0 ||  str_cmp(t,"fprint")==0 ||  str_cmp(t,"fprintf")==0 ||  str_cmp(t,"print")==0 ||  str_cmp(t,"print#")==0)
          {
            OnlyPara=TRUE;
            break;
          }
          // case else
          {
            if(str_cmp(left(Stk[i],2),"].")==0 ||  str_cmp(left(Stk[i],3),"]->")==0)
              {
                InBrace--;
              }
          }
        break;
      }
      if((DoJoin||inchr(",+-*/^;:<>~|&",t))&&!OnlyPara&&!InBrace)
        {
          DoJoin=0;
          if(j)
            {
              strcpy(Stk[sj], join(4,"join$(",str(j+1),",",Stk[sj]));
              j=sj;
              j++;
              while(j<i)
                {
                  strcat(Stk[sj],Stk[j]);
                  *Stk[j]=0;
                  j++;
                }
              strcat(Stk[sj],")");
            }
          j=0;
          sj=i+1;
        }
      i++;
    }
  if(j)
    {
      strcpy(Stk[sj], join(4,"join$(",str(j+1),",",Stk[sj]));
      j=sj;
      j++;
      while(j<=i)
        {
          strcat(Stk[sj],Stk[j]);
          *Stk[j]=0;
          j++;
        }
      strcat(Stk[sj],")");
    }
}


void Transforms (void)
{
  int     nBrace;
  int     CntMarker;
  int     IFCond;
  int     a;
  int     i;
  int     j;
  char Keyword[2048];
  char lszTmp[2048];
  *Keyword=0;
  *lszTmp=0;
  if(Ndx==3&&!WithCnt)
    {
      if(str_cmp(Stk[2],"+")==0 &&  str_cmp(Stk[3],"+")==0)
        {
          fprintf(Outfile,"%s%s%s\n",Scoot,Clean(Stk[1]),"++;");
          Ndx=0;
          Statements++;
          return;
        }
      if(str_cmp(Stk[2],"-")==0 &&  str_cmp(Stk[3],"-")==0)
        {
          fprintf(Outfile,"%s%s%s\n",Scoot,Clean(Stk[1]),"--;");
          Ndx=0;
          Statements++;
          return;
        }
      if(str_cmp(Stk[1],"+")==0 &&  str_cmp(Stk[2],"+")==0)
        {
          fprintf(Outfile,"%s%s%s%s\n",Scoot,"++",Clean(Stk[3]),";");
          Ndx=0;
          Statements++;
          return;
        }
      if(str_cmp(Stk[1],"-")==0 &&  str_cmp(Stk[2],"-")==0)
        {
          fprintf(Outfile,"%s%s%s%s\n",Scoot,"--",Clean(Stk[3]),";");
          Ndx=0;
          Statements++;
          return;
        }
    }
  strcpy(Keyword,lcase(Stk[1]));
  a=inchr("abcdefghijklmnopqrstuvwxyz$",Keyword);
  for(;;)
  {
    if(a==3)
      {
        if(str_cmp(Keyword,"case")==0)
          {
            nBrace=0;
            CntMarker=2;
            j=0;
            for(i=2; i<=Ndx; i+=1)
              {
                if(inchr("([",Stk[i]))
                  {
                    nBrace++;
                  }
                if(inchr(")]",Stk[i]))
                  {
                    nBrace--;
                  }
                if(str_cmp(Stk[i],",")==0)
                  {
                    if(nBrace==0)
                      {
                        CntMarker=i+1;
                      }
                  }
                if(iMatchWrd(Stk[i],"to"))
                  {
                    j=1;
                    strcpy(Stk[i]," and <=");
                    strcpy(Stk[CntMarker], join(2,">=",Stk[CntMarker]));
                  }
              }
            if(j==1)
              {
                *Src=0;
                for(i=1; i<=Ndx; i+=1)
                  {
                    strcpy(Src, join(3,Src,Stk[i]," "));
                  }
                XParse(Src);
              }
            return;
          }
        break;
      }
    if(a==4)
      {
        if(str_cmp(Keyword,"declare")==0 && iMatchWrd(Stk[4],"lib"))
          {
            char alias[2048];
            int     i;
            int     idx=-1;
            char AR_DllName[2048];
            strcpy(Stk[5],RemoveStr(Stk[5],DQ));
            for(i=0; i<=LoadLibsCnt-1; i+=1)
              {
                if(str_cmp(Stk[5],Loadlibs[i])==0)
                  {
                    idx=i;
                    break;
                  }
              }
            if(idx<0)
              {
                strcpy(Loadlibs[LoadLibsCnt],Stk[5]);
                LoadLibsCnt++;
              }
            if(iMatchWrd(Stk[6],"alias"))
              {
                strcpy(alias,Stk[7]);
                *Stk[6]=0;
                *Stk[7]=0;
              }
            else
              {
                strcpy(alias,enc(Stk[3]));
              }
            DllCnt++;
            if(DllCnt>799)
              {
                Abort("Maximum number of declarations exceded.");
              }
            if(inchr(Stk[5],"-"))
              {
                strcpy(AR_DllName,extract(Stk[5],"-"));
              }
            else if(inchr(Stk[5],"."))
              {
                strcpy(AR_DllName,extract(Stk[5],"."));
              }
            strcpy(DllDecl[DllCnt], join(11,"static BCXFPROT",ltrim(str(DllCnt)),SPC,Clean(Stk[3]),"=(BCXFPROT",ltrim(str(DllCnt)),")dlsym(H_",ucase(AR_DllName),", ",alias,");"));
            *Stk[4]=0;
            *Stk[5]=0;
            return;
          }
        break;
      }
    if(a==7)
      {
        if(str_cmp(Keyword,"get$")==0)
          {
            strcpy(Stk[1],"~get");
            return;
          }
        if(str_cmp(Keyword,"global")==0 && iMatchWrd(Stk[2],"dynamic"))
          {
            strcpy(Stk[1],"global");
            return;
          }
        break;
      }
    if(a==9)
      {
        if(str_cmp(Keyword,"iremove")==0)
          {
            char Mat[2048];
            char Fat[2048];
            *Mat=0;
            *Fat=0;
            for(i=2; i<=Ndx; i+=1)
              {
                if(iMatchWrd(Stk[i],"from"))
                  {
                    *Stk[i]=0;
                    break;
                  }
              }
            for(j=2; j<=i; j+=1)
              {
                strcat(Mat,Stk[j]);
              }
            for(j=i; j<=Ndx; j+=1)
              {
                strcat(Fat,Stk[j]);
              }
            strcpy(lszTmp, join(5,"=iremove$(",Fat,",",Mat,")"));
            FastLexer(Fat," ()","");
            strcpy(lszTmp, join(2,Stk[Ndx],lszTmp));
            XParse(lszTmp);
            TokenSubstitutions();
            Emit();
            Ndx=0;
            return;
          }
        if(str_cmp(Keyword,"ireplace")==0)
          {
            if(Ndx<6)
              {
                Abort("Problem with IREPLACE statement");
              }
            int     W;
            int     I;
            char VV[2048];
            char RR[2048];
            char WW[2048];
            *VV=0;
            *RR=0;
            *WW=0;
            for(W=2; W<=Ndx; W+=1)
              {
                if(iMatchWrd(Stk[W],"with"))
                  {
                    *Stk[W]=0;
                    break;
                  }
              }
            for(I=2; I<=Ndx; I+=1)
              {
                if(iMatchWrd(Stk[I],"in"))
                  {
                    *Stk[I]=0;
                    break;
                  }
              }
            i=I+1;
            for(j=i; j<=Ndx; j+=1)
              {
                strcat(VV,Stk[j]);
              }
            for(j=2; j<=W; j+=1)
              {
                strcat(RR,Stk[j]);
              }
            i=W+1;
            for(j=i; j<=I; j+=1)
              {
                strcat(WW,Stk[j]);
              }
            strcpy(lszTmp, join(7,"=ireplace$(",VV,",",RR,",",WW,")"));
            FastLexer(VV," ()","");
            strcpy(lszTmp, join(2,Stk[Ndx],lszTmp));
            XParse(lszTmp);
            TokenSubstitutions();
            Emit();
            Ndx=0;
            return;
          }
        break;
      }
    if(a==12)
      {
        if(str_cmp(Keyword,"local")==0 && iMatchWrd(Stk[2],"dynamic"))
          {
            strcpy(Stk[1],"dim");
            return;
          }
        break;
      }
    if(a==16)
      {
        if(str_cmp(Keyword,"put$")==0)
          {
            strcpy(Stk[1],"~put");
            return;
          }
        break;
      }
    if(a==18)
      {
        if(str_cmp(Keyword,"remove")==0)
          {
            char Mat[2048];
            char Fat[2048];
            *Mat=0;
            *Fat=0;
            for(i=2; i<=Ndx; i+=1)
              {
                if(iMatchWrd(Stk[i],"from"))
                  {
                    *Stk[i]=0;
                    break;
                  }
              }
            for(j=2; j<=i; j+=1)
              {
                strcat(Mat,Stk[j]);
              }
            for(j=i; j<=Ndx; j+=1)
              {
                strcat(Fat,Stk[j]);
              }
            strcpy(lszTmp, join(5,"=remove$(",Fat,",",Mat,")"));
            FastLexer(Fat," ()","");
            strcpy(lszTmp, join(2,Stk[Ndx],lszTmp));
            XParse(lszTmp);
            TokenSubstitutions();
            Emit();
            Ndx=0;
            return;
          }
        if(str_cmp(Keyword,"replace")==0)
          {
            if(Ndx<6)
              {
                Abort("Problem with REPLACE statement");
              }
            int     W;
            int     I;
            char VV[2048];
            char RR[2048];
            char WW[2048];
            *VV=0;
            *RR=0;
            *WW=0;
            for(W=2; W<=Ndx; W+=1)
              {
                if(iMatchWrd(Stk[W],"with"))
                  {
                    *Stk[W]=0;
                    break;
                  }
              }
            for(I=2; I<=Ndx; I+=1)
              {
                if(iMatchWrd(Stk[I],"in"))
                  {
                    *Stk[I]=0;
                    break;
                  }
              }
            i=I+1;
            for(j=i; j<=Ndx; j+=1)
              {
                strcat(VV,Stk[j]);
              }
            for(j=2; j<=W; j+=1)
              {
                strcat(RR,Stk[j]);
              }
            i=W+1;
            for(j=i; j<=I; j+=1)
              {
                strcat(WW,Stk[j]);
              }
            strcpy(lszTmp, join(7,"=replace$(",VV,",",RR,",",WW,")"));
            FastLexer(VV," ()","");
            strcpy(lszTmp, join(2,Stk[Ndx],lszTmp));
            XParse(lszTmp);
            TokenSubstitutions();
            Emit();
            Ndx=0;
            return;
          }
        break;
      }
    if(a==27)
      {
        for(;;)
        {
          if(str_cmp(Keyword,"$ifndef")==0)
            {
              strcpy(Stk[1],"~ifndef");
              InConditional++;
              break;
            }
          if(str_cmp(Keyword,"$if")==0 ||  str_cmp(Keyword,"$ifdef")==0)
            {
              strcpy(Stk[1],"~if");
              InConditional++;
              break;
            }
          if(str_cmp(Keyword,"$else")==0)
            {
              strcpy(Stk[1],"~else");
              break;
            }
          if(str_cmp(Keyword,"$elseif")==0)
            {
              strcpy(Stk[1],"~elseif");
              break;
            }
          if(str_cmp(Keyword,"$endif")==0)
            {
              strcpy(Stk[1],"~endif");
              InConditional--;
              if(InConditional<0)
                {
                  Abort("To many $ENDIFs");
                }
              break;
            }
          if(str_cmp(Keyword,"$cpp")==0)
            {
              Ndx=0;
              UseCpp=TRUE;
              break;
            }
          if(str_cmp(Keyword,"$CPP")==0)
            {
              Ndx=0;
              UseCpp=TRUE;
            }
          break;
        }
        return;
      }
    break;
  }
  IFCond=0;
  for(i=1; i<=Ndx; i+=1)
    {
      if(iMatchWrd(Stk[i],"if"))
        {
          IFCond=i+1;
        }
      if(iMatchWrd(Stk[i],"then")&&iMatchWrd(Stk[i+1],"if"))
        {
          for(j=i+2; j<=Ndx; j+=1)
            {
              if(iMatchWrd(Stk[j],"else"))
                {
                  break;
                }
            }
          if(j>Ndx)
            {
              for(j=i; j>=IFCond+1; j+=-1)
                {
                  strcpy(Stk[j],Stk[j-1]);
                }
              strcpy(Stk[IFCond],"(");
              i++;
              strcpy(Stk[i],")");
              i++;
              for(j=Ndx; j>=i; j+=-1)
                {
                  strcpy(Stk[j+2],Stk[j]);
                }
              Ndx++;
              Ndx++;
              strcpy(Stk[i],"&&");
              i++;
              strcpy(Stk[i],"(");
              i++;
              for(i=i; i<=Ndx; i+=1)
                {
                  if(iMatchWrd(Stk[i],"then"))
                    {
                      Ndx++;
                      for(j=Ndx; j>=i; j+=-1)
                        {
                          strcpy(Stk[j],Stk[j-1]);
                        }
                      strcpy(Stk[i],")");
                      break;
                    }
                }
              i--;
            }
          else
            {
              break;
            }
        }
    }
}


void Parse (char *Arg)
{
  int     A;
  int     B;
  int     CommaCnt;
  int     Tmp;
  int     i;
  int     j;
  int     k;
  char lszTmp[2048];
  char L_Stk_1[2048];
  char L_Stk_2[2048];
  char Var1[2048];
  int     Plus2Amp=0;
  int     vt;
  *L_Stk_1=0;
  *L_Stk_2=0;
  *lszTmp=0;
  *Var1=0;
  XParse(Arg);
  PassOne=0;
  if(!iMatchWrd(Stk[1],"function"))
    {
      Plus2Amp=iMatchNQ(Arg,"&");
      for(Tmp=2; Tmp<=Ndx-1; Tmp+=1)
        {
          if(str_cmp(Stk[Tmp],"+")==0)
            {
              vt=DataType(Stk[Tmp+1]);
              if(vt==vt_STRVAR||vt==vt_STRLIT)
                {
                  strcpy(Stk[Tmp],"&");
                  Plus2Amp=TRUE;
                }
              else
                {
                  vt=DataType(Stk[Tmp-1]);
                  if(vt==vt_STRVAR||vt==vt_STRLIT)
                    {
                      strcpy(Stk[Tmp],"&");
                      Plus2Amp=TRUE;
                    }
                }
            }
        }
      if(Plus2Amp>0)
        {
          Use_Join=UseFlag=TRUE;
          j=0;
          k=0;
          for(Tmp=1; Tmp<=Ndx-1; Tmp+=1)
            {
              A=CheckLocal(Stk[Tmp], &i);
              if(A==vt_UNKNOWN)
                {
                  A=CheckGlobal(Stk[Tmp], &i);
                }
              if(A==vt_STRUCT||A==vt_UDT||A==vt_UNION)
                {
                  j=1;
                }
              if(str_cmp(Stk[Tmp],"&")==0)
                {
                  A=DataType(Stk[Tmp+1]);
                  if(A==vt_STRVAR||A==vt_STRLIT)
                    {
                      k=1;
                    }
                  else
                    {
                      A=DataType(Stk[Tmp-1]);
                      if(A==vt_STRVAR||A==vt_STRLIT)
                        {
                          k=1;
                        }
                    }
                }
            }
          if(k)
            {
              if(j)
                {
                  AsmUnknownStructs(0);
                }
              JoinStrings(1,0);
              *Src=0;
              for(i=1; i<=Ndx; i+=1)
                {
                  if(Stk[i][0])
                    {
                      strcpy(Src, join(3,Src,Stk[i]," "));
                    }
                }
              XParse(Src);
            }
        }
    }
  if(UseCpp)
    {
      if(iMatchNQ(Src,"->lpVtbl"))
        {
            {int i;
          for(i=1; i<=Ndx; i+=1)
            {
              if(iMatchRgt(Stk[i],"->lpVtbl"))
                {
                  strcpy(Stk[i],extract(Stk[i],"->lpVtbl"));
                  if((str_cmp(Stk[i+3],Stk[i-1])==0 ||  str_cmp(Stk[i+3],Stk[i])==0) &&  str_cmp(Stk[i+3],")")!=0)
                    {
                      *Stk[i+3]=0;
                      if(str_cmp(Stk[i+4],",")==0)
                        {
                          *Stk[i+4]=0;
                        }
                    }
                }
            }
            }
          RemEmptyTokens();
        }
    }
  TokenSubstitutions();
  if(Ndx==0)
    {
      return;
    }
  Transforms();
  if(Ndx==0)
    {
      return;
    }
  if(iMatchWrd(Stk[1],"function"))
    {
      if(iMatchWrd(Stk[Ndx-2],"as")&&str_cmp(Stk[Ndx],")")!=0)
        {
          if(!iMatchWrd(Stk[Ndx],"export")&&!iMatchWrd(Stk[Ndx],"stdcall"))
            {
              strcpy(Stk[Ndx-1], join(3,Stk[Ndx-1]," ",Stk[Ndx]));
              Ndx--;
            }
        }
    }
  if(iMatchWrd(Stk[1],"function")||iMatchWrd(Stk[1],"sub"))
    {
      int     offset;
      int     LastBrk=Ndx-2;
      for(i=Ndx; i>=3; i+=-1)
        {
          if(str_cmp(Stk[i],")")==0)
            {
              LastBrk=i;
              break;
            }
        }
      for(i=3; i<=LastBrk; i+=1)
        {
          offset=2;
          if(iMatchWrd(Stk[i],"as")&&(i<LastBrk)&&str_cmp(Stk[i+offset],"=")!=0)
            {
              if(iMatchWrd(Stk[i+1],"function"))
                {
                  offset=3;
                }
              if(!inchr(Stk[i+offset],")")&&!inchr(Stk[i+offset],","))
                {
                  if(strlen(Stk[i+offset])!=0&&!iMatchWrd(Stk[i+3],"as"))
                    {
                      strcpy(Stk[i+offset-1], join(3,Stk[i+offset-1]," ",Stk[i+offset]));
                      *Stk[i+offset]=0;
                    }
                }
            }
        }
    }
  if(!iMatchWrd(Stk[1],"declare"))
    {
      for(i=1; i<=Ndx; i+=1)
        {
          if(iMatchWrd(Stk[i],"lib"))
            {
              if(str_cmp(Stk[i-1],"(")==0 && (DataType(Stk[i+1])==vt_STRLIT||DataType(Stk[i+1])==vt_STRVAR))
                {
                  j=GetNumArgs(i+2);
                  strcpy(lszTmp,"BCX_DynaCall");
                  if(!iMatchWrd(Stk[1],"print"))
                    {
                      if(DataType(Stk[i-2])==vt_STRVAR||DataType(Stk[1])==vt_STRVAR)
                        {
                          strcpy(lszTmp, join(2,"(char*)",lszTmp));
                        }
                    }
                  strcpy(Var1,right(Stk[i-2],1));
                  if(inchr("!$#¦%",Var1))
                    {
                      strcat(lszTmp,Var1);
                      strcpy(Stk[i],enc(left(Stk[i-2],strlen(Stk[i-2])-1)));
                    }
                  else
                    {
                      strcpy(Stk[i],enc(Stk[i-2]));
                    }
                  strcpy(Stk[i-2],lszTmp);
                  for(B=Ndx+3; B>=i+3; B+=-1)
                    {
                      strcpy(Stk[B],Stk[B-3]);
                    }
                  strcpy(Stk[i+2],Stk[i+1]);
                  strcpy(Stk[i+1],",");
                  strcpy(Stk[i+3],",");
                  strcpy(Stk[i+4],ltrim(str(j)));
                  strcpy(Stk[i+5],sziif(j,",",")"));
                  Ndx+=(3);
                  Use_Dynacall=TRUE;
                }
            }
        }
    }
  if(inchr(Arg,"^"))
    {
      int     lp=0;
      int     rp=0;
      Test=FALSE;
      for(i=1; i<=Ndx; i+=1)
        {
          if(str_cmp(Stk[i],"^")==0)
            {
              Test=TRUE;
              if(str_cmp(Stk[i+1],"-")==0)
                {
                  Ndx++;
                  for(A=Ndx; A>=i+2; A+=-1)
                    {
                      strcpy(Stk[A],Stk[A-1]);
                    }
                  strcpy(Stk[i+1],"(");
                  B=i+3;
                  if(str_cmp(Stk[B],"(")==0)
                    {
                      lp=0;
                      rp=0;
                      for(;;)
                        {
                          if(str_cmp(Stk[B],"(")==0)
                            {
                              lp++;
                            }
                          if(str_cmp(Stk[B],")")==0)
                            {
                              rp++;
                            }
                          B++;
                          if(lp==rp)
                            {
                              break;
                            }
                        }
                      Ndx++;
                      j=B+1;
                      for(A=Ndx; A>=j; A+=-1)
                        {
                          strcpy(Stk[A],Stk[A-1]);
                        }
                      strcpy(Stk[B],")");
                    }
                  else
                    {
                      B=i+4;
                      if(inchr("[",Stk[B]))
                        {
                          for(;;)
                            {
                              B++;
                              if(inchr("]",Stk[B]))
                                {
                                  break;
                                }
                            }
                          Ndx++;
                          j=B+2;
                          for(A=Ndx; A>=j; A+=-1)
                            {
                              strcpy(Stk[A],Stk[A-1]);
                            }
                          strcpy(Stk[B+1],")");
                        }
                      else
                        {
                          if(inchr("(",Stk[B]))
                            {
                              for(;;)
                                {
                                  B++;
                                  if(inchr(")",Stk[B]))
                                    {
                                      break;
                                    }
                                }
                              Ndx++;
                              j=B+2;
                              for(A=Ndx; A>=j; A+=-1)
                                {
                                  strcpy(Stk[A],Stk[A-1]);
                                }
                              strcpy(Stk[B+1],")");
                            }
                          else
                            {
                              Ndx++;
                              j=B+1;
                              for(A=Ndx; A>=j; A+=-1)
                                {
                                  strcpy(Stk[A],Stk[A-1]);
                                }
                              strcpy(Stk[B],")");
                            }
                        }
                    }
                }
            }
        }
      if(Test)
        {
          for(i=1; i<=Ndx; i+=1)
            {
              if(str_cmp(Stk[i],"^")==0)
                {
                  A=i-1;
                  B=0;
                  while(str_cmp(Stk[A],"=")!=0)
                    {
                      if(str_cmp(Stk[A],"]")==0)
                        {
                          B++;
                        }
                      if(str_cmp(Stk[A],")")==0)
                        {
                          B++;
                        }
                      if(str_cmp(Stk[A],"[")==0)
                        {
                          B--;
                        }
                      if(str_cmp(Stk[A],"(")==0)
                        {
                          B--;
                        }
                      if(B==0)
                        {
                          break;
                        }
                      A--;
                    }
                  if(str_cmp(Stk[A],"[")==0)
                    {
                      A--;
                    }
                  if(str_cmp(Stk[A],"=")==0)
                    {
                      A++;
                    }
                  if(str_cmp(Stk[A],"(")==0)
                    {
                      B=DataType(Stk[A-1]);
                      if(!iMatchWrd(Stk[A-1],"print")&&(B==vt_INTEGER||B==vt_SINGLE||B==vt_DOUBLE))
                        {
                          A--;
                        }
                    }
                  strcpy(Arg,"pow(");
                  B=A-1;
                  while(B>0)
                    {
                      strcpy(Arg, join(4,Stk[B]," ",Arg," "));
                      B--;
                    }
                  for(B=A; B<=i-1; B+=1)
                    {
                      strcpy(Arg, join(3,Arg," ",Stk[B]));
                    }
                  strcat(Arg,",");
                  A=i+1;
                  B=DataType(Stk[A]);
                  if((str_cmp(Stk[A+1],"(")==0 ||  str_cmp(Stk[A+1],"[")==0) && (B==vt_INTEGER||B==vt_SINGLE||B==vt_DOUBLE))
                    {
                      A++;
                    }
                  B=0;
                  while(A<=Ndx)
                    {
                      if(str_cmp(Stk[A],"[")==0)
                        {
                          B++;
                        }
                      if(str_cmp(Stk[A],"(")==0)
                        {
                          B++;
                        }
                      if(str_cmp(Stk[A],"]")==0)
                        {
                          B--;
                        }
                      if(str_cmp(Stk[A],")")==0)
                        {
                          B--;
                        }
                      if(!B)
                        {
                          break;
                        }
                      A++;
                    }
                  for(B=i+1; B<=A; B+=1)
                    {
                      strcpy(Arg, join(3,Arg," ",Stk[B]));
                    }
                  strcat(Arg,")");
                  A++;
                  while(A<=Ndx)
                    {
                      strcpy(Arg, join(3,Arg," ",Stk[A]));
                      A++;
                    }
                  break;
                }
            }
          Parse(Arg);
        }
    }
  strcpy(L_Stk_1,lcase(Stk[1]));
  strcpy(L_Stk_2,lcase(Stk[2]));
  if(str_cmp(L_Stk_1,"$dll")==0)
    {
      MakeDLL=NoMain=TRUE;
      if(IsApple)
        {
          strcpy(LD_FLAGS,"-fPIC -shared $FILE$.so");
        }
      else
        {
          strcpy(LD_FLAGS,"-fPIC -shared -Wl,-soname,$FILE$.so");
        }
      Ndx=0;
      return;
    }
  IsCallBack=0;
  if(iMatchWrd(Stk[Ndx],"callback"))
    {
      IsCallBack=1;
      Ndx--;
    }
  if(str_cmp(L_Stk_1,"open")==0)
    {
      for(A=1; A<=Ndx; A+=1)
        {
          if(iMatchWrd(Stk[A],"binary"))
            {
              break;
            }
        }
      if(A<Ndx)
        {
          A++;
          strcpy(Var1,lcase(Stk[A]));
          if(str_cmp(Var1,"new")==0)
            {
              strcpy(Stk[A-1],"binarynew");
              for(i=A+1; i<=Ndx; i+=1)
                {
                  strcpy(Stk[i-1],Stk[i]);
                }
              Ndx--;
            }
          if(str_cmp(Var1,"append")==0)
            {
              strcpy(Stk[A-1],"binaryappend");
              for(i=A+1; i<=Ndx; i+=1)
                {
                  strcpy(Stk[i-1],Stk[i]);
                }
              Ndx--;
            }
          if(str_cmp(Var1,"input")==0)
            {
              strcpy(Stk[A-1],"binaryinput");
              for(i=A+1; i<=Ndx; i+=1)
                {
                  strcpy(Stk[i-1],Stk[i]);
                }
              Ndx--;
            }
          if(str_cmp(Var1,"output")==0)
            {
              strcpy(Stk[A-1],"binaryoutput");
              for(i=A+1; i<=Ndx; i+=1)
                {
                  strcpy(Stk[i-1],Stk[i]);
                }
              Ndx--;
            }
        }
    }
  if(str_cmp(L_Stk_1,"option")==0 &&  str_cmp(L_Stk_2,"base")==0)
    {
      OptionBase=VAL(Stk[3]);
      Ndx=0;
      return;
    }
  if(str_cmp(L_Stk_1,"dim")==0)
    {
      if(str_cmp(L_Stk_2,"shared")==0 ||  str_cmp(L_Stk_2,"dynamic")==0 ||  str_cmp(L_Stk_2,"raw")==0 ||  str_cmp(L_Stk_2,"local")==0 ||  str_cmp(L_Stk_2,"auto")==0 ||  str_cmp(L_Stk_2,"register")==0 ||  str_cmp(L_Stk_2,"static")==0)
        {
          strcpy(Stk[1],L_Stk_2);
          strcpy(L_Stk_1,L_Stk_2);
          for(i=3; i<=Ndx; i+=1)
            {
              strcpy(Stk[i-1],Stk[i]);
            }
          Ndx--;
        }
    }
  if(str_cmp(L_Stk_1,"public")==0)
    {
      if(str_cmp(L_Stk_2,"function")==0 ||  str_cmp(L_Stk_2,"sub")==0)
        {
          strcpy(Stk[1],L_Stk_2);
          strcpy(L_Stk_1,L_Stk_2);
          for(i=3; i<=Ndx; i+=1)
            {
              strcpy(Stk[i-1],Stk[i]);
            }
          Ndx--;
        }
    }
  if(str_cmp(L_Stk_1,"private")==0)
    {
      if(str_cmp(L_Stk_2,"function")==0 ||  str_cmp(L_Stk_2,"sub")==0)
        {
          Use_Static=TRUE;
          strcpy(Stk[1],L_Stk_2);
          strcpy(L_Stk_1,L_Stk_2);
          for(i=3; i<=Ndx; i+=1)
            {
              strcpy(Stk[i-1],Stk[i]);
            }
          Ndx--;
        }
    }
  if(str_cmp(L_Stk_1,"onexit")==0)
    {
      if(str_cmp(L_Stk_2,"sub")==0)
        {
          Use_ExitCode=TRUE;
          ExitNdx++;
          strcpy(ExitSub[ExitNdx],Stk[3]);
          strcpy(Stk[1],L_Stk_2);
          strcpy(L_Stk_1,L_Stk_2);
          for(i=3; i<=Ndx; i+=1)
            {
              strcpy(Stk[i-1],Stk[i]);
            }
          Ndx--;
        }
    }
  if(str_cmp(L_Stk_1,"onstart")==0)
    {
      if(str_cmp(L_Stk_2,"sub")==0)
        {
          Use_StartupCode=TRUE;
          StartNdx++;
          strcpy(StartSub[StartNdx],Stk[3]);
          strcpy(Stk[1],L_Stk_2);
          strcpy(L_Stk_1,L_Stk_2);
          for(i=3; i<=Ndx; i+=1)
            {
              strcpy(Stk[i-1],Stk[i]);
            }
          Ndx--;
        }
    }
  if(str_cmp(L_Stk_1,"overloaded")==0 &&  str_cmp(L_Stk_2,"function")==0)
    {
      strcpy(Stk[1],"overloadedfunction");
      strcpy(L_Stk_1,"overloadedfunction");
      for(i=3; i<=Ndx; i+=1)
        {
          strcpy(Stk[i-1],Stk[i]);
        }
      Ndx--;
    }
  if(str_cmp(L_Stk_1,"overloadedfunction")==0 &&  str_cmp(Stk[2],"=")!=0)
    {
      OkayToSend=TRUE;
    }
  if(str_cmp(L_Stk_1,"overloaded")==0 &&  str_cmp(L_Stk_2,"sub")==0)
    {
      strcpy(Stk[1],"overloadedsub");
      for(i=3; i<=Ndx; i+=1)
        {
          strcpy(Stk[i-1],Stk[i]);
        }
      Ndx--;
    }
  if(str_cmp(L_Stk_1,"function")==0 && iMatchWrd(Stk[3],"optional"))
    {
      strcpy(Stk[1],"optfunction");
      strcpy(L_Stk_1,"optfunction");
      for(i=4; i<=Ndx; i+=1)
        {
          strcpy(Stk[i-1],Stk[i]);
        }
      Ndx--;
    }
  if(str_cmp(L_Stk_1,"optfunction")==0 &&  str_cmp(Stk[2],"=")!=0)
    {
      OkayToSend=TRUE;
    }
  if(str_cmp(L_Stk_1,"sub")==0 && iMatchWrd(Stk[3],"optional"))
    {
      strcpy(L_Stk_1,"optsub");
      strcpy(Stk[1],"optsub");
      for(i=4; i<=Ndx; i+=1)
        {
          strcpy(Stk[i-1],Stk[i]);
        }
      Ndx--;
    }
  if(str_cmp(L_Stk_1,"end")==0 &&  str_cmp(Stk[2],"=")!=0)
    {
      strcpy(Stk[1], join(2,L_Stk_1,L_Stk_2));
      Ndx=1;
    }
  if(str_cmp(L_Stk_1,"function")==0 &&  str_cmp(Stk[2],"=")!=0)
    {
      OkayToSend=TRUE;
    }
  if(str_cmp(L_Stk_1,"midstr")==0)
    {
      CommaCnt=0;
      for(i=1; i<=Ndx; i+=1)
        {
          if(str_cmp(Stk[i],",")==0)
            {
              CommaCnt++;
            }
          else if(str_cmp(Stk[i],"=")==0)
            {
              if(CommaCnt<2)
                {
                  strcpy(Stk[i],"-1,");
                }
              else
                {
                  *Stk[i]=0;
                }
              strcpy(Stk[i-1],",");
              Ndx++;
              strcpy(Stk[Ndx],")");
              break;
            }
        }
    }
  if(str_cmp(Stk[2],":")==0)
    {
      if(Ndx==2)
        {
          strcpy(Stk[1], join(2,ucase(Stk[1]),":"));
          Ndx=1;
          return;
        }
    }
  if(str_cmp(L_Stk_1,"case")==0 &&  str_cmp(L_Stk_2,"else")==0)
    {
      Ndx=1;
      strcpy(Stk[1],"caseelse");
    }
  for(i=1; i<=Ndx; i+=1)
    {
      if(iMatchWrd(Stk[i],"let"))
        {
          for(j=i+1; j<=Ndx; j+=1)
            {
              strcpy(Stk[j-1],Stk[j]);
            }
          Ndx--;
        }
    }
  if(str_cmp(Stk[Ndx],"*")==0)
    {
      strcpy(Stk[Ndx-1], join(2,Stk[Ndx-1],"*"));
      Ndx--;
    }
  if(TestState==TRUE)
    {
      if(LastCmd==0)
        {
          if(str_cmp(Stk[1],"*")==0)
            {
              strcpy(Z,Clean(Stk[2]));
            }
          else
            {
              strcpy(Z,Clean(Stk[1]));
            }
          if(str_cmp(left(Z,1),"*")==0)
            {
              strcpy(Z,mid(Z,2));
            }
          i=inchr(Z,".");
          if(i==0)
            {
              i=instr_b(Z,"->");
            }
          if(i>0)
            {
              if(WithCnt)
                {
                  strcpy(Z,WithVar[WithCnt]);
                }
              else
                {
                  strcpy(Z,left(Z,i-1));
                }
            }
          if(inchr(Z,"["))
            {
              strcpy(Z,extract(Z,"["));
            }
          if(CheckLocal(Z, &j)==vt_UNKNOWN)
            {
              if(CheckGlobal(Z, &j)==vt_UNKNOWN)
                {
                  strcpy(Z,lcase(Z));
                  if(str_cmp(Stk[2],"=")==0 &&  str_cmp(Z,"functionreturn")!=0 &&  str_cmp(Z,"bcx_retstr")!=0 &&  str_cmp(Z,"end")!=0)
                    {
                      Warning(join(6,"Assignment before Declaration in Line ",str(ModuleLineNos[ModuleNdx])," in Module: ",trim(Modules[ModuleNdx]),": ",Src));
                    }
                }
            }
        }
    }
}


void FuncSubDecs1 (char *s)
{
  int     i;
  int     j;
  if(iMatchWrd(Stk[1],s))
    {
      if(DataType(Stk[2])==vt_STRVAR)
        {
          Abort(join(3,"Invalid ",s,"name"));
        }
    }
  for(i=1; i<=Ndx; i+=1)
    {
      if(str_cmp(Stk[i],"[")==0 &&  str_cmp(Stk[i+1],"]")==0)
        {
          if(iMatchWrd(Stk[i+2],"as"))
            {
              strcpy(Stk[i+3], join(2,Stk[i+3],"*"));
            }
          else if(str_cmp(Stk[i+2],"[")==0)
            {
              j=i-1;
              while(i<=Ndx)
                {
                  if(iMatchWrd(Stk[i],"as"))
                    {
                      break;
                    }
                  if(iMatchRgt(Stk[j],"]")&&inchr(",)=",Stk[i]))
                    {
                      break;
                    }
                  strcpy(Stk[j], join(2,Stk[j],Stk[i]));
                  *Stk[i++]=0;
                }
              continue;
            }
          else
            {
              if(DataType(Stk[i-1])==vt_STRVAR)
                {
                  strcpy(Stk[i-1], join(2,Stk[i-1],"[][65535]"));
                }
              strcpy(Stk[i-1], join(2,"*",Stk[i-1]));
            }
          *Stk[i++]=0;
          *Stk[i]=0;
        }
    }
  RemEmptyTokens();
  IsExported=FALSE;
  if(iMatchWrd(Stk[Ndx],"export"))
    {
      Ndx--;
      IsExported=TRUE;
      if(UseStdCall)
        {
          strcpy(CallType,"__attribute__((stdcall)) ");
        }
      else
        {
          strcpy(CallType,"__attribute__((cdecl)) ");
        }
    }
}


void RemEmptyTokens (void)
{
  int     i;
  int     j;
  for(i=1; i<=Ndx; i+=1)
    {
      if(!*Stk[i])
        {
          j=i;
          while(!*Stk[j]&&(j<Ndx))
            {
              j++;
            }
          if(!*Stk[j])
            {
              break;
            }
          strcpy(Stk[i],Stk[j]);
          *Stk[j]=0;
        }
    }
  Ndx=i-1;
}


void FuncSubDecs2 (char *s, int method)
{
  if(iMatchWrd(Stk[1],s))
    {
      if(iMatchWrd(Stk[Ndx-1],"as"))
        {
          Abort(join(2,"Attempted type assignment to ",s));
        }
      VarCode.IsPtrFlag=0;
      CurrentFuncType=vt_VOID;
    }
  else
    {
      if(iMatchWrd(Stk[Ndx-1],"as"))
        {
          CurrentFuncType=CheckType(Stk[Ndx]);
          strcpy(VarCode.Token,Stk[2]);
          strcpy(VarCode.AsToken,Stk[Ndx]);
          VarCode.IsPtrFlag=tally(Stk[Ndx],"*");
          *Stk[Ndx]=0;
          *Stk[Ndx-1]=0;
          Ndx--;
          Ndx--;
        }
      else
        {
          CurrentFuncType=DataType(Stk[2]);
          strcpy(VarCode.Token,Stk[2]);
          VarCode.IsPtrFlag=tally(Stk[2],"*");
          *VarCode.AsToken=0;
        }
    }
  strcpy(VarCode.Proto," (");
  strcpy(VarCode.Header," (");
  *VarCode.Functype=0;
  VarCode.Method=method;
  VarCode.VarNo=CurrentFuncType;
  GetVarCode( &VarCode);
}


void FuncSubDecs3 (VARCODE* varcode)
{
  if(*Stk[Ndx-1]==46)
    {
      strcat(varcode->Header,"...");
    }
  strcpy(varcode->Header,rtrim(varcode->Header));
  if(iMatchRgt(varcode->Header,","))
    {
      midstr(varcode->Header,strlen(varcode->Header),-1,")");
    }
  else
    {
      strcat(varcode->Header,")");
    }
  strcpy(varcode->Header,replace(varcode->Header,"()","(void)"));
  strcpy(varcode->Header, join(3,varcode->Functype,varcode->Token,varcode->Header));
  if(varcode->Method==2)
    {
      if(*Stk[Ndx-1]==46)
        {
          strcat(varcode->Proto,"...");
        }
      strcpy(varcode->Proto,rtrim(varcode->Proto));
      if(iMatchRgt(varcode->Proto,","))
        {
          midstr(varcode->Proto,strlen(varcode->Proto),-1,")");
        }
      else
        {
          strcat(varcode->Proto,")");
        }
      strcpy(varcode->Proto,replace(varcode->Proto,"()","(void)"));
      strcpy(varcode->Proto, join(4,varcode->Functype,varcode->Token,varcode->Proto,";"));
    }
  if(IsExported)
    {
      strcpy(varcode->Proto, join(2,"C_EXPORT ",varcode->Proto));
      strcpy(varcode->Header, join(2,"C_EXPORT ",varcode->Header));
    }
}


void AddTypeDefs (char *TypeName, int TDef)
{
  TypeDefsCnt++;
  if(TypeDefsCnt==MaxTypes)
    {
      Abort("Exceeded TYPE Limits.");
    }
  strcpy(TypeDefs[TypeDefsCnt].VarName,TypeName);
  TypeDefs[TypeDefsCnt].TypeofDef=TDef;
  TypeDefs[TypeDefsCnt].EleCnt=0;
}


int DefsID (char *ZZ)
{
  int     i;
  if(TypeDefsCnt>0)
    {
      for(i=1; i<=TypeDefsCnt; i+=1)
        {
          if(str_cmp(ZZ,TypeDefs[i].VarName)==0)
            {
              return i;
            }
        }
    }
  return 0;
}


void GetTypeInfo (char *stk, int* IsPointer, int* UdtIdx, int* vtCode)
{
  char Var1[2048];
  (*IsPointer)=tally(stk,"*");
  strcpy(Var1,RemoveStr(stk,"*"));
  if(str_cmp(right(Var1,6),"_CLASS")==0)
    {
      strcpy(Var1,left(Var1,strlen(Var1)-6));
    }
  (*vtCode)=CheckType(Var1);
  if((*vtCode)==vt_UNKNOWN)
    {
      AddTypeDefs(Var1,vt_UDT);
      (*vtCode)=vt_UDT;
    }
  (*UdtIdx)=0;
  if((*vtCode)==vt_STRUCT||(*vtCode)==vt_UNION||(*vtCode)==vt_UDT)
    {
      (*UdtIdx)=DefsID(Var1);
    }
}


void AddTypedefElement (int WorkingTypeDefsCnt, int ElType, char *EName, char *EType, int EPtr)
{
   UserTypeDefs*  TD;
  TD= &(TypeDefs[WorkingTypeDefsCnt]);
  if(TD->EleCnt==MaxElements)
    {
      Abort("Exceeded TYPE Element Limits.");
    }
  TD->Elements[TD->EleCnt].ElementType=ElType;
  TD->Elements[TD->EleCnt].ElementDynaPtr=EPtr;
  if(ElType==vt_STRUCT||ElType==vt_UNION||ElType==vt_UDT)
    {
      TD->Elements[TD->EleCnt].ElementID=DefsID(EType);
    }
  else
    {
      TD->Elements[TD->EleCnt].ElementID=0;
    }
  strcpy(TD->Elements[TD->EleCnt].ElementName,EName);
  TD->EleCnt=1+TD->EleCnt;
}


char * GetElement (int StartStk, int* vt, int* dms, int id)
{
  char *BCX_RetStr={0};
  int     BC=0;
  int     i;
  char ZZ[2048];
  for(i=StartStk+1; i<=Ndx; i+=1)
    {
      if(str_cmp(Stk[i],"[")==0)
        {
          BC++;
        }
      else if(str_cmp(Stk[i],"]")==0)
        {
          BC--;
        }
      else if(BC==0)
        {
          if(iMatchLft(Stk[i],"->")||*Stk[i]==46)
            {
              strcpy(ZZ,Clean(Stk[i]));
              RemoveAll(ZZ,".->(*)",1);
              (*vt)=GetElementInfo( &id,dms,ZZ);
              if((*vt)!=vt_STRUCT&&(*vt)!=vt_UNION)
                {
                  break;
                }
            }
        }
    }
  if((*vt)==vt_UDT||(*vt)==vt_UNION||(*vt)==vt_STRUCT)
    {
      strcpy(ZZ,TypeDefs[id].VarName);
    }
  else
    {
      strcpy(ZZ,GetVarTypeName(*vt));
    }
  BCX_RetStr=BCX_TmpStr(strlen(ZZ));
  strcpy(BCX_RetStr,ZZ);
  return BCX_RetStr;
}


int GetElementInfo (int* DefID, int* EPtr, char *Elename)
{
  int     i;
  int     id;
  id=(*DefID);
  for(i=0; i<=TypeDefs[id].EleCnt-1; i+=1)
    {
      if(str_cmp(Elename,TypeDefs[id].Elements[i].ElementName)==0)
        {
          (*DefID)=TypeDefs[id].Elements[i].ElementID;
          (*EPtr)=TypeDefs[id].Elements[i].ElementDynaPtr;
          return TypeDefs[id].Elements[i].ElementType;
        }
    }
  return 0;
}


void HandleNonsense (void)
{
  int     i;
  for(i=1; i<=Ndx; i+=1)
    {
      if(iMatchWrd(Stk[i],"as"))
        {
          strcpy(Stk[i-1],Clean(Stk[i-1]));
        }
      if(OptionBase)
        {
          if(str_cmp(Stk[i],"[")==0)
            {
              strcpy(Stk[i+1], join(3,ltrim(str(OptionBase)),"+",Stk[i+1]));
            }
        }
    }
}


void ValidVar (char *v)
{
  char *ZZ;
  ZZ=(char*)calloc(256+65535,1);
  if(!isalpha(*v)&&*v!=95)
    {
      if(!iMatchLft(v,"(*"))
        {
          Abort("Invalid String Variable Name");
        }
    }
  if(RestrictedWords(v)&&TestState)
    {
      strcpy(ZZ, join(3,"Variable ",v," on line"));
      strcpy(ZZ, join(5,ZZ,str(ModuleLineNos[ModuleNdx])," in Module: ",trim(Modules[ModuleNdx])," is a Restricted Word"));
      Warning(ZZ);
    }
  if(ZZ)free(ZZ);
}


void PointerFix (void)
{
  strcpy(Stk[Ndx-1], join(2,Stk[Ndx-1],Stk[Ndx]));
  Stk[Ndx][0]=0;
  Ndx--;
  while(tally(Stk[Ndx],"*")==strlen(Stk[Ndx]))
    {
      strcpy(Stk[Ndx-1], join(2,Stk[Ndx-1],Stk[Ndx]));
      Stk[Ndx][0]=0;
      Ndx--;
    }
}


void DimDynaString (char *SVar, int DG, int s)
{
  int     A;
  char DS[2048];
  strcpy(DS, join(5,"if(",SVar,")free(",SVar,");"));
  if(InFunc&&(IsLocal||IsDim||IsRaw||IsAuto||IsRegister)&&DG==0)
    {
      LocalDynaCnt++;
      strcpy(DynaStr[LocalDynaCnt],DS);
      if(IsAuto)
        {
          fprintf(Outfile,"%s%s%s%s\n",Scoot,"char *",SVar,";");
        }
      else if(IsRegister)
        {
          fprintf(Outfile,"%s%s%s%s\n",Scoot,"register char *",SVar,";");
        }
      else
        {
          fprintf(Outfile,"%s%s%s%s\n",Scoot,"char *",SVar,";");
        }
      AddLocal(SVar,vt_CHAR,0,"",1,0,0);
    }
  else
    {
      if(Use_GenFree)
        {
          GlobalDynaCnt++;
          strcpy(GlobalDynaStr[GlobalDynaCnt],DS);
        }
      if(DG==2)
        {
          AddGlobal(SVar,vt_CHAR,0,"",1,0,1,0);
        }
      else
        {
          if(s)
            {
              AddGlobal(SVar,vt_CHAR,0,"",1,0,2,0);
            }
          else
            {
              AddGlobal(SVar,vt_CHAR,0,"",1,0,0,0);
            }
        }
    }
  if(DG!=2)
    {
      fprintf(Outfile,"%s%s%s",Scoot,SVar,"=(char*)calloc(256+");
      for(A=4; A<=Ndx; A+=1)
        {
          fprintf(Outfile,"%s",Clean(Stk[A]));
        }
      fprintf(Outfile,"%s\n",",1);");
    }
}


int SubFuncTest (void)
{
  if(iMatchWrd(Stk[2],"function")||iMatchWrd(Stk[2],"sub"))
    {
      return 1;
    }
  return 0;
}


int DimSubFunc (int IsDynamic)
{
  int     i;
  char lszTmp[2048];
  int     StartPoint=3;
  int     Funptr=0;
  *lszTmp=0;
  if(iMatchWrd(Stk[Ndx],"stdcall"))
    {
      strcpy(CallType,"__attribute__((stdcall)) ");
      Ndx--;
      IsStdFunc=TRUE;
    }
  else
    {
      strcpy(CallType,"__attribute__((cdecl)) ");
      IsStdFunc=FALSE;
    }
  static   struct _functionParse  FP;
  memset(&FP,0,sizeof(FP));
  SepFuncArgs(3, &FP,TRUE);
  StartPoint=_MAX_(FP.CommaPos[0],3);
  if(!InTypeDef)
    {
      SFPOINTER=TRUE;
      if(FP.NumArgs==0)
        {
          i=_MIN_(FP.CommaPos[1]+1,Ndx);
        }
      else
        {
          i=_MIN_(FP.CommaPos[FP.NumArgs]+1,Ndx);
        }
      if(str_cmp(Stk[i],"=")==0)
        {
          *Stk[i++]=0;
          while(!iMatchWrd(Stk[i],"as")&&i<=Ndx)
            {
              strcat(lszTmp,Stk[i]);
              *Stk[i++]=0;
            }
          RemoveAll(lszTmp,"{}",1);
          if(lszTmp[0]!=0)
            {
              RemEmptyTokens();
            }
        }
      if(!InNameSpace)
        {
          fprintf(FP4,"%s%s\n",MakeDecProto( &FP),";");
        }
      SFPOINTER=FALSE;
      Ndx=StartPoint;
      *Stk[2]=0;
      if(lszTmp[0]!=0)
        {
          strcpy(Stk[Ndx++],"=");
          strcpy(Stk[Ndx++],"{");
          strcpy(Stk[Ndx++],Clean(lszTmp));
          strcpy(Stk[Ndx++],"}");
        }
      strcpy(Stk[Ndx++],"as");
      strcpy(Stk[Ndx], join(3,Clean(Stk[3]),"_TYPE",stringx(Funptr,42)));
      RemEmptyTokens();
      return FALSE;
    }
  else
    {
      if(iMatchWrd(Stk[2],"constructor")||iMatchWrd(Stk[2],"destructor"))
        {
          fprintf(Outfile,"%s%s%s%s\n",LF,Scoot,MakeDecProto( &FP),";");
        }
      else if(Use_Virtual)
        {
          fprintf(Outfile,"%s%s%s%s%s\n",Scoot,"virtual ",MakeDecProto( &FP),vproc,";");
          Use_Virtual=FALSE;
        }
      else
        {
          fprintf(Outfile,"%s%s%s\n",Scoot,MakeDecProto( &FP),";");
        }
    }
  return TRUE;
}


void Emit (void)
{
  int     HasStorage=0;
  int     A;
  int     B;
  int     i;
  int     j;
  int     Tmp;
  int     FuncRetnFlag;
  int     IsPointer=0;
  int     VType;
  int     id=0;
  int     k=0;
  int     vt=0;
  char Arg[2048];
  char CVar[2048];
  char Keyword[2048];
  char lszTmp[2048];
  char Var1[2048];
  char *ZZ;
  ZZ=(char*)calloc(256+65535,1);
  int     IsSubOrFuncPtr;
  int     dms;
  static int     NoBreak;
  static int     NoBreak2;
  FuncRetnFlag=0;
  *lszTmp=0;
  *ZZ=0;
  strcpy(Keyword,lcase(Stk[1]));
  if(NoBreak2&&!iMatchLft(Keyword,"case")&&!iMatchWrd(Keyword,"endselect"))
    {
      NoBreak2=0;
    }

EMITAGAIN:;
  if(Ndx==0)
    {
      if(ZZ)free(ZZ);
      return;
    }
  Statements++;
  if(iMatchRgt(Stk[1],":"))
    {
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s%s\n",ucase(Stk[1]),";");
      if(ZZ)free(ZZ);
      return;
    }
  for(i=1; i<=Ndx; i+=1)
    {
      strcpy(Stk[i],replace(Stk[i],chr(-15),":"));
    }
  if((CurrentFuncType==vt_STRVAR)&&InFunc&&OkayToSend)
    {
      fprintf(Outfile,"%s%s\n",Scoot,"char *BCX_RetStr={0};");
      OkayToSend=0;
    }
  strcpy(Lookup,lcase(Stk[1]));
  for(;;)
  {
    if(str_cmp(Lookup,"fprint")==0 ||  str_cmp(Lookup,"sprint")==0)
      {
        int     IsLprint=FALSE;
        int     IsSprint=FALSE;
        if(iMatchWrd(Stk[1],"sprint"))
          {
            IsSprint=TRUE;
          }
        if(IsNumber(Stk[2]))
          {
            strcpy(Stk[2], join(2,"FP",Stk[2]));
          }
        if(IsSprint)
          {
            strcpy(Handl,Clean(Stk[2]));
          }
        else
          {
            if(str_cmp(lcase(Stk[2]),"stderr")==0)
              {
                strcpy(Handl,lcase(Stk[2]));
              }
            else
              {
                if(CheckLocal(Stk[2], &i)==vt_UNKNOWN)
                  {
                    if(CheckGlobal(Stk[2], &i)==vt_UNKNOWN)
                      {
                        AddGlobal(Stk[2],vt_FILEPTR,0,"",0,0,0,0);
                      }
                  }
                *Handl=0;
                for(i=2; i<=Ndx; i+=1)
                  {
                    if(*Stk[i]==44||*Stk[i]==59)
                      {
                        *Stk[i]=0;
                        break;
                      }
                    strcat(Handl,Stk[i]);
                    *Stk[i]=0;
                  }
                strcat(Handl,"@");
              }
          }
        *Stk[2]=0;
        *Stk[3]=0;
        if(IsSprint)
          {
            strcpy(ZZ, join(2,"s",PrintWriteFormat(0)));
            strcpy(ZZ,RemoveStr(ZZ,"\\n"));
          }
        else
          {
            strcpy(ZZ, join(2,"f",PrintWriteFormat(0)));
          }
        strcpy(ZZ, join(4,left(ZZ,8),RemoveStr(Handl,"@"),",",mid(ZZ,9)));
        fprintf(Outfile,"%s%s\n",Scoot,ZZ);
        break;
      }
    if(str_cmp(Lookup,"end")==0)
      {
        if(Ndx==1)
          {
            fprintf(Outfile,"%s%s\n",Scoot,"fflush(stdout);");
            fprintf(Outfile,"%s%s\n",Scoot,"exit(0);");
            break;
          }
        if(str_cmp(Stk[2],"=")==0)
          {
            fprintf(Outfile,"%s%s\n",Scoot,"fflush(stdout);");
            fprintf(Outfile,"%s%s",Scoot,"exit(");
            for(Tmp=3; Tmp<=Ndx; Tmp+=1)
              {
                fprintf(Outfile,"%s",Clean(Stk[Tmp]));
              }
            fprintf(Outfile,"%s\n",");");
            break;
          }
        if(iMatchWrd(Stk[2],"if"))
          {
            BumpDown();
            fprintf(Outfile,"%s%s\n",Scoot,"}");
            BumpDown();
            break;
          }
        break;
      }
    if(str_cmp(Lookup,"endif")==0)
      {
        BumpDown();
        fprintf(Outfile,"%s%s\n",Scoot,"}");
        BumpDown();
        break;
      }
    if(str_cmp(Lookup,"if")==0)
      {
        EmitIfCond("if");
        break;
      }
    if(str_cmp(Lookup,"elseif")==0)
      {
        BumpDown();
        fprintf(Outfile,"%s%s\n",Scoot,"}");
        BumpDown();
        EmitIfCond("else if");
        break;
      }
    if(str_cmp(Lookup,"for")==0)
      {
        int     FFlg=0;
        int     For1=0;
        int     For2=0;
        int     For3=0;
        int     For4=0;
        char Reg[2048];
        char xxx[2048];
        char yyy[2048];
        char zzz[2048];
        char qqq[2048];
        *Reg=0;
        *xxx=0;
        *yyy=0;
        *zzz=0;
        *qqq=0;
        for(i=Ndx; i>=1; i+=-1)
          {
            if(iMatchWrd(Stk[i],"step"))
              {
                FFlg=TRUE;
                break;
              }
          }
        if(!FFlg)
          {
            Ndx++;
            strcpy(Stk[Ndx],"step");
            Ndx++;
            strcpy(Stk[Ndx],"1");
          }
        Test=FALSE;
        for(i=1; i<=Ndx; i+=1)
          {
            if(str_cmp(Stk[i],"=")==0)
              {
                Test=TRUE;
              }
          }
        if(Test==FALSE)
          {
            Abort("Missing =");
          }
        Test=FALSE;
        for(i=1; i<=Ndx; i+=1)
          {
            if(iMatchWrd(Stk[i],"to"))
              {
                Test=TRUE;
              }
          }
        if(Test==FALSE)
          {
            Abort("Missing TO");
          }
        strcpy(Reg,lcase(Stk[2]));
        for(;;)
        {
          if(str_cmp(Reg,"int")==0 ||  str_cmp(Reg,"fint")==0)
            {
              strcpy(Reg,SPC);
              LoopLocalVar[LoopLocalCnt++]=1;
              fprintf(Outfile,"%s%s",Scoot,"  {int ");
              break;
            }
          if(str_cmp(Reg,"single")==0 ||  str_cmp(Reg,"float")==0)
            {
              strcpy(Reg,SPC);
              LoopLocalVar[LoopLocalCnt++]=1;
              fprintf(Outfile,"%s%s",Scoot,"  {float ");
              break;
            }
          if(str_cmp(Reg,"double")==0)
            {
              strcpy(Reg,SPC);
              LoopLocalVar[LoopLocalCnt++]=1;
              fprintf(Outfile,"%s%s",Scoot,"  {double ");
              break;
            }
          if(str_cmp(Reg,"ldouble")==0)
            {
              strcpy(Reg,SPC);
              LoopLocalVar[LoopLocalCnt++]=1;
              fprintf(Outfile,"%s%s",Scoot,"  {LDOUBLE ");
              break;
            }
            // case else
            {
              *Reg=0;
              LoopLocalVar[LoopLocalCnt++]=0;
            }
          break;
        }
        if(strlen(Reg))
          {
            for(j=3; j<=Ndx; j+=1)
              {
                strcpy(Stk[j-1],Stk[j]);
              }
            Ndx--;
          }
        for(i=2; i<=Ndx; i+=1)
          {
            if(str_cmp(Stk[i],"=")==0)
              {
                For1=i-1;
                break;
              }
          }
        for(i=For1+2; i<=Ndx; i+=1)
          {
            if(iMatchWrd(Stk[i],"to"))
              {
                For2=i-1;
                break;
              }
          }
        for(i=For2+2; i<=Ndx; i+=1)
          {
            if(iMatchWrd(Stk[i],"step"))
              {
                For3=i-1;
                break;
              }
          }
        For4=For3+2;
        for(i=2; i<=For1; i+=1)
          {
            strcat(xxx,Stk[i]);
          }
        for(i=For1+2; i<=For2; i+=1)
          {
            strcat(yyy,Stk[i]);
          }
        for(i=For2+2; i<=For3; i+=1)
          {
            strcat(zzz,Stk[i]);
          }
        for(i=For4; i<=Ndx; i+=1)
          {
            strcat(qqq,Stk[i]);
          }
        strcpy(xxx,Clean(xxx));
        strcpy(yyy,Clean(yyy));
        strcpy(zzz,Clean(zzz));
        strcpy(qqq,Clean(qqq));
        if(str_cmp(Reg,SPC)==0)
          {
            fprintf(Outfile,"%s%s\n",xxx,";");
          }
        *Reg=0;
        if(IsNumberEx(qqq))
          {
            if(str_cmp(left(qqq,1),"-")==0)
              {
                fprintf(Outfile,"%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",Scoot,"for(",Reg,xxx,"=",yyy,"; ",xxx,">=",zzz,"; ",xxx,"+=",qqq,")");
              }
            else
              {
                fprintf(Outfile,"%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",Scoot,"for(",Reg,xxx,"=",yyy,"; ",xxx,"<=",zzz,"; ",xxx,"+=",qqq,")");
              }
          }
        else
          {
            fprintf(Outfile,"%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",Scoot,"for(",Reg,xxx,"=",yyy,"; ",qqq,">=0 ? ",xxx,"<=",zzz," : ",xxx,">=",zzz,"; ",xxx,"+=",qqq,")");
          }
        BumpUp();
        fprintf(Outfile,"%s%s\n",Scoot,"{");
        BumpUp();
        break;
      }
    if(str_cmp(Lookup,"next")==0)
      {
        BumpDown();
        fprintf(Outfile,"%s%s\n",Scoot,"}");
        if(LoopLocalVar[--LoopLocalCnt])
          {
            fprintf(Outfile,"%s%s\n",Scoot,"}");
          }
        if(LoopLocalCnt<0)
          {
            Abort("Next without For");
          }
        BumpDown();
        break;
      }
    if(str_cmp(Lookup,"do")==0)
      {
        fprintf(Outfile,"%s%s\n",Scoot,"for(;;)");
        BumpUp();
        fprintf(Outfile,"%s%s\n",Scoot,"{");
        BumpUp();
        break;
      }
    if(str_cmp(Lookup,"loop")==0)
      {
        BumpDown();
        fprintf(Outfile,"%s%s\n",Scoot,"}");
        BumpDown();
        break;
      }
    if(str_cmp(Lookup,"caseelse")==0)
      {
        CaseElseFlag[Pusher]=TRUE;
        if(CaseFlag)
          {
            if(NoBreak2==0)
              {
                fprintf(Outfile,"%s%s\n",Scoot,"break;");
              }
            BumpDown();
            fprintf(Outfile,"%s%s\n",Scoot,"}");
            fprintf(Outfile,"%s%s\n",Scoot,"// case else");
            fprintf(Outfile,"%s%s\n",Scoot,"{");
            BumpUp();
          }
        break;
      }
    if(str_cmp(Lookup,"endselect")==0)
      {
        if(CaseFlag)
          {
            BumpDown();
            fprintf(Outfile,"%s%s\n",Scoot,"}");
          }
        BumpDown();
        if(CaseElseFlag[Pusher]==0||NoBreak2==0)
          {
            fprintf(Outfile,"%s%s\n",Scoot,"break;");
          }
        BumpDown();
        fprintf(Outfile,"%s%s\n",Scoot,"}");
        NoBreak2=CaseElseFlag[Pusher]=0;
        Pop(CaseVar);
        break;
      }
    if(str_cmp(Lookup,"else")==0)
      {
        BumpDown();
        fprintf(Outfile,"%s%s\n",Scoot,"}");
        BumpDown();
        fprintf(Outfile,"%s%s\n",Scoot,"else");
        BumpUp();
        fprintf(Outfile,"%s%s\n",Scoot,"{");
        BumpUp();
        break;
      }
    if(str_cmp(Lookup,"case")==0)
      {
        for(i=2; i<=Ndx; i+=1)
          {
            if(str_cmp(Stk[i],"%")==0)
              {
                strcpy(Stk[i]," % ");
              }
            if(str_cmp(Stk[i],"!=")==0)
              {
                strcpy(Stk[i],"<>");
              }
            if(str_cmp(Stk[i],"!")==0 &&  str_cmp(Stk[i+1],"=")==0)
              {
                strcpy(Stk[i],"<>");
                *Stk[i+1]=0;
              }
            if(isalpha(Stk[i][0]))
              {
                strcat(Stk[i]," ");
              }
          }
        *szTmp=0;
        Test=FALSE;
        if(DataType(CaseVar)==vt_STRVAR)
          {
            Test=TRUE;
          }
        i=0;
        for(A=2; A<=Ndx; A+=1)
          {
            if(inchr("([",Stk[A]))
              {
                i++;
              }
            if(inchr(")]",Stk[A]))
              {
                i--;
              }
            if(i)
              {
                strcat(szTmp,Stk[A]);
                continue;
              }
            if(str_cmp(Stk[A],",")==0)
              {
                if(!inchr("<>=",Stk[A+1]))
                  {
                    strcpy(szTmp, join(4,szTmp," or ",CaseVar,"="));
                  }
                else
                  {
                    strcpy(szTmp, join(3,szTmp," or ",CaseVar));
                  }
                *Stk[A]=0;
                continue;
              }
            if(str_cmp(Stk[A],"&&")==0)
              {
                strcpy(szTmp, join(3,szTmp," and ",CaseVar));
                *Stk[A]=0;
              }
            else if(str_cmp(Stk[A],"||")==0)
              {
                strcpy(szTmp, join(3,szTmp," or ",CaseVar));
                *Stk[A]=0;
              }
            else
              {
                strcat(szTmp,Stk[A]);
              }
          }
        if(CaseFlag==0)
          {
            NoBreak=0;
          }
        if(CaseFlag)
          {
            if(NoBreak==0)
              {
                if(NoBreak2==0)
                  {
                    fprintf(Outfile,"%s%s\n",Scoot,"break;");
                  }
              }
            BumpDown();
            fprintf(Outfile,"%s%s\n",Scoot,"}");
            BumpDown();
          }
        CaseFlag=TRUE;
        if(iMatchLft(CaseVar," BAND "))
          {
            NoBreak=1;
            strcpy(Src, join(4,"IF ",szTmp,CaseVar," Then "));
          }
        else
          {
            if(inchr("<>=",szTmp)&&!IsQuoted(szTmp))
              {
                strcpy(Src, join(4,"IF ",CaseVar,szTmp," Then "));
              }
            else
              {
                strcpy(Src, join(5,"IF ",CaseVar," = ",szTmp," Then "));
              }
          }
        Parse(Src);
        Emit();
        break;
      }
    if(str_cmp(Lookup,"delay")==0)
      {
        *lszTmp=0;
        for(i=2; i<=Ndx; i+=1)
          {
            strcat(lszTmp,Clean(Stk[i]));
          }
        fprintf(Outfile,"%s%s%s%s\n",Scoot,"sleep(",lszTmp,");");
        break;
      }
    if(str_cmp(Lookup,"qsortidx")==0)
      {
        *lszTmp=0;
        strcpy(Var,Clean(Stk[2]));
        for(i=4; i<=Ndx-4; i+=1)
          {
            strcat(lszTmp,Stk[i]);
          }
        strcpy(lszTmp,Clean(lszTmp));
        fprintf(Outfile,"%s%s%s%s\n",Scoot,"Key = ",Stk[Ndx],";");
        if(str_cmp(Var,"0")!=0)
          {
            fprintf(Outfile,"%s%s\n",Scoot,"int iDx;");
            fprintf(Outfile,"%s%s%s%s",Scoot,"for(iDx=0; iDx<",lszTmp,"; iDx+=1) ");
            fprintf(Outfile,"%s%s\n",Var,"[iDx]=iDx;");
          }
        if(!inchr(Stk[Ndx-2],"."))
          {
            Use_Idxqsort=TRUE;
            fprintf(Outfile,"%s%s%s%s\n",Scoot,"pppStr = ",Clean(Stk[Ndx-2]),";");
            fprintf(Outfile,"%s%s%s%s%s%s\n",Scoot,"qsort(",Var,",",lszTmp,",sizeof(int),IdxCompare);");
          }
        else
          {
            char Stptr[2048];
            char StMem[2048];
            char StName[2048];
            strcpy(StMem,remain(Clean(Stk[Ndx-2]),"."));
            strcpy(Stptr,extract(Stk[Ndx-2],"."));
            if(CheckLocal(Stptr, &i)!=vt_UNKNOWN)
              {
                strcpy(StName,TypeDefs[LocalVars[i].VarDef].VarName);
              }
            else if(CheckGlobal(Stptr, &i)!=vt_UNKNOWN)
              {
                strcpy(StName,TypeDefs[GlobalVars[i].VarDef].VarName);
              }
            if(str_cmp(Var,"0")!=0)
              {
                Use_IdxqsortSt=TRUE;
                fprintf(Outfile,"%s%s%s%s%s%s%s%s\n",Scoot,"cmp1 =(char*)(",Stptr,") + offsetof(",StName,",",StMem,");");
                fprintf(Outfile,"%s%s%s%s\n",Scoot,"StructSize = sizeof(",StName,");");
                fprintf(Outfile,"%s%s%s%s%s%s\n",Scoot,"qsort(",Var,",",lszTmp,",sizeof(int),IdxCompareSt);");
              }
            else
              {
                Use_PtrqsortSt=TRUE;
                fprintf(Outfile,"%s%s%s%s%s%s\n",Scoot,"OffSet = offsetof(",StName,",",StMem,");");
                fprintf(Outfile,"%s%s%s%s%s%s%s%s\n",Scoot,"qsort(",Stptr,",",lszTmp,",sizeof(",StName,"),PtrCompareSt);");
              }
          }
        break;
      }
    if(str_cmp(Lookup,"qsort")==0)
      {
        int     QST=0;
        int     order=0;
        if(iMatchWrd(Stk[2],"dynamic"))
          {
            QST=TRUE;
            for(j=3; j<=Ndx; j+=1)
              {
                strcpy(Stk[j-1],Stk[j]);
              }
            Ndx--;
          }
        if(str_cmp(lcase(Stk[Ndx]),"ascending")==0)
          {
            order=2;
            Ndx--;
            Ndx--;
          }
        if(str_cmp(lcase(Stk[Ndx]),"descending")==0)
          {
            order=1;
            Ndx--;
            Ndx--;
          }
        if(order==0)
          {
            order=2;
          }
        *lszTmp=0;
        for(i=4; i<=Ndx; i+=1)
          {
            strcat(lszTmp,Stk[i]);
          }
        strcpy(Var,Clean(Stk[2]));
        vt=DataType(Stk[2]);
        if(vt!=vt_STRVAR&&vt!=vt_INTEGER&&vt!=vt_SINGLE&&vt!=vt_DOUBLE)
          {
            vt=CheckType(Stk[2]);
          }
        fprintf(Outfile,"%s%s%s%s%s",Scoot,"qsort(",Var,",",Clean(lszTmp));
        for(;;)
        {
          if(vt==vt_STRVAR)
            {
              if(!QST)
                {
                  if(order==1)
                    {
                      fprintf(Outfile,"%s%s%s\n",",sizeof(",Var,"[0]),StrCompareD);");
                      Use_Strqsortd=TRUE;
                    }
                  else
                    {
                      fprintf(Outfile,"%s%s%s\n",",sizeof(",Var,"[0]),StrCompareA);");
                      Use_Strqsorta=TRUE;
                    }
                }
              else
                {
                  if(order==1)
                    {
                      fprintf(Outfile,"%s%s%s\n",",sizeof(",Var,"[0]),DynStrCompareD);");
                      Use_DynStrqsortd=TRUE;
                    }
                  else
                    {
                      fprintf(Outfile,"%s%s%s\n",",sizeof(",Var,"[0]),DynStrCompareA);");
                      Use_DynStrqsorta=TRUE;
                    }
                }
              break;
            }
          if(vt==vt_INTEGER)
            {
              if(order==1)
                {
                  fprintf(Outfile,"%s\n",",sizeof(int),NumCompareDint);");
                  Use_Numqsortdint=TRUE;
                }
              else
                {
                  fprintf(Outfile,"%s\n",",sizeof(int),NumCompareAint);");
                  Use_Numqsortaint=TRUE;
                }
              break;
            }
          if(vt==vt_SINGLE)
            {
              if(order==1)
                {
                  fprintf(Outfile,"%s\n",",sizeof(float),NumCompareDfloat);");
                  Use_Numqsortdfloat=TRUE;
                }
              else
                {
                  fprintf(Outfile,"%s\n",",sizeof(float),NumCompareAfloat);");
                  Use_Numqsortafloat=TRUE;
                }
              break;
            }
          if(vt==vt_DOUBLE)
            {
              if(order==1)
                {
                  fprintf(Outfile,"%s\n",",sizeof(double),NumCompareDdouble);");
                  Use_Numqsortddouble=TRUE;
                }
              else
                {
                  fprintf(Outfile,"%s\n",",sizeof(double),NumCompareAdouble);");
                  Use_Numqsortadouble=TRUE;
                }
              break;
            }
            // case else
            {
              if(order==1)
                {
                  fprintf(Outfile,"%s\n",",sizeof(int),NumCompareDint);");
                  Use_Numqsortdint=TRUE;
                }
              else
                {
                  fprintf(Outfile,"%s\n",",sizeof(int),NumCompareAint);");
                  Use_Numqsortaint=TRUE;
                }
            }
          break;
        }
        break;
      }
    if(str_cmp(Lookup,"endprogram")==0)
      {
        fprintf(Outfile,"%s\n","  return 0;         //  End of main program");
        fprintf(Outfile,"%s\n","}\n\n");
        EndOfProgram=1;
        break;
      }
    if(str_cmp(Lookup,"~ifndef")==0)
      {
        strcpy(InIfDef,"#ifndef ");
        for(i=2; i<=Ndx; i+=1)
          {
            strcpy(InIfDef, join(3,InIfDef,Stk[i]," "));
          }
        strcpy(InIfDef,trim(InIfDef));
        if(InFunc||InMain)
          {
            fprintf(Outfile,"%s\n",InIfDef);
          }
        else
          {
            fprintf(FP6,"%s\n",InIfDef);
          }
        break;
      }
    if(str_cmp(Lookup,"~if")==0)
      {
        strcpy(InIfDef,"#if defined ");
        for(i=2; i<=Ndx; i+=1)
          {
            strcpy(InIfDef, join(3,InIfDef,Stk[i]," "));
          }
        strcpy(InIfDef,trim(InIfDef));
        strcpy(ConstLastDef,InIfDef);
        if(InFunc)
          {
            if(Outfile==FP3)
              {
                fprintf(Outfile,"%s\n","// FP3");
              }
            if(Outfile==FP2)
              {
                fprintf(Outfile,"%s\n","// FP2");
              }
            fprintf(Outfile,"%s%s\n",InIfDef,"// OUTFILE");
            strcpy(InIfDef,"FP3");
          }
        else if(InMain)
          {
            fprintf(Outfile,"%s%s\n",InIfDef,"// --FP2--");
          }
        break;
      }
    if(str_cmp(Lookup,"~else")==0)
      {
        strcpy(InIfDef,"#else");
        strcpy(ConstLastDef,InIfDef);
        if(InFunc||InMain)
          {
            fprintf(Outfile,"%s\n",InIfDef);
          }
        else
          {
            fprintf(FP6,"%s\n",InIfDef);
          }
        break;
      }
    if(str_cmp(Lookup,"~elseif")==0)
      {
        strcpy(InIfDef,"#elif defined ");
        for(i=2; i<=Ndx; i+=1)
          {
            strcpy(InIfDef, join(3,InIfDef,Stk[i]," "));
          }
        strcpy(InIfDef,trim(InIfDef));
        strcpy(ConstLastDef,InIfDef);
        if(InFunc||InMain)
          {
            fprintf(Outfile,"%s\n",InIfDef);
          }
        else
          {
            fprintf(FP6,"%s\n",InIfDef);
          }
        break;
      }
    if(str_cmp(Lookup,"~endif")==0)
      {
        if(str_cmp(InIfDef,"FP3")==0)
          {
            fprintf(FP3,"%s\n","#endif  // FP3");
          }
        else
          {
            fprintf(Outfile,"%s\n","#endif  // Main");
          }
        if(str_cmp(ConstLastDef,"FP6")==0)
          {
            fprintf(FP6,"%s\n","#endif  // FP6");
          }
        strcpy(InIfDef,"#endif  // other");
        if(InConditional==0)
          {
            *InIfDef=0;
            *ConstLastDef=0;
          }
        break;
      }
    if(str_cmp(Lookup,"incr")==0)
      {
        j=FALSE;
        fprintf(Outfile,"%s",Scoot);
        for(i=2; i<=Ndx; i+=1)
          {
            if(str_cmp(Stk[i],",")==0)
              {
                fprintf(Outfile,"%s","+=(");
                j=TRUE;
              }
            else
              {
                fprintf(Outfile,"%s",Clean(Stk[i]));
              }
          }
        fprintf(Outfile,"%s\n",sziif(j,");","++;"));
        break;
      }
    if(str_cmp(Lookup,"decr")==0)
      {
        j=FALSE;
        fprintf(Outfile,"%s",Scoot);
        for(i=2; i<=Ndx; i+=1)
          {
            if(str_cmp(Stk[i],",")==0)
              {
                fprintf(Outfile,"%s","-=(");
                j=TRUE;
              }
            else
              {
                fprintf(Outfile,"%s",Clean(Stk[i]));
              }
          }
        fprintf(Outfile,"%s\n",sziif(j,");","--;"));
        break;
      }
    if(str_cmp(Lookup,"seek")==0)
      {
        if(DataType(Stk[2])==vt_NUMBER)
          {
            strcpy(Stk[2], join(2,"FP",Stk[2]));
          }
        if(CheckLocal(Stk[2], &i)==vt_UNKNOWN)
          {
            AddGlobal(Stk[2],vt_FILEPTR,0,"",0,0,0,0);
          }
        fprintf(Outfile,"%s%s",Scoot,"fseek(");
        for(Tmp=2; Tmp<=Ndx; Tmp+=1)
          {
            fprintf(Outfile,"%s",Clean(Stk[Tmp]));
          }
        fprintf(Outfile,"%s\n",",0);");
        break;
      }
    if(str_cmp(Lookup,"select")==0)
      {
        *CaseVar=0;
        CaseFlag=0;
        for(A=3; A<=Ndx; A+=1)
          {
            strcat(CaseVar,Stk[A]);
          }
        Push(CaseVar);
        fprintf(Outfile,"%s%s\n",Scoot,"for(;;)");
        fprintf(Outfile,"%s%s\n",Scoot,"{");
        BumpUp();
        break;
      }
    if(str_cmp(Lookup,"~get")==0)
      {
        Use_Get=TRUE;
        if(DataType(Stk[2])==vt_NUMBER)
          {
            strcpy(Stk[2], join(2,"FP",Stk[2]));
          }
        if(CheckLocal(Stk[2], &i)==vt_UNKNOWN)
          {
            if(CheckGlobal(Stk[2], &i)==vt_UNKNOWN)
              {
                AddGlobal(Stk[2],vt_FILEPTR,0,"",0,0,0,0);
              }
          }
        fprintf(Outfile,"%s%s",Scoot,"GET(");
        for(Tmp=2; Tmp<=Ndx; Tmp+=1)
          {
            fprintf(Outfile,"%s",Clean(Stk[Tmp]));
          }
        fprintf(Outfile,"%s\n",");");
        break;
      }
    if(str_cmp(Lookup,"~put")==0)
      {
        Use_Put=TRUE;
        if(DataType(Stk[2])==vt_NUMBER)
          {
            strcpy(Stk[2], join(2,"FP",Stk[2]));
          }
        if(CheckLocal(Stk[2], &i)==vt_UNKNOWN)
          {
            if(CheckGlobal(Stk[2], &i)==vt_UNKNOWN)
              {
                AddGlobal(Stk[2],vt_FILEPTR,0,"",0,0,0,0);
              }
          }
        fprintf(Outfile,"%s%s",Scoot,"PUT(");
        for(Tmp=2; Tmp<=Ndx; Tmp+=1)
          {
            fprintf(Outfile,"%s",Clean(Stk[Tmp]));
          }
        fprintf(Outfile,"%s\n",");");
        break;
      }
    if(str_cmp(Lookup,"gosub")==0)
      {
        Use_Gosub=TRUE;
        fprintf(Outfile,"%s%s",Scoot,"if (setjmp(GosubStack[GosubNdx++])==0)");
        fprintf(Outfile,"%s%s%s\n"," goto ",ucase(Stk[2]),";");
        break;
      }
    if(str_cmp(Lookup,"return")==0)
      {
        Use_Gosub=TRUE;
        fprintf(Outfile,"%s%s\n",Scoot,"longjmp (GosubStack [--GosubNdx],1 );");
        fprintf(Outfile,"%s\n","");
        break;
      }
    if(str_cmp(Lookup,"data")==0)
      {
        if(str_cmp(Stk[Ndx],",")!=0)
          {
            strcpy(Stk[Ndx+1],",");
            Ndx++;
          }
        for(A=2; A<=Ndx; A+=1)
          {
            if(inchr(Stk[A],DQ)==0&&str_cmp(Stk[A],",")!=0)
              {
                strcpy(Stk[A],enc(Stk[A]));
              }
            fprintf(FP5,"%s",Stk[A]);
          }
        fprintf(FP5,"%s\n","");
        break;
      }
    if(str_cmp(Lookup,"namespace")==0)
      {
        UseCpp=TRUE;
        strcpy(szTmp,mid(Src,inchr(Src," ")+1));
        fprintf(Outfile,"%s%s\n","namespace ",ltrim(szTmp));
        fprintf(Outfile,"%s\n","{");
        InNameSpace++;
        BumpUp();
        break;
      }
    if(str_cmp(Lookup,"endnamespace")==0)
      {
        InNameSpace--;
        BumpDown();
        fprintf(Outfile,"%s%s\n",Scoot,"}");
        break;
      }
    if(str_cmp(Lookup,"class")==0)
      {
        if(InTypeDef==0)
          {
            SaveOutfileNum=Outfile;
          }
        Outfile=FP4;
        InTypeDef++;
        strcpy(TypeName[InTypeDef],Stk[2]);
        if(str_cmp(Stk[3],"inherits")==0)
          {
            strcpy(Stk[3], join(2,": public ",Stk[4]));
          }
        AddTypeDefs(TypeName[InTypeDef],vt_STRUCT);
        BaseTypeDefsCnt[InTypeDef]=TypeDefsCnt;
        if(InTypeDef==1)
          {
            fprintf(Outfile,"%s\n","");
            fprintf(Outfile,"%s%s%s%s\n","class ",TypeName[InTypeDef],Stk[3]," {");
            BumpUp();
          }
        break;
      }
    if(str_cmp(Lookup,"endclass")==0)
      {
        BumpDown();
        fprintf(Outfile,"%s%s\n","};",LF);
        InTypeDef--;
        break;
      }
    if(str_cmp(Lookup,"type")==0)
      {
        if(InTypeDef==0)
          {
            SaveOutfileNum=Outfile;
          }
        Outfile=FP4;
        if(Ndx>2)
          {
            if(InTypeDef)
              {
                Abort("Single line TYPE within type/union not supported");
              }
            for(i=Ndx; i>=1; i+=-1)
              {
                if(iMatchWrd(Stk[i],"as"))
                  {
                    break;
                  }
              }
            if(!iMatchWrd(Stk[i],"as"))
              {
                Abort("Missing AS TYPE");
              }
            fprintf(Outfile,"%s","typedef ");
            j=i-1;
            i++;
            while(i<=Ndx)
              {
                fprintf(Outfile,"%s%s",Stk[i]," ");
                i++;
              }
            for(i=2; i<=j; i+=1)
              {
                fprintf(Outfile,"%s",Stk[i]);
              }
            fprintf(Outfile,"%s\n",";");
            Outfile=SaveOutfileNum;
          }
        else
          {
            InTypeDef++;
            strcpy(TypeName[InTypeDef],Stk[2]);
            AddTypeDefs(TypeName[InTypeDef],vt_STRUCT);
            BaseTypeDefsCnt[InTypeDef]=TypeDefsCnt;
            if(InTypeDef==1)
              {
                fprintf(Outfile,"%s\n","");
                fprintf(Outfile,"%s%s\n","typedef struct _",TypeName[InTypeDef]);
                fprintf(Outfile,"%s\n","{");
                BumpUp();
              }
            else
              {
                fprintf(Outfile,"%s%s\n",Scoot,"struct");
                fprintf(Outfile,"%s%s\n",Scoot,"{");
                AddTypedefElement(BaseTypeDefsCnt[InTypeDef-1],vt_STRUCT,TypeName[InTypeDef],TypeName[InTypeDef],0);
                BumpUp();
              }
          }
        break;
      }
    if(str_cmp(Lookup,"endtype")==0)
      {
        if(InTypeDef==1)
          {
            BumpDown();
            fprintf(Outfile,"%s%s%s%s%s%s\n","}",TypeName[InTypeDef],", *","LP",ucase(TypeName[InTypeDef]),";");
            fprintf(Outfile,"%s\n","");
            Outfile=SaveOutfileNum;
            fprintf(FP6,"%s%s%s%s%s%s\n",Scoot,"#define ",ucase(TypeName[InTypeDef]),"_CLASS struct _",ucase(TypeName[InTypeDef]),"*");
          }
        else
          {
            BumpDown();
            fprintf(Outfile,"%s%s%s%s\n",Scoot,"} ",TypeName[InTypeDef],";");
            fprintf(Outfile,"%s\n","");
          }
        InTypeDef--;
        break;
      }
    if(str_cmp(Lookup,"union")==0)
      {
        if(InTypeDef==0)
          {
            SaveOutfileNum=Outfile;
          }
        Outfile=FP4;
        InTypeDef++;
        strcpy(TypeName[InTypeDef],Stk[2]);
        AddTypeDefs(TypeName[InTypeDef],vt_UNION);
        BaseTypeDefsCnt[InTypeDef]=TypeDefsCnt;
        if(InTypeDef==1)
          {
            fprintf(Outfile,"%s\n","");
            fprintf(Outfile,"%s\n","typedef union ");
            fprintf(Outfile,"%s\n","{");
            BumpUp();
          }
        else
          {
            fprintf(Outfile,"%s%s\n",Scoot,"union");
            fprintf(Outfile,"%s%s\n",Scoot,"{");
            AddTypedefElement(BaseTypeDefsCnt[InTypeDef-1],vt_UNION,TypeName[InTypeDef],TypeName[InTypeDef],0);
            BumpUp();
          }
        break;
      }
    if(str_cmp(Lookup,"endunion")==0)
      {
        if(InTypeDef==1)
          {
            BumpDown();
            fprintf(Outfile,"%s%s%s%s%s%s\n","} ",TypeName[InTypeDef],", *","LP",ucase(TypeName[InTypeDef]),";");
            fprintf(Outfile,"%s\n","");
            Outfile=SaveOutfileNum;
          }
        else
          {
            BumpDown();
            fprintf(Outfile,"%s%s%s%s\n",Scoot,"} ",TypeName[InTypeDef],";");
            fprintf(Outfile,"%s\n","");
          }
        InTypeDef--;
        break;
      }
    if(str_cmp(Lookup,"with")==0)
      {
        WithCnt++;
        if(WithCnt==8)
          {
            Abort("[With] depth exceeded");
          }
        *WithVar[WithCnt]=0;
        for(i=2; i<=Ndx; i+=1)
          {
            strcat(WithVar[WithCnt],Stk[i]);
          }
        break;
      }
    if(str_cmp(Lookup,"endwith")==0)
      {
        WithCnt--;
        break;
      }
    if(str_cmp(Lookup,"clear")==0)
      {
        Use_Clear=TRUE;
        fprintf(Outfile,"%s%s",Scoot,"Clear ");
        if(str_cmp(Stk[2],"(")!=0)
          {
            fprintf(Outfile,"%s","(");
          }
        for(i=2; i<=Ndx; i+=1)
          {
            fprintf(Outfile,"%s",Clean(Stk[i]));
          }
        if(str_cmp(Stk[2],"(")!=0)
          {
            fprintf(Outfile,"%s",")");
          }
        fprintf(Outfile,"%s\n",";");
        break;
      }
    if(str_cmp(Lookup,"repeat")==0)
      {
        *lszTmp=0;
        for(i=2; i<=Ndx; i+=1)
          {
            strcat(lszTmp,Stk[i]);
          }
        strcpy(lszTmp,Clean(lszTmp));
        BumpUp();
        if(inchr(Stk[2],"-"))
          {
            if(str_cmp(left(lszTmp,1),"-")==0)
              {
                strcpy(lszTmp,mid(lszTmp,2));
              }
            fprintf(Outfile,"%s%s\n",Scoot,"{int BCX_REPEAT;");
            fprintf(Outfile,"%s%s%s%s\n",Scoot,"for(BCX_REPEAT=",lszTmp,";BCX_REPEAT>=1;BCX_REPEAT--)");
            fprintf(Outfile,"%s%s\n",Scoot,"{");
          }
        else
          {
            fprintf(Outfile,"%s%s\n",Scoot,"{int BCX_REPEAT;");
            fprintf(Outfile,"%s%s%s%s\n",Scoot,"for(BCX_REPEAT=1;BCX_REPEAT<=",lszTmp,";BCX_REPEAT++)");
            fprintf(Outfile,"%s%s\n",Scoot,"{");
          }
        BumpUp();
        break;
      }
    if(str_cmp(Lookup,"endrepeat")==0)
      {
        BumpDown();
        fprintf(Outfile,"%s%s\n",Scoot,"}");
        fprintf(Outfile,"%s%s\n",Scoot,"}");
        BumpDown();
        break;
      }
    if(str_cmp(Lookup,"const")==0)
      {
        char Buffer[2048];
        char Sep[2048];
        *Buffer=0;
        *Sep=0;
        *Stk[1]=0;
        for(i=2; i<=Ndx; i+=1)
          {
            if(str_cmp(Stk[i],"=")==0)
              {
                i++;
                break;
              }
            else
              {
                strcat(Stk[1],Stk[i]);
              }
          }
        strcpy(Stk[1], join(3,"#define ",Clean(Stk[1]),SPC));
        for(i=i; i<=Ndx; i+=1)
          {
            if(isalpha(Stk[i][0])||(Stk[i][0]==95&&isalpha(Stk[i+1][0]))||Stk[i+1][0]==95)
              {
                strcpy(Sep," ");
              }
            else
              {
                *Sep=0;
              }
            if(!IsQuoted(Stk[i]))
              {
                strcpy(Stk[i],RemoveStr(Stk[i],"$"));
              }
            strcpy(Buffer, join(3,Buffer,Stk[i],Sep));
          }
        strcpy(Buffer, join(2,Stk[1],Buffer));
        if(InConditional)
          {
            if(InFunc)
              {
                fprintf(Outfile,"%s\n",Buffer);
              }
            else
              {
                if(str_cmp(ConstLastDef,"FP6")!=0)
                  {
                    fprintf(FP6,"%s%s\n",InIfDef,"// FP6");
                    strcpy(ConstLastDef,"FP6");
                  }
                fprintf(FP6,"%s\n",Buffer);
              }
          }
        else
          {
            fprintf(FP6,"%s\n",Buffer);
          }
        break;
      }
    if(str_cmp(Lookup,"kill")==0)
      {
        fprintf(Outfile,"%s%s",Scoot,"remove (");
        for(A=2; A<=Ndx; A+=1)
          {
            fprintf(Outfile,"%s",Clean(trim(Stk[A])));
          }
        fprintf(Outfile,"%s\n",");");
        break;
      }
    if(str_cmp(Lookup,"chdir")==0 ||  str_cmp(Lookup,"_chdir")==0 ||  str_cmp(Lookup,"rmdir")==0 ||  str_cmp(Lookup,"_rmdir")==0 ||  str_cmp(Lookup,"mkdir")==0 ||  str_cmp(Lookup,"_mkdir")==0)
      {
        fprintf(Outfile,"%s%s%s",Scoot,Lookup," (");
        for(A=2; A<=Ndx; A+=1)
          {
            fprintf(Outfile,"%s",Clean(trim(Stk[A])));
          }
        fprintf(Outfile,"%s\n",");");
        break;
      }
    if(str_cmp(Lookup,"free")==0)
      {
         VarInfo*  VI;
        A=2;
        if(iMatchWrd(Stk[2],"dynamic"))
          {
            A=3;
          }
        if(str_cmp(Stk[A],"(")==0)
          {
            A++;
            Ndx--;
          }
        strcpy(CVar,Clean(Stk[A]));
        vt=CheckLocal(CVar, &id);
        if(vt==vt_UNKNOWN)
          {
            vt=CheckGlobal(CVar, &id);
            if(vt==vt_UNKNOWN)
              {
                Abort(join(3,"Can not REDIM ",CVar," not previously dimensioned"));
              }
            VI= &GlobalVars[id];
          }
        else
          {
            VI= &LocalVars[id];
            Warning("Local dynamic variables are automatically freed.",1);
          }
        *CVar=0;
        for(i=A; i<=Ndx; i+=1)
          {
            strcat(CVar,Stk[i]);
          }
        strcpy(CVar,Clean(CVar));
        if(vt==vt_STRUCT||vt==vt_UNION)
          {
            GetElement(2, &vt, &dms,VI->VarDef);
            if(vt!=vt_UNKNOWN&&dms>0)
              {
                Use_DynamicA=TRUE;
                fprintf(Outfile,"%s%s%s",Scoot,"if (",CVar);
                fprintf(Outfile,"%s%s%s%d%s",") { DestroyArr((void **)",CVar,",",(int)dms,", 1); ");
                fprintf(Outfile,"%s%s\n",CVar,"=NULL; }");
                break;
              }
          }
        if(VI->VarPntr>1)
          {
            Use_DynamicA=TRUE;
            fprintf(Outfile,"%s%s%s",Scoot,"if (",CVar);
            fprintf(Outfile,"%s%s%s%s%s",") { DestroyArr((void **)",CVar,",",str(VI->VarPntr),", 1); ");
            fprintf(Outfile,"%s%s\n",CVar,"=NULL; }");
          }
        else
          {
            fprintf(Outfile,"%s%s%s%s%s%s\n",Scoot,"free(",CVar,"), ",CVar,"=NULL;");
          }
        break;
      }
    if(str_cmp(Lookup,"midstr")==0)
      {
        *Src=0;
        for(A=1; A<=Ndx; A+=1)
          {
            strcat(Src,Clean(Stk[A]));
          }
        fprintf(Outfile,"%s%s%s\n",Scoot,trim(Src),";");
        break;
      }
    if(str_cmp(Lookup,"swap")==0)
      {
         VarInfo*  VI1;
         VarInfo*  VI2;
         int  indx;
        fprintf(Outfile,"%s%s",Scoot,"swap ((BYTE*)&");
        for(i=2; i<=Ndx; i+=1)
          {
            if(str_cmp(Stk[i],",")==0)
              {
                break;
              }
            fprintf(Outfile,"%s",Clean(Stk[i]));
          }
        A=CheckLocal(Stk[2], &indx);
        if(A==vt_UNKNOWN)
          {
            A=CheckGlobal(Stk[2], &indx);
            if(A==vt_UNKNOWN)
              {
                Abort(join(3,"Variable '",Stk[2],"' in swap statement unknown"));
              }
            VI1= &GlobalVars[indx];
          }
        else
          {
            VI1= &LocalVars[indx];
          }
        if(str_cmp(right(Stk[i-1],1),"]")!=0)
          {
            if(VI1->VarType==vt_CHAR&&VI1->VarPntr==1)
              {
                fprintf(Outfile,"%s","[0]");
              }
          }
        fprintf(Outfile,"%s",",(BYTE*)&");
        i++;
        for(j=i; j<=Ndx; j+=1)
          {
            fprintf(Outfile,"%s",Clean(Stk[j]));
          }
        A=CheckLocal(Stk[i], &indx);
        if(A==vt_UNKNOWN)
          {
            A=CheckGlobal(Stk[i], &indx);
            if(A==vt_UNKNOWN)
              {
                Abort(join(3,"Variable '",Stk[i],"' in swap statement unknown"));
              }
            VI2= &GlobalVars[indx];
          }
        else
          {
            VI2= &LocalVars[indx];
          }
        if(str_cmp(right(Stk[j-1],1),"]")!=0)
          {
            if(VI2->VarType==vt_CHAR&&VI2->VarPntr==1)
              {
                fprintf(Outfile,"%s","[0]");
              }
          }
        if(VI1->VarType!=VI2->VarType)
          {
            Warning("Possible size error in swap statement");
          }
        if(VI2->VarType==vt_STRVAR||VI2->VarType==vt_CHAR)
          {
            fprintf(Outfile,"%s",",strlen(");
          }
        else
          {
            fprintf(Outfile,"%s",",sizeof(");
          }
        for(j=i; j<=Ndx; j+=1)
          {
            fprintf(Outfile,"%s",Clean(Stk[j]));
          }
        fprintf(Outfile,"%s\n","));");
        break;
      }
    if(str_cmp(Lookup,"rename")==0)
      {
        fprintf(Outfile,"%s%s",Scoot,"rename (");
        for(A=2; A<=Ndx; A+=1)
          {
            fprintf(Outfile,"%s",Clean(trim(Stk[A])));
          }
        fprintf(Outfile,"%s\n",");");
        break;
      }
    if(str_cmp(Lookup,"copyfile")==0)
      {
        fprintf(Outfile,"%s%s",Scoot,"CopyFile ");
        if(str_cmp(Stk[2],"(")!=0)
          {
            fprintf(Outfile,"%s","(");
          }
        for(A=2; A<=Ndx; A+=1)
          {
            fprintf(Outfile,"%s",Clean(trim(Stk[A])));
          }
        if(str_cmp(Stk[Ndx],")")!=0)
          {
            fprintf(Outfile,"%s\n",");");
          }
        else
          {
            fprintf(Outfile,"%s\n",";");
          }
        break;
      }
    if(str_cmp(Lookup,"shell")==0)
      {
        if(Ndx>2)
          {
            for(A=3; A<=Ndx; A+=1)
              {
                strcpy(Stk[2], join(2,Stk[2],Stk[A]));
              }
          }
        strcpy(ZZ,Stk[2]);
        if(ZZ[0]==0)
          {
            strcpy(ZZ,DDQ);
          }
        fprintf(Outfile,"%s%s%s%s\n",Scoot,"Shell(",Clean(ZZ),");");
        break;
      }
    if(str_cmp(Lookup,"lineinput")==0)
      {
        i=DataType(Stk[2]);
        if(i==vt_STRLIT||i==vt_STRVAR)
          {
            if(i!=vt_STRLIT)
              {
                strcpy(Stk[2],Clean(Stk[2]));
              }
            fprintf(Outfile,"%s%s%s%s%s%s\n",Scoot,"printf(",enc("%s"),",",Stk[2],");");
            fprintf(Outfile,"%s%s%s%s\n",Scoot,"AR_fgets_retval=fgets(",Clean(Stk[3]),",65535,stdin);");
            fprintf(Outfile,"%s%s%s%s%s\n",Scoot,Clean(Stk[3]),"[strlen(",Clean(Stk[3]),")-1]=0;");
            break;
          }
        strcpy(Stk[2],RemoveStr(Stk[2],"#"));
        if(DataType(Stk[2])==vt_NUMBER)
          {
            strcpy(Stk[2], join(2,"FP",Stk[2]));
          }
        strcpy(Handl,extract(Stk[2],"["));
        if(CheckLocal(Handl, &i)==vt_UNKNOWN)
          {
            if(CheckGlobal(Handl, &i)==vt_UNKNOWN)
              {
                AddGlobal(Handl,vt_FILEPTR,0,"",0,0,0,0);
              }
          }
        strcpy(Var,Clean(Stk[3]));
        *Var1=0;
        strcpy(CVar,Var);
        if(inchr(Var,"[")&&inchr(Var,"]"))
          {
            if(instr_b(Var,"[++"))
              {
                strcpy(CVar,replace(CVar,"++",""));
              }
            if(instr_b(Var,"[--"))
              {
                strcpy(CVar,replace(CVar,"--",""));
              }
            if(instr_b(Var,"++]"))
              {
                strcpy(CVar,replace(CVar,"++",""));
                strcpy(Var1,mid(Var,inchr(Var,"[")+1));
                strcpy(Var1,extract(Var1,"]"));
                strcpy(Var,CVar);
              }
            if(instr_b(Var,"--]"))
              {
                strcpy(CVar,replace(CVar,"--",""));
                strcpy(Var1,mid(Var,inchr(Var,"[")+1));
                strcpy(Var1,extract(Var1,"]"));
                strcpy(Var,CVar);
              }
          }
        fprintf(Outfile,"%s%s%s\n",Scoot,Var,"[0]=0;");
        fprintf(Outfile,"%s%s%s%s%s%s\n",Scoot,"AR_fgets_retval=fgets(",Var,",65535,",Clean(Stk[2]),");");
        fprintf(Outfile,"%s%s%s%s%s%s",Scoot,"if(",CVar,"[strlen(",CVar,")-1]==10)");
        fprintf(Outfile,"%s%s%s%s\n",CVar,"[strlen(",CVar,")-1]=0;");
        if(Var1[0]!=0)
          {
            fprintf(Outfile,"%s%s\n",Var1,";");
          }
        break;
      }
    if(str_cmp(Lookup,"open")==0)
      {
        for(A=1; A<=Ndx; A+=1)
          {
            strcpy(Keyword,lcase(Stk[A]));
            for(;;)
            {
              if(str_cmp(Keyword,"open")==0)
                {
                  *Stk[A]=0;
                  break;
                }
              if(str_cmp(Keyword,"for")==0)
                {
                  *Stk[A]=0;
                  *Filnam=0;
                  for(j=2; j<=A-1; j+=1)
                    {
                      strcat(Filnam,Stk[j]);
                    }
                  strcpy(Filnam,Clean(Filnam));
                  break;
                }
              if(str_cmp(Keyword,"as")==0)
                {
                  *Stk[A]=0;
                  if(DataType(Stk[A+1])==vt_NUMBER)
                    {
                      strcpy(Stk[A+1], join(2,"FP",Stk[A+1]));
                    }
                  if(CheckLocal(Stk[A+1], &i)==vt_UNKNOWN)
                    {
                      if(CheckGlobal(Stk[A+1], &i)==vt_UNKNOWN)
                        {
                          AddGlobal(Stk[A+1],vt_FILEPTR,0,"",0,0,0,0);
                        }
                    }
                  *Var=0;
                  for(j=A+1; j<=Ndx; j+=1)
                    {
                      if(iMatchWrd(Stk[j],"reclen"))
                        {
                          break;
                        }
                      strcat(Var,Stk[j]);
                      *Stk[j]=0;
                    }
                  strcpy(Handl, join(2,Var,"@"));
                  break;
                }
              if(str_cmp(Keyword,"network")==0)
                {
                  Use_Socket=TRUE;
                  break;
                }
              if(str_cmp(Keyword,"input")==0)
                {
                  strcpy(Op,enc("r"));
                  *Stk[A]=0;
                  break;
                }
              if(str_cmp(Keyword,"output")==0)
                {
                  strcpy(Op,enc("w"));
                  *Stk[A]=0;
                  break;
                }
              if(str_cmp(Keyword,"append")==0)
                {
                  strcpy(Op,enc("a"));
                  *Stk[A]=0;
                  break;
                }
              if(str_cmp(Keyword,"binary")==0)
                {
                  strcpy(Op,enc("rb+"));
                  *Stk[A]=0;
                  break;
                }
              if(str_cmp(Keyword,"binaryappend")==0)
                {
                  strcpy(Op,enc("ab+"));
                  *Stk[A]=0;
                  break;
                }
              if(str_cmp(Keyword,"binarynew")==0)
                {
                  strcpy(Op,enc("wb+"));
                  *Stk[A]=0;
                  break;
                }
              if(str_cmp(Keyword,"binaryinput")==0)
                {
                  strcpy(Op,enc("rb"));
                  *Stk[A]=0;
                  break;
                }
              if(str_cmp(Keyword,"binaryoutput")==0)
                {
                  strcpy(Op,enc("rb+"));
                  *Stk[A]=0;
                  break;
                }
              if(str_cmp(Keyword,"reclen")==0)
                {
                  if(str_cmp(Stk[A+1],"=")==0)
                    {
                      for(j=A+2; j<=Ndx; j+=1)
                        {
                          strcpy(Stk[j-1],Stk[j]);
                        }
                      Ndx--;
                    }
                  strcpy(Var, join(2,extract(Clean(Handl),"["),"len"));
                  if(CheckLocal(Var, &i)==vt_UNKNOWN)
                    {
                      AddGlobal(Var,vt_INTEGER,0,"",0,0,0,0);
                    }
                  else
                    {
                      if(CheckLocal(Var, &i)==vt_UNKNOWN)
                        {
                          AddLocal(Var,vt_INTEGER,0,"",0,0,0);
                          strcpy(Var, join(2,"int ",Var));
                        }
                    }
                  i=CheckType(Stk[A+1]);
                  strcpy(ZZ,lcase(Stk[A+1]));
                  if(i==vt_STRUCT||i==vt_UNION||str_cmp(ZZ,"int")==0 ||  str_cmp(ZZ,"double")==0 ||  str_cmp(ZZ,"float")==0)
                    {
                      fprintf(Outfile,"%s%s%s%s%s\n",Scoot,Var," = sizeof(",Stk[A+1],");");
                    }
                  else
                    {
                      fprintf(Outfile,"%s%s%s%s%s\n",Scoot,Var," = ",Clean(Stk[A+1]),";");
                    }
                  *Stk[A]=0;
                  *Stk[A+1]=0;
                }
              break;
            }
          }
        fprintf(Outfile,"%s%s%s%s%s%s%s%s\n",Scoot,"if((",Clean(Handl),"=fopen(",Filnam,",",Op,"))==0)");
        fprintf(Outfile,"%s%s\n",Scoot," {");
        strcpy(lszTmp,enc("Can't open file %s\\n"));
        fprintf(Outfile,"%s%s%s%s%s%s\n",Scoot,"   fprintf(stderr,",lszTmp,",",Filnam,");");
        fprintf(Outfile,"%s%s\n",Scoot,"   exit(1);");
        fprintf(Outfile,"%s%s\n",Scoot," }");
        break;
      }
    if(str_cmp(Lookup,"record")==0)
      {
        static   struct _functionParse  ffp;
        memset(&ffp,0,sizeof(ffp));
        int     numargs=0;
        if(DataType(Stk[2])==vt_NUMBER)
          {
            strcpy(Stk[2], join(2,"FP",Stk[2]));
          }
        if(Ndx>1)
          {
            numargs=SepFuncArgs(1, &ffp,FALSE);
          }
        if(numargs<1)
          {
            Abort("Missing required arguments to RECORD");
          }
        if(numargs>4)
          {
            Abort("Too many arguments to RECORD");
          }
        if(numargs==3)
          {
            fprintf(Outfile,"%s%s%s%s%s%s%s%s%s%s\n",Scoot,"fseek(",GetArg(1, &ffp),", (",GetArg(2, &ffp)," - 1) * ",Stk[2],"len + ",GetArg(3, &ffp),", SEEK_SET);");
          }
        else if(numargs==2)
          {
            fprintf(Outfile,"%s%s%s%s%s%s%s%s\n",Scoot,"fseek(",GetArg(1, &ffp),", (",GetArg(2, &ffp)," - 1) * ",Stk[2],"len, SEEK_SET);");
          }
        else
          {
            fprintf(Outfile,"%s%s%s%s\n",Scoot,"fseek(",GetArg(1, &ffp),", 0, SEEK_SET);");
          }
        break;
      }
    if(str_cmp(Lookup,"fwrite")==0)
      {
        if(DataType(Stk[2])==vt_NUMBER)
          {
            strcpy(Stk[2], join(2,"FP",Stk[Ndx]));
          }
        if(CheckLocal(Stk[2], &i)==vt_UNKNOWN)
          {
            AddGlobal(Stk[2],vt_FILEPTR,0,"",0,0,0,0);
          }
        *Handl=0;
        for(j=2; j<=Ndx; j+=1)
          {
            if(iMatchWrd(Stk[j],",")||iMatchWrd(Stk[j],";"))
              {
                *Stk[j]=0;
                break;
              }
            strcat(Handl,Stk[j]);
            *Stk[j]=0;
          }
        strcat(Handl,"@");
        strcpy(ZZ, join(2,"f",PrintWriteFormat(1)));
        strcpy(ZZ, join(4,left(ZZ,8),Clean(Handl),",",mid(ZZ,9)));
        fprintf(Outfile,"%s%s\n",Scoot,ZZ);
        break;
      }
    if(str_cmp(Lookup,"close")==0)
      {
        if(Ndx==1)
          {
            fprintf(Outfile,"%s%s\n",Scoot,"fcloseall();");
            break;
          }
        if(DataType(Stk[2])==vt_NUMBER)
          {
            strcpy(Stk[2], join(2,"FP",Stk[Ndx]));
          }
        if(CheckLocal(Stk[2], &i)==vt_UNKNOWN)
          {
            if(CheckGlobal(Stk[2], &i)==vt_UNKNOWN)
              {
                AddGlobal(Stk[2],vt_FILEPTR,0,"",0,0,0,0);
              }
          }
        *Handl=0;
        for(j=2; j<=Ndx; j+=1)
          {
            strcat(Handl,Stk[j]);
          }
        fprintf(Outfile,"%s%s%s%s\n",Scoot,"if(",Handl,")");
        fprintf(Outfile,"%s%s\n",Scoot," {");
        fprintf(Outfile,"%s%s%s%s\n",Scoot,"   fclose(",Handl,");");
        fprintf(Outfile,"%s%s%s%s\n",Scoot,"   ",Handl,"=NULL;");
        fprintf(Outfile,"%s%s\n",Scoot," }");
        break;
      }
    if(str_cmp(Lookup,"call")==0)
      {
        *lszTmp=0;
        for(Tmp=2; Tmp<=Ndx; Tmp+=1)
          {
            strcat(lszTmp,Clean(Stk[Tmp]));
          }
        if(!iMatchRgt(lszTmp,")"))
          {
            strcat(lszTmp,"()");
          }
        strcat(lszTmp,";");
        fprintf(Outfile,"%s%s\n",Scoot,lszTmp);
        break;
      }
    if(str_cmp(Lookup,"declare")==0)
      {
        static   struct _functionParse  FP;
        memset(&FP,0,sizeof(FP));
        char TempProto[2048];
        FuncSubDecs1("sub");
        SepFuncArgs(3, &FP,TRUE);
        strcpy(TempProto,MakeDecProto( &FP));
        if(!NoTypeDeclare)
          {
            fprintf(FP4,"%s%s\n",TempProto,";");
          }
        else
          {
            ProtoCnt++;
            strcpy(ProtoType[ProtoCnt].Prototype, join(2,TempProto,";"));
          }
        break;
      }
    if(str_cmp(Lookup,"function")==0 ||  str_cmp(Lookup,"sub")==0 ||  str_cmp(Lookup,"constructor")==0 ||  str_cmp(Lookup,"destructor")==0)
      {
        static char CTOR_USE[2048];
        memset(&CTOR_USE,0,sizeof(CTOR_USE));
        static char CTOR_SRC[2048];
        memset(&CTOR_SRC,0,sizeof(CTOR_SRC));
        static int     New_Ndx;
        memset(&New_Ndx,0,sizeof(New_Ndx));
        if(str_cmp(Stk[2],"main")==0)
          {
            strcpy(Stk[1],"function");
            strcpy(Stk[2],"main%");
            ForceMainToFunc=TRUE;
          }
        if(iMatchWrd(Stk[1],"constructor")||iMatchWrd(Stk[1],"destructor"))
          {
            strcpy(Stk[1],"sub");
              {int ct;
            for(ct=1; ct<=Ndx; ct+=1)
              {
                if(str_cmp(Stk[ct],"using")==0)
                  {
                    New_Ndx=ct-1;
                      {int ut;
                    for(ut=ct; ut<=Ndx; ut+=1)
                      {
                        strcat(CTOR_USE,Stk[ut]);
                      }
                      }
                  }
              }
              }
            if(strlen(CTOR_USE))
              {
                strcpy(CTOR_USE,iReplace(CTOR_USE,"using",":"));
                Ndx=New_Ndx;
              }
            Use_Ctor=TRUE;
          }
        FuncSubDecs1("sub");
        IsStdFunc=FALSE;
        if(iMatchWrd(Stk[Ndx],"stdcall"))
          {
            strcpy(CallType,"__attribute__((stdcall)) ");
            Ndx--;
            IsStdFunc=TRUE;
          }
        InFunc=TRUE;
        InMain=FALSE;
        LocalVarCnt=0;
        if(InNameSpace)
          {
            Outfile=FP2;
          }
        else
          {
            Outfile=FP3;
          }
        FuncSubDecs2("sub",mt_FuncSubDecC_Dec);
        strcpy(VarCode.Functype,ltrim(VarCode.Functype));
        strcpy(Funcname,Clean(Stk[2]));
        if(IsExported||IsStdFunc)
          {
            strcpy(Funcname, join(2,CallType,Funcname));
          }
        VarCode.Method=mt_FuncSubDecC_Dec2;
        A=3;
        while(A<=Ndx)
          {
            if(str_cmp(Stk[A+1],"(")==0)
              {
                for(k=A+2; k<=Ndx; k+=1)
                  {
                    if(str_cmp(Stk[k],")")==0)
                      {
                        break;
                      }
                  }
                if(iMatchWrd(Stk[k+2],"sub"))
                  {
                    j=vt_VOID;
                    strcpy(VarCode.AsToken,"void");
                  }
                else if(iMatchWrd(Stk[k+2],"function"))
                  {
                    GetTypeInfo(Stk[k+3], &IsPointer, &i, &j);
                    strcpy(VarCode.AsToken,Stk[k+3]);
                  }
                strcpy(VarCode.Token,Stk[A]);
                VarCode.VarNo=j;
                VarCode.IsPtrFlag=1;
                VarCode.Method=mt_FuncSubx1;
                GetVarCode( &VarCode);
                strcpy(Var,Clean(Stk[A]));
                *lszTmp=0;
                A+=2;
                while(A<=k)
                  {
                    if(iMatchWrd(Stk[A+1],"as")&&A<k)
                      {
                        Tmp=A+2;
                        while(str_cmp(Stk[Tmp],",")!=0 &&  str_cmp(Stk[Tmp],")")!=0)
                          {
                            GetTypeInfo(Stk[Tmp], &IsPointer, &i, &j);
                            AddLocal(Stk[A],j,i,"",IsPointer,0,0);
                            strcpy(VarCode.Token,Stk[A]);
                            strcpy(VarCode.AsToken,Stk[Tmp]);
                            VarCode.VarNo=j;
                            VarCode.IsPtrFlag=1;
                            VarCode.Method=mt_FuncSubx2;
                            GetVarCode( &VarCode);
                            Tmp++;
                            if(str_cmp(Stk[Tmp],",")==0)
                              {
                                strcat(VarCode.Proto,",");
                                strcat(VarCode.Header,",");
                              }
                          }
                        A=Tmp;
                      }
                    else
                      {
                        if(str_cmp(Stk[A],",")!=0 &&  str_cmp(Stk[A],")")!=0)
                          {
                            IsPointer=tally((Stk[A]),"*");
                            strcpy(Var,RemoveStr(Stk[A],"*"));
                            j=DataType(Var);
                            if(j!=vt_UNKNOWN&&InFunc==TRUE&&Var[0])
                              {
                                AddLocal(Clean(Var),j,0,"",IsPointer,0,0);
                              }
                            strcpy(VarCode.Token,Stk[A]);
                            *VarCode.AsToken=0;
                            VarCode.VarNo=j;
                            VarCode.IsPtrFlag=IsPointer;
                            VarCode.Method=mt_FuncSubDecC_Dec2;
                            GetVarCode( &VarCode);
                          }
                      }
                    A++;
                  }
                A=k+3;
                if(VarCode.Method==mt_FuncSubDecC_Dec2)
                  {
                    midstr(VarCode.Proto,strlen(VarCode.Proto)-1,1,")");
                    midstr(VarCode.Header,strlen(VarCode.Header)-1,1,")");
                  }
                else
                  {
                    strcat(VarCode.Proto,")");
                    strcat(VarCode.Header,")");
                  }
                VarCode.Method=mt_FuncSubDecC_Dec2;
              }
            else
              {
                if(iMatchWrd(Stk[A+1],"as"))
                  {
                    GetTypeInfo(Stk[A+2], &IsPointer, &i, &j);
                    strcpy(Var,Clean(Stk[A]));
                    AddLocal(Var,j,i,"",IsPointer,0,0);
                    strcpy(VarCode.Token,Stk[A]);
                    strcpy(VarCode.AsToken,Stk[A+2]);
                    VarCode.VarNo=j;
                    VarCode.IsPtrFlag=IsPointer;
                    GetVarCode( &VarCode);
                    *Stk[A+1]=0;
                    *Stk[A+2]=0;
                    A+=2;
                  }
                else
                  {
                    if(inchr("=",Stk[A])&&str_cmp(Stk[A],"")!=0)
                      {
                        Abort("Illegal optional parameter found");
                      }
                    if(!inchr(",().",Stk[A])&&str_cmp(Stk[A],"")!=0)
                      {
                        IsPointer=tally((Stk[A]),"*");
                        strcpy(Var,RemoveStr(Stk[A],"*"));
                        j=DataType(Var);
                        if(j!=vt_UNKNOWN&&Var[0])
                          {
                            AddLocal(Clean(Var),j,0,"",IsPointer,0,0);
                          }
                        strcpy(VarCode.Token,Stk[A]);
                        *VarCode.AsToken=0;
                        VarCode.VarNo=j;
                        VarCode.IsPtrFlag=IsPointer;
                        GetVarCode( &VarCode);
                      }
                  }
              }
            A++;
          }
        VarCode.Method=2;
        strcpy(VarCode.Token,Funcname);
        FuncSubDecs3( &VarCode);
        if(iMatchLft(VarCode.Header,"main("))
          {
            strcpy(VarCode.Header,"int main(int argc, char *argv[])");
            strcpy(VarCode.Proto,"int main(int argc, char *argv[]);");
            CurrentFuncType=vt_INTEGER;
          }
        if(Use_Static)
          {
            strcpy(VarCode.Header, join(2,"static ",VarCode.Header));
            strcpy(VarCode.Proto, join(2,"static ",VarCode.Proto));
          }
        if(!InNameSpace)
          {
            ProtoCnt++;
            strcpy(ProtoType[ProtoCnt].Prototype,VarCode.Proto);
          }
        if(str_cmp(InIfDef,"FP3")==0)
          {
            if(ProtoCnt>1)
              {
                strcpy(ProtoType[ProtoCnt].Condition,ProtoType[ProtoCnt-1].Condition);
              }
            else
              {
                *ProtoType[ProtoCnt].Condition=0;
              }
          }
        else
          {
            strcpy(ProtoType[ProtoCnt].Condition,InIfDef);
          }
        ProtoType[ProtoCnt].CondLevel=InConditional;
        if(*InIfDef)
          {
            if(str_cmp(InIfDef,"FP3")!=0)
              {
                fprintf(Outfile,"%s\n",InIfDef);
                printf("%s\n",InIfDef);
              }
          }
        if(Use_Ctor)
          {
            strcpy(VarCode.Header,replace(VarCode.Header,"void ",""));
            strcpy(VarCode.Header,replace(VarCode.Header,"void",""));
            if(strlen(CTOR_USE))
              {
                fprintf(Outfile,"%s\n",VarCode.Header);
                fprintf(Outfile,"%s%s\n",Scoot,CTOR_USE);
              }
            else
              {
                fprintf(Outfile,"%s\n",VarCode.Header);
              }
            Use_Ctor=FALSE;
          }
        else if(InNameSpace)
          {
            char szCPP_SF1[2048];
            *szCPP_SF1=0;
            if(iMatchLft(Lookup,"public"))
              {
                strcpy(szCPP_SF1,"public: virtual ");
              }
            fprintf(Outfile,"%s%s%s\n",Scoot,szCPP_SF1,VarCode.Header);
          }
        else
          {
            fprintf(Outfile,"%s\n",VarCode.Header);
          }
        fprintf(Outfile,"%s%s\n",Scoot,"{");
        BumpUp();
        break;
      }
    if(str_cmp(Lookup,"optfunction")==0 ||  str_cmp(Lookup,"optsub")==0)
      {
        FuncSubDecs1("optsub");
        InFunc=TRUE;
        LocalVarCnt=0;
        Outfile=FP3;
        if(InNameSpace)
          {
            Outfile=FP2;
          }
        else
          {
            Outfile=FP3;
          }
        FuncSubDecs2("optsub",mt_Opts);
        strcpy(Funcname,Clean(Stk[2]));
        VarCode.Method=mt_Opts2;
        A=4;
        while(A<Ndx)
          {
            if(Stk[A][0]==0)
              {
                A++;
                continue;
              }
            if(str_cmp(Stk[A],",")==0)
              {
                VarCode.Method=mt_Opts3;
                strcpy(VarCode.Token,Stk[A]);
                GetVarCode( &VarCode);
                VarCode.Method=mt_Opts2;
              }
            else if(str_cmp(Stk[A],"=")==0)
              {
                VarCode.Method=mt_Opts3;
                if(str_cmp(Stk[A+1],"-")==0)
                  {
                    strcpy(VarCode.Token, join(3,Stk[A],Stk[A+1],Stk[A+2]));
                    *Stk[A+1]=0;
                    *Stk[A+2]=0;
                    A++;
                  }
                else
                  {
                    strcpy(VarCode.Token, join(2,Stk[A],Stk[A+1]));
                    *Stk[A+1]=0;
                  }
                if(iMatchWrd(Stk[A+2],"as"))
                  {
                    *Stk[A+2]=0;
                    *Stk[A+3]=0;
                  }
                VarCode.VarNo=j;
                VarCode.IsPtrFlag=IsPointer;
                GetVarCode( &VarCode);
                VarCode.Method=mt_Opts2;
              }
            else if(iMatchWrd(Stk[A+1],"as"))
              {
                GetTypeInfo(Stk[A+2], &IsPointer, &i, &j);
                if(InFunc)
                  {
                    strcpy(Var,Clean(Stk[A]));
                    AddLocal(Var,j,i,"",IsPointer,0,0);
                  }
                VarCode.VarNo=j;
                strcpy(VarCode.Token,Stk[A]);
                strcpy(VarCode.AsToken,Stk[A+2]);
                VarCode.IsPtrFlag=IsPointer;
                GetVarCode( &VarCode);
                *Stk[A+1]=0;
                *Stk[A+2]=0;
              }
            else
              {
                IsPointer=tally((Stk[A]),"*");
                strcpy(Var,RemoveStr(Stk[A],"*"));
                j=DataType(Var);
                if(j!=vt_UNKNOWN)
                  {
                    AddLocal(Clean(Var),j,0,"",IsPointer,0,0);
                  }
                VarCode.VarNo=j;
                strcpy(VarCode.Token,Stk[A]);
                *VarCode.AsToken=0;
                VarCode.IsPtrFlag=IsPointer;
                GetVarCode( &VarCode);
              }
            A++;
          }
        VarCode.Method=2;
        strcpy(VarCode.Token,Funcname);
        FuncSubDecs3( &VarCode);
        if(Use_Static)
          {
            strcpy(VarCode.Header, join(2,"static ",VarCode.Header));
            strcpy(VarCode.Proto, join(2,"static ",VarCode.Proto));
          }
        ProtoCnt++;
        strcpy(ProtoType[ProtoCnt].Prototype,VarCode.Proto);
        if(str_cmp(InIfDef,"FP3")==0)
          {
            *ProtoType[ProtoCnt].Condition=0;
          }
        else
          {
            strcpy(ProtoType[ProtoCnt].Condition,InIfDef);
          }
        ProtoType[ProtoCnt].CondLevel=InConditional;
        fprintf(Outfile,"%s\n",VarCode.Header);
        fprintf(Outfile,"%s%s\n",Scoot,"{");
        BumpUp();
        break;
      }
    if(str_cmp(Lookup,"overloadedfunction")==0 ||  str_cmp(Lookup,"overloadedsub")==0)
      {
        Use_Overloaded=TRUE;
        FuncSubDecs1("overloadedsub");
        InFunc=TRUE;
        InMain=FALSE;
        LocalVarCnt=0;
        Outfile=FP8;
        FuncSubDecs2("overloadedsub",mt_OverLoad);
        strcpy(Funcname,Clean(Stk[2]));
        strcpy(lszTmp, join(2," overloaded ",Funcname));
        strcpy(Funcname,lszTmp);
        VarCode.Method=mt_OverLoad2;
        for(A=3; A<=Ndx; A+=1)
          {
            if(iMatchWrd(Stk[A+1],"as"))
              {
                GetTypeInfo(Stk[A+2], &IsPointer, &i, &j);
                strcpy(Var,Clean(Stk[A]));
                AddLocal(Var,j,i,"",IsPointer,0,0);
                strcpy(VarCode.AsToken,Stk[A+2]);
                *Stk[A+1]=0;
                *Stk[A+2]=0;
              }
            else
              {
                strcpy(Var,RemoveStr(Stk[A],"*"));
                j=DataType(Var);
                if(!inchr(",().",Stk[A])&&str_cmp(Stk[A],"")!=0)
                  {
                    IsPointer=tally((Stk[A]),"*");
                    if(j!=vt_UNKNOWN&&InFunc==TRUE&&Var[0])
                      {
                        AddLocal(Clean(Var),j,0,"",IsPointer,0,0);
                      }
                  }
                *VarCode.AsToken=0;
              }
            VarCode.VarNo=j;
            strcpy(VarCode.Token,Stk[A]);
            GetVarCode( &VarCode);
          }
        VarCode.Method=1;
        strcpy(VarCode.Token,Funcname);
        FuncSubDecs3( &VarCode);
        if(Use_Static)
          {
            strcpy(VarCode.Header, join(2,"static ",VarCode.Header));
          }
        fprintf(Outfile,"%s\n",VarCode.Header);
        fprintf(Outfile,"%s%s\n",Scoot,"{");
        BumpUp();
        break;
      }
    if(str_cmp(Lookup,"functionreturn")==0)
      {
        if(CaseFlag)
          {
            NoBreak2=TRUE;
          }
        *lszTmp=0;
        for(A=3; A<=Ndx; A+=1)
          {
            strcpy(lszTmp, join(3,lszTmp,Stk[A]," "));
          }
        if(CurrentFuncType==vt_STRVAR)
          {
            strcpy(lszTmp, join(2,"BCX_RetStr$ = ",lszTmp));
            FuncRetnFlag=1;
            UseFlag=TRUE;
          }
        else
          {
            FuncRetnFlag=2;
          }
        if(FuncRetnFlag==2)
          {
            if(LocalDynaCnt!=0)
              {
                for(j=1; j<=LocalDynaCnt; j+=1)
                  {
                    fprintf(Outfile,"%s%s\n",Scoot,DynaStr[j]);
                  }
              }
            if(LocalDynArrCount!=0)
              {
                for(i=1; i<=LocalDynArrCount; i+=1)
                  {
                    fprintf(Outfile,"%s%s\n",Scoot,LocalDynArrName[i]);
                  }
              }
            fprintf(Outfile,"%s%s",Scoot,"return ");
            LastCmd=2;
          }
        Parse(lszTmp);
        LastCmd=0;
        goto EMITAGAIN;
      }
    if(str_cmp(Lookup,"endfunction")==0 ||  str_cmp(Lookup,"endsub")==0 ||  str_cmp(Lookup,"endconstructor")==0 ||  str_cmp(Lookup,"enddestructor")==0)
      {
        if(iMatchWrd(Stk[1],"endfunction"))
          {
            LocalDynaCnt=0;
            LocalDynArrCount=0;
          }
        if(iMatchWrd(Stk[1],"endsub")||iMatchWrd(Stk[1],"endconstructor")||iMatchWrd(Stk[1],"enddestructor"))
          {
            if(LocalDynaCnt!=0)
              {
                for(j=1; j<=LocalDynaCnt; j+=1)
                  {
                    fprintf(Outfile,"%s%s\n",Scoot,DynaStr[j]);
                  }
                LocalDynaCnt=0;
              }
            if(LocalDynArrCount!=0)
              {
                for(i=1; i<=LocalDynArrCount; i+=1)
                  {
                    fprintf(Outfile,"%s%s\n",Scoot,LocalDynArrName[i]);
                  }
                LocalDynArrCount=0;
              }
          }
        if(ForceMainToFunc==TRUE)
          {
            fprintf(Outfile,"%s%s\n",Scoot,"return 0;");
            ForceMainToFunc=FALSE;
          }
        BumpDown();
        if(InNameSpace)
          {
            fprintf(FP2,"%s%s\n",Scoot,"}\n");
          }
        else
          {
            fprintf(Outfile,"%s%s\n",Scoot,"}\n\n");
            BumpDown();
          }
        InFunc=FALSE;
        Use_Static=FALSE;
        if(Outfile==FP3)
          {
            strcpy(InIfDef,"FP3");
          }
        Outfile=FP2;
        ByrefCnt=0;
        break;
      }
    if(str_cmp(Lookup,"input")==0)
      {
        EmitInputCode();
        break;
      }
    if(str_cmp(Lookup,"finput")==0)
      {
        EmitFileInputCode();
        break;
      }
    if(str_cmp(Lookup,"dynamic")==0)
      {
        int     w=0;
        char SOF[2048];
        HandleNonsense();
        strcpy(CVar,Clean(Stk[2]));
        ValidVar(CVar);
        if(str_cmp(Stk[Ndx],"*")==0)
          {
            PointerFix();
          }
        if(str_cmp(Stk[Ndx],"&")==0)
          {
            *Stk[Ndx--]=0;
            strcat(Stk[Ndx],"&");
          }
        *ZZ=0;
        if(iMatchWrd(Stk[Ndx-1],"as"))
          {
            strcpy(SOF,Stk[Ndx]);
            GetTypeInfo(SOF, &w, &id, &vt);
            if(vt==vt_STRLIT||vt==vt_DECFUNC||vt==vt_NUMBER||(vt==vt_VOID&&inchr(Stk[Ndx],"*")==0))
              {
                Abort(join(2,SOF," is not a valid type"));
              }
            if(vt==vt_FILEPTR&&inchr(SOF,"*")==0)
              {
                strcat(SOF,"*");
              }
            Ndx-=2;
          }
        else
          {
            vt=DataType(Stk[2]);
            id=0;
            strcpy(SOF,GetVarTypeName(vt));
          }
        Use_DynamicA=TRUE;
        for(i=3; i<=Ndx; i+=1)
          {
            strcat(ZZ,Stk[i]);
          }
        dms=tally(ZZ,"][")+1;
        if(dms>1)
          {
            strcpy(ZZ,replace(ZZ,"][",","));
          }
        strcpy(ZZ,Clean(ZZ));
        RemoveAll(ZZ,"[]");
        if(vt==vt_STRVAR)
          {
            vt=vt_CHAR;
            strcpy(SOF,"char");
            if(InTypeDef)
              {
                if(str_cmp(Stk[3],"[")!=0)
                  {
                    dms--;
                  }
                else
                  {
                    vt=vt_CHARPTR;
                  }
              }
            dms++;
            strcat(ZZ,",65535");
          }
        if(InTypeDef)
          {
            if(vt==vt_STRUCT)
              {
                fprintf(Outfile,"%s%s%s%s%s%s%s\n",Scoot,"struct _",SOF,"  ",stringx(dms,42),CVar,";");
              }
            else
              {
                fprintf(Outfile,"%s%s%s%s%s%s\n",Scoot,SOF,"  ",stringx(dms,42),CVar,";");
              }
            AddTypedefElement(BaseTypeDefsCnt[InTypeDef],vt,CVar,SOF,dms);
          }
        else if(InFunc)
          {
            LocalDynArrCount++;
            strcpy(LocalDynArrName[LocalDynArrCount], join(9,"if (",CVar,") { DestroyArr((void **)",CVar,",",str(dms),", 1); ",CVar,"=NULL; }"));
            fprintf(Outfile,"%s%s%s%s%s%s\n",Scoot,SOF,"  ",stringx(dms,42),CVar,"=0;");
            AddLocal(CVar,vt,id,"",dms,0,0);
          }
        else
          {
            if(Use_GenFree)
              {
                GlobalDynaCnt++;
                strcpy(GlobalDynaStr[GlobalDynaCnt], join(9,"if (",CVar,") { DestroyArr((void **)",CVar,",",str(dms),", 1); ",CVar,"=NULL; }"));
              }
            AddGlobal(CVar,vt,id,"",dms,0,0,0);
          }
        if(!InTypeDef)
          {
            fprintf(Outfile,"%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",Scoot,CVar,"= (",SOF,stringx(dms,42),")CreateArr (",CVar,",sizeof(",SOF,"),0,",trim(str(dms)),",",ZZ,");");
          }
        break;
      }
    if(str_cmp(Lookup,"redim")==0)
      {
        int     IsPreserve;
        char SOF[2048];
         VarInfo*  VI;
        int     vt1=0;
        int     IsSplat=0;
        int     BC=0;
        int     StartPoint;
        int     AsPos=Ndx;
        HandleNonsense();
        IsPreserve=iMatchWrd(Stk[2],"preserve");
        StartPoint=2+IsPreserve;
        vt1=DataType(Stk[StartPoint]);
        strcpy(CVar,Clean(Stk[StartPoint]));
        IsSplat=iMatchWrd(Stk[StartPoint+1],"*");
        ValidVar(CVar);
        for(i=Ndx; i>=1; i+=-1)
          {
            if(iMatchWrd(Stk[AsPos],"as"))
              {
                AsPos=i-1;
                break;
              }
          }
        int     L=AsPos;
        int     SP=0;
        while(L>StartPoint)
          {
            if(str_cmp(Stk[L],"[")==0)
              {
                BC--;
              }
            else if(str_cmp(Stk[L],"]")==0)
              {
                BC++;
                if(BC==1)
                  {
                    L--;
                    continue;
                  }
              }
            if(BC==0)
              {
                SP++;
                if(str_cmp(Stk[L-1],"]")!=0)
                  {
                    break;
                  }
                strcpy(ZZ, join(2,",",ZZ));
              }
            else
              {
                strcpy(ZZ, join(2,Stk[L],ZZ));
              }
            L--;
          }
        vt=CheckLocal(CVar, &id);
        if(vt==vt_UNKNOWN)
          {
            vt=CheckGlobal(CVar, &id);
            if(vt==vt_UNKNOWN)
              {
                Abort(join(3,"Can not REDIM ",CVar," not previously dimensioned"));
              }
            VI= &GlobalVars[id];
          }
        else
          {
            VI= &LocalVars[id];
          }
        dms=VI->VarPntr;
        if(vt==vt_STRUCT||vt==vt_UDT||vt==vt_UNION)
          {
            strcpy(SOF,GetElement(StartPoint, &vt, &dms,VI->VarDef));
            i=Ndx;
            Ndx=L-1;
            AsmUnknownStructs(1);
            Ndx=i;
            RemEmptyTokens();
            strcpy(CVar,Clean(Stk[StartPoint]));
            IsSplat=iMatchWrd(Stk[StartPoint+1],"*");
          }
        else
          {
            strcpy(SOF,GetVarTypeName(vt));
          }
        if(iMatchWrd(Stk[Ndx-1],"as"))
          {
            if(str_cmp(SOF,Stk[Ndx])!=0 && !iMatchWrd(Stk[Ndx],"string"))
              {
                Abort(join(6,"Can not change types for variable ",CVar," previously defined as ",SOF," on line",str(VI->VarLine)));
              }
            if(iMatchWrd(Stk[Ndx],"string"))
              {
                Ndx--;
                strcpy(Stk[Ndx],"[");
                strcpy(Stk[++Ndx],"65535");
                strcpy(Stk[++Ndx],"]");
              }
            else
              {
                Ndx-=2;
              }
          }
        else
          {
            if((vt==vt_CHAR&&vt1==vt_STRVAR&&IsSplat==0)||vt==vt_CHARPTR)
              {
                Ndx++;
                strcpy(Stk[Ndx],"[");
                strcpy(Stk[++Ndx],"65535");
                strcpy(Stk[++Ndx],"]");
              }
          }
        if(str_cmp(Stk[3+IsPreserve],"[")==0)
          {
            if(IsPreserve)
              {
                StartPoint=4;
              }
            else
              {
                fprintf(Outfile,"%s%s%s%s%s%s%s%s%s%s\n",Scoot,"if (",CVar,") { DestroyArr((void **)",CVar,",",str(dms),", 1); ",CVar,"=NULL; }");
                StartPoint=3;
              }
            Use_DynamicA=TRUE;
            A=0;
            *ZZ=0;
            for(i=StartPoint; i<=Ndx; i+=1)
              {
                if(str_cmp(Stk[i],"[")==0)
                  {
                    A++;
                    i++;
                    BC=1;
                    while(BC>0)
                      {
                        if(str_cmp(Stk[i],"[")==0)
                          {
                            BC++;
                            strcat(ZZ,Stk[i]);
                          }
                        else
                          {
                            if(str_cmp(Stk[i],"]")==0)
                              {
                                BC--;
                                if(BC==0&&i<Ndx)
                                  {
                                    strcat(ZZ,",");
                                  }
                                if(BC)
                                  {
                                    strcat(ZZ,Stk[i]);
                                  }
                              }
                            else
                              {
                                strcat(ZZ,Stk[i]);
                              }
                          }
                        i++;
                      }
                    i--;
                  }
              }
            strcpy(ZZ,Clean(ZZ));
            if(vt==vt_STRLIT||vt==vt_DECFUNC||vt==vt_NUMBER||(vt==vt_VOID&&inchr(Stk[Ndx],"*")==0))
              {
                Abort(join(2,Stk[Ndx]," is not a valid type"));
              }
            if(vt==vt_STRVAR)
              {
                strcpy(SOF,"char");
                A++;
                strcat(ZZ,",65535");
              }
            if(A!=dms)
              {
                Abort(join(6,"Mismatch in dimensions for ",CVar,", orignally ",str(dms)," found ",str(A)));
              }
            fprintf(Outfile,"%s%s%s%s%s%s%s%s%s%s%s%s%d%s%s%s\n",Scoot,CVar,"= (",SOF,stringx(dms,42),")CreateArr (",CVar,",sizeof(",SOF,"),",trim(str(IsPreserve)),",",(int)dms,",",ZZ,");");
            break;
          }
        if(str_cmp(Stk[3],"*")==0 || (IsPreserve&&str_cmp(Stk[4],"*")==0))
          {
            if(IsPreserve)
              {
                fprintf(Outfile,"%s%s%s%s%s",Scoot,CVar,"=(char*)realloc(",CVar,",256+");
                i=5;
              }
            else
              {
                fprintf(Outfile,"%s%s%s%s\n",Scoot,"free(",CVar,");");
                fprintf(Outfile,"%s%s%s",Scoot,CVar,"=(char*)calloc(256+");
                i=4;
              }
            for(A=i; A<=Ndx; A+=1)
              {
                fprintf(Outfile,"%s",Clean(Stk[A]));
              }
            if(IsPreserve)
              {
                fprintf(Outfile,"%s\n",");");
              }
            else
              {
                fprintf(Outfile,"%s\n",",1);");
              }
            break;
          }
        Abort("Invalid REDIM statement");
        break;
      }
    if(str_cmp(Lookup,"dim")==0 ||  str_cmp(Lookup,"local")==0 ||  str_cmp(Lookup,"raw")==0 ||  str_cmp(Lookup,"static")==0 ||  str_cmp(Lookup,"auto")==0 ||  str_cmp(Lookup,"register")==0)
      {
        int     w=0;
        char UseStatic[2048];
        int     IsVolatile=0;
        char IV[2048];
        IsVolatile=iMatchWrd(Stk[2],"volatile");
        if(IsVolatile)
          {
            strcpy(IV,"volatile ");
          }
        else
          {
            *IV=0;
          }
        IsSubOrFuncPtr=SubFuncTest();
        HandleNonsense();
        if(str_cmp(Stk[Ndx],"*")==0)
          {
            PointerFix();
          }
        if(str_cmp(Stk[Ndx],"&")==0)
          {
            *Stk[Ndx--]=0;
            strcat(Stk[Ndx],"&");
          }
        IsRegister=IsAuto=IsDim=IsLocal=IsStatic=IsRaw=FALSE;
        strcpy(Cmd,lcase(Stk[1]));
        for(;;)
        {
          if(str_cmp(Cmd,"dim")==0)
            {
              IsDim=TRUE;
              break;
            }
          if(str_cmp(Cmd,"local")==0)
            {
              IsLocal=TRUE;
              break;
            }
          if(str_cmp(Cmd,"static")==0)
            {
              IsStatic=TRUE;
              break;
            }
          if(str_cmp(Cmd,"raw")==0)
            {
              IsRaw=TRUE;
              break;
            }
          if(str_cmp(Cmd,"auto")==0)
            {
              IsAuto=TRUE;
              break;
            }
          if(str_cmp(Cmd,"register")==0)
            {
              IsRegister=TRUE;
            }
          break;
        }
        if(InTypeDef)
          {
            if(iMatchWrd(Stk[2],"public")||iMatchWrd(Stk[2],"private")||iMatchWrd(Stk[2],"protected"))
              {
                fprintf(Outfile,"%s%s%s\n",LF,lcase(Stk[2]),":");
                break;
              }
            else if(iMatchWrd(Stk[2],"constructor")||iMatchWrd(Stk[2],"destructor"))
              {
                DimSubFunc(0);
                break;
              }
            else if(iMatchWrd(Stk[2],"virtual"))
              {
                *vproc=0;
                if(iMatchWrd(Stk[Ndx-1],"=")&&iMatchWrd(Stk[Ndx],"0"))
                  {
                    strcpy(vproc, join(2,Stk[Ndx-1],Stk[Ndx]));
                    Ndx-=2;
                  }
                  {int act;
                for(act=3; act<=Ndx; act+=1)
                  {
                    strcpy(Stk[act-1],Stk[act]);
                  }
                  }
                Ndx--;
                DimSubFunc(0);
                break;
              }
          }
        if(IsSubOrFuncPtr)
          {
            if(IsVolatile)
              {
                Abort("volatile SUB/FUNCTION pointers not supported");
              }
            if(DimSubFunc(0))
              {
                break;
              }
          }
        strcpy(CVar,Clean(Stk[2+IsVolatile]));
        ValidVar(CVar);
        VType=DataType(Stk[2+IsVolatile]);
        if(str_cmp(Stk[3+IsVolatile],"*")==0)
          {
            if(IsVolatile)
              {
                Abort("volatile dynamic strings not supported");
              }
            DimDynaString(CVar,0,0);
            break;
          }
        int     iASoffset=0;
        char sConst[2048];
        int     iIsConst;
        if(iMatchWrd(Stk[Ndx-1],"as"))
          {
            iASoffset=Ndx-1;
          }
        if(iMatchWrd(Stk[Ndx-2],"as"))
          {
            iASoffset=Ndx-2;
          }
        if(iASoffset)
          {
            iIsConst=0;
            *sConst=0;
            if(iASoffset==Ndx-2)
              {
                if(iMatchWrd(Stk[Ndx-1],"const"))
                  {
                    strcpy(sConst,"const");
                    iIsConst=1;
                  }
              }
            strcpy(Var1,CVar);
            IsPointer=tally(Stk[Ndx],"*");
            *DimType=0;
            *lszTmp=0;
            for(i=2+IsVolatile; i<=iASoffset-1; i+=1)
              {
                strcat(lszTmp,Stk[i]);
                if(i>2+IsVolatile)
                  {
                    strcat(DimType,Stk[i]);
                  }
              }
            strcpy(Var,RemoveStr(Stk[Ndx],"*"));
            GetTypeInfo(Var, &w, &id, &vt);
            if(vt==vt_STRVAR)
              {
                strcpy(Stk[Ndx],"char");
                strcpy(Var,Stk[Ndx]);
                strcat(DimType,"[65535]");
                strcat(lszTmp,"[65535]");
              }
            if(InFunc||InTypeDef)
              {
                if(IsRegister||IsAuto)
                  {
                    if(IsRegister)
                      {
                        if(IsVolatile)
                          {
                            Abort("Register volatile not supported");
                          }
                        if(vt==vt_FILEPTR)
                          {
                            fprintf(Outfile,"%s%s",Scoot,"register  FILE*   ");
                          }
                        else
                          {
                            fprintf(Outfile,"%s%s%s%s%s%s",Scoot,"register  ",sConst," ",Stk[Ndx],"  ");
                          }
                      }
                    else
                      {
                        if(vt==vt_FILEPTR)
                          {
                            fprintf(Outfile,"%s%s%s%s",Scoot,"auto ",IV,"  FILE*   ");
                          }
                        else
                          {
                            fprintf(Outfile,"%s%s%s%s%s%s%s%s",Scoot,"auto ",IV," ",sConst," ",Stk[Ndx],"  ");
                          }
                      }
                  }
                else
                  {
                    if(IsRaw==TRUE)
                      {
                        if(vt==vt_FILEPTR)
                          {
                            fprintf(Outfile,"%s%s%s%s",Scoot,"static ",IV,"  FILE*   ");
                          }
                        else
                          {
                            fprintf(Outfile,"%s%s%s%s%s%s",Scoot,IV,sConst," ",Stk[Ndx],"  ");
                          }
                      }
                    else
                      {
                        if(InTypeDef)
                          {
                            *UseStatic=0;
                          }
                        else
                          {
                            strcpy(UseStatic,"static  ");
                          }
                        if(vt==vt_STRUCT)
                          {
                            fprintf(Outfile,"%s%s%s%s%s%s%s%s",Scoot,UseStatic,IV,sConst," ","struct _",Stk[Ndx],"  ");
                          }
                        else
                          {
                            if(vt==vt_FILEPTR)
                              {
                                fprintf(Outfile,"%s%s%s%s",Scoot,UseStatic,IV,"FILE   *");
                              }
                            else
                              {
                                fprintf(Outfile,"%s%s%s%s%s%s%s",Scoot,UseStatic,IV,sConst," ",Stk[Ndx],"  ");
                              }
                          }
                        if(InTypeDef)
                          {
                            AddTypedefElement(BaseTypeDefsCnt[InTypeDef],vt,CVar,Var,0);
                          }
                      }
                  }
                if(InFunc&&!InTypeDef)
                  {
                    AddLocal(Var1,vt,id,DimType,IsPointer,0,0,iIsConst);
                  }
                fprintf(Outfile,"%s%s\n",Clean(lszTmp),";");
                if(!InTypeDef&&!IsStatic&&!IsRaw&&!IsRegister&&!IsVolatile)
                  {
                    strcpy(T,Clean(extract(lszTmp,"[")));
                    if(IsPointer)
                      {
                        fprintf(Outfile,"%s%s%s%s%s%s%s\n",Scoot,"memset(&",T,",0,sizeof(",Clean(Var)," *","));");
                      }
                    else
                      {
                        fprintf(Outfile,"%s%s%s%s%s%s\n",Scoot,"memset(&",T,",0,sizeof(",T,"));");
                      }
                  }
              }
            else
              {
                if(IsVolatile)
                  {
                    AddGlobal(Var1,vt,id,DimType,IsPointer,0,3,0,iIsConst);
                  }
                else
                  {
                    AddGlobal(Var1,vt,id,DimType,IsPointer,0,0,0,iIsConst);
                  }
              }
            break;
          }
        if(InFunc||InTypeDef)
          {
            *lszTmp=0;
            if(iMatchWrd(Stk[3+IsVolatile],"as"))
              {
                VType=CheckType(Stk[4+IsVolatile]);
                if(VType==vt_CHAR)
                  {
                    if(str_cmp(Stk[5],"*")==0)
                      {
                        strcpy(lszTmp, join(3,"[",Stk[6+IsVolatile],"]"));
                      }
                  }
              }
            else
              {
                for(i=3+IsVolatile; i<=Ndx; i+=1)
                  {
                    strcat(lszTmp,Stk[i]);
                  }
                strcpy(lszTmp,ltrim(Clean(lszTmp)));
                if(VType==vt_STRVAR)
                  {
                    if(str_cmp(lszTmp,"[65535]")!=0)
                      {
                        strcat(lszTmp,"[2048]");
                      }
                  }
              }
            j=(!InTypeDef BAND !IsStatic BAND !IsRaw BAND !IsRegister);
            if(j)
              {
                strcpy(T,Clean(extract(CVar,"[")));
              }
            for(;;)
            {
              if(VType==vt_STRVAR)
                {
                  if(IsRaw)
                    {
                      fprintf(Outfile,"%s%s%s%s%s%s\n",Scoot,IV,"char ",CVar,lszTmp,";");
                    }
                  else if(IsAuto)
                    {
                      fprintf(Outfile,"%s%s%s%s%s%s%s\n",Scoot,"auto ",IV,"char ",CVar,lszTmp,";");
                    }
                  else if(IsRegister)
                    {
                      if(IsVolatile)
                        {
                          Abort("register volatile not supported");
                        }
                      fprintf(Outfile,"%s%s%s%s%s\n",Scoot,"register char ",CVar,lszTmp,";");
                    }
                  else
                    {
                      if(InTypeDef)
                        {
                          fprintf(Outfile,"%s%s%s%s%s%s\n",Scoot,IV,"char ",CVar,lszTmp,";");
                        }
                      else
                        {
                          fprintf(Outfile,"%s%s%s%s%s%s%s\n",Scoot,"static ",IV,"char ",CVar,lszTmp,";");
                        }
                    }
                  if(j&&!IsVolatile)
                    {
                      fprintf(Outfile,"%s%s%s%s%s%s\n",Scoot,"memset(&",T,",0,sizeof(",T,"));");
                    }
                  break;
                }
              if(VType>=vt_VarMin&&VType<=vt_VarMax)
                {
                  strcpy(ZZ,GetVarTypeName(VType));
                  strcpy(ZZ,rpad(ZZ,7));
                  if(IsRaw)
                    {
                      fprintf(Outfile,"%s%s%s%s%s%s%s\n",Scoot,IV,ZZ," ",CVar,lszTmp,";");
                    }
                  else if(IsAuto)
                    {
                      fprintf(Outfile,"%s%s%s%s%s%s%s%s\n",Scoot,"auto ",IV,ZZ," ",CVar,lszTmp,";");
                    }
                  else if(IsRegister)
                    {
                      if(IsVolatile)
                        {
                          Abort("Regester volatile not supported");
                        }
                      fprintf(Outfile,"%s%s%s%s%s%s%s\n",Scoot,"register ",ZZ," ",CVar,lszTmp,";");
                    }
                  else
                    {
                      if(InTypeDef)
                        {
                          fprintf(Outfile,"%s%s%s%s%s%s%s\n",Scoot,IV,ZZ," ",CVar,lszTmp,";");
                        }
                      else
                        {
                          fprintf(Outfile,"%s%s%s%s%s%s%s%s\n",Scoot,"static ",IV,ZZ," ",CVar,lszTmp,";");
                        }
                    }
                  if(j&&!IsVolatile)
                    {
                      fprintf(Outfile,"%s%s%s%s%s%s\n",Scoot,"memset(&",T,",0,sizeof(",T,"));");
                    }
                }
              break;
            }
            if(InFunc&&!InTypeDef)
              {
                AddLocal(CVar,VType,0,lszTmp,0,0,0);
              }
            if(InTypeDef)
              {
                AddTypedefElement(BaseTypeDefsCnt[InTypeDef],VType,CVar,Var,0);
              }
            break;
          }
        *lszTmp=0;
        for(i=3+IsVolatile; i<=Ndx; i+=1)
          {
            strcat(lszTmp,Stk[i]);
          }
        if(VType==vt_STRVAR&&str_cmp(lszTmp,"")!=0)
          {
            strcat(lszTmp,"[65535]");
          }
        if(IsVolatile)
          {
            AddGlobal(CVar,VType,0,lszTmp,0,0,3,0);
          }
        else
          {
            AddGlobal(CVar,VType,0,lszTmp,0,0,0,0);
          }
        break;
      }
    if(str_cmp(Lookup,"extern")==0)
      {
        int     IsVolatile;
        IsSubOrFuncPtr=SubFuncTest();
        HandleNonsense();
        IsVolatile=iMatchWrd(Stk[2],"volatile");
        strcpy(CVar,Clean(Stk[2+IsVolatile]));
        ValidVar(CVar);
        if(str_cmp(Stk[Ndx],"*")==0)
          {
            PointerFix();
          }
        if(str_cmp(Stk[Ndx],"&")==0)
          {
            *Stk[Ndx--]=0;
            strcat(Stk[Ndx],"&");
          }
        if(str_cmp(Stk[3+IsVolatile],"*")==0)
          {
            if(IsVolatile)
              {
                Abort("volatile dynamic strings not supported");
              }
            DimDynaString(CVar,2,0);
            break;
          }
        if(IsSubOrFuncPtr)
          {
            if(IsVolatile)
              {
                Abort("volatile SUB/FUNCTION pointers not supported");
              }
            if(DimSubFunc(0))
              {
                break;
              }
          }
        strcpy(Var,Clean(Stk[2+IsVolatile]));
        ValidVar(Var);
        IsPointer=0;
        *DimType=0;
        if(iMatchWrd(Stk[Ndx-1],"as"))
          {
            GetTypeInfo(Stk[Ndx], &IsPointer, &id, &vt);
            strcpy(Stk[Ndx],RemoveStr(Stk[Ndx],"*"));
            for(i=3+IsVolatile; i<=Ndx-2; i+=1)
              {
                strcat(DimType,Stk[i]);
              }
          }
        else
          {
            i=3+IsVolatile;
            while(i<=Ndx)
              {
                strcat(DimType,Stk[i]);
                i++;
              }
            vt=DataType(Stk[2+IsVolatile]);
            id=0;
          }
        if(vt==vt_STRVAR)
          {
            strcat(DimType,"[65535]");
          }
        if(IsVolatile)
          {
            AddGlobal(Var,vt,id,DimType,IsPointer,0,4,0);
          }
        else
          {
            AddGlobal(Var,vt,id,DimType,IsPointer,0,1,0);
          }
        break;
      }
    if(str_cmp(Lookup,"shared")==0 ||  str_cmp(Lookup,"global")==0)
      {
        int     w=0;
        char SOF[2048];
        int     IsShared;
        int     IsVolatile;
        IsSubOrFuncPtr=SubFuncTest();
        HandleNonsense();
        IsVolatile=iMatchWrd(Stk[2],"volatile");
        strcpy(CVar,Clean(Stk[2+IsVolatile]));
        ValidVar(CVar);
        IsShared=iMatchWrd(Stk[1],"shared");
        if(str_cmp(Stk[Ndx],"*")==0)
          {
            PointerFix();
          }
        if(str_cmp(Stk[Ndx],"&")==0)
          {
            *Stk[Ndx--]=0;
            strcat(Stk[Ndx],"&");
          }
        if(str_cmp(Stk[3+IsVolatile],"*")==0)
          {
            if(IsVolatile)
              {
                Abort("volatile dynamic strings not supported");
              }
            DimDynaString(CVar,1,IsShared);
            break;
          }
        if(IsSubOrFuncPtr)
          {
            if(IsVolatile)
              {
                Abort("volatile SUB/FUNCTION pointers not supported");
              }
            DimSubFunc(0);
            break;
          }
        if(iMatchWrd(Stk[2],"dynamic"))
          {
            strcpy(CVar,Clean(Stk[3]));
            ValidVar(CVar);
            if(iMatchWrd(Stk[Ndx-1],"as"))
              {
                strcpy(SOF,Stk[Ndx]);
                GetTypeInfo(SOF, &w, &id, &vt);
                if(vt==vt_STRLIT||vt==vt_DECFUNC||vt==vt_NUMBER||(vt==vt_VOID&&inchr(Stk[Ndx],"*")==0))
                  {
                    Abort(join(2,Stk[Ndx]," is not a valid type"));
                  }
                Ndx-=2;
              }
            else
              {
                vt=DataType(Stk[3]);
                id=0;
                strcpy(SOF,GetVarTypeName(vt));
              }
            Use_DynamicA=TRUE;
            *ZZ=0;
            for(i=4; i<=Ndx; i+=1)
              {
                strcat(ZZ,Stk[i]);
              }
            dms=tally(ZZ,"][")+1;
            if(dms>1)
              {
                strcpy(ZZ,replace(ZZ,"][",","));
              }
            strcpy(ZZ,Clean(ZZ));
            RemoveAll(ZZ,"[]");
            if(vt==vt_STRVAR)
              {
                vt=vt_CHAR;
                strcpy(SOF,"char");
                dms++;
                strcat(ZZ,",65535");
              }
            if(Use_GenFree)
              {
                GlobalDynaCnt++;
                strcpy(GlobalDynaStr[GlobalDynaCnt], join(9,"if (",CVar,") { DestroyArr((void **)",CVar,",",str(dms),", 1); ",CVar,"=NULL; }"));
              }
            AddGlobal(CVar,vt,id,"",dms,0,0,0);
            fprintf(Outfile,"%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",Scoot,CVar,"= (",SOF,stringx(dms,42),")CreateArr (",CVar,",sizeof(",SOF,"),0,",trim(str(dms)),",",ZZ,");");
            break;
          }
        IsPointer=0;
        strcpy(Var,Clean(Stk[2+IsVolatile]));
        ValidVar(Var);
        if(iMatchWrd(Stk[Ndx-1],"as"))
          {
            if(inchr(Stk[Ndx],"*"))
              {
                IsPointer=tally(Stk[Ndx],"*");
                strcpy(Stk[Ndx],RemoveStr(Stk[Ndx],"*"));
              }
            *DimType=0;
            for(i=3+IsVolatile; i<=Ndx-2; i+=1)
              {
                strcat(DimType,Stk[i]);
              }
            GetTypeInfo(Stk[Ndx], &w, &id, &vt);
          }
        else
          {
            *DimType=0;
            i=3+IsVolatile;
            while(i<=Ndx)
              {
                strcat(DimType,Stk[i]);
                i++;
              }
            vt=DataType(Stk[2+IsVolatile]);
            id=0;
          }
        if(vt==vt_STRVAR)
          {
            strcat(DimType,"[65535]");
          }
        if(IsShared)
          {
            if(IsVolatile)
              {
                AddGlobal(Var,vt,id,DimType,IsPointer,0,5,0);
              }
            else
              {
                AddGlobal(Var,vt,id,DimType,IsPointer,0,2,0);
              }
          }
        else
          {
            if(IsVolatile)
              {
                AddGlobal(Var,vt,id,DimType,IsPointer,0,3,0);
              }
            else
              {
                AddGlobal(Var,vt,id,DimType,IsPointer,0,0,0);
              }
          }
        break;
      }
    if(str_cmp(Lookup,"while")==0)
      {
        EmitIfCond("while");
        break;
      }
    if(str_cmp(Lookup,"wend")==0 ||  str_cmp(Lookup,"endwhile")==0)
      {
        BumpDown();
        fprintf(Outfile,"%s%s\n",Scoot,"}");
        BumpDown();
        break;
      }
    if(str_cmp(Lookup,"exit")==0)
      {
        if(CaseFlag)
          {
            NoBreak2=TRUE;
          }
        if(iMatchWrd(Stk[2],"sub"))
          {
            if(LocalDynaCnt!=0)
              {
                for(j=1; j<=LocalDynaCnt; j+=1)
                  {
                    fprintf(Outfile,"%s%s\n",Scoot,DynaStr[j]);
                  }
              }
            if(LocalDynArrCount!=0)
              {
                for(i=1; i<=LocalDynArrCount; i+=1)
                  {
                    fprintf(Outfile,"%s%s\n",Scoot,LocalDynArrName[i]);
                  }
              }
            fprintf(Outfile,"%s%s\n",Scoot,"return;");
            break;
          }
        if(iMatchWrd(Stk[2],"function"))
          {
            if(LocalDynaCnt!=0)
              {
                for(j=1; j<=LocalDynaCnt; j+=1)
                  {
                    fprintf(Outfile,"%s%s\n",Scoot,DynaStr[j]);
                  }
              }
            if(LocalDynArrCount!=0)
              {
                for(i=1; i<=LocalDynArrCount; i+=1)
                  {
                    fprintf(Outfile,"%s%s\n",Scoot,LocalDynArrName[i]);
                  }
              }
            fprintf(Outfile,"%s%s\n",Scoot,"return 0;");
          }
        else
          {
            fprintf(Outfile,"%s%s\n",Scoot,"break;");
          }
        break;
      }
    if(str_cmp(Lookup,"goto")==0)
      {
        if(CaseFlag)
          {
            NoBreak2=TRUE;
          }
        fprintf(Outfile,"%s%s%s%s\n",Scoot,"goto ",ucase(Stk[2]),";");
        break;
      }
    if(str_cmp(Lookup,"print")==0)
      {
        fprintf(Outfile,"%s%s\n",Scoot,PrintWriteFormat(0));
        break;
      }
    if(str_cmp(Lookup,"write")==0)
      {
        fprintf(Outfile,"%s%s\n",Scoot,PrintWriteFormat(1));
        break;
      }
    if(str_cmp(Lookup,"run")==0)
      {
        fprintf(Outfile,"%s%s",Scoot,"Run (");
        for(A=2; A<=Ndx; A+=1)
          {
            fprintf(Outfile,"%s",Clean(Stk[A]));
          }
        fprintf(Outfile,"%s%s\n",Scoot,");");
        break;
      }
    if(str_cmp(Lookup,"color")==0)
      {
        fprintf(Outfile,"%s%s",Scoot,"color (");
        for(A=2; A<=Ndx; A+=1)
          {
            fprintf(Outfile,"%s",Clean(Stk[A]));
          }
        fprintf(Outfile,"%s\n",");");
        break;
      }
    if(str_cmp(Lookup,"locate")==0)
      {
        fprintf(Outfile,"%s%s",Scoot,"locate (");
        for(A=2; A<=Ndx; A+=1)
          {
            fprintf(Outfile,"%s",Clean(Stk[A]));
          }
        fprintf(Outfile,"%s\n",");");
        break;
      }
    if(str_cmp(Lookup,"cls")==0)
      {
        fprintf(Outfile,"%s%s\n",Scoot,"cls();");
        break;
      }
      // case else
      {
        for(B=1; B<=Ndx; B+=1)
          {
            if(str_cmp(Stk[B],"=")==0)
              {
                break;
              }
          }
        if(B-1==Ndx)
          {
            *lszTmp=0;
            for(Tmp=1; Tmp<=Ndx; Tmp+=1)
              {
                strcat(lszTmp,Clean(Stk[Tmp]));
              }
            strcat(lszTmp,";");
            if(FuncRetnFlag==2)
              {
                fprintf(Outfile,"%s\n",lszTmp);
              }
            else
              {
                fprintf(Outfile,"%s%s\n",Scoot,lszTmp);
              }
            if(FuncRetnFlag==2)
              {
                FuncRetnFlag=0;
                *Stk[1]=0;
                if(ZZ)free(ZZ);
                return;
              }
            break;
          }
        for(i=2; i<=B-1; i+=1)
          {
            strcat(Stk[1],Stk[i]);
          }
        A=inchr(Stk[1],"*");
        if(A)
          {
            if(!(inchr(Stk[1],"$")&&A>1))
              {
                RemoveAll(Stk[1],"$");
                goto PROCESSNUMERIC;
              }
          }
        static int     strtest;
        memset(&strtest,0,sizeof(strtest));
        static int     varid;
        memset(&varid,0,sizeof(varid));
        static   struct _VarInfo*  vi;
        memset(&vi,0,sizeof(VarInfo *));
        static char vr[2048];
        memset(&vr,0,sizeof(vr));
        static int     brcnt;
        memset(&brcnt,0,sizeof(brcnt));
        strtest=DataType(Stk[1]);
        if(strtest==vt_INTEGER)
          {
            brcnt=tally(Stk[1],"[");
            strcpy(vr,extract(Stk[1],"["));
            strtest=CheckLocal(vr, &varid);
            if(strtest==vt_UNKNOWN)
              {
                strtest=CheckGlobal(vr, &varid);
                vi= &(GlobalVars[varid]);
              }
            else
              {
                vi= &(LocalVars[varid]);
              }
            if(strtest==vt_CHAR)
              {
                strtest=vt_STRVAR;
              }
            if(strtest==vt_STRVAR)
              {
                if(vi->VarPntr!=0)
                  {
                    goto PROCESSNUMERIC;
                  }
                if(tally(vi->VarDim,"[")==brcnt)
                  {
                    goto PROCESSNUMERIC;
                  }
                if(tally(vi->VarDim,"[")!=brcnt+1)
                  {
                    goto PROCESSNUMERIC;
                  }
              }
          }
        if(strtest==vt_STRVAR)
          {
            if(B+1==Ndx)
              {
                if(str_cmp(Stk[Ndx],DDQ)==0)
                  {
                    fprintf(Outfile,"%s%s%s%s\n",Scoot,"*",Clean(Stk[1]),"=0;");
                    goto STRINGEXIT;
                  }
              }
            if(Ndx==3)
              {
                strcpy(Stk[1],Clean(Stk[1]));
                strcpy(Stk[3],Clean(Stk[3]));
                if(str_cmp(Stk[1],"BCX_RetStr")==0)
                  {
                    fprintf(Outfile,"%s%s%s%s\n",Scoot,"BCX_RetStr=BCX_TmpStr(strlen(",Stk[3],"));");
                  }
                fprintf(Outfile,"%s%s%s%s%s%s\n",Scoot,"strcpy(",Stk[1],",",Stk[3],");");
                goto STRINGEXIT;
              }
            *Arg=0;
            *lszTmp=0;
            j=k=0;
            if(iMatchLft(Stk[3],"$$"))
              {
                HasStorage=TRUE;
              }
            strcpy(Var,Clean(Stk[1]));
            if(str_cmp(Clean(Stk[B+1]),Var)==0)
              {
                k=TRUE;
              }
            for(A=B+1; A<=Ndx; A+=1)
              {
                if(str_cmp(Stk[A],"&")==0 &&  str_cmp(Stk[A-1],",")!=0 &&  str_cmp(Stk[A-1],"(")!=0)
                  {
                    j++;
                    strcat(Arg,lszTmp);
                    strcpy(lszTmp,",");
                  }
                else
                  {
                    strcat(lszTmp,Clean(Stk[A]));
                  }
              }
            if(*lszTmp!=0&&str_cmp(lszTmp,",")!=0)
              {
                strcat(Arg,lszTmp);
              }
            RemoveAll(Var,SPC);
            if(j==0)
              {
                if(str_cmp(Var,"BCX_RetStr")==0)
                  {
                    if(HasStorage)
                      {
                        fprintf(Outfile,"%s%s%s%s\n",Scoot,"BCX_RetStr=",Arg,";");
                        goto STRINGEXIT;
                      }
                    else
                      {
                        fprintf(Outfile,"%s%s%s%s\n",Scoot,"BCX_RetStr=BCX_TmpStr(strlen(",Arg,"));");
                      }
                  }
                fprintf(Outfile,"%s%s%s%s%s%s\n",Scoot,"strcpy(",Var,",",Arg,");");
                goto STRINGEXIT;
              }
            if(k==TRUE&&j==1)
              {
                fprintf(Outfile,"%s%s%s%s\n",Scoot,"strcat(",Arg,");");
                goto STRINGEXIT;
              }
            strcpy(lszTmp,ltrim(str(++j)));
            Use_Join=TRUE;
            if(str_cmp(Var,"BCX_RetStr")==0)
              {
                fprintf(Outfile,"%s%s%s%s%s%s\n",Scoot,"BCX_RetStr=join(",lszTmp,",",Arg,");");
              }
            else
              {
                fprintf(Outfile,"%s%s%s%s%s%s%s%s\n",Scoot,"strcpy(",Var,", join(",lszTmp,",",Arg,"));");
              }

STRINGEXIT:;
            break;
          }
        else
          {

PROCESSNUMERIC:;
            for(i=2; i<=B; i+=1)
              {
                *Stk[i]=0;
              }
            strcpy(Stk[B],"=");
            if(str_cmp(Stk[B+1],Stk[1])==0 && Ndx==5)
              {
                if(Inset(Stk[B+2],"+-*/")&&str_cmp(Stk[B+3],">")!=0)
                  {
                    strcpy(Stk[B], join(2,Stk[B+2],Stk[B]));
                    *Stk[B+1]=0;
                    *Stk[B+2]=0;
                  }
              }
            fprintf(Outfile,"%s%s",Scoot,Clean(Stk[1]));
            for(A=2; A<=Ndx; A+=1)
              {
                if(str_cmp(Stk[A],"!")==0)
                  {
                    fprintf(Outfile,"%s","!");
                  }
                else
                  {
                    fprintf(Outfile,"%s",Clean(Stk[A]));
                  }
              }
            fprintf(Outfile,"%s\n",";");
          }
      }
    break;
  }
  if(FuncRetnFlag==1)
    {
      if(LocalDynaCnt!=0)
        {
          for(j=1; j<=LocalDynaCnt; j+=1)
            {
              fprintf(Outfile,"%s%s\n",Scoot,DynaStr[j]);
            }
        }
      fprintf(Outfile,"%s%s\n",Scoot,"return BCX_RetStr;");
    }
  if(ZZ)free(ZZ);
}


void Abort (char *Z)
{
  int     i=0;
  int     j=0;
  int     k=0;
  int     varnum=0;
  char t[2048];
  char frmt[2048];
  *WarnMsg=0;
  if(str_cmp(left(AbortSrc,11),"$BCXVERSION")==0)
    {
      strcat(WarnMsg,Z);
    }
  else
    {
      strcpy(WarnMsg, join(7,WarnMsg,Z," at line",str(ModuleLineNos[ModuleNdx])," in Module: ",trim(Modules[ModuleNdx]),CRLF));
      strcpy(WarnMsg, join(3,WarnMsg,"Original line",CRLF));
      strcpy(WarnMsg, join(3,WarnMsg,AbortSrc,CRLF));
      strcpy(WarnMsg, join(3,WarnMsg,"==============",CRLF));
      strcpy(WarnMsg, join(3,WarnMsg,"Current Tokens",CRLF));
      strcpy(WarnMsg, join(3,WarnMsg,"==============",CRLF));
      for(k=1; k<=Ndx; k+=1)
        {
          j=strlen(Stk[k]);
          if(j<40)
            {
              j=40-j;
            }
          else
            {
              j=8-imod(j,8);
            }
          strcpy(frmt,lpad(str(k),3));
          strcpy(WarnMsg, join(6,WarnMsg,frmt," ",Stk[k],stringx(j,32),CRLF));
          strcpy(t,Clean(Stk[k]));
          i=CheckLocal(t, &varnum);
          if(i!=vt_UNKNOWN)
            {
              strcpy(WarnMsg, join(3,WarnMsg,"is a LOCAL defined at line",str(LocalVars[varnum].VarLine)));
              strcpy(WarnMsg, join(4,WarnMsg," in Module: ",LocalVars[varnum].VarModule,CRLF));
            }
          else
            {
              i=CheckGlobal(t, &varnum);
              if(i!=vt_UNKNOWN)
                {
                  strcpy(WarnMsg, join(3,WarnMsg,"is a GLOBAL defined at line",str(GlobalVars[varnum].VarLine)));
                  strcpy(WarnMsg, join(4,WarnMsg," in Module: ",GlobalVars[varnum].VarModule,CRLF));
                  strcpy(WarnMsg, join(5,WarnMsg," ",Stk[k],GlobalVars[varnum].VarDim," as "));
                  if(GlobalVars[varnum].VarDef)
                    {
                      strcpy(WarnMsg, join(3,WarnMsg,trim(TypeDefs[GlobalVars[varnum].VarDef].VarName),CRLF));
                    }
                  else
                    {
                      strcpy(WarnMsg, join(3,WarnMsg,trim(GetVarTypeName(GlobalVars[varnum].VarType)),CRLF));
                    }
                }
              else
                {
                  if(Stk[k][0]==34)
                    {
                      strcpy(WarnMsg, join(3,WarnMsg,"is a STRING LITERAL",CRLF));
                    }
                }
            }
        }
      strcpy(WarnMsg, join(3,WarnMsg,"===============",CRLF));
      strcpy(WarnMsg, join(3,WarnMsg,"Original Tokens",CRLF));
      strcpy(WarnMsg, join(3,WarnMsg,"===============",CRLF));
      XParse(AbortSrc);
      for(k=1; k<=Ndx; k+=1)
        {
          j=strlen(Stk[k]);
          if(j<40)
            {
              j=40-j;
            }
          else
            {
              j=8-imod(j,8);
            }
          strcpy(frmt,lpad(str(k),3));
          strcpy(WarnMsg, join(6,WarnMsg,frmt," ",Stk[k],stringx(j,32),CRLF));
          strcpy(t,Clean(Stk[k]));
          i=CheckLocal(t, &varnum);
          if(i!=vt_UNKNOWN)
            {
              strcpy(WarnMsg, join(3,WarnMsg,"is a LOCAL defined at line",str(LocalVars[varnum].VarLine)));
              strcpy(WarnMsg, join(4,WarnMsg," in Module: ",LocalVars[varnum].VarModule,CRLF));
            }
          else
            {
              i=CheckGlobal(t, &varnum);
              if(i!=vt_UNKNOWN)
                {
                  strcpy(WarnMsg, join(3,WarnMsg,"is a GLOBAL defined at line",str(GlobalVars[varnum].VarLine)));
                  strcpy(WarnMsg, join(4,WarnMsg," in Module: ",GlobalVars[varnum].VarModule,CRLF));
                  strcpy(WarnMsg, join(5,WarnMsg," ",Stk[k],GlobalVars[varnum].VarDim," as "));
                  if(GlobalVars[varnum].VarDef)
                    {
                      strcpy(WarnMsg, join(3,WarnMsg,TypeDefs[GlobalVars[varnum].VarDef].VarName,CRLF));
                    }
                  else
                    {
                      strcpy(WarnMsg, join(3,WarnMsg,GetVarTypeName(GlobalVars[varnum].VarType),CRLF));
                    }
                }
              else
                {
                  if(Stk[k][0]==34)
                    {
                      strcpy(WarnMsg, join(3,WarnMsg,"is a string literal",CRLF));
                    }
                }
            }
        }
    }
  strcat(WarnMsg,CRLF);
  CloseAll();
  remove (ovrFile);
  remove (FileOut);
  remove (prcFile);
  remove (udtFile);
  remove (hdrFile);
  remove (cstFile);
  remove (datFile);
  remove (setFile);
  remove (enuFile);
  remove ("$t$e$m$p");
  if(ErrFile)
    {
      if((fpErr=fopen(FileErr,"a"))==0)
       {
         fprintf(stderr,"Can't open file %s\n",FileErr);
         exit(1);
       }
      fprintf(fpErr,"%s%s%d%s%s\n",Z," at line",(int)ModuleLineNos[ModuleNdx]," in Module: ",trim(Modules[ModuleNdx]));
      if(fpErr)
       {
         fclose(fpErr);
         fpErr=NULL;
       }
    }
  printf("%s%s%s%s%s\n","Error!",CRLF,FileIn,CRLF,WarnMsg);
  FreeGlobals();
  fflush(stdout);
  exit(1);
}


void BumpDown (void)
{
  Indent--;
  Indent--;
  if(Indent<0)
    {
      Indent=0;
    }
  strcpy(Scoot,space(Indent));
}


void BumpUp (void)
{
  if(Indent<0)
    {
      Indent=0;
    }
  Indent++;
  Indent++;
  strcpy(Scoot,space(Indent));
}


int BraceCount (char *Arg)
{
   char*  p;
  int     braces;
  p=Arg;
  braces=0;
  while(*p)
    {
      if(*p==c_DblQt)
        {
          p++;
          while(*p!=c_DblQt)
            {
              if(*p==0)
                {
                  return braces;
                }
              p++;
            }
        }
      if(*p==125)
        {
          braces--;
        }
      if(*p==123)
        {
          braces++;
        }
      p++;
    }
  return braces;
}


char* BracketHandler (char *Src, int l)
{
   char*  s;
  s=Src;
  for(;;)
  {
    if(l==0)
      {
        for(;;)
          {
            if(*s==0)
              {
                break;
              }
            if(*s==c_DblQt)
              {
                s++;
                while(*s!=c_DblQt)
                  {
                    if(*s==0)
                      {
                        break;
                      }
                    s++;
                  }
              }
            if(*s==c_LtBkt)
              {
                s++;
                s=BracketHandler(s,1);
              }
            if(*s==c_LPar)
              {
                s++;
                s=BracketHandler(s,2);
              }
            s++;
          }
        break;
      }
    if(l==1)
      {
        while(*s!=c_RtBkt)
          {
            if(*s==c_DblQt)
              {
                s++;
                while(*s!=c_DblQt)
                  {
                    if(*s==0)
                      {
                        break;
                      }
                    s++;
                  }
              }
            if(*s==c_LtBkt)
              {
                s++;
                s=BracketHandler(s,1);
              }
            if(*s==c_LPar)
              {
                s++;
                s=BracketHandler(s,2);
              }
            if(*s==c_Komma)
              {
                *s=1;
              }
            if(*s==0)
              {
                break;
              }
            s++;
          }
        break;
      }
    if(l==2)
      {
        while(*s!=c_RPar)
          {
            if(*s==c_DblQt)
              {
                s++;
                while(*s!=c_DblQt)
                  {
                    if(*s==0)
                      {
                        break;
                      }
                    s++;
                  }
              }
            if(*s==c_LtBkt)
              {
                s++;
                s=BracketHandler(s,1);
              }
            if(*s==c_LPar)
              {
                s++;
                s=BracketHandler(s,2);
              }
            if(*s==0)
              {
                break;
              }
            s++;
          }
      }
    break;
  }
  if(l==0)
    {
      strcpy(Src,replace(Src,chr(1),"]["));
      return Src;
    }
  return s;
}


void Push (char *Z)
{
  strcpy(CaseStk[++Pusher],Z);
}


void Pop (char *Z)
{
  strcpy(Z,CaseStk[--Pusher]);
}


void EmitEpilog (void)
{
  if(NoMain+EndOfProgram==0)
    {
      fprintf(Outfile,"%s\n","return 0;   //  End of main program");
      BumpDown();
      fprintf(Outfile,"%s\n","}");
      fflush(Outfile);
    }
}


void EmitProlog (void)
{
  fprintf(Outfile,"%s\n","");
  fprintf(Outfile,"%s\n","int main(int argc, char *argv[])");
  fflush(Outfile);
}


void DeclareVariables (void)
{
  int     i;
  int     A;
  char P[2048];
  char VarName[2048];
  char VarDim[2048];
  char Storage[2048];
  if((FP1=fopen(FileOut,"r"))==0)
   {
     fprintf(stderr,"Can't open file %s\n",FileOut);
     exit(1);
   }
  if((Outfile=fopen("$t$e$m$p","w"))==0)
   {
     fprintf(stderr,"Can't open file %s\n","$t$e$m$p");
     exit(1);
   }
  if((FP3=fopen(cstFile,"r"))==0)
   {
     fprintf(stderr,"Can't open file %s\n",cstFile);
     exit(1);
   }
  if(lof(cstFile)>0)
    {
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","// *************************************************");
      fprintf(Outfile,"%s%s\n","//            ",BCX_STR_USR_CONST);
      fprintf(Outfile,"%s\n","// *************************************************");
      fprintf(Outfile,"%s\n","");
    }
  while(!EoF(FP3))
    {
      Z[0]=0;
      AR_fgets_retval=fgets(Z,65535,FP3);
      if(Z[strlen(Z)-1]==10)Z[strlen(Z)-1]=0;
      fprintf(Outfile,"%s\n",ltrim(Z));
    }
  if(FP3)
   {
     fclose(FP3);
     FP3=NULL;
   }
  if(Use_EnumFile)
    {
      fprintf(Outfile,"%s\n","// *************************************************");
      fprintf(Outfile,"%s\n","//        User's GLOBAL ENUM blocks");
      fprintf(Outfile,"%s\n","// *************************************************");
      if((FP8=fopen(enuFile,"r"))==0)
       {
         fprintf(stderr,"Can't open file %s\n",enuFile);
         exit(1);
       }
      while(!EoF(FP8))
        {
          Z[0]=0;
          AR_fgets_retval=fgets(Z,65535,FP8);
          if(Z[strlen(Z)-1]==10)Z[strlen(Z)-1]=0;
          fprintf(Outfile,"%s\n",Z);
        }
      if(FP8)
       {
         fclose(FP8);
         FP8=NULL;
       }
      fprintf(Outfile,"%s\n","");
    }
  if((FP3=fopen(udtFile,"r"))==0)
   {
     fprintf(stderr,"Can't open file %s\n",udtFile);
     exit(1);
   }
  if(lof(udtFile)>0)
    {
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","// *************************************************");
      fprintf(Outfile,"%s%s\n","//   ",BCX_STR_USR_TYPES);
      fprintf(Outfile,"%s\n","// *************************************************");
      while(!EoF(FP3))
        {
          Z[0]=0;
          AR_fgets_retval=fgets(Z,65535,FP3);
          if(Z[strlen(Z)-1]==10)Z[strlen(Z)-1]=0;
          fprintf(Outfile,"%s%s\n",Scoot,Z);
        }
    }
  if(FP3)
   {
     fclose(FP3);
     FP3=NULL;
   }
  if(HFileCnt>0)
    {
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","// *************************************************");
      fprintf(Outfile,"%s\n","//                User Include Files");
      fprintf(Outfile,"%s\n","// *************************************************");
      fprintf(Outfile,"%s\n","");
      A=0;
      while(A<HFileCnt)
        {
          fprintf(Outfile,"%s\n",HFiles[A]);
          A++;
        }
      fprintf(Outfile,"%s\n","#include <term.h>");
    }
  if(Use_SingleFile==TRUE)
    {
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","// *************************************************");
      fprintf(Outfile,"%s%s\n","//                ",BCX_STR_SYS_VARS);
      fprintf(Outfile,"%s\n","// *************************************************");
      fprintf(Outfile,"%s\n","");
      if(Use_RegEx)
        {
          fprintf(Outfile,"%s\n","typedef struct _REGEX");
          fprintf(Outfile,"%s\n","{");
          fprintf(Outfile,"%s\n","   int         count;");
          fprintf(Outfile,"%s\n","   regmatch_t  matches[1024];");
          fprintf(Outfile,"%s\n","   PCHAR       results[1024];");
          fprintf(Outfile,"%s\n","}REGEX, *LPREGEX;\n");
        }
      if(Use_Time)
        {
          fprintf(Outfile,"%s\n","enum TIME_OPTIONS");
          fprintf(Outfile,"%s\n","{");
          fprintf(Outfile,"%s\n","  TIME,");
          fprintf(Outfile,"%s\n","  HOUR,");
          fprintf(Outfile,"%s\n","  MINUTE,");
          fprintf(Outfile,"%s\n","  SECOND,");
          fprintf(Outfile,"%s\n","  APM,");
          fprintf(Outfile,"%s\n","  YEAR,");
          fprintf(Outfile,"%s\n","  MONTH,");
          fprintf(Outfile,"%s\n","  DAY,");
          fprintf(Outfile,"%s\n","  DAYNAME,");
          fprintf(Outfile,"%s\n","  WEEKDAY,");
          fprintf(Outfile,"%s\n","  YEARDAY,");
          fprintf(Outfile,"%s\n","  WEEKNUMBER,");
          fprintf(Outfile,"%s\n","  DATE,");
          fprintf(Outfile,"%s\n","  FULLDATE");
          fprintf(Outfile,"%s\n"," };\n");
        }
      if(Use_Findfirst||Use_Findnext)
        {
          fprintf(Outfile,"%s\n","typedef struct _FILE_FIND_DATA");
          fprintf(Outfile,"%s\n","{");
          fprintf(Outfile,"%s\n","  DWORD  dwFileAttributes;");
          fprintf(Outfile,"%s\n","  DWORD  ftCreationTime;");
          fprintf(Outfile,"%s\n","  DWORD  ftLastAccessTime;");
          fprintf(Outfile,"%s\n","  DWORD  ftLastWriteTime;");
          fprintf(Outfile,"%s\n","  DWORD  nFileSizeHigh;");
          fprintf(Outfile,"%s\n","  DWORD  nFileSizeLow;");
          fprintf(Outfile,"%s\n","  char   cFileSpec[MAX_PATH];");
          fprintf(Outfile,"%s\n","  char   cFileName[MAX_PATH];");
          fprintf(Outfile,"%s\n","  char   path[MAX_PATH];");
          fprintf(Outfile,"%s\n","  DIR   *FileHandle;");
          fprintf(Outfile,"%s\n","}FILE_FIND_DATA, *LPFILE_FIND_DATA;\n");
        }
      if(Use_Ldouble)
        {
          fprintf(Outfile,"%s\n","#define LDOUBLE long double");
        }
      if(Use_Idxqsort)
        {
          fprintf(Outfile,"%s\n","char*** pppStr;");
        }
      if(Use_Idxqsort||Use_IdxqsortSt||Use_PtrqsortSt)
        {
          fprintf(Outfile,"%s\n","int     Key;");
        }
      if(Use_IdxqsortSt)
        {
          fprintf(Outfile,"%s\n","char*   cmp1;");
          fprintf(Outfile,"%s\n","int     StructSize;");
        }
      if(Use_PtrqsortSt)
        {
          fprintf(Outfile,"%s\n","int     OffSet;");
        }
      if(Use_NUL)
        {
          fprintf(Outfile,"%s\n","char    NUL [1]={0};     // Null");
        }
      if(Use_BEL)
        {
          fprintf(Outfile,"%s\n","char    BEL [2]={7,0};   // Bell");
        }
      if(Use_BS)
        {
          fprintf(Outfile,"%s\n","char    BS  [2]={8,0};   // Back Space");
        }
      if(Use_TAB)
        {
          fprintf(Outfile,"%s\n","char    TAB [2]={9,0};   // Horz Tab");
        }
      if(Use_LF)
        {
          fprintf(Outfile,"%s\n","char    LF  [2]={10,0};  // Line Feed");
        }
      if(Use_VT)
        {
          fprintf(Outfile,"%s\n","char    VT  [2]={11,0};  // Vert Tab");
        }
      if(Use_FF)
        {
          fprintf(Outfile,"%s\n","char    FF  [2]={12,0};  // Form Feed");
        }
      if(Use_CR)
        {
          fprintf(Outfile,"%s\n","char    CR  [2]={13,0};  // Carr Rtn");
        }
      if(Use_EOF)
        {
          fprintf(Outfile,"%s\n","char    EF  [2]={26,0};  // End-of-File");
        }
      if(Use_ESC)
        {
          fprintf(Outfile,"%s\n","char    ESC [2]={27,0};  // Escape");
        }
      if(Use_SPC)
        {
          fprintf(Outfile,"%s\n","char    SPC [2]={32,0};  // Space");
        }
      if(Use_DQ)
        {
          fprintf(Outfile,"%s\n","char    DQ  [2]={34,0};  // Double-Quote");
        }
      if(Use_DDQ)
        {
          fprintf(Outfile,"%s\n","char    DDQ [3]={34,34,0}; // Double-Double-Quote");
        }
      if(Use_Crlf)
        {
          fprintf(Outfile,"%s\n","char    CRLF[3]={13,10,0}; // Carr Rtn & Line Feed");
        }
      if(Use_Console)
        {
          fprintf(Outfile,"%s\n","int     color_fg = 7;");
          fprintf(Outfile,"%s\n","int     color_bg = 0;");
        }
      if(Use_Lineinput)
        {
          fprintf(Outfile,"%s\n","char    *AR_fgets_retval;");
        }
      if(Use_Scan)
        {
          fprintf(Outfile,"%s\n","int     ScanError;");
        }
      if(Use_Inputbuffer==TRUE)
        {
          fprintf(Outfile,"%s\n","char    InputBuffer[65535];");
        }
      if(Use_Findfirst||Use_Findnext)
        {
          fprintf(Outfile,"%s\n","FILE_FIND_DATA FindData;");
        }
      if(Use_Gosub)
        {
          fprintf(Outfile,"%s\n","jmp_buf GosubStack[32];");
          fprintf(Outfile,"%s\n","int     GosubNdx;");
        }
      if(Use_Dynacall)
        {
          fprintf(Outfile,"%s\n","HINSTANCE BCX_DllStore[256];");
        }
    }
  if(GlobalVarCnt)
    {
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","// *************************************************");
      fprintf(Outfile,"%s%s\n","//            ",BCX_STR_USR_VARS);
      fprintf(Outfile,"%s\n","// *************************************************");
      fprintf(Outfile,"%s\n","");
    }
  for(i=1; i<=GlobalVarCnt; i+=1)
    {
      if(GlobalVars[i].VarEmitFlag)
        {
          continue;
        }
      if(str_cmp("",GlobalVars[i].VarDim)==0 && GlobalVars[i].VarCondLevel==0)
        {
          *P=0;
          if(GlobalVars[i].VarPntr)
            {
              strcpy(P,stringx(GlobalVars[i].VarPntr,42));
            }
          A=GlobalVars[i].VarType;
          if(GlobalVars[i].VarSF)
            {
              strcpy(VarName, join(3,"(*",GlobalVars[i].VarName,")"));
            }
          else
            {
              strcpy(VarName,GlobalVars[i].VarName);
            }
          strcpy(Storage, join(2,VarStorage[GlobalVars[i].VarExtn],VarConst[GlobalVars[i].VarConstant]));
          strcpy(VarDim,GlobalVars[i].VarDim);
          PrintGlobal(A,i,Storage,P,VarName,VarDim);
        }
    }
  for(i=1; i<=GlobalVarCnt; i+=1)
    {
      if(GlobalVars[i].VarEmitFlag)
        {
          continue;
        }
      if(str_cmp("",GlobalVars[i].VarDim)!=0 && GlobalVars[i].VarCondLevel==0)
        {
          if(instr_b(GlobalVars[i].VarDim,"{")==0)
            {
              *P=0;
              if(GlobalVars[i].VarPntr)
                {
                  strcpy(P,stringx(GlobalVars[i].VarPntr,42));
                }
              A=GlobalVars[i].VarType;
              if(GlobalVars[i].VarSF)
                {
                  strcpy(VarName, join(4,"(*",GlobalVars[i].VarName,extract(GlobalVars[i].VarDim,"("),")"));
                  strcpy(VarDim,mid(GlobalVars[i].VarDim,instr_b(GlobalVars[i].VarDim,"(")));
                }
              else
                {
                  strcpy(VarName,GlobalVars[i].VarName);
                  strcpy(VarDim,GlobalVars[i].VarDim);
                }
              strcpy(Storage, join(2,VarStorage[GlobalVars[i].VarExtn],VarConst[GlobalVars[i].VarConstant]));
              PrintGlobal(A,i,Storage,P,VarName,VarDim);
            }
        }
    }
  char LastDef[2048];
  int     LastLevel;
  *LastDef=0;
  LastLevel=1;
  for(i=1; i<=GlobalVarCnt; i+=1)
    {
      if(GlobalVars[i].VarEmitFlag)
        {
          continue;
        }
      if(GlobalVars[i].VarCondLevel)
        {
          if(LastDef[0]==0)
            {
              strcpy(LastDef,GlobalVars[i].VarCondDef);
              LastLevel=GlobalVars[i].VarCondLevel;
              fprintf(Outfile,"%s\n",LastDef);
            }
          if(str_cmp(LastDef,GlobalVars[i].VarCondDef)!=0)
            {
              if(str_cmp(GlobalVars[i].VarCondDef,"#else")==0)
                {
                  while(LastLevel>GlobalVars[i].VarCondLevel)
                    {
                      fprintf(Outfile,"%s\n","#endif");
                      LastLevel--;
                    }
                  fprintf(Outfile,"%s\n","#else");
                  strcpy(LastDef,GlobalVars[i].VarCondDef);
                }
              else
                {
                  while(LastLevel>=GlobalVars[i].VarCondLevel)
                    {
                      fprintf(Outfile,"%s\n","#endif");
                      LastLevel--;
                    }
                  strcpy(LastDef,GlobalVars[i].VarCondDef);
                  LastLevel=GlobalVars[i].VarCondLevel;
                  fprintf(Outfile,"%s\n",LastDef);
                }
            }
          *P=0;
          if(GlobalVars[i].VarPntr)
            {
              strcpy(P,stringx(GlobalVars[i].VarPntr,42));
            }
          A=GlobalVars[i].VarType;
          if(GlobalVars[i].VarSF)
            {
              strcpy(VarName, join(3,"(*",GlobalVars[i].VarName,")"));
            }
          else
            {
              strcpy(VarName,GlobalVars[i].VarName);
            }
          strcpy(VarDim,GlobalVars[i].VarDim);
          strcpy(Storage, join(2,VarStorage[GlobalVars[i].VarExtn],VarConst[GlobalVars[i].VarConstant]));
          PrintGlobal(A,i,Storage,P,VarName,VarDim);
        }
    }
  if(*LastDef)
    {
      while(LastLevel)
        {
          fprintf(Outfile,"%s\n","#endif");
          LastLevel--;
        }
    }
  fprintf(Outfile,"%s\n","");
  if(DllCnt)
    {
      int     i;
      char AR_DllName[2048];
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","// **********[ DLL Declarations ]**********");
      fprintf(Outfile,"%s\n","");
      for(i=0; i<=LoadLibsCnt-1; i+=1)
        {
          if(inchr(Loadlibs[i],"-"))
            {
              strcpy(AR_DllName,extract(Loadlibs[i],"-"));
            }
          else if(inchr(Loadlibs[i],"."))
            {
              strcpy(AR_DllName,extract(Loadlibs[i],"."));
            }
          fprintf(Outfile,"%s%s%s%s%s\n","void  *H_",ucase(AR_DllName)," = dlopen(",enc(Loadlibs[i]),", RTLD_LAZY);");
        }
      for(i=1; i<=DllCnt; i+=1)
        {
          fprintf(Outfile,"%s\n",DllDecl[i]);
        }
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","// ****************************************");
      fprintf(Outfile,"%s\n","");
    }
  if((FP5=fopen(datFile,"r"))==0)
   {
     fprintf(stderr,"Can't open file %s\n",datFile);
     exit(1);
   }
  if(lof(datFile)>0)
    {
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","// *************************************************");
      fprintf(Outfile,"%s\n","//              User Data Statements");
      fprintf(Outfile,"%s\n","// *************************************************");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","char * DATA [] =");
      fprintf(Outfile,"%s\n","{");
      while(!EoF(FP5))
        {
          Z[0]=0;
          AR_fgets_retval=fgets(Z,65535,FP5);
          if(Z[strlen(Z)-1]==10)Z[strlen(Z)-1]=0;
          fprintf(Outfile,"%s\n",Z);
        }
      fprintf(Outfile,"%s\n","};");
    }
  if(FP5)
   {
     fclose(FP5);
     FP5=NULL;
   }
  while(!EoF(FP1))
    {
      Z[0]=0;
      AR_fgets_retval=fgets(Z,65535,FP1);
      if(Z[strlen(Z)-1]==10)Z[strlen(Z)-1]=0;
      fprintf(Outfile,"%s\n",Z);
    }
  CloseAll();
  remove (FileOut);
  rename ("$t$e$m$p",FileOut);
}


int GetNumArgs (int Strt,int* NdxPos)
{
  int     CountR=0;
  int     CountS=0;
  int     i;
  int     j=0;
  int     k=1;
  for(i=Strt; i<=Ndx; i+=1)
    {
      if(str_cmp(Stk[i],"(")==0)
        {
          CountR++;
          k++;
        }
      else if(str_cmp(Stk[i],")")==0)
        {
          CountR--;
          k--;
          if(k==0)
            {
              break;
            }
        }
      else if(str_cmp(Stk[i],"[")==0)
        {
          CountS++;
        }
      else if(str_cmp(Stk[i],"]")==0)
        {
          CountS--;
        }
      else if(str_cmp(Stk[i],",")==0 && CountR==0&&CountS==0)
        {
          j++;
          if(NdxPos)
            {
              *NdxPos=i;
            }
        }
    }
  return j;
}


void GetVarCode (VARCODE* varcode)
{
  char CB[2048];
  char PT[2048];
  char PTH[2048];
  char VAR[2048];
  int     vn;
  char RF[2048];
  if(varcode->Method==mt_Opts3)
    {
      strcat(varcode->Proto,varcode->Token);
      if(str_cmp(varcode->Token,",")==0)
        {
          strcat(varcode->Header,varcode->Token);
        }
      return;
    }
  if(varcode->Method==mt_FuncSubx1)
    {
      strcpy(varcode->Proto, join(3,varcode->Proto,varcode->AsToken,"(*)("));
      strcpy(varcode->Header, join(5,varcode->Header,varcode->AsToken," (*",varcode->Token,")("));
      return;
    }
  if(varcode->Method==mt_FuncSubx2)
    {
      strcat(varcode->Proto,varcode->AsToken);
      strcpy(varcode->Header, join(4,varcode->Header,varcode->AsToken," ",varcode->Token));
      return;
    }
  if(IsCallBack)
    {
      strcpy(CB,"CALLBACK ");
    }
  else
    {
      *CB=0;
    }
  if(inchr(varcode->Token,"*")||inchr(varcode->AsToken,"*")||varcode->IsPtrFlag)
    {
      RemoveAll(varcode->Token,"*");
      RemoveAll(varcode->AsToken,"*");
      strcpy(PT, join(2,stringx(varcode->IsPtrFlag,42)," "));
      strcpy(PTH,PT);
    }
  else
    {
      strcpy(PTH," ");
      *PT=0;
    }
  if(inchr(varcode->Token,"&"))
    {
      strcpy(RF," &");
    }
  else
    {
      *RF=0;
    }
  vn=varcode->VarNo;
  strcpy(VAR,GetVarTypeName(vn));
  for(;;)
  {
    if(vn==vt_STRVAR)
      {
        for(;;)
        {
          if(varcode->Method==mt_ProcessSetCommand)
            {
              strcpy(varcode->StaticOut, join(2,"static char   ",Clean(varcode->Token)));
              break;
            }
          if(varcode->Method==mt_FuncSubDecC_Dec)
            {
              strcpy(varcode->Functype, join(2,"char * ",CB));
              break;
            }
          if(varcode->Method==mt_FuncSubDecC_Dec2)
            {
              if(!inchr(varcode->Token,"["))
                {
                  strcpy(varcode->Header, join(4,varcode->Header,"char *",Clean(varcode->Token),", "));
                  strcat(varcode->Proto,"char *, ");
                }
              else
                {
                  strcpy(varcode->Header, join(4,varcode->Header,"char ",RemoveStr(Clean(varcode->Token),"*"),", "));
                  strcat(varcode->Proto,"char [][65535], ");
                }
              break;
            }
          if(varcode->Method==mt_Opts)
            {
              strcpy(varcode->Functype,"char *");
              break;
            }
          if(varcode->Method==mt_Opts2)
            {
              strcpy(varcode->Header, join(3,varcode->Header,"char * ",Clean(varcode->Token)));
              strcat(varcode->Proto,"char* ");
              break;
            }
          if(varcode->Method==mt_OverLoad)
            {
              strcpy(varcode->Functype,"char *");
              break;
            }
          if(varcode->Method==mt_OverLoad2)
            {
              strcpy(varcode->Header, join(4,varcode->Header,"char *",Clean(varcode->Token),", "));
            }
          break;
        }
        break;
      }
    if(vn==vt_BOOL||vn==vt_BYTE||vn==vt_COLORREF||vn==vt_DOUBLE||vn==vt_DWORD||vn==vt_FARPROC||vn==vt_HDC||vn==vt_HANDLE||vn==vt_HINSTANCE||vn==vt_HWND||vn==vt_INTEGER||vn==vt_LONG||vn==vt_LPBYTE||vn==vt_LRESULT||vn==vt_SHORT||vn==vt_SINGLE||vn==vt_UINT||vn==vt_ULONG||vn==vt_USHORT||vn==vt_VARIANT||vn==vt_VOID||vn==vt_LDOUBLE)
      {
        for(;;)
        {
          if(varcode->Method==mt_ProcessSetCommand)
            {
              strcpy(varcode->StaticOut, join(4,"static ",VAR," ",Clean(varcode->Token)));
              break;
            }
          if(varcode->Method==mt_FuncSubDecC_Dec)
            {
              strcpy(varcode->Functype, join(3,VAR,PTH,CB));
              break;
            }
          if(varcode->Method==mt_FuncSubDecC_Dec2)
            {
              strcpy(varcode->Header, join(5,varcode->Header,VAR,PTH,Clean(varcode->Token),", "));
              strcpy(varcode->Proto, join(5,varcode->Proto,VAR,RF,PT,", "));
              break;
            }
          if(varcode->Method==mt_Opts)
            {
              strcpy(varcode->Functype, join(2,VAR,PTH));
              break;
            }
          if(varcode->Method==mt_Opts2)
            {
              strcpy(varcode->Header, join(4,varcode->Header,VAR,PTH,Clean(varcode->Token)));
              strcpy(varcode->Proto, join(4,varcode->Proto,VAR,RF,PT));
              break;
            }
          if(varcode->Method==mt_OverLoad)
            {
              strcpy(varcode->Functype, join(2,VAR," "));
              break;
            }
          if(varcode->Method==mt_OverLoad2)
            {
              strcpy(varcode->Header, join(5,varcode->Header,VAR,PTH,Clean(varcode->Token),", "));
            }
          break;
        }
        break;
      }
    if(vn==vt_FILEPTR||vn==vt_CHAR)
      {
        for(;;)
        {
          if(varcode->Method==mt_FuncSubDecC_Dec)
            {
              strcpy(varcode->Functype, join(3,VAR,PTH,CB));
              break;
            }
          if(varcode->Method==mt_FuncSubDecC_Dec2)
            {
              strcpy(varcode->Header, join(5,varcode->Header,VAR,PTH,Clean(varcode->Token),", "));
              strcpy(varcode->Proto, join(4,varcode->Proto,VAR,PT,", "));
              break;
            }
          if(varcode->Method==mt_Opts)
            {
              strcpy(varcode->Functype, join(2,VAR,PTH));
              break;
            }
          if(varcode->Method==mt_Opts2)
            {
              strcpy(varcode->Header, join(4,varcode->Header,VAR,PTH,Clean(varcode->Token)));
              strcpy(varcode->Proto, join(3,varcode->Proto,VAR,PT));
              break;
            }
          if(varcode->Method==mt_OverLoad)
            {
              strcpy(varcode->Functype, join(2,VAR," "));
              break;
            }
          if(varcode->Method==mt_OverLoad2)
            {
              strcpy(varcode->Header, join(5,varcode->Header,VAR,PTH,Clean(varcode->Token),", "));
            }
          break;
        }
        break;
      }
    if(vn==vt_UDT||vn==vt_STRUCT||vn==vt_UNION)
      {
        for(;;)
        {
          if(varcode->Method==mt_ProcessSetCommand)
            {
              if(vn==vt_UNION)
                {
                  strcpy(varcode->StaticOut, join(2,"static union  ",Clean(varcode->Token)));
                }
              else
                {
                  strcpy(varcode->StaticOut, join(3,"static struct _",Clean(varcode->Token)," "));
                }
              break;
            }
          if(varcode->Method==mt_FuncSubDecC_Dec)
            {
              strcpy(varcode->Functype, join(3,varcode->AsToken,PTH,CB));
              break;
            }
          if(varcode->Method==mt_FuncSubDecC_Dec2)
            {
              strcpy(varcode->Header, join(5,varcode->Header,varcode->AsToken,PTH,Clean(varcode->Token),", "));
              strcpy(varcode->Proto, join(5,varcode->Proto,varcode->AsToken,RF,PT,", "));
              break;
            }
          if(varcode->Method==mt_Opts)
            {
              strcpy(varcode->Functype, join(2,varcode->AsToken,PTH));
              break;
            }
          if(varcode->Method==mt_Opts2)
            {
              strcpy(varcode->Header, join(5,varcode->Header,Clean(varcode->AsToken),PTH," ",Clean(varcode->Token)));
              strcpy(varcode->Proto, join(4,varcode->Proto,Clean(varcode->AsToken),RF,PT));
              break;
            }
          if(varcode->Method==mt_OverLoad)
            {
              strcpy(varcode->Functype, join(2,VAR," "));
              break;
            }
          if(varcode->Method==mt_OverLoad2)
            {
              strcpy(varcode->Header, join(5,varcode->Header,varcode->AsToken,PTH,Clean(varcode->Token),", "));
            }
          break;
        }
        break;
      }
      // case else
      {
        for(;;)
        {
          if(varcode->Method==mt_FuncSubDecC_Dec)
            {
              strcpy(varcode->Functype, join(3,varcode->AsToken,PTH,CB));
              break;
            }
          if(varcode->Method==mt_FuncSubDecC_Dec2)
            {
              strcpy(varcode->Header, join(5,varcode->Header,varcode->AsToken,PTH,Clean(varcode->Token),", "));
              strcpy(varcode->Proto, join(5,varcode->Proto,varcode->AsToken,RF,PT,", "));
              break;
            }
          if(varcode->Method==mt_Opts)
            {
              strcpy(varcode->Functype, join(2,varcode->AsToken,PTH));
              break;
            }
          if(varcode->Method==mt_Opts2)
            {
              strcpy(varcode->Header, join(4,varcode->Header,Clean(varcode->AsToken)," ",Clean(varcode->Token)));
              strcat(varcode->Proto,Clean(varcode->AsToken));
            }
          break;
        }
      }
    break;
  }
}


void AddProtos (void)
{
  char SaveMain[2048];
  char *ZZ;
  ZZ=(char*)calloc(256+65535,1);
  int     A;
  *SaveMain=0;
  if((FP1=fopen(FileOut,"r"))==0)
   {
     fprintf(stderr,"Can't open file %s\n",FileOut);
     exit(1);
   }
  if((Outfile=fopen("$t$e$m$p","w"))==0)
   {
     fprintf(stderr,"Can't open file %s\n","$t$e$m$p");
     exit(1);
   }
  while(!EoF(FP1))
    {
      ZZ[0]=0;
      AR_fgets_retval=fgets(ZZ,65535,FP1);
      if(ZZ[strlen(ZZ)-1]==10)ZZ[strlen(ZZ)-1]=0;
      if(instr_b(ZZ,"int main"))
        {
          strcpy(SaveMain,ZZ);
          break;
        }
      fprintf(Outfile,"%s\n",ZZ);
    }
  fprintf(Outfile,"%s\n","");
  fprintf(Outfile,"%s\n","// *************************************************");
  fprintf(Outfile,"%s%s\n","//               ",BCX_STR_STD_MACROS);
  fprintf(Outfile,"%s\n","// *************************************************");
  fprintf(Outfile,"%s\n","");
  if(Use_BcxSplitPath)
    {
      fprintf(Outfile,"%s\n","#define FDRV   2");
      fprintf(Outfile,"%s\n","#define FPATH  4");
      fprintf(Outfile,"%s\n","#define FNAME  8");
      fprintf(Outfile,"%s\n","#define FEXT  16");
    }
  if(Use_Cbool)
    {
      fprintf(Outfile,"%s\n","#define CBOOL(A)(A!=0)?1:0");
    }
  if(Use_Isptr)
    {
      fprintf(Outfile,"%s\n","#define IsPtr(a)((DWORD)a)");
    }
  if(Use_Band)
    {
      fprintf(Outfile,"%s\n","#define BAND &");
    }
  if(Use_Bor)
    {
      fprintf(Outfile,"%s\n","#define BOR |");
    }
  if(Use_Bnot)
    {
      fprintf(Outfile,"%s\n","#define BNOT ~(int)");
    }
  if(Use_Ubound)
    {
      fprintf(Outfile,"%s\n","#define ubound(T)(sizeof((T))/sizeof((T[0]))-1)");
    }
  if(Use_Clear)
    {
      fprintf(Outfile,"%s\n","#define Clear(arg)memset(&arg,0,sizeof(arg))");
    }
  if(Use_Imod)
    {
      fprintf(Outfile,"%s\n","#define imod(a,b)((a)%(b))");
    }
  if(Use_Get)
    {
      fprintf(Outfile,"%s\n","#define GET(A,B,C) F_GetVal=fread(B,1,C,A)");
      AddGlobal("F_GetVal",vt_INTEGER,0,"",0,0,0,0);
    }
  if(Use_Put)
    {
      fprintf(Outfile,"%s\n","#define PUT(A,B,C) F_PutVal=fwrite(B,1,C,A)");
      AddGlobal("F_PutVal",vt_INTEGER,0,"",0,0,0,0);
    }
  if(Use_Strptr)
    {
      fprintf(Outfile,"%s\n","#define STRPTR(A)((char*)&(A))");
    }
  if(Use_Val)
    {
      fprintf(Outfile,"%s\n","#define VAL(a)(double)atof(a)");
    }
  if(Use_Vall)
    {
      fprintf(Outfile,"%s\n","#define VALL(a) (long double)strtold(a,(char**)NULL)");
    }
  if(Use_Fint)
    {
      fprintf(Outfile,"%s\n","#define FINT(a)floor(a)");
    }
  if(Use_Frac)
    {
      fprintf(Outfile,"%s\n","#define FRAC(a)(double)(a-FIX(a))");
      Use_Fix=TRUE;
    }
  if(Use_Fracl)
    {
      fprintf(Outfile,"%s\n","#define FRACL(a)(long double)(a-FIX(a))");
      Use_Fix=TRUE;
    }
  if(Use_Fix)
    {
      fprintf(Outfile,"%s\n","#define FIX(a)(int)((a))");
    }
  if(Use_Csng)
    {
      fprintf(Outfile,"%s\n","#define CSNG(a)((float)(a))");
    }
  if(Use_Cdbl)
    {
      fprintf(Outfile,"%s\n","#define CDBL(a)((double)(a))");
    }
  if(Use_Cldbl)
    {
      fprintf(Outfile,"%s\n","#define CLDBL(a)((long double)(a))");
    }
  if(Use_Threads)
    {
      fprintf(Outfile,"%s\n","#define BCX_THREAD(fn,arg)   ({ pthread_t tid; pthread_create(&tid, NULL, (void*(*)(void*))fn, arg); tid;})");
      fprintf(Outfile,"%s\n","#define BCX_THREADWAIT(a)    pthread_join(a, NULL)");
      fprintf(Outfile,"%s\n","#define BCX_INITLOCK(a)      pthread_mutex_init(a, NULL)");
      fprintf(Outfile,"%s\n","#define BCX_THREADLOCK(a)    pthread_mutex_lock (a)");
      fprintf(Outfile,"%s\n","#define BCX_THREADUNLOCK(a)  pthread_mutex_unlock (a)");
      fprintf(Outfile,"%s\n","#define BCX_THREADKILL(t)    pthread_cancel(t)");
      fprintf(Outfile,"%s\n","#define BCX_THREADEND        pthread_exit(0)");
    }
  fprintf(Outfile,"%s\n","");
  fprintf(Outfile,"%s\n","");
  fprintf(Outfile,"%s\n","// *************************************************");
  fprintf(Outfile,"%s%s\n","//               ",BCX_STR_STD_PROTOS);
  fprintf(Outfile,"%s\n","// *************************************************");
  fprintf(Outfile,"%s\n","");
  if(NoRT==FALSE)
    {
      if(Use_Clng)
        {
          fprintf(Outfile,"%s\n","long    CLNG(double);");
        }
      if(Use_Cint)
        {
          fprintf(Outfile,"%s\n","int     Cint(double);");
        }
      if(Use_StartupCode)
        {
          fprintf(Outfile,"%s\n","int     BCX_StartupCode_(void);");
        }
      if(Use_ExitCode)
        {
          fprintf(Outfile,"%s\n","int     BCX_ExitCode_(void);");
        }
      if(Use_Str_Cmp)
        {
          fprintf(Outfile,"%s\n","int     str_cmp(char*, char*);");
        }
      if(Use_Eof)
        {
          fprintf(Outfile,"%s\n","int     EoF (FILE*);");
        }
      if(Use_CopyFile)
        {
          fprintf(Outfile,"%s\n","void    CopyFile (char *,char *,int=FALSE);");
        }
      if(Use_QBColor)
        {
          fprintf(Outfile,"%s\n","int     qbcolor (int);");
        }
      if(Use_Cls)
        {
          fprintf(Outfile,"%s\n","void    cls(void);");
        }
      if(Use_Color)
        {
          fprintf(Outfile,"%s\n","void    color (int,int);");
        }
      if(Use_Locate)
        {
          fprintf(Outfile,"%s\n","void    locate (int,int,int=1,int=12);");
        }
      if(Use_Run)
        {
          fprintf(Outfile,"%s\n","int     Run (char*, int =1, int =0);");
        }
      if(Use_Randomize)
        {
          fprintf(Outfile,"%s\n","void    randomize (unsigned int);");
        }
      if(Use_Midstr)
        {
          fprintf(Outfile,"%s\n","void    midstr (char*, int, int, char *);");
        }
      if(Use_Swap)
        {
          fprintf(Outfile,"%s\n","void    swap (UCHAR*,UCHAR*,int);");
        }
      if(UseFlag)
        {
          fprintf(Outfile,"%s\n","char*   BCX_TmpStr(size_t);");
        }
      if(Use_sziif)
        {
          fprintf(Outfile,"%s\n","char*   sziif (bool,char*,char*);");
        }
      if(Use_Using)
        {
          fprintf(Outfile,"%s\n","char*   Using (char*,double);");
        }
      if(Use_TempFileName)
        {
          fprintf(Outfile,"%s\n","char*   TempFileName (char*,char*);");
        }
      if(Use_AppExePath)
        {
          fprintf(Outfile,"%s\n","char*   AppExePath (void);");
        }
      if(Use_AppExeName)
        {
          fprintf(Outfile,"%s\n","char*   AppExeName (void);");
        }
      if(Use_Lcase)
        {
          fprintf(Outfile,"%s\n","char*   lcase (char*);");
        }
      if(Use_Ucase)
        {
          fprintf(Outfile,"%s\n","char*   ucase (char*);");
        }
      if(Use_Mid)
        {
          fprintf(Outfile,"%s\n","char*   mid (char*, int, int=-1);");
        }
      if(Use_Ltrim)
        {
          fprintf(Outfile,"%s\n","char*   ltrim (char*,char=32);");
        }
      if(Use_Rtrim)
        {
          fprintf(Outfile,"%s\n","char*   rtrim (char*,char=32);");
        }
      if(Use_Trim)
        {
          fprintf(Outfile,"%s\n","char*   trim (char*);");
        }
      if(Use_Strim)
        {
          fprintf(Outfile,"%s\n","char*   strim   (char*);");
        }
      if(Use_Left)
        {
          fprintf(Outfile,"%s\n","char*   left (char*,int);");
        }
      if(Use_Right)
        {
          fprintf(Outfile,"%s\n","char*   right (char*,int);");
        }
      if(Use_Rpad)
        {
          fprintf(Outfile,"%s\n","char*   rpad (char*,int,int=32);");
        }
      if(Use_Lpad)
        {
          fprintf(Outfile,"%s\n","char*   lpad (char*,int,int=32);");
        }
      if(Use_String)
        {
          fprintf(Outfile,"%s\n","char*   stringx (int,int);");
        }
      if(Use_Repeat)
        {
          fprintf(Outfile,"%s\n","char*   repeat (int,char*);");
        }
      if(Use_Extract)
        {
          fprintf(Outfile,"%s\n","char*   extract (char*,char*);");
        }
      if(Use_Remain)
        {
          fprintf(Outfile,"%s\n","char*   remain (char*,char*);");
        }
      if(Use_Reverse)
        {
          fprintf(Outfile,"%s\n","char*   reverse (char*);");
        }
      if(Use_Command)
        {
          fprintf(Outfile,"%s\n","char*   command (int=-1);");
        }
      if(Use_Mcase)
        {
          fprintf(Outfile,"%s\n","char*   mcase (char*);");
        }
      if(Use_Replace)
        {
          fprintf(Outfile,"%s\n","char*   replace (char*,char*,char*);");
        }
      if(Use_iReplace)
        {
          fprintf(Outfile,"%s\n","char*   iReplace (char*,char*,char*);");
        }
      if(Use_Shell)
        {
          fprintf(Outfile,"%s\n","void    Shell (char *);");
        }
      if(Use_Space)
        {
          fprintf(Outfile,"%s\n","char*   space (int a);");
        }
      if(Use_Str)
        {
          fprintf(Outfile,"%s\n","char*   str (double);");
        }
      if(Use_Strl)
        {
          fprintf(Outfile,"%s\n","char*   strl (long double);");
        }
      if(Use_Findfirst)
        {
          fprintf(Outfile,"%s\n","char*   findfirst (char*, FILE_FIND_DATA*);");
        }
      if(Use_Findnext)
        {
          fprintf(Outfile,"%s\n","char*   findnext (FILE_FIND_DATA*);");
        }
      if(Use_Curdir)
        {
          fprintf(Outfile,"%s\n","char*   curdir (void);");
        }
      if(Use_Sysdir)
        {
          fprintf(Outfile,"%s\n","char*   sysdir (void);");
        }
      if(Use_Tempdir)
        {
          fprintf(Outfile,"%s\n","char*   tempdir (void);");
        }
      if(Use_Environ)
        {
          fprintf(Outfile,"%s\n","char*   Environ (char*);");
        }
      if(Use_Boolstr)
        {
          fprintf(Outfile,"%s\n","char*   BoolStr (int);");
        }
      if(Use_Hex)
        {
          fprintf(Outfile,"%s\n","char*   hex (int);");
        }
      if(Use_Bin)
        {
          fprintf(Outfile,"%s\n","char*   Bin (int);");
        }
      if(Use_Oct)
        {
          fprintf(Outfile,"%s\n","char*   oct (int);");
        }
      if(Use_Now)
        {
          fprintf(Outfile,"%s\n","char*   now (void);");
        }
      if(Use_SearchPath)
        {
          fprintf(Outfile,"%s\n","char*   SEARCHPATH (char *);");
        }
      if(Use_StrUpLow)
        {
          fprintf(Outfile,"%s\n","char*   _strupr_(char *);");
          fprintf(Outfile,"%s\n","char*   _strlwr_(char *);");
        }
      if(Use_BcxSplitPath)
        {
          fprintf(Outfile,"%s\n","char*   BcxSplitPath (char *, int);");
          fprintf(Outfile,"%s\n","void    _splitpath_(const char* path, char* drv, char* dir, char* name, char* ext);");
        }
      if(Use_Strtoken)
        {
          fprintf(Outfile,"%s\n","char*   StrToken (char*,char*,int);");
        }
      if(Use_FileLocked)
        {
          fprintf(Outfile,"%s\n","int    FileLocked (char*);");
        }
      if(Use_FillArray)
        {
          fprintf(Outfile,"%s\n","int     fillarray (char *, int, int, void *);");
        }
      if(Use_Remove)
        {
          fprintf(Outfile,"%s\n","char*   RemoveStr (char*,char*);");
        }
      if(Use_IRemove)
        {
          fprintf(Outfile,"%s\n","char*   IRemoveStr (char*,char*);");
        }
      if(Use_Time)
        {
          fprintf(Outfile,"%s\n","char*   timef (int i=0);");
        }
      if(Use_Join)
        {
          fprintf(Outfile,"%s\n","char*   join (int, ... );");
        }
      if(Use_Enclose)
        {
          fprintf(Outfile,"%s\n","char*   enc (char*, int=0, int=0);");
        }
      if(Use_Chr)
        {
          fprintf(Outfile,"%s","char*   chr");
          fprintf(Outfile,"%s\n","(int,int=0,int=0,int=0,int=0,int=0,int=0,int=0,int=0,int=0);");
        }
      if(Use_VChr)
        {
          fprintf(Outfile,"%s\n","char*   vchr (int,...);");
        }
      if(Use_Freefile)
        {
          fprintf(Outfile,"%s\n","FILE*   FreeFile (void);");
        }
      if(Use_PeekStr)
        {
          fprintf(Outfile,"%s\n","char*   peekstr (LPVOID,int);");
        }
      if(Use_Asc)
        {
          fprintf(Outfile,"%s\n","int     asc (char*,int=0);");
        }
      if(Use_Instrrev)
        {
          fprintf(Outfile,"%s\n","int     InstrRev (char*,char*,int=0,int=0);");
        }
      if(Use_Instr)
        {
          fprintf(Outfile,"%s\n","int     instr_b(char*,char*,int=0,int=0);");
        }
      if(UseLCaseTbl)
        {
          fprintf(Outfile,"%s\n","char    *MakeLCaseTbl(void);");
        }
      if(Use_Stristr)
        {
          fprintf(Outfile,"%s\n","char    *_stristr_(char*,char*);");
        }
      if(Use_StrStr)
        {
          fprintf(Outfile,"%s\n","char    *_strstr_(char*,char*);");
        }
      if(Use_Verify)
        {
          fprintf(Outfile,"%s\n","int     Verify (char *, char *);");
          fprintf(Outfile,"%s\n","int     VerifyInstr(char*,char*,int=0);");
        }
      if(Use_Retain)
        {
          fprintf(Outfile,"%s\n","char*   Retain (char*,char *);");
        }
      if(Use_LoadFile)
        {
          fprintf(Outfile,"%s\n","char*   LoadFile (char*);");
        }
      if(Use_Inchr)
        {
          fprintf(Outfile,"%s\n","int     inchr (char*,char*);");
        }
      if(Use_Idxqsort)
        {
          fprintf(Outfile,"%s\n","int     IdxCompare (const void *,const void *);");
        }
      if(Use_IdxqsortSt)
        {
          fprintf(Outfile,"%s\n","int     IdxCompareSt (const void *,const void *);");
        }
      if(Use_PtrqsortSt)
        {
          fprintf(Outfile,"%s\n","int     PtrCompareSt (const void *,const void *);");
        }
      if(Use_Strqsorta)
        {
          fprintf(Outfile,"%s\n","int     StrCompareA (const void *,const void *);");
        }
      if(Use_Strqsortd)
        {
          fprintf(Outfile,"%s\n","int     StrCompareD (const void *,const void *);");
        }
      if(Use_DynStrqsorta)
        {
          fprintf(Outfile,"%s\n","int     DynStrCompareA (const void *,const void *);");
        }
      if(Use_DynStrqsortd)
        {
          fprintf(Outfile,"%s\n","int     DynStrCompareD (const void *,const void *);");
        }
      if(Use_Numqsortaint)
        {
          fprintf(Outfile,"%s\n","int     NumCompareAint (const void *,const void *);");
        }
      if(Use_Numqsortdint)
        {
          fprintf(Outfile,"%s\n","int     NumCompareDint (const void *,const void *);");
        }
      if(Use_Numqsortafloat)
        {
          fprintf(Outfile,"%s\n","int     NumCompareAfloat (const void *,const void *);");
        }
      if(Use_Numqsortdfloat)
        {
          fprintf(Outfile,"%s\n","int     NumCompareDfloat (const void *,const void *);");
        }
      if(Use_Numqsortadouble)
        {
          fprintf(Outfile,"%s\n","int     NumCompareAdouble (const void *,const void *);");
        }
      if(Use_Numqsortddouble)
        {
          fprintf(Outfile,"%s\n","int     NumCompareDdouble (const void *,const void *);");
        }
      if(Use_Like)
        {
          fprintf(Outfile,"%s\n","int     like (char*,char*);");
        }
      if(Use_Tally)
        {
          fprintf(Outfile,"%s\n","int     tally (char*,char*,int=0);");
        }
      if(Use_Inkey)
        {
          fprintf(Outfile,"%s\n","char*   inkey (void);");
        }
      if(Use_InkeyD)
        {
          fprintf(Outfile,"%s\n","int     inkeyd (void);");
        }
      if(Use_Instat)
        {
          fprintf(Outfile,"%s\n","int		kbhit(void);");
        }
      if(Use_GetCh)
        {
          fprintf(Outfile,"%s\n","int     _getch_(int);");
        }
      if(Use_Bin2dec)
        {
          fprintf(Outfile,"%s\n","int     Bin2Dec (char*);");
        }
      if(Use_Hex2Dec)
        {
          fprintf(Outfile,"%s\n","int     Hex2Dec (char*);");
        }
      if(Use_Download)
        {
          fprintf(Outfile,"%s\n","int     Download (char*,char*);");
        }
      if(Use_Embed)
        {
          fprintf(Outfile,"%s\n","char*   GetResource (int* );");
        }
      if(Use_Exist)
        {
          if(Use_Osx)
            {
              fprintf(Outfile,"%s\n","bool    Exist   (char*);");
            }
          else
            {
              fprintf(Outfile,"%s\n","BOOL    Exist   (char*);");
            }
        }
      if(Use_Ins)
        {
          fprintf(Outfile,"%s\n","char*   ins (char *S, int i, char *a);");
        }
      if(Use_Del)
        {
          fprintf(Outfile,"%s\n","char*   del (char*,int,int);");
        }
      if(Use_Pause)
        {
          fprintf(Outfile,"%s\n","void    Pause (void);");
        }
      if(Use_Keypress)
        {
          fprintf(Outfile,"%s\n","int     keypress (void);");
        }
      if(Use_Lof)
        {
          fprintf(Outfile,"%s\n","DWORD   lof (char*);");
        }
      if(Use_Sgn)
        {
          fprintf(Outfile,"%s\n","double  sgn (double);");
        }
      if(Use_Round)
        {
          fprintf(Outfile,"%s\n","double  Round (double,int);");
        }
      if(Use_Rnd)
        {
          fprintf(Outfile,"%s\n","float   rnd (void);");
        }
      if(Use_Exp)
        {
          fprintf(Outfile,"%s\n","double  Exp (double);");
        }
      if(Use_Min)
        {
          fprintf(Outfile,"%s\n","double  _MIN_ (double,double);");
        }
      if(Use_Max)
        {
          fprintf(Outfile,"%s\n","double  _MAX_ (double,double);");
        }
      if(Use_Timer)
        {
          fprintf(Outfile,"%s\n","float   timer (void);");
        }
      if(Use_Iif)
        {
          fprintf(Outfile,"%s\n","double  iif (bool,double,double);");
        }
      if(Use_Loc)
        {
          fprintf(Outfile,"%s\n","int     loc (FILE *fp, int fplen);");
        }
      if(Use_Rec)
        {
          fprintf(Outfile,"%s\n","int     rec (FILE *fp, int fplen);");
        }
      if(Use_RecCount)
        {
          fprintf(Outfile,"%s\n","int     reccount (FILE *fp, int fplen);");
        }
      if(Use_Scan)
        {
          fprintf(Outfile,"%s\n","int     scan (char *input, char *format, ... );");
        }
      if(Use_Split)
        {
          fprintf(Outfile,"%s\n","int     Split (char [][65535], char*, char*, int=0);");
        }
      if(Use_DSplit)
        {
          fprintf(Outfile,"%s\n","int     DSplit (PCHAR *, char*, char*, int=0);");
        }
      if(Use_SysStr)
        {
          fprintf(Outfile,"%s\n","BSTR    SysStr (char * szIn, int=0, int=0);");
        }
      if(Use_WideToAnsi)
        {
          fprintf(Outfile,"%s\n","char*   WideToAnsi (wchar_t *, UINT=0, DWORD=0);");
        }
      if(Use_AnsiToWide)
        {
          fprintf(Outfile,"%s\n","wchar_t* AnsiToWide (char*,UINT=0,DWORD=0);");
        }
      if(Use_Cvi)
        {
          fprintf(Outfile,"%s\n","short   CVI (char*);");
        }
      if(Use_Mki)
        {
          fprintf(Outfile,"%s\n","char*   MKI (short);");
        }
      if(Use_Cvl)
        {
          fprintf(Outfile,"%s\n","long    CVL (char*);");
        }
      if(Use_Mkl)
        {
          fprintf(Outfile,"%s\n","char*   MKL (int);");
        }
      if(Use_Cvs)
        {
          fprintf(Outfile,"%s\n","float   CVS (char*);");
        }
      if(Use_Mks)
        {
          fprintf(Outfile,"%s\n","char*   MKS (float);");
        }
      if(Use_Cvd)
        {
          fprintf(Outfile,"%s\n","double  CVD (char*);");
        }
      if(Use_Cvld)
        {
          fprintf(Outfile,"%s\n","long double  CVLD (char*);");
        }
      if(Use_Mkd)
        {
          fprintf(Outfile,"%s\n","char*   MKD (double);");
        }
      if(Use_Mkld)
        {
          fprintf(Outfile,"%s\n","char*   MKLD (long double);");
        }
      if(Use_OSVersion)
        {
          fprintf(Outfile,"%s\n","int     OSVersion (void);");
        }
      if(Use_Dynacall)
        {
          fprintf(Outfile,"%s\n","HINSTANCE BCX_LoadDll(char *);");
          fprintf(Outfile,"%s\n","void    BCX_UnloadDll(void);");
          fprintf(Outfile,"%s\n","typedef int (CALLBACK *DYNACALL1)(void);");
          fprintf(Outfile,"%s\n","int     BCX_DynaCall(char *, char *, int, ...);");
        }
      if(Use_DynamicA)
        {
          fprintf(Outfile,"%s\n","void*   CreateArr (void*,int,int,int,...);");
          fprintf(Outfile,"%s\n","void*   CreateArr_internal(void*, int, int, int, va_list);");
          fprintf(Outfile,"%s\n","void    DestroyArr (void**,int,int);");
        }
      if(Use_ContainedIn)
        {
          fprintf(Outfile,"%s\n","int     containedin(char * ,char **,int=0);");
        }
      if(Use_FindInType)
        {
          fprintf(Outfile,"%s\n","int     FindInType(char *,char *,int,int,int,int=0,int* =0);");
        }
      if(Use_SingleFile==FALSE)
        {
          if((fpHFile=fopen(HFile,"w"))==0)
           {
             fprintf(stderr,"Can't open file %s\n",HFile);
             exit(1);
           }
        }
      /*****2010-11-24ChangeTOemitwxAppCLASSDefinitionFORWXCONSOLEApps-AIR*****/;
      if(Use_Wx)
        {
          fprintf(Outfile,"%s\n","");
          fprintf(Outfile,"%s%s%s\n","class ",BcxSplitPath(FileIn,FNAME),": public wxApp {");
          fprintf(Outfile,"%s\n","  public:");
          fprintf(Outfile,"%s\n","	virtual bool OnInit();");
          fprintf(Outfile,"%s\n","};");
          fprintf(Outfile,"%s\n","");
          fprintf(Outfile,"%s%s%s\n","IMPLEMENT_APP(",BcxSplitPath(FileIn,FNAME),")");
          fprintf(Outfile,"%s\n","");
        }
      if(Use_Socket)
        {
          fprintf(Outfile,"%s\n","");
          fprintf(Outfile,"%s\n","sockaddr_in sock_addr (char* ,int=80);");
          fprintf(Outfile,"%s\n","int     connect_socket (sockaddr_in);");
          fprintf(Outfile,"%s\n","int     BcxSocket (char* ,int=80);");
          fprintf(Outfile,"%s\n","int     BcxSocketSend (int, char *);");
          fprintf(Outfile,"%s\n","int     BcxSocketRead (int, char *);");
          fprintf(Outfile,"%s\n","void    BcxSocketClose(int);");
          fprintf(Outfile,"%s\n","");
        }
      if(Use_RegEx)
        {
          fprintf(Outfile,"%s\n","bool    regmatch (char *, char *, REGEX* );");
        }
    }
  if(ProtoCnt)
    {
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","// *************************************************");
      fprintf(Outfile,"%s%s\n","//               ",BCX_STR_USR_PROTOS);
      fprintf(Outfile,"%s\n","// *************************************************");
      fprintf(Outfile,"%s\n","");
      char LastDef[2048];
      int     LastLevel;
      *LastDef=0;
      LastLevel=1;
      for(A=1; A<=ProtoCnt; A+=1)
        {
          if(LastDef[0]==0)
            {
              strcpy(LastDef,ProtoType[A].Condition);
              LastLevel=ProtoType[A].CondLevel;
              if(Use_SingleFile==FALSE)
                {
                  if(LastDef[0]>0)
                    {
                      fprintf(fpHFile,"%s\n",LastDef);
                    }
                }
              if(LastDef[0]>0)
                {
                  fprintf(Outfile,"%s\n",LastDef);
                }
            }
          if(str_cmp(LastDef,ProtoType[A].Condition)!=0)
            {
              if(str_cmp(ProtoType[A].Condition,"#else")==0)
                {
                  while(LastLevel>ProtoType[A].CondLevel)
                    {
                      if(Use_SingleFile==FALSE)
                        {
                          fprintf(fpHFile,"%s\n","#endif");
                        }
                      fprintf(Outfile,"%s\n","#endif");
                      LastLevel--;
                    }
                  if(Use_SingleFile==FALSE)
                    {
                      fprintf(fpHFile,"%s\n","#else");
                    }
                  fprintf(Outfile,"%s\n","#else");
                  strcpy(LastDef,ProtoType[A].Condition);
                  LastLevel=ProtoType[A].CondLevel;
                }
              else
                {
                  while(LastLevel>ProtoType[A].CondLevel)
                    {
                      if(Use_SingleFile==FALSE)
                        {
                          fprintf(fpHFile,"%s\n","#endif");
                        }
                      fprintf(Outfile,"%s\n","#endif");
                      LastLevel--;
                    }
                  strcpy(LastDef,ProtoType[A].Condition);
                  LastLevel=ProtoType[A].CondLevel;
                  if(Use_SingleFile==FALSE)
                    {
                      if(LastDef[0]>0)
                        {
                          fprintf(fpHFile,"%s\n",LastDef);
                        }
                    }
                  if(LastDef[0]>0)
                    {
                      fprintf(Outfile,"%s\n",LastDef);
                    }
                }
            }
          if(UseStdCall&&UseCpp)
            {
              if(str_cmp(left(ProtoType[A].Prototype,9),"C_EXPORT ")==0)
                {
                  EmitExportDef(ProtoType[A].Prototype);
                }
            }
          strcpy(T,extract(ProtoType[A].Prototype,SPC));
          strcpy(T, join(2,rpad(T,7),SPC));
          strcpy(ProtoType[A].Prototype, join(2,T,remain(ProtoType[A].Prototype,SPC)));
          if(Use_SingleFile==FALSE)
            {
              fprintf(fpHFile,"%s\n",ProtoType[A].Prototype);
            }
          if(UseCpp==FALSE&&!instr_b(ProtoType[A].Prototype,"::"))
            {
              fprintf(Outfile,"%s\n",ProtoType[A].Prototype);
            }
        }
      if(*LastDef)
        {
          while(LastLevel>0)
            {
              if(Use_SingleFile==FALSE)
                {
                  fprintf(fpHFile,"%s\n","#endif");
                }
              fprintf(Outfile,"%s\n","#endif");
              LastLevel--;
            }
        }
    }
  fprintf(Outfile,"%s\n","");
  char P[2048];
  int     i;
  char VarName[2048];
  char VarDim[2048];
  char Storage[2048];
  char VAR[2048];
  if(GlobalVarCnt>0)
    {
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","// *************************************************");
      fprintf(Outfile,"%s\n","//            User Global Initialized Arrays");
      fprintf(Outfile,"%s\n","// *************************************************");
      fprintf(Outfile,"%s\n","");
      for(i=1; i<=GlobalVarCnt; i+=1)
        {
          if(GlobalVars[i].VarEmitFlag)
            {
              continue;
            }
          if(str_cmp("",GlobalVars[i].VarDim)!=0 && GlobalVars[i].VarCondLevel==0)
            {
              if(instr_b(GlobalVars[i].VarDim,"{"))
                {
                  *P=0;
                  if(GlobalVars[i].VarPntr)
                    {
                      strcpy(P,stringx(GlobalVars[i].VarPntr,42));
                    }
                  A=GlobalVars[i].VarType;
                  if(GlobalVars[i].VarSF)
                    {
                      strcpy(VarName, join(4,"(*",GlobalVars[i].VarName,extract(GlobalVars[i].VarDim,"("),")"));
                      strcpy(VarDim,mid(GlobalVars[i].VarDim,instr_b(GlobalVars[i].VarDim,"(")));
                    }
                  else
                    {
                      strcpy(VarName,GlobalVars[i].VarName);
                      strcpy(VarDim,GlobalVars[i].VarDim);
                    }
                  strcpy(Storage, join(2,VarStorage[GlobalVars[i].VarExtn],VarConst[GlobalVars[i].VarConstant]));
                  for(;;)
                  {
                    if(A==vt_STRVAR)
                      {
                        fprintf(Outfile,"%s%s%s%s%s\n",Storage,"char    ",VarName,VarDim,";");
                        break;
                      }
                    if(A==vt_FILEPTR)
                      {
                        strcpy(GlobalVars[i].VarName,RemoveStr(GlobalVars[i].VarName,"@"));
                        fprintf(Outfile,"%s%s%s%s%s\n",Storage,"FILE   *",VarName,VarDim,";");
                        break;
                      }
                    if(A==vt_BOOL)
                      {
                        fprintf(Outfile,"%s%s%s%s%s\n",Storage,"bool    ",VarName,VarDim,";");
                        break;
                      }
                    if(A==vt_UDT||A==vt_STRUCT||A==vt_UNION)
                      {
                        strcpy(VAR,TypeDefs[GlobalVars[i].VarDef].VarName);
                        strcpy(VAR,rpad(VAR,7));
                        fprintf(Outfile,"%s%s%s%s%s%s%s\n",Storage,VAR," ",P,VarName,VarDim,";");
                        break;
                      }
                    if(A>=vt_VarMin&&A<=vt_VarMax)
                      {
                        strcpy(VAR,GetVarTypeName(GlobalVars[i].VarType));
                        strcpy(VAR,rpad(VAR,7));
                        fprintf(Outfile,"%s%s%s%s%s%s%s\n",Storage,VAR," ",P,VarName,VarDim,";");
                      }
                    break;
                  }
                }
            }
        }
      fprintf(Outfile,"%s\n","");
    }
  if(Use_Overloaded)
    {
      fprintf(Outfile,"%s\n","// *************************************************");
      fprintf(Outfile,"%s\n","//        User's Overloaded Subs/Functions          ");
      fprintf(Outfile,"%s\n","// *************************************************");
      if((FP8=fopen(ovrFile,"r"))==0)
       {
         fprintf(stderr,"Can't open file %s\n",ovrFile);
         exit(1);
       }
      while(!EoF(FP8))
        {
          ZZ[0]=0;
          AR_fgets_retval=fgets(ZZ,65535,FP8);
          if(ZZ[strlen(ZZ)-1]==10)ZZ[strlen(ZZ)-1]=0;
          if(instr_b(ZZ,"overloaded"))
            {
              fprintf(Outfile,"%s\n","\n");
            }
          fprintf(Outfile,"%s\n",ZZ);
        }
      if(FP8)
       {
         fclose(FP8);
         FP8=NULL;
       }
      fprintf(Outfile,"%s\n","\n\n");
    }
  if((FP5=fopen(setFile,"r"))==0)
   {
     fprintf(stderr,"Can't open file %s\n",setFile);
     exit(1);
   }
  if(lof(setFile)>0)
    {
      fprintf(Outfile,"%s\n","// *************************************************");
      fprintf(Outfile,"%s\n","//              User GLOBAL SET Statements");
      fprintf(Outfile,"%s\n","// *************************************************");
      fprintf(Outfile,"%s\n","");
      while(!EoF(FP5))
        {
          Z[0]=0;
          AR_fgets_retval=fgets(Z,65535,FP5);
          if(Z[strlen(Z)-1]==10)Z[strlen(Z)-1]=0;
          fprintf(Outfile,"%s\n",Z);
        }
      fprintf(Outfile,"%s\n","");
    }
  if(FP5)
   {
     fclose(FP5);
     FP5=NULL;
   }
  if(Use_SingleFile==FALSE)
    {
      if(fpHFile)
       {
         fclose(fpHFile);
         fpHFile=NULL;
       }
    }
  if(NoMain==0)
    {
      fprintf(Outfile,"%s\n","// *************************************************");
      fprintf(Outfile,"%s%s\n","//                  ",BCX_STR_MAIN_PROG);
      fprintf(Outfile,"%s\n","// *************************************************");
      fprintf(Outfile,"%s\n","");
    }
  if(NoMain==FALSE)
    {
      fprintf(Outfile,"%s\n",SaveMain);
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  G_argc = argc;");
      fprintf(Outfile,"%s\n","  G_argv = argv;");
      BumpUp();
    }
  while(!EoF(FP1))
    {
      ZZ[0]=0;
      AR_fgets_retval=fgets(ZZ,65535,FP1);
      if(ZZ[strlen(ZZ)-1]==10)ZZ[strlen(ZZ)-1]=0;
      fprintf(Outfile,"%s%s\n",Scoot,ZZ);
    }
  if(Use_SingleFile==TRUE)
    {
      RunTimeFunctions();
    }
  fflush(Outfile);
  CloseAll();
  remove (FileOut);
  rename ("$t$e$m$p",FileOut);
  if(ZZ)free(ZZ);
}


void RunTimeFunctions (void)
{
  static char X1[2048];
  memset(&X1,0,sizeof(X1));
  static char O1[2048];
  memset(&O1,0,sizeof(O1));
  static char D1[2048];
  memset(&D1,0,sizeof(D1));
  static char D2[2048];
  memset(&D2,0,sizeof(D2));
  static char T0[2048];
  memset(&T0,0,sizeof(T0));
  static char T1[2048];
  memset(&T1,0,sizeof(T1));
  static char T2[2048];
  memset(&T2,0,sizeof(T2));
  static char T3[2048];
  memset(&T3,0,sizeof(T3));
  static char T4[2048];
  memset(&T4,0,sizeof(T4));
  static char T5[2048];
  memset(&T5,0,sizeof(T5));
  static char T6[2048];
  memset(&T6,0,sizeof(T6));
  static char T7[2048];
  memset(&T7,0,sizeof(T7));
  static char T8[2048];
  memset(&T8,0,sizeof(T8));
  static char T9[2048];
  memset(&T9,0,sizeof(T9));
  static char T10[2048];
  memset(&T10,0,sizeof(T10));
  static char T11[2048];
  memset(&T11,0,sizeof(T11));
  static char T12[2048];
  memset(&T12,0,sizeof(T12));
  static char T13[2048];
  memset(&T13,0,sizeof(T13));
  static char TDIR[2048];
  memset(&TDIR,0,sizeof(TDIR));
  strcpy(D1,vchr(8,34,37,32,46,49,53,71,34));
  strcpy(D2,vchr(9,34,37,32,46,49,57,76,71,34));
  strcpy(O1,vchr(4,34,37,111,34));
  strcpy(T0,vchr(10,34,37,72,58,37,77,58,37,83,34));
  strcpy(T1,vchr(4,34,37,72,34));
  strcpy(T2,vchr(4,34,37,77,34));
  strcpy(T3,vchr(4,34,37,83,34));
  strcpy(T4,vchr(4,34,37,112,34));
  strcpy(T5,vchr(4,34,37,89,34));
  strcpy(T6,vchr(4,34,37,109,34));
  strcpy(T7,vchr(4,34,37,100,34));
  strcpy(T8,vchr(4,34,37,65,34));
  strcpy(T9,vchr(4,34,37,119,34));
  strcpy(T10,vchr(4,34,37,106,34));
  strcpy(T11,vchr(4,34,37,86,34));
  strcpy(T12,vchr(10,34,37,109,47,37,100,47,37,121,34));
  strcpy(T13,vchr(15,34,37,65,44,32,37,66,32,37,100,44,32,37,89,34));
  strcpy(X1,vchr(4,34,37,88,34));
  strcpy(TDIR,enc("/tmp/mbc.XXXXXXXX"));
  fprintf(Outfile,"%s\n","");
  fprintf(Outfile,"%s\n","// *************************************************");
  fprintf(Outfile,"%s%s\n","//                 ",BCX_STR_RUNTIME);
  fprintf(Outfile,"%s\n","// *************************************************");
  fprintf(Outfile,"%s\n","");
  if(NoRT==TRUE)
    {
      return;
    }
  if(UseFlag)
    {
      if(Use_Turbo)
        {
          fprintf(Outfile,"%s\n","char *BCX_TmpStr (size_t Bites)");
          fprintf(Outfile,"%s\n","{");
          fprintf(Outfile,"%s\n","  static int   StrCnt;");
          fprintf(Outfile,"%s%d%s\n","  static char *StrFunc[",(int)TurboSize,"];");
          fprintf(Outfile,"%s%d%s\n","  StrCnt=((StrCnt+1) &",(int)TurboSize-1,");");
          fprintf(Outfile,"%s\n","    #if defined BCX_MAX_VAR_SIZE");
          fprintf(Outfile,"%s\n","  if(Bites*sizeof(char)>BCX_MAX_VAR_SIZE)");
          fprintf(Outfile,"%s\n","  {");
          fprintf(Outfile,"%s%s%s\n","  printf(",enc("Buffer Overflow caught in BCX_TmpStr - requested space of %d EXCEEDS %d\\n"),",(int)(Bites*sizeof(char)),BCX_MAX_VAR_SIZE);");
          fprintf(Outfile,"%s\n","  abort();");
          fprintf(Outfile,"%s\n","  }");
          fprintf(Outfile,"%s\n","  #endif");
          fprintf(Outfile,"%s\n","  StrFunc[StrCnt]=(char*)realloc(StrFunc[StrCnt],Bites + 128);");
          fprintf(Outfile,"%s\n","  return (char*)memset(StrFunc[StrCnt],0,Bites+128);");
          fprintf(Outfile,"%s\n","}\n\n");
        }
      else
        {
          fprintf(Outfile,"%s\n","char *BCX_TmpStr (size_t Bites)");
          fprintf(Outfile,"%s\n","{");
          fprintf(Outfile,"%s\n","  static int   StrCnt;");
          fprintf(Outfile,"%s\n","  static char *StrFunc[65535];");
          fprintf(Outfile,"%s\n","  StrCnt=(StrCnt + 1) & 65535;");
          fprintf(Outfile,"%s\n","  if(StrFunc[StrCnt]) free (StrFunc[StrCnt]);");
          fprintf(Outfile,"%s\n","    #if defined BCX_MAX_VAR_SIZE");
          fprintf(Outfile,"%s\n","  if(Bites*sizeof(char)>BCX_MAX_VAR_SIZE)");
          fprintf(Outfile,"%s\n","  {");
          fprintf(Outfile,"%s%s%s\n","  printf(",enc("Buffer Overflow caught in BCX_TmpStr - requested space of %d EXCEEDS %d\\n"),",(int)(Bites*sizeof(char)),BCX_MAX_VAR_SIZE);");
          fprintf(Outfile,"%s\n","  abort();");
          fprintf(Outfile,"%s\n","  }");
          fprintf(Outfile,"%s\n","  #endif");
          fprintf(Outfile,"%s\n","  return StrFunc[StrCnt]=(char*)calloc(Bites+128,sizeof(char));");
          fprintf(Outfile,"%s\n","}\n\n");
        }
    }
  if(Use_CopyFile)
    {
      fprintf(Outfile,"%s\n","void CopyFile (char *InFile,char *TmpFile,int OverWrite)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  #define BLOCKCOPYSIZE (10 * 1000*1024)");
      fprintf(Outfile,"%s\n","  char*  tmp=0;");
      fprintf(Outfile,"%s\n","  UINT   blocks=1;");
      fprintf(Outfile,"%s\n","  UINT   overage=0;");
      fprintf(Outfile,"%s\n","  UINT   i;");
      fprintf(Outfile,"%s\n","  FILE   *FP1,*FP2;");
      fprintf(Outfile,"%s\n","  if(!OverWrite)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      if(Exist(TmpFile)) return;");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  if(Exist(InFile))");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      UINT length = lof(InFile);");
      fprintf(Outfile,"%s\n","      if(length > BLOCKCOPYSIZE)");
      fprintf(Outfile,"%s\n","        {");
      fprintf(Outfile,"%s\n","          blocks = length/BLOCKCOPYSIZE;");
      fprintf(Outfile,"%s\n","          overage= length % BLOCKCOPYSIZE;");
      fprintf(Outfile,"%s\n","          length = BLOCKCOPYSIZE;");
      fprintf(Outfile,"%s\n","        }");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","      tmp=(char*)calloc(16+length,1);");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s%s%s\n","      if((FP1=fopen(InFile,",enc("rb"),"))==0)");
      fprintf(Outfile,"%s\n","       {");
      fprintf(Outfile,"%s%s%s\n","         fprintf(stderr,",enc("Can't open file %s\\n"),",InFile);");
      fprintf(Outfile,"%s\n","         exit(1);");
      fprintf(Outfile,"%s\n","       }");
      fprintf(Outfile,"%s%s%s\n","      if((FP2=fopen(TmpFile,",enc("wb+"),"))==0)");
      fprintf(Outfile,"%s\n","       {");
      fprintf(Outfile,"%s%s%s\n","         fprintf(stderr,",enc("Can't open file %s\\n"),",TmpFile);");
      fprintf(Outfile,"%s\n","         exit(1);");
      fprintf(Outfile,"%s\n","       }");
      fprintf(Outfile,"%s\n","      for(i=0; i<blocks; i+=1)");
      fprintf(Outfile,"%s\n","        {");
      fprintf(Outfile,"%s\n","          fread(tmp,1,length,FP1);");
      fprintf(Outfile,"%s\n","          fwrite(tmp,1,length,FP2);");
      fprintf(Outfile,"%s\n","        }");
      fprintf(Outfile,"%s\n","      if(overage>0)");
      fprintf(Outfile,"%s\n","        {");
      fprintf(Outfile,"%s\n","          fread(tmp,1,overage,FP1);");
      fprintf(Outfile,"%s\n","          fwrite(tmp,1,overage,FP2);");
      fprintf(Outfile,"%s\n","        }");
      fprintf(Outfile,"%s\n","      fclose(FP2); fclose(FP1);");
      fprintf(Outfile,"%s\n","      if(tmp) free(tmp);");
      fprintf(Outfile,"%s\n","      struct stat st;");
      fprintf(Outfile,"%s\n","      if(stat(InFile, &st) != -1)");
      fprintf(Outfile,"%s\n","        chmod(TmpFile,st.st_mode);");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Str_Cmp)
    {
      fprintf(Outfile,"%s\n","int str_cmp (char *a, char *b)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int counter=0;");
      fprintf(Outfile,"%s\n","  for(;;)");
      fprintf(Outfile,"%s\n","   {");
      fprintf(Outfile,"%s\n","    if((a[counter]^b[counter]))");
      fprintf(Outfile,"%s\n","     {");
      fprintf(Outfile,"%s\n","      if((UINT) a[counter]>= (UINT) b[counter])");
      fprintf(Outfile,"%s\n","      return  1;");
      fprintf(Outfile,"%s\n","      return -1;");
      fprintf(Outfile,"%s\n","     }");
      fprintf(Outfile,"%s\n","    if(!a[counter]) return 0;");
      fprintf(Outfile,"%s\n","    counter++;");
      fprintf(Outfile,"%s\n","   }");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Eof)
    {
      fprintf(Outfile,"%s\n","int EoF (FILE* stream)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int c, status = ((c = fgetc(stream)) == EOF);");
      fprintf(Outfile,"%s\n","  ungetc(c,stream);");
      fprintf(Outfile,"%s\n","  return status;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Cint)
    {
      fprintf(Outfile,"%s\n","int Cint (double A)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  return (A >=0 ? (int)(A+0.5) : (int)(A-0.5));");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Clng)
    {
      fprintf(Outfile,"%s\n","long CLNG (double A)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  float   r=.5;");
      fprintf(Outfile,"%s\n","  double  a=A-(long)A;");
      fprintf(Outfile,"%s\n","  if(A<0) { r=-.5; a=-a; }");
      fprintf(Outfile,"%s\n","  if(((long)A % 2)==0&&a<=.5)");
      fprintf(Outfile,"%s\n","    return (long)A;");
      fprintf(Outfile,"%s\n","  else");
      fprintf(Outfile,"%s\n","    return (long)(A+r);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Left)
    {
      fprintf(Outfile,"%s\n","char *left (char *S, int length)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int tmplen = strlen(S);");
      fprintf(Outfile,"%s\n","  if(length<1) return BCX_TmpStr(1);");
      fprintf(Outfile,"%s\n","  if(length<tmplen) tmplen=length;");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr(tmplen);");
      fprintf(Outfile,"%s\n","  return (char*)memcpy(strtmp,S,tmplen);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Right)
    {
      fprintf(Outfile,"%s\n","char *right (char *S, int length)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int tmplen = strlen(S);");
      fprintf(Outfile,"%s\n","  char *BCX_RetStr = BCX_TmpStr(tmplen);");
      fprintf(Outfile,"%s\n","  tmplen -= length;");
      fprintf(Outfile,"%s\n","  if (tmplen<0) tmplen = 0;");
      fprintf(Outfile,"%s\n","  return strcpy(BCX_RetStr, &S[tmplen]);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Rpad)
    {
      fprintf(Outfile,"%s\n","char *rpad (char *a, int L, int c)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *strtmp;");
      fprintf(Outfile,"%s\n","  int s = strlen(a);");
      fprintf(Outfile,"%s\n","  if((L-s)<1) return a;");
      fprintf(Outfile,"%s\n","  strtmp=BCX_TmpStr(L);");
      fprintf(Outfile,"%s\n","  strcpy(strtmp,a);");
      fprintf(Outfile,"%s\n","  memset(&strtmp[s],c,(L-s));");
      fprintf(Outfile,"%s\n","  return strtmp;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Lpad)
    {
      fprintf(Outfile,"%s\n","char *lpad (char *a, int L, int c)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *strtmp;");
      fprintf(Outfile,"%s\n","  L=L-strlen(a);");
      fprintf(Outfile,"%s\n","  if(L<1) return a;");
      fprintf(Outfile,"%s\n","  strtmp = BCX_TmpStr(L);");
      fprintf(Outfile,"%s\n","  memset(strtmp,c,L);");
      fprintf(Outfile,"%s\n","  return strcat(strtmp,a);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Mid)
    {
      fprintf(Outfile,"%s\n","char *mid (char *S, int start, int length)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *strtmp;");
      fprintf(Outfile,"%s\n","  int tmplen = strlen(S);");
      fprintf(Outfile,"%s\n","  if(start>tmplen||start<1) return BCX_TmpStr(1);");
      fprintf(Outfile,"%s\n","  if (length<0 || length>(tmplen-start)+1)");
      fprintf(Outfile,"%s\n","    length = (tmplen-start)+1;");
      fprintf(Outfile,"%s\n","  strtmp = BCX_TmpStr(length);");
      fprintf(Outfile,"%s\n","  return (char*)memcpy(strtmp,&S[start-1],length);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Trim)
    {
      fprintf(Outfile,"%s\n","char *trim (char *S)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  while(*S==32 || *S==9 || *S==10 || *S==11 || *S==13)");
      fprintf(Outfile,"%s\n","    S++;");
      fprintf(Outfile,"%s\n","  int i = strlen(S);");
      fprintf(Outfile,"%s\n","  while( i>0 && (S[i-1]==32 || S[i-1]==9 || S[i-1]==10");
      fprintf(Outfile,"%s\n","             || S[i-1]==11 || S[i-1]==13))");
      fprintf(Outfile,"%s\n","    i--;");
      fprintf(Outfile,"%s\n","  char *strtmp=BCX_TmpStr(i);");
      fprintf(Outfile,"%s\n","  return (char*)memcpy(strtmp,S,i);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Ltrim)
    {
      fprintf(Outfile,"%s\n","char *ltrim (char *S, char c)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  if(S[0]==0) return S;");
      fprintf(Outfile,"%s\n","  while((*S==32 || *S==c) && *S !=0) S++;");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr(strlen(S));");
      fprintf(Outfile,"%s\n","  return strcpy(strtmp,S);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Rtrim)
    {
      fprintf(Outfile,"%s\n","char *rtrim (char *S,char c)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  if(S[0]==0) return S;");
      fprintf(Outfile,"%s\n","  int i = strlen(S);");
      fprintf(Outfile,"%s\n","  while(i>0 && (S[i-1]==c || S[i-1]==32))");
      fprintf(Outfile,"%s\n","    i--;");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr(i);");
      fprintf(Outfile,"%s\n","  return (char*)memcpy(strtmp,S,i);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Strim)
    {
      fprintf(Outfile,"%s\n","char *strim (char *src)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr(strlen(src));");
      fprintf(Outfile,"%s\n","  char *dst = strtmp;");
      fprintf(Outfile,"%s\n","  while (isspace((unsigned char)*src)) src++;");
      fprintf(Outfile,"%s\n","  do");
      fprintf(Outfile,"%s\n","  {");
      fprintf(Outfile,"%s\n","    while (*src && !isspace((unsigned char)*src)) *dst++ = *src++;");
      fprintf(Outfile,"%s\n","    if (*src)");
      fprintf(Outfile,"%s\n","      {");
      fprintf(Outfile,"%s\n","        *dst++ = *src++;");
      fprintf(Outfile,"%s\n","        while (isspace((unsigned char)*src)) src++;");
      fprintf(Outfile,"%s\n","      }");
      fprintf(Outfile,"%s\n","  } while (*src);");
      fprintf(Outfile,"%s\n","  if (isspace((unsigned char)*(--dst))) *dst = 0;");
      fprintf(Outfile,"%s\n","  return strtmp;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Command)
    {
      fprintf(Outfile,"%s\n","char *command (int nArg)");
      fprintf(Outfile,"%s\n"," {");
      fprintf(Outfile,"%s\n"," int i = 0;");
      fprintf(Outfile,"%s\n"," char *retstr=BCX_TmpStr(1);");
      fprintf(Outfile,"%s\n"," if(nArg < i) // return entire commandline");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      retstr = BCX_TmpStr(G_argc * 2048);");
      fprintf(Outfile,"%s\n","      for(i=1; i < G_argc; i++)");
      fprintf(Outfile,"%s\n","         {");
      fprintf(Outfile,"%s\n","         strcat(retstr, G_argv[i]);");
      fprintf(Outfile,"%s\n","         strcat(retstr, SPC);");
      fprintf(Outfile,"%s\n","         }");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n"," else if(nArg < G_argc)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      retstr = BCX_TmpStr(strlen(G_argv[nArg]) + 1);");
      fprintf(Outfile,"%s\n","      strcpy(retstr, G_argv[nArg]);");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n"," return retstr;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Extract)
    {
      fprintf(Outfile,"%s\n","char *extract (char *mane, char *match)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *a;");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr(strlen(mane));");
      fprintf(Outfile,"%s\n","  if(*match!=0)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      a=_strstr_(mane,match);");
      fprintf(Outfile,"%s\n","      if(a) return (char*)memcpy(strtmp,mane,a-mane);");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  return strcpy(strtmp,mane);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Remain)
    {
      fprintf(Outfile,"%s\n","char *remain (char *mane, char *mat)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *p = strstr(mane,mat);");
      fprintf(Outfile,"%s\n","  if(p)");
      fprintf(Outfile,"%s\n","  {");
      fprintf(Outfile,"%s\n","    p+=(strlen(mat));");
      fprintf(Outfile,"%s\n","    return p;");
      fprintf(Outfile,"%s\n","  }");
      fprintf(Outfile,"%s\n","  return mane;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Replace)
    {
      fprintf(Outfile,"%s\n","char *replace (char *src, char *pat, char *rep)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  size_t patsz, repsz, tmpsz, delta;");
      fprintf(Outfile,"%s\n","  char *strtmp, *p, *q, *r;");
      fprintf(Outfile,"%s\n","  if (!pat || !*pat)");
      fprintf(Outfile,"%s\n","   {");
      fprintf(Outfile,"%s\n","     strtmp = BCX_TmpStr(strlen(src));");
      fprintf(Outfile,"%s\n","     if (!strtmp) return NULL;");
      fprintf(Outfile,"%s\n","     return strcpy(strtmp, src);");
      fprintf(Outfile,"%s\n","   }");
      fprintf(Outfile,"%s\n","  repsz = strlen(rep);");
      fprintf(Outfile,"%s\n","  patsz = strlen(pat);");
      fprintf(Outfile,"%s\n","  for (tmpsz=0, p=src; (q=_strstr_(p,pat))!=0; p=q+patsz)");
      fprintf(Outfile,"%s\n","   tmpsz += (size_t) (q - p) + repsz;");
      fprintf(Outfile,"%s\n","   tmpsz += strlen(p);");
      fprintf(Outfile,"%s\n","   strtmp = BCX_TmpStr(tmpsz);");
      fprintf(Outfile,"%s\n","   if (!strtmp) return NULL;");
      fprintf(Outfile,"%s\n","    for (r=strtmp,p=src; (q=_strstr_(p,pat))!=0;p=q+patsz)");
      fprintf(Outfile,"%s\n","     {");
      fprintf(Outfile,"%s\n","       delta = (size_t) (q-p);");
      fprintf(Outfile,"%s\n","       memcpy(r,p,delta); r += delta;");
      fprintf(Outfile,"%s\n","       strcpy(r,rep);      r += repsz;");
      fprintf(Outfile,"%s\n","     }");
      fprintf(Outfile,"%s\n","  strcpy(r,p);");
      fprintf(Outfile,"%s\n","  return strtmp;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Reverse)
    {
      fprintf(Outfile,"%s\n","char *reverse (char *s)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int j=strlen(s);");
      fprintf(Outfile,"%s\n","  char *rstr = BCX_TmpStr(j);");
      fprintf(Outfile,"%s\n","  while(j)  rstr[--j] = *(s++);");
      fprintf(Outfile,"%s\n","  return rstr;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Findfirst)
    {
      fprintf(Outfile,"%s\n","char *findfirst (char *filespec, FILE_FIND_DATA *FindData)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  struct dirent *dp;");
      fprintf(Outfile,"%s\n","  struct stat st;");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","  if(FindData->FileHandle)");
      fprintf(Outfile,"%s\n","    closedir(FindData->FileHandle);");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","  strcpy(FindData->path, BcxSplitPath(filespec, FDRV|FPATH));");
      fprintf(Outfile,"%s\n","  strcpy(FindData->cFileSpec,BcxSplitPath(filespec, FNAME|FEXT));");
      fprintf(Outfile,"%s%s%s\n","  if(*FindData->path==0) strcpy(FindData->path, ",enc("."),");");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","  FindData->FileHandle=opendir(FindData->path);");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","  while(FindData->FileHandle)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      dp=readdir(FindData->FileHandle);");
      fprintf(Outfile,"%s\n","      if(dp==NULL) break;");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","      if(like(dp->d_name,FindData->cFileSpec))");
      fprintf(Outfile,"%s\n","        {");
      fprintf(Outfile,"%s\n","          strcpy(FindData->cFileName,dp->d_name);");
      fprintf(Outfile,"%s\n","          lstat(join(2,FindData->path,dp->d_name), &st);");
      fprintf(Outfile,"%s\n","          FindData->dwFileAttributes = st.st_mode;");
      fprintf(Outfile,"%s\n","          return FindData->cFileName;");
      fprintf(Outfile,"%s\n","        }");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","  *FindData->cFileName=0;");
      fprintf(Outfile,"%s\n","  return FindData->cFileName;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Findnext)
    {
      fprintf(Outfile,"%s\n","char *findnext (FILE_FIND_DATA *FindData)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  struct dirent *dp;");
      fprintf(Outfile,"%s\n","  struct stat st;");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","  while(FindData->FileHandle)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      dp=readdir(FindData->FileHandle);");
      fprintf(Outfile,"%s\n","      if(dp==NULL) break;");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","      if(like(dp->d_name,FindData->cFileSpec))");
      fprintf(Outfile,"%s\n","        {");
      fprintf(Outfile,"%s\n","          strcpy(FindData->cFileName,dp->d_name);");
      fprintf(Outfile,"%s\n","          lstat(join(2,FindData->path,dp->d_name), &st);");
      fprintf(Outfile,"%s\n","          FindData->dwFileAttributes = st.st_mode;");
      fprintf(Outfile,"%s\n","          return FindData->cFileName;");
      fprintf(Outfile,"%s\n","        }");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","  *FindData->cFileName=0;");
      fprintf(Outfile,"%s\n","  return FindData->cFileName;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Ucase)
    {
      fprintf(Outfile,"%s\n","char *ucase (char *S)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr(strlen(S));");
      fprintf(Outfile,"%s\n","  return _strupr_(strcpy(strtmp,S));");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Lcase)
    {
      fprintf(Outfile,"%s\n","char *lcase (char *S)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr(strlen(S));");
      fprintf(Outfile,"%s\n","  return _strlwr_(strcpy(strtmp,S));");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Mcase)
    {
      fprintf(Outfile,"%s\n","char *mcase (char *S)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr(strlen(S)+1);");
      fprintf(Outfile,"%s\n","  char *s = strtmp;");
      fprintf(Outfile,"%s\n","  _strlwr_(strcpy(strtmp,S));");
      fprintf(Outfile,"%s\n","  while(*s)");
      fprintf(Outfile,"%s\n","  {");
      fprintf(Outfile,"%s\n","    if(islower(*s))");
      fprintf(Outfile,"%s\n","      {");
      fprintf(Outfile,"%s\n","        *s-=32;");
      fprintf(Outfile,"%s\n","        while(isalpha(*++s));");
      fprintf(Outfile,"%s\n","      }");
      fprintf(Outfile,"%s\n","     s++;");
      fprintf(Outfile,"%s\n","  }");
      fprintf(Outfile,"%s\n","  return strtmp;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Remove)
    {
      fprintf(Outfile,"%s\n","char *RemoveStr (char *a, char *b)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *strtmp, *p, *d;");
      fprintf(Outfile,"%s\n","  int  tmplen;");
      fprintf(Outfile,"%s\n","  strtmp = d = BCX_TmpStr(strlen(a));");
      fprintf(Outfile,"%s\n","  if(!b || !*b) return strcpy(strtmp,a);");
      fprintf(Outfile,"%s\n","  p=_strstr_(a,b); tmplen = strlen(b);");
      fprintf(Outfile,"%s\n","  while(p)");
      fprintf(Outfile,"%s\n","   {");
      fprintf(Outfile,"%s\n","     memcpy(d,a,p-a);");
      fprintf(Outfile,"%s\n","     d+= (p-a);");
      fprintf(Outfile,"%s\n","     a=p+tmplen;");
      fprintf(Outfile,"%s\n","     p=_strstr_(a,b);");
      fprintf(Outfile,"%s\n","   }");
      fprintf(Outfile,"%s\n","  strcpy(d,a);");
      fprintf(Outfile,"%s\n","  return strtmp;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_IRemove)
    {
      fprintf(Outfile,"%s\n","char *IRemoveStr (char *a, char *b)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *strtmp, *p, *d;");
      fprintf(Outfile,"%s\n","  int  tmplen;");
      fprintf(Outfile,"%s\n","  strtmp = d = BCX_TmpStr(strlen(a));");
      fprintf(Outfile,"%s\n","  if(!b || !*b) return strcpy(strtmp,a);");
      fprintf(Outfile,"%s\n","  p=_stristr_(a,b); tmplen = strlen(b);");
      fprintf(Outfile,"%s\n","  while(p)");
      fprintf(Outfile,"%s\n","   {");
      fprintf(Outfile,"%s\n","     memcpy(d,a,p-a);");
      fprintf(Outfile,"%s\n","     d+= (p-a);");
      fprintf(Outfile,"%s\n","     a=p+tmplen;");
      fprintf(Outfile,"%s\n","     p=_stristr_(a,b);");
      fprintf(Outfile,"%s\n","   }");
      fprintf(Outfile,"%s\n","  strcpy(d,a);");
      fprintf(Outfile,"%s\n","  return strtmp;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Ins)
    {
      fprintf(Outfile,"%s\n","char *ins (char *S, int i, char *a)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int j = strlen(S);");
      fprintf(Outfile,"%s\n","  if(i<1 || i>j+1) return S;");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr(j + strlen(a));");
      fprintf(Outfile,"%s\n","  memcpy(strtmp,S,--i);");
      fprintf(Outfile,"%s\n","  strcpy(&strtmp[i],a);");
      fprintf(Outfile,"%s\n","  return strcat(strtmp,&S[i]);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Del)
    {
      fprintf(Outfile,"%s\n","char *del (char *S, int i, int j)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int ln = strlen(S);");
      fprintf(Outfile,"%s\n","  if(i<1 || i>ln) return S;");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr(ln);");
      fprintf(Outfile,"%s\n","  memcpy(strtmp,S,--i);");
      fprintf(Outfile,"%s\n","  return strcat(strtmp,&S[i+j]);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Str)
    {
      fprintf(Outfile,"%s\n","char *str (double d)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr(16);");
      fprintf(Outfile,"%s%s%s\n","  sprintf(strtmp,",D1,",d);");
      fprintf(Outfile,"%s\n","  return strtmp;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Strl)
    {
      fprintf(Outfile,"%s\n","char *strl (long double d)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr(27);");
      fprintf(Outfile,"%s%s%s\n","  sprintf(strtmp,",D2,",d);");
      fprintf(Outfile,"%s\n","  return strtmp;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Curdir)
    {
      fprintf(Outfile,"%s\n","char *curdir (void)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr(2048);");
      fprintf(Outfile,"%s\n","  char *res=getcwd(strtmp, 1024);");
      fprintf(Outfile,"%s\n","  return strtmp;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Hex)
    {
      fprintf(Outfile,"%s\n","char *hex (int a)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr(16);");
      fprintf(Outfile,"%s%s%s\n","  sprintf(strtmp,",enc("%02X"),",a);");
      fprintf(Outfile,"%s\n","  return strtmp;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Tempdir)
    {
      fprintf(Outfile,"%s\n","char *tempdir (void)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr(2048);");
      fprintf(Outfile,"%s%s%s\n","  if(!Exist(",enc("/tmp/mbc.compiler"),")) {");
      fprintf(Outfile,"%s%s%s\n","    mkdir (",enc("/tmp/mbc.compiler"),",0755);");
      fprintf(Outfile,"%s\n","  }");
      fprintf(Outfile,"%s%s%s\n","  strcpy(strtmp,",enc("/tmp/mbc.compiler"),");");
      fprintf(Outfile,"%s\n","  return strtmp;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Sysdir)
    {
      fprintf(Outfile,"%s\n","char *sysdir (void)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr(2048);");
      fprintf(Outfile,"%s\n","  GetSystemDirectory (strtmp,2048);");
      fprintf(Outfile,"%s\n","  return strtmp;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Repeat)
    {
      fprintf(Outfile,"%s\n","char *repeat (int count, char *a)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr((1+count)*strlen(a));");
      fprintf(Outfile,"%s\n","  while(count-->0) strtmp = strcat(strtmp, a);");
      fprintf(Outfile,"%s\n","  return strtmp;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_String)
    {
      fprintf(Outfile,"%s\n","char *stringx (int count, int a)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  if(count<1) return BCX_TmpStr(1);");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr(count);");
      fprintf(Outfile,"%s\n","  return (char*)memset(strtmp,a,count);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Shell)
    {
      fprintf(Outfile,"%s\n","void Shell (char *cmd)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int res=system(cmd);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Space)
    {
      fprintf(Outfile,"%s\n","char *space (int count)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  if(count<1) return BCX_TmpStr(1);");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr(count);");
      fprintf(Outfile,"%s\n","  return (char*)memset(strtmp,32,count);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Time)
    {
      fprintf(Outfile,"%s\n","char *timef (int t)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  time_t elapse_time;");
      fprintf(Outfile,"%s\n","  struct tm *tp;");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr(256);");
      fprintf(Outfile,"%s\n","  time (&elapse_time);");
      fprintf(Outfile,"%s\n","  tp = localtime(&elapse_time);");
      fprintf(Outfile,"%s\n","  switch (t)");
      fprintf(Outfile,"%s\n","  {");
      fprintf(Outfile,"%s\n","   case 0:");
      fprintf(Outfile,"%s%s%s\n","   strftime(strtmp,256,",T0,",tp); break;");
      fprintf(Outfile,"%s\n","   case 1:");
      fprintf(Outfile,"%s%s%s\n","   strftime(strtmp,256,",T1,",tp); break;");
      fprintf(Outfile,"%s\n","   case 2:");
      fprintf(Outfile,"%s%s%s\n","   strftime(strtmp,256,",T2,",tp); break;");
      fprintf(Outfile,"%s\n","   case 3:");
      fprintf(Outfile,"%s%s%s\n","   strftime(strtmp,256,",T3,",tp); break;");
      fprintf(Outfile,"%s\n","   case 4:");
      fprintf(Outfile,"%s%s%s\n","   strftime(strtmp,256,",T4,",tp); break;");
      fprintf(Outfile,"%s\n","   case 5:");
      fprintf(Outfile,"%s%s%s\n","   strftime(strtmp,256,",T5,",tp); break;");
      fprintf(Outfile,"%s\n","   case 6:");
      fprintf(Outfile,"%s%s%s\n","   strftime(strtmp,256,",T6,",tp); break;");
      fprintf(Outfile,"%s\n","   case 7:");
      fprintf(Outfile,"%s%s%s\n","   strftime(strtmp,256,",T7,",tp); break;");
      fprintf(Outfile,"%s\n","   case 8:");
      fprintf(Outfile,"%s%s%s\n","   strftime(strtmp,256,",T8,",tp); break;");
      fprintf(Outfile,"%s\n","   case 9:");
      fprintf(Outfile,"%s%s%s\n","   strftime(strtmp,256,",T9,",tp); break;");
      fprintf(Outfile,"%s\n","   case 10:");
      fprintf(Outfile,"%s%s%s\n","   strftime(strtmp,256,",T10,",tp); break;");
      fprintf(Outfile,"%s\n","   case 11:");
      fprintf(Outfile,"%s%s%s\n","   strftime(strtmp,256,",T11,",tp); break;");
      fprintf(Outfile,"%s\n","   case 12:");
      fprintf(Outfile,"%s%s%s\n","   strftime(strtmp,256,",T12,",tp); break;");
      fprintf(Outfile,"%s\n","   case 13:");
      fprintf(Outfile,"%s%s%s\n","   strftime(strtmp,256,",T13,",tp); break;");
      fprintf(Outfile,"%s\n","  }");
      fprintf(Outfile,"%s\n","  return strtmp;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Enclose)
    {
      fprintf(Outfile,"%s\n","char *enc (char *A, int L, int R)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *BCX_RetStr = BCX_TmpStr(strlen(A)+3);");
      fprintf(Outfile,"%s\n","  if(L==0) L=34;");
      fprintf(Outfile,"%s\n","  if(R==0) R=L;");
      fprintf(Outfile,"%s%s%s%s%s\n","  sprintf(BCX_RetStr,",enc("%c%s%c%s"),",L,A,R,",enc("\0"),");");
      fprintf(Outfile,"%s\n","  return BCX_RetStr;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Chr)
    {
      fprintf(Outfile,"%s\n","char *chr (int a,int b,int c,int d,int e,int f,int g,int h,int i,int j)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr(11);");
      fprintf(Outfile,"%s\n","  strtmp[0]  = a;");
      fprintf(Outfile,"%s\n","  strtmp[1]  = b;");
      fprintf(Outfile,"%s\n","  strtmp[2]  = c;");
      fprintf(Outfile,"%s\n","  strtmp[3]  = d;");
      fprintf(Outfile,"%s\n","  strtmp[4]  = e;");
      fprintf(Outfile,"%s\n","  strtmp[5]  = f;");
      fprintf(Outfile,"%s\n","  strtmp[6]  = g;");
      fprintf(Outfile,"%s\n","  strtmp[7]  = h;");
      fprintf(Outfile,"%s\n","  strtmp[8]  = i;");
      fprintf(Outfile,"%s\n","  strtmp[9]  = j;");
      fprintf(Outfile,"%s\n","  strtmp[10] = 0;");
      fprintf(Outfile,"%s\n","  return strtmp;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_VChr)
    {
      fprintf(Outfile,"%s\n","char *vchr(int charcount, ...)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int c = 0, i = charcount;");
      fprintf(Outfile,"%s\n","  char *s_ = BCX_TmpStr(charcount + 1);");
      fprintf(Outfile,"%s\n","  va_list marker;");
      fprintf(Outfile,"%s\n","  s_[i] = 0;");
      fprintf(Outfile,"%s\n","  va_start(marker, charcount);");
      fprintf(Outfile,"%s\n","  while(i-- > 0) s_[c++] = va_arg(marker,int);");
      fprintf(Outfile,"%s\n","  va_end(marker);");
      fprintf(Outfile,"%s\n","  return s_;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Join)
    {
      fprintf(Outfile,"%s\n","char * join(int n, ...)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int i = n, tmplen = 0;");
      fprintf(Outfile,"%s\n","  char *strtmp, *s_;");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","  va_list marker;");
      fprintf(Outfile,"%s\n","  va_start(marker, n); // Initialize variable arguments");
      fprintf(Outfile,"%s\n","  while(i-- > 0)");
      fprintf(Outfile,"%s\n","  {");
      fprintf(Outfile,"%s\n","    s_ = va_arg(marker, char *);");
      fprintf(Outfile,"%s\n","    if(s_) tmplen += strlen(s_);");
      fprintf(Outfile,"%s\n","  }");
      fprintf(Outfile,"%s\n","  strtmp = BCX_TmpStr(tmplen);");
      fprintf(Outfile,"%s\n","  va_end(marker); // Reset variable arguments");
      fprintf(Outfile,"%s\n","  i = n;");
      fprintf(Outfile,"%s\n","  va_start(marker, n); // Initialize variable arguments");
      fprintf(Outfile,"%s\n","  while(i-- > 0)");
      fprintf(Outfile,"%s\n","  {");
      fprintf(Outfile,"%s\n","    s_ = va_arg(marker, char *);");
      fprintf(Outfile,"%s\n","    if(s_) strcat(strtmp, s_);");
      fprintf(Outfile,"%s\n","  }");
      fprintf(Outfile,"%s\n","  va_end(marker); // Reset variable arguments");
      fprintf(Outfile,"%s\n","  return strtmp;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Environ)
    {
      fprintf(Outfile,"%s\n","char* Environ(char *S)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *strtmp, *tmp;");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","  tmp = getenv(S);");
      fprintf(Outfile,"%s\n","  if(tmp != NULL) {");
      fprintf(Outfile,"%s\n","    strtmp = BCX_TmpStr(strlen(tmp)+1);");
      fprintf(Outfile,"%s\n","    return strcpy(strtmp, tmp);");
      fprintf(Outfile,"%s\n","  }");
      fprintf(Outfile,"%s\n","  return BCX_TmpStr(1);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Oct)
    {
      fprintf(Outfile,"%s\n","char *oct (int a)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr(2048);");
      fprintf(Outfile,"%s%s%s\n","  sprintf(strtmp,",O1,",a);");
      fprintf(Outfile,"%s\n","  return strtmp;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Bin)
    {
      fprintf(Outfile,"%s\n","char* Bin(int number)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr(2048);");
      fprintf(Outfile,"%s\n","   itoa(number,strtmp,2);");
      fprintf(Outfile,"%s\n","  return strtmp;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Pause)
    {
      fprintf(Outfile,"%s\n","void Pause(void)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s%s%s%s%s\n","  printf(",enc("\\n%s\\n"),",",enc("Press any key to continue . . ."),");");
      fprintf(Outfile,"%s\n","  _getch_(TRUE);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Keypress)
    {
      fprintf(Outfile,"%s\n","int keypress(void)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  return _getch_(TRUE);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Inkey)
    {
      fprintf(Outfile,"%s\n","char* inkey(void)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr(2);");
      fprintf(Outfile,"%s\n","  strtmp[0] = _getch_(FALSE);");
      fprintf(Outfile,"%s\n","  if(strtmp[0] == -1) strtmp[0] = 0;");
      fprintf(Outfile,"%s\n","  return strtmp;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_InkeyD)
    {
      fprintf(Outfile,"%s\n","int inkeyd(void)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  return _getch_(TRUE);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Instat)
    {
      fprintf(Outfile,"%s\n","int kbhit(void)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  struct termios oldt, newt;");
      fprintf(Outfile,"%s\n","  int ch;");
      fprintf(Outfile,"%s\n","	int oldf;");
      fprintf(Outfile,"%s\n","  tcgetattr(STDIN_FILENO, &oldt);");
      fprintf(Outfile,"%s\n","  newt = oldt;");
      fprintf(Outfile,"%s\n","  newt.c_lflag &= ~(ICANON | ECHO);");
      fprintf(Outfile,"%s\n","  tcsetattr(STDIN_FILENO, TCSANOW, &newt);");
      fprintf(Outfile,"%s\n","  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);");
      fprintf(Outfile,"%s\n","  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);");
      fprintf(Outfile,"%s\n","  ch = getchar();");
      fprintf(Outfile,"%s\n","  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);");
      fprintf(Outfile,"%s\n","  fcntl(STDIN_FILENO, F_SETFL, oldf);");
      fprintf(Outfile,"%s\n","  if(ch != EOF)");
      fprintf(Outfile,"%s\n","  {");
      fprintf(Outfile,"%s\n","    ungetc(ch, stdin);");
      fprintf(Outfile,"%s\n","    return 1;");
      fprintf(Outfile,"%s\n","  }");
      fprintf(Outfile,"%s\n","  return 0;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_GetCh)
    {
      fprintf(Outfile,"%s\n","int _getch_(int waitkey)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  struct termios initial_settings, new_settings;");
      fprintf(Outfile,"%s\n","  unsigned char ch;");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","  tcgetattr(0,&initial_settings);");
      fprintf(Outfile,"%s\n","  new_settings = initial_settings;");
      fprintf(Outfile,"%s\n","  new_settings.c_lflag &= ~ICANON;");
      fprintf(Outfile,"%s\n","  new_settings.c_lflag &= ~ECHO;");
      fprintf(Outfile,"%s\n","  new_settings.c_lflag &= ~ISIG;");
      fprintf(Outfile,"%s\n","  new_settings.c_cc[VMIN] = waitkey;");
      fprintf(Outfile,"%s\n","  new_settings.c_cc[VTIME] = 0;");
      fprintf(Outfile,"%s\n","  tcsetattr(0, TCSANOW, &new_settings);");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","    //read(0,&ch,1);");
      fprintf(Outfile,"%s\n","    ch = getchar();");
      fprintf(Outfile,"%s\n","  tcsetattr(0, TCSANOW, &initial_settings);");
      fprintf(Outfile,"%s\n","  return ch;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Now)
    {
      fprintf(Outfile,"%s\n","char *now (void)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  time_t elapse_time;");
      fprintf(Outfile,"%s\n","  struct tm *tp;");
      fprintf(Outfile,"%s\n","  char *strtmp = BCX_TmpStr(2048);");
      fprintf(Outfile,"%s\n","  time(&elapse_time);");
      fprintf(Outfile,"%s\n","  tp=localtime(&elapse_time);");
      fprintf(Outfile,"%s%s%s\n","  strftime(strtmp,256,",enc("%m/%d/%y %I:%M:%S: %p"),",tp);");
      fprintf(Outfile,"%s\n","  return strtmp;");
      fprintf(Outfile,"%s\n","}");
    }
  if(Use_AppExePath)
    {
      fprintf(Outfile,"%s\n","char *AppExePath (void)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char fullpath[MAX_PATH];");
      fprintf(Outfile,"%s\n","  int length;");
 #if defined (__APPLE__)
      fprintf(Outfile,"%s\n","  pid_t pid = getpid();");
      fprintf(Outfile,"%s\n","  length = proc_pidpath (pid, fullpath, sizeof(fullpath));");
 #else
      fprintf(Outfile,"%s%s%s\n","  length = readlink(",enc("/proc/self/exe"),", fullpath, MAX_PATH);");
 #endif
      fprintf(Outfile,"%s\n","  if(length < 1) return BCX_TmpStr(1);");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","  fullpath[length] = 0;");
      fprintf(Outfile,"%s\n","  return BcxSplitPath(fullpath, FDRV|FPATH);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_AppExeName)
    {
      fprintf(Outfile,"%s\n","char *AppExeName (void)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  return BcxSplitPath(G_argv[0], FNAME|FEXT);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_TempFileName)
    {
      fprintf(Outfile,"%s\n","char * TempFileName (char *dr, char *prefix)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  static unsigned int count;");
      fprintf(Outfile,"%s\n","  char *f, *tmpstr = BCX_TmpStr(MAX_PATH);");
      fprintf(Outfile,"%s\n","  int  i, length;");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","  if(!count) srand(time(0));");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","  if(dr) strcpy(tmpstr, dr);");
      fprintf(Outfile,"%s\n","  length = strlen(tmpstr);");
      fprintf(Outfile,"%s\n","  if(length && (tmpstr[length-1] != '\\\\' && tmpstr[length-1] != '/'))");
      fprintf(Outfile,"%s\n","      tmpstr[length++] = '/';");
      fprintf(Outfile,"%s\n","  if(prefix) strcpy(&tmpstr[length], prefix);");
      fprintf(Outfile,"%s\n","  f = &tmpstr[strlen(tmpstr)];");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","  do {");
      fprintf(Outfile,"%s\n","      count++;");
      fprintf(Outfile,"%s\n","      for(i=0; i<5; i+=1)");
      fprintf(Outfile,"%s\n","        {");
      fprintf(Outfile,"%s\n","          do {");
      fprintf(Outfile,"%s\n","            f[i]=(char)(rnd()*122);");
      fprintf(Outfile,"%s\n","          }while((f[i]<65)||(f[i]>90&&f[i]<97));");
      fprintf(Outfile,"%s\n","        }");
      fprintf(Outfile,"%s%s%s\n","        snprintf(&f[5],3,",enc("%x"),", count);");
      fprintf(Outfile,"%s\n","    } while (Exist(tmpstr));");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","  return tmpstr;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Boolstr)
    {
      fprintf(Outfile,"%s\n","char * BoolStr (int a)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *BCX_RetStr=BCX_TmpStr(5);");
      fprintf(Outfile,"%s%s%s\n","  if(a) return strcpy(BCX_RetStr,",enc("True"),");");
      fprintf(Outfile,"%s%s%s\n","  return strcpy(BCX_RetStr,",enc("False"),");");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Using)
    {
      fprintf(Outfile,"%s\n","char *Using (char *Mask, double Num)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int Spaces = 0;");
      fprintf(Outfile,"%s\n","  int CntDec = 0;");
      fprintf(Outfile,"%s\n","  int Decimals = 0;");
      fprintf(Outfile,"%s\n","  int Dollar = 0;");
      fprintf(Outfile,"%s\n","  char* BCX_RetStr = BCX_TmpStr(512);");
      fprintf(Outfile,"%s\n","  char Buf_1[512]={0};");
      fprintf(Outfile,"%s\n","  char* p = Mask;");
      fprintf(Outfile,"%s\n","  char* r;");
      fprintf(Outfile,"%s\n","  int  len;");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","  while (*p)");
      fprintf(Outfile,"%s\n","  {");
      fprintf(Outfile,"%s\n","    if (*p == 36) Dollar++;");
      fprintf(Outfile,"%s\n","    if (*p == 32) Spaces++;");
      fprintf(Outfile,"%s\n","    if ((*p == 32 || *p == 35)&& CntDec) Decimals++;");
      fprintf(Outfile,"%s\n","    if (*p == 46) CntDec = 1;");
      fprintf(Outfile,"%s\n","    p++;");
      fprintf(Outfile,"%s\n","  }");
      fprintf(Outfile,"%s%s%s\n","  sprintf(Buf_1,",enc("%1.*f"),",Decimals,Num);");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","  len = strlen(Buf_1)-Decimals-(Decimals>0?1:0);");
      fprintf(Outfile,"%s\n","  r = BCX_RetStr+Dollar+Spaces;");
      fprintf(Outfile,"%s\n","  p = Buf_1;");
      fprintf(Outfile,"%s\n","  while (*p)");
      fprintf(Outfile,"%s\n","   {");
      fprintf(Outfile,"%s\n","     *r++ = *p++;");
      fprintf(Outfile,"%s\n","     if (--len>2 && *(p-1) != '-' && len % 3 == 0)");
      fprintf(Outfile,"%s\n","       {");
      fprintf(Outfile,"%s\n","         *r++ = ',';");
      fprintf(Outfile,"%s\n","       }");
      fprintf(Outfile,"%s\n","   }");
      fprintf(Outfile,"%s\n","  if(Dollar) BCX_RetStr[Spaces]=36;");
      fprintf(Outfile,"%s\n","  if(Spaces) memset(BCX_RetStr,32,Spaces);");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","  return BCX_RetStr;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_SearchPath)
    {
      fprintf(Outfile,"%s\n","char *SEARCHPATH (char *szFile)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *BCX_RetStr=BCX_TmpStr(MAX_PATH+1);");
      fprintf(Outfile,"%s\n","  PCHAR lpbs=0;");
      fprintf(Outfile,"%s\n","  SearchPath(0,szFile,0,MAX_PATH,BCX_RetStr,&lpbs);");
      fprintf(Outfile,"%s\n","  if(lpbs) *lpbs=0;");
      fprintf(Outfile,"%s\n","  return BCX_RetStr;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Instrrev)
    {
      fprintf(Outfile,"%s\n","int InstrRev (char *s, char *p, int os, int sens)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n"," int sl, pl, ox;");
      fprintf(Outfile,"%s\n"," int (*cmp)(const char *, const char *, size_t );");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n"," if (!s || !p)  return 0;");
      fprintf(Outfile,"%s\n"," sl  = strlen(s); pl  = strlen(p);");
      fprintf(Outfile,"%s\n"," if (os > sl || sl == 0 || pl == 0 || (ox = sl - pl) < 0)");
      fprintf(Outfile,"%s\n","   return 0;");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n"," if (os <= 0)  ");
      fprintf(Outfile,"%s\n","   os = ox ;");
      fprintf(Outfile,"%s\n"," else if(os >= pl)");
      fprintf(Outfile,"%s\n","   os = os - pl ;");
      fprintf(Outfile,"%s\n"," else");
      fprintf(Outfile,"%s\n","   return 0;");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n"," cmp = (sens ? strncasecmp : strncmp);");
      fprintf(Outfile,"%s\n"," do { if (cmp(s + os , p, pl) == 0)");
      fprintf(Outfile,"%s\n","       return os+1;");
      fprintf(Outfile,"%s\n","    } while (os--);");
      fprintf(Outfile,"%s\n"," return 0;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Instr)
    {
      fprintf(Outfile,"%s\n","int instr_b(char* mane,char* match,int offset,int sensflag)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *s;");
      fprintf(Outfile,"%s\n","  if (!mane || !match || ! *match || offset>(int)strlen(mane)) return 0;");
      fprintf(Outfile,"%s\n","  if (sensflag)");
      fprintf(Outfile,"%s\n","    s = _stristr_(offset>0 ? mane+offset-1 : mane,match);");
      fprintf(Outfile,"%s\n","  else");
      fprintf(Outfile,"%s\n","    s = _strstr_(offset>0 ? mane+offset-1 : mane,match);");
      fprintf(Outfile,"%s\n","  return s ? (int)(s-mane)+1 : 0;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(UseLCaseTbl)
    {
      fprintf(Outfile,"%s\n","char  *MakeLCaseTbl (void)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  static char tbl[256];");
      fprintf(Outfile,"%s\n","  if(!tbl['a'])");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      int i; for (i=0; i < 256; i++)");
      fprintf(Outfile,"%s\n","        tbl[i] = (char)(int)tolower(i);");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  return tbl;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Stristr)
    {
      fprintf(Outfile,"%s\n","char *_stristr_(char *String, char *Pattern)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int   mi=-1;");
      fprintf(Outfile,"%s\n","  char *LowCase = MakeLCaseTbl();");
      fprintf(Outfile,"%s\n","  while(Pattern[++mi])");
      fprintf(Outfile,"%s\n","   {");
      fprintf(Outfile,"%s\n","     if(String[mi]==0) return 0;");
      fprintf(Outfile,"%s\n","     if(LowCase[(unsigned char)String[mi]]!=LowCase[(unsigned char)Pattern[mi]])");
      fprintf(Outfile,"%s\n","       { String++; mi=-1; }");
      fprintf(Outfile,"%s\n","   }");
      fprintf(Outfile,"%s\n","  return String;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_StrStr)
    {
      fprintf(Outfile,"%s\n","char *_strstr_(char *String, char *Pattern)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int   mi=-1;");
      fprintf(Outfile,"%s\n","  while(Pattern[++mi])");
      fprintf(Outfile,"%s\n","   {");
      fprintf(Outfile,"%s\n","     if(String[mi]==0) return 0;");
      fprintf(Outfile,"%s\n","     if(String[mi]!=Pattern[mi])");
      fprintf(Outfile,"%s\n","       { String++; mi=-1; }");
      fprintf(Outfile,"%s\n","   }");
      fprintf(Outfile,"%s\n","  return String;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Inchr)
    {
      fprintf(Outfile,"%s\n","int inchr (char *A, char *B)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char* C=A;");
      fprintf(Outfile,"%s\n","  while(*C)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      if(*C==*B) return C-A+1;");
      fprintf(Outfile,"%s\n","      C++;");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  return 0;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Asc)
    {
      fprintf(Outfile,"%s\n","extern int asc (char *z,int index)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  return (unsigned char) z[index];");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Sgn)
    {
      fprintf(Outfile,"%s\n","double sgn (double a)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  if(a<0) return -1;");
      fprintf(Outfile,"%s\n","  if(a>0) return  1;");
      fprintf(Outfile,"%s\n","  return  0;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Round)
    {
      fprintf(Outfile,"%s\n","double Round (double n, int d)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  return (floor((n)*pow(10.0,(d))+0.5)/pow(10.0,(d)));");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Embed)
    {
      fprintf(Outfile,"%s\n","char* GetResource (int *resource)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *BCX_RetStr={0};");
      fprintf(Outfile,"%s\n","  static  char*  dat;");
      fprintf(Outfile,"%s\n","  memset(&dat,0,sizeof(char *));");
      fprintf(Outfile,"%s\n","  dat=(char*)resource;");
      fprintf(Outfile,"%s\n","  BCX_RetStr=BCX_TmpStr(strlen(dat));");
      fprintf(Outfile,"%s\n","  strcpy(BCX_RetStr,dat);");
      fprintf(Outfile,"%s\n","  return BCX_RetStr;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Exist)
    {
      fprintf(Outfile,"%s\n","bool Exist (char *szFilePath)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int retstat;");
      fprintf(Outfile,"%s\n","  struct stat sb;");
      fprintf(Outfile,"%s\n","  retstat = stat(szFilePath, &sb);");
      fprintf(Outfile,"%s\n","  if(retstat != -1)");
      fprintf(Outfile,"%s\n","    return TRUE;");
      fprintf(Outfile,"%s\n","  return FALSE;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Tally)
    {
      fprintf(Outfile,"%s\n","int tally (char *szLine, char *szChar, int sensflag)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  if(!*szChar) return 0;");
      fprintf(Outfile,"%s\n","  int   mlen = strlen(szChar);");
      fprintf(Outfile,"%s\n","  int  iCount = 0;");
      fprintf(Outfile,"%s\n","  char *p = (sensflag == 0 ? _strstr_(szLine, szChar) : _stristr_(szLine, szChar));");
      fprintf(Outfile,"%s\n","  while (p)");
      fprintf(Outfile,"%s\n","  {");
      fprintf(Outfile,"%s\n","    iCount++;");
      fprintf(Outfile,"%s\n","    p+=mlen;");
      fprintf(Outfile,"%s\n"," p = (sensflag == 0 ? _strstr_(p, szChar) : _stristr_(p, szChar));");
      fprintf(Outfile,"%s\n","  }");
      fprintf(Outfile,"%s\n","  return iCount;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Timer)
    {
      fprintf(Outfile,"%s\n","float timer (void)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  return ((double)clock()/CLOCKS_PER_SEC);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Rnd)
    {
      fprintf(Outfile,"%s\n","float rnd (void)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  return (float)rand()/RAND_MAX;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Exp)
    {
      fprintf(Outfile,"%s\n","double Exp (double arg)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  return pow(2.718281828459045,arg);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Randomize)
    {
      fprintf(Outfile,"%s\n","void randomize (unsigned int seed)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  srand(seed);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Max)
    {
      fprintf(Outfile,"%s\n","double _MAX_ (double a, double b)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  if(a>b)");
      fprintf(Outfile,"%s\n","  return a;");
      fprintf(Outfile,"%s\n","  return b;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Min)
    {
      fprintf(Outfile,"%s\n","double _MIN_ (double a, double b)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  if(a<b)");
      fprintf(Outfile,"%s\n","  return a;");
      fprintf(Outfile,"%s\n","  return b;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Locate)
    {
      fprintf(Outfile,"%s\n","void locate (int row,int col,int show,int shape)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s%s%s%s%s%s%s%s%s\n","  printf(",enc("%c%s%u%s%u%s"),",27,",enc("["),",row,",enc(";"),",col,",enc("H"),");");
      fprintf(Outfile,"%s\n","  // find cursor size/shape function!");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Cls)
    {
      fprintf(Outfile,"%s\n","void cls (void)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s%s%s%s%s%s%s\n","  printf(",enc("%s%s%s%s"),",ESC,",enc("[2J"),",ESC,",enc("[H"),");");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Color)
    {
      fprintf(Outfile,"%s\n","void color (int fg,int bg)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s%s%s%s%s%s%s%s%s\n","  printf(",enc("%c%s%u%s%u%s"),",27,",enc("["),",30+(fg&7),",enc(";"),",40+(bg&7),",enc("m"),");");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Midstr)
    {
      fprintf(Outfile,"%s\n","void midstr (char *src, int st, int length, char *rep)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int srclen = strlen(src);");
      fprintf(Outfile,"%s\n","  if(st>srclen++ || st<1) return;");
      fprintf(Outfile,"%s\n","  int replen = strlen(rep);");
      fprintf(Outfile,"%s\n","  if(replen < length || length==-1) length=replen;");
      fprintf(Outfile,"%s\n","  if((st+length) > srclen) length=srclen-st;");
      fprintf(Outfile,"%s\n","  memcpy(&src[st-1],rep,length);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Swap)
    {
      fprintf(Outfile,"%s\n","void swap ( UCHAR* A, UCHAR* B, int length)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  UCHAR t;");
      fprintf(Outfile,"%s\n","  while(length--)");
      fprintf(Outfile,"%s\n","  {");
      fprintf(Outfile,"%s\n","    t = *A;");
      fprintf(Outfile,"%s\n","    *(A++) = *B;");
      fprintf(Outfile,"%s\n","    *(B++) = t;");
      fprintf(Outfile,"%s\n","  }");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Like)
    {
      fprintf(Outfile,"%s\n","int like (char *raw, char *pat)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n"," char a, b, d;");
      fprintf(Outfile,"%s\n"," char *r, *p;");
      fprintf(Outfile,"%s\n"," int star = 0;");
      fprintf(Outfile,"%s\n"," for(;;) {");
      fprintf(Outfile,"%s\n","   if ((d = *pat++)==0) return (star || !*raw);");
      fprintf(Outfile,"%s\n","   else if (d == '*') star = 1;");
      fprintf(Outfile,"%s\n","   else if (d == '?') { if (!*raw++) return 0; }");
      fprintf(Outfile,"%s\n","   else break;");
      fprintf(Outfile,"%s\n"," }");
      fprintf(Outfile,"%s\n"," b = d;");
      fprintf(Outfile,"%s\n"," do if ((a = *raw++) == b) {");
      fprintf(Outfile,"%s\n","   r = raw;");
      fprintf(Outfile,"%s\n","   p = pat;");
      fprintf(Outfile,"%s\n","   do {");
      fprintf(Outfile,"%s\n","     if ((d = *p++) == '*')");
      fprintf(Outfile,"%s\n","       if (like(r, p - 1)) return 1;");
      fprintf(Outfile,"%s\n","       else break;");
      fprintf(Outfile,"%s\n","     else if (!d) {");
      fprintf(Outfile,"%s\n","       if (!*r) return 1;");
      fprintf(Outfile,"%s\n","       else break;");
      fprintf(Outfile,"%s\n","     }");
      fprintf(Outfile,"%s\n","   } while (*r++ == d || d == '?');");
      fprintf(Outfile,"%s\n"," } while (star && a);");
      fprintf(Outfile,"%s\n"," return 0;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Lof)
    {
      fprintf(Outfile,"%s\n","DWORD lof (char *FileName)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","  int retstat;");
      fprintf(Outfile,"%s\n","  struct stat sb;");
      fprintf(Outfile,"%s\n","  retstat = stat(FileName, &sb);");
      fprintf(Outfile,"%s\n","  if(retstat != -1)");
      fprintf(Outfile,"%s\n","    return sb.st_size;");
      fprintf(Outfile,"%s\n","  return 0;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Iif)
    {
      fprintf(Outfile,"%s\n","double iif (bool cond, double tp, double fp)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  if(cond) return tp;");
      fprintf(Outfile,"%s\n","  return fp;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_sziif)
    {
      fprintf(Outfile,"%s\n","char * sziif (bool i, char *a, char *b)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  if(i) return a;");
      fprintf(Outfile,"%s\n","  return b;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_DynamicA)
    {
      fprintf(Outfile,"%s\n","void *CreateArr(void *a, int elem_size, int update, int num_dims, ... )");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  va_list ap;");
      fprintf(Outfile,"%s\n","  void   *RetPtr;");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","  va_start(ap, num_dims);");
      fprintf(Outfile,"%s\n","  RetPtr = CreateArr_internal(a, elem_size, update, num_dims, ap);");
      fprintf(Outfile,"%s\n","  va_end(ap);");
      fprintf(Outfile,"%s\n","  return (RetPtr);");
      fprintf(Outfile,"%s\n","}\n\n");
      fprintf(Outfile,"%s\n","void *CreateArr_internal(void *a, int elem_size, int update, int num_dims, va_list ap)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  size_t s, s1, s2;");
      fprintf(Outfile,"%s\n","  void **vp;");
      fprintf(Outfile,"%s\n","  va_list marker;");
      fprintf(Outfile,"%s\n"," ");
      fprintf(Outfile,"%s\n","#ifdef va_copy");
      fprintf(Outfile,"%s\n","  va_copy(marker, ap);");
      fprintf(Outfile,"%s\n","#else");
      fprintf(Outfile,"%s\n","  marker = ap;");
      fprintf(Outfile,"%s\n","#endif");
      fprintf(Outfile,"%s\n","  s = va_arg(marker, size_t);");
      fprintf(Outfile,"%s\n","  s2 = s + 2;");
      fprintf(Outfile,"%s\n","  if(num_dims == 1)");
      fprintf(Outfile,"%s\n","        {");
      fprintf(Outfile,"%s\n","    if(update && a)");
      fprintf(Outfile,"%s\n","        a=realloc(a,s2*elem_size);");
      fprintf(Outfile,"%s\n","     else");
      fprintf(Outfile,"%s\n","        a=calloc(s2,elem_size);");
      fprintf(Outfile,"%s\n","    return a;");
      fprintf(Outfile,"%s\n","   }");
      fprintf(Outfile,"%s\n"," else");
      fprintf(Outfile,"%s\n","    if(update && a)");
      fprintf(Outfile,"%s\n","     {");
      fprintf(Outfile,"%s\n","     s1 = 0;");
      fprintf(Outfile,"%s\n","     vp = (void**)a;");
      fprintf(Outfile,"%s\n","     while(*vp && s1 <= s)");
      fprintf(Outfile,"%s\n","       {");
      fprintf(Outfile,"%s\n","       vp++;");
      fprintf(Outfile,"%s\n","       s1++;");
      fprintf(Outfile,"%s\n","       }");
      fprintf(Outfile,"%s\n","     if(s1 > s)");
      fprintf(Outfile,"%s\n","       {");
      fprintf(Outfile,"%s\n","       vp--;");
      fprintf(Outfile,"%s\n","        DestroyArr(vp, num_dims, 0);");
      fprintf(Outfile,"%s\n","       }");
      fprintf(Outfile,"%s\n","      a=realloc(a,s2*sizeof(int));");
      fprintf(Outfile,"%s\n","     s1 = 0;");
      fprintf(Outfile,"%s\n","     vp = (void**)a;");
      fprintf(Outfile,"%s\n","     while(*vp && s1 <= s)");
      fprintf(Outfile,"%s\n","       {");
      fprintf(Outfile,"%s\n","       vp++;");
      fprintf(Outfile,"%s\n","       s1++;");
      fprintf(Outfile,"%s\n","       }");
      fprintf(Outfile,"%s\n","     while(s1 < s2)");
      fprintf(Outfile,"%s\n","       {");
      fprintf(Outfile,"%s\n","       *(((int *)vp)) = 0;");
      fprintf(Outfile,"%s\n","       vp++;");
      fprintf(Outfile,"%s\n","       s1++;");
      fprintf(Outfile,"%s\n","       }");
      fprintf(Outfile,"%s\n","     }");
      fprintf(Outfile,"%s\n","   else");
      fprintf(Outfile,"%s\n","      a=calloc(s2*sizeof(int),1);");
      fprintf(Outfile,"%s\n"," vp = (void**)a;");
      fprintf(Outfile,"%s\n"," if(--num_dims > 0)");
      fprintf(Outfile,"%s\n"," {");
      fprintf(Outfile,"%s\n"," for(s1 = 0; s1 < s; s1++)");
      fprintf(Outfile,"%s\n","   {");
      fprintf(Outfile,"%s\n","     vp[s1] = CreateArr_internal(vp[s1], elem_size, update, num_dims, marker);");
      fprintf(Outfile,"%s\n","   }");
      fprintf(Outfile,"%s\n"," }");
      fprintf(Outfile,"%s\n"," return a;");
      fprintf(Outfile,"%s\n","}\n\n");
      fprintf(Outfile,"%s\n","void DestroyArr (void** a,int num_dims, int top_free)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n"," int i = 0;");
      fprintf(Outfile,"%s\n"," static int s = 0;");
      fprintf(Outfile,"%s\n"," if(num_dims == 1)");
      fprintf(Outfile,"%s\n","   {");
      fprintf(Outfile,"%s\n","   free(a);");
      fprintf(Outfile,"%s\n","   return;");
      fprintf(Outfile,"%s\n","   }");
      fprintf(Outfile,"%s\n"," s++;");
      fprintf(Outfile,"%s\n"," num_dims--;  ");
      fprintf(Outfile,"%s\n"," while(a[i])");
      fprintf(Outfile,"%s\n","     {");
      fprintf(Outfile,"%s\n","   DestroyArr((void**)a[i], num_dims, top_free);");
      fprintf(Outfile,"%s\n","   if(num_dims > 1)");
      fprintf(Outfile,"%s\n","         free(a[i]);");
      fprintf(Outfile,"%s\n","       a[i++]=NULL;");
      fprintf(Outfile,"%s\n","       }");
      fprintf(Outfile,"%s\n"," s--;");
      fprintf(Outfile,"%s\n"," if(s == 0 && top_free)");
      fprintf(Outfile,"%s\n","   free(a);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Idxqsort)
    {
      fprintf(Outfile,"%s\n","int IdxCompare (const void *one, const void *two)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int *ptr1 = (int *)(one);");
      fprintf(Outfile,"%s\n","  int *ptr2 = (int *)(two);");
      fprintf(Outfile,"%s\n","  return strcasecmp (pppStr[Key][*ptr1],pppStr[Key][*ptr2]);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_IdxqsortSt)
    {
      fprintf(Outfile,"%s\n","int IdxCompareSt (const void* one, const void* two)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","#define compare1 cmp1+(StructSize * (*(UINT *)(one)))");
      fprintf(Outfile,"%s\n","#define compare2 cmp1+(StructSize * (*(UINT *)(two)))");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n"," if (Key==0)");
      fprintf(Outfile,"%s\n","   return  strcasecmp(compare1, compare2);");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n"," if (Key==1)");
      fprintf(Outfile,"%s\n"," {");
      fprintf(Outfile,"%s\n","  if (*(int*)(compare1) < *(int*)(compare2)) return -1;");
      fprintf(Outfile,"%s\n","  if (*(int*)(compare1) > *(int*)(compare2)) return 1;");
      fprintf(Outfile,"%s\n","  return 0;");
      fprintf(Outfile,"%s\n"," }");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n"," if (Key==2)");
      fprintf(Outfile,"%s\n"," {");
      fprintf(Outfile,"%s\n","  if (*(double*)(compare1) < *(double*)(compare2)) return -1;");
      fprintf(Outfile,"%s\n","  if (*(double*)(compare1) > *(double*)(compare2)) return 1;");
      fprintf(Outfile,"%s\n","  return 0;");
      fprintf(Outfile,"%s\n"," }");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n"," if (Key==3)");
      fprintf(Outfile,"%s\n"," {");
      fprintf(Outfile,"%s\n","  if (*(UINT*)(compare1) < *(UINT*)(compare2)) return -1;");
      fprintf(Outfile,"%s\n","  if (*(UINT*)(compare1) > *(UINT*)(compare2)) return 1;");
      fprintf(Outfile,"%s\n"," }");
      fprintf(Outfile,"%s\n","return 0;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_PtrqsortSt)
    {
      fprintf(Outfile,"%s\n","int PtrCompareSt (const void* one, const void* two)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","#define pcompare1 ((char*)(one)+OffSet)");
      fprintf(Outfile,"%s\n","#define pcompare2 ((char*)(two)+OffSet)");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n"," if (Key==0)");
      fprintf(Outfile,"%s\n","   return  strcasecmp(pcompare1, pcompare2);");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n"," if (Key==1)");
      fprintf(Outfile,"%s\n"," {");
      fprintf(Outfile,"%s\n","  if (*(int*)(pcompare1) < *(int*)(pcompare2)) return -1;");
      fprintf(Outfile,"%s\n","  if (*(int*)(pcompare1) > *(int*)(pcompare2)) return 1;");
      fprintf(Outfile,"%s\n","  return 0;");
      fprintf(Outfile,"%s\n"," }");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n"," if (Key==2)");
      fprintf(Outfile,"%s\n"," {");
      fprintf(Outfile,"%s\n","  if (*(double*)(pcompare1) < *(double*)(pcompare2)) return -1;");
      fprintf(Outfile,"%s\n","  if (*(double*)(pcompare1) > *(double*)(pcompare2)) return 1;");
      fprintf(Outfile,"%s\n","  return 0;");
      fprintf(Outfile,"%s\n"," }");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n"," if (Key==3)");
      fprintf(Outfile,"%s\n"," {");
      fprintf(Outfile,"%s\n","  if (*(UINT*)(pcompare1) < *(UINT*)(pcompare2)) return -1;");
      fprintf(Outfile,"%s\n","  if (*(UINT*)(pcompare1) > *(UINT*)(pcompare2)) return 1;");
      fprintf(Outfile,"%s\n"," }");
      fprintf(Outfile,"%s\n","return 0;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Strqsorta)
    {
      fprintf(Outfile,"%s\n","int StrCompareA (const void *arg1, const void *arg2)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *v1 = (char*) arg1;");
      fprintf(Outfile,"%s\n","  char *v2 = (char*) arg2;");
      fprintf(Outfile,"%s\n","  return strcasecmp (v1,v2);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Strqsortd)
    {
      fprintf(Outfile,"%s\n","int StrCompareD (const void *arg1, const void *arg2)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *v1 = (char*) arg1;");
      fprintf(Outfile,"%s\n","  char *v2 = (char*) arg2;");
      fprintf(Outfile,"%s\n","  return strcasecmp (v2,v1);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_DynStrqsorta)
    {
      fprintf(Outfile,"%s\n","int DynStrCompareA (const void *arg1, const void *arg2)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *v1 = *(char **) arg1;");
      fprintf(Outfile,"%s\n","  char *v2 = *(char **) arg2;");
      fprintf(Outfile,"%s\n","  return strcasecmp(v1, v2);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_DynStrqsortd)
    {
      fprintf(Outfile,"%s\n","int DynStrCompareD (const void *arg1, const void *arg2)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *v1 = *(char **) arg1;");
      fprintf(Outfile,"%s\n","  char *v2 = *(char **) arg2;");
      fprintf(Outfile,"%s\n","  return strcasecmp(v2, v1);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Numqsortaint)
    {
      fprintf(Outfile,"%s\n","int NumCompareAint (const void *one, const void *two)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int *ptr1 = (int *)(one);");
      fprintf(Outfile,"%s\n","  int *ptr2 = (int *)(two);");
      fprintf(Outfile,"%s\n","  if (*ptr1 < *ptr2) return -1;");
      fprintf(Outfile,"%s\n","  else if (*ptr1 == *ptr2) return 0;");
      fprintf(Outfile,"%s\n","  else return 1;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Numqsortdint)
    {
      fprintf(Outfile,"%s\n","int NumCompareDint (const void *one, const void *two)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int *ptr1 = (int *)(one);");
      fprintf(Outfile,"%s\n","  int *ptr2 = (int *)(two);");
      fprintf(Outfile,"%s\n","  if (*ptr1 > *ptr2) return -1;");
      fprintf(Outfile,"%s\n","  else if (*ptr1 == *ptr2) return 0;");
      fprintf(Outfile,"%s\n","  else return 1;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Numqsortafloat)
    {
      fprintf(Outfile,"%s\n","int NumCompareAfloat (const void *one, const void *two)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  float *ptr1 = (float *)(one);");
      fprintf(Outfile,"%s\n","  float *ptr2 = (float *)(two);");
      fprintf(Outfile,"%s\n","  if (*ptr1 < *ptr2) return -1;");
      fprintf(Outfile,"%s\n","  else if (*ptr1 == *ptr2) return 0;");
      fprintf(Outfile,"%s\n","  else return 1;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Numqsortdfloat)
    {
      fprintf(Outfile,"%s\n","int NumCompareDfloat (const void *one, const void *two)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  float *ptr1 = (float *)(one);");
      fprintf(Outfile,"%s\n","  float *ptr2 = (float *)(two);");
      fprintf(Outfile,"%s\n","  if (*ptr1 > *ptr2) return -1;");
      fprintf(Outfile,"%s\n","  else if (*ptr1 == *ptr2) return 0;");
      fprintf(Outfile,"%s\n","  else return 1;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Numqsortadouble)
    {
      fprintf(Outfile,"%s\n","int NumCompareAdouble (const void *one, const void *two)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  double *ptr1 = (double *)(one);");
      fprintf(Outfile,"%s\n","  double *ptr2 = (double *)(two);");
      fprintf(Outfile,"%s\n","  if (*ptr1 < *ptr2) return -1;");
      fprintf(Outfile,"%s\n","  else if (*ptr1 == *ptr2) return 0;");
      fprintf(Outfile,"%s\n","  else return 1;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Numqsortddouble)
    {
      fprintf(Outfile,"%s\n","int NumCompareDdouble (const void *one, const void *two)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  double *ptr1 = (double *)(one);");
      fprintf(Outfile,"%s\n","  double *ptr2 = (double *)(two);");
      fprintf(Outfile,"%s\n","  if (*ptr1 > *ptr2) return -1;");
      fprintf(Outfile,"%s\n","  else if (*ptr1 == *ptr2) return 0;");
      fprintf(Outfile,"%s\n","  else return 1;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_FillArray)
    {
      fprintf(Outfile,"%s\n","int fillarray(char *input, int ArrayType, int MaxCnt, void *Array)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n"," if(MaxCnt < 1) return -1;");
      fprintf(Outfile,"%s\n"," int c = 0, cnt=-1, cnt2;");
      fprintf(Outfile,"%s\n"," char A[65535];");
      fprintf(Outfile,"%s\n"," int    *intptr    = (int *)Array;");
      fprintf(Outfile,"%s\n"," float  *floatptr  = (float *)Array;");
      fprintf(Outfile,"%s\n"," double *doubleptr = (double *)Array;");
      fprintf(Outfile,"%s\n"," long double *ldoubleptr = (long double *)Array;");
      fprintf(Outfile,"%s\n"," for(;;)");
      fprintf(Outfile,"%s\n","  {");
      fprintf(Outfile,"%s\n","     cnt2=0;");
      fprintf(Outfile,"%s\n","     while(input[++cnt]!=',')");
      fprintf(Outfile,"%s\n","      {");
      fprintf(Outfile,"%s\n","        if(input[cnt]==0) break;");
      fprintf(Outfile,"%s\n","        A[cnt2++]=input[cnt];");
      fprintf(Outfile,"%s\n","      }");
      fprintf(Outfile,"%s\n","     A[cnt2]=0;");
      fprintf(Outfile,"%s\n","     if(cnt2==0||c==MaxCnt) break;");
      fprintf(Outfile,"%s\n","     ");
      fprintf(Outfile,"%s\n","     if(ArrayType==2)");
      fprintf(Outfile,"%s\n","       intptr[c++] = atoi(A);");
      fprintf(Outfile,"%s\n","     else if(ArrayType==3)");
      fprintf(Outfile,"%s\n","       floatptr[c++] = atof(A);");
      fprintf(Outfile,"%s\n","     else if(ArrayType==4)");
      fprintf(Outfile,"%s\n","       doubleptr[c++] = atof(A);");
      fprintf(Outfile,"%s\n","     else if(ArrayType==5)");
      fprintf(Outfile,"%s\n","       ldoubleptr[c++] = atof(A);");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","     if(input[cnt]==0) break;");
      fprintf(Outfile,"%s\n","  } ");
      fprintf(Outfile,"%s\n"," return (c-1);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Loc)
    {
      fprintf(Outfile,"%s\n","int loc(FILE *fp, int fplen)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  fpos_t t;");
      fprintf(Outfile,"%s\n","  fgetpos(fp, &t);");
      fprintf(Outfile,"%s\n","#if defined( __POCC__ )");
      fprintf(Outfile,"%s\n","  t.off %= fplen;");
      fprintf(Outfile,"%s\n","  return (int)t.off;");
      fprintf(Outfile,"%s\n","#else");
      fprintf(Outfile,"%s\n","  t %= fplen;");
      fprintf(Outfile,"%s\n","  return (int)t;");
      fprintf(Outfile,"%s\n","#endif");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Rec)
    {
      fprintf(Outfile,"%s\n","int rec(FILE *fp, int fplen)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  fpos_t t;");
      fprintf(Outfile,"%s\n","  fgetpos(fp, &t);");
      fprintf(Outfile,"%s\n","#if defined( __POCC__ )");
      fprintf(Outfile,"%s\n","  t.off /= fplen;");
      fprintf(Outfile,"%s\n","  return (int)++t.off;");
      fprintf(Outfile,"%s\n","#else");
      fprintf(Outfile,"%s\n","  t /= fplen;");
      fprintf(Outfile,"%s\n","  return (int)++t;");
      fprintf(Outfile,"%s\n","#endif");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_RecCount)
    {
      fprintf(Outfile,"%s\n","int reccount(FILE *fp, int fplen)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  fpos_t t;");
      fprintf(Outfile,"%s\n","  fseek(fp,0,SEEK_END);");
      fprintf(Outfile,"%s\n","  fgetpos(fp, &t);");
      fprintf(Outfile,"%s\n","#if defined( __POCC__ )");
      fprintf(Outfile,"%s\n","  t.off /= fplen;");
      fprintf(Outfile,"%s\n","  return (int)t.off;");
      fprintf(Outfile,"%s\n","#else");
      fprintf(Outfile,"%s\n","  t /= fplen;");
      fprintf(Outfile,"%s\n","  return (int)t;");
      fprintf(Outfile,"%s\n","#endif");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Scan)
    {
      fprintf(Outfile,"%s\n","int scan(char *input, char *format, ... )");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int c,d ;");
      fprintf(Outfile,"%s\n","  char     *s_;");
      fprintf(Outfile,"%s\n","  int      *intptr;");
      fprintf(Outfile,"%s\n","  float    *floatptr;");
      fprintf(Outfile,"%s\n","  double   *doubleptr;");
      fprintf(Outfile,"%s\n","  char     A[50][65535];");
      fprintf(Outfile,"%s\n","  va_list  marker;");
      fprintf(Outfile,"%s\n","  c = 0;");
      fprintf(Outfile,"%s%s%s\n","  d = Split(A,input,",enc(","),");");
      fprintf(Outfile,"%s\n","  va_start(marker, format); //Initialize arguments");
      fprintf(Outfile,"%s\n","  while(d && *format)");
      fprintf(Outfile,"%s\n","   {");
      fprintf(Outfile,"%s\n","     if(*format == '%') format++;");
      fprintf(Outfile,"%s\n","     if(*format == 's')");
      fprintf(Outfile,"%s\n","       {");
      fprintf(Outfile,"%s\n","         s_ = va_arg(marker, char *);");
      fprintf(Outfile,"%s\n","         strcpy(s_, A[c]);");
      fprintf(Outfile,"%s\n","         c++;");
      fprintf(Outfile,"%s\n","         d--;");
      fprintf(Outfile,"%s\n","       }");
      fprintf(Outfile,"%s\n","  if(*format == 'd')");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      intptr = va_arg(marker, int *);");
      fprintf(Outfile,"%s\n","      *intptr = atoi(A[c]);");
      fprintf(Outfile,"%s\n","      c++;");
      fprintf(Outfile,"%s\n","      d--;");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  if(*format == 'g')");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      floatptr = va_arg(marker, float *);");
      fprintf(Outfile,"%s\n","      *floatptr = atof(A[c]);");
      fprintf(Outfile,"%s\n","      c++;");
      fprintf(Outfile,"%s\n","      d--;");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n"," if(*format == 'l')");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      format++;");
      fprintf(Outfile,"%s\n","      doubleptr = va_arg(marker, double *);");
      fprintf(Outfile,"%s\n","      *doubleptr = atof(A[c]);");
      fprintf(Outfile,"%s\n","      c++;");
      fprintf(Outfile,"%s\n","      d--;");
      fprintf(Outfile,"%s\n","     }");
      fprintf(Outfile,"%s\n","  format++;");
      fprintf(Outfile,"%s\n","   }");
      fprintf(Outfile,"%s\n","  va_end(marker);              // Reset variable arguments");
      fprintf(Outfile,"%s\n","  if(d) return(1);             // More data than variables");
      fprintf(Outfile,"%s\n","  if(*format == 0) return(0);  // OK");
      fprintf(Outfile,"%s\n","  return(-1);                  // More variables than data");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Split)
    {
      fprintf(Outfile,"%s\n","int Split (char Buf[][65535], char *T, char *Delim, int Flg)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int  Begin = 0;");
      fprintf(Outfile,"%s\n","  int  Count = 0;");
      fprintf(Outfile,"%s\n","  int  Quote = 0;");
      fprintf(Outfile,"%s\n","  int  Index,i;");
      fprintf(Outfile,"%s\n","  int  lenT  = strlen(T);");
      fprintf(Outfile,"%s\n","  char Chr34[2]={34,0};");
      fprintf(Outfile,"%s\n","  for(Index=1;Index<=lenT;Index++)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      if(instr_b(Delim,mid(T,Index,1))&&!Quote)");
      fprintf(Outfile,"%s\n","        {");
      fprintf(Outfile,"%s\n","          strcpy(Buf[Count],(char*)mid(T,Begin,Index-Begin));");
      fprintf(Outfile,"%s\n","          if ((Flg & 2) == 0)  // 0 if old version");
      fprintf(Outfile,"%s\n","           Count++;");
      fprintf(Outfile,"%s\n","          else");
      fprintf(Outfile,"%s\n","           if (Buf[Count][0] != 0) Count++;");
      fprintf(Outfile,"%s\n","           Begin=0;");
      fprintf(Outfile,"%s\n","           if((Flg & 1) == 1)   // 1 if true");
      fprintf(Outfile,"%s\n","              strcpy(Buf[Count++],(char*)mid(T,Index,1));");
      fprintf(Outfile,"%s\n","        }");
      fprintf(Outfile,"%s\n","   else");
      fprintf(Outfile,"%s\n","     {");
      fprintf(Outfile,"%s\n","       if(strcmp(mid(T,Index,1),Chr34)==0) Quote=!Quote;");
      fprintf(Outfile,"%s\n","       if(Begin==0) Begin=Index;");
      fprintf(Outfile,"%s\n","     }");
      fprintf(Outfile,"%s\n","   }");
      fprintf(Outfile,"%s\n","  if(Begin)");
      fprintf(Outfile,"%s\n","     strcpy(Buf[Count++],(char*)mid(T,Begin,Index-Begin));");
      fprintf(Outfile,"%s\n","  if((Flg & 1) == 0)   // 0 if false");
      fprintf(Outfile,"%s\n","      for(i=0;i<Count;i++) strcpy(Buf[i],(char*)RemoveStr(Buf[i],Chr34));");
      fprintf(Outfile,"%s\n","  return Count;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_DSplit)
    {
      fprintf(Outfile,"%s\n","int DSplit (PCHAR *Buf, char *T, char *Delim, int Flg)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int  Begin=0;");
      fprintf(Outfile,"%s\n","  int  Count=0;");
      fprintf(Outfile,"%s\n","  int  Quote=0;");
      fprintf(Outfile,"%s\n","  int  Index=0;");
      fprintf(Outfile,"%s\n","  int  lenT  = strlen(T);");
      fprintf(Outfile,"%s\n","  char Chr34[2]={34,0};");
      fprintf(Outfile,"%s\n","  for(Index=1;Index<=lenT;Index++)");
      fprintf(Outfile,"%s\n","   {");
      fprintf(Outfile,"%s\n","     if(instr_b(Delim,mid(T,Index,1))&&!Quote)");
      fprintf(Outfile,"%s\n","       {");
      fprintf(Outfile,"%s\n","         strcpy(Buf[Count],(char*)mid(T,Begin,Index-Begin));");
      fprintf(Outfile,"%s\n","         if ((Flg & 2) == 0)  // 0 if old version");
      fprintf(Outfile,"%s\n","         Count++;");
      fprintf(Outfile,"%s\n","     else");
      fprintf(Outfile,"%s\n","         if (Buf[Count][0] != 0) Count++;");
      fprintf(Outfile,"%s\n","         Begin=0;");
      fprintf(Outfile,"%s\n","         if((Flg & 1) == 1)   // 1 if true");
      fprintf(Outfile,"%s\n","             strcpy(Buf[Count++],(char*)mid(T,Index,1));");
      fprintf(Outfile,"%s\n","       }");
      fprintf(Outfile,"%s\n","    else");
      fprintf(Outfile,"%s\n","      {");
      fprintf(Outfile,"%s\n","        if(strcmp(mid(T,Index,1),Chr34)==0) Quote=!Quote;");
      fprintf(Outfile,"%s\n","        if(Begin==0)  Begin=Index;");
      fprintf(Outfile,"%s\n","      }");
      fprintf(Outfile,"%s\n","   }");
      fprintf(Outfile,"%s\n","  if(Begin) strcpy(Buf[Count++],(char*)mid(T,Begin,Index-Begin));");
      fprintf(Outfile,"%s\n","  if((Flg & 1) == 0)   // 0 if false");
      fprintf(Outfile,"%s\n","     for(Index=0;Index<Count;Index++) strcpy(Buf[Index],(char*)RemoveStr(Buf[Index],Chr34));");
      fprintf(Outfile,"%s\n","  return Count;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Bin2dec)
    {
      fprintf(Outfile,"%s\n","int Bin2Dec (char *cptr)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int i, j = 0;");
      fprintf(Outfile,"%s%s%s\n","  while(cptr && *cptr && strchr(",enc("01"),", *cptr))");
      fprintf(Outfile,"%s\n","  {");
      fprintf(Outfile,"%s\n","    i = *cptr++ - '0';");
      fprintf(Outfile,"%s\n","    j <<= 1;");
      fprintf(Outfile,"%s\n","    j |= (i & 0x01);");
      fprintf(Outfile,"%s\n","  }");
      fprintf(Outfile,"%s\n"," return(j);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Hex2Dec)
    {
      fprintf(Outfile,"%s\n","int Hex2Dec (char *szInput)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char   ch;");
      fprintf(Outfile,"%s\n","  char  *dwLen   = szInput+strlen(szInput);");
      fprintf(Outfile,"%s\n","  char  *LowCase = MakeLCaseTbl();");
      fprintf(Outfile,"%s\n","  DWORD  dwOut   = 0;");
      fprintf(Outfile,"%s\n","  while(*szInput)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      ch = LowCase[(unsigned char)*szInput++];");
      fprintf(Outfile,"%s\n","      if((ch >= 'a' && ch <= 'f')  || (ch >= '0' && ch <= '9'))");
      fprintf(Outfile,"%s\n","        dwOut |=((int)ch - (ch>'9' ? 'a'-10 : '0')) << ((dwLen - szInput) << 2);");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  return dwOut;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Verify)
    {
      fprintf(Outfile,"%s\n","int Verify (char *Src, char *Allowed)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int i, j;");
      fprintf(Outfile,"%s\n","  for (i=1; i<=strlen(Src); i++)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      j=VerifyInstr(Allowed,mid(Src,i,1));");
      fprintf(Outfile,"%s\n","      if (!j) return 0;");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  return TRUE;");
      fprintf(Outfile,"%s\n","}\n\n");
      fprintf(Outfile,"%s\n","int VerifyInstr(char* mane,char* match,int offset)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *s;");
      fprintf(Outfile,"%s\n","  if (!mane || !match || !*match || offset>(int)strlen(mane)) return 0;");
      fprintf(Outfile,"%s\n","  s = strstr (offset>0 ? mane+offset-1 : mane,match);");
      fprintf(Outfile,"%s\n","  return s ? (int)(s-mane)+1 : 0;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Retain)
    {
      fprintf(Outfile,"%s\n","char *Retain (char *Text, char *ValidChars)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *BCX_RetStr=BCX_TmpStr(strlen(Text));");
      fprintf(Outfile,"%s\n","  char *temp=BCX_RetStr;");
      fprintf(Outfile,"%s\n","  while(*Text)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      if(strchr(ValidChars,*Text)) *(temp++) = *Text;");
      fprintf(Outfile,"%s\n","      Text++;");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  return BCX_RetStr;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_LoadFile)
    {
      fprintf(Outfile,"%s\n","char* LoadFile (char *N)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  FILE* FP1;");
      fprintf(Outfile,"%s\n","  char* BCX_RetStr;");
      fprintf(Outfile,"%s\n","  if(Exist(N))");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      BCX_RetStr=BCX_TmpStr(lof(N));");
      fprintf(Outfile,"%s%s%s\n","      if((FP1=fopen(N,",enc("rb"),"))!=0)");
      fprintf(Outfile,"%s\n","      GET(FP1,BCX_RetStr,lof(N));");
      fprintf(Outfile,"%s\n","      fclose(FP1);");
      fprintf(Outfile,"%s\n","      return BCX_RetStr;");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  else");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      BCX_RetStr=BCX_TmpStr(64);");
      fprintf(Outfile,"%s%s%s\n","      return strcpy(BCX_RetStr,",enc("File Not Found"),");");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Freefile)
    {
      fprintf(Outfile,"%s\n","FILE* FreeFile (void)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  static FILE *pf;");
      fprintf(Outfile,"%s\n","  if(pf){free(pf);pf=NULL;}");
      fprintf(Outfile,"%s\n","  pf = (FILE*)calloc(sizeof(FILE*),sizeof(FILE*));");
      fprintf(Outfile,"%s\n","  return pf;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Run)
    {
      fprintf(Outfile,"%s\n","int Run (char* Cmdline, int ShowHide, int WaitState)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","   int    processId;");
      fprintf(Outfile,"%s\n","   char  *s, *p, *cmd_line;");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","  cmd_line=(char*)malloc(strlen(Cmdline)+1);");
      fprintf(Outfile,"%s\n","  if(cmd_line==NULL) return -2;");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","  strcpy(cmd_line, Cmdline);");
      fprintf(Outfile,"%s\n","  p = s = cmd_line;");
      fprintf(Outfile,"%s\n","  processId=fork();");
      fprintf(Outfile,"%s\n","  if(processId==0)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      PCHAR  argv[30];");
      fprintf(Outfile,"%s\n","      int     i=0;");
      fprintf(Outfile,"%s\n","      while(*p)");
      fprintf(Outfile,"%s\n","        {");
      fprintf(Outfile,"%s\n","          if(*p==34)");
      fprintf(Outfile,"%s\n","            {");
      fprintf(Outfile,"%s\n","              while(*(++p)!=34) {}");
      fprintf(Outfile,"%s\n","            }");
      fprintf(Outfile,"%s\n","          if(*p==32)");
      fprintf(Outfile,"%s\n","            {");
      fprintf(Outfile,"%s\n","              while(*(p+1)==32) p++;");
      fprintf(Outfile,"%s\n","              argv[i++]=s;");
      fprintf(Outfile,"%s\n","              *p=0; s=p+1;");
      fprintf(Outfile,"%s\n","            }");
      fprintf(Outfile,"%s\n","          p++;");
      fprintf(Outfile,"%s\n","        }");
      fprintf(Outfile,"%s\n","      argv[i]  = s;");
      fprintf(Outfile,"%s\n","      argv[i+1]= 0;");
      fprintf(Outfile,"%s\n","      execvp(argv[0],argv);");
      fprintf(Outfile,"%s%s%s\n","      printf(",enc("Failed to run%s\\n"),",argv[0]);");
      fprintf(Outfile,"%s\n","      exit(-1);");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  else if(processId!=-1)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      if(WaitState) waitpid(processId,NULL,0);");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  waitpid(-1,NULL,WNOHANG);");
      fprintf(Outfile,"%s\n","  free(cmd_line), cmd_line=NULL;");
      fprintf(Outfile,"%s\n","  return processId;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Download)
    {
      fprintf(Outfile,"%s\n","int Download (char *URL,char *Localname)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int RetVal;");
      fprintf(Outfile,"%s\n","  return RetVal=!RetVal;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_PeekStr)
    {
      fprintf(Outfile,"%s\n","char *peekstr (LPVOID Src, int Count)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *Des=BCX_TmpStr(Count);");
      fprintf(Outfile,"%s\n","  memmove(Des,Src,Count);");
      fprintf(Outfile,"%s\n","  return Des;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_QBColor)
    {
      fprintf(Outfile,"%s\n","int qbcolor (int N)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n"," switch (N)");
      fprintf(Outfile,"%s\n"," {");
      fprintf(Outfile,"%s\n"," case  0 : return RGB(0,0,0);");
      fprintf(Outfile,"%s\n"," case  1 : return RGB(0,0,128);");
      fprintf(Outfile,"%s\n"," case  2 : return RGB(0,128,0);");
      fprintf(Outfile,"%s\n"," case  3 : return RGB(0,128,128);");
      fprintf(Outfile,"%s\n"," case  4 : return RGB(196,0,0);");
      fprintf(Outfile,"%s\n"," case  5 : return RGB(128,0,128);");
      fprintf(Outfile,"%s\n"," case  6 : return RGB(128,64,0);");
      fprintf(Outfile,"%s\n"," case  7 : return RGB(196,196,196);");
      fprintf(Outfile,"%s\n"," case  8 : return RGB(128,128,128);");
      fprintf(Outfile,"%s\n"," case  9 : return RGB(0,0, 255);");
      fprintf(Outfile,"%s\n"," case 10 : return RGB(0,255,0);");
      fprintf(Outfile,"%s\n"," case 11 : return RGB(0,255,255);");
      fprintf(Outfile,"%s\n"," case 12 : return RGB(255,0,0);");
      fprintf(Outfile,"%s\n"," case 13 : return RGB(255,0,255);");
      fprintf(Outfile,"%s\n"," case 14 : return RGB(255,255,0);");
      fprintf(Outfile,"%s\n"," case 15 : return RGB(255,255,255);");
      fprintf(Outfile,"%s\n"," case 16 : return RGB(164,164,164);");
      fprintf(Outfile,"%s\n"," case 17 : return RGB(128,160,255);");
      fprintf(Outfile,"%s\n"," case 18 : return RGB(160,255,160);");
      fprintf(Outfile,"%s\n"," case 19 : return RGB(160,255,255);");
      fprintf(Outfile,"%s\n"," case 20 : return RGB(255,160,160);");
      fprintf(Outfile,"%s\n"," case 21 : return RGB(255,160,255);");
      fprintf(Outfile,"%s\n"," case 22 : return RGB(255,255,160);");
      fprintf(Outfile,"%s\n"," case 23 : return RGB(212,212,212);");
      fprintf(Outfile,"%s\n"," case 24 : return RGB(180,180,180);");
      fprintf(Outfile,"%s\n"," case 25 : return RGB(188,220,255);");
      fprintf(Outfile,"%s\n"," case 26 : return RGB(220,255,220);");
      fprintf(Outfile,"%s\n"," case 27 : return RGB(220,255,255);");
      fprintf(Outfile,"%s\n"," case 28 : return RGB(255,220,220);");
      fprintf(Outfile,"%s\n"," case 29 : return RGB(255,220,255);");
      fprintf(Outfile,"%s\n"," case 30 : return RGB(255,255,220);");
      fprintf(Outfile,"%s\n"," case 31 : return RGB(228,228,228);");
      fprintf(Outfile,"%s\n"," }");
      fprintf(Outfile,"%s\n","return 0;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Cvi)
    {
      fprintf(Outfile,"%s\n","short CVI (char *s)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n"," return ((short*)s)[0];");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Mki)
    {
      fprintf(Outfile,"%s\n","char *MKI (short cvt)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  static char temp[3];");
      fprintf(Outfile,"%s\n","  return (char *)memmove(temp,&cvt,2);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Cvl)
    {
      fprintf(Outfile,"%s\n","long CVL (char *s)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n"," return ((long*)s)[0];");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Mkl)
    {
      fprintf(Outfile,"%s\n","char *MKL (int cvt)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  static char temp[5];");
      fprintf(Outfile,"%s\n","  return (char *) memmove(temp,&cvt,4);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Cvs)
    {
      fprintf(Outfile,"%s\n","float CVS (char *s)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n"," return ((float*)s)[0];");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Mks)
    {
      fprintf(Outfile,"%s\n","char *MKS (float cvt)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  static char temp[5];");
      fprintf(Outfile,"%s\n","  return (char *) memmove(temp,&cvt,4);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Cvd)
    {
      fprintf(Outfile,"%s\n","double CVD (char *s)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n"," return ((double*)s)[0];");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Cvld)
    {
      fprintf(Outfile,"%s\n","long double CVLD (char *s)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n"," return ((long double*)s)[0];");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Mkd)
    {
      fprintf(Outfile,"%s\n","char *MKD (double cvt)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  static char temp[9];");
      fprintf(Outfile,"%s\n","  return (char *) memmove(temp,&cvt,8);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Mkld)
    {
      fprintf(Outfile,"%s\n","char *MKLD (long double cvt)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  static char temp[11];");
      fprintf(Outfile,"%s\n","  return (char *) memmove(temp,&cvt,10);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_BcxSplitPath)
    {
      fprintf(Outfile,"%s\n","char *BcxSplitPath (char *FPath, int mask)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  if(!FPath) return BCX_TmpStr(1);");
      fprintf(Outfile,"%s\n","  char *BCX_RetStr=BCX_TmpStr(strlen(FPath));");
      fprintf(Outfile,"%s\n","  char tmp[MAX_PATH*4];");
      fprintf(Outfile,"%s\n","  _splitpath_(FPath,tmp,&tmp[MAX_PATH],&tmp[MAX_PATH*2],&tmp[MAX_PATH*3]);");
      fprintf(Outfile,"%s\n","  if(mask & FDRV) strcat(BCX_RetStr,tmp);");
      fprintf(Outfile,"%s\n","  if(mask & FPATH)strcat(BCX_RetStr,&tmp[MAX_PATH]);");
      fprintf(Outfile,"%s\n","  if(mask & FNAME)strcat(BCX_RetStr,&tmp[MAX_PATH*2]);");
      fprintf(Outfile,"%s\n","  if(mask & FEXT) strcat(BCX_RetStr,&tmp[MAX_PATH*3]);");
      fprintf(Outfile,"%s\n","  return BCX_RetStr;");
      fprintf(Outfile,"%s\n","}\n\n");
      fprintf(Outfile,"%s\n"," void _splitpath_(const char* path, char* drv, char* dir, char* name, char* ext)");
      fprintf(Outfile,"%s\n"," {");
      fprintf(Outfile,"%s\n","     const char* pend; /* end of processed string */");
      fprintf(Outfile,"%s\n","     const char* p;   /* search pointer */");
      fprintf(Outfile,"%s\n","     const char* s;   /* copy pointer */");
      fprintf(Outfile,"%s\n"," ");
      fprintf(Outfile,"%s\n","     /* extract drive name */");
      fprintf(Outfile,"%s\n","     if (path[0] && path[1]==':') {");
      fprintf(Outfile,"%s\n","         if (drv) {");
      fprintf(Outfile,"%s\n","             *drv++ = *path++;");
      fprintf(Outfile,"%s\n","             *drv++ = *path++;");
      fprintf(Outfile,"%s\n","             *drv = 0;");
      fprintf(Outfile,"%s\n","         }");
      fprintf(Outfile,"%s\n","     } else if (drv)");
      fprintf(Outfile,"%s\n","         *drv = 0;");
      fprintf(Outfile,"%s\n"," ");
      fprintf(Outfile,"%s\n","     /* search for end of string or stream separator */");
      fprintf(Outfile,"%s\n","     for(pend=path; *pend && *pend!=':'; )");
      fprintf(Outfile,"%s\n","         pend++;");
      fprintf(Outfile,"%s\n"," ");
      fprintf(Outfile,"%s\n","     /* search for begin of file extension */");
      fprintf(Outfile,"%s\n","     for(p=pend; p > path && *--p != '\\\\' && *p!='/'; )");
      fprintf(Outfile,"%s\n","         if (*p == '.') {");
      fprintf(Outfile,"%s\n","             pend = p;");
      fprintf(Outfile,"%s\n","             break;");
      fprintf(Outfile,"%s\n","         }");
      fprintf(Outfile,"%s\n"," ");
      fprintf(Outfile,"%s\n","     if (ext)");
      fprintf(Outfile,"%s\n","     {");
      fprintf(Outfile,"%s\n","         s=pend;");
      fprintf(Outfile,"%s\n","         do{ *ext++ = *s; } while(*s++);");
      fprintf(Outfile,"%s\n","     }");
      fprintf(Outfile,"%s\n","     /* search for end of directory name */");
      fprintf(Outfile,"%s\n","     for(p=pend; p > path; )");
      fprintf(Outfile,"%s\n","         if (*--p == '\\\\' || *p == '/') {");
      fprintf(Outfile,"%s\n","             p++;");
      fprintf(Outfile,"%s\n","             break;");
      fprintf(Outfile,"%s\n","         }");
      fprintf(Outfile,"%s\n"," ");
      fprintf(Outfile,"%s\n","     if (name) {");
      fprintf(Outfile,"%s\n","         for(s=p; s<pend; )");
      fprintf(Outfile,"%s\n","             *name++ = *s++;");
      fprintf(Outfile,"%s\n"," ");
      fprintf(Outfile,"%s\n","         *name = 0;");
      fprintf(Outfile,"%s\n","     }");
      fprintf(Outfile,"%s\n"," ");
      fprintf(Outfile,"%s\n","     if (dir) {");
      fprintf(Outfile,"%s\n","         for(s=path; s<p; )");
      fprintf(Outfile,"%s\n","             *dir++ = *s++;");
      fprintf(Outfile,"%s\n"," ");
      fprintf(Outfile,"%s\n","         *dir = 0;");
      fprintf(Outfile,"%s\n","     }");
      fprintf(Outfile,"%s\n"," }\n");
    }
  if(Use_StrUpLow)
    {
      fprintf(Outfile,"%s\n","char *_strupr_(char *string)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","   char *s;");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","   if (string)");
      fprintf(Outfile,"%s\n","   {");
      fprintf(Outfile,"%s\n","      for(s = string; *s; ++s)");
      fprintf(Outfile,"%s\n","         *s = toupper(*s);");
      fprintf(Outfile,"%s\n","   }");
      fprintf(Outfile,"%s\n","   return string;");
      fprintf(Outfile,"%s\n","}\n");
      fprintf(Outfile,"%s\n","char *_strlwr_(char *string)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","    char *s;");
      fprintf(Outfile,"%s\n","");
      fprintf(Outfile,"%s\n","    if (string)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","       for (s = string; *s; ++s)");
      fprintf(Outfile,"%s\n","           *s = tolower(*s);");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","    return string;");
      fprintf(Outfile,"%s\n","}\n");
    }
  if(Use_Strtoken)
    {
      fprintf(Outfile,"%s\n","char * StrToken (char *Source, char *TokenChar, int n)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *BCX_RetStr={0};");
      fprintf(Outfile,"%s\n","  char *RetVal;");
      fprintf(Outfile,"%s\n","  char *Copy;");
      fprintf(Outfile,"%s\n","  int   Posn=0;");
      fprintf(Outfile,"%s\n","  int   Find=0;");
      fprintf(Outfile,"%s\n","  int   LenSrc=strlen(Source);");
      fprintf(Outfile,"%s\n","  RetVal=(char*)calloc(LenSrc+1,1);");
      fprintf(Outfile,"%s\n","  Copy=Source;");
      fprintf(Outfile,"%s\n","  if(tally(Source,TokenChar)==0)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      BCX_RetStr=BCX_TmpStr(1);");
      fprintf(Outfile,"%s\n","      if(RetVal)free(RetVal);");
      fprintf(Outfile,"%s\n","      return BCX_RetStr;");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  if(n==1)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      BCX_RetStr=BCX_TmpStr(LenSrc);");
      fprintf(Outfile,"%s\n","      strcpy(BCX_RetStr,(char*)extract(Source,TokenChar));");
      fprintf(Outfile,"%s\n","      if(RetVal)free(RetVal);");
      fprintf(Outfile,"%s\n","      return BCX_RetStr;");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  if(n>tally(Source,TokenChar)+1)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      BCX_RetStr=BCX_TmpStr(1);");
      fprintf(Outfile,"%s\n","      if(RetVal)free(RetVal);");
      fprintf(Outfile,"%s\n","      return BCX_RetStr;");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  while(*Copy)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      if(*Copy==TokenChar[0]) Find++;");
      fprintf(Outfile,"%s\n","      if(Find==n) break;");
      fprintf(Outfile,"%s\n","      Copy++;");
      fprintf(Outfile,"%s\n","      Posn++;");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  if(n==tally(Source,TokenChar)+1)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      Posn=LenSrc;");
      fprintf(Outfile,"%s\n","      Copy=Source+Posn;");
      fprintf(Outfile,"%s\n","      while(*Copy&&Source[Posn]!=TokenChar[0])");
      fprintf(Outfile,"%s\n","        {");
      fprintf(Outfile,"%s\n","          Posn--;");
      fprintf(Outfile,"%s\n","          Copy--;");
      fprintf(Outfile,"%s\n","        }");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  strcpy(RetVal,(char*)mid(Source,1,Posn));");
      fprintf(Outfile,"%s\n","  strcpy(RetVal,(char*)mid(RetVal,InstrRev(RetVal,TokenChar)));");
      fprintf(Outfile,"%s\n","  BCX_RetStr=BCX_TmpStr(LenSrc);");
      fprintf(Outfile,"%s\n","  strcpy(BCX_RetStr,(char*)RemoveStr(RetVal,TokenChar));");
      fprintf(Outfile,"%s\n","  if(RetVal)free(RetVal);");
      fprintf(Outfile,"%s\n","  return BCX_RetStr;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_iReplace)
    {
      fprintf(Outfile,"%s\n","char *iReplace (char *src, char *pat, char *rep)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  size_t patsz, repsz, tmpsz, delta;");
      fprintf(Outfile,"%s\n","  char *strtmp, *p, *q, *r;");
      fprintf(Outfile,"%s\n","  if (!pat || !*pat)");
      fprintf(Outfile,"%s\n","   {");
      fprintf(Outfile,"%s\n","     strtmp = BCX_TmpStr(strlen(src));");
      fprintf(Outfile,"%s\n","     if (!strtmp) return NULL;");
      fprintf(Outfile,"%s\n","     return strcpy(strtmp, src);");
      fprintf(Outfile,"%s\n","   }");
      fprintf(Outfile,"%s\n","  repsz = strlen(rep);");
      fprintf(Outfile,"%s\n","  patsz = strlen(pat);");
      fprintf(Outfile,"%s\n","  for (tmpsz=0, p=src;(q=_stristr_(p,pat))!=0; p=q+patsz)");
      fprintf(Outfile,"%s\n","    tmpsz += (size_t) (q - p) + repsz;");
      fprintf(Outfile,"%s\n","    tmpsz += strlen(p);");
      fprintf(Outfile,"%s\n","    strtmp = BCX_TmpStr(tmpsz);");
      fprintf(Outfile,"%s\n","    if (!strtmp) return NULL;");
      fprintf(Outfile,"%s\n","    for (r=strtmp,p=src;(q=_stristr_(p,pat))!=0;p=q+patsz)");
      fprintf(Outfile,"%s\n","     {");
      fprintf(Outfile,"%s\n","       delta = (size_t) (q-p);");
      fprintf(Outfile,"%s\n","       memcpy(r,p,delta); r += delta;");
      fprintf(Outfile,"%s\n","       strcpy(r,rep);      r += repsz;");
      fprintf(Outfile,"%s\n","     }");
      fprintf(Outfile,"%s\n","  strcpy(r,p);");
      fprintf(Outfile,"%s\n","  return strtmp;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_WideToAnsi)
    {
      fprintf(Outfile,"%s\n","char* WideToAnsi (wchar_t *WideStr, UINT CodePage,DWORD dwFlags)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  char *BCX_RetStr={0};");
      fprintf(Outfile,"%s\n","  UINT uLen;");
      fprintf(Outfile,"%s\n","  uLen=wcstombs(NULL, WideStr, 0); //WideCharToMultiByte(CodePage,dwFlags,WideStr,-1,0,0,0,0);");
      fprintf(Outfile,"%s\n","  BCX_RetStr=(char*)BCX_TmpStr(uLen);");
      fprintf(Outfile,"%s\n","  wcstombs(BCX_RetStr, WideStr, uLen); //WideCharToMultiByte(CodePage,dwFlags,WideStr,-1,BCX_RetStr,uLen,0,0);");
      fprintf(Outfile,"%s\n","  return BCX_RetStr;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_SysStr)
    {
      fprintf(Outfile,"%s\n","BSTR SysStr (char * szIn, int widstr, int bfree)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  static  BSTR  bStr[32];");
      fprintf(Outfile,"%s\n","  static  int   index;");
      fprintf(Outfile,"%s\n","  if(bfree)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      for(index=0; index<32; index+=1) ");
      fprintf(Outfile,"%s\n","        SysFreeString(bStr[index]);");
      fprintf(Outfile,"%s\n","      return 0;");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  index=(++index & 31);");
      fprintf(Outfile,"%s\n","  SysFreeString(bStr[index]);");
      fprintf(Outfile,"%s\n","  int   length=strlen(szIn);");
      fprintf(Outfile,"%s\n","  if(widstr)");
      fprintf(Outfile,"%s\n","   {");
      fprintf(Outfile,"%s\n","     bStr[index]=SysAllocStringLen(NULL, (2*length));");
      fprintf(Outfile,"%s\n","     MultiByteToWideChar(CP_ACP,0,szIn,-1,bStr[index],(2*length+1));");
      fprintf(Outfile,"%s\n","   }else{");
      fprintf(Outfile,"%s\n","     bStr[index]=SysAllocStringByteLen(szIn, length);");
      fprintf(Outfile,"%s\n","   }");
      fprintf(Outfile,"%s\n","  return bStr[index];");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_AnsiToWide)
    {
      fprintf(Outfile,"%s\n","wchar_t *AnsiToWide (char *AnsiStr, UINT CodePage,DWORD dwFlags)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  UINT uLen;");
      fprintf(Outfile,"%s\n","  wchar_t *WideStr;");
      fprintf(Outfile,"%s\n","  uLen=mbstowcs(NULL, AnsiStr, 0); //MultiByteToWideChar(CodePage,dwFlags,AnsiStr,-1,0,0);");
      fprintf(Outfile,"%s\n","  if(uLen<=1) return (wchar_t*)BCX_TmpStr(2);");
      fprintf(Outfile,"%s\n","  WideStr = (wchar_t*)BCX_TmpStr(2*uLen);");
      fprintf(Outfile,"%s\n","  mbstowcs(WideStr, AnsiStr, uLen); //MultiByteToWideChar(CodePage,dwFlags,AnsiStr,uLen,WideStr,uLen);");
      fprintf(Outfile,"%s\n","  return WideStr;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_FileLocked)
    {
      fprintf(Outfile,"%s\n","int FileLocked (char *Filename)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s%s%s\n","  FILE *FP=fopen(Filename,",enc("rb+"),");");
      fprintf(Outfile,"%s\n","  if(FP==0) return 1;");
      fprintf(Outfile,"%s\n","  fclose(FP);");
      fprintf(Outfile,"%s\n","  return 0;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_ContainedIn)
    {
      fprintf(Outfile,"%s\n","int containedin(char * Token,char **Contain ,int c)");
      fprintf(Outfile,"%s\n","  {");
      fprintf(Outfile,"%s\n","    int i=0;");
      fprintf(Outfile,"%s\n","    while(Contain[i][0])");
      fprintf(Outfile,"%s\n","      {");
      fprintf(Outfile,"%s\n","        if(0 == ((c == 0 || c == 2) ? strcmp(Contain[i],Token) : strcasecmp(Contain[i],Token)))");
      fprintf(Outfile,"%s\n","          {");
      fprintf(Outfile,"%s\n","            return ((c < 2) ? 0 : i);");
      fprintf(Outfile,"%s\n","          }");
      fprintf(Outfile,"%s\n","        i++;");
      fprintf(Outfile,"%s\n","      }");
      fprintf(Outfile,"%s\n","    return -1;");
      fprintf(Outfile,"%s\n","  }\n\n");
    }
  if(Use_FindInType)
    {
      fprintf(Outfile,"%s\n","int FindInType(char *Token,char *StOffset,int StSize,int start,int finish,int c,int *idx)");
      fprintf(Outfile,"%s\n","  {");
      fprintf(Outfile,"%s\n","    int j;");
      fprintf(Outfile,"%s\n","    char *Srch;");
      fprintf(Outfile,"%s\n","    int (*cmp)(const char*,const char*);");
      fprintf(Outfile,"%s\n","    cmp = ((c == 0 || c == 2) ? strcmp : strcasecmp);");
      fprintf(Outfile,"%s\n","    for(j=start; j<=finish; j++)");
      fprintf(Outfile,"%s\n","      {");
      fprintf(Outfile,"%s\n","        Srch = StOffset + ((idx==0) ? j*StSize : idx[j]*StSize);");
      fprintf(Outfile,"%s\n","        if(cmp(Srch,Token)==0)");
      fprintf(Outfile,"%s\n","          {");
      fprintf(Outfile,"%s\n","            return ((c < 2) ? 0 : j);");
      fprintf(Outfile,"%s\n","          }");
      fprintf(Outfile,"%s\n","      }");
      fprintf(Outfile,"%s\n","    return -1;");
      fprintf(Outfile,"%s\n","  }\n\n");
    }
  if(Use_StartupCode)
    {
      fprintf(Outfile,"%s\n","int BCX_StartupCode_(void)");
      fprintf(Outfile,"%s\n","{");
        {int i;
      for(i=1; i<=StartNdx; i+=1)
        {
          fprintf(Outfile,"%s%s%s\n","  ",StartSub[i],"();");
        }
        }
      fprintf(Outfile,"%s\n","  return 1;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_ExitCode)
    {
      fprintf(Outfile,"%s\n","int BCX_ExitCode_(void)");
      fprintf(Outfile,"%s\n","{");
        {int i;
      for(i=1; i<=ExitNdx; i+=1)
        {
          fprintf(Outfile,"%s%s%s\n","  atexit(",ExitSub[i],");");
        }
        }
      fprintf(Outfile,"%s\n","  return 1;");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_Socket)
    {
      fprintf(Outfile,"%s\n","sockaddr_in sock_addr (char *ServerName,int port)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  in_addr  iaHost;");
      fprintf(Outfile,"%s\n","  hostent*  lpHostEntry;");
      fprintf(Outfile,"%s\n","  sockaddr_in  saServer;");
      fprintf(Outfile,"%s\n","  iaHost.s_addr=inet_addr(ServerName);");
      fprintf(Outfile,"%s\n","  if(iaHost.s_addr==INADDR_NONE)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      lpHostEntry=gethostbyname(ServerName);");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  else");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","     lpHostEntry=gethostbyaddr((char*)&iaHost,sizeof(in_addr),AF_INET);");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n"," if(lpHostEntry==NULL)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s%s%s\n","      printf(",enc("Error! HOST NOT FOUND: %s\\n"),", ServerName);");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  else");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      saServer.sin_port=htons(port);");
      fprintf(Outfile,"%s\n","      saServer.sin_family=AF_INET;");
      fprintf(Outfile,"%s\n","      saServer.sin_addr=*(in_addr*)lpHostEntry->h_addr;");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  return saServer;");
      fprintf(Outfile,"%s\n","}\n\n");
      fprintf(Outfile,"%s\n","int connect_socket (sockaddr_in saServer)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  int Socket, nRet;");
      fprintf(Outfile,"%s\n","  Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);");
      fprintf(Outfile,"%s\n","  if(Socket==-1)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      return Socket;");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  nRet=connect(Socket,(sockaddr*)&saServer,sizeof(sockaddr_in));");
      fprintf(Outfile,"%s\n","  if(nRet==-1)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      close(Socket);");
      fprintf(Outfile,"%s\n","      return nRet;");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  return Socket;");
      fprintf(Outfile,"%s\n","}\n\n");
      fprintf(Outfile,"%s\n","int BcxSocket (char *ServerName,int port)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  sockaddr_in  saServer;");
      fprintf(Outfile,"%s\n","  saServer=sock_addr(ServerName,port);");
      fprintf(Outfile,"%s\n","  return connect_socket(saServer);");
      fprintf(Outfile,"%s\n","}\n\n");
      fprintf(Outfile,"%s\n","int BcxSocketSend (int Socket, char *szBuffer)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  static int     nRet;");
      fprintf(Outfile,"%s\n","  nRet=send(Socket,szBuffer,strlen(szBuffer),0);");
      fprintf(Outfile,"%s\n","  if(nRet==-1)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      close(Socket);");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  return nRet;");
      fprintf(Outfile,"%s\n","}\n\n");
      fprintf(Outfile,"%s\n","int BcxSocketRead (int Socket, char *szBuffer)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  return read(Socket,szBuffer,strlen(szBuffer));");
      fprintf(Outfile,"%s\n","}\n\n");
      fprintf(Outfile,"%s\n","void    BcxSocketClose(int Socket) {");
      fprintf(Outfile,"%s\n","	close(Socket);");
      fprintf(Outfile,"%s\n","}\n\n");
    }
  if(Use_RegEx)
    {
      fprintf(Outfile,"%s\n","bool regmatch (char *buffer, char *pattern, REGEX* retval)");
      fprintf(Outfile,"%s\n","{");
      fprintf(Outfile,"%s\n","  static int     t;");
      fprintf(Outfile,"%s\n","  static int     i;");
      fprintf(Outfile,"%s\n","  static   regex_t  re;");
      fprintf(Outfile,"%s\n","  t=regcomp( &re,pattern,REG_ICASE|REG_EXTENDED);");
      fprintf(Outfile,"%s\n","  if(t)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      regerror(t, &re,buffer,sizeof(buffer));");
      fprintf(Outfile,"%s%s%s\n","      printf(",enc("regex error: %s %s"),",buffer,pattern);");
      fprintf(Outfile,"%s\n","      return 0;");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  t=regexec( &re,buffer,1023,(*retval).matches,0);");
      fprintf(Outfile,"%s\n","  (*retval).count=re.re_nsub;");
      fprintf(Outfile,"%s\n","  if(!t)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      for(i=1; i<=(*retval).count; i+=1)");
      fprintf(Outfile,"%s\n","        {");
      fprintf(Outfile,"%s\n","          if((*retval).matches[i].rm_so>=0)");
      fprintf(Outfile,"%s\n","            {");
      fprintf(Outfile,"%s\n","             (*retval).results[i]=peekstr( &buffer[(*retval).matches[i].rm_so],((*retval).matches[i].rm_eo-(*retval).matches[i].rm_so));");
      fprintf(Outfile,"%s\n","           }");
      fprintf(Outfile,"%s\n","        }");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  regfree( &re);");
      fprintf(Outfile,"%s\n","  if(!t)");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      return TRUE;");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","  else");
      fprintf(Outfile,"%s\n","    {");
      fprintf(Outfile,"%s\n","      return FALSE;");
      fprintf(Outfile,"%s\n","    }");
      fprintf(Outfile,"%s\n","}\n\n");
    }
}


int JoinLines (char *Arg)
{
  if(iMatchRgt(Arg," _"))
    {
      Arg[strlen(Arg)-1]=0;
      strcat(CurLine,Arg);
      return 1;
    }
  if(*CurLine!=0)
    {
      strcpy(Arg, join(2,CurLine,Arg));
      *CurLine=0;
    }
  UmQt=FALSE;
  return 0;
}


void StripCode (char *Arg)
{
   PCHAR  p;
   PCHAR  p2=Arg;
  int     asmFlag=0;
  int     eStr=0;
  char sub_[2048];
  while((*p2>8&&*p2<14)||*p2==32)
    {
      p2++;
    }
  if(*p2==33)
    {
      asmFlag=!UmQt;
    }
  p=p2;
  while(*p)
    {
      if(*p==9)
        {
          *p=32;
        }
      if(*p==34)
        {
          if(*(p-1)==69)
            {
              *(p-1)=1;
              eStr=TRUE;
            }
          while(*(++p)!=34)
            {
              if(*p==92&&eStr)
                {
                  *p=2;
                  for(;;)
                  {
                    if(*(p+1)==48)
                      {
                        *(p+1)=3;
                        break;
                      }
                    if(*(p+1)==116)
                      {
                        *(p+1)=4;
                        break;
                      }
                    if(*(p+1)==110)
                      {
                        *(p+1)=5;
                        break;
                      }
                    if(*(p+1)==114)
                      {
                        *(p+1)=6;
                        break;
                      }
                    if(*(p+1)==113)
                      {
                        *(p+1)=7;
                        break;
                      }
                    if(*(p+1)==92)
                      {
                        *(p+1)=8;
                      }
                    break;
                  }
                  p++;
                }
              if(*p==0)
                {
                  UmQt=!UmQt;
                  break;
                }
            }
        }
      if(!UmQt&&!asmFlag)
        {
          if((*p BOR 32)==114)
            {
              if((*(p+1) BOR 32)==101&&(*(p+2) BOR 32)==109&&(*(p+3)==32||*(p+3)==0))
                {
                  if(p==p2||*(p-1)==58||*(p-1)==32)
                    {
                      *p=0;
                      break;
                    }
                }
            }
          if(*p==39||(*p==47&&*(p+1)==47))
            {
              *p=0;
              break;
            }
        }
      p++;
    }
  while(p2<p)
    {
      while((*(p-1)>8&&*(p-1)<14)||*(p-1)==32)
        {
          *(--p)=0;
        }
      if(UmQt||asmFlag)
        {
          break;
        }
      if(*(p-1)==58&&*(p-2)==32)
        {
          p--;
        }
      else
        {
          break;
        }
    }
  if(eStr)
    {
      strcpy(p2,replace(p2,chr(1),""));
      strcpy(p2,replace(p2,chr(2),""));
      strcpy(sub_, join(3,DQ,"+CHR$(0)+",DQ));
      strcpy(p2,replace(p2,chr(3),sub_));
      strcpy(sub_, join(3,DQ,"+CHR$(9)+",DQ));
      strcpy(p2,replace(p2,chr(4),sub_));
      strcpy(sub_, join(3,DQ,"+CHR$(10)+",DQ));
      strcpy(p2,replace(p2,chr(5),sub_));
      strcpy(sub_, join(3,DQ,"+CHR$(13)+",DQ));
      strcpy(p2,replace(p2,chr(6),sub_));
      strcpy(sub_, join(3,DQ,"+CHR$(34)+",DQ));
      strcpy(p2,replace(p2,chr(7),sub_));
      strcpy(sub_, join(3,DQ,"+CHR$(92)+",DQ));
      strcpy(p2,replace(p2,chr(8),sub_));
      strcpy(p2,replace(p2,(join(3,chr(34),chr(34),chr(43))),""));
      strcpy(p2,replace(p2,(join(3,chr(43),chr(34),chr(34))),""));
    }
  memcpy(Arg,p2,strlen(p2)+1);
}


void ProcSingleLineIf (int* ifFlag)
{
  char Tmp[2048];
  int     ifp;
  int     NdIfs;
  static int     EFlag;
  if((*ifFlag)==0)
    {
      EFlag=0;
    }

REDO:;
  if(SplitCnt>120)
    {
      Abort("Stack Overflow - Too many statements on one line");
    }
  strcpy(Tmp, join(2,SplitStk[SplitCnt],SPC));
  if(iMatchLft(Tmp,"if "))
    {
      ifp=iMatchNQ(Tmp," then ");
      if(ifp)
        {
          strcpy(SplitStk[SplitCnt++],left(Tmp,ifp+4));
          strcpy(SplitStk[SplitCnt],ltrim(Tmp+ifp+4));
          EFlag=_MAX_(0,EFlag-1);
          (*ifFlag)++;
          goto REDO;
        }
    }
  else if((*ifFlag))
    {
      if(iMatchLft(Tmp,"else "))
        {

LFTLSE:;
          if(++EFlag>1)
            {
              NdIfs=_MAX_(1,(*ifFlag)-1);
              (*ifFlag)=1;
              EFlag=0;
              if(iMatchWrd(SplitStk[SplitCnt-1],"else"))
                {
                  SplitCnt--;
                }
                {int BCX_REPEAT;
                for(BCX_REPEAT=1;BCX_REPEAT<=NdIfs;BCX_REPEAT++)
                {
                  strcpy(SplitStk[SplitCnt++],"END IF");
                }
                }
            }
          strcpy(SplitStk[SplitCnt++],"ELSE");
          strcpy(SplitStk[SplitCnt],trim(Tmp+4));
          goto REDO;
        }
      else
        {
          ifp=iMatchNQ(Tmp," else ");
          if(ifp)
            {
              strcpy(SplitStk[SplitCnt++],rtrim(left(Tmp,ifp-1)));
              strcpy(Tmp,mid(Tmp,ifp+1));
              goto LFTLSE;
            }
        }
    }
}


int SplitLines (char *Arg)
{
   PCHAR  p=Arg;
   PCHAR  st=Arg;
  int     i=0;
  int     IfFlag=0;
  int     SpcolonFlag=0;
  int     ParaCnt=0;
  if(*p==33||*p==36)
    {
      return 0;
    }
  while(*p)
    {
      if(*p==32)
        {
          SpcolonFlag=1;
        }
      if(*p==34)
        {
          while(*(++p)!=34)
            {
              if(*p==0)
                {
                  return SplitCnt;
                }
            }
        }
      if(*p==40)
        {
          ParaCnt++;
        }
      if(*p==41)
        {
          ParaCnt--;
        }
      if(*p==58&&*(p+1)!=61)
        {
          if(*(p+1)==58)
            {
              *p=-15;
              *(p+1)=-15;
            }
          else
            {
              if(*(p+1)!=0||SpcolonFlag)
                {
                  while(*st==32)
                    {
                      st++;
                    }
                  SplitCnt++;
                  while(st<p)
                    {
                      SplitStk[SplitCnt][i++]=*(st++);
                    }
                  while(SplitStk[SplitCnt][i-1]==32)
                    {
                      i--;
                    }
                  SplitStk[SplitCnt][i]=0;
                  if(ParaCnt==0)
                    {
                      i=0;
                      st++;
                      ProcSingleLineIf( &IfFlag);
                    }
                  else
                    {
                      SplitCnt--;
                    }
                }
            }
        }
      p++;
    }
  if(SplitCnt>0)
    {
      while(*st==32)
        {
          st++;
        }
      SplitCnt++;
      while(*st)
        {
          SplitStk[SplitCnt][i++]=*(st++);
        }
      SplitStk[SplitCnt][i]=0;
      ProcSingleLineIf( &IfFlag);
    }
  else if(iMatchLft(Arg,"if ")&&!iMatchRgt(Arg," then"))
    {
      strcpy(SplitStk[++SplitCnt],Arg);
      ProcSingleLineIf( &IfFlag);
    }
  if(IfFlag)
    {
      while(IfFlag)
        {
          strcpy(SplitStk[++SplitCnt],"END IF");
          IfFlag--;
        }
    }
  return SplitCnt;
}


int iMatch (char *Arg, char *MatchStr, int mt)
{
  if(mt==2)
    {
      int     L1;
      int     L2;
      L1=strlen(Arg);
      L2=strlen(MatchStr);
      if(L1<L2)
        {
          return 0;
        }
      Arg=(Arg+L1)-L2;
    }
  while(*MatchStr)
    {
      if(*Arg==0)
        {
          return 0;
        }
      if((*Arg BOR 32)!=(*MatchStr BOR 32))
        {
          return 0;
        }
      Arg++;
      MatchStr++;
    }
  if(mt&&*Arg!=0)
    {
      return 0;
    }
  return 1;
}


int iMatchNQ (char *Arg, char *MatchStr)
{
  int     mi=0;
   PCHAR  a=Arg;
  while(MatchStr[mi])
    {
      if(*a==34)
        {
          mi=0;
          while(*(++a)!=34)
            {
              if(*a==0)
                {
                  return 0;
                }
            }
        }
      if(a[mi]==0)
        {
          return 0;
        }
      if((a[mi] BOR 32)!=(MatchStr[mi] BOR 32))
        {
          a++;
          mi=-1;
        }
      mi++;
    }
  return (a-Arg)+1;
}


int SpecialCaseHandler (char *Arg)
{
  int     i;
  int     j;
  char lsz[2048];
  if(iMatchNQ(Arg," sub ")||iMatchNQ(Arg," function "))
    {
      return 0;
    }
  if(iMatchNQ(Arg,"function main("))
    {
      strcpy(SrcStk[++SrcCnt],Arg);
      strcpy(SrcStk[++SrcCnt],"G_argc = argc");
      strcpy(SrcStk[++SrcCnt],"G_argv = argv");
      goto PROCESSNEW;
    }
  strcpy(lsz, join(3,SPC,extract(Arg," "),SPC));
  if(iMatchNQ(" dim , local , global , raw , static , shared , dynamic , auto , register , extern ",lsz))
    {
      FastLexer(Arg," ",",(){}");
      for(i=1; i<=Ndx; i+=1)
        {
          if(iMatchWrd(Stk[i],"as"))
            {
              strcpy(Stk[i-1],Clean(Stk[i-1]));
            }
        }
      strcpy(Stk[2], join(3,SPC,Stk[2],SPC));
      if(iMatchNQ(" raw local dynamic register static shared auto ",Stk[2]))
        {
          strcpy(Stk[1], join(2,Stk[1],Stk[2]));
          *Stk[2]=0;
        }
      SrcCnt++;
      j=0;
      for(i=1; i<=Ndx; i+=1)
        {
          if(Stk[i][0]==40)
            {
              j++;
            }
          if(Stk[i][0]==123)
            {
              j++;
            }
          if(Stk[i][0]==41)
            {
              j--;
            }
          if(Stk[i][0]==125)
            {
              j--;
            }
          if(Stk[i][0]==44&&!j)
            {
              strcpy(Stk[i],Stk[1]);
              SrcCnt++;
            }
          strcpy(SrcStk[SrcCnt], join(3,SrcStk[SrcCnt],Stk[i]," "));
        }
      goto PROCESSNEW;
    }
  for(;;)
  {
    if(TRUE==iMatchLft(Arg,"on "))
      {
        int     Target;
        j=0;
        FastLexer(Arg," ",",");
        for(i=1; i<=Ndx; i+=1)
          {
            if(iMatchLft(Stk[i],"gosub")||iMatchLft(Stk[i],"goto")||iMatchLft(Stk[i],"call"))
              {
                Target=i+1;
                break;
              }
          }
        strcpy(SrcStk[++SrcCnt],"select case ");
        for(i=2; i<=Target-2; i+=1)
          {
            strcpy(SrcStk[SrcCnt], join(3,SrcStk[SrcCnt]," ",Stk[i]));
          }
        for(i=Target; i<=Ndx; i+=1)
          {
            if(str_cmp(Stk[i],",")==0)
              {
                continue;
              }
            j++;
            strcpy(SrcStk[++SrcCnt], join(2,"case",str(j)));
            strcpy(SrcStk[++SrcCnt], join(3,Stk[Target-1]," ",Stk[i]));
          }
        strcpy(SrcStk[++SrcCnt],"end select");
        goto PROCESSNEW;
      }
    if(TRUE==iMatchLft(Arg,"loop "))
      {
        FastLexer(Arg," ",",()");
        if(iMatchLft(Stk[2],"until"))
          {
            strcpy(SrcStk[++SrcCnt],"if ");
            for(i=3; i<=Ndx; i+=1)
              {
                strcpy(SrcStk[SrcCnt], join(3,SrcStk[SrcCnt],Stk[i]," "));
              }
            strcpy(SrcStk[SrcCnt], join(2,SrcStk[SrcCnt]," then"));
            strcpy(SrcStk[++SrcCnt],"exit loop");
            strcpy(SrcStk[++SrcCnt],"end if");
            strcpy(SrcStk[++SrcCnt],"loop");
            goto PROCESSNEW;
          }
        else if(iMatchLft(Stk[2],"while"))
          {
            strcpy(SrcStk[++SrcCnt],"if NOT (");
            for(i=3; i<=Ndx; i+=1)
              {
                strcpy(SrcStk[SrcCnt], join(3,SrcStk[SrcCnt],Stk[i]," "));
              }
            strcpy(SrcStk[SrcCnt], join(2,SrcStk[SrcCnt],") then"));
            strcpy(SrcStk[++SrcCnt],"exit loop");
            strcpy(SrcStk[++SrcCnt],"end if");
            strcpy(SrcStk[++SrcCnt],"loop");
            goto PROCESSNEW;
          }
        else
          {
            if(Ndx>1)
              {
                Abort(join(3,"UNKNOWN Word ",Stk[2]," After LOOP"));
              }
          }
        break;
      }
    if(TRUE==iMatchLft(Arg,"do "))
      {
        FastLexer(Arg," ",",()");
        if(iMatchLft(Stk[2],"until"))
          {
            strcpy(SrcStk[++SrcCnt],"do");
            strcpy(SrcStk[++SrcCnt],"if ");
            for(i=3; i<=Ndx; i+=1)
              {
                strcpy(SrcStk[SrcCnt], join(3,SrcStk[SrcCnt],Stk[i]," "));
              }
            strcpy(SrcStk[SrcCnt], join(2,SrcStk[SrcCnt],"then"));
            strcpy(SrcStk[++SrcCnt],"exit loop");
            strcpy(SrcStk[++SrcCnt],"end if");
            goto PROCESSNEW;
          }
        else if(iMatchLft(Stk[2],"while"))
          {
            strcpy(SrcStk[++SrcCnt],"while ");
            for(i=3; i<=Ndx; i+=1)
              {
                strcpy(SrcStk[SrcCnt], join(3,SrcStk[SrcCnt],Stk[i]," "));
              }
            goto PROCESSNEW;
          }
        else
          {
            if(Ndx>1)
              {
                Abort(join(3,"UNKNOWN Word ",Stk[2]," After DO"));
              }
          }
      }
    break;
  }
  return 0;

PROCESSNEW:;
  Ndx=i=0;
  while(SrcCnt)
    {
      strcpy(Arg,SrcStk[++i]);
      *SrcStk[i]=0;
      SrcCnt--;
      Parse(Arg);
      if(Ndx)
        {
          Emit();
        }
    }
  return TRUE;
}


void FastLexer (char * Arg,char * delim1,char * delim2,int TokQuote)
{
  int     cnt1=0;
  int     cnt2=0;
   PCHAR  pd1;
   PCHAR  pd2;
  Ndx=1;
  while(Arg[cnt1])
    {
      if(Arg[cnt1]==34)
        {
          if(cnt2&&TokQuote)
            {
              Stk[Ndx++][cnt2]=0;
              cnt2=0;
            }
          Stk[Ndx][cnt2]=34;
          while(Arg[++cnt1]!=34)
            {
              Stk[Ndx][++cnt2]=Arg[cnt1];
              if(Arg[cnt1]==0)
                {
                  return;
                }
            }
          Stk[Ndx][++cnt2]=Arg[cnt1];
          if(TokQuote)
            {
              Stk[Ndx++][++cnt2]=0;
              cnt2=0;
              goto AGAIN;
            }
        }
      pd1=delim1;
      while(*pd1)
        {
          if(*(pd1++)==Arg[cnt1])
            {
              if(cnt2)
                {
                  Stk[Ndx++][cnt2]=0;
                  cnt2=0;
                }
              goto AGAIN;
            }
        }
      pd2=delim2;
      while(*pd2)
        {
          if(*(pd2++)==Arg[cnt1])
            {
              if(cnt2)
                {
                  Stk[Ndx++][cnt2]=0;
                }
              Stk[Ndx][0]=Arg[cnt1];
              Stk[Ndx++][1]=0;
              cnt2=0;
              goto AGAIN;
            }
        }
      Stk[Ndx][cnt2++]=Arg[cnt1];

AGAIN:;
      cnt1++;
    }
  Stk[Ndx][cnt2]=0;
  if(cnt2==0)
    {
      Ndx--;
    }
}


void InsertTokens (int PosAfter, int NumTokens, ...)
{
   va_list  ap;
  int     i;
  for(i=Ndx; i>=PosAfter+1; i+=-1)
    {
      strcpy(Stk[i+NumTokens],Stk[i]);
    }
  va_start(ap,NumTokens);
  for(i=PosAfter+1; i<=PosAfter+NumTokens; i+=1)
    {
      strcpy(Stk[i],va_arg(ap,char*));
    }
  va_end(ap);
  Ndx+=(NumTokens);
}


void EmitExportDef (char *fs)
{
  static int     beenhere;
  char fname[2048];
  char funcname[2048];
  int     i;
  int     st=1;
  int     sz=0;
  strcpy(fname, join(2,extract(FileIn,"."),".def"));
  if(!beenhere)
    {
      if((fpdef=fopen(fname,"w"))==0)
       {
         fprintf(stderr,"Can't open file %s\n",fname);
         exit(1);
       }
      _splitpath_(FileIn,NULL,NULL,fname,NULL);
      fprintf(fpdef,"%s%s\n","LIBRARY ",enc(fname));
      fprintf(fpdef,"%s\n","EXPORTS");
      beenhere=TRUE;
    }
  FastLexer(fs,"","(,)");
  while(*Stk[st]!=40)
    {
      st++;
    }
  for(i=st+1; i<=Ndx; i+=1)
    {
      if(*Stk[i]==41)
        {
          break;
        }
      if(*Stk[i]!=44)
        {
          if(inchr(Stk[i],"*"))
            {
              sz+=(4);
              continue;
            }
          if(instr_b(Stk[i],"longlong",1,1)||instr_b(Stk[i],"double",1,1)||instr_b(Stk[i],"long long"))
            {
              sz+=(8);
              continue;
            }
          if(!inchr(Stk[i],"void"))
            {
              sz+=(4);
            }
        }
    }
  strcpy(Stk[1],trim(Stk[1]));
  strcpy(funcname,mid(Stk[1],InstrRev(Stk[1]," ")+1));
  fprintf(fpdef,"%s%s%s%s%s\n",funcname," = _",funcname,"@",ltrim(str(sz)));
}


char * GetArg (int ArgNum, functionParse* fp)
{
  char *BCX_RetStr={0};
  char RetArg[2048];
  int     ArgEnd=fp->CommaPos[ArgNum]-1;
  int     ArgStart=fp->CommaPos[ArgNum-1]+1;
  *RetArg=0;
  if(ArgNum>=fp->NumArgs)
    {
      ArgEnd=Ndx;
    }
  for(ArgStart=ArgStart; ArgStart<=ArgEnd; ArgStart+=1)
    {
      strcat(RetArg,Stk[ArgStart]);
    }
  BCX_RetStr=BCX_TmpStr(strlen(RetArg));
  strcpy(BCX_RetStr,RetArg);
  return BCX_RetStr;
}


int SepFuncArgs (int Strt, functionParse* fp, int functionflag)
{
  int     CountR=0;
  int     i=Strt;
  if(functionflag)
    {
      while(i<=Ndx)
        {
          if(Stk[i][0]==40)
            {
              break;
            }
          i++;
        }
      Strt=i+1;
      fp->NumArgs=0;
      fp->CommaPos[0]=i;
      if(Strt>Ndx)
        {
          return 0;
        }
    }
  else
    {
      Strt=2;
      fp->CommaPos[0]=1;
    }
  if(*Stk[Strt]==41)
    {
      fp->CommaPos[1]=Strt;
      return 0;
    }
  fp->NumArgs=1;
  for(i=Strt; i<=Ndx; i+=1)
    {
      if(*Stk[i]==40||*Stk[i]==91)
        {
          CountR++;
        }
      else if(*Stk[i]==41||*Stk[i]==93)
        {
          if(CountR==0)
            {
              fp->CommaPos[fp->NumArgs]=i;
              break;
            }
          CountR--;
        }
      else if(*Stk[i]==44&&CountR==0)
        {
          fp->CommaPos[fp->NumArgs]=i;
          fp->NumArgs++;
        }
    }
  if(functionflag==0)
    {
      fp->CommaPos[fp->NumArgs]=Ndx;
    }
  return fp->NumArgs;
}


PCHAR MakeDecProto (functionParse* fp)
{
   functionParse  fpp;
  char FunType[2048];
  char AsType[2048];
  char AsArrys[2048];
  int     FoundAs;
  int     pointer=0;
  int     i;
  int     ii;
  char OptValue[2048];
  int     OptFlag=0;
  static char Proto[2048];
  static int     SubFunPtr;
  if(SubFunPtr)
    {
      goto ARGPARSE;
    }
  *Proto=0;
  *FunType=0;
  if(iMatchWrd(Stk[2],"sub")||iMatchWrd(Stk[2],"constructor")||iMatchWrd(Stk[2],"destructor"))
    {
      strcpy(FunType,"void");
    }
  else if(*Stk[Ndx]==41)
    {
      strcpy(FunType,VarTypeLookup[inchr(VarTypes,right(Stk[3],1))]);
    }
  else
    {
      for(i=Ndx; i>=fp->CommaPos[fp->NumArgs]+1; i+=-1)
        {
          if(iMatchWrd(Stk[i],"ptr"))
            {
              pointer++;
            }
          else if(iMatchWrd(Stk[i],"as"))
            {
              break;
            }
          else
            {
              strcpy(FunType, join(3,Stk[i],SPC,FunType));
            }
        }
    }
  if(InTypeDef)
    {
      if(iMatchWrd(Stk[2],"constructor"))
        {
          strcpy(Proto, join(2,Clean(Stk[3]),"("));
        }
      else if(iMatchWrd(Stk[2],"destructor"))
        {
          strcpy(Proto, join(3,"~",Clean(Stk[3]),"("));
        }
      else
        {
          strcpy(Proto, join(4,FunType," ",Clean(Stk[3]),"("));
        }
      char Var[2048];
      int     w;
      int     id;
      int     vt;
      strcpy(Var, join(2,FunType,stringx(pointer,42)));
      GetTypeInfo(Var, &w, &id, &vt);
      AddTypedefElement(BaseTypeDefsCnt[InTypeDef],vt,Clean(Stk[3]),FunType,0);
    }
  else if(SFPOINTER)
    {
      strcpy(Proto, join(7,"typedef ",FunType," (",CallType,"*",Clean(Stk[3]),"_TYPE)("));
    }
  else if(!NoTypeDeclare)
    {
      strcpy(Proto, join(7,"typedef ",FunType," (",CallType,"*BCXFPROT",ltrim(str(DllCnt)),")("));
    }
  else
    {
      if(UseCProto)
        {
          UseCProto=FALSE;
          strcpy(Proto, join(7,FunType,"  ",stringx(pointer,42),SPC,CallType,Clean(Stk[3]),"("));
        }
      else
        {
          strcpy(Proto, join(8,"C_IMPORT ",FunType,"  ",stringx(pointer,42),SPC,CallType,Clean(Stk[3]),"("));
        }
    }

ARGPARSE:;
  if(fp->NumArgs==0)
    {
      if(iMatchWrd(Stk[2],"destructor")||iMatchWrd(Stk[2],"constructor")||Use_Virtual)
        {
          strcat(Proto,")");
        }
      else
        {
          strcat(Proto,"void)");
        }
    }
  else
    {
      for(ii=0; ii<=fp->NumArgs-1; ii+=1)
        {
          *OptValue=0;
          *AsType=0;
          *AsArrys=0;
          pointer=0;
          FoundAs=0;
          int     FirstToken=fp->CommaPos[ii]+1;
          int     LastToken=fp->CommaPos[ii+1]-1;
          int     NumOfTokens=(LastToken-FirstToken)+1;
          i=inchr(Stk[FirstToken],"[");
          if(i)
            {
              strcpy(AsArrys,mid(Stk[FirstToken],i));
              Stk[FirstToken][i-1]=0;
            }
          if(NumOfTokens==1)
            {
              strcpy(AsType,VarTypeLookup[inchr(VarTypes,right(Stk[FirstToken],1))]);
              if(*AsArrys)
                {
                  strcpy(AsType,RemoveStr(AsType,"*"));
                }
              else
                {
                  pointer=tally(Stk[FirstToken],"*");
                }
              FoundAs=TRUE;
            }
          else
            {
              for(i=LastToken; i>=FirstToken; i+=-1)
                {
                  if(iMatchWrd(Stk[i],"ptr")||*Stk[i]==42)
                    {
                      pointer++;
                    }
                  else if(iMatchWrd(Stk[i],"sub"))
                    {
                      SepFuncArgs(fp->CommaPos[ii]+2, &fpp,TRUE);
                      strcat(Proto,"void (*)(");
                      SubFunPtr=FoundAs=TRUE;
                      MakeDecProto( &fpp);
                      SubFunPtr=FALSE;
                      break;
                    }
                  else if(iMatchWrd(Stk[i],"function"))
                    {
                      SepFuncArgs(fp->CommaPos[ii]+2, &fpp,TRUE);
                      if(AsType[0]==0)
                        {
                          strcpy(AsType,VarTypeLookup[inchr(VarTypes,right(Stk[FirstToken],1))]);
                        }
                      strcpy(Proto, join(4,Proto,rtrim(AsType),stringx(pointer,42)," (*)("));
                      pointer=0;
                      *AsType=0;
                      SubFunPtr=FoundAs=TRUE;
                      MakeDecProto( &fpp);
                      SubFunPtr=FALSE;
                      break;
                    }
                  else if(iMatchWrd(Stk[i],"as"))
                    {
                      if(AsType[0]==0)
                        {
                          Abort(join(2,"No type specified for argument",str(ii+1)));
                        }
                      FoundAs=TRUE;
                      break;
                    }
                  else if(*Stk[i]==61)
                    {
                      OptFlag=FoundAs=TRUE;
                      strcpy(OptValue, join(2," =",AsType));
                      *AsType=0;
                      if(i==FirstToken+1)
                        {
                          strcpy(AsType,VarTypeLookup[inchr(VarTypes,right(Stk[FirstToken],1))]);
                          if(*AsArrys)
                            {
                              strcpy(AsType,RemoveStr(AsType,"*"));
                            }
                          else
                            {
                              pointer=tally(Stk[FirstToken],"*");
                            }
                          break;
                        }
                    }
                  else
                    {
                      if(*Stk[i]!=46)
                        {
                          strcpy(AsType, join(3,Stk[i],SPC,AsType));
                        }
                      else
                        {
                          if(*Stk[i-1]==46)
                            {
                              if(OptFlag)
                                {
                                  Abort("Default value not allowed when using variable arguments");
                                }
                              if(ii!=(fp->NumArgs-1))
                                {
                                  Abort("Variable argument must be the last parameter");
                                }
                              if(fp->NumArgs==1)
                                {
                                  Abort("Variable argument must be preceded by at least one other parameter");
                                }
                              FoundAs=TRUE;
                            }
                          strcpy(AsType, join(2,Stk[i],AsType));
                        }
                    }
                }
            }
          if(!FoundAs)
            {
              Abort(join(2,"Malformed argument type in parameter",str(ii+1)));
            }
          if(ii!=fp->NumArgs&&OptFlag&&str_cmp(OptValue,"")==0)
            {
              Warning(join(2,"No default value specified for parameter",str(ii+1)),1);
            }
          strcpy(Proto, join(6,Proto,rtrim(AsType),AsArrys,stringx(pointer,42),OptValue,Stk[fp->CommaPos[ii+1]]));
        }
    }
  return Proto;
}


void AsmUnknownStructs (int CompArrays)
{
  int     InBrace=0;
  int     InStruct=0;
  int     i;
  char sztemp[2048];
  for(i=2; i<=Ndx; i+=1)
    {
      if(CompArrays)
        {
          if(str_cmp(Stk[i],"[")==0)
            {
              strcpy(sztemp,Stk[i-1]);
              *Stk[i-1]=0;
              for(;;)
                {
                  strcat(sztemp,Stk[i]);
                  if(str_cmp(Stk[i],"]")==0)
                    {
                      InBrace--;
                    }
                  if(str_cmp(Stk[i],"[")==0)
                    {
                      InBrace++;
                    }
                  *Stk[i]=0;
                  i++;
                  if(!(InBrace&&i<=Ndx))
                    {
                      break;
                    }
                }
              strcpy(Stk[--i],sztemp);
            }
        }
      if(strlen(Stk[i])>1&&!IsNumber(Stk[i]+1))
        {
          if(*Stk[i]==46||iMatchLft(Stk[i],"->"))
            {
              if(InStruct==0)
                {
                  strcpy(Stk[i], join(2,Stk[i-1],Stk[i]));
                  *Stk[i-1]=0;
                  InStruct=i;
                }
              else
                {
                  strcat(Stk[InStruct],Stk[i]);
                  *Stk[i]=0;
                }
              continue;
            }
        }
      if(*Stk[i]&&InStruct>0)
        {
          InStruct=0;
        }
    }
  RemEmptyTokens();
}


void EmitIfCond (char *CondType)
{
  int     TestString;
  int     A;
  int     B;
  int     ParCnt;
  int     Tmp;
  int     IsWhile=FALSE;
  char szTest[2048];
  TestString=DataType(Stk[2]);
  if(TestString==vt_STRVAR)
    {
      if(str_cmp(Stk[4],DDQ)==0)
        {
          strcpy(Stk[2], join(2,Clean(Stk[2]),"[0]"));
          strcpy(Stk[4],"0");
        }
      else if(str_cmp(Stk[3],"[")==0 &&  str_cmp(Stk[7],DDQ)==0)
        {
          strcpy(Stk[2],Clean(Stk[2]));
          strcat(Stk[5],"[0]");
          strcpy(Stk[7],"0");
        }
    }
  if(str_cmp(CondType,"while")==0)
    {
      IsWhile=TRUE;
    }
  fprintf(Outfile,"%s%s%s",Scoot,CondType,"(");
  Tmp=2;
  while(str_cmp(Stk[Tmp],"(")==0 ||  str_cmp(Stk[Tmp],"!")==0)
    {
      fprintf(Outfile,"%s",Stk[Tmp]);
      Tmp++;
    }
  TestString=FALSE;
  A=DataType(Stk[Tmp]);
  if(A==vt_STRLIT||A==vt_STRVAR)
    {
      if(str_cmp(Stk[Tmp+1],")")!=0 && !iMatchWrd(Stk[Tmp+1],"then"))
        {
          TestString=TRUE;
          Use_Str_Cmp=TRUE;
          fprintf(Outfile,"%s","str_cmp(");
        }
    }
  *szTest=0;
  ParCnt=0;
  for(;;)
    {
      if(TestString)
        {
          if(str_cmp(Stk[Tmp],"=")==0)
            {
              strcpy(Stk[Tmp],",");
              strcpy(szTest,")==0");
              ParCnt=0;
            }
          else if(str_cmp(Stk[Tmp],"!=")==0)
            {
              strcpy(Stk[Tmp],",");
              strcpy(szTest,")!=0");
              ParCnt=0;
            }
          else if(str_cmp(Stk[Tmp],">")==0)
            {
              if(str_cmp(Stk[Tmp+1],"=")==0)
                {
                  strcpy(Stk[Tmp],",");
                  strcpy(szTest,")>=0");
                  *Stk[Tmp+1]=0;
                }
              else
                {
                  strcpy(Stk[Tmp],",");
                  strcpy(szTest,")==1");
                }
              ParCnt=0;
            }
          else if(str_cmp(Stk[Tmp],"<")==0)
            {
              if(str_cmp(Stk[Tmp+1],"=")==0)
                {
                  strcpy(Stk[Tmp],",");
                  strcpy(szTest,")<=0");
                  *Stk[Tmp+1]=0;
                }
              else
                {
                  strcpy(Stk[Tmp],",");
                  strcpy(szTest,")==-1");
                }
              ParCnt=0;
            }
          else if(str_cmp(Stk[Tmp],"(")==0)
            {
              ParCnt++;
            }
          else if(str_cmp(Stk[Tmp],")")==0)
            {
              ParCnt--;
            }
          if(str_cmp(Stk[Tmp],")")==0 &&  str_cmp(szTest,"")!=0 && ParCnt<0)
            {
              fprintf(Outfile,"%s%s",szTest,Stk[Tmp]);
              *szTest=0;
            }
          else
            {
              if(str_cmp(Stk[Tmp],"||")==0 ||  str_cmp(Stk[Tmp],"&&")==0)
                {
                  strcpy(Stk[Tmp], join(4,szTest," ",Stk[Tmp]," "));
                  *szTest=0;
                  B=1;
                  while(str_cmp(Stk[Tmp+B],"(")==0)
                    {
                      strcat(Stk[Tmp],"(");
                      *Stk[Tmp+B]=0;
                      B++;
                    }
                  A=DataType(Stk[Tmp+B]);
                  if((A==vt_STRLIT||A==vt_STRVAR)&&str_cmp(Stk[Tmp+B+1],")")!=0)
                    {
                      strcat(Stk[Tmp]," str_cmp(");
                      Use_Str_Cmp=TRUE;
                    }
                  else
                    {
                      fprintf(Outfile,"%s",Clean(Stk[Tmp]));
                      TestString=FALSE;
                      goto NXTTOKEN;
                    }
                }
              fprintf(Outfile,"%s",Clean(Stk[Tmp]));
            }
        }
      else
        {
          if(str_cmp(Stk[Tmp],"||")==0 ||  str_cmp(Stk[Tmp],"&&")==0)
            {
              B=1;
              while(str_cmp(Stk[Tmp+B],"(")==0)
                {
                  strcat(Stk[Tmp],"(");
                  *Stk[Tmp+B]=0;
                  B++;
                }
              A=DataType(Stk[Tmp+B]);
              if((A==vt_STRLIT||A==vt_STRVAR)&&str_cmp(Stk[Tmp+B+1],")")!=0)
                {
                  strcat(Stk[Tmp],"str_cmp(");
                  TestString=TRUE;
                  Use_Str_Cmp=TRUE;
                  *szTest=0;
                  ParCnt=0;
                  fprintf(Outfile,"%s",Clean(Stk[Tmp]));
                  goto NXTTOKEN;
                }
            }
          if(str_cmp(Stk[Tmp],"!")==0)
            {
              fprintf(Outfile,"%s",Stk[Tmp]);
            }
          else
            {
              fprintf(Outfile,"%s",Clean(Stk[Tmp]));
            }
          if(str_cmp(Stk[Tmp],"=")==0)
            {
              if(str_cmp(Stk[Tmp-1],"<")!=0 &&  str_cmp(Stk[Tmp-1],">")!=0)
                {
                  if(str_cmp(Stk[Tmp+1],">")!=0 &&  str_cmp(Stk[Tmp+1],"<")!=0)
                    {
                      fprintf(Outfile,"%s","=");
                    }
                }
            }
        }

NXTTOKEN:;
      Tmp++;
      if(!IsWhile)
        {
          if(iMatchWrd(Stk[Tmp],"then"))
            {
              break;
            }
          else if(Tmp>Ndx)
            {
              Abort("If Without THEN");
            }
        }
      if(Tmp>Ndx)
        {
          break;
        }
    }
  fprintf(Outfile,"%s%s\n",szTest,")");
  BumpUp();
  fprintf(Outfile,"%s%s\n",Scoot,"{");
  BumpUp();
}


void PrintGlobal (int A, int idx, char *Storage, char *P, char *VarName, char *VarDim)
{
  char VAR[2048];
  for(;;)
  {
    if(A==vt_FILEPTR)
      {
        strcpy(VarName,RemoveStr(VarName,"@"));
        fprintf(Outfile,"%s%s%s%s%s%s\n",Storage,"FILE   *",P,VarName,VarDim,";");
        break;
      }
    if(A==vt_UDT||A==vt_STRUCT||A==vt_UNION)
      {
        strcpy(VAR,TypeDefs[GlobalVars[idx].VarDef].VarName);
        strcpy(VAR,rpad(VAR,7));
        fprintf(Outfile,"%s%s%s%s%s%s%s\n",Storage,VAR," ",P,VarName,VarDim,";");
        break;
      }
    if(A==vt_BOOL)
      {
        fprintf(Outfile,"%s%s%s%s%s\n",Storage,"bool    ",VarName,VarDim,";");
        break;
      }
    if(A==vt_STRVAR)
      {
        if(VarDim[0]==0)
          {
            strcpy(VarDim,"[65535]");
          }
        fprintf(Outfile,"%s%s%s%s%s%s\n",Storage,"char    ",P,VarName,VarDim,";");
        break;
      }
    if(A>=vt_VarMin&&A<=vt_VarMax)
      {
        strcpy(VAR,GetVarTypeName(GlobalVars[idx].VarType));
        strcpy(VAR,rpad(VAR,7));
        fprintf(Outfile,"%s%s%s%s%s%s%s\n",Storage,VAR," ",P,VarName,VarDim,";");
      }
    break;
  }
}


void ReDirectFPrint (FILE* TgtFile, char *pat, ...)
{
   va_list  ap;
  if(DoCountLines&&TgtFile==FP3)
    {
      gLinesWritten++;
    }
  va_start(ap,pat);
  vfprintf(TgtFile,pat,ap);
  va_end(ap);
}


int IsReservedWord (char *match)
{
  char mat[2048];
  strcpy(mat,ucase(match));
  if(containedin(mat,ReservedWord)==0)
    {
      return 1;
    }
  return 0;
}


int GetAsPos (void)
{
  int     i;
  for(i=Ndx; i>=2; i+=-1)
    {
      if(iMatchWrd(Stk[i],"as"))
        {
          return i;
        }
    }
  return 0;
}


void FreeGlobals (void)
{
  if(RmLibs)free(RmLibs);
  if(WarnMsg)free(WarnMsg);
  if(AbortSrc)free(AbortSrc);
  if(Src)free(Src);
  if(szTmp)free(szTmp);
}


