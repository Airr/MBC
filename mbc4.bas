'******************************************************************************
'******************************************************************************
' BCX Universal - The Cross Platform Basic To C/C++ Translator Version 2.0d
'******************************************************************************
'                          (c) 1999 - 2009 Kevin Diggins
'******************************************************************************

'********************************
'** OSX 10.5+ UNIVERSAL BINARY **
'********************************
'$OSX

'*****************
'** GTK Support **
'*****************
'$GTK

'*****************
'** GLIB Support *
'*****************
'$GLIB

'****************************
'** WX WIDGETS GUI SUPPORT **
'****************************
'$WX

'********************************
'** WX WIDGETS CONSOLE SUPPORT **
'********************************
'$WXC

'***********************
'** Apple IOS SUPPORT **
'***********************
'$IOS

'**********************************
'** AUTO BUILD TRANSLATOR BINARY **
'**********************************
$EXECON


'**********************
'** STRIP EXECUTABLE **
'**********************
' $EXESTRIP


'
CONST Version$ = "4.0-Beta3 (2018/12/09)" 'BCX version number and date (YYYY/MM/DD)
'*******************************************************************************
'
'BCX is distributed under the terms of the GNU General Public License Ver.(2).
'The complete source code that is PRODUCED BY BCX is subject to a License
'Exception to the GPL, which allows you to produce commercial applications.
'
'******************************************************************************
'    BCX LICENSE EXCEPTION
'******************************************************************************
'
'As a special exception, the BCX license gives permission for additional uses
'of the text contained in its release of BCX. The exception is that, if you use
'BCX to create source code that will link the BCX libraries with other files to
'produce an executable, this does not by itself cause the resulting executable
'to be covered by the GNU GPL.  Your use of that executable is in no way
'restricted on account of using BCX to produce source code that will link the
'BCX library code into it.
'
'This exception does not invalidate any other reasons why the executable file
'might be covered by the GNU General Public License.  This exception applies
'only to the code released with this BCX explicit exception. If you add or copy
'code from other sources, as the General Public License permits, the above
'exception does not apply to the code that you add in this way.
'
'To avoid misleading anyone as to the status of such modified files, you must
'delete this exception notice from them.  If you write modifications of your
'own for BCX, it is your choice whether to permit this exception to apply to
'your modifications.
'This program is distributed in the hope that it will be useful, but WITHOUT
'ANY WARRANTY; WITHOUT EVEN THE IMPLIED WARRANTY  OF MERCHANTABILITY OR FITNESS
'FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
'
'    You should have received a copy of the GNU General Public License along with
'    this program; if not, write to the Free Software Foundation, Inc.,
'59 Temple Place - Suite 330, Boston, MA  02111-1307, USA or visit
'http://www.gnu.org/copyleft/gpl.html#SEC1

$COMMENT - Comment section added 10/20/2004 05:00AM by Vic McClung
*******************************************************************************
Developer Guidelines
*******************************************************************************
Code should be written in BCX Basic. If it can not be written in BCX Basic for
some reason or results in code that seems too inefficient then this may be a
cue that a new Basic function is needed.
* All KEYWORDS should be capitalized
* Use two space indentation
* Use spaces not tabs
* Record all notes in reverse chronological order
* And most importantly....Have fun!
******************************************************************************************
This section is used to communicate to-do 's, changes, ideas, suggestions, etc.
******************************************************************************************
-------------------------------------------
2018-12-12 Armando Rivera
  * Changed BcxRegEx function to REGMATCH
  * Changed BcxRegEx keyword to REGMATCH
  * Added $MODULE as alias to $INCLUDE to support external modules.  ** MUST BE AT TOP OF MAIN SOURCE FILE **
  * Added $LDFLAGS directive to support external modules
-------------------------------------------
-------------------------------------------
2016-02-15 Armando Rivera
-------------------------------------------
  * Changed default string size to 65K from 
    2k, which was limiting.
  * Updated output of PRINT command, eliminating
    leading spaces from numbers.
-------------------------------------------
2015-07-03 Armando Rivera
-------------------------------------------
  * Changed $OSX flag to use Cocoa instead of Carbon in MacOS
    This is in preparation of the new custom libcocoa library
    that I'm currently creating that will allow mbc
    to create 64bit GUI applications in OSX
-------------------------------------------
2013-06-26 Armando Rivera
-------------------------------------------
  * Added BcxRegex keyword, based on Posix Regex in Libc
  * Broke up main source file into files containing Runtime, Declarations, etc.
  * Added BYTE type

-------------------------------------------
2013-06-17 Armando Rivera
-------------------------------------------
  * Tweaked HEX$ so that it will emit 2-digit hex numbers
  * Added PUCHAR (unsigned char*) typedef
-------------------------------------------
2011-03-11 Armando Rivera
-------------------------------------------
  * Added Wayne's suggestion to support Reference Variables as return types.

-------------------------------------------
2011-03-10 Armando Rivera
-------------------------------------------
  * Ported $PROJECT directive from ConsoleBC.  This doesn't emit the RTL yet, but it's a start.
    It's the first step towards re-writing the RT code to leverage CPP/WX.

  * Fixed bug where BCX_TmpStr sometimes wasn't emitted when returning a string from a function

  * Added Named Enum support.  Syntax:
      myenum AS ENUM
      …
      END ENUM

      This required moving the Enum emit code to before the User Prototype emit code
      to allow passing the named enum to user defined functions.

-------------------------------------------
2011-01-23 Armando Rivera
-------------------------------------------
  * Initial Beta1 Release

  * Fixed bug in INPUT statement to remove trailing newlines (James Fuller)

  * Removed COLOR statements to avoid terminal output issues with redirected
    translator output (James Fuller)

  * Added CONST keyword when declaring variables (Global, Local, and as Function/Sub parameters)
    At the moment, this is experimental (meaning I haven't fully tested it) but it seems to work

  * Added PRIVATE keyword for CPP classes
-------------------------------------------
2010/12/21  Armando Rivera
-------------------------------------------
  * Cleaned up code emission so that unneeded defines/global vars are not emitted

  * Added new $IOS directive, which is MAC ONLY, to compile source for iDevices (iPhone/iTouch/AppleTV2)
    At this point in time, running binaries built this way requires a jailbroken iDevice.
    This is experimental, and for console apps only for now.
    A simple console example is in the Examples/IOS folder
-------------------------------------------
2010/12/11  Armando Rivera
-------------------------------------------
	* Add new Socket keywords: BcxSocket, BcxSocketSend, BcxSocketRead, and BcxSocketClose
		See the BcxSocket.bas demo in the Examples/Socket folder for info.

	* Added kbhit() , which doesn't exist outside of Windows
		This is a custom sub which emulates what kbhit() does

	* Changed the conditional emission of term.h to only be emitted when
		Use_Keypress is TRUE (InKey)

-------------------------------------------
2010/12/01  Armando Rivera
-------------------------------------------
	* Changed wxApp emission to use BCXPLITHPATH$, per James Fuller's suggestion.

	* Added support for Abstract Classes (gcc doesn't have the INTERFACE keyword)

		Example:
			Class MyAbstractClass
				public

					virtual sub Proc1() = 0
					Virtual sub Proc2()=0
					virtual function Proc3(a$,b$) as integer = 0

			End Class
-------------------------------------------
2010/11/30  Armando Rivera
-------------------------------------------
	* Removed $CLASS/$ENDCLASS $NAMESPACE/$ENDNAMESPACE
		Using either will emit a message stating that they have been replaced.

	* Addded NAMESPACE / END NAMESPACE
		This allows creating methods within the NAMESPACE like so:

		$CPP
		$NOMAIN
		$EXECON
		'==============================================================================
		NAMESPACE Dlg_01
			Sub DoIt()
				Print "Dlg_01"
			End Sub

			Function GetString$(A$) as string
				function = "The String you Passed Was: " + enc$(A$)
			end function
		END NAMESPACE
		'==============================================================================
		Function main(argc as INTEGER, argv as PCHAR ptr) as INTEGER
			Print "James"
			Dlg_01::DoIt()
			print Dlg_01::GetString$("Hello, World!")
		End Function

  * If using $WX, the #define for Clear() will not be emitted due to conflict
    with Classes that have that method defined

  * Made the inclusion of "term.h" conditional based on whether $WX/$WXC
    is used.  "term.h" is required for the implementation of
    the PAUSE keyword in CONSOLE apps.

-------------------------------------------
2010/11/25  Armando Rivera
-------------------------------------------
  * Changed code so that in $CPP mode, the case of the emitted
    .cpp filename is preserved (James Fuller bug report)

-------------------------------------------
2010/11/24  Armando Rivera
-------------------------------------------
  * Minor change in StripCode() to correct
    possible overflow issue under 64bit Linux (James Fuller bug report)

  * Added $WXC Directive to support WX Console-Based Apps
    Using this switch, neither a wxApp or the IMPLEMENT_APP() macro are
    auto added to the translated source (James Fuller request)
-------------------------------------------
2010/11/20  Armando Rivera
-------------------------------------------
	* Changed $DLL directive so that it would generate *nix Shared Libraries.
	* Added $DLL support to $EXECON
	* Added required flags to LD_FLAGS$ for creating *nix Shared Libraries
		Example:
			$dll
			$execon

			function printdemo() export
				print "This was called from a Dynamic Library"
			end function

		Note that this is currently only useful for creating shared libraries
		for **OTHER** languages; it won't work with MBC created apps because of
		duplicate naming conflicts.

-------------------------------------------
2010/11/18  Armando Rivera
-------------------------------------------
  * Removed "-Os" compiler optimization flag from $EXECON for fastest tranlator compliation
    during Alpha testing stage.

    This will be re-added when translator is not longer in Alpha status

  * Added USE_CTOR global as flag for supporting Constructor/Destructor syntax

  * Added "USING" keyword for CONSTRUCTOR/DESTRUCTOR methods.  It is used like this:

      CONSTRUCTOR MainWin::MainWin(title as wxString, winStyle as long) USING wxFrame( 0, -1, title, wxPoint(50,50), wxSize(490,296), winStyle )

    Which will emit:

      MainWin::MainWin (wxString title, long winStyle)
      : wxFrame( 0, -1, title, wxPoint(50,50), wxSize(490,296), winStyle )
      {

  * Added code to extract and emit derived class methods

-------------------------------------------
2010/11/17  Armando Rivera
-------------------------------------------
  * Added new CLASS / END CLASS / PUBLIC / PROTECTED / CONSTRUCTOR / DESTRUCTOR keywords.
    These additions flesh out Basic-Like C++ CLASS support, superceding $CLASS/$ENDCLASS,
    and now allows syntax like the following:

        $CPP
        $NOMAIN
        $execon

        class MyClass

        	protected
        		first as string
        		secnd$
        		third%

        	public
        		type ATest
        			a as PCHAR
        			b as long
        			c as single
        			d as float
        		end type

        	Constructor MyClass(a$, b)
        	Destructor MyClass()
        end class

        FUNCTION main(argc as INTEGER, argv as PCHAR ptr) as INTEGER
          RAW theClass as MyClass PTR

          theClass = new MyClass("Hello", 12)

          print (char*)theClass->ATest.a
          print theClass->ATest.b
        END FUNCTION

        Constructor MyClass::MyClass(a$,b)
          ATest.a = a$
          ATest.b = b
        END Constructor
        '
        Destructor MyClass::~MyClass()

        END Destructor

-------------------------------------------
2010/11/12  Armando Rivera
-------------------------------------------
  * Added code that (mostly) eliminates the need for a trailing ";" in $class/$endclass

  * Added code to allow the use of "SUB" in $class/$endclass.  It just substitutes "void" for "sub"
    at this point.

  * Fixed "THIS" keyword code so that it emits a lowercase "this".  Linux/OSX aren't affected
    by this breaking COM statements. :-P  Thanks to JCFULLER for the tip!

  * For $CPP mode, added typedefs for std::string (CSTRING) and std::fstream (CFILE)
    These are direct replacements for STRING and FILE, and allows the full use of each
    C++ object/class.

    So instead of "dim mystring as string", for example, you would do "dim mystring as CSTRING".
    You would then have access to all of std::string's methods like .replace, .substr, .compare, etc.

    I'm considering doing the same with the other toolkit directives ($OSX, $GTK, etc) but we'll see...

  * Added "inherits" in $CPP mode so that subclassing can be done like so:

  		$class MyClass inherits AnotherClass

  * For $WX mode, added code to automatically emit the required derived wxApp class.
  	Note that it will be named the same as your sourcefile (minus the extension), and you MUST provide
  	a "FUNCTION ::OnInit() as bool" for it:

  		FUNCTION TestApp::OnInit() as bool
  			<initialize app here>
  		END FUNCTION

  * For $WX mode, made "$NOMAIN" the default, so no need to pass that directive

  * Colorized some of the compiler output text.  Just because I can.

  * Back-ported Wayne's changes to "WITH" to allow the use of "->" syntax

  * TODO:
      Finish off the $class/$endclass code to allow full basic syntax for method and variable
      declarations.

      Remove ALL remaining WIN32 related code and ifdefs.
      No need for that stuff under Linux/OSX, the Windows version of BCX can handle all
      of the Windows stuff one might need.

      Other stuff I can't remember right now…..
-------------------------------------------
2010/03/31  Armando Rivera
Beginning with this version of the console compiler,
the goal is to have a 100% unified code-base, because
I'm fracking tired of trying to maintain separate builds
for different Operating Systems.
-------------------------------------------

  * Added $OSX, $GTK¸$GLIB and $WX Directives
    (Use_Osx, Use_Wx, Use_Gtk, Use_Glib and LD_FLAGS$ Globals added)

    $OSX will automatically enable Carbon GUI support, and if $EXECON is invoked
    will also build a Universal Binary with 32bit and 64bit support

    $GTK will automatically enable GTK/GLIB support, and if $EXECON is invoked
    will build the executable linking in libgtk and it's support libraries.

    $GLIB will automatically enable >GLIB ONLY< support, and if $EXECON is invoked
    will build the executable linking in libglib and it's support libraries.

    $WX will automatically enable wxWidgets with $CPP set to "TRUE", and if $EXECON
    is invoked will build the executable linking in libwx and it's support libraries

    This is, in part, in preparation for moving the GTK support from the core of the
    LinuxBC translator to an external library which will be linked in as required.  This
    will GREATLY simplify maintenence of the translator core once the lib  is ready.

  * Changed alls instances of byte* to UCHAR* in SWAP() Function

  * Added internal return values for PUT/GET to get rid of ALL compiler warnings.

  * Updated runtime functions calling PUT()/GET()/fread()/fwrite  so that they
    will not trigger compiler warnings

  * Reworked the way functions declared using C_DECLARE with the LIB and ALIAS keywords
    are emitted.  This is so that you can dynamically load functions from a shared
    library at runtime via dlopen/dlsym.

    The syntax is:
    C_DECLARE FUNCTION <YOUR FUNCTION NAME> LIB <shared library> ALIAS <quoted name of actual function (<parameters>) AS <return type>

    For example:
    C_DECLARE FUNCTION b64encode LIB "libglib-2.0.so" ALIAS "g_base64_encode" (txt AS char*, length AS integer) AS string
    C_DECLARE FUNCTION g_base64_decode LIB "libglib-2.0.so" ALIAS "g_base64_decode" (txt AS char*, length AS INTEGER PTR) AS string

    NOTE that the ALIAS is the actual name of the function you want to call from the shared library.
    This is so you avoid redeclaration errors if you attempt to link to a library (libm is a good example)
    that is already compile-time linked with g++.

    NOTE 2: There is currently no checking whether the function was loaded without error.  It is on the TODO list.

  * Changed compiler invocation to include -Wformat and -D_FORTIFY_SOURCE=2 (Ubuntu Standard)

  * Fixed User Include File handling in order to support mixed case filenames

  * Updated the CURDIR$, TEMPDIR$, AND SHELL code to eliminate warnings emitted when compiling on
    a system that has "_FORTIFY_SOURCE=2" enabled by default in GCC/G++ (Ubuntu)

  * Fixed a potential overflow problem with LINE INPUT that would also cause G++ to emit
     warnings as above.

  *Re-coded the $RESOURCE directive and the GETRESOURCE$ function to allow
   linking of Resources under Linux/Unix.  Using $RESOURCE generates a #define
   allowing you to reference the embedded resource using an arbitrary IDENTIFIER.

  For example:

    DIRECTIVE    FILE    IDENTIFIER
    -------------------------------
    $RESOURCE "file.txt"  "myres"


  Note that you reference the resource using the identifier you passed as the
  SECOND parameter to the $RESOURCE directive, minus the quotes.

  "file.txt" above can be any arbitrary file on one's system

  At the moment, the resource is returned as a string with the GETRESOURCE$ function.
  *****************************************************************************************************
  ** YOU WILL HAVE TO ENSURE THAT A BUFFER WITH ENOUGH SPACE TO HOLD THE RESOURCE HAS BEEN ALLOCATED **
  *****************************************************************************************************
  To aid in this, a constant is automatically created with the size of the resource.  It will have the
  name you specified as the second parameter to $RESOURCE, with _SIZE appended.
  Using the example above, the constant would be defined as: myres_SIZE


  You should be able to manually cast the reference *itself* to what you require, since it is
  merely a pointer to the location of the resource itself.

  The resource will be converted to an object file, named using the filename provided with ".o" apppended.
  "file.txt" will be converted to "file.txt.o" in the above example, which can then be linked
  to the final executable via $EXECON "file.txt.o" or $EXEGUI "file.txt.o"

  * Tweaked $GUI directive and GUI keyword so that one can use the directive without
  having all of the support for BCX_* form objects automatically added to one's app.

  This is usefull when using GtkBuilder or Glade to build the user interface.

-------------------------------------------
2010-01-17 Armando Rivera
-------------------------------------------
  modified the $CLASS/$ENDCLASS directives to allow creation and inheritance of C++ Classes

  modified the Function/Sub prototype emitter so that it would not emit prototypes
    for C++ Class Methods, which are supposed to be prototyped within the Class itself

  made the inclusion of <term.h> conditional based on whether UseCPP is true/false
    it will not be included if UseCpp is "true" because some C++ toolkits (wxWidgets)
    throw a "redefined" error when it's included

-------------------------------------------
2010-01-15 Armando Rivera
-------------------------------------------
  per wmhalsdorf's recommendation, modified SplitLines and Emit procs to support
    C++ Method syntax (CLASSNAME::METHOD) [see Yahoo group Message #40282]

-------------------------------------------
2010-01-10 Armando Rivera
-------------------------------------------
  changed $CPP directive to output lowercase filenames

-------------------------------------------
2009-10-18 Armando Rivera
-------------------------------------------
  added Carbon.h as a default include, to support Carbon/CoreFoundation calls
  added Carbon framework to $execon section
  removed TRUE and FALSE defines, which are now provided by Carbon.h
  changed Handle$ to Handl$ to resolve conflict with Carbon.h

-------------------------------------------
2009-10-13 Armando Rivera
-------------------------------------------
  added typedef for "byte" type (typedef unsigned char byte;)

$COMMENT ================== END OF COMMENT SECTION ============================

CONST __BCX__ = 1 ' define BCX so we know we are in bc.bas
$NOMAIN
$GENFREE
$IPRINT_OFF
$NOINI
$TURBO
$HEADER
typedef long (*CPP_FARPROC)(char *);
$HEADER
ENUM
  vt_UNKNOWN '  Not a Variable
  vt_STRLIT '  "Quoted String Literal"
  vt_INTEGER '  Integer%
  vt_SINGLE '  Single!
  vt_DOUBLE '  Double#
  vt_LDOUBLE '  Long Double¦
  VT_LLONG '  Long Long
  vt_STRVAR '  StringVariable$
  vt_DECFUNC '  Translated Decimal Func: Strlen,Asin
  vt_NUMBER '  A Pure Literal Number
  vt_FILEPTR '  @ FILE*
  vt_UDT '  User ( or Windows ) Defined Type
  vt_STRUCT '  Structures
  vt_UNION '  Unions
  vt_BOOL
  vt_CHAR
  vt_LPSTRPTR
  vt_PCHAR
  vt_CHARPTR
  vt_VOID
  vt_LONG
  vt_DWORD
  vt_FARPROC
  vt_LPBYTE
  vt_LRESULT
  vt_BYTE
  vt_SHORT
  vt_USHORT
  vt_UINT
  vt_ULONG
  vt_HWND
  vt_HDC
  vt_COLORREF
  vt_HANDLE
  vt_HINSTANCE
  vt_WNDCLASSEX
  vt_HFONT
  vt_VARIANT
END ENUM
'*********************************
CONST vt_VarMin    =  2
CONST vt_VarMax    =  vt_VARIANT
'*********************************
ENUM
  mt_ProcessSetCommand
  mt_FuncSubDecC_Dec
  mt_FuncSubDecC_Dec2
  mt_Opts
  mt_Opts2
  mt_Opts3
  mt_OverLoad
  mt_OverLoad2
  mt_FuncSubx1
  mt_FuncSubx2
END ENUM
CONST fprintf = ReDirectFPrint
'******************************
'   User Defined Type Support
'******************************
CONST MaxElements   =  128
CONST MaxTypes      =  512
CONST MaxLocalVars  =  512
CONST MaxGlobalVars = 4096 'max size 233000
'******************************
'   Library Support
'******************************
CONST MaxLib        = 64 ' max no of libraries
'***********************
'  Bracket Handling
'***********************
CONST c_SglQt = 39
CONST c_DblQt = 34
CONST c_LPar  = 40
CONST c_RPar  = 41
CONST c_Komma = 44
CONST c_LtBkt = 91
CONST c_RtBkt = 93
'**************************************************************
' Runtime Library support
' These are used to keep Modifiers of BCX source code
' from accidently changing certain output lines of
' code that are used by the $PROJECT/Library code
'**************************************************************
CONST BCX_STR_RUNTIME          = "Runtime Functions"
CONST BCX_STR_MAIN_PROG        = "Main Program"
CONST BCX_STR_SYS_VARS         = "System Variables"
CONST BCX_STR_STD_MACROS       = "Standard Macros"
CONST BCX_STR_STD_PROTOS       = "Standard Prototypes"
CONST BCX_STR_USR_PROCS        = "User Subs and Functions"
CONST BCX_STR_USR_VARS         = "User Global Variables"
CONST BCX_STR_USR_PROTOS       = "User Prototypes"
CONST BCX_STR_USR_CONST        = "User Defined Constants"
CONST BCX_STR_USR_TYPES        = "User Defined Types, Classes (CPP Mode), And Unions"
'**************************************************************
TYPE functionParse
  NumArgs
  CommaPos[128]
END TYPE
'**************************************************************
'               These need to always stay in sync
'**************************************************************
CONST VarTypes$ = "%$#!@¦"
SET VarTypeLookup[] AS CHAR PTR
  "int", "int", "char *", "double", "float", "FILE *", "long double"
END SET
'**************************************************************
TYPE ARGTYPE
  Arg$
  ArgType
END TYPE

TYPE ProtoStore
  Prototype$[2048] AS CHAR
  Condition$[512]  AS CHAR
  CondLevel        AS INTEGER
END TYPE

TYPE Element
  ElementType      AS INTEGER
  ElementID        AS INTEGER
  ElementDynaPtr   AS INTEGER
  ElementName$[64] AS CHAR
END TYPE

TYPE UserTypeDefs
  TypeofDef             AS INTEGER
  EleCnt                AS INTEGER
  Elements[MaxElements] AS Element
  VarName$[64]          AS CHAR
END TYPE

TYPE VarInfo
  VarLine         AS INTEGER
  VarType         AS INTEGER
  VarDef          AS INTEGER
  VarPntr         AS INTEGER
  VarSF           AS INTEGER
  VarExtn         AS INTEGER
  VarCondLevel    AS INTEGER
  VarEmitFlag     AS INTEGER
  VarConstant     AS INTEGER
  VarName$[64]    AS CHAR
  VarDim$[128]    AS CHAR
  VarModule[300]  AS CHAR
  VarCondDef[128] AS CHAR
END TYPE

TYPE VARCODE
  VarNo     AS INTEGER
  Method    AS INTEGER
  IsPtrFlag AS INTEGER
  Header$
  Proto$
  Functype$
  StaticOut$
  Token$
  AsToken$
END TYPE

'*************************************************************************
'                            GLOBAL VARIABLES
'*************************************************************************
GLOBAL  NoRT
GLOBAL  ByrefVars$[1024]
GLOBAL  ByrefCnt
GLOBAL  CurLine$
GLOBAL  gLinesWritten
GLOBAL  LoopLocalVar[256]
GLOBAL  LoopLocalCnt
GLOBAL  GlobalVarCnt
GLOBAL  BaseTypeDefsCnt[16]
GLOBAL  TypeDefsCnt
GLOBAL  LocalVarCnt
GLOBAL  LocalDynArrCount ' Local Dynamic String Array Stack Counter
GLOBAL  LocalDynaCnt ' Queue Stack Counter
GLOBAL  GlobalDynaCnt
GLOBAL  Modules$[256] ' array of source filenames
GLOBAL  ModuleNdx ' index of source files
GLOBAL  ModuleLineNos[256] ' line no in source files, uses ModuleNdx also
GLOBAL  FPtrNdx ' Controls $Include Files
GLOBAL  FPtr             [256] AS FILE ' Controls $Include Files
GLOBAL  Stk$            [4096] ' Parse array
GLOBAL  ProtoType       [1024] AS ProtoStore ' C prototype declarations of user func's
GLOBAL  SrcStk$          [128] ' used in parsing single line if-THEN-else
GLOBAL  SplitStk$        [128] ' used in parsing ":" separated lines
GLOBAL  SplitCnt
GLOBAL  SplitCur
GLOBAL  SrcTmp$ ' used for storing string to use as parameter to Parse()
GLOBAL  CaseStk$         [256] ' Stack For Nested "Select Case" variable
GLOBAL  CaseElseFlag     [256] ' Set if Select Case contains a Case Else
GLOBAL  Entry$           [256] ' Controls the $OnEntry
GLOBAL  Xit$             [256] ' Controls the $OnExit
GLOBAL  LocalDynArrName$ [256] ' Queues LOCAL dynamic string arrays
GLOBAL  GlobalDynaStr$   [256]
GLOBAL  DynaStr$         [256] ' Queues Dynamic strings in SUBS/FUNCTIONS
GLOBAL  StartSub$        [32] ' user's startup code subs
GLOBAL  StartNdx ' index for StartSub$
GLOBAL  ExitSub$         [32] ' user's exit code subs
GLOBAL  ExitNdx ' index for ExitSub$
GLOBAL  Library$         [MaxLib] ' stores libraries to used
GLOBAL  GlobalVarHash[MaxGlobalVars]
GLOBAL  GlobalVars[MaxGlobalVars] AS VarInfo ' Holds global variables
GLOBAL  LocalVars[MaxLocalVars]   AS VarInfo ' Holds local variables
GLOBAL  TypeDefs [MaxTypes]       AS UserTypeDefs ' Holds typedefs
GLOBAL  VarCode                   AS VARCODE
GLOBAL  UmQt 'Handles quoted lines split with a contination _
GLOBAL  LD_FLAGS$ ' Holds Linker Flags for GUI Toolkits/OS (GTK, OSX, WXWIDGETS)
'************************************************************************************************
GLOBAL  Accelerator$
GLOBAL  CallType$ ' Calling convention cdecl, stdcall ...
GLOBAL  CaseFlag
GLOBAL  CaseVar$
GLOBAL  Cmd$
GLOBAL  Compiler$
GLOBAL  CmdLineConst$
GLOBAL  CmdLineFileOut$
GLOBAL  CurrentFuncType
GLOBAL  DimType$
GLOBAL  DllDecl$  [800][512] AS CHAR
GLOBAL  DllCnt
GLOBAL  Loadlibs$ [128][512] AS CHAR
GLOBAL  LoadLibsCnt
GLOBAL  Elapsed AS SINGLE
GLOBAL  EndOfProgram
GLOBAL  EntryCnt
GLOBAL  ErrFile
GLOBAL  szFile$
GLOBAL  Filnam$
GLOBAL  ForceMainToFunc
GLOBAL  Funcname$
GLOBAL  Handl$
GLOBAL  HFileCnt
GLOBAL  HFiles$[128]
GLOBAL  HFile$
GLOBAL  InConditional
GLOBAL  InIfDef$
GLOBAL  Indent
GLOBAL  InFunc
GLOBAL  InMain
GLOBAL  IsCallBack
GLOBAL  TurboSize
GLOBAL  UseCProto
GLOBAL  InTypeDef
GLOBAL  IsAuto
GLOBAL  NoTypeDeclare
GLOBAL  IsDim
GLOBAL  IsExported
GLOBAL  IsRegister
GLOBAL  IsStatic
GLOBAL  IsStdFunc
GLOBAL  IsLocal
GLOBAL  IsRaw
GLOBAL  IsApple
GLOBAL  KillCFile
GLOBAL  Keyword1$
GLOBAL  LastCmd
GLOBAL  LinesRead
GLOBAL  Linker$
GLOBAL  Lookup$
GLOBAL  MakeDLL
GLOBAL  Ndx
GLOBAL  NoMain
GLOBAL  NoDllMain
GLOBAL  OkayToSend
GLOBAL  Op$
GLOBAL  OptionBase
GLOBAL  OutfileClone$
GLOBAL  PassOne
GLOBAL  ProtoCnt
GLOBAL  Pusher
GLOBAL  Quiet ' no output to screen, for use with BCX Builder
GLOBAL  ReDirect
GLOBAL  SaveOutfileNum AS FILE
GLOBAL  Scoot$
GLOBAL  ShowStatus
GLOBAL  SrcCnt
GLOBAL  SrcFlag
GLOBAL  TrcFlag
GLOBAL  TestForBcxIni
GLOBAL  FileIn$
GLOBAL  FileOut$
GLOBAL  FileErr$
GLOBAL  T$
GLOBAL  Test
GLOBAL  Statements
GLOBAL  TestState
GLOBAL  Tipe$
GLOBAL  TranslateSlash
GLOBAL  TypeName$[16]
GLOBAL  UseCpp
GLOBAL  UseFlag '= true
'/** 2010/11/30 Added to support NameSpace - AIR 88/
GLOBAL	InNameSpace
'/***** 2010-12-01 Added to support Abstract Classes -AIR *****/
GLOBAL	Use_Virtual
GLOBAL  vproc$

GLOBAL  UseStdCall
GLOBAL  UseLCaseTbl
GLOBAL  Var$
GLOBAL  XitCount
GLOBAL  Z$
GLOBAL ConstLastDef$
'**********************
GLOBAL  Use_AnsiToWide
GLOBAL  Use_Asc
GLOBAL  Use_AppExeName
GLOBAL  Use_AppExePath
GLOBAL  Use_Boolstr
GLOBAL  Use_Bor
GLOBAL  Use_Band
GLOBAL  Use_Bnot
GLOBAL  Use_BcxSplitPath
GLOBAL  Use_Bin
GLOBAL  Use_Bin2dec
GLOBAL  Use_Osx ' Used for OSX build - AIR
GLOBAL  Use_Cvd
GLOBAL  Use_Cvld
GLOBAL  Use_Cvi
GLOBAL  Use_Cvl
GLOBAL  Use_Cvs
GLOBAL  Use_Chr
GLOBAL  Use_Cdbl
GLOBAL  Use_Cldbl
GLOBAL  Use_Csng
GLOBAL  Use_Clear
GLOBAL  Use_Cbool
GLOBAL  Use_Cint
GLOBAL  Use_Clng
GLOBAL  Use_Cls
GLOBAL  Use_Color
GLOBAL  Use_Command
GLOBAL  Use_ContainedIn
GLOBAL  Use_Console
GLOBAL  Use_CopyFile
GLOBAL  Use_Static
GLOBAL  Use_Crlf
GLOBAL  Use_Curdir
GLOBAL  Use_Del
GLOBAL  Use_Download
GLOBAL  Use_Dynacall
GLOBAL  Use_DynamicA
GLOBAL  Use_Embed
GLOBAL  Use_Enclose
GLOBAL  Use_Environ
GLOBAL  Use_EnumFile
GLOBAL  Use_Eof
GLOBAL  Use_Exist
GLOBAL  Use_ExitCode
GLOBAL  Use_Extract
GLOBAL  Use_LoadFile
GLOBAL  Use_FillArray
GLOBAL  Use_Findfirst
GLOBAL  Use_Findnext
GLOBAL  Use_FindInType
GLOBAL  Use_Fint
GLOBAL  Use_Fix
GLOBAL  Use_FileLocked
GLOBAL  Use_Frac
GLOBAL  Use_Fracl
GLOBAL  Use_Freefile
GLOBAL  Use_Get
GLOBAL  Use_GetCh
GLOBAL  Use_GenFree
GLOBAL  Use_Gosub
GLOBAL  Use_Gtk  ' GTK SUPPORT - AIR
GLOBAL  Use_Glib ' GLIB SUPPORT - AIR
GLOBAL  Use_Hex
GLOBAL  Use_Hex2Dec
GLOBAL  Use_Iif
GLOBAL  Use_Imod
GLOBAL  Use_Inkey
GLOBAL  Use_InkeyD
GLOBAL  Use_Ins
GLOBAL  Use_Instr
GLOBAL  Use_Inchr
GLOBAL  Use_Isptr
GLOBAL  Use_iReplace
GLOBAL  Use_IRemove
GLOBAL  Use_Instrrev
GLOBAL  Use_Join
GLOBAL  Use_Keypress
GLOBAL  Use_Lcase
GLOBAL  Use_Ldouble
GLOBAL  Use_Left
GLOBAL  Use_Like
GLOBAL  Use_Lineinput
GLOBAL  Use_Loc
GLOBAL  Use_Locate
GLOBAL  Use_Lof
GLOBAL  Use_Lpad
GLOBAL  Use_Ltrim
GLOBAL  Use_Mcase
GLOBAL  Use_Mid
GLOBAL  Use_Midstr
GLOBAL  Use_Mkd
GLOBAL  Use_Mkld
GLOBAL  Use_Mki
GLOBAL  Use_Mkl
GLOBAL  Use_Mks
GLOBAL  Use_Min
GLOBAL  Use_Max
GLOBAL  Use_Now
GLOBAL  Use_Numqsortdint
GLOBAL  Use_Numqsortaint
GLOBAL  Use_Numqsortdfloat
GLOBAL  Use_Numqsortafloat
GLOBAL  Use_Numqsortddouble
GLOBAL  Use_Numqsortadouble
GLOBAL  Use_Idxqsort
GLOBAL  Use_IdxqsortSt
GLOBAL  Use_PtrqsortSt
GLOBAL  Use_Oct
GLOBAL  Use_Overloaded
GLOBAL  Use_OSVersion
GLOBAL  Use_Pause
GLOBAL  Use_PeekStr
GLOBAL  Use_Put
GLOBAL  Use_QBColor
GLOBAL  Use_Randomize
GLOBAL  Use_Rec
GLOBAL  Use_RecCount
GLOBAL  Use_Remain
GLOBAL  Use_Remove
GLOBAL  Use_Repeat
GLOBAL  Use_Replace
GLOBAL  Use_Reverse
GLOBAL  Use_Right
GLOBAL  Use_Rpad
GLOBAL  Use_Rnd
GLOBAL  Use_Exp
GLOBAL  Use_Retain
GLOBAL  Use_Round
GLOBAL  Use_Rtrim
GLOBAL  Use_Run
GLOBAL  Use_Scan
GLOBAL  Use_Inputbuffer
GLOBAL  Use_SearchPath
GLOBAL  Use_StrUpLow
GLOBAL  Use_Shell

'$HEADER
'static int Use_Shell;
'$HEADER

GLOBAL  Use_Sgn
GLOBAL  Use_SingleFile
GLOBAL  Use_Space
GLOBAL  Use_Split
GLOBAL  Use_DSplit
GLOBAL  Use_StartupCode
GLOBAL  Use_Stristr
GLOBAL  Use_StrStr
GLOBAL  Use_Str
GLOBAL  Use_Strl
GLOBAL  Use_Str_Cmp
GLOBAL  Use_Strim
GLOBAL  Use_String
GLOBAL  Use_Strptr
GLOBAL  Use_Strqsorta
GLOBAL  Use_Strqsortd
GLOBAL  Use_Strtoken
GLOBAL  Use_DynStrqsorta
GLOBAL  Use_DynStrqsortd
GLOBAL  Use_Swap
GLOBAL  Use_Sysdir
GLOBAL  Use_SysStr
GLOBAL  Use_sziif
GLOBAL  Use_Tally
GLOBAL  Use_Tempdir
GLOBAL  Use_TempFileName
GLOBAL  Use_Threads
GLOBAL  Use_Time
GLOBAL  Use_Timer
GLOBAL  Use_Trim
GLOBAL  Use_Turbo
GLOBAL  Use_Ubound
GLOBAL  Use_Ucase
GLOBAL  Use_Using
GLOBAL  Use_VChr
GLOBAL  Use_Verify
GLOBAL  Use_Val
GLOBAL  Use_Vall
GLOBAL  Use_WideToAnsi
GLOBAL  Use_Wx  ' WxWidgets GUI Support -AIR
GLOBAL  Use_WxC     '/***** 2010-11-24 WxWidgets CONSOLE ONLY support -AIR *****/
GLOBAL  Use_Ctor    '/***** 2010-11-17 Added to support Constructor/Destructor Method Syntax - AIR *****/
GLOBAL  Use_Instat  '/***** 2010-12-08 Added to support INSTAT keyword - AIR *****/
GLOBAL	Use_Socket  '/***** 2010-12-10  Added to support Sockets -AIR *****/
GLOBAL  Use_IOS     '/***** 2010-12-17  Added to support IOS -AIR *****/
GLOBAL  Use_RegEx  '/***** 2013-06-26 New REGEX Keywords -AIR *****/
'*********************
'GLOBAL  S1$    '  "%s"
'GLOBAL  S2$    '  "%s%s"


'GLOBAL  U1$

'********************************
' PB Compatible String Constants
'********************************

GLOBAL  Use_BEL
GLOBAL  Use_BS
GLOBAL  Use_CR
GLOBAL  Use_DDQ
GLOBAL  Use_DQ
GLOBAL  Use_EOF
GLOBAL  Use_ESC
GLOBAL  Use_FF
GLOBAL  Use_LF
GLOBAL  Use_NUL
GLOBAL  Use_SPC
GLOBAL  Use_TAB
GLOBAL  Use_VT

'*********************
'**************************************************************
GLOBAL  prcFile$ ' translated subs and functions
GLOBAL  udtFile$ ' translated User Defined Types
GLOBAL  datFile$ ' translated DATA statements
GLOBAL  cstFile$ ' translated CONSTants
GLOBAL  ovrFile$ ' translated overloaded subs and functions
GLOBAL  hdrFile$ ' user specified .h directives
GLOBAL  setFile$ ' translated GLOBAL set statements
GLOBAL  enuFile$ ' user GLOBAL enum blocks

SET VarConst[2][8] AS CHAR
  "",
  "const "
END SET

SET VarStorage[6][18] AS CHAR
  "static ",
  "extern ",
  "",
  "static volatile ",
  "extern volatile ",
  "volatile "
END SET
'*************************************************************************
'                              CODE BEGINS
'*************************************************************************
FUNCTION main(ARGC AS INTEGER, ARGV AS PCHAR PTR)
  GLOBAL  szTmp$    * 1048576 'This is a problem, cannot exceed 2047+1 or bad things *WILL* happen.
  GLOBAL  Src$      * 1048576 'This is a problem, cannot exceed 2047+1 or bad things *WILL* happen.
  GLOBAL  AbortSrc$ * 1048576 'This must be at least the size of Src$
  GLOBAL  WarnMsg$  * 32767   'This must be MORE than the size of Src$
  GLOBAL  RmLibs$   * 32767   ' libraries to remove
  LOCAL   bitz as INTEGER     ' is OS 32/64 bit
  ProtoCnt               =   0 ' Prototypes counter
  TranslateSlash         =  TRUE ' Default TO changing "\" TO "\\"
  OkayToSend             =  TRUE
  Use_SingleFile         =  TRUE
  Use_StartupCode        =  FALSE
  StartNdx               =  0
  Use_ExitCode           =  FALSE
  ExitNdx                =  0
  HFile$                 =  ""
  CmdLineFileOut$        =  ""
  RmLibs$                =  ""
  InMain                 =  TRUE
  TestState              =  FALSE
  CmdLineConst$          = ""
  '/***** 64BIT Check -AIR *****/
  bitz=SIZEOF(long)*8

  '**************************************************************************
  '  $IF __APPLE__
  '    Use_Carbon = TRUE
  '    SPRINT LD_FLAGS$, "-framework Carbon"
  ''    LD_FLAGS = "-framework Carbon"
  '  $ENDIF

  IF COMMAND$ = "" THEN
    !#if defined (__APPLE__)
    PRINT "MBC4:  Ported to Mac OSX by Armando Rivera (c) 2009-2018"
    !#else
    PRINT "MBC4: Based on Linux BCX by Mike Henning (c) 2009"
    PRINT "(c) 2009-2018 Armando Rivera with additional code (c) 2009 John Jacques",LF$
    !#endif

    PRINT "Version ", Version$, "  Compiled with ";
    $IF __BCPLUSPLUS__
      PRINT "Borland C++"
    $ELSEIF __BORLANDC__
      PRINT "Borland C"
    $ELSEIF __POCC__
      PRINT "Pelles C"
    $ELSEIF __GNUG__
      PRINT "GNU G++"
    $ELSE
      PRINT "Unknown"
    $ENDIF


    '/***** 64BIT Check -AIR *****/
    IF bitz=64 THEN
      PRINT
      PRINT "********************"
      PRINT "** 64 BIT VERSION **"
      PRINT "********************",LF$
    END IF

    PRINT " Usage: ";APPEXENAME$;" infile [.bas] [options]"
    PRINT " [-c] Generate C++ Compatible code"
    PRINT " [-d] DEFINE a constant ... ex. ";APPEXENAME$;" MyFile -D:MyConst[=SomeValue]"
    PRINT " [-e] Write ERRORS to BCX.ERR file"
    PRINT " [-f] Output FILENAME... ex. ";APPEXENAME$;" MyFile -f:/MyFiles/MyFile.c"
    PRINT " [-k] KILL the generated BCX generated 'C' file"
    PRINT " [-o] OUTPUT a copy of the generated C file to STDOUT"
    PRINT " [-q] QUIET - No output to screen during translation"
    PRINT " [-s] Show STATUS of translation by line number"
    PRINT " [-w] Enable WARNINGS during translation"
    PRINT " [-t] TURBO Mode ON w/optional size ... ex. ";APPEXENAME$;" MyFile -t[:1024]"
    PRINT " [-u] Turn UNICODE Support ON"
    CALL FREEGLOBALS
    END
  END IF
  Quiet        =  FALSE
  FOR INTEGER i = 2 TO ARGC-1
    IF INSTR(LCASE$(ARGV$[i]),"-f") THEN CmdLineFileOut$ = MID$(ARGV$[i],4)
    IF INSTR(LCASE$(ARGV$[i]),"-d") THEN CmdLineConst$ = CmdLineConst$ + MID$(ARGV$[i],4) + CHR$(1)
    IF LCASE$(ARGV$[i]) = "-c" THEN UseCpp      = TRUE
    IF LCASE$(ARGV$[i]) = "-e" THEN ErrFile     = TRUE
    IF LCASE$(ARGV$[i]) = "-q" THEN Quiet       = TRUE
    IF LCASE$(ARGV$[i]) = "-k" THEN KillCFile   = TRUE
    IF LCASE$(ARGV$[i]) = "-o" THEN ReDirect    = TRUE
    IF LCASE$(ARGV$[i]) = "-s" THEN ShowStatus  = TRUE
    IF LCASE$(ARGV$[i]) = "-w" THEN TestState   = TRUE
    IF INSTR(LCASE$(ARGV$[i]),"-t") THEN
      Use_Turbo = TRUE
      TurboSize = VAL(MID$(ARGV$[i],4))
      IF TurboSize <> 0 THEN
        IF (TurboSize & (TurboSize-1)) <> 0 THEN
          TurboSize = 512
          Warning("Invalid $Turbo size - defaulting to 512")
        END IF
      ELSE
        TurboSize = 512
      END IF
    END IF
  NEXT
  '****************************** [ Announce Program ] ********************************
  IF ShowStatus THEN CLS
  IF NOT Quiet THEN
    CLS

    PRINT "MBC Version ", Version$
    !#if defined (__APPLE__)
    IsApple = TRUE
    PRINT "MBC4:  Ported to Mac OSX by Armando Rivera (c) 2009-2018",LF$
    !#else
    PRINT "MBC4: Based on Linux BCX by Mike Henning (c) 2009"
    PRINT "(c) 2009-2018 Armando Rivera with additional code (c) 2009 John Jacques",LF$
    !#endif


    '/***** 64BIT Check -AIR *****/
    IF bitz=64 THEN
      PRINT
      PRINT "********************"
      PRINT "** 64 BIT VERSION **"
      PRINT "********************",LF$
    END IF
  END IF
  '************************************************************************************
  IF INCHR(COMMAND$(1),".") THEN 'Is there a period in the filename?
    Cmd$ = COMMAND$(1) ' yes, allow ANY extension
  ELSE 'no period in filename
    IF EXIST(COMMAND$(1) + ".bas") THEN ' check for .bas
      Cmd$ = COMMAND$(1) + ".bas"
    ELSEIF EXIST(COMMAND$(1) + ".BAS") THEN ' check for .BAS
      Cmd$ = COMMAND$(1) + ".BAS"
    END IF
  END IF
  IF NOT EXIST (Cmd$) THEN
    PRINT
    PRINT "FILE NOT FOUND: ",COMMAND$(1)
    CALL FREEGLOBALS 'file not found, exit gracefully
    END
  END IF

  FileIn$ = Cmd
  IF CmdLineFileOut$ = "" THEN
    '/***** 2018-12-09  Changed default output extension to ".cc" -AIR *****/
    FileOut$ = LEFT$(Cmd$, INSTRREV(Cmd$,".",0)-1) + ".cc"
  ELSE
    FileOut$ = CmdLineFileOut$
  END IF
  FileErr$ = LEFT$(Cmd$, INSTRREV(Cmd$,".",0)-1) + ".ERR"
  IF EXIST(FileErr$) THEN
    KILL FileErr$
  END IF
  '*******************************************************
  prcFile$ = TEMPFILENAME$(TEMPDIR$,"prc")
  udtFile$ = TEMPFILENAME$(TEMPDIR$,"udt")
  datFile$ = TEMPFILENAME$(TEMPDIR$,"dat")
  cstFile$ = TEMPFILENAME$(TEMPDIR$,"cst")
  ovrFile$ = TEMPFILENAME$(TEMPDIR$,"ovr")
  hdrFile$ = TEMPFILENAME$(TEMPDIR$,"hdr")
  setFile$ = TEMPFILENAME$(TEMPDIR$,"set")
  'resFile$ = TEMPFILENAME$(TEMPDIR$,"res")
  enuFile$ = TEMPFILENAME$(TEMPDIR$,"enu")
  '**************************************************************************
  OPEN FileIn$  FOR INPUT  AS SourceFile
  OPEN FileOut$ FOR OUTPUT AS FP2 ' THE FINAL C FILE <<<<<<<<
  '**************************************************************************
  Outfile = FP2 ' Outfile = FP3 when in a SUB or FUNCTION
  '**************************************************************************
  OPEN prcFile$ FOR OUTPUT AS FP3 ' Temp File FOR Storing User Functions
  OPEN udtFile$ FOR OUTPUT AS FP4 ' Temp File FOR Storing User Def Types
  OPEN datFile$ FOR OUTPUT AS FP5 ' Temp File FOR Storing User "Data"
  OPEN cstFile$ FOR OUTPUT AS FP6 ' Temp File FOR Storing User CONST
  OPEN hdrFile$ FOR OUTPUT AS FP7 ' Temp File FOR Storing User .H files
  OPEN ovrFile$ FOR OUTPUT AS FP8 ' Temp File FOR Storing overloaded funcs
  OPEN setFile$ FOR OUTPUT AS FP9 ' Temp File FOR Storing GLOBAL SET Vars
  'OPEN resFile$ FOR OUTPUT AS FP10 ' Temp File FOR Storing User .rc files
  OPEN enuFile$ FOR OUTPUT AS FP11 ' Temp File FOR Storing User global enums
  '*************************************************************************
  ModuleNdx = 1
  Modules$[ModuleNdx] = FileIn$ ' store the current module name
  ModuleLineNos[ModuleNdx] = 0
  '**************************************************************************
  CALL EmitProlog
  CALL ClearIfThenStacks
  CALL EmitCmdLineConst
  CALL AddGlobal("G_argv",vt_PCHAR, 0,"",1,0,0,0)
  CALL AddGlobal("G_argc",vt_INTEGER, 0,"",0,0,0,0)
  '*****************
  '  The Main LOOP
  '*****************
  ReadSrcLine:
  '*****************
  WHILE NOT EOF(SourceFile) OR SplitCnt
    IF SplitCnt = 0 THEN 'Process separated lines before
      LINE INPUT SourceFile,Src$ 'getting next line from file.
      ModuleLineNos[ModuleNdx]++
      CALL StripCode(Src$) 'Remove spaces, tabs, comments
      IF *Src = 0 THEN ITERATE
      IF JoinLines(Src$) = 1 THEN ITERATE 'Join continuation lines " _"
      IF INCHR(Src$,"[") THEN CALL BracketHandler(Src$,0) 'Fix Brackets
      IF SplitLines(Src$) THEN Src$ = SplitStk$[++SplitCur] 'Split statements separated by
    ELSE                                                    'colons and single line if/then
      Src$ = SplitStk$[++SplitCur]
    END IF
    IF SplitCur = SplitCnt THEN SplitCur = SplitCnt = 0
    IF *Src = 0 THEN ITERATE
    AbortSrc$ = Src$
    '***************************************************************************
    '    ReProcess:  ' label added for use with BCX User-Defined PreProcessor
    '             so line could be changed and be run back thru BCX from start
    '***************************************************************************
    IF TrcFlag AND InFunc THEN
      IF NOT iMatchLft(Src$,"$trace") THEN
        IF NOT iMatchLft(Src$,"end ") AND INSTR(Src$,"FUNCTION",0,1) = 0 THEN
          FPRINT Outfile,"// [", TRIM$(Modules$[ModuleNdx]), " - ", TRIM$(STR$(ModuleLineNos[ModuleNdx])), "] ", Src$
          Z$ = TRIM$(Modules$[ModuleNdx])
          Z$ = REPLACE$(Z$,"\\","\\\\")
          Z$ = " " + Z$ + " - " + STR$(ModuleLineNos[ModuleNdx]) + " \\n"
          Z$ = "printf(" + ENC$(Z$) + ");"
          FPRINT Outfile,Z$
        END IF
      END IF
    END IF
    '******************************
    IF SrcFlag THEN
      IF NOT iMatchLft(Src$,"$sourc") AND *Src <> 33 THEN '33 = !
        FPRINT Outfile,"// [", TRIM$(Modules$[ModuleNdx]), " - ", TRIM$(STR$(ModuleLineNos[ModuleNdx])), "] ", Src$
      END IF
    END IF
    '******************************
    IF ShowStatus THEN
      LOCATE 2,1,0
      PRINT "Processing Module: ", TRIM$(Modules$[ModuleNdx]), " - Line:", ModuleLineNos[ModuleNdx]
    END IF
    '******************************
    IF Src[0] = 33 THEN 'Test for ! symbol -- inline C
      Src[0] = 32
      FPRINT Outfile,Src$
      Src$ = ""
    END IF
    '******************************
    IF *Src$ = 0 THEN ITERATE
    DIM RAW di
    di = Directives()
    IF di = 0 THEN GOTO ReadNextLine
    IF di = 1 THEN GOTO ReadSrcLine
    IF iMatchLft(Src$,"set ") THEN
      CALL ProcessSetCommand(0)
    END IF
    IF iMatchLft(Src$,"sharedset ") THEN
      CALL ProcessSetCommand(1)
    END IF
    PassOne = TRUE
    '****************
    '    CallParse:
    '****************
    CALL CheckParQuotes
    IF SpecialCaseHandler(Src$) THEN ITERATE
    CALL Parse(Src$)
    PassOne = FALSE
    IF Ndx THEN
      CALL Emit
    END IF
    '****************
    ReadNextLine:
    '****************
  WEND
  '***************************************************
  ' END OF MAIN LOOP -- All Source code has been read
  '***************************************************
  ' everything from here below must be stopped from
  ' executing more than once
  IF CmdLineConst$ > "" THEN
    Src$ = "CONST " + CmdLineConst$
    CALL Parse (Src$)
    CALL Emit
    CmdLineConst$ = ""
  END IF
  IF TestForBcxIni = FALSE THEN
    TestForBcxIni = TRUE
    szFile$ = CURDIR$ + "\\bcx.ini"
    IF NOT EXIST(szFile$) THEN
      szFile$ = APPEXEPATH$ + "bcx.ini"
    END IF
    IF EXIST(szFile$) THEN
      CALL PushFileIO
      OPEN szFile$ FOR INPUT AS SourceFile
      Modules$[++ModuleNdx] = szFile$
      ModuleLineNos[ModuleNdx] = 0
      GOTO ReadSrcLine
    END IF
  END IF


  FLUSH (Outfile) '*************************************
  IF FPtrNdx THEN '  Pop out the $Include File Handles
    CALL PopFileIO '  and close them in sequence until
    GOTO ReadSrcLine '  we end up back in the main file
  END IF '*************************************


  IF Use_GenFree AND GlobalDynaCnt THEN
    CALL MakeFreeGlobals
  END IF
  CALL ExportInternalConst
  CALL EmitEpilog
  CALL CloseAll
  CALL AddProtos
  CALL DeclareVariables
  CALL AddFuncs
  CALL CloseAll
  '***************************
  '   Final Disk Gymnastics
  '***************************
  IF UseCpp AND CmdLineFileOut$ = "" THEN
    szTmp$ = EXTRACT$(FileOut$,".") + ".cpp"
    KILL szTmp$
    RENAME FileOut$, szTmp$
    FileOut$ = szTmp$
  END IF
  '/***** 2015-07-03  Added to support OSX Cocoa -AIR *****/
  IF Use_Osx AND CmdLineFileOut$ = "" THEN
    szTmp$ = EXTRACT$(FileOut$,".") + ".mm"
    KILL szTmp$
    RENAME FileOut$, szTmp$
    FileOut$ = szTmp$
  END IF

  OPEN  FileOut$ FOR INPUT  AS FP1
  OPEN  hdrFile$ FOR INPUT  AS FP2
  OPEN "$temp$"  FOR OUTPUT AS FP3
  GLOBAL DoCountLines
  DoCountLines = TRUE
  FPRINT FP3,"// *********************************************************************"
  FPRINT FP3,"//   Created with MBC (V) ", Version$, "Ported to OSX by Armando Rivera"
  FPRINT FP3,"//   Ported from BCX32 BASIC To C/C++ Translator (V) 5.12"
  FPRINT FP3,"//   BCX (c) 1999 - 2018 by Kevin Diggins"
  FPRINT FP3,"//   LinuxBC (c) 2009 by Mike Henning "
  FPRINT FP3,"//   MBC (c) 2009 - 2018 by Armando Rivera"
  FPRINT FP3,"// *********************************************************************"
  FPRINT FP3,"//   Translated for compiling with the g++ Compiler"
  IF UseCpp THEN
    FPRINT FP3,"//   g++ -Wformat -D_FORTIFY_SOURCE=2 -Wno-write-strings $FILE$.cpp -ldl -o $FILE$"
  ELSE
    '/***** 2018-12-09  Changed default output extension to ".cc" -AIR *****/
    FPRINT FP3,"//   g++ -Wformat -D_FORTIFY_SOURCE=2 -Wno-write-strings $FILE$.cc -ldl -o $FILE$"
  END IF
  FPRINT FP3,"// *********************************************************************"

IF NoRT=FALSE THEN

  '********* CARBON OSX SUPPORT *********
  IF Use_Osx THEN
    FPRINT FP3,"#import <Cocoa/Cocoa.h>"
  END IF
  '**************************************

  '********* WX WIDGETS SUPPORT *********
  /***** 2010-11-24 Added WxC FOR WX CONSOLE Apps -AIR *****/
  IF Use_Wx OR Use_WxC THEN
    FPRINT FP3,"// WXWIDGETS HEADER FILES //"
    FPRINT FP3,"#include <wx/wx.h>"
    FPRINT FP3,"#include <wx/process.h>"
    FPRINT FP3,"#include <wx/txtstrm.h>"
    FPRINT FP3,"#include <wx/msgdlg.h>"
    FPRINT FP3,"#include <wx/stdpaths.h>"
    FPRINT FP3,"#include <wx/event.h>"
    FPRINT FP3,"// ******************* //"
    FPRINT FP3,""
  END IF
  '**************************************

  '*********** GTK  SUPPORT ***********
  IF Use_Gtk THEN
    FPRINT FP3,"#include <gtk/gtk.h>"
  END IF
  '**************************************

  '*********** GLIB  SUPPORT **********
  IF Use_Glib THEN
    FPRINT FP3,"#include <glib.h>"
  END IF
  '**************************************
  FPRINT FP3,"#include <stdbool.h>"
  FPRINT FP3,"#include <ctype.h>"
  FPRINT FP3,"#include <math.h>"
  FPRINT FP3,"#include <stdio.h>"
  FPRINT FP3,"#include <iostream>"
  FPRINT FP3,"#include <fstream>"
  FPRINT FP3,"#include <string.h>"
  FPRINT FP3,"#include <stddef.h>"
  FPRINT FP3,"#include <stdlib.h>"
  FPRINT FP3,"#include <setjmp.h>"
  FPRINT FP3,"#include <time.h>"
  FPRINT FP3,"#include <stdarg.h>"
  FPRINT FP3,"#include <dirent.h>"
  FPRINT FP3,"#include <sys/types.h>"
  FPRINT FP3,"#include <sys/stat.h>"
  FPRINT FP3,"#include <sys/wait.h>"
  FPRINT FP3,"#include <unistd.h>"
  FPRINT FP3,"#include <dlfcn.h>"
  !#if defined (__APPLE__)
    FPRINT FP3,"#include <libproc.h>"
  !#endif

  IF UseCpp THEN
    FPRINT FP3,"#include <iostream>"
    FPRINT FP3,"#include <fstream>"
  END IF

	'/***** 2010-12-08  Added to support INSTAT Keyword-AIR *****/
  IF Use_Instat THEN
		Use_Keypress = true
    FPRINT FP3,"#include <fcntl.h>"
  END IF

  '/***** 2010-12-08  Changed to fix minor issue -AIR *****/
  IF Use_Keypress THEN
    FPRINT FP3,"#include <term.h>"
  END IF

  '/***** 2010-12-10  Added to support Sockets -AIR *****/
  if Use_Socket then
    FPRINT FP3,"#include <sys/socket.h>"
    FPRINT FP3,"#include <netinet/in.h>"
    FPRINT FP3,"#include <netdb.h>"
    FPRINT FP3,"#include <errno.h>"
    FPRINT FP3,"#include <arpa/inet.h>"
  end if

  '/***** 2013-06-26 New REGEX supprt -AIR *****/
  IF Use_RegEx then
    FPRINT FP3,"#include <regex.h>"
  END IF

  FPRINT FP3,""


  CALL EmitCompilerDefines
  END IF 'NoRT
  WHILE NOT EOF(FP2)
    LINE INPUT FP2,Z$ ' Read from BCX.HDR
    FPRINT FP3,Z$ ' Write to $temp$
  WEND
  DIM RAW Lastlyne$
  Lastlyne$ = ""
  WHILE NOT EOF(FP1)
    STATIC bMainOut = 0
    LINE INPUT FP1,Z$ ' Read from "C" FileOut$
    IF iMatchLft(Lastlyne$, "#if") THEN
      IF iMatchLft(Z$, "#endif") THEN
        Lastlyne$ = ""
        ITERATE
      ELSE
        FPRINT FP3, Lastlyne$
      END IF
    END IF
    Lastlyne$ = Z$
    IF iMatchLft(Lastlyne$, "#if") THEN ITERATE
    FPRINT FP3,Z$ ' Write to $temp$
    IF bMainOut THEN ITERATE
    IF LEFT$(LTRIM$(Z$),8)  = "int main" THEN
      WHILE TRIM$(Z$) <> "{"
        LINE INPUT FP1,Z$
        FPRINT FP3,Z$
      WEND
      IF Use_StartupCode THEN
        FPRINT FP3,Scoot$,"int BCX_SUCode = BCX_StartupCode_();  // execute user's startup code"
      END IF
      IF Use_ExitCode THEN
        FPRINT FP3,Scoot$,"int BCX_EXCode = BCX_ExitCode_();     // Prepare for user's exit code"
      END IF
      bMainOut++
    END IF
  WEND
  DoCountLines = FALSE
  CALL CloseAll
  KILL hdrFile$
  KILL FileOut$
  '***************************************************************
  RENAME "$temp$", FileOut$ ' This is our FINAL "C" File
  '***************************************************************
  '*******************************
  IF ShowStatus THEN LOCATE 2,1,1
  '*******************************
  IF NOT Quiet THEN
    INCR LinesRead, ModuleLineNos[1]
    Elapsed! = ROUND((float)clock()/(float)CLOCKS_PER_SEC,2)
    PRINT "[Lines In:" ; LinesRead ; "] [Lines Out:" ; gLinesWritten ; "] ";
    PRINT "[Statements:" ; Statements ; "] [Time:" ; Elapsed! ; " sec's]"
    Z$ = "BCX translated " + REMOVE$(FileIn$," ") + " to " + REMOVE$(FileOut$," ")
    PRINT Z$
  END IF
  CALL PostProcess
  IF WarnMsg$ > "" THEN
    PRINT "Warnings! :", CRLF$, WarnMsg$
  END IF
  IF KillCFile THEN KILL FileOut$ ' -k switch issued ?
  CALL FREEGLOBALS
END FUNCTION ' Function main  (END of BCX Translator)
SUB EmitCmdLineConst()
  IF CmdLineConst$ > "" THEN
    RAW Ftmp AS FILE
    FPRINT FP7, ""
    FPRINT FP7, "// ***************************************************"
    FPRINT FP7, "// Commandline Defines"
    FPRINT FP7, "// ***************************************************"
    FPRINT FP7, ""
    ' Save FILE Ptr to SourceFile
    Ftmp = FP6
    ' Direct output to HeaderFile
    FP6 = FP7
    FOR INTEGER i = 1 TO TALLY( CmdLineConst$, CHR$(1) )
      Src$ = STRTOKEN$( CmdLineConst$, CHR$(1), i )
      IF Src$ = "" THEN EXIT
      Src$ = "CONST " + Src$ ' CmdLineConst$
      CALL Parse (Src$)
      CALL Emit
    NEXT
    CmdLineConst$ = ""
    ' Restore Ptr to SourceFile
    FP6 = Ftmp
    FPRINT FP7, ""
  END IF
END SUB 'EmitCmdLineConst
SUB EmitCompilerDefines()
  FPRINT FP3,""
  FPRINT FP3,"// ***************************************************"
  FPRINT FP3,"// Compiler Defines"
  FPRINT FP3,"// ***************************************************"

  FPRINT FP3,"  #define C_EXPORT extern ", ENC$("C")
  FPRINT FP3,"  #define C_IMPORT extern ", ENC$("C")
  FPRINT FP3,""
  FPRINT FP3,"#ifndef stat"
  FPRINT FP3,"  #define lstat stat"
  FPRINT FP3,"#endif"
  FPRINT FP3,"#ifndef _fcloseall"
  FPRINT FP3,"  #define _fcloseall _fcloseall"
  FPRINT FP3,"#endif"
  FPRINT FP3,"#ifndef HWND"
  FPRINT FP3,"  #define HWND GHWND"
  FPRINT FP3,"#endif"
  FPRINT FP3,"#ifndef MAX_PATH"
  FPRINT FP3,"  #define MAX_PATH 2048"
  FPRINT FP3,"#endif"
  FPRINT FP3,"#ifndef CALLBACK"
  FPRINT FP3,"  #define CALLBACK"
  FPRINT FP3,"#endif"
  FPRINT FP3,"typedef unsigned int HINSTANCE;"
  'FPRINT FP3, typedef const char CCHAR;"
  FPRINT FP3,"typedef void* LPVOID;"
  FPRINT FP3,"typedef char* PCHAR;"
  FPRINT FP3,"typedef unsigned char BYTE;"
  FPRINT FP3,"typedef unsigned int  UINT;"
  FPRINT FP3,"typedef unsigned char UCHAR;"
  FPRINT FP3,"typedef unsigned char* PUCHAR;"
  FPRINT FP3,"typedef unsigned long ULONG;"
  FPRINT FP3,"typedef unsigned long* ULONG_PTR;"
  FPRINT FP3,"typedef unsigned long DWORD;"
  FPRINT FP3,""
  FPRINT FP3,"#ifndef TRUE"
  FPRINT FP3,"  #define TRUE 1"
  FPRINT FP3,"#endif"
  FPRINT FP3,""
  FPRINT FP3,"#ifndef FALSE"
  FPRINT FP3,"  #define FALSE 0"
  FPRINT FP3,"#endif"
  IF NOT Use_Osx THEN
  	FPRINT FP3,"#define BOOL bool"
  END IF
  FPRINT FP3,""
  IF UseCpp THEN
    FPRINT FP3,"#define println(a)  (std::cout << a << std::endl)"
    'FPRINT FP3,"#define stdstring  std::string"
    'FPRINT FP3,"#define stdfile  std::fstream"
    FPRINT FP3,"  typedef std::string CSTRING;"
    FPRINT FP3,"  typedef std::fstream CFILE;"
  END IF

END SUB 'EmitCompilerDefines

SUB MakeFreeGlobals
  Src$ = "SUB FreeGlobals"
  PassOne = 1
  CALL Parse(Src$)
  CALL Emit
  WHILE GlobalDynaCnt
    FPRINT Outfile,"  ", GlobalDynaStr$[GlobalDynaCnt]
    GlobalDynaCnt--
  WEND
  Src$ = "END SUB"
  PassOne = 1
  CALL Parse(Src$)
  CALL Emit
END SUB ' MakeFreeGlobals
SUB ProcessSetCommand(GS)
  DIM RAW i, ii, j, SetString=0
  DIM RAW CVar$
  DIM RAW vt
  LOCAL SaveFP AS FILE
  SaveFP = Outfile
  IF NOT InFunc THEN Outfile = FP9 ' Global context
  IF INCHR(Src$,"$") AND TALLY(Src$,"[") >1 THEN
    Src$ = STRIM$(Src$)
    IREMOVE "as string" FROM Src$
    IREMOVE "as char"   FROM Src$
    CONCAT(Src$," AS char")
  END IF
  CONCAT(Src$,"=")
  PassOne = 1
  CALL Parse(Src$)
  Tipe$ = ""
  FOR i = 1 TO Ndx
    IF iMatchWrd(Stk$[i],"as") THEN
      Tipe$ = Stk$[i+1]
      Stk$[i]   = ""
      Stk$[i+1] = ""
      EXIT FOR
    END IF
  NEXT
  IF Tipe$ = "" THEN
    szTmp$ = Stk$[2]
    SetString = DataType(Stk$[2])
    j = SetString
    VarCode.Method% = mt_ProcessSetCommand
    VarCode.Token$ = szTmp$
    VarCode.VarNo% = j
    CALL GetVarCode(&VarCode)
    IF GS THEN
      FPRINT Outfile,Scoot$,REMOVE$(VarCode.StaticOut$,"static ");
    ELSE
      FPRINT Outfile,Scoot$,VarCode.StaticOut$;
    END IF
    DIM RAW lszTmp as string
    lszTmp$ = ""
    CVar$ = Clean$(Stk$[2])
    CALL ValidVar(CVar$)
    vt = DataType(Stk$[2])
    FOR i = 3 TO Ndx
      CONCAT (lszTmp$, Stk$[i])
    NEXT
    IF vt = vt_STRVAR AND lszTmp$ <> "" THEN
      CONCAT (lszTmp$, "[65535]")
    END IF
    IF NOT InFunc THEN
      CALL AddGlobal(CVar$, vt, 0,lszTmp$,0,0,0,1)
    ELSE
      CALL AddLocal(CVar$, vt, 0,lszTmp$,0,0,1)
    END IF
  ELSE
    CVar$ = Clean$(Stk$[2])
    IF GS THEN
      FPRINT Outfile,Scoot$ ; Tipe$;" ";CVar$;
    ELSE
      FPRINT Outfile,Scoot$ ; "static ";Tipe$;" ";CVar$;
    END IF
    DIM RAW DimType$
    DIM RAW IsPointer
    DIM RAW id
    DimType$ = REMOVE$(Tipe$,"*") ' *mh - 3/9/09
    GetTypeInfo(Tipe$, &IsPointer, &id, &vt)
    IF vt = vt_STRVAR THEN
      CONCAT(DimType$, "[65535]")
    END IF
    IF NOT InFunc THEN
      CALL AddGlobal(CVar$, vt, id, DimType$,IsPointer,0,0,1)
    ELSE
      CALL AddLocal(CVar$, vt, id, DimType$,IsPointer,0,1)
    END IF
  END IF
  i = 2
  j = 0
  DO
    i++
    IF Stk$[i]= "=" THEN j = 1
    IF SetString = vt_STRVAR AND j = 1 THEN
      FPRINT Outfile,"[65535]=";
    ELSE
      FPRINT Outfile,Stk$[i];
    END IF
    IF Stk$[i]= "=" THEN EXIT LOOP
    IF i = Ndx THEN EXIT LOOP
  LOOP
  FPRINT Outfile,""
  FPRINT Outfile,"{"
  WHILE NOT EOF(SourceFile)
    LINE INPUT SourceFile,Src$
    ModuleLineNos[ModuleNdx]++
    CALL StripCode(Src$)
    IF JoinLines(Src$) = 1 THEN ITERATE
    PassOne = TRUE
    CALL XParse(Src$)
    PassOne = FALSE
    CALL TokenSubstitutions
    IF iMatchLft(Src$,"end ") THEN EXIT LOOP
    IF LEN (Src$) THEN
      FPRINT Outfile,"  ";
      FOR ii = 1 TO Ndx
        FPRINT Outfile, Clean$(Stk$[ii]);
      NEXT ii
      FPRINT Outfile,""
    END IF
  WEND
  FPRINT Outfile,"};\n"
  Src$ = ""
  Outfile = SaveFP
END SUB 'ProcessSetCommand


FUNCTION Directives
  DIM RAW lszTmp$, i
  DIM RAW COutputFile$
  '       = #          = $
  IF *Src = 35 OR *Src = 36 THEN
    Z$ = RTRIM$(LCASE$(LEFT$(Src$,6)))
    '******************************
    SELECT CASE Z$
      '****************************
      CASE "$proje"
      '****************************
      NoRT=TRUE
      Src$ = ""
      EXIT FUNCTION
     '****************************
      CASE "$accel"
      '****************************
      CALL XParse(Src$)
      Accelerator$ = REMOVE$(Stk$[2],DQ$)
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$bcxve"
      '****************************
      Src$ = TRIM$(MID$(Src$,12))
      REMOVE DQ$ FROM Src$
      IF LCASE$(Version$) < LCASE$(Src$) THEN
        Abort (CRLF$ + "Your Translator needs updating." + CRLF$ + _
        "This program " + ENC$(Modules$[ModuleNdx]) + " requires BCX Version: " + Src$ + " or later." + CRLF$ + CRLF$)
      ELSE
        PRINT ""
        PRINT "Program written for BCX Version ", Src$
        PRINT ""
      END IF
      EXIT FUNCTION
      '****************************
      CASE "$compi"
      '****************************
      PassOne = 1
      CALL XParse(Src$)
      PassOne = 0
      Compiler$ = Stk$[2]
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$execo"
      '****************************
      LOCAL SrcExt$
      PassOne = 1
      CALL XParse(Src$)
      PassOne = 0
      XitCount++

      IF UseCpp THEN
        SrcExt$=".cpp"
      '/***** 2015-07-03  Added to support OSX Cocoa -AIR *****/
      ELSEIF Use_Osx THEN
      	SrcExt$=".mm"
      ELSE
      '/***** 2018-12-09  Changed default output extension to ".cc" -AIR *****/
        SrcExt$=".cc"
      END IF

      IF MakeDLL THEN
        Xit$[XitCount]= "g++  -Wformat -D_FORTIFY_SOURCE=2 -Wno-write-strings $FILE$" + SrcExt$ + " -ldl " + LD_FLAGS$ + SPC$ + Stk$[2] + " -o lib$FILE$.so"
        SrcExt$ = ""
        Src$ = ""
        EXIT FUNCTION
      END IF

      '/***** 2010-12-17  Added to support IOS -AIR *****/
      IF Use_IOS THEN
        LOCAL IOS_COMPILER$
        IOS_COMPILER$ = "/Developer/Platforms/iPhoneOS.platform/Developer/usr/bin/g++"

        IF LEN(Stk$[2])>0 THEN
          Xit$[XitCount]= IOS_COMPILER$ & "  -Wformat -D_FORTIFY_SOURCE=2 -Wno-write-strings $FILE$" + SrcExt$ + " -ldl " + LD_FLAGS$ + SPC$ + Stk$[2] + " -o $FILE$"
        ELSE
          Xit$[XitCount]= IOS_COMPILER$ & "  -Wformat -D_FORTIFY_SOURCE=2 -Wno-write-strings $FILE$" + SrcExt$ + " -ldl " + LD_FLAGS$ + " -o $FILE$"
        END IF
        SrcExt$ = ""
        Src$ = ""
        EXIT FUNCTION
      END IF

      IF LEN(Stk$[2])>0 THEN
        Xit$[XitCount]= "g++  -Wformat -D_FORTIFY_SOURCE=2 -Wno-write-strings $FILE$" + SrcExt$ + " -ldl " + LD_FLAGS$ + SPC$ + Stk$[2] + " -o $FILE$"
      ELSE
        Xit$[XitCount]= "g++  -Wformat -D_FORTIFY_SOURCE=2 -Wno-write-strings $FILE$" + SrcExt$ + " -ldl " + LD_FLAGS$ + " -o $FILE$"
      END IF
      SrcExt$ = ""
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$exest"
      '****************************
        PassOne = 1
        CALL XParse(Src$)
        PassOne = 0
        XitCount++
        IF IsApple then
            Xit$[XitCount]= "strip $FILE$"
        ELSE
            Xit$[XitCount]= "strip -s -R .comment -R .note -R .note.ABI-tag $FILE$"
        END IF
        Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$genfr"
      '****************************
      Use_GenFree = TRUE
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$osx"
      Use_Osx = TRUE
      '/***** 2015-07-03 Changed Carbon to Cocoa, added Objc flag -AIR *****/
      '/***** 2018-12-12 Added ARC flag -AIR *****/
      LD_FLAGS$ = JOIN$(2, LD_FLAGS$," -fobjc-arc -framework Cocoa")
      EXIT FUNCTION

      '/***** 2010-12-17  Added to support IOS -AIR *****/
      CASE "$ios"
      !#if !defined __APPLE__
        Abort(CRLF$+"The $IOS Directive REQUIRES an Apple OSX Operating System"+CRLF$)
      !#endif
      Use_IOS = TRUE
      PassOne = 1
      CALL XParse(Src$)
      PassOne = 0

      LD_FLAGS$ = JOIN$(2, LD_FLAGS$," -arch armv6 -arch armv7 -mthumb -isysroot /Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS4.2.sdk -framework Foundation -framework CoreFoundation")

      EXIT FUNCTION

      CASE "$gtk"
      Use_Gtk = TRUE
      LD_FLAGS$ = JOIN$(2, LD_FLAGS$," $(pkg-config --libs --cflags gtk+-2.0)")
      EXIT FUNCTION

      '/***** 2018-12-12  Added to support passing ldflags -AIR *****/
      CASE "$ldfla"
      LD_FLAGS$ = JOIN$(2, LD_FLAGS$, REMAIN$(Src$," "))
      EXIT FUNCTION 

      '****************************
      /***** 2010-11-24 Added WxC FOR WX CONSOLE Apps -AIR *****/
      '****************************
      CASE "$wxc"
      Use_WxC = UseCpp = NoMain = TRUE
      LD_FLAGS$ = JOIN$(2, LD_FLAGS$, " $(wx-config --libs --cppflags)")
      EXIT FUNCTION
      '****************************
      CASE "$wx"
      Use_Wx = UseCpp = NoMain = TRUE
      LD_FLAGS$ = JOIN$(2, LD_FLAGS$, " $(wx-config --libs --cppflags)")
      EXIT FUNCTION
      '****************************
      CASE "$glib"
      Use_Glib = TRUE
      LD_FLAGS$ = JOIN$(2, LD_FLAGS$," $(pkg-config --libs --cflags glib-2.0)")
      EXIT FUNCTION
      '****************************
      CASE "$noini"
      '****************************
      Src$ = ""
      TestForBcxIni = TRUE
      EXIT FUNCTION
      '****************************
      CASE "$linke"
      '****************************
      PassOne = 1
      CALL XParse(Src$)
      PassOne = 0
      Linker$ = Stk$[2]
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$onexi"
      '****************************
      PassOne = 1
      CALL XParse(Src$)
      PassOne = 0
      XitCount++
      Xit$[XitCount]= Stk$[2]
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$onent"
      '****************************
      PassOne = 1
      CALL XParse(Src$)
      PassOne = 0
      EntryCnt++
      Entry$[EntryCnt]= Stk$[2]
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$pack","$pack("
      '****************************
      'Src$ = EXTRACT$(Src$,"'") ' allow Basic comments
      Src$ = MID$(Src$,6)
      FPRINT FP4,"#pragma pack ",LTRIM$(Src$)
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$nodll"
      '****************************
      NoDllMain = TRUE
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$pelle"
      '****************************
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$stdca"
      '****************************
      UseStdCall = TRUE
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$iprin"
      '****************************
      IF INSTR(LCASE$(Src$),"_on") THEN
        TranslateSlash = TRUE
      ELSE
        TranslateSlash = FALSE
      END IF
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$nomai"
      '****************************
      NoMain = TRUE
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$test"
      '****************************
      TestState = NOT TestState
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$typed"
      '****************************
      FPRINT FP7,"typedef " + REMAIN$(Src$," "),";"
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$resou"
      '****************************
      LOCAL resAlias$,resFile$
      Use_Embed = TRUE
      PassOne = 1
      CALL XParse(Src$)
      PassOne = 0
      EntryCnt++
      Entry$[EntryCnt]= "ld -r -b binary "+ Stk$[2] +" -o "+Stk$[2]+".o"
      REPLACE "." WITH "_" IN Stk$[2]
      resFile$=REMOVE$(Stk$[2],DQ$)
      resAlias$=REMOVE$(Stk$[3],DQ$)
      CALL AddGlobal("_binary_"+resFile$+"_start",vt_INTEGER, 0,"",0,0,1,0)
      CALL AddGlobal("_binary_"+resFile$+"_size",vt_INTEGER, 0,"",0,0,1,0)
      Src$="CONST " +resAlias$ + "= &_binary_"+resFile$+"_start"
      CALL Parse(Src$)
      CALL Emit
      Src$="CONST " +resAlias$ + "_SIZE = (int)&_binary_"+resFile$+"_size"
      CALL Parse(Src$)
      CALL Emit
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$turbo"
      '****************************
      Src$ = LTRIM$(MID$(Src$,7))
      IF *Src$ <> 0 THEN
        TurboSize = VAL(Src$)
        IF (TurboSize & (TurboSize-1)) <> 0 THEN
          TurboSize = 512
          Warning("Invalid $Turbo size - defaulting to 512")
        END IF
      ELSE
        TurboSize = 512
      END IF
      Use_Turbo = TRUE
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$sourc"
      '****************************
      SrcFlag = NOT SrcFlag
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$fssta"
      '****************************
      Use_Static = NOT Use_Static
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$trace"
      '****************************
      TrcFlag = NOT TrcFlag
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$inclu","$modul"
      '****************************
      DIM RAW orgfileName$
      szFile$ = TRIM$(REMOVE$(MID$(Src$,9),DQ$))
      orgfileName$ = szFile$
      IF LEFT$(szFile$,1) = "<" THEN
        szFile$ = MID$(szFile$, 2, LEN(szFile$)-2)
        szFile$ = ENVIRON$("BCXLIB") + szFile$
      END IF
      IF NOT EXIST(szFile$) THEN
        szFile$ = BcxSplitPath$(szFile$, FNAME|FEXT)
        szFile$ = BcxSplitPath$(FileIn$, FDRV|FPATH) + szFile$
      END IF
      IF NOT EXIST(szFile$) THEN Abort("Unable to locate " + orgfileName$)
      CALL PushFileIO
      OPEN szFile$ FOR INPUT AS SourceFile
      Modules$[++ModuleNdx] = szFile$
      ModuleLineNos[ModuleNdx] = 0
      FUNCTION = 1
      '****************************
      ' Beginning of Temporary Directives
      ' in support of C++ Classes
      '****************************
      CASE "$try"
      '****************************
      FPRINT Outfile,"try {"
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$throw"
      szTmp$ = MID$(Src$,8)
      IF szTmp$ = "" THEN szTmp$ = ENC$("An Exception has occured!")
      FPRINT Outfile,Scoot$,"throw " + szTmp$ + ";"
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$catch"
      '****************************
      szTmp$ = MID$(Src$,8)
      IF szTmp$ = "" THEN szTmp$ = "char *str"
      FPRINT Outfile,"}"
      FPRINT Outfile,"catch (" + szTmp$ + ")" ' catch (char *str)
      FPRINT Outfile,"{"
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$endtr"
      '****************************
      FPRINT Outfile,"}"
      Src$ = ""
      EXIT FUNCTION
      '/** 2010/11/30 Added -AIR **/
      '****************************
      CASE "$endna"
      '****************************
      InNameSpace--
      CALL BumpDown
      FPRINT Outfile,Scoot$,"}"
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$names"
      '****************************
      '// 2010/11/30 REMOVED $NAMESPACE
      Abort("$NAMESPACE/$ENDNAMESPACE have been removed from this version.  Use NAMESPACE / END NAMESPACE instead.")
      '~ UseCpp = TRUE
      '~ szTmp$ = MID$(Src$,INCHR(Src$," ")+1)
      '~ FPRINT Outfile,"namespace " + LTRIM$(szTmp$)
      '~ FPRINT Outfile,"{"
      '~ '/** 2010/11/30 Added -AIR **/
      '~ InNameSpace++
      '~ CALL BumpUp
      '~ Src$ = ""
      '~ EXIT FUNCTION
      '****************************
      CASE "$usena"
      '****************************
      UseCpp = TRUE
      szTmp$ = MID$(Src$, INCHR(Src$, " ") + 1)
      IF RIGHT$(TRIM$(szTmp$),1) <> ";" THEN
        FPRINT Outfile,"using namespace ", szTmp$, ";"
      ELSE
        FPRINT Outfile,"using namespace ", szTmp$
      END IF
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$class"
      '****************************
      '/** 2010/11/30 REMOVED $CLASS KEYWORD/FUNCTIONALITY -AIR **/
      Abort("$CLASS has been removed from this version.  Use CLASS instead.")
      '~ LOCAL tmpSrc$
      '~ STATIC BeenHere
      '~ UseCpp = TRUE
      '~ szTmp$ = MID$(Src$, INCHR(Src$, " ") + 1)
      '~ IF NOT BeenHere THEN
      '~ BeenHere++
      '~ FPRINT FP4,"#ifndef __cplusplus"
      '~ FPRINT FP4,"  #error A C++ compiler is required"
      '~ FPRINT FP4,"#endif"
      '~ FPRINT FP4,""
      '~ END IF
      '~ '--------- BEGIN INSERT ----------------
      '~ IF INSTR(szTmp$,"inherits",0,1) THEN IREPLACE "inherits" WITH ": public" IN szTmp$
      '~ FPRINT FP4,"class ";szTmp$;" {"
      '~ '--------- END INSERT ----------------
      '~
      '~ '************
      '~ WHILE NOT iMatchLft(Src$,"$endclass")
      '~ IF EOF(SourceFile) THEN Abort ("$Class Without $EndClass")
      '~ LINE INPUT SourceFile,Src$
      '~ tmpSrc$=TRIM$(Src$)
      '~ ModuleLineNos[ModuleNdx]++
      '~ 'StripCode(Src$)
      '~ '--------- BEGIN INSERT ----------------
      '~ IF iMatchLft(Src$,"$endclass") THEN
      '~ FPRINT FP4,"};"
      '~ '--------- END INSERT ----------------
      '~ EXIT LOOP
      '~ END IF
      '~ '        IF iMatchLft(tmpSrc$,"sub") THEN IREPLACE "sub" with "void" in Src$
      '~ '        IF iMatchLft(tmpSrc$,"public:") OR iMatchLft(tmpSrc$,"private:") OR iMatchLft(tmpSrc$,"DECLARE_EVENT_TABLE()") OR iMatchLft(tmpSrc$,"'") OR LEN(tmpSrc$)=0 THEN
      '~ '          FPRINT FP4,Src$
      '~ '        ELSE
      '~ '          FPRINT FP4,Src$;";"
      '~ '        END IF
      '~ WEND
      '~ Src$ = ""
      '~ tmpSrc$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$inter"
      '****************************
      STATIC BeenHere
      UseCpp = TRUE
      szTmp$ = REMAIN$(Src$, SPC$)
      IF NOT BeenHere THEN
        BeenHere++
        FPRINT FP4,"#ifndef __cplusplus"
        FPRINT FP4,"  #error A C++ compiler is required"
        FPRINT FP4,"#endif"
      END IF
      FPRINT FP4,"interface ";szTmp$;" {"   '<--------------
      DO  '//; changed/added by whatsup
        IF EOF(SourceFile) THEN Abort ("$Interface Without $EndInterface")
        LINE INPUT SourceFile,Src$
        ModuleLineNos[ModuleNdx]++
        'StripCode(Src$)
        IF iMatchLft(LTRIM$(Src$),"$endinterface") THEN
          EXIT LOOP
        END IF
        FPRINT FP4,Src$
      LOOP
      FPRINT FP4,"}";TRIM$(Src$ + 13);";"   '<--------------  '//; changed/added by whatsup
      '//;Src$ = ""
      EXIT FUNCTION
      '****************************
      ' END of Temporary Directives
      ' in support of C++ Classes
      '****************************
      CASE "$comme"
      '****************************
      Src$ = ""
      DO
        IF EOF(SourceFile) THEN Abort ("Unbalanced $Comment")
        LINE INPUT SourceFile,Src$
        ModuleLineNos[ModuleNdx]++
        CALL StripTabs
        IF iMatchLft(LTRIM$(Src$),"$comment") THEN EXIT LOOP
        FPRINT Outfile,"// ",Src$
      LOOP
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$ccode"
      '****************************
      Src$ = ""
      DO
        IF EOF(SourceFile) THEN Abort ("Unbalanced $Ccode")
        LINE INPUT SourceFile,Src$
        ModuleLineNos[ModuleNdx]++
        CALL StripTabs
        IF iMatchLft(LTRIM$(Src$) ,"$ccode") THEN
          IF SrcFlag THEN 'comments seem to interfere with C line continuations '\'
            FPRINT Outfile,"// [", TRIM$(Modules$[ModuleNdx]), " - ", _
            TRIM$(STR$(ModuleLineNos[ModuleNdx])), "] End of $CCODE Block"
          END IF
          EXIT LOOP
        END IF
        FPRINT Outfile,RTRIM$(Src$)
      LOOP
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$cprot"
      '****************************
      FastLexer(Src$, SPC$, "!")
      IF iMatchWrd(Stk$[2], "!") THEN
        ProtoCnt++
        ProtoType[ProtoCnt].Prototype$ = REMAIN$(Src$, "!")
        ProtoType[ProtoCnt].Condition$ = ""
        ProtoType[ProtoCnt].CondLevel  = 0
      ELSE
        i = iMatchNQ(Src$, "function")
        IF i = 0 THEN
          i = iMatchNQ(Src$, "sub")
        END IF
        IF i THEN
          Src$ = "c_declare " + MID$(Src$, i)
        ELSE
          i = iMatchNQ(Src$, "$cproto")
          Src$ = "c_declare function " + MID$(Src$, i+7)
        END IF
        UseCProto = TRUE
        FUNCTION = 2
      END IF
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$heade"
      '****************************
      Src$ = ""
      FPRINT FP7, "// ***************************************************"
      FPRINT FP7, ""
      DO
        IF EOF(SourceFile) THEN Abort ("Unbalanced $Header")
        LINE INPUT SourceFile,Src$
        ModuleLineNos[ModuleNdx]++
        CALL StripTabs
        Src$ = TRIM$(Src$)
        IF iMatchLft(Src$,"$heade") THEN EXIT LOOP
        FPRINT FP7,Src$
      LOOP
      Src$ = ""
      FPRINT FP7, ""
      EXIT FUNCTION
      '****************************
      CASE "$asm"
      '****************************
      IF NOT iMatchLft(Src$,"$asm") THEN
        Abort ("Unknown metastatement: " + Src$)
      END IF
      Src$ = ""
      DO
        IF EOF(SourceFile) THEN Abort ("Unbalanced $Asm")
        LINE INPUT SourceFile,Src$
        ModuleLineNos[ModuleNdx]++
        IF SrcFlag THEN
          FPRINT Outfile,"// ",Src$
        END IF
        CALL StripTabs
        Src$ = TRIM$(Src$)
        DIM meta_asm_loop
        DIM meta_asm_comment_present AS bool
        DIM Src_Len
        Src_Len = LEN(Src$)
        meta_asm_comment_present = FALSE
        FOR meta_asm_loop = 0 TO Src_Len
          '******************************************
          '   Extracts both the Basic Single Quote
          '   and the Assembly Semicolon
          '******************************************
          IF Src[meta_asm_loop] = 39 OR Src[meta_asm_loop] = 59 THEN
            lszTmp$ = RIGHT$(Src$,Src_Len - meta_asm_loop - 1)
            Src[meta_asm_loop] = 0
            meta_asm_comment_present = TRUE
            EXIT LOOP
          END IF
        NEXT
        Src$ = TRIM$(Src$)
        IF iMatchLft(Src$,"$asm") THEN EXIT LOOP
        REPLACE "$" WITH "0x" IN Src$
        IREPLACE "&h" WITH "0x" IN Src$
        IF Src$ <> "" THEN
          Src$ = "_asm(" + ENC$(Src$) + CHR$(1)
          IF meta_asm_comment_present THEN
            Src$ = Src$ + TAB$ + "//" + lszTmp$
          END IF
          SrcTmp$ = Src$
          FPRINT Outfile,"#if !defined( __POCC__ ) && !defined (__cplusplus )"
          REPLACE CHR$(1) WITH ")" IN Src$
          FPRINT Outfile,Src$
          FPRINT Outfile,"#else"
          REPLACE "_asm(" WITH "__asm{" IN SrcTmp$
          REPLACE CHR$(1) WITH "}" IN SrcTmp$
          FPRINT Outfile,REMOVE$(SrcTmp$,DQ$)
          FPRINT Outfile,"#endif"
        END IF
      LOOP
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "#inclu"
      '****************************
      '/***** 2010-11-18 Fixed this to always emit lowercase "#include" -AIR *****/
      Src$ = REMOVE$(LCASE$(Src$),"#include")
      Src$ = TRIM$(Src$)
      FPRINT FP7, "#include ",Src$
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$libra"
      '****************************
      'Src$ = EXTRACT$(Src$,"'")   ' allow comments
      REPLACE "\\" WITH "\\\\" IN Src$
      Src$ = REMOVE$(LCASE$(Src$),"$library")
      Src$ = TRIM$(Src$)
      AddLibrary(Src$)
      Src$ = ""
      EXIT FUNCTION
      '****************************
      CASE "$nolib"
      '****************************
      'Src$ = EXTRACT$(Src$,"'")   ' allow comments
      REPLACE "\\" WITH "\\\\" IN Src$
      Src$ = REMOVE$(LCASE$(Src$),"$nolibrary")
      RemoveLibrary(Src$)
      Src$ = ""
      EXIT FUNCTION
    END SELECT
  END IF
  FUNCTION = 2
END FUNCTION ' Directives
FUNCTION SubVarType(TokenNum)
  DIM RAW k, j = 0
  k = CheckLocal(Stk$[TokenNum], &j)
  IF k = vt_CHAR THEN
    IF *LocalVars[j].VarDim$ <> ASC("[") AND LocalVars[j].VarPntr = 0 THEN
      k = vt_INTEGER
    ENDIF
  ELSEIF k = vt_UNKNOWN THEN
    k = CheckGlobal(Stk$[TokenNum], &j)
    IF k = vt_CHAR THEN
      IF *GlobalVars[j].VarDim$ <> ASC("[") AND GlobalVars[j].VarPntr = 0 THEN
        k = vt_INTEGER
      ENDIF
    ENDIF
  END IF
  j = ASC(RIGHT$(Stk$[TokenNum],1))
  SELECT CASE k
    CASE vt_STRVAR, vt_CHAR
    IF j <> 36 THEN
      CONCAT (Stk$[TokenNum], "$")
    END IF
    CASE vt_INTEGER
    IF j <> 37 THEN
      CONCAT (Stk$[TokenNum], "%")
    END IF
    CASE vt_SINGLE
    IF j <> 33 THEN
      CONCAT (Stk$[TokenNum], "!")
    END IF
    CASE vt_DOUBLE
    IF j <> 35 THEN
      CONCAT (Stk$[TokenNum], "#")
    END IF
    CASE vt_LDOUBLE
    IF j <> 166 THEN
      CONCAT (Stk$[TokenNum], "¦")
    END IF
  END SELECT
  FUNCTION = k
END FUNCTION ' SubVarType
FUNCTION PrintWriteFormat$(DoWrite)
  DIM RAW Stak[128] AS ARGTYPE
  DIM RAW Frmat$
  DIM RAW Arg$
  DIM RAW ZZ$
  DIM RAW Cast$
  DIM RAW NewLineFlag = 0
  DIM RAW Argcount = 0
  DIM RAW i = 0
  DIM RAW j = 0
  DIM RAW k = 0
  Frmat$ = ""
  Arg$   = ""
  ZZ$    = ""
  IF Stk$[Ndx]= ";" THEN
    NewLineFlag = TRUE
    Ndx--
  END IF
  IF Ndx = 1 THEN GOTO PrintWriteLabel
  Stak[1].ArgType = -1
  j = 2
  WHILE j <= Ndx
    IF Clean$(Stk$[j]) <> "BCX_DynaCall" THEN
      i = SubVarType(j)
      IF Stak[Argcount+1].ArgType = -1 THEN
        IF i = vt_CHAR OR i = vt_STRVAR OR i = vt_INTEGER OR i = vt_SINGLE OR i = vt_DOUBLE OR i = vt_LDOUBLE THEN
          Stak[Argcount+1].ArgType = i
        END IF
      END IF
      IF Stk$[j] = "(" THEN
        i = 0
        DO
          IF Stk$[j] = "(" THEN i++
          IF Stk$[j] = ")" THEN i--
          CONCAT (Arg$,Stk$[j])
          j++
        LOOP UNTIL i <= 0 OR j >= Ndx
      END IF
      IF Stk$[j] = "[" THEN
        i = 0
        DO
          IF Stk$[j] = "[" THEN i++
          IF Stk$[j] = "]" THEN i--
          CONCAT (Arg$,Stk$[j])
          j++
          IF Stk$[j] = "["  AND i = 0 THEN ITERATE
        LOOP UNTIL i <= 0 OR j >= Ndx
      END IF
      IF Stk$[j] = ";" OR Stk$[j] = "," OR Stk$[j] = "&" THEN
        Argcount++
        Stak[Argcount].Arg$ = Arg$
        Stak[Argcount+1].ArgType = -1
        Arg$ = ""
        j++
      ELSE
        CONCAT (Arg$,Stk$[j])
        j++
      END IF
    ELSE
      CONCAT(Arg$,Stk$[j])
      j++
    END IF
  WEND
  Argcount++
  Stak[Argcount].Arg$ = Arg$
  Arg$ = ""
  FOR i = 1 TO Argcount
    j = Stak[i].ArgType
    IF j = -1 THEN
      ZZ$ = EXTRACT$(Stak[i].Arg$,"(")
      j = DataType(ZZ$)
    END IF
    SELECT CASE j
      CASE vt_STRLIT, vt_STRVAR, vt_CHAR
      IF DoWrite THEN
        Frmat$ = Frmat$ + "\\" + DQ$ + "%s" + "\\" + DQ$ + ","
      ELSE
        CONCAT (Frmat$,"%s")
      END IF
      IF LEFT$(ZZ$, 12) = "BCX_DynaCall" THEN
        Arg$ = Arg$ + ",(char*)" + Stak[i].Arg$
      ELSE
        Arg$ = Arg$ + "," + Stak[i].Arg$
      END IF
      CASE vt_INTEGER, vt_DECFUNC
      IF DoWrite THEN
        Frmat$ = Frmat$ + "%d" + ","
      ELSE
        CONCAT (Frmat$,"%d")
      END IF
      Arg$ = Arg$ + ",(int)" + Stak[i].Arg$
      CASE vt_SINGLE
      IF DoWrite THEN
        Frmat$ = Frmat$ + "%.7G" + ","
      ELSE
        CONCAT (Frmat$,"%.7G")
      END IF
      Arg$ = Arg$ + ",(float)" + Stak[i].Arg$
      CASE vt_DOUBLE,vt_NUMBER
      IF DoWrite THEN
        Frmat$ = Frmat$ + "%.15G" + ","
      ELSE
        CONCAT (Frmat$,"%.15G")
      END IF
      Arg$ = Arg$ + ",(double)" + Stak[i].Arg$
      CASE vt_LDOUBLE
      IF DoWrite THEN
        Frmat$ = Frmat$ + "%.19LG" + ","
      ELSE
        CONCAT (Frmat$,"%.19LG")
      END IF
      Arg$ = Arg$ + ",(LDOUBLE)" + Stak[i].Arg$
      CASE ELSE
      IF ASC(Stak[i].Arg$) = ASC("(") THEN
        ZZ$ = ""
        CONCAT(Arg$,",")
        DO
          k = INSTR(Stak[i].Arg$,")")
          Cast$ = MID$(Stak[i].Arg$ ,1 ,k)
          Stak[i].Arg$ = TRIM$(MID$(Stak[i].Arg$,k+1))
          IREPLACE "char*"   WITH "char *" IN Cast$
          IREPLACE "integer" WITH "int" IN Cast$
          IREPLACE "single"  WITH "float" IN Cast$
          IREPLACE "ldouble" WITH "LDOUBLE" IN Cast$
          IF ZZ$ = "" THEN
            IF Cast$ = "(char *)" OR Cast$ = "(int)" OR Cast$ = "(float)" OR Cast$ = "(double)" OR Cast$ = "(LDOUBLE)" THEN
              ZZ$ = Cast$
            ELSE
              ZZ$ = "(double)"
              Cast$ = ZZ$ + Cast$
            END IF
            RemoveAll(ZZ$,"()")
            IREPLACE "char *"  WITH "%s"      IN ZZ$
            IREPLACE "int"     WITH "%d"     IN ZZ$
            IREPLACE "float"   WITH "%.7G"   IN ZZ$
            IREPLACE "ldouble" WITH "%.19LG" IN ZZ$
            IREPLACE "double"  WITH "%.15G"  IN ZZ$
          END IF
          CONCAT(Arg$,Cast$)
        LOOP WHILE ASC(Stak[i].Arg$) = 40
        CONCAT(Arg$, Stak[i].Arg$)
        CONCAT (Frmat$,ZZ$)
        IF DoWrite THEN CONCAT (Frmat$,",")
      ELSE
        IF DoWrite THEN
          Frmat$ = Frmat$ + "%G" + ","
        ELSE
          CONCAT (Frmat$,"%G")
          Arg$ = Arg$ + ",(float)" + Stak[i].Arg$
        END IF
      END IF
    END SELECT
  NEXT
  IF DoWrite THEN Frmat$ = LEFT$(Frmat$,LEN(Frmat$)-1)
  '*********************
  PrintWriteLabel:
  '*********************
  IF NewLineFlag = 0 THEN
    CONCAT (Frmat$,"\\n")
  END IF
  FUNCTION = "printf(" + ENC$(Frmat$) + Clean$(Arg$) + ");"
END FUNCTION ' PrintWriteFormat$
SUB EmitInputCode
  DIM RAW Argcount = 0
  DIM RAW VarCnt = 0
  DIM RAW i = 0
  DIM RAW j = 0
  DIM RAW l = 0
  DIM RAW Arg$
  DIM RAW Tmp$
  DIM RAW Frmat$
  DIM Stak$[128]
  DIM RAW Y$
  DIM RAW ZZ$
  Use_Inputbuffer = TRUE
  Use_Scan    = TRUE
  Use_Split   = TRUE
  Use_Remove  = TRUE
  Use_StrStr  = TRUE
  Use_Mid     = TRUE
  Use_Left    = TRUE
  Use_Instr   = TRUE
  Use_Stristr = TRUE
  UseLCaseTbl = TRUE
  UseFlag     = TRUE
  Use_Lineinput = TRUE

  Arg$   =  ""
  ZZ$    =  ""
  Frmat$ =  ""
  Tmp$   =  DQ$ + "," + DQ$ + "," + DQ$ + " " + DQ$
  IF DataType(Stk$[2]) = vt_STRLIT THEN
    FPRINT Outfile,Scoot$,"printf(" ; Clean$(Stk$[2]) ; ");"
  END IF
  IF DataType(Stk$[2]) = vt_STRLIT THEN
    j = 4
  ELSE
    j = 2
  END IF
  l = j
  WHILE j <= Ndx
    IF j = l THEN
      i = SubVarType(j)
    END IF
    IF Stk$[j] = "," THEN l = j + 1
    CONCAT(ZZ$, Stk$[j])
    j++
  WEND
  FastLexer(ZZ$, "", ",")
  j = 1 '0
  WHILE j <= Ndx
    IF Stk$[j] = "," THEN
      Argcount++
      Stak$[Argcount]= Arg$
      Arg$ = ""
      j++
    ELSE
      CONCAT (Arg$, Stk$[j])
      j++
      IF j < Ndx THEN
        IF Stk$[j] = "[" THEN
          i = 0
          DO
            DoAgain:
            IF Stk$[j] = "[" THEN i++
            IF Stk$[j] = "]" THEN i--
            CONCAT (Arg$,Stk$[j])
            j++
            IF Stk$[j] = "[" AND i = 0 THEN GOTO DoAgain
          LOOP UNTIL i <= 0 OR j >= Ndx
        END IF
      END IF
    END IF
  WEND
  Argcount++
  Stak$[Argcount] = Arg$
  Arg$ = ""
  FOR i = 1 TO Argcount
    Y$ = Stak$[i]
    j  = DataType(Y$)
    SELECT CASE j
      CASE vt_STRVAR
      CONCAT (Frmat$,"%s")
      Arg$ = Arg$ + "," + Clean$(Stak$[i])
      FPRINT Outfile,Scoot$, "*" + TRIM$(Clean$(Stak$[i])) + "=0;"
      VarCnt++
      CASE vt_INTEGER
      CONCAT (Frmat$,"%d")
      Arg$ = Arg$ + ",&" + Clean$(Stak$[i])
      FPRINT Outfile,Scoot$, Clean$(Stak$[i]) + "=0;"
      VarCnt++
      CASE vt_SINGLE
      CONCAT (Frmat$,"%g")
      Arg$ = Arg$ + ",&" + Clean$(Stak$[i])
      FPRINT Outfile,Scoot$, Clean$(Stak$[i]) + "=0;"
      VarCnt++
      CASE vt_DOUBLE
      CONCAT (Frmat$,"%lG")
      Arg$ = Arg$ + ",&" + Clean$(Stak$[i])
      FPRINT Outfile,Scoot$, Clean$(Stak$[i]) + "=0;"
      VarCnt++
      CASE vt_LDOUBLE
      CONCAT (Frmat$,"%lG")
      Arg$ = Arg$ + ",&" + Clean$(Stak$[i])
      FPRINT Outfile,Scoot$, Clean$(Stak$[i]) + "=0;"
      VarCnt++
      CASE ELSE
      CONCAT (Frmat$,"%d")
      Arg$ = Arg$ + ",&" + Clean$(Stak$[i])
      FPRINT Outfile,Scoot$, Clean$(Stak$[i]) + "=0;"
      VarCnt++
    END SELECT
  NEXT
  FPRINT Outfile,Scoot$, "AR_fgets_retval=fgets(InputBuffer,sizeof(InputBuffer),stdin);"
  FPRINT Outfile,Scoot$, "InputBuffer[strlen(InputBuffer)-1]=0;"
  FPRINT Outfile,Scoot$, "ScanError = scan(InputBuffer," + ENC$(Frmat$) + Arg$ + ");\n"
  FPRINT Outfile,Scoot$, "*InputBuffer=0;"
END SUB ' EmitInputCode
SUB EmitFileInputCode
  DIM RAW Argcount = 0
  DIM RAW VarCnt = 0
  DIM RAW i
  DIM RAW j
  DIM RAW Arg$
  DIM RAW Frmat$
  DIM RAW FHandle$
  DIM RAW Y$
  DIM RAW ZZ$
  DIM Stak$[128]
  Arg$     =  ""
  Frmat$   =  ""
  ZZ$      =  ""
  FHandle$ =  ""
  Use_Inputbuffer = TRUE
  Use_Scan  = TRUE
  Use_Split = TRUE
  Use_Remove= TRUE
  Use_StrStr= TRUE
  Use_Mid   = TRUE
  Use_Left  = TRUE
  Use_Instr = TRUE
  Use_Stristr = TRUE
  UseLCaseTbl = TRUE

  i = 4                      ' Extract the file handle
  FOR j = 2 TO Ndx
    IF *Stk$[j] = ASC(",") THEN i=j+1 : EXIT FOR
    FHandle$ = FHandle$ + Stk$[j]
  NEXT j
  FOR j = i TO Ndx           ' build the variable list
    IF j = i THEN SubVarType(j)
    IF Stk$[j] = "," THEN SubVarType(j+1)
    CONCAT(ZZ$, Stk$[j])
  NEXT
  FastLexer(ZZ$, "", ",")
  j = 1 '0
  WHILE j <= Ndx
    IF Stk$[j] = "," THEN
      Argcount++
      Stak$[Argcount]= Arg$
      Arg$ = ""
      j++
    ELSE
      CONCAT (Arg$, Stk$[j])
      j++
      IF j < Ndx THEN
        IF Stk$[j] = "[" THEN
          i = 0
          DO
            DoAgain:
            IF Stk$[j] = "[" THEN i++
            IF Stk$[j] = "]" THEN i--
            CONCAT (Arg$,Stk$[j])
            j++
            IF Stk$[j] = "[" AND i = 0 THEN GOTO DoAgain
          LOOP UNTIL i <= 0 OR j >= Ndx
        END IF
      END IF
    END IF
  WEND
  Argcount++
  Stak$[Argcount] = Arg$
  Arg$ = ""
  FOR i = 1 TO Argcount
    Y$ = Stak$[i]
    j  = DataType(Y$)
    SELECT CASE j
      CASE vt_STRVAR
      CONCAT (Frmat$, "%s")
      Arg$ = Arg$ + "," + Clean$(Stak$[i])
      FPRINT Outfile,Scoot$, "*" + TRIM$(Clean$(Stak$[i])) + "=0;"
      VarCnt++
      CASE vt_INTEGER
      CONCAT (Frmat$, "%d")
      Arg$ = Arg$ + ",&" + Clean$(Stak$[i])
      FPRINT Outfile,Scoot$, Clean$(Stak$[i]) + "=0;"
      VarCnt++
      CASE vt_SINGLE
      CONCAT (Frmat$, "%g")
      Arg$ = Arg$ + ",&" + Clean$(Stak$[i])
      FPRINT Outfile,Scoot$, Clean$(Stak$[i]) + "=0;"
      VarCnt++
      CASE vt_DOUBLE
      CONCAT (Frmat$, "%lG")
      Arg$ = Arg$ + ",&" + Clean$(Stak$[i])
      FPRINT Outfile,Scoot$, Clean$(Stak$[i]) + "=0;"
      VarCnt++
      CASE vt_LDOUBLE
      CONCAT (Frmat$, "%lG")
      Arg$ = Arg$ + ",&" + Clean$(Stak$[i])
      FPRINT Outfile,Scoot$, Clean$(Stak$[i]) + "=0;"
      VarCnt++
      CASE ELSE
      CONCAT (Frmat$, "%d")
      Arg$ = Arg$ + ",&" + Clean$(Stak$[i])
      FPRINT Outfile,Scoot$, Clean$(Stak$[i]) + "=0;"
      VarCnt++
    END SELECT
  NEXT
  FPRINT Outfile,Scoot$, "AR_fgets_retval=fgets(InputBuffer,1048576," ; FHandle$ ; ");"
  FPRINT Outfile,Scoot$, "if(InputBuffer[strlen(InputBuffer)-1]== 10)"
  FPRINT Outfile,Scoot$, "   InputBuffer[strlen(InputBuffer)-1]=0;"
  FPRINT Outfile,Scoot$, "ScanError = scan(InputBuffer," + ENC$(Frmat$) + Arg$ + ");\n"
  FPRINT Outfile,Scoot$, "*InputBuffer=0;"
END SUB ' EmitFileInputCode
SUB AddFuncs
  DIM RAW ZZ$
  DIM RAW Last$
  Last$ = ""
  CALL CloseAll
  OPEN prcFile$ FOR INPUT  AS FP1
  OPEN FileOut$ FOR APPEND AS Outfile
  IF ProtoType[1].Prototype$ > "" THEN
    FPRINT Outfile,""
    FPRINT Outfile,"// ************************************"
    FPRINT Outfile,"//       " + $BCX_STR_USR_PROCS
    FPRINT Outfile,"// ************************************"
    FPRINT Outfile,"\n"
  END IF
  WHILE NOT EOF(FP1)
    LINE INPUT FP1,ZZ$
    '================== strip out dead callback code ======================
    IF INSTR(ZZ$,"DefWindowProc") THEN
      IF INSTR(Last$,"return ")  OR _
        INSTR(Last$,"CallWindowProc")  OR _
        INSTR(Last$,"DefWindowProc")   OR _
        INSTR(Last$,"DefMDIChildProc") OR _
        INSTR(Last$,"DefFrameProc") THEN
        Last$ = ""
        ITERATE
      END IF
    END IF
    '======================================================================
    FPRINT Outfile,ZZ$
    IF LEFT$(ZZ$,2) <> "//" THEN
      Last$ = ZZ$
    END IF
  WEND
  CALL CloseAll
  KILL prcFile$   ' translated subs and functions
  KILL udtFile$   ' translated User Defined Types
  KILL datFile$   ' translated DATA statements
  KILL cstFile$   ' translated CONSTants
  KILL ovrFile$   ' translated overloaded subs and functions
  KILL setFile$   ' translated KILL set statements
  KILL enuFile$   ' translated GLOBAL enum blocks
END SUB ' AddFuncs
FUNCTION CheckLocal(ZZ$, BYREF varidx)
  DIM RAW TT$
  IF LocalVarCnt THEN
    TT$ = Clean$(ZZ$)
    RemoveAll(TT$, " &*()", 1)
    IF INSTR(TT$,"[") THEN TT$ = LEFT$(TT$,INSTR(TT$,"[")-1)
    FOR INTEGER i = 1 TO LocalVarCnt
      IF TT$ = LocalVars[i].VarName$ THEN
        varidx = i
        FUNCTION = LocalVars[i].VarType
      END IF
    NEXT
  END IF
  FUNCTION = vt_UNKNOWN
END FUNCTION ' CheckLocal
FUNCTION CheckGlobal(ZZ$, BYREF varidx)
  DIM RAW hn
  DIM RAW s
  DIM RAW TT$
  TT$ = Clean$(ZZ$)
  RemoveAll(TT$, " &*()", 1)
  IF INSTR(TT$,"[") THEN TT$ = LEFT$(TT$,INSTR(TT$,"[")-1)
  hn  = HashNumber(TT$)
  WHILE GlobalVarHash[hn]
    s = GlobalVarHash[hn]
    IF TT$ = GlobalVars[s].VarName$ THEN
      varidx = s
      FUNCTION = GlobalVars[s].VarType
    END IF
    hn = IMOD(hn + 1,MaxGlobalVars)
  WEND
  FUNCTION = vt_UNKNOWN
END FUNCTION ' CheckGlobal
FUNCTION CheckType(ZZ$)
  DIM RAW Keyword$
  DIM RAW varid = 0
  DIM RAW i
  Keyword$ = LCASE$(ZZ$)
  SELECT CASE Keyword$
    CASE "int"
    FUNCTION = vt_INTEGER
    CASE "string"
    FUNCTION = vt_STRVAR
    CASE "char"
    FUNCTION = vt_CHAR
    CASE "pchar"
    FUNCTION = vt_PCHAR
    CASE "byte"
    FUNCTION = vt_BYTE
    CASE "double"
    FUNCTION = vt_DOUBLE
    CASE "ldouble"
    FUNCTION = vt_LDOUBLE
    CASE "file"
    FUNCTION = vt_FILEPTR
    CASE "float"
    FUNCTION = vt_SINGLE
    CASE "bool", "boolean"
    FUNCTION = vt_BOOL
    CASE "long"
    FUNCTION = vt_LONG
    CASE "dword"
    FUNCTION = vt_DWORD
    CASE "farproc"
    FUNCTION = vt_FARPROC
    CASE "void"
    FUNCTION = vt_VOID
    CASE "lpbyte"
    FUNCTION = vt_LPBYTE
    CASE "lresult"
    FUNCTION = vt_LRESULT
    CASE "short"
    FUNCTION = vt_SHORT
    CASE "ushort"
    FUNCTION = vt_USHORT
    CASE "uint"
    FUNCTION = vt_UINT
    CASE "ulong"
    FUNCTION = vt_ULONG
    CASE "colorref"
    FUNCTION = vt_COLORREF
    CASE "handle"
    FUNCTION = vt_HANDLE
    CASE "hdc"
    FUNCTION = vt_HDC
    CASE "variant"
    FUNCTION = vt_VARIANT
  END SELECT
  i = CheckLocal(ZZ$, &varid)
  IF i = vt_UNKNOWN THEN
    i = DefsID(ZZ$)
    IF i THEN FUNCTION = TypeDefs[i].TypeofDef
  ELSE
    FUNCTION = i
  END IF
  FUNCTION = CheckGlobal(ZZ$, &varid)
END FUNCTION ' CheckType
SUB ExportInternalConst
  IF Use_FillArray THEN
    Src$="CONST vt_INTEGER =  2"
    PassOne = 1
    CALL Parse(Src$)
    CALL Emit
    Src$="CONST vt_SINGLE  =  3"
    PassOne = 1
    CALL Parse(Src$)
    CALL Emit
    Src$="CONST vt_DOUBLE  =  4"
    PassOne = 1
    CALL Parse(Src$)
    CALL Emit
    Src$="CONST vt_LDOUBLE  =  5"
    PassOne = 1
    CALL Parse(Src$)
    CALL Emit
  END IF
END SUB ' ExportInternalConst
FUNCTION RestrictedWords(ZZ$)
  IF ZZ$ = "CmdLine"    THEN FUNCTION = 1
  IF ZZ$ = "CmdShow"    THEN FUNCTION = 1
  IF ZZ$ = "hInst"      THEN FUNCTION = 1
  IF ZZ$ = "hPrev"      THEN FUNCTION = 1
  IF ZZ$ = "hWnd"       THEN FUNCTION = 1
  IF ZZ$ = "lParam"     THEN FUNCTION = 1
  IF ZZ$ = "Msg"        THEN FUNCTION = 1
  IF ZZ$ = "wParam"     THEN FUNCTION = 1
  IF ZZ$ = "vt_INTEGER" THEN FUNCTION = 1
  IF ZZ$ = "vt_SINGLE"  THEN FUNCTION = 1
  IF ZZ$ = "vt_DOUBLE"  THEN FUNCTION = 1
  IF ZZ$ = "vt_LDOUBLE" THEN FUNCTION = 1
  FUNCTION = 0
END FUNCTION ' RestrictedWords
FUNCTION DataType(ZZ$)
  DIM RAW Keyword$
  DIM RAW i
  IF ZZ[0] = 34 THEN
    FUNCTION = vt_STRLIT
  END IF
  IF INCHR(ZZ$,"$") THEN
    FUNCTION = vt_STRVAR
  END IF
  IF IsNumber(ZZ$) THEN
    FUNCTION = vt_NUMBER
  END IF
  i = DefsID(ZZ$)
  IF i THEN FUNCTION = TypeDefs[i].TypeofDef
  '****************
  '   Functions
  '****************
  Keyword$ = LCASE$(ZZ$)
  IF Keyword$ = "strlen" THEN
    FUNCTION = vt_DECFUNC
  END IF
  IF Keyword$ = "instr" THEN
    FUNCTION = vt_DECFUNC
  END IF
  IF Keyword$ = "inchr" THEN
    FUNCTION = vt_DECFUNC
  END IF
  IF Keyword$ = "sizeof" THEN
    FUNCTION = vt_DECFUNC
  END IF
  IF Keyword$ = "tally" THEN
    FUNCTION = vt_DECFUNC
  END IF
  IF Keyword$ = "band" THEN
    FUNCTION = vt_DECFUNC
  END IF
  IF Keyword$ = "bor" THEN
    FUNCTION = vt_DECFUNC
  END IF
  IF Keyword$ = "lof" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "pos" THEN
    FUNCTION = vt_DECFUNC
  END IF
  IF Keyword$ = "qbcolor" THEN
    FUNCTION = vt_DECFUNC
  END IF
  IF Keyword$ = "split" THEN
    FUNCTION = vt_DECFUNC
  END IF
  IF Keyword$ = "dsplit" THEN
    FUNCTION = vt_DECFUNC
  END IF
  IF Keyword$ = "sgn" THEN
    FUNCTION = vt_DECFUNC
  END IF
  IF Keyword$ = "timer" THEN
    FUNCTION = vt_SINGLE
  END IF
  IF Keyword$ = "keypress()" THEN
    FUNCTION = vt_DECFUNC
  END IF
  IF Keyword$ = "getattr" THEN
    FUNCTION = vt_DECFUNC
  END IF
  IF Keyword$ = "fix" THEN
    FUNCTION = vt_DECFUNC
  END IF
  IF Keyword$ = "instrrev" THEN
    FUNCTION = vt_DECFUNC
  END IF
  IF Keyword$ = "kbhit" THEN
    FUNCTION = vt_DECFUNC
  END IF
  IF Keyword$ = "exp" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "expl" THEN
    FUNCTION = vt_LDOUBLE
  END IF
  IF Keyword$ = "sinh" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "cosh" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "tanh" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "asinh" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "acosh" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "atanh" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "round" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "val" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "vall" THEN
    FUNCTION = vt_LDOUBLE
  END IF
  IF Keyword$ = "iif" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "bin2dec" THEN
    FUNCTION = vt_INTEGER
  END IF
  IF Keyword$ = "hex2dec" THEN
    FUNCTION = vt_INTEGER
  END IF
  IF Keyword$ = "rnd" THEN
    FUNCTION = vt_SINGLE
  END IF
  IF Keyword$ = "frac" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "fracl" THEN
    FUNCTION = vt_LDOUBLE
  END IF
  IF Keyword$ = "asin" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "asinl" THEN
    FUNCTION = vt_LDOUBLE
  END IF
  IF Keyword$ = "hypot" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "hypotl" THEN
    FUNCTION = vt_LDOUBLE
  END IF
  IF Keyword$ = "log" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "logl" THEN
    FUNCTION = vt_LDOUBLE
  END IF
  IF Keyword$ = "log10" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "log10l" THEN
    FUNCTION = vt_LDOUBLE
  END IF
  IF Keyword$ = "acos" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "acosl" THEN
    FUNCTION = vt_LDOUBLE
  END IF
  IF Keyword$ = "atan" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "atanl" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "sin" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "sinl" THEN
    FUNCTION = vt_LDOUBLE
  END IF
  IF Keyword$ = "cos" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "cosl" THEN
    FUNCTION = vt_LDOUBLE
  END IF
  IF Keyword$ = "tan" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "tanl" THEN
    FUNCTION = vt_LDOUBLE
  END IF
  IF Keyword$ = "pow" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "powl" THEN
    FUNCTION = vt_LDOUBLE
  END IF
  IF Keyword$ = "sqrt" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "sqrtl" THEN
    FUNCTION = vt_LDOUBLE
  END IF
  IF Keyword$ = "min" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "max" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "exist" THEN
    FUNCTION = vt_DECFUNC
  END IF
  IF Keyword$ = "abs" THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF Keyword$ = "absl" THEN
    FUNCTION = vt_LDOUBLE
  END IF
  IF Keyword$ = "freefile" THEN
    FUNCTION = vt_FILEPTR
  END IF
  IF Keyword$ = "fint" THEN
    FUNCTION = vt_INTEGER
  END IF
  IF INCHR(ZZ$,"%") THEN
    FUNCTION = vt_INTEGER
  END IF
  IF INCHR(ZZ$,"!") THEN
    FUNCTION = vt_SINGLE
  END IF
  IF INCHR(ZZ$,"#") THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF INCHR(ZZ$,"^") THEN
    FUNCTION = vt_DOUBLE
  END IF
  IF INCHR(ZZ$,"¦") THEN
    FUNCTION = vt_LDOUBLE
  END IF
  IF iMatchRgt(ZZ$,"@") THEN
    FUNCTION = vt_FILEPTR
  END IF
  IF INCHR(ZZ$," ") THEN
    FUNCTION = vt_UDT
  END IF
  IF isalpha(*ZZ$) THEN
    FUNCTION = vt_INTEGER
  END IF
  FUNCTION = vt_UNKNOWN
END FUNCTION ' DataType
SUB CloseAll
  !#if defined (__APPLE__)
  CLOSE SourceFile
  CLOSE FP2
  CLOSE FP3
  CLOSE FP4
  CLOSE FP5
  CLOSE FP6
  CLOSE FP7
  CLOSE FP8
  CLOSE FP9
  CLOSE FP10
  CLOSE FP11
  CLOSE Outfile
  CLOSE FP1
  CLOSE ResIn
  CLOSE ResOut
  CLOSE UserResIn
  CLOSE fpErr
  CLOSE fpHFile
  CLOSE FP68
  CLOSE fpdef
  CLOSE SaveOutfileNum
  !#else
  CLOSE   ' Flush and Close all open files
  !#endif
END SUB ' CloseAll
FUNCTION Clean$(ZZ$)
  DIM RAW Tmp$
  IF INCHR(ZZ$,"%") THEN
    IF TRIM$(ZZ$) = "%" THEN FUNCTION = " % "
  END IF
  IF iMatchNQ(ZZ$,"!=") THEN FUNCTION = ZZ$
  Tmp$ = ZZ$
  RemoveAll(Tmp$,"%$#!@¦",1)   '1 = ignore anything in quotes
  FUNCTION = Tmp$
END FUNCTION ' Clean$
SUB RemoveAll OPTIONAL(Arg$, MatchChars$, qtflag=0)
  DIM RAW C = Arg AS PCHAR
  DIM RAW pmc AS PCHAR
  WHILE *Arg
    IF qtflag THEN
      IF *Arg = 34 THEN
        *(C++) = *Arg
        WHILE *(++Arg) <> 34
          *(C++) = *Arg
          IF *Arg = 0 THEN EXIT SUB
        WEND
        *(C++) = *(Arg++)
        ITERATE
      END IF
    END IF
    pmc = MatchChars
    WHILE *pmc
      IF *(pmc++) = *Arg THEN GOTO SKIP
    WEND
    *(C++) = *Arg
    SKIP:
    INCR Arg
  WEND
  *C = 0
END SUB
SUB Warning OPTIONAL(ZZ$, WarnLvl=0)
  LOCAL fErr AS FILE
  IF WarnLvl THEN
    WarnMsg$ = WarnMsg$ + " Line" + STR$(ModuleLineNos[ModuleNdx]) + " in Module: " + TRIM$(Modules$[ModuleNdx]) + " - " + ZZ$
  ELSE
    WarnMsg$ = WarnMsg$ + ZZ$
  END IF
  WarnMsg$ = WarnMsg$ + CRLF$
  IF ErrFile THEN
    OPEN FileErr$ FOR APPEND AS fErr
    FPRINT fErr, "WARNING ";ZZ$
    CLOSE fErr
  END IF
END SUB ' Warnings
FUNCTION GetVarTypeName(i) AS PCHAR
  DIM STATIC A$
  SELECT CASE i
    CASE vt_INTEGER    :    A$ = "int"
    CASE vt_STRVAR     :    A$ = "char *"
    CASE vt_STRLIT     :    A$ = "STRLIT"
    CASE vt_UNKNOWN    :    A$ = "UNKNOWN"
    CASE vt_SINGLE     :    A$ = "float"
    CASE vt_DOUBLE     :    A$ = "double"
    CASE vt_LDOUBLE    :    A$ = "LDOUBLE"
    CASE vt_DECFUNC    :    A$ = "DECFUNC"
    CASE vt_NUMBER     :    A$ = "NUMBER"
    CASE vt_FILEPTR    :    A$ = "FILE*"
    CASE vt_UDT        :    A$ = "struct"
    CASE vt_STRUCT     :    A$ = "struct"
    CASE vt_UNION      :    A$ = "union"
    CASE vt_BOOL       :    A$ = "bool"
    CASE vt_CHAR       :    A$ = "char"
    CASE vt_CHARPTR    :    A$ = "char"
    CASE vt_PCHAR      :    A$ = "PCHAR"
    CASE vt_VOID       :    A$ = "void"

    CASE vt_LONG       :    A$ = "long"
    CASE vt_DWORD      :    A$ = "DWORD"
    CASE vt_FARPROC    :    A$ = "FARPROC"
    CASE vt_LPBYTE     :    A$ = "LPBYTE"
    CASE vt_LRESULT    :    A$ = "LRESULT"
    CASE vt_BYTE       :    A$ = "BYTE"
    CASE vt_SHORT      :    A$ = "short"
    CASE vt_USHORT     :    A$ = "USHORT"
    CASE vt_COLORREF   :    A$ = "COLORREF"
    CASE vt_UINT       :    A$ = "UINT"
    CASE vt_ULONG      :    A$ = "ULONG"
    CASE vt_HANDLE     :    A$ = "HANDLE"
    CASE vt_HINSTANCE  :    A$ = "HINSTANCE"
    CASE vt_HDC        :    A$ = "HDC"
    CASE vt_VARIANT    :    A$ = "VARIANT"
    CASE ELSE          :    A$ = ""
  END SELECT
  FUNCTION = A
END FUNCTION ' GetVarTypeName$
FUNCTION HashNumber(HT$)
  DIM RAW TT AS CHAR PTR
  DIM RAW i = 0 AS ULONG
  TT = HT
  WHILE *TT
    i <<= 1
    ! i ^= *TT;
    TT++
  WEND
  FUNCTION = IMOD(i,MaxGlobalVars)
END FUNCTION 'HashNumber
SUB AddLibrary( LibName$ )
  STATIC nTimes
  LOCAL nLibNdx
  DIM RAW TempLibName$
  TempLibName$ = LCASE$(LibName$)
  IF NOT INCHR(TempLibName$,DQ$) AND NOT INCHR(TempLibName$,"<") THEN
    TempLibName$ = ENC$(TempLibName$,60,62)
  END IF
  IF nTimes = 0 THEN
    FOR INTEGER i = 0 TO MaxLib - 1
      Library$[i] = ""
    NEXT
    nTimes++
    Library$[0] = TempLibName$
    EXIT SUB
  END IF
  nLibNdx = 0
  WHILE Library$[nLibNdx] <> ""
    IF Library$[nLibNdx] = TempLibName$ THEN EXIT SUB
    INCR nLibNdx
  WEND
  IF nLibNdx < MaxLib - 1 THEN
    Library$[nLibNdx] = TempLibName$
  END IF
END SUB ' AddLibrary
SUB RemoveLibrary( LibName$ )
  IF NOT INSTR( RmLibs$, LibName$, 1, 1 ) THEN
    RmLibs$ = RmLibs$ + "," + LCASE$(LibName$)
  END IF
END SUB ' RemoveLibrary
SUB EmitLibs()
  STATIC nTimes
  STATIC nCount
  DIM RAW ltmp$
  IF nTimes > 0 THEN EXIT SUB
  INCR nTimes
  IF Library$[0] = "" THEN EXIT SUB
  FPRINT FP7,""
  FPRINT FP7,"#ifndef LINUXBCX"
  FPRINT FP7,"#if !defined( __LCC__ )"
  FOR INTEGER i = 0 TO MaxLib - 1
    IF Library$[i] = "" AND nCount > 0 THEN
      GOTO NEXTLIB
    ELSEIF Library$[i] = "" THEN
      GOTO NEXTLIB
    END IF
    ltmp$ = Library$[i]
    RemoveAll(ltmp$,"<>" & DQ$)
    IF INSTR( RmLibs$, ltmp$ ) THEN ITERATE ' skip libraries that have been removed
    IF nCount = 0 THEN
      INCR nCount
      FPRINT FP7,"// *************************************************"
      FPRINT FP7,"// Instruct Linker to Search Object/Import Libraries"
      FPRINT FP7,"// *************************************************"
    END IF
    FPRINT FP7,"#pragma comment(lib,",ENC$(ltmp$), ")"
  NEXT
  NEXTLIB:
  FPRINT FP7, "#else"
  ' add lccwin32's default libraries to the remove library list so they won't be emitted
  RmLibs$ = RmLibs$ + ",<libc.lib>,<kernel32.lib>,<comdlg32.lib>,<user32.lib>,<gdi32.lib>,<advapi32.lib>,<comctl32.lib>,<crtdll.lib>"
  FOR INTEGER i = 0 TO MaxLib - 1
    IF Library$[i] = "" AND nCount > 0 THEN
      FPRINT FP7,"// *************************************************"
      FPRINT FP7,"// End of Object/Import Libraries To Search"
      FPRINT FP7,"// *************************************************"
      GOTO LIBEND
    ELSEIF Library$[i] = "" THEN
      GOTO LIBEND
    END IF
    IF INSTR( RmLibs$, Library$[i] ) THEN ITERATE ' skip libraries that have been removed
    IF nCount = 0 THEN
      INCR nCount
      FPRINT FP7,""
      FPRINT FP7,"// *************************************************"
      FPRINT FP7,"// Instruct Linker to Search Object/Import Libraries"
      FPRINT FP7,"// *************************************************"
    END IF
    FPRINT FP7,"#pragma lib ",Library$[i]
  NEXT
  LIBEND:
  FPRINT FP7,"#endif"
  FPRINT FP7,"#endif     // LINUXBCX not defined"
END SUB ' EmitLibs
SUB AddGlobal OPTIONAL(GlobalName$, GlobalType, GlobalDef, GlobalDim$, GlobalPtr, GlobalFS, GlobalExtn, iEmitted, iConst=0)
  DIM RAW FirstVar$
  DIM RAW SecondVar$
  DIM RAW Warn$
  DIM RAW ss
  DIM RAW s
  IF RestrictedWords(GlobalName$) AND TestState THEN
    Warn$ = "Restricted Word " + GlobalName$ + " on Line"
    Warn$ = Warn$ + STR$(ModuleLineNos[ModuleNdx]) + " in Module: " + TRIM$(Modules$[ModuleNdx])
    CALL Warning(Warn$)
  END IF
  ss = HashNumber(GlobalName$)
  WHILE GlobalVarHash[ss]
    s = GlobalVarHash[ss]
    IF GlobalName$ = GlobalVars[s].VarName$ THEN
      IF InConditional = 0 OR (InConditional > 0 AND InIfDef$ = GlobalVars[s].VarCondDef$) THEN
        IF GlobalVars[s].VarType <> GlobalType OR _
          GlobalDim$ <> GlobalVars[s].VarDim$ OR _
          GlobalVars[s].VarDef <> GlobalDef THEN
          FirstVar$ = "Line" + STR$(ModuleLineNos[ModuleNdx]) + " in Module: " + TRIM$(Modules$[ModuleNdx]) + " : " + GlobalName$ + GlobalDim$ + " as " + GetVarTypeName$(GlobalType) + " " + TypeDefs[GlobalDef].VarName$
          SecondVar$ = "Line" + STR$(GlobalVars[s].VarLine) + " in Module: " + GlobalVars[s].VarModule + " : " + GlobalName$ + GlobalVars[s].VarDim$ + " as " + GetVarTypeName$(GlobalVars[s].VarType) + " " + TypeDefs[GlobalVars[s].VarDef].VarName$
          Warn$ = "Two Variables " + FirstVar$ + " previously defined at " + SecondVar$
          CALL Warning(Warn$)
        END IF
        EXIT SUB
      END IF
    END IF
    ss = IMOD(ss + 1,MaxGlobalVars)
  WEND
  GlobalVarCnt++
  IF GlobalVarCnt = MaxGlobalVars THEN Abort("Maximum Global Variables reached.")
  GlobalVars[GlobalVarCnt].VarName$     =  GlobalName$
  GlobalVars[GlobalVarCnt].VarType      =  GlobalType
  GlobalVars[GlobalVarCnt].VarDef       =  GlobalDef
  GlobalVars[GlobalVarCnt].VarDim$      =  GlobalDim$
  GlobalVars[GlobalVarCnt].VarLine      =  ModuleLineNos[ModuleNdx]
  GlobalVars[GlobalVarCnt].VarPntr      =  GlobalPtr
  GlobalVars[GlobalVarCnt].VarSF        =  GlobalFS
  GlobalVars[GlobalVarCnt].VarEmitFlag  =  iEmitted
  GlobalVars[GlobalVarCnt].VarModule$   =  TRIM$(Modules$[ModuleNdx])
  GlobalVars[GlobalVarCnt].VarExtn      =  GlobalExtn
  GlobalVars[GlobalVarCnt].VarCondLevel =  InConditional
  GlobalVars[GlobalVarCnt].VarConstant  =  iConst
  GlobalVars[GlobalVarCnt].VarCondDef$  =  InIfDef$
  GlobalVarHash[ss] = GlobalVarCnt
END SUB ' AddGlobal





SUB AddLocal OPTIONAL(LocalName$, LocalType, LocalDef, LocalDim$, LocalPtr, LocalFS, iEmitted, iConst=0)
  DIM RAW varid = 0
  DIM RAW FirstVar$
  DIM RAW SecondVar$
  DIM RAW Warn$
  DIM RAW s
  IF LocalVarCnt AND TestState THEN
    IF CheckGlobal(LocalName$, &varid) <> vt_UNKNOWN THEN
      IF LocalDef THEN
        FirstVar$ = "Line" + STR$(ModuleLineNos[ModuleNdx]) + " in Module: " + TRIM$(Modules$[ModuleNdx]) + " : " + LocalName$ + LocalDim$ + " as " + TypeDefs[LocalDef].VarName$
      ELSE
        FirstVar$ = "Line" + STR$(ModuleLineNos[ModuleNdx]) + " in Module: " + TRIM$(Modules$[ModuleNdx])  + " : " + LocalName$ + LocalDim$ + " as " + GetVarTypeName$(LocalType)
      END IF
      IF GlobalVars[varid].VarDef THEN
        SecondVar$ = "Line" + STR$(GlobalVars[varid].VarLine) + " in Module: " + GlobalVars[varid].VarModule + " : " + LocalName$ + GlobalVars[varid].VarDim$ + " as " + TypeDefs[GlobalVars[varid].VarDef].VarName$
      ELSE
        SecondVar$ = "Line" + STR$(GlobalVars[varid].VarLine) + " in Module: " + GlobalVars[varid].VarModule + " : " + LocalName$ + GlobalVars[varid].VarDim$ + " as " + GetVarTypeName$(GlobalVars[varid].VarType)
      END IF
      Warn$ = "Local Variable " + FirstVar$ + CRLF$ + "Has Same Name as Global " + SecondVar$
      CALL Warning(Warn$)
    END IF
    FOR s = 1 TO LocalVarCnt
      IF LocalName$ = LocalVars[s].VarName$ THEN
        IF LocalVars[s].VarType <> LocalType OR LocalDim$ <> LocalVars[s].VarDim$ OR LocalVars[s].VarDef <> LocalDef THEN
          FirstVar$ = "Line" + STR$(ModuleLineNos[ModuleNdx]) + " in Module: " + TRIM$(Modules$[ModuleNdx]) + " : " + LocalName$ + LocalDim$ + " as " + GetVarTypeName$(LocalType) + " " + TypeDefs[LocalDef].VarName$
          SecondVar$ = "Line" + STR$(LocalVars[s].VarLine) + " in Module: " + LocalVars[s].VarModule + " : " + LocalName$ + LocalVars[s].VarDim$ + " as " + GetVarTypeName$(LocalVars[s].VarType) + " " + TypeDefs[LocalVars[s].VarDef].VarName$
          Warn$ = "Two Variables " + FirstVar$ + " previously defined at " + SecondVar$
          CALL Warning(Warn$)
        END IF
        EXIT SUB
      END IF
    NEXT
  END IF
  LocalVarCnt++
  IF LocalVarCnt = MaxLocalVars THEN
    Warn$ = "Maximum Local Variables reached."
    Abort(Warn$)
  END IF
  LocalVars[LocalVarCnt].VarName$  =  LocalName$
  LocalVars[LocalVarCnt].VarType   =  LocalType
  LocalVars[LocalVarCnt].VarDef    =  LocalDef
  LocalVars[LocalVarCnt].VarDim$   =  LocalDim$
  LocalVars[LocalVarCnt].VarLine   =  ModuleLineNos[ModuleNdx]
  LocalVars[LocalVarCnt].VarPntr   =  LocalPtr
  LocalVars[LocalVarCnt].VarSF     =  LocalFS
  LocalVars[LocalVarCnt].VarEmitFlag  =  iEmitted
  LocalVars[LocalVarCnt].VarConstant  =  iConst
  LocalVars[LocalVarCnt].VarModule$=  TRIM$(Modules$[ModuleNdx])
END SUB ' AddLocal
FUNCTION IsNumber(a$)
  DIM RAW i = 0
  IF NOT *a THEN FUNCTION = FALSE  ' Handle null arguments
  WHILE a[i]                       ' While NOT null terminator
    IF a[i]>47 AND a[i]<58 THEN    ' Test for 0123456789
      i++                          ' bump our index
    ELSE
      FUNCTION = FALSE             ' a$ is not a number
    END IF                         '
  WEND                             '
  FUNCTION = TRUE                  ' a$ is a number
END FUNCTION ' IsNumber
FUNCTION IsNumberEx(a$)
  DIM RAW i = 0
  IF NOT *a THEN FUNCTION = FALSE  ' Handle null arguments
  WHILE a[i]                       ' While NOT null terminator
    IF a[i]>44 AND a[i]<58 THEN    ' Test FOR -+.0123456789
      i++                          ' bump our index
    ELSE
      FUNCTION = FALSE             ' a$ is not a number
    END IF                         '
  WEND                             '
  FUNCTION = TRUE                  ' a$ is a number
END FUNCTION ' IsNumberEx
SUB StripTabs
  DIM RAW i = 0
  WHILE Src[i]
    IF Src[i] = 9 THEN Src[i] = 32
    i++
  WEND
END SUB ' StripTabs
SUB PushFileIO
  FPtr[++FPtrNdx] = SourceFile
END SUB 'PushFileIO
SUB PopFileIO
  IF FPtrNdx = 0 THEN EXIT SUB
  CLOSE SourceFile
  INCR LinesRead, ModuleLineNos[ModuleNdx--]
  SourceFile = FPtr[FPtrNdx--]
END SUB 'PopFileIO
FUNCTION Inset(Mane$,Match$)
  DIM RAW i = -1, j = -1
  WHILE Match[++i]
    WHILE Mane[++j]
      IF Match[i] = Mane[j] THEN FUNCTION = TRUE
    WEND
    j = -1
  WEND
  FUNCTION = FALSE
END FUNCTION 'Inset
SUB CheckParQuotes
  DIM RAW CountR=0 'Round bracket counter
  DIM RAW CountS=0 'Square bracket counter
  DIM RAW i=0
  DIM RAW DoCount = TRUE AS bool
  WHILE Src[i]
    IF Src[i]=34 THEN
      DoCount = NOT DoCount
    END IF
    IF DoCount THEN
      IF Src[i]=40 THEN
        CountR++
      ELSEIF Src[i]=41 THEN
        CountR--
      ELSEIF Src[i]=91 THEN
        CountS++
      ELSEIF Src[i]=93 THEN
        CountS--
      END IF
    END IF
    i++
  WEND
  IF NOT DoCount THEN
    Abort ("Unmatched Quotes")
  ELSEIF CountS THEN
    Abort ("Unmatched []")
  ELSEIF CountR THEN
    Abort ("Unmatched ()")
  END IF
END SUB ' CheckParQuotes
SUB ClearIfThenStacks
  FOR INTEGER i = 0 TO 127
    SrcStk$[i] = ""
  NEXT
  SrcCnt = 0
END SUB ' ClearIfThenStacks
FUNCTION IsQuoted(ZZ$)
  IF NOT iMatchLft(LTRIM$(ZZ$),DQ$) THEN EXIT FUNCTION
  IF NOT iMatchRgt(RTRIM$(ZZ$),DQ$) THEN EXIT FUNCTION
  FUNCTION = TRUE
END FUNCTION ' IsQuoted
SUB PostProcess
  DIM RAW A
  IF ReDirect = TRUE THEN
    OPEN FileOut$ FOR INPUT AS FP1
    WHILE NOT EOF(FP1)
      LINE INPUT FP1,Z$
      PRINT Z$
    WEND
    CALL CloseAll
  END IF
  '**************************
  OutfileClone$ = FileOut$
  FOR A = 1 TO EntryCnt
    OutfileClone$ = EXTRACT$(OutfileClone$,".")
    Cmd$ = REMOVE$(Entry$[A],DQ$)
    REPLACE "\\\\" WITH "\\" IN Cmd$
    IREPLACE "$file$"  WITH EXTRACT$(OutfileClone$,".") IN Cmd$
    PRINT "Shelling Out To: ", Cmd$
    SHELL Cmd$
  NEXT
  IF Compiler$ > "" THEN
    Compiler$ = TRIM$(REMOVE$(Compiler$,DQ$))
    IF INCHR(Compiler$, " ") THEN
      Compiler$ = ENC$(EXTRACT$(Compiler$," ")) + " " +  REMAIN$(Compiler$," ")
    ELSE
      Compiler$ = ENC$(Compiler$)
    END IF
    '/***** 2018-12-09  Changed default output extension to ".cc" -AIR *****/
    FileOut$ = EXTRACT$(FileOut$,".") + ".cc"
    Compiler$ = Compiler$ + " " + FileOut$
    IREPLACE "$FILE$"  WITH EXTRACT$(OutfileClone$,".") IN Compiler$
    REPLACE "\\\\" WITH "\\" IN Compiler$
    REPLACE DDQ$   WITH DQ$  IN Compiler$
    PRINT "Shelling Out To: ", Compiler$
    SHELL Compiler$
  END IF
  '**************************
  IF Linker$ > "" THEN
    Linker$ = TRIM$(REMOVE$(Linker$,DQ$))
    IF INCHR(Linker$, " ") THEN
      Linker$ = DQ$ + EXTRACT$(Linker$," ") + DQ$ + " " + REMAIN$(Linker$," ")
    ELSE
      Linker$ = ENC$(Linker$)
    END IF
    FileOut$ = EXTRACT$(FileOut$,".") + ".obj"
    Linker$ = Linker$ + " " + FileOut$
    IREPLACE "$FILE$" WITH EXTRACT$(OutfileClone$,".") IN Linker$
    REPLACE "\\\\" WITH "\\" IN Linker$
    REPLACE DDQ$   WITH DQ$  IN Linker$
    PRINT "Shelling Out To:", Linker$
    SHELL Linker$
  END IF
  '**************************
  FOR A = 1 TO XitCount
    FileOut$ = EXTRACT$(FileOut$,".")
    Cmd$ = REMOVE$(Xit$[A],DQ$)
    IREPLACE "$FILE$" WITH EXTRACT$(OutfileClone$,".") IN Cmd$
    REPLACE "\\\\" WITH "\\" IN Cmd$
    REPLACE DDQ$ WITH DQ$ IN Cmd$
    PRINT "Shelling Out To: ", Cmd$
    SHELL Cmd$
  NEXT
END SUB ' PostProcess
SUB XParse(Arg$)
  DIM RAW lszTmp$
  DIM RAW j, i = 0, Gapflag = 0
  DIM RAW InIF = 0
  IF TRIM$(Arg$) = "" THEN
    Ndx = 0
    EXIT SUB
  END IF
  '-----------------------------------------------
  ' A temporary cure to allow the C '&&' operator
  '-----------------------------------------------
  i = iMatchNQ(Arg$, "&&")
  WHILE i
    Arg$ = DEL$(Arg$, i, 2)
    Arg$ = INS$(Arg$, i, " and ")
    i = iMatchNQ(Arg$, "&&")
  WEND
  '-----------------------------------------------
  FastLexer(Arg$, SPC$, "=&()[]{}',+-*/<>?;.|:^")
  '****************************************
  '              Pre Parse
  '****************************************
  WHILE ++i < 17
    Stk$[i+Ndx] = ""
  WEND
  FOR i = 1 TO Ndx
    Keyword1$ = LCASE$(Stk$[i])
    IF Keyword1[1] <> 0 THEN
      SELECT CASE Keyword1$
        CASE "and"  : Stk$[i] = "&&"
        CASE "or"   : Stk$[i] = "||"
        CASE "not"  : Stk$[i] = "!"
        CASE "is"   : Stk$[i] = "="
        CASE "xor"  : Stk$[i] = "xor"
        CASE "if","iif","iif$","case","elseif","while"
        InIF = 1
        CASE "then"
        InIF = 0
        CASE "byval"
        Stk$[i] = ""
        Gapflag = TRUE
        CASE "byref"
        IF NOT iMatchWrd(Stk$[1], "declare") AND _
          NOT iMatchWrd(Stk$[1], "c_declare") THEN
          ByrefVars$[++ByrefCnt] = Stk$[i+1]
        END IF
        FOR j = i TO Ndx
          IF Stk$[j+1] = "," OR Stk$[j+1] = ")" THEN
            Stk$[j] = "PTR"
            EXIT FOR
          END IF
          Stk$[j] = Stk$[j+1]
        NEXT
        CASE ELSE
        IF PassOne THEN
          IF Keyword1$ = ENC$(CHR$(92)) THEN
            Stk$[i] = "chr$"
            InsertTokens(i, 3, "(", "92", ")")
            INCR i,3
          ELSEIF  TranslateSlash THEN
            REPLACE "\\" WITH "\\\\" IN Stk$[i]
          END IF
        END IF
      END SELECT
      '*******************************************************************
      '  Allow logical 'OR/AND' to be used as 'binary BOR/BAND'
      '*******************************************************************
      IF NOT InIF THEN
        IF Stk$[i] = "&&" THEN
          Stk$[i] = "BAND"
        ELSEIF Stk$[i] = "||" THEN
          Stk$[i] = "BOR"
        END IF
      END IF
    ELSE
      SELECT CASE ASC(Keyword1$)
        ' --------------------------------
        ' Connect (&)addressof operator.
        ' --------------------------------
        CASE ASC("&")
        IF i < 3 OR INCHR("+&,(=", Stk$[i-1]) THEN
          Stk$[i+1] = " &" + Stk$[i+1]
          Stk$[i] = "" : Gapflag=TRUE
        END IF
        CASE ASC("?")
        Stk$[i] = "print"
        CASE ASC("-")
        IF ASC(Stk$[i+1]) = ASC(">") THEN
          Stk$[i] = "->" & Stk$[i+2]
          Stk$[++i] = "" : Stk$[++i] = ""
          Gapflag=TRUE
        END IF
        CASE ASC(".")
        IF IsNumber(Stk$[i-1]) THEN
          Stk$[i] = Stk$[i-1] & "."
          Stk$[i-1] = "" : Gapflag=TRUE
        END IF
        IF NOT INCHR( ",)=<>*/+-^" , Stk[i+1]) THEN
          Stk$[i] = Stk$[i] & Stk$[i+1]
          Stk$[++i] = "" : Gapflag=TRUE
        END IF
      END SELECT
    END IF
  NEXT i
  IF Gapflag THEN
    FOR i = 1 TO Ndx
      IF NOT *Stk[i] THEN
        j = i + 1
        WHILE NOT *Stk[j] AND (j < Ndx)
          INCR j
        WEND
        IF NOT *Stk[j] THEN EXIT FOR
        Stk$[i] = Stk$[j] : Stk$[j] = ""
      END IF
    NEXT i
    Ndx = i-1
  END IF
  ' *******************************************************************
  ' Special Case Handler: BYREF - BCX prepends * to BYREF'd Variables
  ' *******************************************************************
  IF PassOne = 1 THEN
    IF InFunc THEN ' Must be in a SUB or FUNCTION
      FOR i = 1 TO Ndx
        FOR j = 1 TO ByrefCnt
          IF iMatchLft(Stk$[i], " &") THEN lszTmp$ = Stk$[i] + 2 ELSE lszTmp$ = Stk$[i]
          IF Clean$(lszTmp$) = Clean$(ByrefVars[j]) THEN
            IF i > 2 THEN
              IF INCHR("+-^%*/|&<=>,", Stk$[i-2]) AND Stk$[i-1] = "*" THEN
                Stk$[i-1] = ""
              END IF
              IF iMatchLft(Stk$[i], " &") THEN
                Stk$[i] = Stk$[i] + 2
                EXIT FOR
              END IF
            ELSEIF i = 2 THEN
              IF Stk$[i-1] = "*" THEN Stk$[i-1] = ""
            END IF
            Stk$[i] = "*" & Stk$[i]
            IF Stk$[i-1] <> "(" OR Stk$[i+1] <> ")" THEN
              Stk$[i] = ENC$(Stk$[i], ASC("("), ASC(")"))
            END IF
            EXIT FOR
          END IF
        NEXT
      NEXT
    END IF
  END IF
  ' *******************************************************************
  ' Special Case Handler: DIM BLAHBLAH[22][33] AS STATIC INTEGER
  ' *******************************************************************
  IF iMatchWrd(Stk$[1],"dim") THEN
    IF iMatchWrd(Stk$[Ndx-1],"static") THEN
      Stk$[1] = "static"
      Stk$[Ndx-1] = Stk$[Ndx]
      Ndx--
    END IF
  END IF
  ' ***************************************************************************
  ' Special Case Handler: In the contexts of UDT,s this handler transforms:
  ' FUNCTION Foo (a as integer) AS INTEGER         to:
  ' DIM FUNCTION Foo (a as integer) AS INTEGER
  '
  ' Change "as string" to "as char *" for UDTs and Declarations
  ' ***************************************************************************
  Keyword1$ = LCASE$(Stk$[1])
  IF InTypeDef THEN
    IF Keyword1$ <> "end" AND Keyword1$ <> "dim" AND Keyword1$ <> "declare" AND Keyword1$ <> "type" AND Keyword1$ <> "union" THEN
      InsertTokens(0, 1, "dim")
    END IF
  END IF
  '******************************
  '
  '******************************
  IF NOT InTypeDef THEN
    DIM RAW lsz$, Res = 1
    lsz$ =  SPC$ & Keyword1$ & SPC$
    IF iMatchNQ(" dim , local , global , raw , static , shared , dynamic , auto , register , extern ", lsz$) THEN
      Res = 1
    END IF
    lsz$ =  SPC$ & LCASE$(Stk$[2]) & SPC$
    IF iMatchNQ(" dim , local , global , raw , static , shared , dynamic , auto , register , extern ", lsz$) THEN
      Res = 2
    END IF
    IF Res > 0 THEN
      i = Ndx
      WHILE i > 1 AND Stk$[i] <> ")"
        IF iMatchWrd(Stk$[i], "as") THEN
          IF iMatchWrd(Stk$[i+1], "function") THEN
            IF i+1 = Ndx THEN Stk$[i] = "" ' remove "as"
            Stk$[i+1] = ""
            InsertTokens(Res, 1, "function")
          ELSEIF iMatchWrd(Stk$[i+1], "sub") THEN
            IF i+1 = Ndx THEN Stk$[i] = "" ' remove "as"
            Stk$[i+1] = ""
            InsertTokens(Res, 1, "sub")
          END IF
          CALL RemEmptyTokens
          EXIT WHILE
        END IF
        DECR i
      WEND
    END IF
  END IF
  IF InTypeDef OR iMatchWrd(Stk$[1], "declare") OR iMatchWrd(Stk$[1], "c_declare") THEN
    IF iMatchWrd(Stk$[2],"sub") OR iMatchWrd(Stk$[2],"function") THEN
      FOR INTEGER i = 2 TO Ndx
        IF iMatchLft(Stk$[i],"as") AND iMatchWrd(Stk$[i+1],"string") THEN
          IF *Stk$[i+2] <> ASC("*") THEN Stk$[i+1] = "char *"
        END IF
      NEXT
    END IF
  END IF
END SUB 'XParse
SUB TokenSubstitutions
  '*****************************
  ' Start Doing Text Substitutions
  '*****************************
  DIM RAW A
  DIM RAW CompPtr
  DIM RAW CompToken
  DIM RAW Keyword$
  DIM RAW a, i, j, Tmp
  '******************************************************************************************
  ' Following block added in 4.13 --  Dim XXX as string * 12345
  ' Works in  UDT, GLOBALS, LOCALS, and RAW
  '******************************************************************************************
  FOR i = 1 TO Ndx
    IF iMatchWrd(Stk$[i],"as") THEN
      IF iMatchWrd(Stk$[i+1],"string") THEN
        IF Stk$[i+2] = "*" THEN
          Stk$[i]   = "["
          Stk$[i+1] = Stk$[i+3]
          Stk$[i+2] = "]"
          Stk$[i+3] = "as"
          INCR Ndx
          Stk$[Ndx] = "char"
          EXIT FOR
        END IF
      END IF
    END IF
  NEXT
  '******************************************************************************************
  FOR i = 1 TO Ndx
    IF NOT InFunc THEN
      IF iMatchWrd(Stk$[i],"global") THEN Stk$[i] = "dim"
    END IF
  NEXT
  A = FALSE
  FOR Tmp = 1 TO Ndx
    IF *Stk[Tmp] = ASC("0") AND Stk[Tmp][1] <> ASC("x") AND Stk[Tmp][1] <> ASC("l") THEN
      Stk$[Tmp] = LTRIM$(Stk$[Tmp],48) 'allow leading zero's in numbers
      IF Stk$[Tmp] = "" THEN Stk$[Tmp] = "0"
    END IF
    IF iMatchWrd(Stk$[Tmp],"xor") THEN
      Stk$[Tmp] = "^"
    ELSEIF Stk$[Tmp] = "=" AND Stk$[Tmp+1]= ">" THEN
      Stk$[Tmp] = ">"
      Stk$[Tmp+1]= "="
    ELSEIF Stk$[Tmp] = "=" AND Stk$[Tmp+1]= "<" THEN
      Stk$[Tmp] = "<"
      Stk$[Tmp+1] = "="
    ELSEIF Stk$[Tmp] = "<" AND Stk$[Tmp+1]= ">"  THEN
      Stk$[Tmp]  = "!="
      Stk$[Tmp+1] = ""
      A = TRUE
    ELSEIF Stk$[Tmp]  = ">" AND Stk$[Tmp+1]= "<" THEN
      Stk$[Tmp]   = "!="
      Stk$[Tmp+1] = ""
      A = TRUE
    ELSEIF Stk$[Tmp]= "!" AND Stk$[Tmp+1]= "=" THEN
      Stk$[Tmp]= "!="
      Stk$[Tmp+1] = ""
      A = TRUE
    END IF
  NEXT
  IF A = TRUE THEN CALL RemEmptyTokens
  '*************************************************************************
  ' needed when recursively calling parse() after <> has already translated
  ' to != Otherwise, on pass 2, it emits as !== which is NOT desired.
  '*************************************************************************
  CompToken = 0
  FOR Tmp = 1 TO Ndx
    A = CheckLocal(Stk$[Tmp], &i)
    IF A = vt_UNKNOWN THEN A = CheckGlobal(Stk$[Tmp], &i)
    IF A = vt_STRUCT OR A = vt_UDT OR A = vt_UNION THEN
      CompToken = 1
    END IF
    IF iMatchWrd(Stk$[Tmp],"int") AND Stk$[Tmp+1] = "(" THEN
      Stk$[Tmp]= "fint"
    ELSEIF iMatchWrd(Stk$[Tmp],"integer") THEN
      Stk$[Tmp]= "int"
    ELSEIF iMatchWrd(Stk$[Tmp],"fint") AND Stk$[Tmp+1]= ")" THEN
      Stk$[Tmp]= "int"
    END IF
  NEXT
  '*****************************
  CompPtr = 0
  FOR Tmp = 1 TO Ndx
    Keyword$ = LCASE$(Stk$[Tmp])
    a = INCHR("abcdefghijklmnopqrstuvwxyz", Keyword$)
    SELECT CASE a
      CASE 1
      SELECT CASE Keyword$
        CASE "abs"
        Stk$[Tmp]= "abs" ' might need fabs
        CASE "acos"
        Stk$[Tmp]= "acos"
        CASE "acosl"
        Stk$[Tmp]= "acosl"
        CASE "acosh"
        Stk$[Tmp]= "acosh"
        CASE "appexename$"
        Stk$[Tmp] = "AppExeName$()"
        Use_AppExeName = Use_BcxSplitPath = UseFlag =  TRUE
        CASE "appexepath$"
        Stk$[Tmp] = "AppExePath$()"
        IF Stk$[Tmp+1]= "(" AND Stk$[Tmp+2]= ")" THEN
          Stk$[Tmp+1] = ""
          Stk$[Tmp+2] = ""
        END IF
        Use_AppExePath = Use_BcxSplitPath = UseFlag = TRUE
        CASE "ansitowide"
        Stk$[Tmp] = "AnsiToWide"
        Use_AnsiToWide = UseFlag = TRUE
        CASE "argc"
        Stk$[Tmp]= "argc"
        CASE "argv"
        Stk$[Tmp]= "argv"
        CASE "argv$"
        Stk$[Tmp]= "argv$"
        CASE "asc"
        i=0
        j=GetNumArgs(Tmp+2,&i)
        IF *Stk[Tmp+2] = *DQ$ THEN
          IF j > 0 OR *Stk[Tmp+3] <> ASC(")") THEN
            Stk$[Tmp] = "asc"
            Use_Asc = TRUE
          ELSE
            IF Stk$[Tmp+2] = DDQ$ THEN
              Stk$[Tmp] = "0"
            ELSE
              Stk$[Tmp] = LTRIM$(STR$(ASC(Stk$[Tmp+2],1)))
            END IF
            Stk$[Tmp+1] = "" : Stk$[Tmp+2] = "" : Stk$[Tmp+3] = ""
          END IF
        ELSE
          IF j > 0 THEN Stk$[i] = "+"
          Stk$[Tmp] = "(UCHAR)*"
        END IF
        CASE "asin"
        Stk$[Tmp]= "asin"
        CASE "asinl"
        Stk$[Tmp]= "asinl"
        CASE "asinh"
        Stk$[Tmp]= "asinh"
        CASE "atanh"
        Stk$[Tmp]= "atanh"
        CASE "atn","atan"
        Stk$[Tmp]= "atan"
        CASE "atnl","atanl"
        Stk$[Tmp]= "atanl"
        CASE "auto"
        IF iMatchWrd(Stk$[Tmp+1],"local") THEN
          Stk$[Tmp] = "dim" : Stk$[Tmp+1] = "raw"
        ELSE
          Stk$[Tmp]= "auto"
        END IF
      END SELECT
      CASE  2
      SELECT CASE Keyword$
        CASE "bcopy"
        *Stk[1] = 0
        FOR i = Tmp+1 TO Ndx
          IF iMatchWrd(Stk$[i],"to") THEN EXIT FOR
          CONCAT(Stk$[1], Stk$[i]) 'Source
        NEXT
        *Stk[2] = 0
        FOR i = i+1 TO Ndx
          CONCAT(Stk$[2], Stk$[i]) 'Destination
        NEXT
        Src$ = "memmove(&" + Stk$[2] + ",&" + Stk$[1] + ",sizeof(" + Stk$[2] + "))"
        REMOVE "&*" FROM Src$
        Ndx = 0
        CALL XParse(Src$)
        CASE "bel$"
        Stk$[Tmp] = "BEL$"
        Use_BEL = UseFlag = TRUE
        CASE "bs$"
        Stk$[Tmp] = "BS$"
        Use_BS = UseFlag = TRUE
        CASE "bool","boolean"
        Stk$[Tmp]= "bool"
        CASE "band"
        Stk$[Tmp]= " BAND "
        Use_Band = TRUE
        CASE "bnot"
        Stk$[Tmp] = " BNOT "
        Use_Bnot = TRUE
        ' *******************************************************************
        ' Special Case Handler: Maintain case sensitivity for this structure
        ' *******************************************************************
        CASE "bcx_font"
        Stk$[Tmp]   = UCASE$(Stk$[Tmp])
        DIM RAW tmp$
        tmp$ = Clean$(UCASE$(Stk$[Tmp+1]))
        SELECT CASE tmp$
          CASE ".NAME"         : Stk$[Tmp+1] = ".lf.lfFaceName$"
          CASE ".BOLD"         : Stk$[Tmp+1] = ".lf.lfWeight"
          CASE ".UNDERLINE"    : Stk$[Tmp+1] = ".lf.lfUnderline"
          CASE ".STRIKEOUT"    : Stk$[Tmp+1] = ".lf.lfStrikeOut"
          CASE ".ITALIC"       : Stk$[Tmp+1] = ".lf.lfItalic"
          CASE ".CHARSET"      : Stk$[Tmp+1] = ".lf.lfCharSet"
          CASE ".SIZE", ".RGB" : Stk$[Tmp+1] = tmp$
          CASE ELSE
          Stk$[Tmp+1] = Clean$(Stk$[Tmp+1])
        END SELECT
        CASE "bcxsplitpath$"
        Stk$[Tmp] = "$$BcxSplitPath$"
        Use_BcxSplitPath = UseFlag =  TRUE
        CASE "bcxpath$"
        UseFlag = TRUE
        Stk$[Tmp] = "BcxPath$()"
        IF Stk$[Tmp+1]= "(" AND Stk$[Tmp+2]= ")" THEN
          Stk$[Tmp+1] = ""
          Stk$[Tmp+2] = ""
        END IF

        CASE "bcxfont"
        Stk$[Tmp] = "BcxFont"



        '/***** 2010-12-11 New Socket Keywords -AIR *****/
        case "bcxsocket"
        Stk$[Tmp] = "BcxSocket"
        Use_Socket = true
        case "bcxsocketsend"
        Stk$[Tmp] = "BcxSocketSend"
        case "bcxsocketread"
        Stk$[Tmp] = "BcxSocketRead"
        case "bcxsocketclose"
        Stk$[Tmp] = "BcxSocketClose"


        CASE "bcx_thread", "bcx_threadwait", "bcx_threadsuspend","bcx_threadresume","bcx_threadkill","bcx_threadend"
        Stk$[Tmp] = UCASE$(Stk$[Tmp])
        Use_Threads =  TRUE
        CASE "bin$"
        Stk$[Tmp] = "$$Bin$"
        Use_Bin = UseFlag = TRUE
        CASE "bool$"
        Stk$[Tmp] = "$$BoolStr$"
        Use_Boolstr = UseFlag = TRUE
        CASE "bin2dec"
        Stk$[Tmp]= "Bin2Dec"
        Use_Bin2dec = TRUE
        CASE "boolean"
        Stk$[Tmp]= "BOOLEAN"
        CASE "bor"
        Stk$[Tmp]= " BOR "
        Use_Bor = TRUE
        CASE "byte"
        Stk$[Tmp]= "BYTE"
      END SELECT
      CASE 3
      SELECT CASE Keyword$
        CASE "containedin"
        Stk$[Tmp] = "containedin"
        Use_ContainedIn = TRUE
        CASE "copyfile"
        Use_CopyFile = TRUE
        Use_Exist = Use_Lof = TRUE
        CASE "cr$"
        Stk$[Tmp] = "CR$"
        Use_CR = UseFlag = TRUE
        CASE "close#"
        Stk$[Tmp] = "close"
        CASE "close"
        IF LEFT$(Stk$[Tmp+1],1)= "#" THEN
          Stk$[Tmp+1] = MID$(Stk$[Tmp+1],2)
        END IF
        CASE "cvd"
        Stk$[Tmp]="CVD"
        Use_Cvd = TRUE
        CASE "cvi"
        Stk$[Tmp]="CVI"
        Use_Cvi = TRUE
        CASE "cvl"
        Stk$[Tmp]="CVL"
        Use_Cvl = TRUE
        CASE "cvld"
        Stk$[Tmp]="CVLD"
        Use_Cvld = TRUE
        CASE "cvs"
        Stk$[Tmp]="CVS"
        Use_Cvs = TRUE
        CASE "concat"
        Stk$[Tmp]= "strcat"
        CASE "chr$"
        Stk$[Tmp]= "$$chr$"
        Use_Chr = UseFlag = TRUE
        CASE "char"
        Stk$[Tmp]= "char"
        CASE "crlf$"
        Stk$[Tmp] = "CRLF$"
        Use_Crlf = UseFlag = TRUE
        CASE "cbctl"
        Stk$[Tmp]= "LOWORD(wParam)"
        CASE "cbctlmsg"
        Stk$[Tmp]= "HIWORD(wParam)"
        CASE "cblparam"
        Stk$[Tmp]= "lParam"
        CASE "cbmsg"
        Stk$[Tmp]= "Msg"
        CASE "cbwparam"
        Stk$[Tmp]= "wParam"
        CASE "cdbl"
        Stk$[Tmp]= "CDBL"
        Use_Cdbl = TRUE
        CASE "chdrive", "chdir"
        Stk$[Tmp]= "chdir"
        CASE "cint"
        Stk$[Tmp]= "Cint"
        Use_Cint = TRUE
        CASE "cldbl"
        Stk$[Tmp]= "CLDBL"
        Use_Cldbl = TRUE
        CASE "clng"
        Stk$[Tmp]= "CLNG"
        Use_Clng = TRUE
        CASE "cls"
        Stk$[Tmp]= "cls"
        Use_Cls = Use_ESC = TRUE
        CASE "color", "color_fg", "color_bg"
        Stk$[Tmp] = LCASE$(Stk$[Tmp])
        Use_Color = Use_Console = TRUE
        CASE "command$"
        Use_Command = Use_SPC = UseFlag = TRUE
        Stk$[Tmp]= "command$(-1)"
        IF Stk$ [Tmp+1] = "(" THEN
          Stk$ [Tmp]= "command$"
        END IF
        CASE "colorref"
        Stk$[Tmp]= "COLORREF"
        CASE "cos"
        Stk$[Tmp]= "cos"
        CASE "cosl"
        Stk$[Tmp]= "cosl"
        CASE "cosh"
        Stk$[Tmp]= "cosh"
        CASE "cbool"
        Stk$[Tmp] = "CBOOL"
        DIM fp AS functionParse, i, t, expos = 0
        IF SepFuncArgs(Tmp+1, &fp, TRUE) = 0 THEN Abort("No argument specified in CBOOL")
        FOR i = fp.CommaPos[0] TO fp.CommaPos[1]
          t = INCHR("!<>=", Stk$[i])
          IF t THEN
            IF t < 4 THEN
              IF Stk$[i+1] = "=" THEN
                Stk$[i] = Stk$[i] + Stk$[i+1]
                Stk$[i+1] = ""
              ELSEIF t = 1 AND Stk$[i] <> "!=" THEN
                ITERATE
              END IF
            ELSE
              IF Stk$[i+1] <> "=" THEN Stk$[i] = "=="
            END IF
            expos = i
            EXIT FOR
          END IF
        NEXT
        t = DataType(Stk$[expos-1])
        IF t = vt_STRLIT OR t = vt_STRVAR THEN
          IF expos THEN
            Stk$[Tmp+1] = Stk$[Tmp+1] + "strcmp("
            Stk$[fp.CommaPos[1]] = ")" + Stk$[expos] + "0)"
            Stk$[expos] = ","
            Src$ = ""
            FOR i = 1 TO Ndx
              Src$ = Src$ + Stk$[i] + SPC$
            NEXT
            FastLexer(Src$," ","(),")
          END IF
        END IF
        CASE "csng"
        Stk$[Tmp]= "CSNG"
        Use_Csng = TRUE

        CASE "curdir$"
        Stk$[Tmp]= "curdir$()"
        IF Stk$[Tmp+1]= "(" AND Stk$[Tmp+2]= ")" THEN
          Stk$[Tmp+1] = ""
          Stk$[Tmp+2] = ""
        END IF
        Use_Curdir = UseFlag = TRUE

        CASE "currency"
        Stk$[Tmp] = "CURRENCY"
        CASE "c_declare"
        CallType$ = "__attribute__((cdecl)) "
        Stk$[Tmp]= "declare"
        IF iMatchWrd(Stk$[4], "lib") THEN
          NoTypeDeclare = FALSE
        ELSE
          NoTypeDeclare = TRUE
        END IF
      END SELECT
      CASE 4
      SELECT CASE Keyword$
        CASE "declare"
        CallType$ = "__attribute__((stdcall)) "
        Stk$[Tmp]= "declare"
        IF NOT iMatchWrd(Stk$[4], "lib") THEN
          NoTypeDeclare = TRUE
        ELSE
          NoTypeDeclare = FALSE
        END IF
        CASE "dq$"
        Stk$[Tmp] = "DQ$"
        Use_DQ = UseFlag = TRUE
        CASE "ddq$"
        Stk$[Tmp] = "DDQ$"
        Use_DDQ = UseFlag = TRUE
        CASE "data$"
        Stk$[Tmp]= "DATA$"
        CASE "date$"
        Stk$[Tmp] = "$$timef$(12)"
        Use_Time = UseFlag = TRUE
        CASE "delete"
        IF UseCpp = FALSE THEN Abort( "'DELETE' can only be used with C++" )
        Stk$[Tmp]="delete "
        CASE "del$"
        Stk$[Tmp]= "del$"
        Use_Del = UseFlag = TRUE
        CASE "double"
        Stk$[Tmp]= "double"
        CASE "download"
        Stk$[Tmp] = "Download"
        Use_Download = Use_Dynacall = TRUE
        CASE "dsplit"
        Stk$[Tmp]= "DSplit"
        Use_DSplit = TRUE
        Use_Remove = TRUE
        Use_StrStr = TRUE
        Use_Mid    = TRUE
        Use_Left   = TRUE
        Use_Instr  = TRUE
        Use_Stristr = TRUE
        UseLCaseTbl = TRUE
        UseFlag = TRUE
        CASE "dword"
        Stk$[Tmp]= "DWORD"
      END SELECT
      CASE  5
      SELECT CASE Keyword$
        CASE "extern"
        Stk$[Tmp] = "extern"
        CASE "enc$"
        Stk$[Tmp]= "$$enc$"
        Use_Enclose =  UseFlag = TRUE
        CASE "extract$"
        Stk$[Tmp]= "$$extract$"
        Use_Extract = Use_StrStr = UseFlag = TRUE
        CASE "eof$"
        Stk$[Tmp] = "EF$"
        Use_EOF = UseFlag = TRUE
        CASE "eof"
        Stk$[Tmp]= "EoF"
        Use_Eof = UseFlag = TRUE
        IF DataType(Stk$[Tmp + 2]) = vt_NUMBER THEN
          Stk$[Tmp + 2] = "FP" + Stk$[Tmp + 2]
        END IF
        CASE "esc$"
        Stk$[Tmp] = "ESC$"
        Use_ESC = UseFlag = TRUE
        CASE "enum"
        '/***** 2011-03-09 Added support Named ENUMS -AIR *****/
        '/***** SYNTAX:  blah as ENUM *****/
        IF Ndx = 1 OR iMatchWrd(Stk$[3],"enum") THEN
          Use_EnumFile = TRUE
          '******************************************************
          '     We're dealing with a ENUM - END ENUM block
          '******************************************************
          DIM RAW EnumFlag = FALSE
          FPRINT FP11,""
          '/***** 2011-03-09 Added support Named ENUMS -AIR *****/
          IF Ndx = 1 THEN
            FPRINT FP11,"enum"
          ELSE IF Ndx = 3 then
            FPRINT FP11,"enum " + Stk$[1]
          END IF
          '/*****************************************************/
          FPRINT FP11,"  {"

          Src$ = ""
          WHILE NOT iMatchLft(Src$,"end ")
            IF EOF(SourceFile) THEN Abort ("Unbalanced ENUM")
            LINE INPUT SourceFile,Src$
            ModuleLineNos[ModuleNdx]++
            CALL StripCode(Src$)
            IF iMatchLft(Src$,"$comme") THEN
              Directives()
              ITERATE
            END IF
            Src$ = TRIM$(Src$)
            IF Src$ = "" THEN ITERATE ' line starts with comment
            IF LCASE$(LEFT$(Src$ + " ",4)) = "end " THEN
              EXIT LOOP
            ELSE
              IF EnumFlag = FALSE THEN
                EnumFlag = TRUE
              ELSE
                FPRINT FP11,","
              END IF
            END IF
            FPRINT FP11,"    ",RTRIM$(Src$);
          WEND
          Src$ = ""
          Ndx = 0
          FPRINT FP11,""
          FPRINT FP11,"  };\n"
          EXIT SUB
        END IF
        '*************************************************************
        '  We're dealing with a smaller, single line ENUM statement
        '*************************************************************
        Stk$[1] = "enum {"
        FOR j = 2 TO Ndx
          CONCAT (Stk$[1], Stk$[j])
        NEXT
        CONCAT (Stk$[1], "}")
        Ndx = 1
        CASE "environ$"
        Stk$[Tmp]= "Environ$"
        Use_Environ = UseFlag = TRUE

        CASE "exist"
        Stk$[Tmp]= "Exist"
        Use_Exist = UseFlag = TRUE
        CASE "exp"
        Stk$[Tmp]= "Exp"
        Use_Exp = TRUE
      END SELECT
      CASE  6
      SELECT CASE Keyword$
        CASE "freeglobals"
        Stk$[Tmp] = "FreeGlobals"
        CASE "ff$"
        Stk$[Tmp] = "FF$"
        Use_FF = UseFlag = TRUE
        CASE "function"
        IF Stk$[Tmp+1] = "=" THEN
          IF Stk$[Tmp+2] = DDQ$ THEN Stk$[Tmp+2] = "NUL$"
          Stk$[Tmp] = "functionreturn"
        END IF
        CASE "false"
        Stk$[Tmp]= "FALSE"
        CASE "file"
        Stk$[Tmp]= "FILE"
        CASE "findintype"
        'Convert this :FindInType(char *Token, Type.member, int c)
        'To this      :FindInType(char *Token, Stptr + offsetof(Type,member), sizeof(Type), int c)
        Stk$[Tmp]= "FindInType"
        Use_FindInType = TRUE
        DIM RAW StMem$, StName$, VarName$
        DIM fp AS functionParse
        CALL SepFuncArgs(Tmp, &fp, TRUE)
        StMem$ = REMAIN$(Clean$(GetArg$(2, &fp)),".")
        VarName$ = EXTRACT$(Clean$(GetArg$(2, &fp)),".")
        FOR j = fp.CommaPos[1] + 1 TO fp.CommaPos[2] - 1
          Stk$[j] = ""
        NEXT
        IF CheckLocal(VarName$,&i) <> vt_UNKNOWN THEN
          StName$ = TypeDefs[LocalVars[i].VarDef].VarName$
        ELSEIF CheckGlobal(VarName$,&i) <> vt_UNKNOWN THEN
          StName$ = TypeDefs[GlobalVars[i].VarDef].VarName$
        END IF
        j = fp.CommaPos[1] + 1
        Stk$[j] =  "(char*)" & VarName$ & " + offsetof(" & StName$ & "," & StMem$ & "), sizeof(" & StName$ & ")"
        CASE "farproc"
        Stk$[Tmp] = "FARPROC"
        CASE "fillarray"
        Stk$[Tmp] = "fillarray"
        Use_FillArray = TRUE
        CASE "findfirst$"
        Stk$[Tmp]= "findfirst$"
        j = GetNumArgs(Tmp+2)
        IF j = 0 THEN Stk$[Ndx] = ", &FindData)"
        Use_Findfirst = Use_Like = TRUE
        Use_BcxSplitPath =  TRUE
        Use_Join = TRUE
        UseFlag = TRUE
        CASE "findnext$"
        Stk$[Tmp]= "findnext$"
        IF Stk$[Tmp+1]= "(" AND Stk$[Tmp+2]= ")" THEN
          Stk$[Tmp+1] = "(&FindData"
        ELSEIF Tmp = Ndx THEN
          Ndx++
          Stk$[Ndx] = "(&FindData)"
        END IF
        Use_Findnext = Use_Like = UseFlag = TRUE
        Use_Join = TRUE
        CASE "fint"
        Stk$[Tmp]= "FINT"
        Use_Fint = TRUE
        CASE "fix"
        Stk$[Tmp]= "FIX"
        Use_Fix = TRUE
        CASE "filelocked"
        Stk$[Tmp]= "FileLocked"
        Use_FileLocked = TRUE
        CASE "flush"
        Stk$[Tmp]= "fflush"
        CASE "frac"
        Stk$[Tmp]= "FRAC"
        Use_Frac = TRUE
        CASE "fracl"
        Stk$[Tmp]= "FRACL"
        Use_Fracl = TRUE
        CASE "freefile"
        Stk$[Tmp]= "FreeFile()"
        Use_Freefile = TRUE
      END SELECT
      CASE  7
      SELECT CASE Keyword$
        CASE "getprocaddress"
        LOCAL GlobalName$, s, ss, tempA$
        GlobalName$ = Stk$[Tmp-2]
        ss = HashNumber(GlobalName$)
        WHILE GlobalVarHash[ss]
          s = GlobalVarHash[ss]
          IF GlobalName$ = GlobalVars[s].VarName$ THEN
            tempA$ = TypeDefs[GlobalVars[s].VarDef].VarName$
            IF GlobalVars[s].VarPntr THEN
              tempA$=tempA$+" *"
            END IF
          END IF
          ss = IMOD(ss + 1,MaxGlobalVars)
        WEND
        IF tempA$ = "" THEN
          LOCAL LocalName$
          LocalName$ = Stk$[Tmp-2]
          IF LocalVarCnt THEN
            FOR INTEGER i = 1 TO LocalVarCnt
              IF LocalName$ = LocalVars[i].VarName$ THEN
                tempA$ = TypeDefs[LocalVars[i].VarDef].VarName$
                IF LocalVars[i].VarPntr THEN
                  tempA$ = tempA$ + " *"
                END IF
                EXIT FOR
              END IF
            NEXT
          END IF
        END IF
        IF tempA$ <> "" THEN
          '~ Stk$[Tmp]= "(" + tempA$ + ")GetProcAddress"
          Stk$[Tmp]= "(" + tempA$ + ")dlsym"
        ELSE
          '~ Stk$[Tmp]= "GetProcAddress"
          Stk$[Tmp]= "dlsym"
        END IF

        CASE "getattr"
        Stk$[Tmp]= "GETATTR"
        CASE "getbvalue"
        Stk$[Tmp]= "GetBValue"
        CASE "getc"
        Stk$[Tmp]= "getc"
        CASE "getgvalue"
        Stk$[Tmp]= "GetGValue"
        CASE "getrvalue"
        Stk$[Tmp]= "GetRValue"

        CASE "getresource"
        Stk$[Tmp] = "GetResource"
        Use_Embed = TRUE

      END SELECT
      CASE  8
      SELECT CASE Keyword$
        CASE "hiword"
        Stk$[Tmp]= "HIWORD"
        CASE "hex$"
        Stk$[Tmp]= "hex$"
        Use_Hex = UseFlag = TRUE
        CASE "hex2dec"
        Stk$[Tmp]= "Hex2Dec"
        Use_Hex2Dec = UseLCaseTbl = TRUE
        CASE "hibyte"
        Stk$[Tmp]= "HIBYTE"
        CASE "hide"
        Stk$[Tmp]= "Hide"
        CASE "hypot"
        Stk$[Tmp]= "hypot"
      END SELECT
      CASE  9
      SELECT CASE Keyword$
        CASE "inherits"
        Stk$[Tmp]="inherits"
        CASE "instr"
        Stk$[Tmp]= "instr_b"
        Use_Instr = Use_StrStr = TRUE
        Use_Stristr = UseLCaseTbl = TRUE
        CASE "inchr"
        Stk$[Tmp]= "inchr"
        Use_Inchr = TRUE
        CASE "imod"
        Stk$[Tmp]= "imod"
        Use_Imod = TRUE
        CASE "iif"
        Stk$[Tmp]= "iif"
        Use_Iif = TRUE
        FOR i = Tmp+1 TO Ndx
          IF Stk$[i] = "=" THEN
            IF Stk$[i-1] <> "<" AND Stk$[i-1] <> ">" THEN
              Stk$[i] = "=="
            END IF
          END IF
        NEXT
        CASE "iif$"
        Stk$[Tmp]= "sziif$"
        Use_sziif = TRUE
        FOR i = Tmp+1 TO Ndx
          IF Stk$[i] = "=" THEN
            IF Stk$[i-1] <> "<" AND Stk$[i-1] <> ">" THEN
              Stk$[i] = "=="
            END IF
          END IF
        NEXT
        CASE "inkey"
        Use_InkeyD = TRUE
        Use_GetCh = TRUE
        UseFlag = TRUE
        Stk$[Tmp]= "inkeyd()"
        IF Stk$[Tmp+1]= "(" AND Stk$[Tmp+2]= ")" THEN
          Stk$[Tmp+1] = ""
          Stk$[Tmp+2] = ""
        END IF
        CASE "inkey$"
        Use_Inkey = TRUE
        Use_GetCh = TRUE
        UseFlag = TRUE
        Stk$[Tmp]= "inkey$()"
        IF Stk$[Tmp+1]= "(" AND Stk$[Tmp+2]= ")" THEN
          Stk$[Tmp+1] = ""
          Stk$[Tmp+2] = ""
        END IF
        CASE "ins$"
        Stk$[Tmp]= "ins$"
        Use_Ins = UseFlag = TRUE
        CASE "instat"
        Use_Instat = true
        Stk$[Tmp]= "kbhit()"
        CASE "instrrev"
        Stk$[Tmp]= "InstrRev"
        Use_Instrrev = TRUE
        CASE "isptr"
        Stk$[Tmp]= "IsPtr"
        Use_Isptr = TRUE
        CASE "ireplace$"
        Stk$[Tmp]= "iReplace$"
        Use_iReplace = Use_Stristr = UseFlag = TRUE
        UseLCaseTbl = TRUE
        CASE "iremove$"
        Stk$[Tmp]= "IRemoveStr$"
        Use_IRemove = UseFlag = TRUE
        Use_Stristr = UseLCaseTbl = TRUE
        CASE "iterate"
        Stk$[Tmp]= "continue"
      END SELECT
      CASE  10
      SELECT CASE Keyword$
        CASE "join$"
        Stk$[Tmp]= "$$join$"
        Use_Join = UseFlag = TRUE
      END SELECT
      CASE  11
      SELECT CASE Keyword$
        CASE "keypress"
        Stk$[Tmp] = "keypress()"
        IF Stk$[Tmp+1] = "(" AND Stk$[Tmp+2]= ")" THEN
          Stk$[Tmp+1] = ""
          Stk$[Tmp+2] = ""
        END IF
        Use_Keypress = TRUE
        Use_GetCh = TRUE
      END SELECT
      CASE  12
      SELECT CASE Keyword$
        CASE "loadfile$"
        Stk$[Tmp]= "$$LoadFile$"
        Use_LoadFile = Use_Get = UseFlag = TRUE
        Use_Exist = Use_Lof = TRUE
        CASE "lf$"
        Stk$[Tmp] = "LF$"
        Use_LF = UseFlag = TRUE
        CASE "line"
        IF iMatchWrd(Stk$[Tmp+1],"input") THEN
          Use_Lineinput = TRUE
          Stk$[Tmp] = "lineinput"
          j = Tmp + 4
          Stk$[Tmp+1] = "" ' Extract the file handle
          FOR i = Tmp+2 TO Ndx
            IF *Stk$[i] = ASC(",") THEN j=i+1 : EXIT FOR
            Stk$[Tmp+1] = Stk$[Tmp+1] + Stk$[i]
            Stk$[i] = ""
          NEXT j
          FOR i = j TO Ndx
            Stk$[Tmp+2]= Stk$[Tmp+2] & Stk$[i]
          NEXT
        END IF
        CASE "lcase$"
        Stk$[Tmp] = "$$lcase$"
        Use_Lcase = TRUE
        Use_StrUpLow = UseFlag = TRUE
        CASE "ldouble"
        Stk$[Tmp] = "LDOUBLE"
        Use_Ldouble = UseFlag = TRUE
        CASE "left$"
        Stk$[Tmp]= "$$left$"
        Use_Left = TRUE
        UseFlag = TRUE
        CASE "long"
        Stk$[Tmp]= "long"
        CASE "longlong"
        Stk$[Tmp] = "LONGLONG"
        CASE "lpbyte"
        Stk$[Tmp] = "LPBYTE"
        CASE "len"
        Stk$[Tmp]= "strlen"
        CASE "lprint"
        Stk$[Tmp]= "lprint"
        IF Tmp = Ndx THEN
          Ndx++
          Stk$[Ndx] = ENC$ ("") ' Allow LPRINT with no args
        END IF
        CASE "lpad$"
        Stk$[Tmp]= "$$lpad$"
        Use_Lpad = UseFlag = TRUE
        CASE "ltrim$"
        Stk$[Tmp]= "$$ltrim$"
        Use_Ltrim = UseFlag = TRUE
        CASE "lof"
        Stk$[Tmp]= "lof"
        IF DataType(Stk$[Tmp + 2]) = vt_NUMBER THEN
          Stk$[Tmp + 2] = "FP" + Stk$[Tmp + 2]
        END IF
        Use_Lof = TRUE
        CASE "loadlibrary", "load_dll"
        Stk$[Tmp]= "LoadLibrary"
        CASE "like"
        Stk$[Tmp] = "like"
        Use_Like  =  TRUE
        CASE "lobyte"
        Stk$[Tmp]= "LOBYTE"
        CASE "loc"
        IF DataType(Stk$[Tmp + 2]) = vt_NUMBER THEN
          Stk$[Tmp + 2] = "FP" + Stk$[Tmp + 2]
        END IF
        Stk$[Tmp] = "loc(" + Stk$[Tmp + 2] + "," + Stk$[Tmp + 2] + "len)"
        Stk$[Tmp + 1] = ""
        Stk$[Tmp + 2] = ""
        Stk$[Tmp + 3] = ""
        Use_Loc = TRUE
        CASE "locate"
        Use_Locate =  TRUE
        CASE "log"
        Stk$[Tmp]= "log"
        CASE "logl"
        Stk$[Tmp]= "logl"
        CASE "log10"
        Stk$[Tmp]= "log10"
        CASE "log10l"
        Stk$[Tmp]= "log10l"
        CASE "loword"
        Stk$[Tmp]= "LOWORD"
        CASE "lpstr"
        Stk$[Tmp]= "PCHAR"
      END SELECT
      CASE  13
      SELECT CASE Keyword$
        CASE "mkd$"
        IF Tmp > 2 THEN
          IF INCHR(Stk$[Tmp-2],"$") AND *Stk$[Tmp-1] = ASC("=") THEN
            Stk$[1] = "memcpy(" + Stk$[1]
            Stk$[Tmp-1] = ","
            Stk$[++Ndx] = ",9)"
          END IF
        END IF
        Stk$[Tmp]="MKD"
        Use_Mkd = UseFlag = TRUE
        CASE "mki$"
        IF Tmp > 2 THEN
          IF INCHR(Stk$[Tmp-2],"$") AND *Stk$[Tmp-1] = ASC("=") THEN
            Stk$[1] = "memcpy(" + Stk$[1]
            Stk$[Tmp-1] = ","
            Stk$[++Ndx] = ",3)"
          END IF
        END IF
        Stk$[Tmp]="MKI"
        Use_Mki = UseFlag = TRUE
        CASE "mkl$"
        IF Tmp > 2 THEN
          IF INCHR(Stk$[Tmp-2],"$") AND *Stk$[Tmp-1] = ASC("=") THEN
            Stk$[1] = "memcpy(" + Stk$[1]
            Stk$[Tmp-1] = ","
            Stk$[++Ndx] = ",5)"
          END IF
        END IF
        Stk$[Tmp]="MKL"
        Use_Mkl = UseFlag = TRUE
        CASE "mkld$"
        IF Tmp > 2 THEN
          IF INCHR(Stk$[Tmp-2],"$") AND *Stk$[Tmp-1] = ASC("=") THEN
            Stk$[1] = "memcpy(" + Stk$[1]
            Stk$[Tmp-1] = ","
            Stk$[++Ndx] = ",11)"
          END IF
        END IF
        Stk$[Tmp]="MKLD"
        Use_Mkld = UseFlag = TRUE
        CASE "mks$"
        IF Tmp > 2 THEN
          IF INCHR(Stk$[Tmp-2],"$") AND *Stk$[Tmp-1] = ASC("=") THEN
            Stk$[1] = "memcpy(" + Stk$[1]
            Stk$[Tmp-1] = ","
            Stk$[++Ndx] = ",5)"
          END IF
        END IF
        Stk$[Tmp]="MKS"
        Use_Mks = UseFlag = TRUE
        CASE "mid$"
        IF Tmp > 1 THEN
          Stk$[Tmp]= "$$mid$"
          Use_Mid = UseFlag = TRUE
        ELSE
          Stk$[Tmp]= "midstr"
          Use_Midstr = UseFlag = TRUE
        END IF
        CASE "min"
        Stk$[Tmp]= "_MIN_"
        Use_Min = TRUE
        CASE "main"
        Stk$[Tmp]= "main"
        CASE "makeintresource"
        Stk$[Tmp]= "MAKEINTRESOURCE"
        CASE "makelong"
        Stk$[Tmp]= "MAKELONG"
        CASE "makeword"
        Stk$[Tmp]= "MAKEWORD"
        CASE "max"
        Stk$[Tmp]= "_MAX_"
        Use_Max = TRUE
        CASE "mcase$"
        Stk$[Tmp] = "$$mcase$"
        Use_Mcase = UseFlag = TRUE
        Use_StrUpLow = TRUE
        CASE "mkdir"
        Stk$[Tmp]= "mkdir"
        CASE "mod"
        Stk$[Tmp]= "fmod"
      END SELECT
      CASE  14
      SELECT CASE Keyword$
        CASE "new"
        IF iMatchWrd(Stk$[Tmp-1],"binary") THEN EXIT
        IF UseCpp = FALSE THEN Abort( "'NEW' can only be used with C++" )
        Stk$[Tmp] = "new "
        CASE "nul$"
        Stk$[Tmp] = "NUL$"
        Use_NUL = UseFlag = TRUE
        CASE "null"
        Stk$[Tmp]= "NULL"
        CASE "now$"
        Stk$[Tmp]= "now$()"
        Use_Now = UseFlag = TRUE
      END SELECT
      CASE  15
      SELECT CASE Keyword$
        CASE "open"
            FOR A = Tmp+1 TO Ndx
              IF LEFT$(Stk$[A],1) = "#" THEN
                Stk$[A] = MID$(Stk$[A],2)
                EXIT FOR
              END IF
            NEXT
        CASE "oct$"
        Stk$[Tmp]= "oct$"
        Use_Oct = UseFlag = TRUE
        CASE "osversion"
        Stk$[Tmp]= "OSVersion()"
        IF Stk$[Tmp+1]= "(" AND Stk$[Tmp+2]= ")" THEN
          Stk$[Tmp+1] = ""
          Stk$[Tmp+2] = ""
        END IF
        Use_OSVersion = TRUE
      END SELECT
      CASE  16
      SELECT CASE Keyword$
        CASE "pause"
        Stk$[Tmp] = "Pause()"
        IF Stk$[Tmp+1] = "(" AND Stk$[Tmp+2]= ")" THEN
          Stk$[Tmp+1] = ""
          Stk$[Tmp+2] = ""
        END IF
        Use_Pause = Use_Keypress = TRUE
        Use_GetCh = TRUE
        CASE "preserve"
        Stk$[Tmp] = "PRESERVE"
        CASE "print#"
        Stk$[Tmp] = "fprint"
        CASE "print"
        IF LEFT$(Stk$[Tmp+1],1)= "#" THEN
          Stk$[Tmp] = "fprint"
          Stk$[Tmp+1] = MID$(Stk$[Tmp+1],2)
        END IF
        CASE "ptr"
        CompPtr = 1
        Stk$[Tmp-1] = Stk$[Tmp-1] + "*"
        Stk$[Tmp]= ""
        IF Tmp = Ndx THEN
          Ndx--
          WHILE TALLY(Stk$[Ndx],"*") = LEN(Stk$[Ndx])
            Stk$[Ndx-1] = Stk$[Ndx-1] + Stk$[Ndx]
            Stk$[Ndx] = ""
            Ndx--
          WEND
        ELSE
          i = Tmp-1
          WHILE TALLY(Stk$[i],"*") = LEN(Stk$[i])
            Stk$[i-1] = Stk$[i-1] + Stk$[i]
            Stk$[i] = ""
            i--
          WEND
        END IF
        CASE "peek$"
        Stk$[Tmp]= "$$peekstr$"
        Use_PeekStr = UseFlag = TRUE
        CASE "poke"
        Stk$[Tmp]= "memmove"
        CASE "pow"
        Stk$[Tmp]= "pow"
        CASE "powl"
        Stk$[Tmp]= "powl"
        CASE "private"
          IF UseCpp THEN
            Stk$[Tmp]= "private"
          END IF
          IF iMatchWrd(Stk$[Tmp+1],"const") THEN
            Stk$[Tmp]= "enum "
            Stk$[Tmp+1]= Stk$[Tmp+2] + "{"
            Ndx++
            Stk$[Ndx]= "}"
          END IF

        CASE "public"
        IF UseCpp THEN
          Stk$[Tmp]= "public"
        END IF

      END SELECT
      CASE  17
      SELECT CASE Keyword$
        CASE "qbcolor"
        Stk$[Tmp]= "qbcolor"
        Use_QBColor = TRUE
      END SELECT
      CASE  18
      SELECT CASE Keyword$
        '/***** 2012-12-12 New REGMATCH Keyword -AIR *****/
        CASE "regmatch"
          Stk$[Tmp] = "regmatch"
          ' print "REGMATCH FOUND"
          Use_PeekStr = Use_RegEx = TRUE      
        CASE "rewind"
        Stk$[Tmp]= "rewind"
        IF DataType(Stk$[Tmp + 2]) = vt_NUMBER THEN
          Stk$[Tmp + 2] = "FP" + Stk$[Tmp + 2]
        END IF
        CASE "remove$"
        Stk$[Tmp]= "$$RemoveStr$"
        Use_Remove = Use_StrStr = UseFlag = TRUE
        CASE "replace$"
        Stk$[Tmp]= "$$replace$"
        Use_Replace = Use_StrStr = UseFlag = TRUE
        CASE "right$"
        Stk$[Tmp]= "$$right$"
        Use_Right = UseFlag = TRUE
        CASE "rename"
        Stk$[Tmp]= "rename"
        CASE "register"
        Stk$[Tmp]= "register"
        CASE "randomize"
        Stk$[Tmp]= "randomize"
        Use_Randomize = TRUE
        Use_Rnd   = TRUE
        IF Ndx = 1 THEN
          Use_Timer = TRUE
          Stk$[1] ="randomize(timer())"
        END IF
        CASE "rec"
        IF DataType(Stk$[Tmp + 2]) = vt_NUMBER THEN
          Stk$[Tmp + 2] = "FP" + Stk$[Tmp + 2]
        END IF
        Stk$[Tmp] = "rec(" + Stk$[Tmp + 2] + "," + Stk$[Tmp + 2] + "len)"
        Stk$[Tmp + 1] = ""
        Stk$[Tmp + 2] = ""
        Stk$[Tmp + 3] = ""
        Use_Rec = TRUE
        CASE "reccount"
        DIM RAW length$
        IF DataType(Stk$[Tmp + 2]) = vt_NUMBER THEN
          Stk$[Tmp + 2] = "FP" + Stk$[Tmp + 2]
        END IF
        Stk$[Tmp] = "reccount"
        length$ = Stk$[Tmp + 2] + "len)"
        FOR i = Tmp+1 TO Ndx
          IF *Stk$[i] = ASC(")") THEN
            Stk$[i] = ""
            EXIT FOR
          END IF
          Stk$[Tmp] = Stk$[Tmp] + Stk$[i]
          Stk$[i] = ""
        NEXT i
        Stk$[Tmp] = Stk$[Tmp] + "," + length$
        Use_RecCount = TRUE
        CASE "reclen"
        Stk$[Tmp] = "reclen"
        CASE "record"
        Stk$[Tmp] = "record"
        CASE "remain$"
        Stk$[Tmp]= "$$remain$"
        Use_Remain = UseFlag = TRUE
        CASE "retain$"
        Stk$[Tmp]= "$$Retain$"
        Use_Retain = UseFlag = TRUE
        CASE "repeat$"
        Stk$[Tmp]= "$$repeat$"
        Use_Repeat = UseFlag = TRUE
        CASE "reverse$"
        Stk$[Tmp]= "$$reverse$"
        Use_Reverse = UseFlag = TRUE
        CASE "rgb"
        Stk$[Tmp]= "RGB"
        CASE "rmdir"
        Stk$[Tmp]= "rmdir"
        CASE "rnd"
        Stk$[Tmp]= "rnd()"
        IF Stk$[Tmp+1]= "(" AND Stk$[Tmp+2]= ")" THEN
          Stk$[Tmp+1] = ""
          Stk$[Tmp+2] = ""
        END IF
        Use_Rnd = TRUE
        CASE "round"
        Stk$[Tmp]= "Round"
        Use_Round = TRUE
        CASE "rpad$"
        Stk$[Tmp]= "$$rpad$"
        Use_Rpad = UseFlag = TRUE
        CASE "rtrim$"
        Stk$[Tmp]= "$$rtrim$"
        Use_Rtrim = UseFlag = TRUE
        CASE "run"
        Stk$[Tmp]= "Run"
        Use_Run = TRUE
      END SELECT
      CASE  19
      SELECT CASE Keyword$
        CASE "scanerror"
        Stk$[Tmp] = "ScanError"
        CASE "sprint"
        Stk$[Tmp]= "sprint"
        CASE "spc$"
        Stk$[Tmp] = "SPC$"
        Use_SPC = UseFlag = TRUE
        CASE "str$"
        Stk$[Tmp]= "$$str$"
        Use_Str = UseFlag = TRUE
        CASE "strl$"
        Stk$[Tmp]= "$$strl$"
        Use_Strl = UseFlag = TRUE
        CASE "searchpath$"
        Stk$[Tmp]= "$$SEARCHPATH$"
        Use_SearchPath =  UseFlag = TRUE
        CASE "sizeof"
        Stk$[Tmp]= "sizeof"
        CASE "setattr"
        Stk$[Tmp]= "SETATTR"
        CASE "setwindowrtftext"
        Stk$[Tmp] = "SetWindowRTFText"
        CASE "sgn"
        Stk$[Tmp]= "sgn"
        Use_Sgn = TRUE
        CASE "short"
        Stk$[Tmp] = "short"
        CASE "shell"
        Use_Shell = TRUE
        CASE "show"
        Stk$[Tmp]= "Show"
        CASE "sin"
        Stk$[Tmp]= "sin"
        CASE "sinl"
        Stk$[Tmp]= "sinl"
        CASE "single"
        Stk$[Tmp]= "float"
        CASE "sinh"
        Stk$[Tmp]= "sinh"
        CASE "sleep"
        Stk$[Tmp]= "sleep"
        CASE "space$"
        Stk$[Tmp]= "$$space$"
        Use_Space = UseFlag = TRUE
        CASE "split"
        Stk$[Tmp]= "Split"
        Use_Split = UseFlag = TRUE
        Use_Remove= TRUE
        Use_StrStr= TRUE
        Use_Mid   = TRUE
        Use_Left  = TRUE
        Use_Instr = TRUE
        Use_Stristr = TRUE
        UseLCaseTbl = TRUE
        CASE "splitbarfg"
        Stk$[Tmp]= "SplitBarFG"
        CASE "splitbarbg"
        Stk$[Tmp]= "SplitBarBG"
        CASE "sqr","sqrt"
        Stk$[Tmp]= "sqrt"
        CASE "sqrl","sqrtl"
        Stk$[Tmp]= "sqrtl"
        CASE "strarray"
        Stk$[Tmp]= "PCHAR*"
        CASE "strim$"
        Stk$[Tmp]= "$$strim$"
        Use_Strim = UseFlag = TRUE
        CASE "string"
        Stk$[Tmp]= "string"
        CASE "string$"
        Stk$[Tmp]= "$$stringx$"
        Use_String = UseFlag = TRUE
        CASE "strptr"
        Stk$[Tmp]= "STRPTR"
        Use_Strptr = TRUE
        CASE "strtoken$"
        Stk$[Tmp]= "StrToken$"
        Use_Strtoken = Use_Mid = Use_Left = Use_Extract = TRUE
        Use_Instr =Use_Instrrev = Use_Stristr = Use_Tally = Use_Remove = TRUE
        Use_StrStr = UseLCaseTbl = UseFlag = TRUE
        CASE "swap"
        Stk$[Tmp]= "swap"
        Use_Swap = TRUE
        CASE "sysdir$"
        Stk$[Tmp]= "$$sysdir$()"
        IF Stk$[Tmp+1]= "(" AND Stk$[Tmp+2]= ")" THEN
          Stk$[Tmp+1] = ""
          Stk$[Tmp+2] = ""
        END IF
        Use_Sysdir = UseFlag = TRUE
        CASE "sysstr"
        Stk$[Tmp] = "SysStr"
        Use_SysStr = TRUE
      END SELECT
      CASE  20
      SELECT CASE Keyword$
        CASE "tab$"
        Stk$[Tmp] = "TAB$"
        Use_TAB = UseFlag = TRUE
        CASE "true"
        Stk$[Tmp]= "TRUE"
        CASE "trim$"
        Stk$[Tmp]= "$$trim$"
        Use_Trim = UseFlag = TRUE
        CASE "tally"
        Stk$[Tmp]= "tally"
        Use_Tally = UseLCaseTbl = Use_Stristr = Use_StrStr = TRUE
        CASE "tan"
        Stk$[Tmp]= "tan"
        CASE "tanh"
        Stk$[Tmp]= "tanh"
        CASE "tanl"
        Stk$[Tmp]= "tanl"
        CASE "tempdir$"
        Stk$[Tmp]= "$$tempdir$()"
        IF Stk$[Tmp+1]= "(" AND Stk$[Tmp+2]= ")" THEN
          Stk$[Tmp+1] = ""
          Stk$[Tmp+2] = ""
        END IF
        Use_Tempdir = UseFlag = Use_Exist = TRUE
        CASE "tempfilename$"
        Stk$[Tmp] = "$$TempFileName$"
        Use_TempFileName = UseFlag = TRUE
        Use_Exist = Use_Rnd = TRUE
        ' *********************************************************
        ' Special Case Handler: Substitute "This." with "This->"
        ' *********************************************************
        CASE "this"
        Stk$[Tmp] = "this"
        IF *Stk[Tmp+1] = ASC(".") THEN
          Stk$[Tmp+1] = "->" & MID$(Stk$[Tmp+1],2)
        END IF
        CASE "time$"
        IF Stk$[Tmp+1] <> "("  THEN
          Stk$[Tmp] = "$$timef$()"
        ELSE
          Stk$[Tmp] = "$$timef$"
        END IF
        IF Stk$[Tmp+1]= "(" AND Stk$[Tmp+2]= ")" THEN
          Stk$[Tmp+1] = ""
          Stk$[Tmp+2] = ""
        END IF
        Use_Time = UseFlag = TRUE
        CASE "timer"
        Stk$[Tmp]= "timer()"
        IF Stk$[Tmp+1]= "(" AND Stk$[Tmp+2]= ")" THEN
          Stk$[Tmp+1] = ""
          Stk$[Tmp+2] = ""
        END IF
        Use_Timer =  TRUE
      END SELECT
      CASE  21
      SELECT CASE Keyword$
        CASE "uint"
        Stk$[Tmp]= "UINT"
        CASE "ushort"
        Stk$[Tmp] = "USHORT"
        CASE "ulong"
        Stk$[Tmp] = "ULONG"
        CASE "ulonglong"
        Stk$[Tmp] = "ULONGLONG"
        CASE "ucase$"
        Stk$[Tmp]= "$$ucase$"
        Use_Ucase = UseFlag = TRUE
        Use_StrUpLow = TRUE
        CASE "ubound"
        Stk$[Tmp]= "ubound"
        Use_Ubound = TRUE
        CASE "using$"
        Stk$[Tmp] = "$$Using$"
        Use_Using = UseFlag = TRUE
        '/***** 2010-11-18 Added for new Constructor/Desctructor syntax -AIR *****/
        CASE "using"
        Stk$[Tmp]= "using"

      END SELECT
      CASE  22
      SELECT CASE Keyword$
        CASE "val"
        Stk$[Tmp]= "VAL"
        Use_Val = TRUE
        CASE "vall"
        Stk$[Tmp]= "VALL"
        Use_Vall = TRUE
        CASE "variant"
        Stk$[Tmp]= "VARIANT"
        CASE "varptr"
        Stk$[Tmp]= ""
        CASE "vchr$"
        Stk$[Tmp] = "$$vchr$"
        Use_VChr = UseFlag = TRUE
        '/***** 2010-12-01 Added to support Abstract Classes  -AIR *****/
        CASE "virtual"
        Stk$[Tmp]="virtual"
        Use_Virtual = TRUE
        CASE "vt$"
        Stk$[Tmp] = "VT$"
        Use_VT = UseFlag = TRUE
        CASE "verify"
        Stk$[Tmp] = "Verify"
        Use_Verify = Use_Mid = UseFlag = TRUE
      END SELECT
      CASE  23
      SELECT CASE Keyword$
        CASE "widetoansi$"
        Stk$[Tmp] = "$$WideToAnsi$"
        Use_WideToAnsi = UseFlag = TRUE
      END SELECT
    END SELECT
  NEXT
  IF CompPtr = 1 THEN CALL RemEmptyTokens
  '************************************************************
  ' Moved the WITH/END WITH handling here from the Emit sub
  ' The ill formed variables would cause conflict with the new
  ' AsmUnKnown structs function.
  '************************************************************
  IF WithCnt THEN
    FOR i = 1 TO Ndx
      'IF LEFT$(Stk$[i],1) = "." AND NOT IsNumber(MID$(Stk$[i],2,1)) THEN
      IF LEFT$(Stk$[i],2) = "->" OR (LEFT$(Stk$[i],1) = "." AND NOT IsNumber(MID$(Stk$[i],2,1))) THEN
        IF WithVar$[WithCnt] = "this" THEN
          Stk$[i] = "->" + MID$(Stk$[i],2)
        END IF
        IF i = 1 THEN
          Stk$[i] = WithVar$[WithCnt] + Stk$[i]
        ELSE
          IF NOT IsReservedWord(Stk$[i-1]) THEN
            IF NOT (isalpha(Stk[i-1][LEN(Stk$[i-1]-1)]) OR IsNumber(RIGHT$(Stk$[i-1],LEN(Stk$[i-1]-1)))) THEN
              Stk$[i] = WithVar$[WithCnt] + Stk$[i]
            END IF
          ELSE
            Stk$[i] = WithVar$[WithCnt] + Stk$[i]
          END IF
        END IF
        WHILE (isalpha(*Stk[i+1]) OR *Stk[i+1] = ASC(".")) AND (i < Ndx)
          INCR i
        WEND
      END IF
    NEXT
  END IF
  '************************************************************
  ' handle programming style global and locals using same name
  '************************************************************
  IF CompToken = 1 THEN
    Keyword$ = LCASE$(Stk$[1])
    SELECT CASE Keyword$
      CASE "dim"         :  CompToken = 0
      CASE "local"       :  CompToken = 0
      CASE "global"      :  CompToken = 0
      CASE "static"      :  CompToken = 0
      CASE "shared"      :  CompToken = 0
      CASE "raw"         :  CompToken = 0
      CASE "dynamic"     :  CompToken = 0
      CASE "free"        :  CompToken = 0
      CASE "redim"       :  CompToken = 0
      CASE "sub"         :  CompToken = 0
      CASE "function"    :  CompToken = 0
      CASE "overloaded"  :  CompToken = 0
      CASE "public"      :  CompToken = 0
      CASE "declare"     :  CompToken = 0
      CASE "c_declare"   :  CompToken = 0
      CASE "auto"        :  CompToken = 0
      CASE "register"    :  CompToken = 0
      CASE "extern"      :  CompToken = 0
      CASE ELSE          :  CALL AsmUnknownStructs(1)
    END SELECT
  END IF
END SUB 'TokenSubstitutions
SUB JoinStrings( i, inif )
  '************************
  DIM RAW DoJoin   = 0
  DIM RAW InBrace  = 0
  DIM RAW OnlyPara = 0
  DIM RAW j  = 0
  DIM RAW l  = 0
  DIM RAW sj = i
  DIM RAW t$
  DIM RAW vt
  '************************
  WHILE i <= Ndx
    t$ = LCASE$(Stk$[i])
    IF NOT j AND NOT OnlyPara AND NOT InBrace THEN
      vt = DataType(t$)
      IF vt = vt_STRVAR OR vt = vt_STRLIT THEN
        sj = i
        INCR i
        ITERATE
      END IF
    END IF
    SELECT CASE t$
      CASE "&"
      IF OnlyPara THEN EXIT SELECT
      vt = DataType(Stk$[i+1])
      IF vt <> vt_STRVAR AND vt <> vt_STRLIT THEN
        vt = DataType(Stk$[i-1])
      END IF
      IF vt = vt_STRVAR OR vt = vt_STRLIT THEN
        j++
        Stk$[i] = ","
        t$ = ""
      END IF
      CASE "["
      INCR InBrace
      CASE "]"
      DECR InBrace
      CASE "("
      IF Stk$[i+1] <> "*" THEN
        CALL JoinStrings(i+1, inif)
        l = i-1
        WHILE Stk$[i] <> ")"
          Stk$[l] = Stk$[l] + Stk$[i] + " "
          Stk$[i] = ""
          i++
        WEND
        CONCAT(Stk$[l], Stk$[i])
        Stk$[i] = ""
      END IF
      CASE ")"
      IF j THEN
        Stk$[sj] = "join$(" + STR$(j+1) + "," + Stk$[sj]
        j = sj + 1
        WHILE j < i
          CONCAT(Stk$[sj], Stk$[j])
          Stk$[j] = ""
          j++
        WEND
        CONCAT(Stk$[sj], ")")
      END IF
      EXIT SUB
      CASE "||"
      Stk$[i] = " or "
      DoJoin = TRUE
      CASE "&&"
      Stk$[i] = " and "
      DoJoin = TRUE
      CASE "then", "for"
      DoJoin = TRUE
      CASE "="
      IF NOT inif THEN
        OnlyPara = TRUE
      ELSE
        DoJoin = TRUE
      END IF
      CASE "if", "elseif", "while"
      inif = TRUE
      sj = i + 1
      CASE  "sprint", "lprint", "fprint", "fprintf", "print", "print#"
      OnlyPara = TRUE
      CASE ELSE
      IF LEFT$(Stk$[i],2) = "]." OR LEFT$(Stk$[i],3) = "]->" THEN
        DECR InBrace
      END IF
    END SELECT
    IF (DoJoin OR INCHR(",+-*/^;:<>~|&", t$)) AND NOT OnlyPara AND NOT InBrace THEN
      DoJoin = 0
      IF j THEN
        Stk$[sj] = "join$(" + STR$(j+1) + "," + Stk$[sj]
        j = sj
        j++
        WHILE j < i
          CONCAT(Stk$[sj], Stk$[j])
          Stk$[j] = ""
          j++
        WEND
        CONCAT(Stk$[sj], ")")
      END IF
      j = 0
      sj = i + 1
    END IF
    INCR i
  WEND
  IF j THEN
    Stk$[sj] = "join$(" + STR$(j+1) + "," + Stk$[sj]
    j = sj
    j++
    WHILE j <= i
      CONCAT(Stk$[sj], Stk$[j])
      Stk$[j] = ""
      j++
    WEND
    CONCAT(Stk$[sj], ")")
  END IF
END SUB ' JoinStrings
SUB Transforms()
  '****************
  DIM RAW nBrace
  DIM RAW CntMarker
  DIM RAW IFCond
  DIM RAW a
  DIM RAW i
  DIM RAW j
  DIM RAW Keyword$
  DIM RAW lszTmp$
  '****************
  Keyword$ = ""
  lszTmp$  = ""
  IF Ndx = 3 AND NOT WithCnt THEN
    IF Stk$[2] = "+" AND Stk$[3] = "+" THEN
      FPRINT Outfile,Scoot$,Clean$(Stk$[1]);"++;"
      Ndx = 0
      Statements++
      EXIT SUB
    END IF
    IF Stk$[2] = "-" AND Stk$[3] = "-" THEN
      FPRINT Outfile,Scoot$,Clean$(Stk$[1]);"--;"
      Ndx = 0
      Statements++
      EXIT SUB
    END IF
    IF Stk$[1] = "+" AND Stk$[2] = "+" THEN
      FPRINT Outfile,Scoot$,"++";Clean$(Stk$[3]);";"
      Ndx = 0
      Statements++
      EXIT SUB
    END IF
    IF Stk$[1] = "-" AND Stk$[2] = "-" THEN
      FPRINT Outfile,Scoot$,"--";Clean$(Stk$[3]);";"
      Ndx = 0
      Statements++
      EXIT SUB
    END IF
  END IF
  Keyword$ = LCASE$(Stk$[1])
  a = INCHR("abcdefghijklmnopqrstuvwxyz$", Keyword$)
  SELECT CASE a
    CASE 3
    IF Keyword$ = "case" THEN
      nBrace = 0
      CntMarker = 2
      j = 0
      FOR i = 2 TO Ndx
        IF INCHR("([",Stk$[i]) THEN nBrace++
        IF INCHR(")]",Stk$[i]) THEN nBrace--
        IF Stk$[i] = ","  THEN
          IF nBrace=0 THEN CntMarker = i + 1
        END IF
        IF iMatchWrd(Stk$[i],"to") THEN
          j = 1
          Stk$[i] = " and <="
          Stk$[CntMarker] = ">=" + Stk$[CntMarker]
        END IF
      NEXT
      IF j=1 THEN
        Src$ = ""
        FOR i = 1 TO Ndx
          Src$ = Src$ + Stk$[i] + " "
        NEXT
        CALL XParse(Src$)
      END IF
      EXIT SUB
    END IF
    CASE 4
    '**************************************************************************
    ' The following code introduces the following DLL declarations to BCX
    '**************************************************************************
    '  DECLARE FUNCTION Foo LIB "FOO.DLL" ALIAS "FooA" ( A$ )
    '                     OR
    '  DECLARE FUNCTION Foo LIB "FOO.DLL" ( A$ ) - Alias will default to "FOO"
    '  [5.08.1102] Foo = (BCXFPROTx)GetProcAddress(H_FOO, "FooA");
    '**************************************************************************
    IF Keyword$ = "declare" AND iMatchWrd(Stk$[4],"lib") THEN
      DIM RAW alias$, i, idx=-1, AR_DllName$
      REMOVE DQ$ FROM Stk$[5]
      FOR i = 0 TO LoadLibsCnt - 1
        IF Stk$[5] = Loadlibs$[i] THEN
          idx = i
          EXIT FOR
        END IF
      NEXT i
      IF idx < 0 THEN
        Loadlibs$[LoadLibsCnt] = Stk$[5]
        INCR LoadLibsCnt
      END IF
      IF iMatchWrd(Stk$[6],"alias") THEN
        alias$ = Stk$[7]
        Stk$[6] = ""
        Stk$[7] = ""
      ELSE
        alias$ = ENC$(Stk$[3])
      END IF

      INCR DllCnt
      IF DllCnt > 799 THEN Abort("Maximum number of declarations exceded.")

      IF INCHR(Stk$[5],"-") THEN
        AR_DllName$ = EXTRACT$(Stk$[5], "-")
      ELSEIF INCHR(Stk$[5],".") THEN
        AR_DllName$ = EXTRACT$(Stk$[5], ".")
      END IF

      DllDecl$ [DllCnt] = "static BCXFPROT" + LTRIM$(STR$(DllCnt)) + SPC$ + Clean$(Stk$[3]) + "=(BCXFPROT" + LTRIM$(STR$(DllCnt)) + _
      ")dlsym(H_" + UCASE$(AR_DllName$) + ", " + alias$ + ");"

      Stk$[4] = ""
      Stk$[5] = ""
      EXIT SUB
    END IF
    CASE 7
    IF Keyword$ = "get$" THEN
      Stk$[1] = "~get"
      EXIT SUB
    END IF
    IF Keyword$ = "global" AND iMatchWrd(Stk$[2],"dynamic") THEN
      Stk$[1] = "global"
      EXIT SUB
    END IF
    CASE 9
    IF Keyword$ = "iremove" THEN
      '***********************************************************
      '  Translate   IREMOVE UCASE$("aaa") FROM LTRIM$(RTRIM$(A$))
      '  into   A$ = IREMOVE$(LTRIM$(RTRIM$(A$)),UCASE$("aaa"))
      '***********************************************************
      DIM RAW Mat$, Fat$
      Mat$ = "" : Fat$ = ""
      FOR i = 2 TO Ndx
        IF iMatchWrd(Stk$[i],"from") THEN
          Stk$[i]= ""
          EXIT FOR
        END IF
      NEXT
      FOR j = 2 TO i
        CONCAT(Mat$,Stk$[j]) ' build match string
      NEXT
      FOR j = i TO Ndx
        CONCAT(Fat$,Stk$[j]) ' build fat source
      NEXT
      lszTmp$ = "=iremove$(" + Fat$ + "," + Mat$ + ")"
      FastLexer(Fat$," ()","")
      lszTmp$ = Stk$[Ndx] + lszTmp$
      CALL XParse(lszTmp$)
      CALL TokenSubstitutions
      CALL Emit
      Ndx = 0
      EXIT SUB
    END IF
    IF Keyword$ = "ireplace" THEN
      '**********************************************************
      '  IREPLACE "this" WITH "that" IN A$ is transformed into
      '  A$ = ireplace$ ( A$, "this", "that" )
      '  BCX 3.73 introduces CASE INSENSITIVE REPLACE
      '**********************************************************
      IF Ndx < 6 THEN Abort("Problem with IREPLACE statement")
      DIM RAW W, I, VV$, RR$, WW$
      VV$ = "" : RR$ = "" : WW$ = ""
      FOR W = 2 TO Ndx
        IF iMatchWrd(Stk$[W],"with") THEN
          Stk$[W]= ""
          EXIT FOR
        END IF
      NEXT
      FOR I = 2 TO Ndx
        IF iMatchWrd(Stk$[I],"in") THEN
          Stk$[I]= ""
          EXIT FOR
        END IF
      NEXT
      i = I+1
      FOR j = i TO Ndx
        CONCAT (VV$,Stk$[j])
      NEXT
      FOR j = 2 TO W
        CONCAT (RR$,Stk$[j])
      NEXT
      i = W+1
      FOR j = i TO I
        CONCAT (WW$,Stk$[j])
      NEXT
      lszTmp$ = "=ireplace$(" + VV$ + "," + RR$ + "," + WW$ + ")"
      FastLexer(VV$," ()","")
      lszTmp$ = Stk$[Ndx] + lszTmp$
      CALL XParse(lszTmp$)
      CALL TokenSubstitutions
      CALL Emit
      Ndx = 0
      EXIT SUB
    END IF
    CASE 12
    IF Keyword$ = "local" AND iMatchWrd(Stk$[2],"dynamic") THEN
      Stk$[1] = "dim"
      EXIT SUB
    END IF
    CASE 16
    IF Keyword$ = "put$" THEN
      Stk$[1] = "~put"
      EXIT SUB
    END IF
    CASE 18
    IF Keyword$ = "remove" THEN
      '***********************************************************
      '  Translate   REMOVE UCASE$("aaa") FROM LTRIM$(RTRIM$(A$))
      '  into   A$ = REMOVE$(LTRIM$(RTRIM$(A$)),UCASE$("aaa"))
      '***********************************************************
      DIM RAW Mat$, Fat$
      Mat$ = ""
      Fat$ = ""
      FOR i = 2 TO Ndx
        IF iMatchWrd(Stk$[i],"from") THEN
          Stk$[i]= ""
          EXIT FOR
        END IF
      NEXT
      FOR j = 2 TO i
        CONCAT(Mat$,Stk$[j]) ' build match string
      NEXT
      FOR j = i TO Ndx
        CONCAT(Fat$,Stk$[j]) ' build fat source
      NEXT
      lszTmp$ = "=remove$(" + Fat$ + "," + Mat$ + ")"
      FastLexer(Fat$," ()","")
      lszTmp$ = Stk$[Ndx] + lszTmp$
      CALL XParse(lszTmp$)
      CALL TokenSubstitutions
      CALL Emit
      Ndx = 0
      EXIT SUB
    END IF
    IF Keyword$ = "replace" THEN
      '*******************************************************
      '  REPLACE "this" WITH "that" IN A$ is transformed into
      '  A$ = replace$ ( A$, "this", "that" )
      '  BCX 2.93 allows expressions and arrays to be used
      '*******************************************************
      IF Ndx < 6 THEN Abort("Problem with REPLACE statement")
      DIM RAW W, I, VV$, RR$, WW$
      VV$ = ""
      RR$ = ""
      WW$ = ""
      FOR W = 2 TO Ndx
        IF iMatchWrd(Stk$[W],"with") THEN
          Stk$[W]= ""
          EXIT FOR
        END IF
      NEXT
      FOR I = 2 TO Ndx
        IF iMatchWrd(Stk$[I],"in") THEN
          Stk$[I]= ""
          EXIT FOR
        END IF
      NEXT
      i = I+1
      FOR j = i TO Ndx
        CONCAT (VV$,Stk$[j])
      NEXT
      FOR j = 2 TO W
        CONCAT (RR$,Stk$[j])
      NEXT
      i = W+1
      FOR j = i TO I
        CONCAT (WW$,Stk$[j])
      NEXT
      lszTmp$ = "=replace$(" + VV$ + "," + RR$ + "," + WW$ + ")"
      FastLexer(VV$," ()","")
      lszTmp$ = Stk$[Ndx] + lszTmp$
      CALL XParse(lszTmp$)
      CALL TokenSubstitutions
      CALL Emit
      Ndx = 0
      EXIT SUB
    END IF
    CASE 27
    SELECT CASE Keyword$
      '**************************
      CASE "$ifndef"
      Stk$[1] = "~ifndef"
      InConditional++
      '**************************
      CASE "$if","$ifdef"
      Stk$[1] = "~if"
      InConditional++
      '**************************
      CASE "$else"
      Stk$[1] = "~else"
      '**************************
      CASE "$elseif"
      Stk$[1] = "~elseif"
      '**************************
      CASE "$endif"
      Stk$[1] = "~endif"
      InConditional--
      IF InConditional < 0 THEN 'simple check to see if to see if conditionals are balanced
        Abort("To many $ENDIFs")
      END IF
      '**************************
      CASE "$cpp"
      Ndx = 0
      UseCpp = TRUE
      '**************************
      CASE "$CPP"
      Ndx = 0
      UseCpp = TRUE
    END SELECT
    EXIT SUB
  END SELECT
  IFCond = 0
  FOR i = 1 TO Ndx
    IF iMatchWrd(Stk$[i],"if") THEN IFCond = i + 1
    IF iMatchWrd(Stk$[i],"then") AND iMatchWrd(Stk$[i+1],"if") THEN
      FOR j = i + 2 TO Ndx
        IF iMatchWrd(Stk$[j],"else") THEN
          EXIT FOR
        END IF
      NEXT
      IF j > Ndx THEN ' safe to transform
        FOR j = i TO IFCond + 1 STEP -1
          Stk$[j] = Stk$[j - 1]
        NEXT
        Stk$[IFCond] = "("
        i++
        Stk$[i] = ")"
        i++
        FOR j = Ndx TO i STEP -1
          Stk$[j + 2] = Stk$[j]
        NEXT
        Ndx++
        Ndx++
        Stk$[i] = "&&"
        i++
        Stk$[i] = "("
        i++
        FOR i = i TO Ndx
          IF iMatchWrd(Stk$[i],"then") THEN
            Ndx++
            FOR j = Ndx TO i STEP -1
              Stk$[j] = Stk$[j - 1]
            NEXT
            Stk$[i] = ")"
            EXIT FOR
          END IF
        NEXT
        i--
      ELSE
        EXIT FOR
      END IF
    END IF
  NEXT
END SUB ' Transforms
SUB Parse(Arg$)
  '****************
  DIM RAW A, B
  DIM RAW CommaCnt
  DIM RAW Tmp
  DIM RAW i
  DIM RAW j
  DIM RAW k
  DIM RAW lszTmp$
  DIM RAW L_Stk_1$
  DIM RAW L_Stk_2$
  DIM RAW Var1$
  DIM RAW Plus2Amp = 0
  DIM RAW vt
  '****************
  L_Stk_1$ = ""
  L_Stk_2$ = ""
  lszTmp$  = ""
  Var1$    = ""
  '****************
  CALL XParse(Arg$)
  PassOne = 0
  IF NOT iMatchWrd(Stk$[1],"function")  THEN
    Plus2Amp = iMatchNQ(Arg$, "&")
    FOR Tmp = 2 TO Ndx-1
      IF Stk$[Tmp] = "+" THEN
        vt = DataType(Stk$[Tmp+1])
        IF vt = vt_STRVAR OR vt = vt_STRLIT THEN
          Stk$[Tmp] = "&"
          Plus2Amp = TRUE
        ELSE
          vt = DataType(Stk$[Tmp-1])
          IF vt = vt_STRVAR OR vt = vt_STRLIT THEN
            Stk$[Tmp] = "&"
            Plus2Amp = TRUE
          END IF
        END IF
      END IF
    NEXT
    IF Plus2Amp > 0 THEN
      Use_Join = UseFlag = TRUE
      j = 0
      k = 0
      FOR Tmp = 1 TO Ndx-1
        A = CheckLocal(Stk$[Tmp], &i)
        IF A = vt_UNKNOWN THEN A = CheckGlobal(Stk$[Tmp], &i)
        IF A = vt_STRUCT OR A = vt_UDT OR A = vt_UNION THEN 'added vt_UNION 4.40
          j = 1
        END IF
        IF Stk$[Tmp] = "&" THEN
          A = DataType(Stk$[Tmp+1])
          IF A = vt_STRVAR OR A = vt_STRLIT THEN
            k = 1
          ELSE
            A = DataType(Stk$[Tmp-1])
            IF A = vt_STRVAR OR A = vt_STRLIT THEN
              k = 1
            END IF
          END IF
        END IF
      NEXT
      IF k THEN
        IF j THEN CALL AsmUnknownStructs(0)
        CALL JoinStrings(1, 0)
        Src$ = ""
        FOR i = 1 TO Ndx
          IF Stk[i][0] THEN
            Src$ = Src$ + Stk$[i] + " "
          END IF
        NEXT
        CALL XParse(Src$)
      END IF
    END IF
  END IF
  '***********************************************************
  'Moved here by Mike H. Was being applied too early.
  'causing lines with multiple statements to not receive the
  'conversion. i.e. sp->lpVtbl->Release(sp) : sp = NULL
  '***********************************************************
  IF UseCpp THEN
    IF iMatchNQ(Src$,"->lpVtbl") THEN
      FOR INTEGER i= 1 TO Ndx
        IF iMatchRgt(Stk$[i],"->lpVtbl") THEN
          Stk$[i] = EXTRACT$(Stk$[i],"->lpVtbl")
          IF (Stk$[i+3] = Stk$[i-1] OR Stk$[i+3] = Stk$[i]) AND Stk$[i+3] <> ")" THEN
            Stk$[i+3] = ""
            IF Stk$[i+4] = "," THEN Stk$[i+4] = ""
          END IF
        END IF
      NEXT
      CALL RemEmptyTokens
    END IF
  END IF
  '********************************************************************
  '  At this point we have a fresh set of Stk$[] values, totaling Ndx
  '                Start handling some unique situations
  '********************************************************************
  CALL TokenSubstitutions
  IF Ndx = 0 THEN EXIT SUB
  CALL Transforms
  IF Ndx = 0 THEN EXIT SUB
  '***********************************************************
  'Modification to allow 2 names as function types
  '***********************************************************
  IF iMatchWrd(Stk$[1],"function") THEN
    IF iMatchWrd(Stk$[Ndx-2],"as") AND Stk$[Ndx] <> ")" THEN
      IF NOT iMatchWrd(Stk$[Ndx],"export") AND NOT iMatchWrd(Stk$[Ndx],"stdcall") THEN
        Stk$[Ndx-1] = Stk$[Ndx-1] + " " + Stk$[Ndx]
        Ndx--
      END IF
    END IF
  END IF
  '********************************************************************
  'Modification to allow 2 names as argument types in sub or function
  '********************************************************************
  IF iMatchWrd(Stk$[1],"function") OR iMatchWrd(Stk$[1],"sub") THEN
    DIM RAW offset
    DIM RAW LastBrk = Ndx - 2
    FOR i = Ndx TO 3 STEP -1
      IF Stk$[i] = ")" THEN
        LastBrk = i
        EXIT FOR
      END IF
    NEXT
    FOR i = 3 TO LastBrk
      offset = 2
      IF iMatchWrd(Stk$[i],"as") AND (i < LastBrk) AND Stk$[i + offset] <> "=" THEN
        IF iMatchWrd(Stk$[i+1],"function") THEN offset = 3
        IF NOT INCHR(Stk$[i + offset],")") AND NOT INCHR(Stk$[i + offset],",") THEN
          IF LEN(Stk$[i + offset]) <> 0 AND NOT iMatchWrd(Stk$[i + 3],"as") THEN
            Stk$[i+offset-1] = Stk$[i+offset-1] + " " + Stk$[i+offset]
            Stk$[i + offset] = ""
          END IF
        END IF
      END IF
    NEXT
  END IF
  '***********************************************************
  'DynaCall Handler
  IF NOT iMatchWrd(Stk$[1],"declare") THEN
    FOR i = 1 TO Ndx
      IF iMatchWrd(Stk$[i],"lib") THEN
        IF Stk$[i-1] = "(" AND (DataType(Stk$[i+1]) = vt_STRLIT OR DataType(Stk$[i+1]) = vt_STRVAR) THEN
          j = GetNumArgs(i+2)
          lszTmp$ = "BCX_DynaCall"
          IF NOT iMatchWrd(Stk$[1],"print") THEN 'print does its own casting
            IF DataType(Stk$[i-2]) = vt_STRVAR OR DataType(Stk$[1]) = vt_STRVAR THEN
              lszTmp$ = "(char*)" & lszTmp$
            END IF
          END IF
          Var1$ = RIGHT$(Stk$[i-2], 1)
          IF INCHR ("!$#¦%", Var1$) THEN
            CONCAT (lszTmp$, Var1$)
            Stk$[i] = ENC$(LEFT$(Stk$[i-2], LEN(Stk$[i-2]) - 1))
          ELSE
            Stk$[i] = ENC$(Stk$[i-2])
          END IF
          Stk$[i-2] = lszTmp$
          FOR B = Ndx+3 TO i+3 STEP -1
            Stk$[B] = Stk$[B-3]
          NEXT
          Stk$[i+2] = Stk$[i+1]
          Stk$[i+1] = ","
          Stk$[i+3] = ","
          Stk$[i+4] = LTRIM$(STR$(j))
          Stk$[i+5] = IIF$(j, ",", ")")
          INCR Ndx, 3
          Use_Dynacall = TRUE
        END IF
      END IF
    NEXT
  END IF
  '****************[ Exponentiation Operator Handler ]******************
  IF INCHR(Arg$,"^") THEN
    DIM RAW lp = 0
    DIM RAW rp = 0
    Test = FALSE
    FOR i = 1 TO Ndx
      IF Stk$[i] = "^" THEN
        Test = TRUE
        IF Stk$[i+1] = "-" THEN
          Ndx++
          FOR A = Ndx TO i+2 STEP -1
            Stk$[A] = Stk$[A-1]
          NEXT
          Stk$[i+1] = "("
          B = i+3
          IF Stk$[B] = "(" THEN
            lp=0
            rp=0
            DO
              IF Stk$[B] = "(" THEN lp++
              IF Stk$[B] = ")" THEN rp++
              B++
            LOOP UNTIL lp = rp
            Ndx++
            j = B+1
            FOR A = Ndx TO j STEP -1
              Stk$[A] = Stk$[A-1]
            NEXT
            Stk$[B] = ")"
          ELSE
            B=i+4
            IF INCHR("[",Stk$[B]) THEN
              DO
                B++
              LOOP UNTIL INCHR("]",Stk$[B])
              Ndx++
              j = B+2
              FOR A = Ndx TO j STEP -1
                Stk$[A] = Stk$[A-1]
              NEXT
              Stk$[B+1] = ")"
            ELSE
              IF INCHR("(",Stk$[B]) THEN
                DO
                  B++
                LOOP UNTIL INCHR(")",Stk$[B])
                Ndx++
                j = B+2
                FOR A = Ndx TO j STEP -1
                  Stk$[A] = Stk$[A-1]
                NEXT
                Stk$[B+1] = ")"
              ELSE
                Ndx++
                j = B+1
                FOR A = Ndx TO j STEP -1
                  Stk$[A] = Stk$[A-1]
                NEXT
                Stk$[B] = ")"
              END IF
            END IF
          END IF
        END IF
      END IF
    NEXT
    IF Test THEN
      FOR i = 1 TO  Ndx
        IF Stk$[i] = "^" THEN
          A = i - 1
          B = 0
          WHILE Stk$[A] <> "="
            IF Stk$[A] = "]" THEN B++
            IF Stk$[A] = ")" THEN B++
            IF Stk$[A] = "[" THEN B--
            IF Stk$[A] = "(" THEN B--
            IF B = 0 THEN EXIT WHILE
            A--
          WEND
          IF Stk$[A] = "[" THEN A--
          IF Stk$[A] = "=" THEN A++
          IF Stk$[A] = "(" THEN
            B = DataType(Stk$[A-1]) ' check if it's a function
            IF NOT iMatchWrd(Stk$[A-1], "print") AND  _
              (B = vt_INTEGER OR B = vt_SINGLE OR B = vt_DOUBLE) THEN
              A--
            END IF
          END IF
          Arg$ = "pow("
          B = A - 1
          WHILE B > 0
            Arg$ = Stk$[B] + " " + Arg$ + " "
            B--
          WEND
          FOR B = A TO i - 1
            Arg$ = Arg$ + " " + Stk$[B]
          NEXT
          CONCAT (Arg$, ",")
          A = i + 1
          B = DataType(Stk$[A])
          IF (Stk$[A + 1] = "(" OR Stk$[A + 1] = "[") AND _
            (B = vt_INTEGER OR B = vt_SINGLE OR B = vt_DOUBLE) THEN
            A++
          END IF
          B = 0
          WHILE A <= Ndx
            IF Stk$[A] = "[" THEN B++
            IF Stk$[A] = "(" THEN B++
            IF Stk$[A] = "]" THEN B--
            IF Stk$[A] = ")" THEN B--
            IF NOT B THEN EXIT DO
            A++
          WEND
          FOR B = i + 1 TO A
            Arg$ = Arg$ + " " + Stk$[B]
          NEXT
          CONCAT(Arg$,")")
          A++
          WHILE A <= Ndx
            Arg$ = Arg$ + " " + Stk$[A]
            A++
          WEND
          EXIT FOR
        END IF
      NEXT
      CALL Parse(Arg$)
    END IF
  END IF
  '*****************************************************
  L_Stk_1$ = LCASE$(Stk$[1]) ' Performance Optimizer
  L_Stk_2$ = LCASE$(Stk$[2]) ' Performance Optimizer
  '*****************************************************
  IF L_Stk_1$ = "$dll" THEN
    MakeDLL = NoMain = TRUE
    IF IsApple then
      LD_FLAGS$ = "-fPIC -shared $FILE$.so"
    ELSE
      LD_FLAGS$ = "-fPIC -shared -Wl,-soname,$FILE$.so"
    END IF

    Ndx = 0
    '~ IF L_Stk_2$ = "stdcall" THEN
    '~ UseStdCall = TRUE
    '~ END IF
    '~ IF NoDllMain THEN
    '~ EXIT SUB
    '~ END IF
    '~ FPRINT Outfile,""
    '~ FPRINT Outfile,"__declspec(dllexport) bool WINAPI DllMain (HINSTANCE hInst, DWORD Reason, LPVOID Reserved)"
    '~ FPRINT Outfile,"{"
    '~ FPRINT Outfile," switch (Reason)"
    '~ FPRINT Outfile," {"
    '~ FPRINT Outfile," case DLL_PROCESS_ATTACH:"
    '~ FPRINT Outfile," BCX_hInstance = hInst;"
    '~ FPRINT Outfile," break;"
    '~ FPRINT Outfile," case DLL_PROCESS_DETACH:"
    '~ FPRINT Outfile," break;"
    '~ FPRINT Outfile," case DLL_THREAD_ATTACH:"
    '~ FPRINT Outfile," break;"
    '~ FPRINT Outfile," case DLL_THREAD_DETACH:"
    '~ FPRINT Outfile," break;"
    '~ FPRINT Outfile," }"
    '~ FPRINT Outfile," return TRUE;"
    '~ FPRINT Outfile,"}\n\n"
    '~ Src$ = "GLOBAL BCX_hInstance AS HINSTANCE"
    '~ Parse(Src$)
    '~ Emit()
    EXIT SUB
  END IF
  IsCallBack = 0
  '******************************
  IF iMatchWrd(Stk$[Ndx],"callback") THEN
    IsCallBack = 1
    Ndx--
  END IF
  '******************************
  IF L_Stk_1$ = "open" THEN
    FOR A = 1 TO Ndx
      IF iMatchWrd(Stk$[A],"binary") THEN
        EXIT FOR
      END IF
    NEXT
    IF A < Ndx THEN
      A++
      Var1$ = LCASE$(Stk$[A])
      IF Var1$ = "new" THEN
        Stk$[A-1]= "binarynew"
        FOR i = A+1 TO Ndx
          Stk$[i-1]= Stk$[i]
        NEXT
        Ndx--
      END IF
      IF Var1$ = "append" THEN
        Stk$[A-1]= "binaryappend"
        FOR i = A+1 TO Ndx
          Stk$[i-1]= Stk$[i]
        NEXT
        Ndx--
      END IF
      IF Var1$ = "input" THEN
        Stk$[A-1]= "binaryinput"
        FOR i = A+1 TO Ndx
          Stk$[i-1]= Stk$[i]
        NEXT
        Ndx--
      END IF
      IF Var1$ = "output" THEN
        Stk$[A-1]= "binaryoutput"
        FOR i = A+1 TO Ndx
          Stk$[i-1]= Stk$[i]
        NEXT
        Ndx--
      END IF
    END IF
  END IF
  IF L_Stk_1$ = "option" AND L_Stk_2$ = "base" THEN
    OptionBase = VAL(Stk$[3])
    Ndx = 0
    EXIT SUB
  END IF
  '******************************
  IF L_Stk_1$   = "dim"  THEN
    IF L_Stk_2$ = "shared"    OR _
      L_Stk_2$    = "dynamic"   OR _
      L_Stk_2$    = "raw"       OR _
      L_Stk_2$    = "local"     OR _
      L_Stk_2$    = "auto"      OR _
      L_Stk_2$    = "register"  OR _
      L_Stk_2$    = "static"    THEN
      Stk$[1]     = L_Stk_2$
      L_Stk_1$    = L_Stk_2$
      FOR i = 3 TO Ndx
        Stk$[i-1]= Stk$[i]
      NEXT
      Ndx--
    END IF
  END IF
  '******************************
  IF L_Stk_1$ = "public" THEN
    IF L_Stk_2$ = "function" OR L_Stk_2$ = "sub" THEN
      Stk$[1]  = L_Stk_2$
      L_Stk_1$ = L_Stk_2$
      FOR i = 3 TO Ndx
        Stk$[i-1] = Stk$[i]
      NEXT
      Ndx--
    END IF
  END IF
  '******************************
  ' creates a static function for use in $PROJECTs
  IF L_Stk_1$ = "private" THEN
    IF L_Stk_2$ = "function" OR L_Stk_2$ = "sub" THEN
      Use_Static = TRUE
      Stk$[1]  = L_Stk_2$
      L_Stk_1$ = L_Stk_2$
      FOR i = 3 TO Ndx
        Stk$[i-1] = Stk$[i]
      NEXT
      Ndx--
    END IF
  END IF
  '******************************
  IF L_Stk_1$ = "onexit" THEN
    IF L_Stk_2$ = "sub" THEN
      Use_ExitCode = TRUE
      INCR ExitNdx
      ExitSub$[ExitNdx] = Stk$[3]
      Stk$[1]  = L_Stk_2$
      L_Stk_1$ = L_Stk_2$
      FOR i = 3 TO Ndx
        Stk$[i-1] = Stk$[i]
      NEXT
      Ndx--
    END IF
  END IF
  '******************************
  IF L_Stk_1$ = "onstart" THEN
    IF L_Stk_2$ = "sub" THEN
      Use_StartupCode = TRUE
      INCR StartNdx
      StartSub$[StartNdx] = Stk$[3]
      Stk$[1]  = L_Stk_2$
      L_Stk_1$ = L_Stk_2$
      FOR i = 3 TO Ndx
        Stk$[i-1] = Stk$[i]
      NEXT
      Ndx--
    END IF
  END IF
  '******************************
  IF L_Stk_1$ = "overloaded" AND L_Stk_2$ = "function" THEN
    Stk$[1] = "overloadedfunction"
    L_Stk_1$ = "overloadedfunction"
    FOR i = 3 TO Ndx
      Stk$[i-1]= Stk$[i]
    NEXT
    Ndx--
  END IF
  '******************************
  IF L_Stk_1$ = "overloadedfunction" AND Stk$[2] <> "=" THEN
    OkayToSend = TRUE
  END IF
  '******************************
  IF L_Stk_1$ = "overloaded" AND L_Stk_2$ = "sub" THEN
    Stk$[1]= "overloadedsub"
    FOR i = 3 TO Ndx
      Stk$[i-1] = Stk$[i]
    NEXT
    Ndx--
  END IF
  '******************************
  IF L_Stk_1$ = "function" AND iMatchWrd(Stk[3],"optional") THEN
    Stk$[1]= "optfunction"
    L_Stk_1$ = "optfunction"
    FOR i = 4 TO Ndx
      Stk$[i-1]= Stk$[i]
    NEXT
    Ndx--
  END IF
  '******************************
  IF L_Stk_1$ = "optfunction" AND Stk$[2] <> "=" THEN
    OkayToSend = TRUE
  END IF
  '******************************
  IF L_Stk_1$ = "sub" AND iMatchWrd(Stk[3],"optional") THEN
    L_Stk_1$ = "optsub"
    Stk$[1]= "optsub"
    FOR i = 4 TO Ndx
      Stk$[i-1]= Stk$[i]
    NEXT
    Ndx--
  END IF
  '******************************
  IF L_Stk_1$ = "end" AND Stk$[2] <> "=" THEN
    Stk$[1]= L_Stk_1$ + L_Stk_2$
    Ndx = 1
  END IF
  '******************************
  IF L_Stk_1$ = "function" AND Stk$[2] <> "=" THEN
    OkayToSend = TRUE
  END IF
  '******************************
  IF L_Stk_1$ = "midstr"  THEN
    CommaCnt = 0
    FOR i = 1 TO Ndx
      IF Stk$[i] = "," THEN
        INCR CommaCnt
      ELSEIF Stk$[i]= "=" THEN
        IF CommaCnt < 2 THEN
          Stk$[i] = "-1,"
        ELSE
          Stk$[i]= ""
        END IF
        Stk$[i-1]= ","
        Ndx++
        Stk$[Ndx]= ")"
        EXIT FOR
      END IF
    NEXT
  END IF
  '******************************
  IF Stk$[2]= ":" THEN
    IF Ndx = 2 THEN
      Stk$[1]= UCASE$(Stk$[1]) + ":" 'preserve the GOTO labels
      Ndx = 1
      EXIT SUB
    END IF
  END IF
  '******************************
  IF L_Stk_1$ = "case" AND L_Stk_2$ = "else" THEN
    Ndx = 1
    Stk$[1]= "caseelse"
  END IF
  '******************************
  FOR i = 1 TO Ndx
    IF iMatchWrd(Stk$[i],"let") THEN
      FOR j = i+1 TO Ndx
        Stk$[j-1] = Stk$[j]
      NEXT
      Ndx--
    END IF
  NEXT
  '******************************
  IF Stk$[Ndx]= "*" THEN
    Stk$[Ndx-1]= Stk$[Ndx-1] + "*"
    Ndx--
  END IF
  '******************************
  IF TestState = TRUE THEN
    IF LastCmd = 0 THEN
      IF Stk$[1] = "*" THEN
        Z$ = Clean$(Stk$[2])
      ELSE
        Z$ = Clean$(Stk$[1])
      END IF
      IF LEFT$(Z$,1) = "*" THEN Z$ = MID$(Z$,2)
      i = INCHR(Z$,".")
      IF i = 0 THEN i = INSTR(Z$,"->")
      IF i > 0 THEN
        IF WithCnt THEN
          Z$ = WithVar$[WithCnt]
        ELSE
          Z$ = LEFT$(Z$, i - 1)
        END IF
      END IF
      IF INCHR(Z$,"[") THEN Z$ = EXTRACT$(Z$,"[")
      IF CheckLocal(Z$, &j) = vt_UNKNOWN THEN
        IF CheckGlobal(Z$, &j) = vt_UNKNOWN THEN
          Z$ = LCASE$(Z$)
          IF Stk$[2] = "=" AND Z$ <> "functionreturn" AND Z$ <> "bcx_retstr" AND Z$ <> "end" THEN
            Warning("Assignment before Declaration in Line " + STR$(ModuleLineNos[ModuleNdx]) + " in Module: " + TRIM$(Modules$[ModuleNdx]) + ": " + Src$)
          END IF
        END IF
      END IF
    END IF
  END IF
END SUB ' Parse
SUB FuncSubDecs1(s$)
  '*****************
  DIM RAW i, j
  '*****************
  IF iMatchWrd(Stk$[1], s$) THEN
    IF DataType(Stk$[2]) = vt_STRVAR THEN
      Abort("Invalid " + s$ + "name")
    END IF
  END IF
  FOR i = 1 TO Ndx
    IF Stk$[i]= "[" AND Stk$[i+1]= "]" THEN
      IF iMatchWrd(Stk$[i+2],"as") THEN
        Stk$[i+3] = Stk$[i+3] + "*"
      ELSEIF Stk$[i+2] = "[" THEN
        j = i-1
        WHILE i <= Ndx
          IF iMatchWrd(Stk$[i],"as") THEN EXIT FOR
          IF iMatchRgt(Stk$[j],"]") AND INCHR(",)=", Stk$[i]) THEN EXIT FOR
          Stk$[j] = Stk$[j] + Stk$[i]
          Stk$[i++] = ""
        WEND
        ITERATE
      ELSE
        IF DataType(Stk$[i-1]) = vt_STRVAR THEN
          Stk$[i-1] = Stk$[i-1] + "[][65535]"
        END IF
        Stk$[i-1] = "*"  +  Stk$[i-1]
      END IF
      Stk$[i++] = "" : Stk$[i] = ""
    END IF
  NEXT
  CALL RemEmptyTokens
  IsExported = FALSE
  IF iMatchWrd(Stk$[Ndx],"export") THEN
    Ndx--
    IsExported = TRUE
    IF UseStdCall THEN
      CallType$ = "__attribute__((stdcall)) "
    ELSE
      CallType$ = "__attribute__((cdecl)) "
    END IF
  END IF
END SUB ' FuncSubDecs1

SUB RemEmptyTokens()
  DIM RAW i, j
  FOR i = 1 TO Ndx
    IF NOT *Stk[i] THEN
      j = i
      WHILE NOT *Stk[j] AND (j < Ndx)
        INCR j
      WEND
      IF NOT *Stk[j] THEN EXIT FOR
      Stk$[i] = Stk$[j]
      Stk$[j] = ""
    END IF
  NEXT i
  Ndx = i-1
END SUB
SUB FuncSubDecs2(s$, method)
  IF iMatchWrd(Stk$[1], s$) THEN
    IF iMatchWrd(Stk$[Ndx-1],"as") THEN
      Abort("Attempted type assignment to " + s$)
    END IF
    VarCode.IsPtrFlag = 0
    CurrentFuncType = vt_VOID
  ELSE
    IF iMatchWrd(Stk$[Ndx-1],"as") THEN
      CurrentFuncType  = CheckType(Stk$[Ndx])
      VarCode.Token$   = Stk$[2]
      VarCode.AsToken$ = Stk$[Ndx]
      VarCode.IsPtrFlag = TALLY(Stk$[Ndx],"*")
      Stk$[Ndx]   = ""
      Stk$[Ndx-1] = ""
      Ndx--
      Ndx--
    ELSE
      CurrentFuncType = DataType(Stk$[2])
      VarCode.Token$ = Stk$[2]
      'print Stk$[2]
      VarCode.IsPtrFlag = TALLY(Stk$[2],"*")
      VarCode.AsToken$ = ""
    END IF
  END IF
  VarCode.Proto$    = " ("
  VarCode.Header$   = " ("
  VarCode.Functype$ = ""
  VarCode.Method%   = method
  VarCode.VarNo%    = CurrentFuncType
  CALL GetVarCode(&VarCode)
END SUB ' FuncSubDecs2

SUB FuncSubDecs3(varcode AS VARCODE PTR)
  IF *Stk[Ndx-1] = ASC(".") THEN ' Allow Functions | Subs WITH one OR
    varcode->Header$ = varcode->Header$  +  "..." ' more "." TO produce the "..." needed
  END IF
  varcode->Header$ = RTRIM$(varcode->Header$)
  IF iMatchRgt(varcode->Header$, ",") THEN
    MID$(varcode->Header$, LEN(varcode->Header$)) = ")"
  ELSE
    CONCAT(varcode->Header$, ")")
  END IF
  REPLACE "()" WITH "(void)" IN varcode->Header$
  varcode->Header$ = varcode->Functype$ + varcode->Token$ + varcode->Header$
  IF varcode->Method% = 2 THEN
    IF *Stk[Ndx-1] = ASC(".") THEN ' Allow Functions | Subs with one OR
      varcode->Proto$  = varcode->Proto$   +  "..." ' FOR variable argument declarations
    END IF
    varcode->Proto$ = RTRIM$(varcode->Proto$)
    IF iMatchRgt(varcode->Proto$, ",")  THEN
      MID$(varcode->Proto$, LEN(varcode->Proto$)) = ")"
    ELSE
      CONCAT(varcode->Proto$, ")")
    END IF
    REPLACE "()" WITH "(void)" IN varcode->Proto$
    varcode->Proto$ = varcode->Functype$ + varcode->Token$ + varcode->Proto$ + ";"
  END IF
  IF IsExported THEN
    varcode->Proto$  = "C_EXPORT " + varcode->Proto$
    varcode->Header$ = "C_EXPORT " + varcode->Header$
  END IF
END SUB ' FuncSubDecs3

SUB AddTypeDefs(TypeName$, TDef)
  TypeDefsCnt++
  IF TypeDefsCnt = MaxTypes THEN Abort("Exceeded TYPE Limits.")
  TypeDefs[TypeDefsCnt].VarName$ = TypeName$
  TypeDefs[TypeDefsCnt].TypeofDef = TDef
  TypeDefs[TypeDefsCnt].EleCnt = 0
END SUB ' AddTypeDefs

FUNCTION DefsID(ZZ$)
  DIM RAW i
  IF TypeDefsCnt > 0 THEN
    FOR i = 1 TO TypeDefsCnt
      IF ZZ$ = TypeDefs[i].VarName$ THEN
        FUNCTION = i
      END IF
    NEXT
  END IF
  FUNCTION = 0
END FUNCTION ' DefsID

SUB GetTypeInfo(stk$, BYREF IsPointer, BYREF UdtIdx, BYREF vtCode)
  DIM RAW Var1$
  IsPointer = TALLY(stk$,"*")
  Var1$     = REMOVE$(stk$,"*")
  ' if it's a CLASS then get the structure information added 2008/10/07
  IF RIGHT$(Var1$,6) = "_CLASS" THEN Var1$ = LEFT$(Var1$,LEN(Var1$)-6)
  vtCode    = CheckType(Var1$)
  IF vtCode = vt_UNKNOWN THEN
    CALL AddTypeDefs(Var1$, vt_UDT) 'windows def
    vtCode = vt_UDT
  END IF
  UdtIdx = 0
  IF vtCode = vt_STRUCT OR vtCode = vt_UNION OR vtCode = vt_UDT THEN
    UdtIdx = DefsID(Var1$)
  END IF
END SUB ' GetTypeInfo

SUB AddTypedefElement(WorkingTypeDefsCnt, ElType, EName$, EType$, EPtr)
  DIM RAW TD AS UserTypeDefs PTR
  TD = &(TypeDefs[WorkingTypeDefsCnt])
  IF TD->EleCnt = MaxElements THEN Abort("Exceeded TYPE Element Limits.")
  TD->Elements[TD->EleCnt].ElementType    = ElType
  TD->Elements[TD->EleCnt].ElementDynaPtr = EPtr
  IF ElType = vt_STRUCT OR ElType = vt_UNION OR ElType = vt_UDT THEN
    TD->Elements[TD->EleCnt].ElementID = DefsID(EType$)
  ELSE
    TD->Elements[TD->EleCnt].ElementID = 0
  END IF
  TD->Elements[TD->EleCnt].ElementName$ = EName$
  TD->EleCnt = 1 + TD->EleCnt
END SUB ' AddTypedefElement

FUNCTION GetElement$(StartStk, BYREF vt, BYREF dms, id)
  DIM RAW BC = 0, i, ZZ$
  FOR i = StartStk+1 TO Ndx
    IF Stk$[i] = "[" THEN
      INCR BC
    ELSEIF Stk$[i] = "]" THEN
      DECR BC
    ELSEIF BC = 0 THEN
      IF iMatchLft(Stk$[i], "->") OR *Stk$[i] = ASC(".") THEN
        ZZ$ = Clean$(Stk$[i])
        RemoveAll(ZZ$, ".->(*)", 1)
        vt = GetElementInfo(&id, &dms, ZZ$)
        IF vt <> vt_STRUCT AND vt <> vt_UNION THEN EXIT FOR
      END IF
    END IF
  NEXT
  IF vt = vt_UDT OR vt = vt_UNION OR vt = vt_STRUCT THEN
    ZZ$ = TypeDefs[id].VarName$
  ELSE
    ZZ$ = GetVarTypeName(vt)
  END IF
  FUNCTION = ZZ$
END FUNCTION

FUNCTION GetElementInfo(BYREF DefID, BYREF EPtr, Elename$)
  DIM RAW i, id
  id = DefID
  FOR i = 0 TO TypeDefs[id].EleCnt - 1
    IF Elename$ = TypeDefs[id].Elements[i].ElementName$ THEN
      DefID = TypeDefs[id].Elements[i].ElementID
      EPtr  = TypeDefs[id].Elements[i].ElementDynaPtr
      FUNCTION = TypeDefs[id].Elements[i].ElementType
    END IF
  NEXT
  FUNCTION = 0
END FUNCTION

SUB HandleNonsense
  DIM RAW i
  FOR i = 1 TO Ndx ' tolerate nonsense like DIM A% as double
    IF iMatchWrd(Stk$[i],"as") THEN Stk$[i - 1] = Clean$(Stk$[i - 1])
    IF OptionBase THEN ' This was the easiest way I could see to do this!
      IF Stk$[i] = "[" THEN Stk$[i+1] = LTRIM$(STR$(OptionBase)) + "+" + Stk$[i+1]
    END IF
  NEXT
END SUB ' HandleNonsense
SUB ValidVar(v$)
  DIM RAW ZZ$
  IF NOT isalpha(*v$) AND *v$ <> ASC("_") THEN
    IF NOT iMatchLft(v$, "(*") THEN ' Allow byref format (*A).xxx
      Abort("Invalid String Variable Name")
    END IF
  END IF
  IF RestrictedWords(v$) AND TestState THEN
    ZZ$ = "Variable " + v$ + " on line"
    ZZ$ = ZZ$ + STR$(ModuleLineNos[ModuleNdx]) + " in Module: " + TRIM$(Modules$[ModuleNdx]) + " is a Restricted Word"
    CALL Warning(ZZ$)
  END IF
END SUB ' ValidVar

SUB PointerFix
  Stk$[Ndx-1] = Stk$[Ndx-1] + Stk$[Ndx]
  Stk[Ndx][0] = 0
  Ndx--
  WHILE TALLY(Stk$[Ndx],"*") = LEN(Stk$[Ndx])
    Stk$[Ndx-1] = Stk$[Ndx-1] + Stk$[Ndx]
    Stk[Ndx][0] = 0
    Ndx--
  WEND
END SUB ' PointerFix

SUB DimDynaString(SVar$, DG, s)
  DIM RAW A
  DIM RAW DS$
  DS$ = "if(" + SVar$ + ")free(" + SVar$ + ");"
  IF InFunc AND (IsLocal OR IsDim OR IsRaw OR IsAuto OR IsRegister) AND DG = 0 THEN
    LocalDynaCnt++
    DynaStr$[LocalDynaCnt] = DS$
    IF IsAuto THEN
      FPRINT Outfile,Scoot$ ;"char *";SVar$;";"
    ELSEIF IsRegister THEN
      FPRINT Outfile,Scoot$ ;"register char *";SVar$;";"
    ELSE
      FPRINT Outfile,Scoot$ ;"char *";SVar$;";"
    END IF
    CALL AddLocal(SVar$, vt_CHAR, 0,"",1,0,0)
  ELSE
    IF Use_GenFree THEN
      GlobalDynaCnt++
      GlobalDynaStr$[GlobalDynaCnt] = DS$
    END IF
    IF DG = 2 THEN
      CALL AddGlobal(SVar$, vt_CHAR, 0,"",1,0,1,0)
    ELSE
      IF s THEN
        CALL AddGlobal(SVar$, vt_CHAR, 0,"",1,0,2,0)
      ELSE
        CALL AddGlobal(SVar$, vt_CHAR, 0,"",1,0,0,0)
      END IF
    END IF
  END IF
  IF DG <> 2 THEN
    FPRINT Outfile,Scoot$ ; SVar$ ; "=(char*)calloc(256+";
    FOR A = 4 TO Ndx
      FPRINT Outfile,Clean$(Stk$[A]);
    NEXT
    FPRINT Outfile,",1);"
  END IF
END SUB ' DimDynaString

FUNCTION SubFuncTest
  IF iMatchWrd(Stk$[2],"function") OR iMatchWrd(Stk$[2],"sub") THEN
    FUNCTION = 1
  END IF
  FUNCTION = 0
END FUNCTION ' SubFuncTest

FUNCTION DimSubFunc(IsDynamic)
  '******************************
  DIM RAW i
  DIM RAW lszTmp$
  DIM RAW StartPoint = 3
  DIM RAW Funptr     = 0
  '******************************
  lszTmp$ =   ""
  IF iMatchWrd(Stk$[Ndx],"stdcall") THEN
    CallType$ = "__attribute__((stdcall)) "
    Ndx--
    IsStdFunc = TRUE
  ELSE
    CallType$ = "__attribute__((cdecl)) " ' Default calling convention
    IsStdFunc = FALSE
  END IF
  GLOBAL SFPOINTER
  DIM FP AS functionParse
  '------------------------------------------------------
  '  Find start of function body ( ... )
  '------------------------------------------------------
  CALL SepFuncArgs(3, &FP, TRUE)
  StartPoint = MAX(FP.CommaPos[0], 3)
  IF NOT InTypeDef THEN
    SFPOINTER = TRUE
    '------------------------------------------------------
    '  Get intialized data  " = xxx" or "= {xxx,xxx}"
    '------------------------------------------------------
    IF FP.NumArgs = 0 THEN
      i = MIN(FP.CommaPos[1]+1, Ndx)
    ELSE
      i = MIN(FP.CommaPos[FP.NumArgs]+1, Ndx)
    END IF
    IF Stk$[i] = "=" THEN
      Stk$[i++] = ""
      WHILE NOT iMatchWrd(Stk$[i], "as") AND i <= Ndx
        lszTmp$ = lszTmp$ +Stk$[i]
        Stk$[i++] = ""
      WEND
      RemoveAll(lszTmp$, "{}", 1)
      IF lszTmp$ <> "" THEN CALL RemEmptyTokens
    END IF
    '------------------------------------------------------
    IF NOT InNameSpace THEN FPRINT FP4, MakeDecProto$(&FP), ";"
    SFPOINTER = FALSE
    Ndx = StartPoint
    Stk$[2] = ""
    IF lszTmp$ <> "" THEN
      Stk$[Ndx++] = "="
      Stk$[Ndx++] = "{"
      Stk$[Ndx++] = Clean$(lszTmp$)
      Stk$[Ndx++] = "}"
    END IF
    Stk$[Ndx++] = "as"
    Stk$[Ndx] = Clean$(Stk$[3]) + "_TYPE" + STRING$(Funptr, ASC("*"))
    CALL RemEmptyTokens
    FUNCTION = FALSE
  ELSE
    '/***** 2010-11-15 Added Constructor/Destructor - AIR *****/
    IF iMatchWrd(Stk$[2], "constructor") OR iMatchWrd(Stk$[2], "destructor") THEN
      FPRINT Outfile, LF$, Scoot$, MakeDecProto$(&FP),";"
      '/***** 2010-12-01 Added to support Abtract Classes - AIR *****/
    ELSEIF Use_Virtual THEN
      FPRINT Outfile, Scoot$, "virtual ", MakeDecProto$(&FP), vproc$, ";"
      Use_Virtual = FALSE
    ELSE
      FPRINT Outfile, Scoot$, MakeDecProto$(&FP), ";"
    END IF
  END IF
  FUNCTION = TRUE
END FUNCTION ' DimSubFunc

SUB Emit
  '******************************
  DIM RAW HasStorage = 0
  DIM RAW A,B,i,j,Tmp
  DIM RAW FuncRetnFlag
  DIM RAW IsPointer = 0
  DIM RAW VType
  DIM RAW id = 0
  DIM RAW k  = 0
  DIM RAW vt = 0
  DIM RAW Arg$
  DIM RAW CVar$
  DIM RAW Keyword$
  DIM RAW lszTmp$
  DIM RAW Var1$
  DIM RAW ZZ$
  DIM RAW IsSubOrFuncPtr
  DIM RAW dms
  STATIC NoBreak
  STATIC NoBreak2
  '******************************
  FuncRetnFlag  =   0
  lszTmp$       =  ""
  ZZ$           =  ""
  '******************************
  '*************************************
  ' Resets the break suppression flag if
  ' any keyword follows other than these
  '*************************************
  Keyword$ = LCASE$(Stk$[1])
  IF NoBreak2 AND NOT iMatchLft(Keyword$,"case") AND NOT iMatchWrd(Keyword$,"endselect") THEN
    NoBreak2 = 0
  END IF
  '*********************
  EmitAgain:
  '*********************
  IF Ndx = 0 THEN EXIT SUB
  Statements++
  IF iMatchRgt(Stk$[1], ":") THEN 'This Must Be A Label
    FPRINT Outfile,""
    FPRINT Outfile,UCASE$(Stk$[1]),";"
    EXIT SUB
  END IF
  '--------- BEGIN INSERT ----------------
  FOR i = 1 TO Ndx
    REPLACE CHR$(-15) WITH ":" IN Stk$[i]
  NEXT
  '--------- END INSERT ----------------
  IF (CurrentFuncType = vt_STRVAR) AND InFunc AND OkayToSend THEN
    FPRINT Outfile,Scoot$,"char *BCX_RetStr={0};"
    OkayToSend = 0
  END IF
  '**************************
  '  SingleLineIfReEntry:
  '**************************
  Lookup$ = LCASE$(Stk$[1])
  SELECT CASE Lookup$
    '********************************************************************
    CASE "fprint", "sprint"
    '********************************************************************
    DIM RAW IsLprint = FALSE
    DIM RAW IsSprint = FALSE
    IF iMatchWrd(Stk$[1],"sprint") THEN
      IsSprint = TRUE
    END IF
    IF IsNumber(Stk$[2]) THEN
      Stk$[2] = "FP" + Stk$[2]
    END IF
    IF IsSprint THEN
      Handl$ = Clean$(Stk$[2])
    ELSE
      IF LCASE$(Stk$[2]) = "stderr" THEN
        Handl$ = LCASE$(Stk$[2])
      ELSE
        IF CheckLocal(Stk$[2], &i) = vt_UNKNOWN THEN
          IF CheckGlobal(Stk$[2], &i) = vt_UNKNOWN THEN
            CALL AddGlobal(Stk$[2], vt_FILEPTR, 0,"",0,0,0,0)
          END IF
        END IF
        Handl$ = ""
        FOR i = 2 TO Ndx
          IF *Stk$[i] = ASC(",") OR *Stk$[i] = ASC(";") THEN
            Stk$[i] = ""
            EXIT FOR
          END IF
          Handl$ = Handl$ + Stk$[i]
          Stk$[i] = ""
        NEXT i
        Handl$ = Handl$ + "@"
      END IF
    END IF
    Stk$[2] = "" 'get rid of handle
    Stk$[3] = "" 'get rid of the Comma
    IF IsSprint THEN
      ZZ$ = "s" + PrintWriteFormat$(0)
      REMOVE "\\n" FROM ZZ$
    ELSE
      ZZ$ = "f" + PrintWriteFormat$(0)
    END IF
    ZZ$ = LEFT$(ZZ$,8) + REMOVE$(Handl$,"@") + "," + MID$(ZZ$,9)
    FPRINT Outfile,Scoot$, ZZ$
    '***********************
    CASE "end"
    '***********************
    IF Ndx = 1 THEN
      FPRINT Outfile,Scoot$,"fflush(stdout);"
      FPRINT Outfile,Scoot$,"exit(0);"
      EXIT SELECT
    END IF
    IF Stk$[2] = "=" THEN
      FPRINT Outfile,Scoot$,"fflush(stdout);"
      FPRINT Outfile,Scoot$,"exit(";
      FOR Tmp = 3 TO Ndx
        FPRINT Outfile,Clean$(Stk$[Tmp]);
      NEXT
      FPRINT Outfile,");"
      EXIT SELECT
    END IF
    IF iMatchWrd(Stk$[2],"if") THEN
      CALL BumpDown
      FPRINT Outfile,Scoot$,"}"
      CALL BumpDown
      EXIT SELECT
    END IF
    '***********************
    CASE "endif"
    '***********************
    CALL BumpDown
    FPRINT Outfile,Scoot$,"}"
    CALL BumpDown
    '***********************
    CASE "if"
    '***********************
    CALL EmitIfCond("if")
    '***********************
    CASE "elseif"
    '***********************
    CALL BumpDown
    FPRINT Outfile,Scoot$,"}"
    CALL BumpDown
    CALL EmitIfCond("else if")
    '******************************************************
    CASE "for"
    '******************************************************
    DIM RAW FFlg = 0
    DIM RAW For1 = 0
    DIM RAW For2 = 0
    DIM RAW For3 = 0
    DIM RAW For4 = 0
    DIM RAW Reg$, xxx$, yyy$, zzz$, qqq$
    Reg$ = ""
    xxx$ = ""
    yyy$ = ""
    zzz$ = ""
    qqq$ = ""
    '******************************************************
    FOR i = Ndx TO 1 STEP -1
      IF iMatchWrd(Stk$[i],"step") THEN
        FFlg = TRUE
        EXIT FOR
      END IF
    NEXT
    IF NOT FFlg THEN
      Ndx++
      Stk$[Ndx] = "step"
      Ndx++
      Stk$[Ndx] = "1"
    END IF
    '******************************************************
    Test = FALSE
    FOR i = 1 TO Ndx
      IF Stk$[i]= "=" THEN Test = TRUE
    NEXT
    IF Test = FALSE THEN Abort("Missing =")
    '******************************************************
    Test = FALSE
    FOR i = 1 TO Ndx
      IF iMatchWrd(Stk$[i],"to") THEN Test = TRUE
    NEXT
    IF Test = FALSE THEN Abort("Missing TO")
    '******************************************************
    Reg$ = LCASE$(Stk$[2])
    SELECT CASE Reg$
      CASE "int","fint"
      Reg$ = SPC$
      LoopLocalVar[LoopLocalCnt++] = 1
      FPRINT Outfile,Scoot$,"  {register int ";
      CASE "single", "float"
      Reg$ = SPC$
      LoopLocalVar[LoopLocalCnt++] = 1
      FPRINT Outfile,Scoot$,"  {float ";
      CASE "double"
      Reg$ = SPC$
      LoopLocalVar[LoopLocalCnt++] = 1
      FPRINT Outfile,Scoot$,"  {double ";
      CASE "ldouble"
      Reg$ = SPC$
      LoopLocalVar[LoopLocalCnt++] = 1
      FPRINT Outfile,Scoot$,"  {LDOUBLE ";
      CASE ELSE
      Reg$ = ""
      LoopLocalVar[LoopLocalCnt++] = 0
    END SELECT
    IF LEN(Reg$) THEN
      FOR j = 3 TO Ndx
        Stk$[j-1] = Stk$[j]
      NEXT
      Ndx--
    END IF
    '******************************************************
    ' Every statement now conforms to the following:
    ' FOR xxx = yyy TO zzz STEP qqq
    '******************************************************
    FOR i = 2 TO Ndx
      IF Stk$[i] = "=" THEN
        For1 = i-1 'xxx spans from Stk$[2] to Stk$[For1]
        EXIT FOR
      END IF
    NEXT
    FOR i = For1+2 TO Ndx
      IF iMatchWrd(Stk$[i],"to") THEN
        For2 = i-1 'yyy spans from Stk$[For1+2] to Stk$[For2]
        EXIT FOR
      END IF
    NEXT
    FOR i = For2+2 TO Ndx
      IF iMatchWrd(Stk$[i],"step") THEN
        For3 = i-1 'zzz spans from Stk$[For2+2] to Stk$[For3]
        EXIT FOR
      END IF
    NEXT
    For4 = For3+2 'qqq spans from Stk$[For4] to Stk$[Ndx]
    FOR i = 2 TO For1
      CONCAT(xxx$,Stk$[i])
    NEXT
    FOR i = For1+2 TO For2
      CONCAT(yyy$,Stk$[i])
    NEXT
    FOR i = For2+2 TO For3
      CONCAT(zzz$,Stk$[i])
    NEXT
    FOR i = For4 TO Ndx
      CONCAT(qqq$,Stk$[i])
    NEXT
    xxx$ = Clean$(xxx$)
    yyy$ = Clean$(yyy$)
    zzz$ = Clean$(zzz$)
    qqq$ = Clean$(qqq$)
    IF Reg$ = SPC$ THEN FPRINT Outfile, xxx$, ";"
    Reg$ = ""
    IF IsNumberEx (qqq$) THEN
      IF LEFT$(qqq$,1) = "-" THEN
        FPRINT Outfile,Scoot$,"for(", Reg$, xxx$, "=", yyy$, "; ", xxx$, ">=" , zzz$, "; " , xxx$, "+=" , qqq$, ")"
      ELSE
        FPRINT Outfile,Scoot$,"for(", Reg$, xxx$, "=", yyy$, "; ", xxx$, "<=" , zzz$, "; " , xxx$, "+=" , qqq$, ")"
      END IF
    ELSE
      FPRINT Outfile,Scoot$,"for(", Reg$, xxx$, "=", yyy$, "; ", qqq$, ">=0 ? ", xxx$, "<=" , zzz$, " : ", xxx$, ">=", zzz$, "; " , xxx$, "+=" , qqq$, ")"
    END IF
    CALL BumpUp
    FPRINT Outfile,Scoot$,"{"
    CALL BumpUp
    '***********************
    CASE "next"
    '***********************
    CALL BumpDown
    FPRINT Outfile,Scoot$,"}"
    IF LoopLocalVar[--LoopLocalCnt] THEN FPRINT Outfile,Scoot$,"}"
    IF LoopLocalCnt < 0 THEN Abort ("Next without For")
    CALL BumpDown
    '***********************
    CASE "do"
    '***********************
    FPRINT Outfile,Scoot$,"for(;;)"
    CALL BumpUp
    FPRINT Outfile,Scoot$,"{"
    CALL BumpUp
    '***********************
    CASE "loop"
    '***********************
    CALL BumpDown
    FPRINT Outfile,Scoot$,"}"
    CALL BumpDown
    '***********************
    CASE "caseelse"
    '***********************
    CaseElseFlag[Pusher] = TRUE
    IF CaseFlag THEN
      IF NoBreak2 = 0 THEN
        FPRINT Outfile,Scoot$,"break;"
      END IF
      CALL BumpDown
      FPRINT Outfile,Scoot$,"}"
      FPRINT Outfile,Scoot$,"// case else"
      FPRINT Outfile,Scoot$,"{"
      CALL BumpUp
    END IF
    '***********************
    CASE "endselect"
    '***********************
    IF CaseFlag THEN
      CALL BumpDown
      FPRINT Outfile,Scoot$,"}"
    END IF
    CALL BumpDown
    ' Only suppress this break if the Case block contains
    ' a "CASE ELSE" and the last statement is a redirection.
    IF CaseElseFlag[Pusher] = 0 OR NoBreak2 = 0 THEN
      FPRINT Outfile,Scoot$,"break;"
    END IF
    CALL BumpDown
    FPRINT Outfile,Scoot$,"}"
    NoBreak2 = CaseElseFlag[Pusher] = 0
    CALL Pop(CaseVar$)
    '***********************
    CASE "else"
    '***********************
    CALL BumpDown
    FPRINT Outfile,Scoot$,"}"
    CALL BumpDown
    FPRINT Outfile,Scoot$,"else"
    CALL BumpUp
    FPRINT Outfile,Scoot$,"{"
    CALL BumpUp
    ' **************
    CASE "case"
    ' **************
    FOR i = 2 TO Ndx
      IF Stk$[i] = "%" THEN Stk$[i] = " % " ' Added by MrBCX 3.36
      IF Stk$[i] = "!=" THEN Stk$[i] = "<>"
      IF Stk$[i] = "!" AND Stk$[i+1] = "=" THEN
        Stk$[i] = "<>" : Stk$[i+1] = ""
      END IF
      IF isalpha(Stk[i][0]) THEN
        CONCAT(Stk$[i]," ")
      END IF
    NEXT
    szTmp$ = ""
    Test = FALSE
    IF DataType(CaseVar$) = vt_STRVAR THEN Test = TRUE
    i = 0
    FOR A = 2 TO Ndx
      IF INCHR("([",Stk$[A]) THEN i++
      IF INCHR(")]",Stk$[A]) THEN i--
      IF i THEN
        CONCAT(szTmp$, Stk$[A])
        ITERATE
      END IF
      IF Stk$[A] = "," THEN ' comma
        IF NOT INCHR("<>=",Stk$[A+1]) THEN
          szTmp$ = szTmp$ + " or " + CaseVar$ + "="
        ELSE
          szTmp$ = szTmp$ + " or " + CaseVar$
        END IF
        Stk$[A] = ""
        ITERATE
      END IF
      IF Stk$[A] = "&&" THEN
        szTmp$ = szTmp$ + " and " + CaseVar$
        Stk$[A]= ""
      ELSEIF Stk$[A] = "||" THEN
        szTmp$ = szTmp$ + " or "  + CaseVar$
        Stk$[A]= ""
      ELSE
        CONCAT(szTmp$, Stk$[A])
      END IF
    NEXT
    IF CaseFlag = 0 THEN NoBreak = 0
    IF CaseFlag THEN
      IF NoBreak = 0 THEN
        IF NoBreak2 = 0 THEN FPRINT Outfile,Scoot$;"break;"
      END IF
      CALL BumpDown()
      FPRINT Outfile,Scoot$;"}"
      CALL BumpDown()
    END IF
    CaseFlag = TRUE
    IF iMatchLft(CaseVar$," BAND ") THEN
      NoBreak = 1
      Src$ = "IF " + szTmp$ + CaseVar$ + " Then "
    ELSE
      IF INCHR("<>=",szTmp$) AND NOT IsQuoted(szTmp$) THEN
        Src$ = "IF " + CaseVar$ + szTmp$ + " Then "
      ELSE
        Src$ = "IF " + CaseVar$ + " = " + szTmp$ + " Then "
      END IF
    END IF
    CALL Parse(Src$)
    CALL Emit()
    '***********************
    CASE "delay"
    '***********************
    lszTmp$ = ""
    FOR i = 2 TO Ndx ' Allow size to be an expression
      CONCAT(lszTmp$, Clean$(Stk$[i]))
    NEXT
    FPRINT Outfile,Scoot$,"sleep(";lszTmp$;");"
    '***********************
    CASE "qsortidx"
    '***********************
    lszTmp$ = ""
    Var$ = Clean$(Stk$[2]) 'index array
    FOR i = 4 TO Ndx-4 'allow size to be an expression
      CONCAT(lszTmp$, Stk$[i])
    NEXT
    lszTmp$ = Clean$(lszTmp$)
    FPRINT Outfile,Scoot$,"Key = ",Stk[Ndx],";"
    IF Var$ <> "0" THEN
      FPRINT Outfile,Scoot$,"int iDx;"
      FPRINT Outfile,Scoot$,"for(iDx=0; iDx<",lszTmp$,"; iDx+=1) ";
      FPRINT Outfile, Var$,"[iDx]=iDx;"
    END IF
    IF NOT INCHR(Stk$[Ndx-2],".") THEN 'Check if this is a struct sort
      Use_Idxqsort = TRUE
      FPRINT Outfile,Scoot$,"pppStr = ",Clean$(Stk[Ndx-2]),";"
      FPRINT Outfile,Scoot$,"qsort(";Var$;",";lszTmp$;",sizeof(int),IdxCompare);"
    ELSE
      DIM RAW Stptr$, StMem$, StName$
      StMem$ = REMAIN$(Clean$(Stk$[Ndx-2]),".")
      Stptr$ = EXTRACT$(Stk$[Ndx-2],".")
      IF CheckLocal(Stptr,&i) <> vt_UNKNOWN THEN
        StName$ = TypeDefs[LocalVars[i].VarDef].VarName$
      ELSEIF CheckGlobal(Stptr,&i) <> vt_UNKNOWN THEN
        StName$ = TypeDefs[GlobalVars[i].VarDef].VarName$
      END IF
      IF Var$ <> "0" THEN
        Use_IdxqsortSt = TRUE
        FPRINT Outfile,Scoot$,"cmp1 =(char*)(",Stptr$ ,") + offsetof(",StName$,",",StMem$,");"
        FPRINT Outfile,Scoot$,"StructSize = sizeof(",StName$,");"
        FPRINT Outfile,Scoot$,"qsort(",Var$;",",lszTmp$,",sizeof(int),IdxCompareSt);"
      ELSE
        Use_PtrqsortSt = TRUE
        FPRINT Outfile,Scoot$,"OffSet = offsetof(",StName$,",",StMem$,");"
        FPRINT Outfile,Scoot$,"qsort(",Stptr$;",",lszTmp$,",sizeof(",StName$,"),PtrCompareSt);"
      END IF
    END IF
    '***********************
    CASE "qsort"
    '***********************
    DIM RAW QST=0
    DIM RAW order=0
    IF iMatchWrd(Stk$[2],"dynamic") THEN
      QST = TRUE
      FOR j = 3 TO Ndx
        Stk$ [j-1] = Stk$[j]
      NEXT
      Ndx--
    END IF
    IF LCASE$(Stk$[Ndx])= "ascending"  THEN
      order = 2
      Ndx--
      Ndx--
    END IF
    IF LCASE$(Stk$[Ndx])= "descending" THEN
      order = 1
      Ndx--
      Ndx--
    END IF
    IF order = 0 THEN order = 2 'default to ascending
    lszTmp$ = ""
    FOR i = 4 TO Ndx 'allow size to be an expression
      CONCAT(lszTmp$, Stk$[i])
    NEXT
    Var$ = Clean$(Stk$[2])
    vt = DataType(Stk$[2])
    IF vt <> vt_STRVAR AND vt <> vt_INTEGER AND vt <> vt_SINGLE AND vt <> vt_DOUBLE THEN
      vt = CheckType(Stk$[2])
    END IF
    FPRINT Outfile,Scoot$,"qsort(";Var$;",";Clean$(lszTmp$);
    SELECT CASE vt
      CASE vt_STRVAR
      IF NOT QST THEN
        IF order = 1 THEN
          FPRINT Outfile,",sizeof(";Var$;"[0]),StrCompareD);"
          Use_Strqsortd = TRUE
        ELSE
          FPRINT Outfile,",sizeof(";Var$;"[0]),StrCompareA);"
          Use_Strqsorta = TRUE
        END IF
      ELSE
        IF order = 1 THEN
          FPRINT Outfile,",sizeof(";Var$;"[0]),DynStrCompareD);"
          Use_DynStrqsortd = TRUE
        ELSE
          FPRINT Outfile,",sizeof(";Var$;"[0]),DynStrCompareA);"
          Use_DynStrqsorta = TRUE
        END IF
      END IF
      CASE vt_INTEGER
      IF order = 1 THEN
        FPRINT Outfile,",sizeof(int),NumCompareDint);"
        Use_Numqsortdint = TRUE
      ELSE
        FPRINT Outfile,",sizeof(int),NumCompareAint);"
        Use_Numqsortaint = TRUE
      END IF
      CASE vt_SINGLE
      IF order = 1 THEN
        FPRINT Outfile,",sizeof(float),NumCompareDfloat);"
        Use_Numqsortdfloat = TRUE
      ELSE
        FPRINT Outfile,",sizeof(float),NumCompareAfloat);"
        Use_Numqsortafloat = TRUE
      END IF
      CASE vt_DOUBLE
      IF order = 1 THEN
        FPRINT Outfile,",sizeof(double),NumCompareDdouble);"
        Use_Numqsortddouble = TRUE
      ELSE
        FPRINT Outfile,",sizeof(double),NumCompareAdouble);"
        Use_Numqsortadouble = TRUE
      END IF
      CASE ELSE
      IF order = 1 THEN
        FPRINT Outfile,",sizeof(int),NumCompareDint);"
        Use_Numqsortdint = TRUE
      ELSE
        FPRINT Outfile,",sizeof(int),NumCompareAint);"
        Use_Numqsortaint = TRUE
      END IF
    END SELECT
    '***********************
    CASE "endprogram"
    '***********************
    FPRINT Outfile,"  return 0;         //  End of main program"
    FPRINT Outfile,"}\n\n"
    EndOfProgram = 1
    '******************************
    ' Allow Conditional Compilation
    '******************************
    '***********************
    CASE "~ifndef"
    '***********************
    InIfDef$ = "#ifndef "
    FOR i = 2 TO Ndx
      InIfDef$ = InIfDef$ + Stk$[i] + " "
    NEXT
    InIfDef$ = TRIM$(InIfDef$)
    IF InFunc OR InMain THEN
      FPRINT Outfile,InIfDef$
    ELSE
      FPRINT FP6,InIfDef$
    END IF
    '***********************
    CASE "~if"
    '***********************
    InIfDef$ = "#if defined "
    FOR i = 2 TO Ndx
      InIfDef$ = InIfDef$ + Stk$[i] + " "
    NEXT
    InIfDef$ = TRIM$(InIfDef$)
    ConstLastDef$ = InIfDef$
    IF InFunc THEN
      IF Outfile = FP3 THEN FPRINT Outfile,"// FP3"
      IF Outfile = FP2 THEN FPRINT Outfile,"// FP2"
      FPRINT Outfile,InIfDef$,"// OUTFILE"
      InIfDef$ = "FP3"
    ELSEIF InMain THEN
      FPRINT Outfile, InIfDef$, "// --FP2--"
    END IF
    '***********************
    CASE "~else"
    '***********************
    InIfDef$ = "#else"
    ConstLastDef$ = InIfDef$
    IF InFunc OR InMain THEN
      FPRINT Outfile,InIfDef$
    ELSE
      FPRINT FP6,InIfDef$
    END IF
    '***********************
    CASE "~elseif"
    '***********************
    InIfDef$ = "#elif defined "
    FOR i = 2 TO Ndx
      InIfDef$ = InIfDef$ + Stk$[i] + " "
    NEXT
    InIfDef$ = TRIM$(InIfDef$)
    ConstLastDef$ = InIfDef$
    IF InFunc OR InMain THEN
      FPRINT Outfile, InIfDef$
    ELSE
      FPRINT FP6, InIfDef$
    END IF
    '***********************
    CASE "~endif"
    '***********************
    IF InIfDef$ = "FP3" THEN
      FPRINT FP3, "#endif  // FP3"
    ELSE 'elseif InMain THEN
      FPRINT Outfile, "#endif  // Main"
    END IF
    IF ConstLastDef$ = "FP6" THEN
      FPRINT FP6, "#endif  // FP6"
    END IF
    InIfDef$ = "#endif  // other"
    IF InConditional = 0 THEN
      InIfDef$ = ""
      ConstLastDef$ = ""
      'DidConsts = 0
    END IF
    '***********************
    CASE "incr"
    '***********************
    j=FALSE
    FPRINT Outfile,Scoot$;
    FOR i=2 TO Ndx
      IF Stk$[i]="," THEN
        FPRINT Outfile,"+=(";
        j=TRUE
      ELSE
        FPRINT Outfile,Clean$(Stk$[i]);
      END IF
    NEXT
    FPRINT Outfile,IIF$(j,");","++;")
    '***********************
    CASE "decr"
    '***********************
    j=FALSE
    FPRINT Outfile,Scoot$;
    FOR i=2 TO Ndx
      IF Stk$[i]="," THEN
        FPRINT Outfile,"-=(";
        j=TRUE
      ELSE
        FPRINT Outfile,Clean$(Stk$[i]);
      END IF
    NEXT
    FPRINT Outfile,IIF$(j,");","--;")
    '***********************
    CASE "seek"
    '***********************
    IF DataType(Stk$[2])= vt_NUMBER THEN
      Stk$[2]= "FP" + Stk$[2]
    END IF
    IF CheckLocal(Stk$[2], &i) = vt_UNKNOWN THEN
      CALL AddGlobal(Stk$[2], vt_FILEPTR, 0,"",0,0,0,0)
    END IF
    FPRINT Outfile,Scoot$,"fseek(";
    FOR Tmp = 2 TO Ndx
      FPRINT Outfile,Clean$(Stk$[Tmp]);
    NEXT
    FPRINT Outfile,",0);"
    '***********************
    CASE "select"
    '***********************
    CaseVar$ = ""
    CaseFlag = 0
    FOR A = 3 TO Ndx
      CONCAT(CaseVar$, Stk$[A])
    NEXT
    CALL Push(CaseVar$)
    FPRINT Outfile,Scoot$,"for(;;)"
    FPRINT Outfile,Scoot$,"{"
    CALL BumpUp
    '***********************
    CASE "~get"
    '***********************
    Use_Get = TRUE
    IF DataType(Stk$[2])= vt_NUMBER THEN
      Stk$[2]= "FP" + Stk$[2]
    END IF
    IF CheckLocal(Stk$[2], &i) = vt_UNKNOWN THEN
      IF CheckGlobal(Stk$[2], &i) = vt_UNKNOWN THEN
        CALL AddGlobal(Stk$[2], vt_FILEPTR, 0,"",0,0,0,0)
      END IF
    END IF
    FPRINT Outfile,Scoot$,"GET(";
    FOR Tmp = 2 TO Ndx
      FPRINT Outfile,Clean$(Stk$[Tmp]);
    NEXT
    FPRINT Outfile,");"
    '***********************
    CASE "~put"
    '***********************
    Use_Put = TRUE
    IF DataType(Stk$[2]) = vt_NUMBER THEN
      Stk$[2]= "FP" + Stk$[2]
    END IF
    IF CheckLocal(Stk$[2], &i) = vt_UNKNOWN THEN
      IF CheckGlobal(Stk$[2], &i) = vt_UNKNOWN THEN
        CALL AddGlobal(Stk$[2], vt_FILEPTR, 0,"",0,0,0,0)
      END IF
    END IF
    FPRINT Outfile,Scoot$,"PUT(";
    FOR Tmp = 2 TO Ndx
      FPRINT Outfile,Clean$(Stk$[Tmp]);
    NEXT
    FPRINT Outfile,");"
    '***********************
    CASE "gosub"
    '***********************
    Use_Gosub = TRUE
    FPRINT Outfile,Scoot$,"if (setjmp(GosubStack[GosubNdx++])==0)";
    FPRINT Outfile," goto ";UCASE$(Stk$[2]);";"
    '***********************
    CASE "return"
    '***********************
    Use_Gosub = TRUE
    FPRINT Outfile,Scoot$,"longjmp (GosubStack [--GosubNdx],1 );"
    FPRINT Outfile,""
    '***********************
    CASE "data"
    '***********************
    IF Stk$[Ndx] <> "," THEN
      Stk$[Ndx+1] = ","
      Ndx++
    END IF
    FOR A = 2 TO Ndx
      IF INCHR(Stk$[A],DQ$) = 0 AND Stk$[A] <> "," THEN
        Stk$[A] = ENC$(Stk$[A]) ' Allow unquoted text
      END IF
      FPRINT FP5,Stk$[A];
    NEXT
    FPRINT FP5,""

    CASE "namespace"
    UseCpp = TRUE
    szTmp$ = MID$(Src$,INCHR(Src$," ")+1)
    FPRINT Outfile,"namespace " + LTRIM$(szTmp$)
    FPRINT Outfile,"{"
    '/** 2010/11/30 Added -AIR **/
    InNameSpace++
    CALL BumpUp

    CASE "endnamespace"
    InNameSpace--
    CALL BumpDown
    FPRINT Outfile,Scoot$,"}"

    '/****** ADDED 2010-11-14 AIR *****/
    '***********************
    CASE "class"
    '***********************
    IF InTypeDef = 0 THEN
      SaveOutfileNum = Outfile
    END IF
    Outfile = FP4
    InTypeDef++
    TypeName$[InTypeDef] = Stk$[2]

    IF Stk$[3] = "inherits" THEN Stk$[3] = ": public " + Stk$[4]
    CALL AddTypeDefs(TypeName$[InTypeDef],vt_STRUCT)
    BaseTypeDefsCnt[InTypeDef] = TypeDefsCnt
    IF InTypeDef = 1 THEN
      FPRINT Outfile,""
      FPRINT Outfile,"class ";TypeName$[InTypeDef];Stk$[3];" {"
      CALL BumpUp
    END IF

    '/****** ADDED 2010-11-14 AIR *****/
    '***********************
    CASE "endclass"
    '***********************
    CALL BumpDown
    FPRINT Outfile,"};";LF$
    InTypeDef--

    '***********************
    CASE "type"
    '***********************
    IF InTypeDef = 0 THEN
      SaveOutfileNum = Outfile
    END IF
    Outfile = FP4
    IF Ndx > 2 THEN
      IF InTypeDef THEN
        CALL Abort("Single line TYPE within type/union not supported")
      END IF
      FOR i = Ndx TO 1 STEP -1
        IF iMatchWrd(Stk$[i],"as") THEN
          EXIT FOR
        END IF
      NEXT
      IF NOT iMatchWrd(Stk$[i],"as") THEN
        CALL Abort("Missing AS TYPE")
      END IF
      FPRINT Outfile,"typedef ";
      j = i-1
      i++
      WHILE i <= Ndx
        FPRINT Outfile,Stk$[i];" ";
        i++
      WEND
      FOR i = 2 TO j
        FPRINT Outfile,Stk$[i];
      NEXT
      FPRINT Outfile,";"
      Outfile = SaveOutfileNum
    ELSE
      InTypeDef++
      TypeName$[InTypeDef] = Stk$[2]
      CALL AddTypeDefs(TypeName$[InTypeDef],vt_STRUCT)
      BaseTypeDefsCnt[InTypeDef] = TypeDefsCnt
      IF InTypeDef = 1 THEN
        FPRINT Outfile,""
        FPRINT Outfile,"typedef struct _";TypeName$[InTypeDef]
        FPRINT Outfile,"{"
        CALL BumpUp
      ELSE
        FPRINT Outfile,Scoot$;"struct"
        FPRINT Outfile,Scoot$;"{"
        CALL AddTypedefElement(BaseTypeDefsCnt[InTypeDef-1],vt_STRUCT,TypeName$[InTypeDef],TypeName$[InTypeDef], 0)
        CALL BumpUp
      END IF
    END IF
    '***********************
    CASE "endtype"
    '***********************
    IF InTypeDef = 1 THEN
      CALL BumpDown
      FPRINT Outfile,"}";TypeName$[InTypeDef];", *";"LP";UCASE$(TypeName$[InTypeDef]); ";"
      FPRINT Outfile,""
      Outfile = SaveOutfileNum
      FPRINT FP6,Scoot$;"#define ",UCASE$(TypeName$[InTypeDef]),"_CLASS struct _",UCASE$(TypeName$[InTypeDef]),"*"
    ELSE
      CALL BumpDown
      FPRINT Outfile,Scoot$;"} ";TypeName$[InTypeDef];";"
      FPRINT Outfile,""
    END IF
    InTypeDef--
    '***********************
    CASE "union"
    '***********************
    IF InTypeDef = 0 THEN
      SaveOutfileNum = Outfile
    END IF
    Outfile = FP4
    InTypeDef++
    TypeName$[InTypeDef] = Stk$[2]
    CALL AddTypeDefs(TypeName$[InTypeDef],vt_UNION)
    BaseTypeDefsCnt[InTypeDef] = TypeDefsCnt
    IF InTypeDef = 1 THEN
      FPRINT Outfile,""
      FPRINT Outfile,"typedef union "
      FPRINT Outfile,"{"
      CALL BumpUp
    ELSE
      FPRINT Outfile,Scoot$;"union"
      FPRINT Outfile,Scoot$;"{"
      CALL AddTypedefElement(BaseTypeDefsCnt[InTypeDef-1],vt_UNION,TypeName$[InTypeDef],TypeName$[InTypeDef], 0)
      CALL BumpUp
    END IF
    '***********************
    CASE "endunion"
    '***********************
    IF InTypeDef = 1 THEN
      CALL BumpDown
      FPRINT Outfile,"} ";TypeName$[InTypeDef];", *";"LP";UCASE$(TypeName$[InTypeDef]); ";"
      FPRINT Outfile,""
      Outfile = SaveOutfileNum
    ELSE
      CALL BumpDown
      FPRINT Outfile,Scoot$;"} ";TypeName$[InTypeDef];";"
      FPRINT Outfile,""
    END IF
    InTypeDef--
    '***********************
    CASE "with"
    '***********************
    GLOBAL WithVar$[8]
    GLOBAL WithCnt
    WithCnt++
    IF WithCnt = 8 THEN Abort("[With] depth exceeded")
    WithVar$[WithCnt] = ""
    FOR i = 2 TO Ndx
      CONCAT(WithVar$[WithCnt],Stk$[i])
    NEXT
    '***********************
    CASE "endwith"
    '***********************
    WithCnt--
    '***********************
    CASE "clear"
    '***********************
    Use_Clear = TRUE
    FPRINT Outfile, Scoot$, "Clear ";
    IF Stk$[2]<> "(" THEN FPRINT Outfile,"(";
    FOR i = 2 TO Ndx
      FPRINT Outfile,Clean$(Stk$[i]);
    NEXT
    IF Stk$[2]<> "(" THEN FPRINT Outfile,")";
    FPRINT Outfile,";"
    '***********************
    CASE "repeat"
    '***********************
    lszTmp$ = ""
    FOR i = 2 TO Ndx
      CONCAT(lszTmp$, Stk$[i])
    NEXT
    lszTmp$ = Clean$(lszTmp$)
    CALL BumpUp
    IF INCHR(Stk$[2],"-") THEN
      IF LEFT$(lszTmp$,1) = "-" THEN lszTmp$ = MID$(lszTmp$,2)
      FPRINT Outfile,Scoot$,"{register int BCX_REPEAT;"
      FPRINT Outfile,Scoot$,"for(BCX_REPEAT=";lszTmp$;";BCX_REPEAT>=1;BCX_REPEAT--)"
      FPRINT Outfile,Scoot$,"{"
    ELSE
      FPRINT Outfile,Scoot$,"{register int BCX_REPEAT;"
      FPRINT Outfile,Scoot$,"for(BCX_REPEAT=1;BCX_REPEAT<=";lszTmp$;";BCX_REPEAT++)"
      FPRINT Outfile,Scoot$,"{"
    END IF
    CALL BumpUp
    '***********************
    CASE "endrepeat"
    '***********************
    CALL BumpDown
    FPRINT Outfile,Scoot$,"}"
    FPRINT Outfile,Scoot$,"}"
    CALL BumpDown
    CASE "const"
    '***********************
    DIM RAW Buffer$
    DIM RAW Sep$
    Buffer$ = ""
    Sep$    = ""
    Stk$[1] = ""
    FOR i = 2 TO Ndx
      IF Stk$[i] = "=" THEN
        INCR i
        EXIT FOR
      ELSE
        CONCAT(Stk$[1], Stk$[i])
      END IF
    NEXT
    Stk$[1] = "#define " + Clean$(Stk$[1]) + SPC$
    FOR i = i TO Ndx
      IF isalpha(Stk[i][0]) OR (Stk[i][0] = ASC("_") AND _
      isalpha(Stk[i+1][0])) OR Stk[i+1][0] = ASC("_") THEN Sep$ = " " ELSE Sep$ = ""
      IF NOT IsQuoted(Stk$[i]) THEN REMOVE "$" FROM Stk$[i]
      Buffer$ = Buffer$ + Stk$[i] + Sep$
    NEXT
    Buffer$ = Stk$[1] + Buffer$
    IF InConditional THEN
      IF InFunc THEN
        FPRINT Outfile,Buffer$
      ELSE
        IF ConstLastDef$ <> "FP6" THEN
          FPRINT FP6,InIfDef$,"// FP6"
          ConstLastDef$ = "FP6"
        END IF
        FPRINT FP6,Buffer$
      END IF
    ELSE
      FPRINT FP6,Buffer$
    END IF
    '***********************
    CASE "kill"
    '***********************
    FPRINT Outfile,Scoot$,"remove (";
    FOR A = 2 TO Ndx
      FPRINT Outfile,Clean$(TRIM$(Stk$[A]));
    NEXT
    FPRINT Outfile,");"
    '***********************
    CASE "chdir", "_chdir", "rmdir", "_rmdir", "mkdir", "_mkdir"
    '***********************
    FPRINT Outfile,Scoot$,Lookup$;" (";
    FOR A = 2 TO Ndx
      FPRINT Outfile,Clean$(TRIM$(Stk$[A]));
    NEXT
    FPRINT Outfile,");"
    '***********************
    CASE "free"
    '***********************
    DIM RAW VI AS VarInfo PTR
    A = 2
    IF iMatchWrd(Stk$[2], "dynamic") THEN A = 3
    IF Stk$[A] = "(" THEN
      INCR A
      DECR Ndx
    END IF
    CVar$ = Clean$(Stk$[A])
    vt = CheckLocal(CVar$, &id)
    IF vt = vt_UNKNOWN THEN
      vt = CheckGlobal(CVar$, &id)
      IF vt = vt_UNKNOWN THEN
        Abort("Can not REDIM " + CVar$ + " not previously dimensioned")
      END IF
      VI = &GlobalVars[id]
    ELSE
      VI = &LocalVars[id]
      Warning("Local dynamic variables are automatically freed.", 1)
    END IF
    CVar$ = ""
    FOR i = A TO Ndx
      CVar$ = CVar$ + Stk$[i]
    NEXT
    CVar$ = Clean$(CVar$)
    IF vt = vt_STRUCT OR vt = vt_UNION THEN
      GetElement$(2, &vt, &dms, VI->VarDef)
      IF vt <> vt_UNKNOWN AND dms > 0 THEN
        Use_DynamicA = TRUE
        FPRINT Outfile,Scoot$,"if (",  CVar$;
        FPRINT Outfile,") { DestroyArr((void **)", CVar$, ",", dms, ", 1); ";
        FPRINT Outfile,CVar$ ; "=NULL; }"
        EXIT SELECT
      END IF
    END IF
    IF VI->VarPntr > 1 THEN
      Use_DynamicA = TRUE
      FPRINT Outfile,Scoot$,"if ("   ; CVar$ ;
      FPRINT Outfile,") { DestroyArr((void **)" + CVar$ + "," + STR$(VI->VarPntr) + ", 1); ";
      FPRINT Outfile,CVar$ ; "=NULL; }"
    ELSE
      FPRINT Outfile,Scoot$,"free(", CVar$, "), ", CVar$, "=NULL;"
    END IF
    '*************************************************************************
    CASE "midstr"
    '*************************************************************************
    Src$ = ""
    FOR A = 1 TO Ndx
      CONCAT(Src$,Clean$(Stk$[A]))
    NEXT
    FPRINT Outfile,Scoot$, TRIM$(Src$), ";"
    '***********************
    CASE "swap"
    '***********************
    RAW VI1 AS VarInfo PTR
    RAW VI2 AS VarInfo PTR
    RAW indx AS INTEGER
    FPRINT Outfile,Scoot$,"swap ((BYTE*)&";
    FOR i = 2 TO Ndx
      IF Stk$[i]= "," THEN EXIT FOR
      FPRINT Outfile,Clean$(Stk$[i]);
    NEXT
    A = CheckLocal(Stk$[2], &indx)
    IF A = vt_UNKNOWN THEN
      A = CheckGlobal(Stk$[2], &indx)
      IF A = vt_UNKNOWN THEN
        Abort("Variable '"+Stk$[2]+"' in swap statement unknown")
      END IF
      VI1 = &GlobalVars[indx]
    ELSE
      VI1 = &LocalVars[indx]
    END IF
    IF RIGHT$(Stk$[i-1],1) <> "]" THEN
      IF VI1->VarType = vt_CHAR AND VI1->VarPntr = 1 THEN FPRINT Outfile,"[0]";
    END IF
    FPRINT Outfile,",(BYTE*)&";
    i++
    FOR j = i TO Ndx
      FPRINT Outfile,Clean$(Stk$[j]);
    NEXT
    A = CheckLocal(Stk$[i], &indx)
    IF A = vt_UNKNOWN THEN
      A = CheckGlobal(Stk$[i], &indx)
      IF A = vt_UNKNOWN THEN
        Abort("Variable '"+Stk$[i]+"' in swap statement unknown")
      END IF
      VI2 = &GlobalVars[indx]
    ELSE
      VI2 = &LocalVars[indx]
    END IF
    IF RIGHT$(Stk$[j-1],1) <> "]" THEN
      IF VI2->VarType = vt_CHAR AND VI2->VarPntr = 1 THEN FPRINT Outfile,"[0]";
    END IF
    IF VI1->VarType <> VI2->VarType THEN
      Warning("Possible size error in swap statement")
    END IF
    IF VI2->VarType = vt_STRVAR OR VI2->VarType = vt_CHAR THEN
      FPRINT Outfile,",strlen(";
    ELSE
      FPRINT Outfile,",sizeof(";
    END IF
    FOR j = i TO Ndx
      FPRINT Outfile,Clean$(Stk$[j]);
    NEXT
    FPRINT Outfile,"));"
    '***********************
    CASE "rename"
    '***********************
    FPRINT Outfile,Scoot$,"rename (";
    FOR A = 2 TO Ndx
      FPRINT Outfile,Clean$(TRIM$(Stk$[A]));
    NEXT
    FPRINT Outfile,");"
    '***********************
    CASE "copyfile"
    '***********************
    FPRINT Outfile,Scoot$,"CopyFile ";
    IF Stk$[2] <> "(" THEN FPRINT Outfile, "(";
    FOR A = 2 TO Ndx
      FPRINT Outfile,Clean$(TRIM$(Stk$[A]));
    NEXT
    IF Stk$[Ndx] <> ")" THEN
      FPRINT Outfile, ");"
    ELSE
      FPRINT Outfile, ";"
    END IF
    '***********************
    CASE "shell"
    '***********************
    IF Ndx > 2 THEN
      FOR A = 3 TO Ndx
        Stk$[2] = Stk$[2] + Stk$[A]
      NEXT
    END IF
    ZZ$ = Stk$[2]
    IF ZZ$ = "" THEN ZZ$ = DDQ$
    FPRINT Outfile,Scoot$ ; "Shell(" ; Clean$(ZZ$) ; ");"


    '*****************************************************************************
    CASE "lineinput"
    '                    LINEINPUT "prompt", A$  <<< Keyboard version 4.21
    '*****************************************************************************
    '     Test for new keyboard version of LINE INPUT
    i = DataType(Stk$[2])
    IF i = vt_STRLIT OR i = vt_STRVAR THEN
      IF i <> vt_STRLIT THEN Stk$[2] = Clean$(Stk$[2])
      FPRINT Outfile,Scoot$,"printf(", ENC$("%s"), ",", Stk$[2], ");"
      FPRINT Outfile,Scoot$,"AR_fgets_retval=fgets(", Clean$(Stk$[3]),  ",2048-1,stdin);"
      FPRINT Outfile,Scoot$,Clean$(Stk$[3]),"[strlen(",Clean$(Stk$[3]),")-1]=0;"
      EXIT SELECT
    END IF
    ' ********************* Okay, we're dealing with a file ************************
    REMOVE "#" FROM Stk$[2]
    IF DataType(Stk$[2]) = vt_NUMBER THEN
      Stk$[2]= "FP" & Stk$[2]
    END IF
    Handl$ = EXTRACT$(Stk$[2], "[")
    IF CheckLocal(Handl$, &i) = vt_UNKNOWN THEN
      IF CheckGlobal(Handl$, &i) = vt_UNKNOWN THEN
        CALL AddGlobal(Handl$, vt_FILEPTR, 0,"",0,0,0,0)
      END IF
    END IF
    Var$ = Clean$(Stk$[3])
    Var1$ = ""
    CVar$ = Var$
    IF INCHR( Var$, "[" ) AND INCHR( Var$, "]" ) THEN
      IF INSTR( Var$, "[++" ) THEN
        REPLACE "++" WITH "" IN CVar$
      END IF
      IF INSTR( Var$, "[--" ) THEN
        REPLACE "--" WITH "" IN CVar$
      END IF
      IF INSTR( Var$, "++]" ) THEN
        REPLACE "++" WITH "" IN CVar$
        Var1$ = MID$(Var$,INCHR(Var$,"[")+1)
        Var1$ = EXTRACT$(Var1$,"]")
        Var$ = CVar$
      END IF
      IF INSTR( Var$, "--]" ) THEN
        REPLACE "--" WITH "" IN CVar$
        Var1$ = MID$(Var$,INCHR(Var$,"[")+1)
        Var1$ = EXTRACT$(Var1$,"]")
        Var$ = CVar$
      END IF
    END IF
    FPRINT Outfile,Scoot$, Var$ ; "[0]=0;"
    FPRINT Outfile,Scoot$, "AR_fgets_retval=fgets(" ; Var$ ; ",1048576,"; Clean$(Stk$[2]) ; ");"
    FPRINT Outfile,Scoot$, "if("    ; CVar$ ; "[strlen(" ;CVar$ ; ")-1]==10)";
    FPRINT Outfile,CVar$  ; "[strlen(" ; CVar$ ; ")-1]=0;"
    IF Var1$ <> "" THEN
      FPRINT Outfile,Var1$ ; ";"
    END IF
    '*************************************************************************
    CASE "open"
    '*************************************************************************
    FOR A = 1 TO Ndx
      Keyword$ = LCASE$(Stk$[A])
      SELECT CASE Keyword$
        CASE "open"
        Stk$[A] = ""
        CASE "for"
        Stk$[A] = ""
        Filnam$ = ""
        FOR j = 2 TO A-1
          CONCAT (Filnam$,Stk$[j])
        NEXT
        Filnam$ = Clean$(Filnam$)
        CASE "as"
        Stk$[A] = ""
        IF DataType(Stk$[A + 1]) = vt_NUMBER THEN
          Stk$[A + 1] = "FP" + Stk$[A + 1]
        END IF
        IF CheckLocal(Stk$[A + 1], &i) = vt_UNKNOWN THEN
          IF CheckGlobal(Stk$[A + 1], &i) = vt_UNKNOWN THEN
            CALL AddGlobal(Stk$[A + 1], vt_FILEPTR, 0,"",0,0,0,0)
          END IF
        END IF
        Var$ = ""
        FOR j = A+1 TO Ndx
          IF iMatchWrd(Stk$[j], "reclen") THEN EXIT FOR
          CONCAT (Var$,Stk$[j])
          Stk$[j] = ""
        NEXT
        Handl$ = Var$ + "@"
        CASE "network"
            Use_Socket = TRUE
        CASE "input"
        Op$ = ENC$("r")
        Stk$[A] = ""
        CASE "output"
        Op$ = ENC$("w")
        Stk$[A] = ""
        CASE "append"
        Op$ = ENC$("a")
        Stk$[A] = ""
        CASE "binary"
        Op$ = ENC$("rb+")
        Stk$[A] = ""
        CASE "binaryappend"
        Op$ = ENC$("ab+")
        Stk$[A] = ""
        CASE "binarynew"
        Op$ = ENC$("wb+")
        Stk$[A] = ""
        CASE "binaryinput"
        Op$ = ENC$("rb")
        Stk$[A] = ""
        CASE "binaryoutput"
        Op$ = ENC$("rb+")
        Stk$[A] = ""
        CASE "reclen"
        IF Stk$[A+1] = "=" THEN
          FOR j = A+2 TO Ndx
            Stk$[j-1] = Stk$[j]
          NEXT
          Ndx--
        END IF
        Var$ = EXTRACT$(Clean$(Handl$), "[") + "len"
        IF CheckLocal(Var$, &i) = vt_UNKNOWN THEN
          CALL AddGlobal(Var$, vt_INTEGER , 0,"",0,0,0,0)
        ELSE
          IF CheckLocal(Var$, &i) = vt_UNKNOWN THEN
            CALL AddLocal(Var$, vt_INTEGER , 0,"",0,0,0)
            Var$ = "int " + Var$
          END IF
        END IF
        i = CheckType(Stk$[A+1])
        ZZ$ = LCASE$(Stk$[A+1])
        IF i = vt_STRUCT OR i = vt_UNION OR ZZ$ = "int" OR ZZ$ = "double" OR ZZ$ = "float" THEN
          FPRINT Outfile,Scoot$,Var$ + " = sizeof(";Stk$[A+1];");"
        ELSE
          FPRINT Outfile,Scoot$,Var$ + " = ";Clean$(Stk$[A+1]);";"
        END IF
        Stk$[A] = ""
        Stk$[A + 1] = ""
      END SELECT
    NEXT
    FPRINT Outfile,Scoot$,"if((";Clean$(Handl$);"=fopen(";Filnam$;",";Op$;"))==0)"
    FPRINT Outfile,Scoot$," {"
    lszTmp$ = ENC$("Can't open file %s\\n")
    FPRINT Outfile,Scoot$,"   fprintf(stderr,";lszTmp$;",";Filnam$;");"
    FPRINT Outfile,Scoot$,"   exit(1);"
    FPRINT Outfile,Scoot$," }"

    '*************************************************************************
    ' Statement  RECORD [#] filenumber,recordnumber [,location in record]
    ' Definition:          Position the file pointer anywhere in a file.
    ' filenumber           Filenumber from  1 to 99
    ' record number        RECORD number to point to. Default first record
    ' location in record   Optional location in RECORD. Default is Zero
    ' RECORD fp1, 6[, 10]
    '*************************************************************************
    CASE "record"
    DIM ffp AS functionParse
    DIM RAW numargs = 0
    IF DataType(Stk$[2]) = vt_NUMBER THEN
      Stk$[2]= "FP"  +  Stk$[2]
    END IF
    IF Ndx > 1 THEN numargs = SepFuncArgs(1, &ffp, FALSE)
    IF numargs < 1 THEN Abort("Missing required arguments to RECORD")
    IF numargs > 4 THEN Abort("Too many arguments to RECORD")
    IF numargs = 3 THEN
      FPRINT Outfile,Scoot$,"fseek("; GetArg$(1, &ffp); _
      ", ("; GetArg$(2, &ffp); " - 1) * ";Stk$[2];"len + ";GetArg$(3, &ffp);", SEEK_SET);"
    ELSEIF numargs = 2 THEN
      FPRINT Outfile,Scoot$,"fseek("; GetArg$(1, &ffp); _
      ", ("; GetArg$(2, &ffp); " - 1) * ";Stk$[2];"len, SEEK_SET);"
    ELSE
      FPRINT Outfile,Scoot$,"fseek("; GetArg$(1, &ffp); ", 0, SEEK_SET);"
    END IF
    '***********************
    CASE "fwrite"
    '***********************
    IF DataType(Stk$[2]) = vt_NUMBER THEN
      Stk$[2] = "FP" + Stk$[Ndx]
    END IF
    IF CheckLocal(Stk$[2], &i) = vt_UNKNOWN THEN
      CALL AddGlobal(Stk$[2], vt_FILEPTR, 0,"",0,0,0,0)
    END IF
    Handl$ = ""
    FOR j = 2 TO Ndx
      IF iMatchWrd(Stk$[j], ",") OR iMatchWrd(Stk$[j], ";") THEN
        Stk$[j] = "" 'get rid of the Comma
        EXIT FOR
      END IF
      Handl$ = Handl$ + Stk$[j]
      Stk$[j] = "" 'get rid of handle
    NEXT j
    Handl$ = Handl$ + "@"
    ZZ$ = "f" + PrintWriteFormat$(1)
    ZZ$ = LEFT$(ZZ$,8)  +  Clean$(Handl$)  +  ","  +  MID$(ZZ$,9)
    FPRINT Outfile,Scoot$, ZZ$
    '***********************
    CASE "close"
    '***********************
    IF Ndx = 1 THEN
      FPRINT Outfile,Scoot$, "fcloseall();"
      EXIT SELECT
    END IF
    IF DataType(Stk$[2]) = vt_NUMBER THEN
      Stk$[2]= "FP"  +  Stk$[Ndx]
    END IF
    IF CheckLocal(Stk$[2], &i) = vt_UNKNOWN THEN
      IF CheckGlobal(Stk$[2], &i) = vt_UNKNOWN THEN
        CALL AddGlobal(Stk$[2], vt_FILEPTR, 0,"",0,0,0,0)
      END IF
    END IF
    Handl$ = ""
    FOR j = 2 TO Ndx
      Handl$ = Handl$ + Stk$[j]
    NEXT j
    FPRINT Outfile,Scoot$,"if(",Handl$,")"
    FPRINT Outfile,Scoot$," {"
    FPRINT Outfile,Scoot$,"   fclose(";Handl$;");"
    FPRINT Outfile,Scoot$,"   ";Handl$;"=NULL;"
    FPRINT Outfile,Scoot$," }"
    '***********************
    CASE "call"
    '***********************
    lszTmp$ = ""
    FOR Tmp = 2 TO Ndx
      CONCAT(lszTmp$,  Clean$(Stk$[Tmp]))
    NEXT
    IF NOT iMatchRgt(lszTmp$,")") THEN
      CONCAT(lszTmp$,  "()")
    END IF
    CONCAT(lszTmp$,  ";")
    FPRINT Outfile,Scoot$,lszTmp$
    '*************************************************************************
    CASE "declare"
    '*************************************************************************
    DIM FP AS functionParse
    DIM RAW TempProto$
    CALL FuncSubDecs1("sub") 'convert [] to pointer * and $[] to [][2048]
    CALL SepFuncArgs(3, &FP, TRUE)
    TempProto$ = MakeDecProto$(&FP)
    IF NOT NoTypeDeclare THEN
      FPRINT FP4, TempProto$, ";"
    ELSE
      ProtoCnt++
      ProtoType[ProtoCnt].Prototype$ = TempProto$ + ";"
    END IF
    '*************************************************************************
    '/***** 2010-11-16 Added Constructor/Destructor - AIR *****/
    CASE "function", "sub", "constructor", "destructor"
    '*************************************************************************
    DIM CTOR_USE$, CTOR_SRC$, New_Ndx
    IF Stk$[2] = "main" THEN
      Stk$[1] = "function"
      Stk$[2] = "main%"
      ForceMainToFunc = TRUE
    END IF

    '/***** 2010-11-17 Added to change constructor/destructor to sub -AIR *****/
    IF iMatchWrd(Stk$[1], "constructor") OR iMatchWrd(Stk$[1], "destructor") THEN
      Stk$[1] = "sub"
      '/***** 2010-11-18 this extracts the derived class method after "USING" keyword *****/
      '/***** and stuffs it into CTOR_USE$ variable - AIR *****/
      FOR INTEGER ct = 1 TO Ndx
        IF Stk$[ct] = "using" THEN
          New_Ndx = ct-1 '/*** SEE NEXT COMMENT!!! -AIR *****/
          FOR INTEGER ut = ct TO Ndx
            CTOR_USE$ = CTOR_USE$ + Stk$[ut]
          NEXT
        END IF
      NEXT



      IF LEN(CTOR_USE$) THEN
        IREPLACE "using" WITH ":" IN CTOR_USE$
        '/***** 2010-11-18 Truncates current line so that everything AFTER "USING" keyword is NOT *****/
        '/***** processed by default FUNCTION/SUB parser! -AIR *****/
        Ndx = New_Ndx
        '/*********************************************************************************************/
      END IF
      Use_Ctor = TRUE
    END IF

    CALL FuncSubDecs1("sub")

    IsStdFunc = FALSE
    IF iMatchWrd(Stk$[Ndx],"stdcall") THEN
      CallType$ = "__attribute__((stdcall)) "
      Ndx--
      IsStdFunc = TRUE
    END IF
    InFunc = TRUE
    InMain = FALSE
    LocalVarCnt = 0
    '~ Outfile = FP3
    '/** 2010/11/30 Added -AIR **/
    IF InNameSpace THEN
      Outfile = FP2
    ELSE
      Outfile = FP3
    END IF

    CALL FuncSubDecs2("sub", mt_FuncSubDecC_Dec)
    ' to compensate previous substitution errors not fixed
    VarCode.Functype$ = LTRIM$(VarCode.Functype$)

    Funcname$ = Clean$(Stk$[2])
    IF IsExported OR IsStdFunc THEN
      Funcname$ = CallType$ + Funcname$
    END IF
    VarCode.Method% = mt_FuncSubDecC_Dec2
    A = 3
    WHILE A <= Ndx
      IF Stk$[A+1] = "(" THEN ' sub/function ptr
        FOR k = A+2 TO Ndx
          IF Stk$[k] = ")" THEN
            EXIT FOR
          END IF
        NEXT

        IF iMatchWrd(Stk$[k+2], "sub") THEN
          j = vt_VOID
          VarCode.AsToken$ = "void"
        ELSEIF iMatchWrd(Stk$[k+2], "function") THEN
          CALL GetTypeInfo(Stk$[k+3], &IsPointer, &i, &j)
          VarCode.AsToken$ = Stk$[k+3]
        END IF
        VarCode.Token$ = Stk$[A]
        VarCode.VarNo% = j
        VarCode.IsPtrFlag = 1
        VarCode.Method% = mt_FuncSubx1
        CALL GetVarCode(&VarCode)
        Var$ = Clean$(Stk$[A])

        lszTmp$ = ""
        A += 2
        WHILE A <= k
          IF iMatchWrd(Stk$[A+1], "as") AND A < k THEN
            Tmp = A + 2
            WHILE Stk$[Tmp] <> "," AND Stk$[Tmp] <> ")"
              CALL GetTypeInfo(Stk$[Tmp], &IsPointer, &i, &j)
              CALL AddLocal(Stk$[A], j, i, "", IsPointer,0,0)
              VarCode.Token$ = Stk$[A]
              VarCode.AsToken$ = Stk$[Tmp]
              VarCode.VarNo% = j
              VarCode.IsPtrFlag = 1
              VarCode.Method% = mt_FuncSubx2
              CALL GetVarCode(&VarCode)
              Tmp++
              IF Stk$[Tmp] = "," THEN
                CONCAT(VarCode.Proto$,",")
                CONCAT(VarCode.Header$,",")
              END IF
            WEND
            A = Tmp
          ELSE
            IF Stk$[A] <> "," AND Stk$[A] <> ")" THEN
              IsPointer = TALLY((Stk$[A]), "*")
              Var$ = REMOVE$(Stk$[A], "*") ' in case we used ptr
              j = DataType(Var$)
              IF j <> vt_UNKNOWN AND InFunc = TRUE AND Var[0] THEN
                CALL AddLocal(Clean(Var$), j, 0, "", IsPointer,0,0)
              END IF
              VarCode.Token$ = Stk$[A]
              VarCode.AsToken$ = ""
              VarCode.VarNo% = j
              VarCode.IsPtrFlag = IsPointer
              VarCode.Method% = mt_FuncSubDecC_Dec2
              CALL GetVarCode(&VarCode)
            END IF
          END IF
          A++
        WEND
        A = k+3
        IF VarCode.Method% = mt_FuncSubDecC_Dec2 THEN
          MID$(VarCode.Proto$,LEN(VarCode.Proto$)-1,1) = ")"
          MID$(VarCode.Header$,LEN(VarCode.Header$)-1,1) = ")"
        ELSE
          CONCAT(VarCode.Proto$,")")
          CONCAT(VarCode.Header$,")")
        END IF
        VarCode.Method% = mt_FuncSubDecC_Dec2
      ELSE
        IF iMatchWrd(Stk$[A+1],"as") THEN
          CALL GetTypeInfo(Stk$[A+2], &IsPointer, &i, &j)
          Var$ = Clean$(Stk$[A])
          CALL AddLocal(Var$, j, i, "", IsPointer,0,0)
          VarCode.Token$ = Stk$[A]
          VarCode.AsToken$ = Stk$[A+2]
          VarCode.VarNo% = j
          VarCode.IsPtrFlag = IsPointer
          CALL GetVarCode(&VarCode)
          Stk$[A+1] = ""
          Stk$[A+2] = ""
          A+=2
        ELSE
          IF INCHR("=", Stk$[A]) AND Stk$[A] <> "" THEN
            CALL Abort("Illegal optional parameter found")
          END IF
          IF NOT INCHR(",().",Stk$[A]) AND Stk$[A] <> "" THEN
            IsPointer = TALLY((Stk$[A]), "*")
            Var$ = REMOVE$(Stk$[A], "*") ' in case we used ptr
            j = DataType(Var$)
            IF j <> vt_UNKNOWN AND Var[0] THEN
              CALL AddLocal(Clean(Var$), j, 0, "", IsPointer,0,0)
            END IF
            VarCode.Token$ = Stk$[A]
            VarCode.AsToken$ = ""
            VarCode.VarNo% = j
            VarCode.IsPtrFlag = IsPointer
            CALL GetVarCode(&VarCode)
          END IF
        END IF
      END IF
      A++
    WEND
    VarCode.Method% = 2
    VarCode.Token$ = Funcname$
    FuncSubDecs3(&VarCode)
    IF iMatchLft(VarCode.Header$,"main(")  THEN
      VarCode.Header$ = "int main(int argc, char *argv[])"
      VarCode.Proto$  = "int main(int argc, char *argv[]);"
      CurrentFuncType = vt_INTEGER
    END IF
    IF Use_Static THEN
      VarCode.Header$ = "static " + VarCode.Header$
      VarCode.Proto$  = "static " + VarCode.Proto$
    END IF

    '/** 2010/11/30 DON'T EMIT FUNCTION PROTOTYPE FOR NAMESPACE -AIR **/
    IF NOT InNameSpace THEN
      ProtoCnt++
      ProtoType[ProtoCnt].Prototype$ = VarCode.Proto$
    END IF

    IF InIfDef$ = "FP3" THEN
      IF ProtoCnt > 1 THEN
        ProtoType[ProtoCnt].Condition$ = ProtoType[ProtoCnt-1].Condition$
      ELSE
        ProtoType[ProtoCnt].Condition$ = ""
      END IF
    ELSE
      ProtoType[ProtoCnt].Condition$ = InIfDef$
    END IF
    ProtoType[ProtoCnt].CondLevel  = InConditional

    IF *InIfDef$ THEN
      IF InIfDef$ <> "FP3" THEN
        FPRINT Outfile,InIfDef$
        PRINT InIfDef$
      END IF
    END IF




    '/***** 2010-11-17 Check if Constructor/Destructor, if so remove VOID from Method Sig -AIR *****/
    IF Use_Ctor THEN
      REPLACE "void " WITH "" IN VarCode.Header$
      REPLACE "void" WITH "" IN VarCode.Header$
      '/***** 2010-11-18 Emit derived class methods via "USING" keyword if required -AIR *****/
      IF LEN (CTOR_USE$) THEN
        FPRINT Outfile,VarCode.Header$
        FPRINT Outfile,Scoot$,CTOR_USE$
      ELSE
        FPRINT Outfile,VarCode.Header$
      END IF
      Use_Ctor = FALSE
      '/** 2010/11/30 Added Wayne's fix for NAMESPACE -AIR **/
    ELSEIF InNameSpace THEN
      'FPRINT Outfile,Scoot$;VarCode.Header$
      RAW szCPP_SF1$
      szCPP_SF1$ = ""
      IF iMatchLft(Lookup$,"public") THEN szCPP_SF1$ = "public: virtual "
      FPRINT Outfile,Scoot$;szCPP_SF1$;VarCode.Header$
    ELSE
      FPRINT Outfile,VarCode.Header$
    END IF
    FPRINT Outfile,Scoot$,"{"
    CALL BumpUp
    '***********************************************
    CASE "optfunction", "optsub"
    '***********************************************
    CALL FuncSubDecs1("optsub")
    InFunc  = TRUE
    LocalVarCnt = 0
    Outfile = FP3

    '/** Added -AIR **/
    IF InNameSpace THEN
      Outfile = FP2
    ELSE
      Outfile = FP3
    END IF

    CALL FuncSubDecs2("optsub", mt_Opts)
    Funcname$ = Clean$(Stk$[2])
    VarCode.Method% = mt_Opts2
    A = 4
    WHILE A < Ndx
      IF Stk$[A] = "" THEN A++ : ITERATE
      IF Stk$[A] = "," THEN
        VarCode.Method% = mt_Opts3
        VarCode.Token$ = Stk$[A]
        CALL GetVarCode(&VarCode)
        VarCode.Method% = mt_Opts2
      ELSEIF Stk$[A] = "=" THEN
        VarCode.Method% = mt_Opts3
        IF Stk$[A + 1] = "-" THEN
          VarCode.Token$ = Stk$[A] + Stk$[A + 1] + Stk$[A + 2]
          Stk$[A + 1] = "" : Stk$[A + 2] = "" : A++
        ELSE
          VarCode.Token$ = Stk$[A] + Stk$[A + 1]
          Stk$[A + 1] = ""
        END IF
        IF iMatchWrd(Stk$[A+2],"as") THEN
          Stk$[A + 2] = "" : Stk$[A + 3] = ""
        END IF
        VarCode.VarNo% = j
        VarCode.IsPtrFlag = IsPointer
        CALL GetVarCode(&VarCode)
        VarCode.Method% = mt_Opts2
      ELSEIF iMatchWrd(Stk$[A+1],"as") THEN
        CALL GetTypeInfo(Stk$[A+2], &IsPointer, &i, &j)
        IF InFunc THEN
          Var$ = Clean$(Stk$[A])
          CALL AddLocal(Var$, j, i, "", IsPointer,0,0)
        END IF
        VarCode.VarNo%    = j
        VarCode.Token$    = Stk$[A]
        VarCode.AsToken$  = Stk$[A+2]
        VarCode.IsPtrFlag = IsPointer
        CALL GetVarCode(&VarCode)
        Stk$[A+1]= "" : Stk$[A+2]= ""
      ELSE
        IsPointer = TALLY((Stk$[A]),"*")
        Var$ = REMOVE$(Stk$[A],"*") ' in case we used ptr
        j = DataType(Var$)
        IF j <> vt_UNKNOWN THEN
          CALL AddLocal(Clean(Var$),j,0,"",IsPointer,0,0)
        END IF
        VarCode.VarNo% = j
        VarCode.Token$ = Stk$[A]
        VarCode.AsToken$ = ""
        VarCode.IsPtrFlag = IsPointer
        CALL GetVarCode(&VarCode)
      END IF
      A++
    WEND
    VarCode.Method% = 2
    VarCode.Token$ = Funcname$
    FuncSubDecs3(&VarCode)
    IF Use_Static THEN
      VarCode.Header$ = "static " + VarCode.Header$
      VarCode.Proto$ = "static " + VarCode.Proto$
    END IF
    ProtoCnt++
    ProtoType[ProtoCnt].Prototype$ = VarCode.Proto$
    IF InIfDef$ = "FP3" THEN
      ProtoType[ProtoCnt].Condition$ = ""
    ELSE
      ProtoType[ProtoCnt].Condition$ = InIfDef$
    END IF
    ProtoType[ProtoCnt].CondLevel  = InConditional
    FPRINT Outfile,VarCode.Header$
    FPRINT Outfile,Scoot$,"{"
    CALL BumpUp
    '*******************************************
    CASE "overloadedfunction", "overloadedsub"
    '*******************************************
    Use_Overloaded = TRUE
    CALL FuncSubDecs1("overloadedsub")
    InFunc = TRUE
    InMain = FALSE
    LocalVarCnt = 0
    Outfile = FP8 '<<----- writing TO BCX.OVR
    CALL FuncSubDecs2("overloadedsub", mt_OverLoad)
    Funcname$ = Clean$(Stk$[2])
    lszTmp$ = " overloaded " + Funcname$
    Funcname$ = lszTmp$
    VarCode.Method% = mt_OverLoad2
    FOR A = 3 TO Ndx
      IF iMatchWrd(Stk$[A+1],"as") THEN
        CALL GetTypeInfo(Stk$[A+2], &IsPointer, &i, &j)
        Var$ = Clean$(Stk$[A])
        CALL AddLocal(Var$, j, i, "", IsPointer,0,0)
        VarCode.AsToken$ = Stk$[A+2]
        Stk$[A+1] = ""
        Stk$[A+2] = ""
      ELSE
        Var$ = REMOVE$(Stk$[A],"*") ' in case we used ptr
        j = DataType(Var$)
        IF NOT INCHR(",().",Stk$[A]) AND Stk$[A] <> "" THEN
          IsPointer = TALLY((Stk$[A]),"*")
          IF j <> vt_UNKNOWN AND InFunc = TRUE AND Var[0] THEN
            CALL AddLocal(Clean(Var$), j, 0, "", IsPointer,0,0)
          END IF
        END IF
        VarCode.AsToken$ = ""
      END IF
      VarCode.VarNo% = j
      VarCode.Token$ = Stk$[A]
      CALL GetVarCode(&VarCode)
    NEXT
    VarCode.Method% = 1
    VarCode.Token$ = Funcname$
    FuncSubDecs3(&VarCode)
    IF Use_Static THEN
      VarCode.Header$ = "static " + VarCode.Header$
    END IF
    FPRINT Outfile,VarCode.Header$
    FPRINT Outfile,Scoot$,"{"
    CALL BumpUp
    '*******************************************************************
    CASE "functionreturn"
    '*******************************************************************
    IF CaseFlag THEN NoBreak2 = TRUE
    lszTmp$ = ""
    FOR A = 3 TO Ndx
      lszTmp$ = lszTmp$ + Stk$[A] + " "
    NEXT
    IF CurrentFuncType = vt_STRVAR THEN
      lszTmp$ = "BCX_RetStr$ = " + lszTmp$
      FuncRetnFlag = 1 '1 = return a string
      UseFlag = TRUE
    ELSE
      FuncRetnFlag = 2 '2 = return a number
    END IF
    IF FuncRetnFlag = 2 THEN
      '*********************************
      '    Clean up dynamic strings
      '*********************************
      IF LocalDynaCnt <> 0 THEN
        FOR j = 1 TO LocalDynaCnt
          FPRINT Outfile,Scoot$,DynaStr$[j]
        NEXT
      END IF
      '*********************************
      ' Clean up dynamic strings arrays
      '*********************************
      IF LocalDynArrCount <> 0 THEN
        FOR i = 1 TO LocalDynArrCount
          FPRINT Outfile,Scoot$,LocalDynArrName$[i]
        NEXT
      END IF
      '*********************************
      FPRINT Outfile,Scoot$,"return ";
      LastCmd = 2
    END IF
    CALL Parse(lszTmp$)
    LastCmd = 0
    GOTO EmitAgain
    '*******************************
    '/***** 2010-11-16 Added endconstructor/enddestructor - AIR *****/
    CASE "endfunction", "endsub", "endconstructor", "enddestructor"
    '*******************************
    IF iMatchWrd(Stk$[1],"endfunction") THEN
      LocalDynaCnt = 0
      LocalDynArrCount = 0
    END IF
    '/***** 2010-11-16 Added endconstructor/enddestructor - AIR *****/
    IF iMatchWrd(Stk$[1],"endsub") OR iMatchWrd(Stk$[1],"endconstructor") OR iMatchWrd(Stk$[1],"enddestructor") THEN
      '**************************
      ' Clean up dynamic strings
      '**************************
      IF LocalDynaCnt <> 0 THEN
        FOR j = 1 TO LocalDynaCnt
          FPRINT Outfile,Scoot$,DynaStr$[j]
        NEXT
        LocalDynaCnt = 0
      END IF
      '*********************************
      ' Clean up dynamic strings arrays
      '*********************************
      IF LocalDynArrCount <> 0 THEN
        FOR i = 1 TO LocalDynArrCount
          FPRINT Outfile,Scoot$,LocalDynArrName$[i]
        NEXT
        LocalDynArrCount = 0
      END IF
    END IF
    '*********************************
    IF ForceMainToFunc = TRUE THEN
      FPRINT Outfile,Scoot$,"return 0;"
      ForceMainToFunc = FALSE
    END IF
    CALL BumpDown
    '~ FPRINT Outfile,Scoot$,"}\n\n"
    '~ CALL BumpDown
    //** 2010/11/30 Added FOR NAMESPACE -AIR **/
    IF InNameSpace THEN
      FPRINT FP2,Scoot$,"}\n"
    ELSE
      FPRINT Outfile,Scoot$,"}\n\n"
      CALL BumpDown
    END IF

    InFunc = FALSE
    Use_Static = FALSE
    IF Outfile = FP3 THEN
      InIfDef$ = "FP3"
    END IF
    Outfile = FP2
    ByrefCnt = 0
    '***********************
    CASE "input"
    '***********************
    CALL EmitInputCode
    '***********************
    CASE "finput"
    '***********************
    CALL EmitFileInputCode
    '***********************
    CASE "dynamic"
    '***********************
    DIM RAW w = 0
    DIM RAW SOF$
    CALL HandleNonsense
    CVar$ = Clean$(Stk$[2])
    CALL ValidVar(CVar$)
    IF Stk$[Ndx] = "*" THEN CALL PointerFix
    IF Stk$[Ndx] = "&" THEN Stk$[Ndx--] = "" : CONCAT(Stk$[Ndx], "&")
    ZZ$ = ""
    IF iMatchWrd(Stk$[Ndx-1], "as") THEN
      SOF$ = Stk$[Ndx]
      GetTypeInfo(SOF$, &w, &id, &vt)
      IF vt = vt_STRLIT OR vt = vt_DECFUNC OR vt = vt_NUMBER OR _
        (vt = vt_VOID AND INCHR(Stk$[Ndx], "*") = 0) THEN
        Abort(SOF$ + " is not a valid type")
      END IF
      IF vt = vt_FILEPTR AND INCHR(SOF$, "*") = 0 THEN SOF$ = SOF$ + "*"
      Ndx -= 2
    ELSE
      vt = DataType(Stk$[2])
      id = 0
      SOF$ = GetVarTypeName$(vt)
    END IF
    Use_DynamicA = TRUE
    FOR i = 3 TO Ndx
      CONCAT(ZZ$, Stk$[i])
    NEXT
    dms = TALLY(ZZ$,"][") + 1
    IF dms > 1 THEN REPLACE "][" WITH "," IN ZZ$
    ZZ$ = Clean$(ZZ$)
    RemoveAll(ZZ$,"[]")
    IF vt = vt_STRVAR THEN
      vt = vt_CHAR
      SOF$ = "char"
      IF InTypeDef THEN
        IF Stk$[3] <> "[" THEN
          DECR dms
        ELSE
          vt = vt_CHARPTR
        END IF
      END IF
      dms++
      CONCAT(ZZ$,",65535")
    END IF
    IF InTypeDef THEN
      IF vt = vt_STRUCT THEN
        FPRINT Outfile, Scoot$, "struct _", SOF$, "  ", STRING$(dms,42), CVar$, ";"
      ELSE
        FPRINT Outfile, Scoot$, SOF$, "  ", STRING$(dms,42), CVar$, ";"
      END IF
      CALL AddTypedefElement(BaseTypeDefsCnt[InTypeDef], vt, CVar$, SOF$, dms)
    ELSEIF InFunc THEN
      LocalDynArrCount++
      LocalDynArrName$ [LocalDynArrCount] = "if (" + CVar$ + ") { DestroyArr((void **)" + CVar$ + "," + STR$(dms) + ", 1); " +  CVar$ + "=NULL; }"
      FPRINT Outfile,Scoot$,SOF$;"  ";STRING$(dms,42);CVar$;"=0;"
      CALL AddLocal(CVar$, vt, id,"",dms,0,0)
    ELSE
      IF Use_GenFree THEN
        GlobalDynaCnt++
        GlobalDynaStr$[GlobalDynaCnt] = "if (" + CVar$ + ") { DestroyArr((void **)" + CVar$ + "," + STR$(dms) + ", 1); " +  CVar$ + "=NULL; }"
      END IF
      CALL AddGlobal(CVar$, vt, id,"",dms,0,0,0)
    END IF
    IF NOT InTypeDef THEN
      FPRINT Outfile,Scoot$,CVar$ ; "= ("; SOF$ ;STRING$(dms,42);")CreateArr ("; CVar$ ; ",sizeof(";SOF$;"),0,";TRIM$(STR$(dms));"," ; ZZ$ ; ");"
    END IF
    '***********************
    CASE "redim"
    '***********************
    'REDIM b$ * 14
    'REDIM PRESERVE b$ * 20
    'REDIM a$[10]
    'REDIM PRESERVE a$[20]
    '***********************
    DIM RAW IsPreserve
    DIM RAW SOF$
    DIM RAW VI AS VarInfo PTR
    DIM RAW vt1 = 0
    DIM RAW IsSplat = 0
    DIM RAW BC = 0
    DIM RAW StartPoint
    DIM RAW AsPos = Ndx
    CALL HandleNonsense
    IsPreserve  = iMatchWrd(Stk$[2], "preserve")
    StartPoint  = 2 + IsPreserve
    vt1     = DataType(Stk$[StartPoint])
    CVar$   = Clean$(Stk$[StartPoint])
    IsSplat = iMatchWrd(Stk$[StartPoint + 1], "*")
    CALL ValidVar(CVar$)
    FOR i = Ndx TO 1 STEP -1
      IF iMatchWrd(Stk$[AsPos], "as") THEN
        AsPos = i - 1
        EXIT FOR
      END IF
    NEXT
    DIM RAW L = AsPos, SP = 0
    WHILE L > StartPoint
      IF Stk$[L] = "[" THEN
        DECR BC
      ELSEIF Stk$[L] = "]" THEN
        INCR BC
        IF BC = 1 THEN DECR L : ITERATE
      END IF
      IF BC = 0 THEN
        INCR SP
        IF Stk$[L-1] <> "]" THEN EXIT WHILE
        ZZ$ = "," + ZZ$
      ELSE
        ZZ$ = Stk$[L] + ZZ$
      END IF
      DECR L
    WEND
    'get info
    vt = CheckLocal(CVar$, &id)
    IF vt = vt_UNKNOWN THEN
      vt = CheckGlobal(CVar$, &id)
      IF vt = vt_UNKNOWN THEN
        Abort("Can not REDIM " + CVar$ + " not previously dimensioned")
      END IF
      VI = &GlobalVars[id]
    ELSE
      VI = &LocalVars[id]
    END IF
    dms = VI->VarPntr
    IF vt = vt_STRUCT OR vt = vt_UDT OR vt = vt_UNION THEN 'added vt_UNION 4.40
      SOF$ = GetElement$( StartPoint, &vt, &dms, VI->VarDef)
      i = Ndx
      Ndx = L-1
      CALL AsmUnknownStructs(1)
      Ndx = i
      CALL RemEmptyTokens
      CVar$   = Clean$(Stk$[StartPoint])
      IsSplat = iMatchWrd(Stk$[StartPoint + 1], "*")
    ELSE
      SOF$ = GetVarTypeName$(vt)
    END IF
    IF iMatchWrd(Stk$[Ndx-1], "as") THEN
      IF SOF$ <> Stk$[Ndx] AND NOT iMatchWrd(Stk$[Ndx], "string") THEN
        Abort("Can not change types for variable " + CVar$ + " previously defined as " + SOF$ + " on line" + STR$(VI->VarLine))
      END IF
      IF iMatchWrd(Stk$[Ndx], "string") THEN
        Ndx--
        Stk$[Ndx] = "["
        Stk$[++Ndx] = "65535"
        Stk$[++Ndx] = "]"
      ELSE
        Ndx -= 2
      END IF
    ELSE
      IF (vt = vt_CHAR AND vt1 = vt_STRVAR AND IsSplat = 0) OR vt = vt_CHARPTR THEN
        Ndx++
        Stk$[Ndx] = "["
        Stk$[++Ndx] = "65535"
        Stk$[++Ndx] = "]"
      END IF
    END IF
    IF Stk$[3 + IsPreserve] = "[" THEN
      IF IsPreserve THEN
        StartPoint = 4
      ELSE
        FPRINT Outfile,Scoot$, "if (" + CVar$ + ") { DestroyArr((void **)" + CVar$ + "," + STR$(dms) + ", 1); " +  CVar$ + "=NULL; }"
        StartPoint = 3
      END IF
      Use_DynamicA =TRUE
      A = 0
      ZZ$ = ""
      FOR i = StartPoint TO Ndx
        IF Stk$[i] = "[" THEN
          A++
          i++
          BC = 1
          WHILE BC > 0
            IF Stk$[i] = "[" THEN
              BC++
              CONCAT(ZZ$, Stk$[i])
            ELSE
              IF Stk$[i] = "]" THEN
                BC--
                IF BC = 0 AND i < Ndx THEN
                  CONCAT(ZZ$, ",")
                END IF
                IF BC THEN
                  CONCAT(ZZ$, Stk$[i])
                END IF
              ELSE
                CONCAT(ZZ$, Stk$[i])
              END IF
            END IF
            i++
          WEND
          i--
        END IF
      NEXT
      ZZ$ = Clean$(ZZ$)
      IF vt = vt_STRLIT OR vt = vt_DECFUNC OR vt = vt_NUMBER OR _
        (vt = vt_VOID AND INCHR(Stk$[Ndx],"*") = 0) THEN
        Abort(Stk$[Ndx] + " is not a valid type")
      END IF
      IF vt = vt_STRVAR THEN
        SOF$ = "char"
        A++
        CONCAT(ZZ$,",65535")
      END IF
      IF A <> dms THEN
        Abort("Mismatch in dimensions for " + CVar$ + ", orignally " + STR$(dms) + " found " + STR$(A))
      END IF
      FPRINT Outfile,Scoot$,CVar$ ; "= ("; SOF$ ;STRING$(dms,42);")CreateArr ("; CVar$ ; ",sizeof(";SOF$;"),";TRIM$(STR$(IsPreserve));",";dms;"," ; ZZ$ ; ");"
      EXIT SELECT
    END IF
    IF Stk$[3]= "*" OR (IsPreserve AND Stk$[4]= "*") THEN ' DIM MySTRING$ * NumBytes
      IF IsPreserve THEN
        FPRINT Outfile,Scoot$ ; CVar$ ; "=(char*)realloc(";CVar$;",256+";
        i = 5
      ELSE
        FPRINT Outfile,Scoot$ ; "free(" ; CVar$ ; ");"
        FPRINT Outfile,Scoot$ ; CVar$ ; "=(char*)calloc(256+";
        i = 4
      END IF
      FOR A = i TO Ndx
        FPRINT Outfile,Clean$(Stk$[A]);
      NEXT
      IF IsPreserve THEN
        FPRINT Outfile,");"
      ELSE
        FPRINT Outfile,",1);"
      END IF
      EXIT SELECT
    END IF
    Abort("Invalid REDIM statement")

    '*********************************************************
    CASE "dim", "local", "raw", "static", "auto", "register"
    '********************************************************
    ' DIM A$ * blah blah blah
    ' DIM a%[1000]  (integer)
    ' DIM a![1000]  (single)
    ' DIM a#[1000]  (double)
    ' DIM a¦[1000]  (long double)
    ' DIM A$[1000]  (string)
    ' DIM r             AS DATA_TYPE
    ' DIM r[1][2]...[n] AS DATA_TYPE
    ' DIM DYNAMIC A$[1000]
    ' DIM a AS CONST CHAR PTR
    '********************************************************
    DIM RAW w = 0
    DIM RAW UseStatic$
    DIM RAW IsVolatile = 0
    DIM RAW IV$

    IsVolatile = iMatchWrd(Stk$[2],"volatile")
    IF IsVolatile THEN
      IV$ = "volatile "
    ELSE
      IV$ = ""
    END IF
    IsSubOrFuncPtr = SubFuncTest()
    CALL HandleNonsense
    IF Stk$[Ndx] = "*" THEN CALL PointerFix
    IF Stk$[Ndx] = "&" THEN Stk$[Ndx--] = "" : CONCAT(Stk$[Ndx], "&")
    IsRegister = IsAuto = IsDim = IsLocal = IsStatic = IsRaw = FALSE
    Cmd$ = LCASE$(Stk$[1])

    SELECT CASE Cmd$
      CASE "dim"      : IsDim      = TRUE
      CASE "local"    : IsLocal    = TRUE
      CASE "static"   : IsStatic   = TRUE
      CASE "raw"      : IsRaw      = TRUE
      CASE "auto"     : IsAuto     = TRUE
      CASE "register" : IsRegister = TRUE
    END SELECT

    '/***** 2010-11-15 Added support for public/protected/constructor/destructor in Classes -AIR
    IF InTypeDef THEN
      IF iMatchWrd(Stk$[2], "public") OR iMatchWrd(Stk$[2], "private") OR iMatchWrd(Stk$[2], "protected") THEN
        FPRINT Outfile, LF$;LCASE$(Stk$[2]);":"
        EXIT SELECT
      ELSEIF iMatchWrd(Stk$[2], "constructor") OR iMatchWrd(Stk$[2], "destructor") THEN
        'ADD SUPPORT HERE FOR PARSING METHOD PARAMETERS
        CALL DimSubFunc(0)
        EXIT SELECT
        '/***** 2010-12-01  -AIR *****/
      ELSEIF iMatchWrd(Stk$[2], "virtual") THEN
        vproc$ = ""
        IF iMatchWrd(Stk$[Ndx-1],"=") and iMatchWrd(Stk$[Ndx], "0") THEN
          ' Store the "=0"
          vproc$ = Stk$[Ndx-1] + Stk$[Ndx]
          '~ change Ndx to strip off "=0"
          Ndx = Ndx-2
        END IF
        '~ STRIP OUT "VIRTUAL" AND LEFT SHIFT ENTIRE SOURCE
        FOR integer act = 3 TO Ndx
          Stk$[act-1] = Stk$[act]
        NEXT

        Ndx--

        CALL DimSubFunc(0)

        EXIT SELECT
      END IF
    END IF
    '*************************************************************************
    IF IsSubOrFuncPtr THEN
      IF IsVolatile THEN Abort("volatile SUB/FUNCTION pointers not supported")
      IF DimSubFunc(0) THEN EXIT SELECT
    END IF
    '*************************************************************************
    CVar$ = Clean$(Stk$[2+IsVolatile])
    CALL ValidVar(CVar$)
    VType = DataType(Stk$[2+IsVolatile])
    '***********************************************************************
    IF Stk$[3+IsVolatile] = "*" THEN ' DIM MySTRING$ * NumBytes
      IF IsVolatile THEN Abort("volatile dynamic strings not supported")
      CALL DimDynaString(CVar$, 0, 0)
      EXIT SELECT
    END IF

    RAW iASoffset = 0
    RAW sConst$
    RAW iIsConst

    IF iMatchWrd(Stk$[Ndx-1],"as") THEN iASoffset = Ndx-1
    IF iMatchWrd(Stk$[Ndx-2],"as") THEN iASoffset = Ndx-2


    IF iASoffset THEN

      iIsConst = 0
      sConst$ = ""
      IF iASoffset = Ndx-2 THEN
        IF iMatchWrd(Stk$[Ndx-1],"const") THEN
          sConst$ = "const"
          iIsConst = 1
        END IF
      END IF

      Var1$ = CVar$
      IsPointer = TALLY(Stk$[Ndx],"*")
      DimType$ = ""
      lszTmp$  = ""

      FOR i = 2+IsVolatile TO iASoffset-1
        CONCAT(lszTmp$, Stk$[i])
        IF i > 2+IsVolatile THEN CONCAT(DimType$, Stk$[i])
      NEXT
      Var$ = REMOVE$(Stk$[Ndx],"*")
      GetTypeInfo(Var$, &w, &id, &vt)
      IF vt = vt_STRVAR THEN
        Stk$[Ndx] = "char"
        Var$ = Stk$[Ndx]
        CONCAT(DimType$, "[65535]")
        CONCAT(lszTmp$, "[65535]")
      END IF
      IF InFunc OR InTypeDef THEN
        IF IsRegister OR IsAuto THEN
          IF IsRegister THEN
            IF IsVolatile THEN Abort("Register volatile not supported")
            IF vt = vt_FILEPTR THEN
              FPRINT Outfile,Scoot$,"register  FILE*   ";
            ELSE
              FPRINT Outfile,Scoot$,"register  ";sConst$;" ";Stk$[Ndx];"  ";
            END IF
          ELSE
            IF vt = vt_FILEPTR THEN
              FPRINT Outfile,Scoot$,"auto ";IV$;"  FILE*   ";
            ELSE
              FPRINT Outfile,Scoot$,"auto ";IV$;" ";sConst$;" ";Stk$[Ndx];"  ";
            END IF
          END IF
        ELSE
          IF IsRaw = TRUE THEN
            IF vt = vt_FILEPTR THEN
              FPRINT Outfile,Scoot$,"static ";IV$;"  FILE*   ";
            ELSE
              FPRINT Outfile,Scoot$,IV$;sConst$;" ";Stk$[Ndx];"  ";
            END IF
          ELSE
            IF InTypeDef THEN
              UseStatic$ = ""
            ELSE
              UseStatic$ = "static  "
            END IF
            IF vt = vt_STRUCT THEN
              FPRINT Outfile,Scoot$,UseStatic$;IV$;sConst$;" ";"struct _" ; Stk$[Ndx]; "  ";
            ELSE
              IF vt = vt_FILEPTR THEN
                FPRINT Outfile,Scoot$,UseStatic$;IV$;"FILE   *";
              ELSE
                FPRINT Outfile,Scoot$,UseStatic$;IV$;sConst$;" ";Stk$[Ndx] ; "  ";
              END IF
            END IF
            IF InTypeDef THEN
              CALL AddTypedefElement(BaseTypeDefsCnt[InTypeDef], vt, CVar$, Var$, 0)
            END IF
          END IF
        END IF

        IF InFunc AND NOT InTypeDef THEN
          CALL AddLocal(Var1$, vt, id, DimType$, IsPointer,0,0,iIsConst)
        END IF

        FPRINT Outfile,Clean$(lszTmp$); ";"
        IF NOT InTypeDef AND NOT IsStatic AND NOT IsRaw AND NOT IsRegister AND NOT IsVolatile THEN
          T$ = Clean$(EXTRACT$(lszTmp$,"["))
          IF IsPointer THEN
            FPRINT Outfile,Scoot$,"memset(&";T$;",0,sizeof(";Clean$(Var$) + " *";"));"
          ELSE
            FPRINT Outfile,Scoot$,"memset(&";T$;",0,sizeof(";T$;"));"
          END IF
        END IF
      ELSE
        IF IsVolatile THEN
          CALL AddGlobal(Var1$, vt, id, DimType$,IsPointer,0,3,0,iIsConst)
        ELSE
          CALL AddGlobal(Var1$, vt, id, DimType$,IsPointer,0,0,0,iIsConst)
        END IF
      END IF
      EXIT SELECT
    END IF
    '*************************************************************************
    IF InFunc OR InTypeDef THEN
      lszTmp$ = ""
      IF iMatchWrd(Stk$[3+IsVolatile],"as") THEN
        VType = CheckType(Stk$[4+IsVolatile])
        IF VType = vt_CHAR THEN
          IF Stk$[5] = "*" THEN
            lszTmp$ = "[" + Stk$[6+IsVolatile] + "]"
          END IF
        END IF
      ELSE
        FOR i = 3+IsVolatile TO Ndx
          CONCAT (lszTmp$, Stk$[i])
        NEXT
        lszTmp$ = LTRIM$(Clean$(lszTmp$))
        IF VType = vt_STRVAR THEN 'AND ((Stk$[3+IsVolatile] = "" AND InTypeDef) OR (NOT InTypeDef)) THEN
          'print lszTmp$
          IF lszTmp$ <> "[65535]" THEN CONCAT (lszTmp$, "[2048]")
          'print lszTmp$
        END IF
      END IF
      j = (NOT InTypeDef AND NOT IsStatic AND NOT IsRaw AND NOT IsRegister)
      IF j THEN
        T$ = Clean$(EXTRACT$(CVar$,"["))
      END IF

      SELECT CASE VType
        CASE vt_STRVAR
          IF IsRaw THEN
            FPRINT Outfile,Scoot$;IV$;"char ";CVar$;lszTmp$;";"
          ELSEIF IsAuto THEN
            FPRINT Outfile,Scoot$;"auto ";IV$;"char ";CVar$;lszTmp$;";"
          ELSEIF IsRegister THEN
            IF IsVolatile THEN Abort("register volatile not supported")
            FPRINT Outfile,Scoot$;"register char ";CVar$;lszTmp$;";"
          ELSE
            IF InTypeDef THEN
              FPRINT Outfile,Scoot$;IV$;"char ";CVar$;lszTmp$;";"
            ELSE
              FPRINT Outfile,Scoot$;"static ";IV$;"char ";CVar$;lszTmp$;";"
            END IF
          END IF

          IF j AND NOT IsVolatile THEN
            FPRINT Outfile,Scoot$;"memset(&";T$;",0,sizeof(";T$;"));"
          END IF

        CASE vt_VarMin TO vt_VarMax
          ZZ$ = GetVarTypeName$(VType)
          ZZ$ = RPAD$(ZZ$, 7)
          IF IsRaw THEN
            FPRINT Outfile,Scoot$;IV$;ZZ$;" ";CVar$;lszTmp$;";"
          ELSEIF IsAuto THEN
            FPRINT Outfile,Scoot$;"auto ";IV$;ZZ$;" ";CVar$;lszTmp$;";"
          ELSEIF IsRegister THEN
            IF IsVolatile THEN Abort("Regester volatile not supported")
            FPRINT Outfile,Scoot$;"register ";ZZ$;" ";CVar$;lszTmp$;";"
          ELSE
            IF InTypeDef THEN
              FPRINT Outfile,Scoot$;IV$;ZZ$;" ";CVar$;lszTmp$;";"
            ELSE
              FPRINT Outfile,Scoot$;"static ";IV$;ZZ$;" ";CVar$;lszTmp$;";"
            END IF
          END IF
          IF j AND NOT IsVolatile THEN
            FPRINT Outfile,Scoot$;"memset(&";T$;",0,sizeof(";T$;"));"
          END IF
        END SELECT

        IF InFunc AND NOT InTypeDef THEN
          CALL AddLocal(CVar$, VType, 0, lszTmp$,0,0,0)
        END IF
        IF InTypeDef THEN
          CALL AddTypedefElement(BaseTypeDefsCnt[InTypeDef], VType, CVar$, Var$, 0)
        END IF
        EXIT SELECT
    END IF
    '************************************************************************
    lszTmp$ = "" ' if we get here, we're creating with a GLOBAL variable
    '************************************************************************

    FOR i = 3+IsVolatile TO Ndx
      CONCAT (lszTmp$, Stk$[i])
    NEXT
    IF VType = vt_STRVAR AND lszTmp$ <> "" THEN
      CONCAT (lszTmp$, "[65535]")
    END IF
    IF IsVolatile THEN
      CALL AddGlobal(CVar$, VType, 0,lszTmp$,0,0,3,0)
    ELSE
      CALL AddGlobal(CVar$, VType, 0,lszTmp$,0,0,0,0)
    END IF
    '***********************
    CASE "extern"
    '***********************
    DIM RAW IsVolatile
    IsSubOrFuncPtr = SubFuncTest()
    CALL HandleNonsense
    IsVolatile = iMatchWrd(Stk$[2],"volatile")
    CVar$ = Clean$(Stk$[2+IsVolatile])
    CALL ValidVar(CVar$)
    IF Stk$[Ndx] = "*" THEN CALL PointerFix
    IF Stk$[Ndx] = "&" THEN Stk$[Ndx--] = "" : CONCAT(Stk$[Ndx], "&")
    IF Stk$[3+IsVolatile] = "*" THEN
      IF IsVolatile THEN Abort("volatile dynamic strings not supported")
      CALL DimDynaString(CVar$, 2, 0)
      EXIT SELECT
    END IF
    IF IsSubOrFuncPtr THEN
      IF IsVolatile THEN Abort("volatile SUB/FUNCTION pointers not supported")
      IF DimSubFunc(0) THEN EXIT SELECT
    END IF
    Var$ = Clean$(Stk$[2+IsVolatile])
    CALL ValidVar(Var$)
    IsPointer = 0
    DimType$  = ""
    IF iMatchWrd(Stk$[Ndx-1],"as") THEN
      GetTypeInfo(Stk$[Ndx], &IsPointer, &id, &vt)
      Stk$[Ndx] = REMOVE$(Stk$[Ndx],"*")
      FOR i = 3+IsVolatile TO Ndx-2
        CONCAT (DimType$, Stk$[i])
      NEXT
    ELSE
      i = 3+IsVolatile
      WHILE i <= Ndx
        CONCAT(DimType$,Stk$[i])
        i++
      WEND
      vt = DataType(Stk$[2+IsVolatile])
      id = 0
    END IF
    IF vt = vt_STRVAR THEN '  AND DimType$ <> "" THEN
      CONCAT (DimType$, "[65535]")
    END IF
    IF IsVolatile THEN
      CALL AddGlobal(Var$, vt, id, DimType$, IsPointer,0,4,0)
    ELSE
      CALL AddGlobal(Var$, vt, id, DimType$, IsPointer,0,1,0)
    END IF
    '*************************
    CASE "shared", "global"
    '*************************
    DIM RAW w = 0
    DIM RAW SOF$
    DIM RAW IsShared
    DIM RAW IsVolatile
    IsSubOrFuncPtr = SubFuncTest()
    CALL HandleNonsense
    IsVolatile = iMatchWrd(Stk$[2],"volatile")
    CVar$ = Clean$(Stk$[2+IsVolatile])
    CALL ValidVar(CVar$)
    IsShared = iMatchWrd(Stk$[1],"shared")
    IF Stk$[Ndx] = "*" THEN CALL PointerFix
    IF Stk$[Ndx] = "&" THEN Stk$[Ndx--] = "" : CONCAT(Stk$[Ndx], "&")
    IF Stk$[3+IsVolatile] = "*" THEN
      IF IsVolatile THEN Abort("volatile dynamic strings not supported")
      CALL DimDynaString(CVar$, 1, IsShared)
      EXIT SELECT
    END IF
    IF IsSubOrFuncPtr THEN
      IF IsVolatile THEN Abort("volatile SUB/FUNCTION pointers not supported")
      CALL DimSubFunc(0)
      EXIT SELECT
    END IF
    IF iMatchWrd(Stk$[2],"dynamic") THEN
      CVar$ = Clean$(Stk$[3])
      CALL ValidVar(CVar$)
      IF iMatchWrd(Stk$[Ndx-1],"as") THEN
        SOF$ = Stk$[Ndx]
        GetTypeInfo(SOF$, &w, &id, &vt)
        IF vt = vt_STRLIT OR _
          vt = vt_DECFUNC OR _
          vt = vt_NUMBER OR _
          (vt = vt_VOID AND INCHR(Stk$[Ndx],"*") = 0) THEN
          Abort(Stk$[Ndx] + " is not a valid type")
        END IF
        Ndx -= 2
      ELSE
        vt = DataType(Stk$[3])
        id = 0
        SOF$ = GetVarTypeName$(vt)
      END IF
      Use_DynamicA = TRUE
      ZZ$ = ""
      FOR i = 4 TO Ndx
        CONCAT(ZZ$, Stk$[i])
      NEXT
      dms = TALLY(ZZ$,"][") + 1
      IF dms > 1 THEN REPLACE "][" WITH "," IN ZZ$
      ZZ$ = Clean$(ZZ$)
      RemoveAll(ZZ$,"[]")
      IF vt = vt_STRVAR THEN
        vt = vt_CHAR
        SOF$ = "char"
        dms++
        CONCAT(ZZ$,",65535")
      END IF
      IF Use_GenFree THEN
        GlobalDynaCnt++
        GlobalDynaStr$[GlobalDynaCnt] = "if (" + CVar$ + ") { DestroyArr((void **)" + CVar$ + "," + STR$(dms) + ", 1); " +  CVar$ + "=NULL; }"
      END IF
      CALL AddGlobal(CVar$, vt, id,"",dms,0,0,0)
      FPRINT Outfile,Scoot$,CVar$ ; "= ("; SOF$ ;STRING$(dms,42);")CreateArr ("; CVar$ ; ",sizeof(";SOF$;"),0,";TRIM$(STR$(dms));"," ; ZZ$ ; ");"
      EXIT SELECT
    END IF
    IsPointer = 0
    Var$ = Clean$(Stk$[2+IsVolatile])
    CALL ValidVar(Var$)
    IF iMatchWrd(Stk$[Ndx-1],"as") THEN
      IF INCHR(Stk$[Ndx],"*") THEN
        IsPointer = TALLY(Stk$[Ndx],"*")
        Stk$[Ndx] = REMOVE$(Stk$[Ndx],"*")
      END IF
      DimType$ = ""
      FOR i = 3+IsVolatile TO Ndx-2
        CONCAT (DimType$, Stk$[i])
      NEXT
      GetTypeInfo(Stk$[Ndx], &w, &id, &vt)
    ELSE
      DimType$ = ""
      i = 3+IsVolatile
      WHILE i <= Ndx
        CONCAT(DimType$,Stk$[i])
        i++
      WEND
      vt = DataType(Stk$[2+IsVolatile])
      id = 0
    END IF
    IF vt = vt_STRVAR THEN
      CONCAT (DimType$, "[65535]")
    END IF
    IF IsShared THEN
      IF IsVolatile THEN
        CALL AddGlobal(Var$, vt, id, DimType$, IsPointer,0,5,0)
      ELSE
        CALL AddGlobal(Var$, vt, id, DimType$, IsPointer,0,2,0)
      END IF
    ELSE
      IF IsVolatile THEN
        CALL AddGlobal(Var$, vt, id, DimType$, IsPointer,0,3,0)
      ELSE
        CALL AddGlobal(Var$, vt, id, DimType$, IsPointer,0,0,0)
      END IF
    END IF
    '*********************************************************************
    CASE "while"
    CALL EmitIfCond("while")
    '***********************
    CASE "wend", "endwhile"
    '***********************
    CALL BumpDown
    FPRINT Outfile,Scoot$,"}"
    CALL BumpDown
    '***********************
    CASE "exit"
    '***********************
    IF CaseFlag THEN NoBreak2 = TRUE
    IF iMatchWrd(Stk$[2],"sub") THEN
      '*************************
      ' Clean up dynamic strings
      '*************************
      IF LocalDynaCnt <> 0 THEN
        FOR j = 1 TO LocalDynaCnt
          FPRINT Outfile,Scoot$,DynaStr$[j]
        NEXT
      END IF
      '*********************************
      ' Clean up dynamic strings arrays
      '*********************************
      IF LocalDynArrCount <> 0 THEN
        FOR i = 1 TO LocalDynArrCount
          FPRINT Outfile,Scoot$, LocalDynArrName$[i]
        NEXT
      END IF
      '*********************************
      FPRINT Outfile,Scoot$,"return;"
      EXIT SELECT
    END IF
    IF iMatchWrd(Stk$[2],"function") THEN
      '*************************
      ' Clean up dynamic strings
      '*************************
      IF LocalDynaCnt <> 0 THEN
        FOR j = 1 TO LocalDynaCnt
          FPRINT Outfile,Scoot$,DynaStr$[j]
        NEXT
      END IF
      '*********************************
      ' Clean up dynamic strings arrays
      '*********************************
      IF LocalDynArrCount <> 0 THEN
        FOR i = 1 TO LocalDynArrCount
          FPRINT Outfile,Scoot$, LocalDynArrName$[i]
        NEXT
      END IF
      '*********************************
      FPRINT Outfile,Scoot$,"return 0;"
    ELSE
      FPRINT Outfile,Scoot$,"break;"
    END IF
    '***********************
    CASE "goto"
    '***********************
    IF CaseFlag THEN NoBreak2 = TRUE
    FPRINT Outfile,Scoot$,"goto ";UCASE$(Stk$[2]);";"
    '***********************
    CASE "print"
    '***********************
    FPRINT Outfile,Scoot$, PrintWriteFormat$(0)
    '***********************
    CASE "write"
    '***********************
    FPRINT Outfile,Scoot$,PrintWriteFormat$(1)
    '***********************
    CASE "run"
    '***********************
    FPRINT Outfile,Scoot$,"Run (";
    FOR A = 2 TO Ndx
      FPRINT Outfile,Clean$(Stk$[A]);
    NEXT
    FPRINT Outfile,Scoot$,");"
    '***********************
    CASE "color"
    '***********************
    FPRINT Outfile,Scoot$,"color (";
    FOR A = 2 TO Ndx
      FPRINT Outfile,Clean$(Stk$[A]);
    NEXT
    FPRINT Outfile,");"
    '***********************
    CASE "locate"
    '***********************
    FPRINT Outfile,Scoot$,"locate (";
    FOR A = 2 TO Ndx
      FPRINT Outfile,Clean$(Stk$[A]);
    NEXT
    FPRINT Outfile,");"
    '***********************
    CASE "cls"
    '***********************
    FPRINT Outfile,Scoot$,"cls();"
    '**********************************************************************
    CASE ELSE
    '**********************************************************************
    ' "="   We MUST be processing an assignment statement if we get here!
    '       or perhaps calling a SUB without using the CALL keyword
    '**********************************************************************
    FOR B = 1 TO Ndx
      IF Stk$[B]= "=" THEN EXIT FOR
    NEXT
    '*************************************************************************
    'There's no "=" so we're either calling a SUB or this is a FUNCTION RETURN
    '*************************************************************************
    IF B-1 = Ndx THEN
      lszTmp$ = ""
      FOR Tmp = 1 TO Ndx
        CONCAT(lszTmp$, Clean$(Stk$[Tmp]))
      NEXT
      CONCAT(lszTmp$, ";")
      IF FuncRetnFlag = 2 THEN
        FPRINT Outfile,lszTmp$
      ELSE
        FPRINT Outfile,Scoot$,lszTmp$
      END IF
      IF FuncRetnFlag = 2 THEN
        FuncRetnFlag = 0
        Stk$[1] = ""
        EXIT SUB
      END IF
      EXIT SELECT
    END IF
    '*************************************************************************
    '      It can only be one thing now -- a normal assignment statement
    '*************************************************************************
    FOR i = 2 TO B-1
      CONCAT(Stk$[1], Stk$[i]) ' IF present, build the Array Variable
    NEXT
    A = INCHR(Stk$[1], "*")
    IF A THEN
      IF NOT ( INCHR(Stk$[1], "$") AND A > 1 ) THEN 'Exclude strings BYREF
        RemoveAll(Stk$[1], "$")
        GOTO ProcessNumeric
      END IF
    END IF
    '*************************************************************************
    '                    'processing a string equation
    '*************************************************************************
    LOCAL strtest, varid, vi AS VarInfo PTR, vr$, brcnt
    strtest = DataType(Stk$[1])
    IF strtest = vt_INTEGER THEN
      brcnt = TALLY(Stk$[1], "[")
      vr$ = EXTRACT$(Stk$[1], "[")
      strtest = CheckLocal(vr$, &varid)
      IF strtest = vt_UNKNOWN THEN
        strtest = CheckGlobal(vr$, &varid)
        vi = &(GlobalVars[varid])
      ELSE
        vi = &(LocalVars[varid])
      END IF
      IF strtest = vt_CHAR THEN
        strtest = vt_STRVAR
      END IF
      IF strtest = vt_STRVAR THEN
        IF vi->VarPntr <> 0 THEN
          ' string pointer
          GOTO ProcessNumeric
        END IF
        IF TALLY(vi->VarDim,"[") = brcnt THEN
          ' the character within string
          GOTO ProcessNumeric
        END IF
        IF TALLY(vi->VarDim,"[") <> brcnt+1 THEN
          ' string pointer
          GOTO ProcessNumeric
        END IF
      END IF
    END IF
    IF strtest = vt_STRVAR THEN
      '*************************************************************************
      IF B+1 = Ndx THEN
        IF Stk$[Ndx] = DDQ$ THEN
          FPRINT Outfile,Scoot$,"*",Clean$(Stk$[1]),"=0;"
          GOTO StringExit
        END IF
      END IF
      ' [ Speed up No. 1 ] ****************************************************
      IF Ndx = 3 THEN
        Stk$[1]=Clean$(Stk$[1])
        Stk$[3]=Clean$(Stk$[3])
        IF Stk$[1] = "BCX_RetStr" THEN
          FPRINT Outfile,Scoot$,"BCX_RetStr=BCX_TmpStr(strlen(" ; Stk$[3] ; "));"
        END IF
        FPRINT Outfile,Scoot$,"strcpy(", Stk$[1], ",", Stk$[3], ");"
        GOTO StringExit
      END IF
      '***********************
      Arg$    = ""
      lszTmp$ = ""
      j=k=0
      '***********************
      IF iMatchLft(Stk$[3],"$$") THEN HasStorage = TRUE
      Var$ = Clean$(Stk$[1])
      IF Clean$(Stk$[B+1]) = Var$ THEN
        k = TRUE
      END IF
      FOR A = B+1 TO Ndx ' B marks the position of the "=" char
        IF Stk$[A]= "&" AND Stk$[A-1] <> "," AND Stk$[A-1] <> "(" THEN
          INCR j
          Arg$ = Arg$ + lszTmp$
          lszTmp$ = ","
        ELSE
          CONCAT(lszTmp$, Clean$(Stk$[A]))
        END IF
      NEXT
      IF *lszTmp <> 0 AND lszTmp$ <> "," THEN
        Arg$ = Arg$ + lszTmp$
      END IF
      '*************************************************************************
      '                                 Rules
      '*************************************************************************
      ' IF j = 0 & K = ANY                     THEN use strcpy
      ' IF j = 1 & K = TRUE                    THEN use strcat
      ' All else                               THEN use join
      '*************************************************************************
      RemoveAll(Var$, SPC$) 'Added this during the beta testing
      '*** needs to be checked out still ***
      'stk[++i] is getting here as stk [ + + i ]
      IF j = 0 THEN
        IF Var$ = "BCX_RetStr" THEN
          IF HasStorage THEN
            FPRINT Outfile,Scoot$,"BCX_RetStr=", Arg$, ";"
            GOTO StringExit
          ELSE
            FPRINT Outfile,Scoot$,"BCX_RetStr=BCX_TmpStr(strlen(" , Arg$ , "));"
          END IF
        END IF
        FPRINT Outfile,Scoot$,"strcpy(", Var$ , "," , Arg$, ");"
        GOTO StringExit
      END IF
      'If we make it here then we should have 2 or more expressions
      IF k = TRUE AND j = 1 THEN
        FPRINT Outfile,Scoot$,"strcat(", Arg$ , ");"
        GOTO StringExit
      END IF
      lszTmp$ = LTRIM$(STR$(++j))
      Use_Join = TRUE
      IF Var$ = "BCX_RetStr" THEN
        FPRINT Outfile,Scoot$,"BCX_RetStr=join(" , lszTmp$ , "," , Arg$, ");"
      ELSE
        FPRINT Outfile,Scoot$,"strcpy(",Var$, ", join(" , lszTmp$ , "," , Arg$, "));"
      END IF
      StringExit:
      EXIT SELECT
      '***********************
    ELSE
      '***********************
      ProcessNumeric:
      '***********************
      FOR i = 2 TO B
        Stk$[i] = ""
      NEXT
      Stk$[B]= "=" 'This is necessary
      ' change x = x ? c to x ?= c
      IF Stk$[B + 1] = Stk$[1] AND Ndx = 5 THEN
        IF Inset(Stk$[B + 2], "+-*/") AND Stk$[B + 3] <> ">" THEN
          Stk$[B] = Stk$[B + 2] + Stk$[B]
          Stk$[B + 1] = ""
          Stk$[B + 2] = ""
        END IF
      END IF
      FPRINT Outfile,Scoot$,Clean$(Stk$[1]);
      FOR A = 2 TO Ndx
        IF Stk$[A] = "!" THEN
          FPRINT Outfile,"!";
        ELSE
          FPRINT Outfile,Clean$(Stk$[A]);
        END IF
      NEXT
      FPRINT Outfile,";"
    END IF
  END SELECT
  IF FuncRetnFlag = 1 THEN
    IF LocalDynaCnt <> 0 THEN
      FOR j = 1 TO LocalDynaCnt
        FPRINT Outfile,Scoot$,DynaStr$[j]
      NEXT
    END IF
    '******************************************************************
    FPRINT Outfile,Scoot$,"return BCX_RetStr;" ' $ FUNCTION Return
    '******************************************************************
  END IF
END SUB ' Emit
SUB Abort(Z$)
  DIM RAW i = 0
  DIM RAW j = 0
  DIM RAW k = 0
  DIM RAW varnum = 0
  DIM RAW t$
  DIM RAW frmt$
  WarnMsg$ = ""
  IF LEFT$(AbortSrc$,11) = "$BCXVERSION" THEN
    CONCAT(WarnMsg$,Z$)
  ELSE
    WarnMsg$ = WarnMsg$ + Z$ + " at line" + STR$(ModuleLineNos[ModuleNdx]) + " in Module: " + TRIM$(Modules$[ModuleNdx]) + CRLF$
    WarnMsg$ = WarnMsg$ + "Original line" + CRLF$
    WarnMsg$ = WarnMsg$ +  AbortSrc$ + CRLF$
    WarnMsg$ = WarnMsg$ + "==============" + CRLF$
    WarnMsg$ = WarnMsg$ + "Current Tokens" + CRLF$
    WarnMsg$ = WarnMsg$ + "==============" + CRLF$
    FOR k = 1 TO Ndx
      j = LEN(Stk$[k])
      IF j < 40 THEN
        j = 40 - j
      ELSE
        j = 8 - IMOD(j,8)
      END IF
      frmt$ = LPAD$(STR$(k),3)
      WarnMsg$ = WarnMsg$ + frmt$ + " " + Stk$[k] + STRING$(j,32) + CRLF$
      t$ = Clean$(Stk$[k])
      i = CheckLocal(t$, &varnum)
      IF i <> vt_UNKNOWN THEN
        WarnMsg$ = WarnMsg$ + "is a LOCAL defined at line" + STR$(LocalVars[varnum].VarLine)
        WarnMsg$ = WarnMsg$ + " in Module: " + LocalVars[varnum].VarModule + CRLF$
      ELSE
        i = CheckGlobal(t$, &varnum)
        IF i <> vt_UNKNOWN THEN
          WarnMsg$ = WarnMsg$ + "is a GLOBAL defined at line" + STR$(GlobalVars[varnum].VarLine)
          WarnMsg$ = WarnMsg$ + " in Module: " + GlobalVars[varnum].VarModule + CRLF$
          WarnMsg$ = WarnMsg$ + " " + Stk$[k] & GlobalVars[varnum].VarDim$ + " as "
          IF GlobalVars[varnum].VarDef THEN
            WarnMsg$ = WarnMsg$ + TRIM$(TypeDefs[GlobalVars[varnum].VarDef].VarName$) + CRLF$
          ELSE
            WarnMsg$ = WarnMsg$ + TRIM$(GetVarTypeName$(GlobalVars[varnum].VarType)) + CRLF$
          END IF
        ELSE
          IF Stk[k][0] = 34 THEN
            WarnMsg$ = WarnMsg$ + "is a STRING LITERAL" + CRLF$
          END IF
        END IF
      END IF
    NEXT
    WarnMsg$ = WarnMsg$ + "===============" + CRLF$
    WarnMsg$ = WarnMsg$ + "Original Tokens" + CRLF$
    WarnMsg$ = WarnMsg$ + "===============" + CRLF$
    CALL XParse(AbortSrc$)
    FOR k = 1 TO Ndx
      j = LEN(Stk$[k])
      IF j < 40 THEN
        j = 40 - j
      ELSE
        j = 8 - IMOD(j,8)
      END IF
      frmt$ = LPAD$(STR$(k),3)
      WarnMsg$ = WarnMsg$ + frmt$ + " " + Stk$[k] + STRING$(j,32) + CRLF$
      t$ = Clean$(Stk$[k])
      i = CheckLocal(t$, &varnum)
      IF i <> vt_UNKNOWN THEN
        WarnMsg$ = WarnMsg$ + "is a LOCAL defined at line" + STR$(LocalVars[varnum].VarLine)
        WarnMsg$ = WarnMsg$ + " in Module: " + LocalVars[varnum].VarModule + CRLF$
      ELSE
        i = CheckGlobal(t$, &varnum)
        IF i <> vt_UNKNOWN THEN
          WarnMsg$ = WarnMsg$ + "is a GLOBAL defined at line" + STR$(GlobalVars[varnum].VarLine)
          WarnMsg$ = WarnMsg$ + " in Module: " + GlobalVars[varnum].VarModule + CRLF$
          WarnMsg$ = WarnMsg$ + " " + Stk$[k] & GlobalVars[varnum].VarDim$ + " as "
          IF GlobalVars[varnum].VarDef THEN
            WarnMsg$ = WarnMsg$ + TypeDefs[GlobalVars[varnum].VarDef].VarName$ + CRLF$
          ELSE
            WarnMsg$ = WarnMsg$ + GetVarTypeName$(GlobalVars[varnum].VarType) + CRLF$
          END IF
        ELSE
          IF Stk[k][0] = 34 THEN
            WarnMsg$ = WarnMsg$ + "is a string literal" + CRLF$
          END IF
        END IF
      END IF
    NEXT
  END IF
  WarnMsg$ = WarnMsg$ + CRLF$
  CALL CloseAll
  KILL ovrFile$
  KILL FileOut$
  KILL prcFile$
  KILL udtFile$
  KILL hdrFile$
  KILL cstFile$
  KILL datFile$
  KILL setFile$
  KILL enuFile$
  'KILL resFile$
  KILL "$t$e$m$p"
  IF ErrFile THEN
    OPEN FileErr$ FOR APPEND AS fpErr
    FPRINT fpErr, Z$ ; " at line" ; ModuleLineNos[ModuleNdx] ; " in Module: "; TRIM$(Modules$[ModuleNdx]) 'LinesRead
    CLOSE fpErr
  END IF
  PRINT "Error!",CRLF$, FileIn$,CRLF$, WarnMsg$
  CALL FREEGLOBALS
  END = 1
END SUB ' Abort
SUB BumpDown
  Indent--
  Indent--
  IF Indent<0 THEN Indent = 0
  Scoot$ = SPACE$(Indent)
END SUB ' BumpDown
SUB BumpUp
  IF Indent<0 THEN Indent = 0
  Indent++
  Indent++
  Scoot$ = SPACE$(Indent)
END SUB ' BumpUp
FUNCTION BraceCount( Arg$ )
  DIM RAW p AS CHAR PTR
  DIM RAW braces
  p = Arg$
  braces = 0
  WHILE *p
    IF *p = c_DblQt THEN
      p++
      WHILE *p <> c_DblQt
        IF *p = 0 THEN FUNCTION = braces
        p++
      WEND
    END IF
    IF *p = ASC("}") THEN braces--
    IF *p = ASC("{") THEN braces++
    p++
  WEND
  FUNCTION = braces
END FUNCTION ' BraceCount
FUNCTION BracketHandler(Src$,l) AS CHAR PTR
  DIM RAW s AS CHAR PTR
  s = Src$
  SELECT CASE l
    CASE 0
    DO
      IF *s = 0 THEN EXIT LOOP
      IF *s = c_DblQt THEN
        s++
        WHILE *s <> c_DblQt
          IF *s = 0 THEN EXIT LOOP
          s++
        WEND
      END IF
      IF *s = c_LtBkt THEN
        s++
        s = BracketHandler(s,1)
      END IF
      IF *s = c_LPar THEN
        s++
        s = BracketHandler(s,2)
      END IF
      s++
    LOOP
    CASE 1
    WHILE *s <> c_RtBkt
      IF *s = c_DblQt THEN
        s++
        WHILE *s <> c_DblQt
          IF *s = 0 THEN EXIT LOOP
          s++
        WEND
      END IF
      IF *s = c_LtBkt THEN
        s++
        s = BracketHandler(s, 1)
      END IF
      IF *s = c_LPar THEN
        s++
        s = BracketHandler(s, 2)
      END IF
      IF *s = c_Komma THEN *s = 1
      IF *s = 0 THEN EXIT LOOP
      s++
    WEND
    CASE 2
    WHILE *s <> c_RPar
      IF *s = c_DblQt THEN
        s++
        WHILE *s <> c_DblQt
          IF *s = 0 THEN EXIT LOOP
          s++
        WEND
      END IF
      IF *s = c_LtBkt THEN
        s++
        s = BracketHandler(s, 1)
      END IF
      IF *s = c_LPar THEN
        s++
        s = BracketHandler(s, 2)
      END IF
      IF *s = 0 THEN EXIT LOOP
      s++
    WEND
  END SELECT
  IF l = 0 THEN
    REPLACE CHR$(1) WITH "][" IN Src$
    FUNCTION = Src
  END IF
  FUNCTION = s
END FUNCTION ' BracketHandler
SUB Push(Z$)
  CaseStk$[++Pusher]= Z$
END SUB
SUB Pop(Z$)
  Z$ = CaseStk$[--Pusher]
END SUB ' Pop
SUB EmitEpilog
  IF NoMain + EndOfProgram = 0 THEN
    FPRINT Outfile,"return 0;   //  End of main program"
    CALL BumpDown
    FPRINT Outfile,"}"
    FLUSH(Outfile)
  END IF
END SUB ' EmitEpilog
SUB EmitProlog
  FPRINT Outfile,""
  FPRINT Outfile,"int main(int argc, char *argv[])"
  '*****************************************************************************
  '         int main is conditionally removed later IN SUB AddProtos
  '*****************************************************************************
  FLUSH (Outfile)
END SUB ' EmitProlog
SUB DeclareVariables
  DIM RAW i
  DIM RAW A
  DIM RAW P$
  'DIM RAW VAR$
  DIM RAW VarName$
  DIM RAW VarDim$
  DIM RAW Storage$
  OPEN FileOut$ FOR INPUT AS FP1
  OPEN "$t$e$m$p" FOR OUTPUT AS Outfile
  OPEN cstFile$ FOR INPUT AS FP3
  IF LOF(cstFile$) > 0 THEN
    FPRINT Outfile,""
    FPRINT Outfile,"// *************************************************"
    FPRINT Outfile,"//            " + $BCX_STR_USR_CONST
    FPRINT Outfile,"// *************************************************"
    FPRINT Outfile,""
  END IF
  WHILE NOT EOF(FP3)
    LINE INPUT FP3,Z$
    FPRINT Outfile,LTRIM$(Z$)
  WEND
  CLOSE FP3

  '/***** 2011-03-10  Moved ENUM Emmission so that Named Enums can be used with User Prototypes / Classes -AIR *****/
  IF Use_EnumFile THEN
    FPRINT Outfile,"// *************************************************"
    FPRINT Outfile,"//        User's GLOBAL ENUM blocks"
    FPRINT Outfile,"// *************************************************"
    OPEN enuFile$ FOR INPUT AS FP8
    WHILE NOT EOF(FP8)
      LINE INPUT FP8,Z$
      FPRINT Outfile,Z$
    WEND
    CLOSE FP8
    FPRINT Outfile,""
  END IF

  OPEN udtFile$ FOR INPUT AS FP3
  IF LOF(udtFile$) > 0 THEN
    FPRINT Outfile,""
    FPRINT Outfile,"// *************************************************"
    FPRINT Outfile,"//   " + $BCX_STR_USR_TYPES
    FPRINT Outfile,"// *************************************************"
    WHILE NOT EOF(FP3)
      LINE INPUT FP3,Z$
      FPRINT Outfile,Scoot$,Z$
    WEND
  END IF
  CLOSE FP3
  IF HFileCnt > 0 THEN
    FPRINT Outfile,""
    FPRINT Outfile,"// *************************************************"
    FPRINT Outfile,"//                User Include Files"
    FPRINT Outfile,"// *************************************************"
    FPRINT Outfile,""
    A = 0
    WHILE A < HFileCnt
      FPRINT Outfile,HFiles$[A]
      A++
    WEND
    FPRINT Outfile,"#include <term.h>"
  END IF
  IF Use_SingleFile = TRUE THEN
    FPRINT Outfile,""
    FPRINT Outfile,"// *************************************************"
    FPRINT Outfile,"//                "+$BCX_STR_SYS_VARS
    FPRINT Outfile,"// *************************************************"
    FPRINT Outfile,""

    IF Use_RegEx THEN
      FPRINT Outfile,"typedef struct _REGEX"
      FPRINT Outfile,"{"
      FPRINT Outfile,"   int         count;"
      FPRINT Outfile,"   regmatch_t  matches[1024];"
      FPRINT Outfile,"   PCHAR       results[1024];"
      FPRINT Outfile,"}REGEX, *LPREGEX;\n"
    END IF

    IF Use_Time THEN
      FPRINT Outfile,"enum TIME_OPTIONS"
      FPRINT Outfile,"{"
      FPRINT Outfile,"  TIME,"
      FPRINT Outfile,"  HOUR,"
      FPRINT Outfile,"  MINUTE,"
      FPRINT Outfile,"  SECOND,"
      FPRINT Outfile,"  APM,"
      FPRINT Outfile,"  YEAR,"
      FPRINT Outfile,"  MONTH,"
      FPRINT Outfile,"  DAY,"
      FPRINT Outfile,"  DAYNAME,"
      FPRINT Outfile,"  WEEKDAY,"
      FPRINT Outfile,"  YEARDAY,"
      FPRINT Outfile,"  WEEKNUMBER,"
      FPRINT Outfile,"  DATE,"
      FPRINT Outfile,"  FULLDATE"
      FPRINT Outfile," };\n"

    END IF

    IF Use_Findfirst OR Use_Findnext THEN
      FPRINT Outfile,"typedef struct _FILE_FIND_DATA"
      FPRINT Outfile,"{"
      FPRINT Outfile,"  DWORD  dwFileAttributes;"
      FPRINT Outfile,"  DWORD  ftCreationTime;"
      FPRINT Outfile,"  DWORD  ftLastAccessTime;"
      FPRINT Outfile,"  DWORD  ftLastWriteTime;"
      FPRINT Outfile,"  DWORD  nFileSizeHigh;"
      FPRINT Outfile,"  DWORD  nFileSizeLow;"
      FPRINT Outfile,"  char   cFileSpec[MAX_PATH];"
      FPRINT Outfile,"  char   cFileName[MAX_PATH];"
      FPRINT Outfile,"  char   path[MAX_PATH];"
      FPRINT Outfile,"  DIR   *FileHandle;"
      FPRINT Outfile,"}FILE_FIND_DATA, *LPFILE_FIND_DATA;\n"
    END IF
    IF Use_Ldouble THEN
      FPRINT Outfile,"#define LDOUBLE long double"
    END IF
    IF Use_Idxqsort THEN
      FPRINT Outfile,"char*** pppStr;"
    END IF
    IF Use_Idxqsort OR Use_IdxqsortSt OR Use_PtrqsortSt THEN
      FPRINT Outfile,"int     Key;"
    END IF
    IF Use_IdxqsortSt THEN
      FPRINT Outfile,"char*   cmp1;"
      FPRINT Outfile,"int     StructSize;"
    END IF
    IF Use_PtrqsortSt THEN
      FPRINT Outfile,"int     OffSet;"
    END IF
    '********************************
    ' PB Compatible String Constants
    '********************************
    IF Use_NUL THEN
      FPRINT Outfile,"char    NUL [1]={0};     // Null"
    END IF

    IF Use_BEL THEN
      FPRINT Outfile,"char    BEL [2]={7,0};   // Bell"
    END IF

    IF Use_BS THEN
      FPRINT Outfile,"char    BS  [2]={8,0};   // Back Space"
    END IF

    IF Use_TAB THEN
      FPRINT Outfile,"char    TAB [2]={9,0};   // Horz Tab"
    END IF

    IF Use_LF THEN
      FPRINT Outfile,"char    LF  [2]={10,0};  // Line Feed"
    END IF

    IF Use_VT THEN
      FPRINT Outfile,"char    VT  [2]={11,0};  // Vert Tab"
    END IF

    IF Use_FF THEN
      FPRINT Outfile,"char    FF  [2]={12,0};  // Form Feed"
    END IF

    IF Use_CR THEN
      FPRINT Outfile,"char    CR  [2]={13,0};  // Carr Rtn"
    END IF

    IF Use_EOF THEN
      FPRINT Outfile,"char    EF  [2]={26,0};  // End-of-File"
    END IF

    IF Use_ESC THEN
      FPRINT Outfile,"char    ESC [2]={27,0};  // Escape"
    END IF

    IF Use_SPC THEN
      FPRINT Outfile,"char    SPC [2]={32,0};  // Space"
    END IF

    IF Use_DQ THEN
      FPRINT Outfile,"char    DQ  [2]={34,0};  // Double-Quote"
    END IF

    IF Use_DDQ THEN
      FPRINT Outfile,"char    DDQ [3]={34,34,0}; // Double-Double-Quote"
    END IF

    IF Use_Crlf THEN
      FPRINT Outfile,"char    CRLF[3]={13,10,0}; // Carr Rtn & Line Feed"
    END IF

    '********************************

    IF Use_Console THEN
      FPRINT Outfile,"int     color_fg = 7;"
      FPRINT Outfile,"int     color_bg = 0;"
    END IF

    IF Use_Lineinput THEN
      FPRINT Outfile,"char    *AR_fgets_retval;"
    END IF

    IF Use_Scan THEN
      FPRINT Outfile,"int     ScanError;"
    END IF

    IF Use_Inputbuffer = TRUE THEN
      FPRINT Outfile,"char    InputBuffer[1048576];"
    END IF

    IF Use_Findfirst OR Use_Findnext THEN
      FPRINT Outfile,"FILE_FIND_DATA FindData;"
    END IF
    IF Use_Gosub THEN
      FPRINT Outfile,"jmp_buf GosubStack[32];"
      FPRINT Outfile,"int     GosubNdx;"
    END IF
    IF Use_Dynacall THEN
      FPRINT Outfile,"HINSTANCE BCX_DllStore[256];"
    END IF

    '/***** 2013-06-26 New REGEX Keyword -AIR *****/


  END IF
  IF GlobalVarCnt THEN
    FPRINT Outfile,""
    FPRINT Outfile,"// *************************************************"
    FPRINT Outfile,"//            " + $BCX_STR_USR_VARS
    FPRINT Outfile,"// *************************************************"
    FPRINT Outfile,""
  END IF

  '*************************************
  'First we declare the simple Variables
  '*************************************
  FOR i = 1 TO GlobalVarCnt
    IF GlobalVars[i].VarEmitFlag THEN ITERATE
    IF "" = GlobalVars[i].VarDim$ AND GlobalVars[i].VarCondLevel = 0 THEN
      P$ = ""
      IF GlobalVars[i].VarPntr THEN P$ = STRING$(GlobalVars[i].VarPntr,42)
      A = GlobalVars[i].VarType
      IF GlobalVars[i].VarSF THEN
        VarName$ = "(*" + GlobalVars[i].VarName$ + ")"
      ELSE
        VarName$ = GlobalVars[i].VarName$
      END IF
      Storage$ = VarStorage$[GlobalVars[i].VarExtn] & VarConst$[GlobalVars[i].VarConstant]
      VarDim$ = GlobalVars[i].VarDim$
      CALL PrintGlobal(A, i, Storage$, P$, VarName$, VarDim$)
    END IF
  NEXT
  '   Next, we declare the Arrays
  FOR i = 1 TO GlobalVarCnt
    IF GlobalVars[i].VarEmitFlag THEN ITERATE
    IF "" <> GlobalVars[i].VarDim$ AND GlobalVars[i].VarCondLevel = 0 THEN
      IF INSTR(GlobalVars[i].VarDim,"{") = 0 THEN ' do uninitialized global arrays
        P$ = ""
        IF GlobalVars[i].VarPntr THEN P$ = STRING$(GlobalVars[i].VarPntr,42)
        A = GlobalVars[i].VarType
        IF GlobalVars[i].VarSF THEN
          VarName$ = "(*" + GlobalVars[i].VarName$ + EXTRACT$(GlobalVars[i].VarDim,"(") + ")"
          VarDim$ = MID$(GlobalVars[i].VarDim, INSTR(GlobalVars[i].VarDim,"("))
        ELSE
          VarName$ = GlobalVars[i].VarName$
          VarDim$ = GlobalVars[i].VarDim$
        END IF
        Storage$ = VarStorage$[GlobalVars[i].VarExtn] & VarConst$[GlobalVars[i].VarConstant]
        CALL PrintGlobal(A, i, Storage$, P$, VarName$, VarDim$)
      END IF
    END IF
  NEXT
  DIM RAW LastDef$
  DIM RAW LastLevel
  LastDef$ = ""
  LastLevel = 1
  FOR i = 1 TO GlobalVarCnt
    IF GlobalVars[i].VarEmitFlag THEN ITERATE
    IF GlobalVars[i].VarCondLevel THEN
      IF LastDef$ = "" THEN
        LastDef$ = GlobalVars[i].VarCondDef$
        LastLevel = GlobalVars[i].VarCondLevel
        FPRINT Outfile,LastDef$
      END IF
      IF LastDef$ <> GlobalVars[i].VarCondDef$ THEN
        IF GlobalVars[i].VarCondDef$ = "#else" THEN
          WHILE LastLevel > GlobalVars[i].VarCondLevel
            FPRINT Outfile,"#endif"
            LastLevel--
          WEND
          FPRINT Outfile,"#else"
          LastDef$ = GlobalVars[i].VarCondDef$
        ELSE
          WHILE LastLevel => GlobalVars[i].VarCondLevel
            FPRINT Outfile,"#endif"
            LastLevel--
          WEND
          LastDef$ = GlobalVars[i].VarCondDef$
          LastLevel = GlobalVars[i].VarCondLevel
          FPRINT Outfile,LastDef$
        END IF
      END IF
      P$ = ""
      IF GlobalVars[i].VarPntr THEN P$ = STRING$(GlobalVars[i].VarPntr,42)
      A = GlobalVars[i].VarType
      IF GlobalVars[i].VarSF THEN
        VarName$ = "(*" + GlobalVars[i].VarName$ + ")"
      ELSE
        VarName$ = GlobalVars[i].VarName$
      END IF
      VarDim$ = GlobalVars[i].VarDim
      Storage$ = VarStorage$[GlobalVars[i].VarExtn] & VarConst$[GlobalVars[i].VarConstant]
      CALL PrintGlobal(A, i, Storage$, P$, VarName$, VarDim$)
    END IF
  NEXT
  IF *LastDef$ THEN
    WHILE LastLevel
      FPRINT Outfile,"#endif"
      LastLevel--
    WEND
  END IF
  FPRINT Outfile,""



  '*************************************
  'Add Declared Dll variables
  '*************************************
  '  FPRINT Outfile, "// ****************************************"
  '  FPRINT Outfile, ""
  IF DllCnt THEN
    DIM RAW i, AR_DllName$

    FPRINT Outfile, ""
    FPRINT Outfile, "// **********[ DLL Declarations ]**********"
    FPRINT Outfile, ""

    ''------------------------------------------------------------------------
    '' Emit LoadLibrary assignments
    '' HMODULE  H_DLLNAME = LoadLibrary("DLLNAME.DLL");
    '' Todo: Add a check for H_DLLNAME = NULL in case of failure to load the DLL.
    ''------------------------------------------------------------------------
    FOR i = 0 TO LoadLibsCnt - 1
      IF INCHR(Loadlibs$[i],"-") THEN
        AR_DllName$ = EXTRACT$(Loadlibs$[i],"-")
      ELSEIF INCHR(Loadlibs$[i],".") THEN
        AR_DllName$ = EXTRACT$(Loadlibs$[i],".")
      END IF
      '~ FPRINT Outfile, "void  *H_", UCASE$(EXTRACT$(Loadlibs$[i], ".")), " = dlopen(", ENC$(Loadlibs$[i]), ", RTLD_LAZY);"
      FPRINT Outfile, "void  *H_", UCASE$(AR_DllName$), " = dlopen(", ENC$(Loadlibs$[i]), ", RTLD_LAZY);"
    NEXT i

    FOR i = 1 TO DllCnt
      FPRINT Outfile, DllDecl$[i]    ' Emit the users DLL Declarations
    NEXT

    FPRINT Outfile, ""
    FPRINT Outfile, "// ****************************************"
    FPRINT Outfile, ""
  END IF

  '********************************
  ' Read In The Data Statement File
  '********************************
  OPEN datFile$ FOR INPUT AS FP5
  IF LOF(datFile$) > 0 THEN
    FPRINT Outfile,""
    FPRINT Outfile,"// *************************************************"
    FPRINT Outfile,"//              User Data Statements"
    FPRINT Outfile,"// *************************************************"
    FPRINT Outfile,""
    FPRINT Outfile,"char * DATA [] ="
    FPRINT Outfile,"{"
    WHILE NOT EOF(FP5)
      LINE INPUT FP5,Z$
      FPRINT Outfile,Z$
    WEND
    FPRINT Outfile,"};"
  END IF
  CLOSE FP5
  WHILE NOT EOF(FP1)
    LINE INPUT FP1,Z$
    FPRINT Outfile,Z$
  WEND
  CALL CloseAll
  KILL FileOut$
  RENAME "$t$e$m$p", FileOut$
END SUB 'DeclareVariables
FUNCTION GetNumArgs OPTIONAL(Strt, NdxPos AS INTEGER PTR=NULL)
  DIM RAW CountR = 0 '() counter
  DIM RAW CountS = 0 '[] counter
  DIM RAW i 'loop counter
  DIM RAW j = 0 'comma counter
  DIM RAW k = 1 'function end flag
  FOR i = Strt TO Ndx
    IF Stk$[i] = "(" THEN
      CountR++
      k++
    ELSEIF Stk$[i] = ")" THEN
      CountR--
      k--
      IF k = 0 THEN EXIT FOR
    ELSEIF Stk$[i] = "[" THEN
      CountS++
    ELSEIF Stk$[i] = "]" THEN
      CountS--
    ELSEIF Stk$[i] = "," AND CountR = 0 AND CountS = 0 THEN
      j++
      IF NdxPos THEN *NdxPos = i
    END IF
  NEXT
  FUNCTION = j 'No. of commas = No. of args
END FUNCTION ' GetNumArgs
SUB GetVarCode(varcode AS VARCODE PTR)
  DIM RAW CB$, PT$, PTH$, VAR$, vn, RF$
  IF varcode->Method% = mt_Opts3 THEN
    varcode->Proto$ = varcode->Proto$  +  varcode->Token$
    IF varcode->Token$ = "," THEN
      varcode->Header$ = varcode->Header$ + varcode->Token$
    END IF
    EXIT SUB
  END IF
  IF varcode->Method% = mt_FuncSubx1 THEN
    varcode->Proto$ = varcode->Proto$  +  varcode->AsToken$ + "(*)("
    varcode->Header$ = varcode->Header$ + varcode->AsToken$  + " (*" + varcode->Token$ + ")("
    EXIT SUB
  END IF
  IF varcode->Method% = mt_FuncSubx2 THEN
    varcode->Proto$ = varcode->Proto$  +  varcode->AsToken$
    varcode->Header$ = varcode->Header$ + varcode->AsToken$ + " " + varcode->Token$
    EXIT SUB
  END IF
  IF IsCallBack THEN
    CB$ = "CALLBACK "
  ELSE
    CB$ = ""
  END IF
  IF INCHR(varcode->Token$,"*") OR INCHR(varcode->AsToken$,"*") OR varcode->IsPtrFlag THEN
    RemoveAll(varcode->Token$, "*")
    RemoveAll(varcode->AsToken$, "*")
    PT$  = STRING$(varcode->IsPtrFlag, ASC("*")) + " "
    PTH$ = PT$
  ELSE
    PTH$ = " "
    PT$ = ""
  END IF
  IF INCHR(varcode->Token$,"&") THEN
    RF$ = " &"
  ELSE
    RF$ = ""
  END IF
  vn = varcode->VarNo%
  VAR$ = GetVarTypeName$(vn)
  SELECT CASE vn
    '************************************************************************
    CASE vt_STRVAR
    '************************************************************************
    SELECT CASE varcode->Method%
      CASE mt_ProcessSetCommand
      varcode->StaticOut$ = "static char   " + Clean$(varcode->Token$)
      CASE mt_FuncSubDecC_Dec
      varcode->Functype$ = "char * " + CB$
      CASE mt_FuncSubDecC_Dec2
      IF NOT INCHR(varcode->Token$, "[") THEN
        varcode->Header$ = varcode->Header$  +  "char *" + Clean$(varcode->Token$)  +  ", "
        varcode->Proto$  = varcode->Proto$   +  "char *, "
      ELSE
        varcode->Header$ = varcode->Header$  +  "char " + REMOVE$(Clean$(varcode->Token$), "*") + ", "
        varcode->Proto$  = varcode->Proto$   +  "char [][65535], "
      END IF
      CASE mt_Opts
      varcode->Functype$ = "char *"
      CASE mt_Opts2
      varcode->Header$ = varcode->Header$  + "char * "  +  Clean$(varcode->Token$)
      varcode->Proto$  = varcode->Proto$   + "char* "
      CASE mt_OverLoad
      varcode->Functype$ = "char *"
      CASE mt_OverLoad2
      varcode->Header$ = varcode->Header$ + "char *" + Clean$(varcode->Token$) + ", "
    END SELECT
    '************************************************************************
    CASE vt_BOOL,vt_BYTE,vt_COLORREF,vt_DOUBLE,vt_DWORD,vt_FARPROC,vt_HDC, _
    vt_HANDLE,vt_HINSTANCE,vt_HWND,vt_INTEGER,vt_LONG,vt_LPBYTE,vt_LRESULT, _
    vt_SHORT,vt_SINGLE,vt_UINT,vt_ULONG,vt_USHORT,vt_VARIANT,vt_VOID,vt_LDOUBLE
    '************************************************************************
    SELECT CASE varcode->Method%
      CASE mt_ProcessSetCommand
      varcode->StaticOut$ = "static " + VAR$ + " " + Clean$(varcode->Token$)
      CASE mt_FuncSubDecC_Dec
      varcode->Functype$ = VAR$ + PTH$ + CB$
      CASE mt_FuncSubDecC_Dec2
      varcode->Header$ = varcode->Header$  +  VAR$ + PTH$ + Clean$(varcode->Token$)  +  ", "
      varcode->Proto$  = varcode->Proto$   +  VAR$ + RF$ + PT$ + ", "
      CASE mt_Opts
      varcode->Functype$ = VAR$ + PTH$
      CASE mt_Opts2
      varcode->Header$ = varcode->Header$  +  VAR$ + PTH$ + Clean$(varcode->Token$)
      varcode->Proto$ = varcode->Proto$   +  VAR$ + RF$ + PT$
      CASE mt_OverLoad
      varcode->Functype$ = VAR$ + " "
      CASE mt_OverLoad2
      varcode->Header$ = varcode->Header$ + VAR$ + PTH$ + Clean$(varcode->Token$) + ", "
    END SELECT
    '************************************************************************
    CASE vt_FILEPTR, vt_CHAR
    '************************************************************************
    SELECT CASE varcode->Method%
      CASE mt_FuncSubDecC_Dec
      varcode->Functype$ = VAR$ + PTH$ + CB$
      CASE mt_FuncSubDecC_Dec2
      varcode->Header$ = varcode->Header$  +  VAR$ + PTH$ + Clean$(varcode->Token$)  +  ", "
      varcode->Proto$  = varcode->Proto$   +  VAR$ + PT$ + ", "
      CASE mt_Opts
      varcode->Functype$ = VAR$ + PTH$
      CASE mt_Opts2
      varcode->Header$ = varcode->Header$  +  VAR$ + PTH$  +  Clean$(varcode->Token$)
      varcode->Proto$  = varcode->Proto$   +  VAR$ + PT$
      CASE mt_OverLoad
      varcode->Functype$ = VAR$ + " "
      CASE mt_OverLoad2
      varcode->Header$ = varcode->Header$ + VAR$ + PTH$ + Clean$(varcode->Token$) + ", "
    END SELECT
    '************************************************************************
    CASE vt_UDT, vt_STRUCT, vt_UNION
    '************************************************************************
    SELECT CASE varcode->Method%
      CASE mt_ProcessSetCommand
      IF vn = vt_UNION THEN
        varcode->StaticOut$ = "static union  " + Clean$(varcode->Token$)
      ELSE
        varcode->StaticOut$ = "static struct _" + Clean$(varcode->Token$) + " "
      END IF
      CASE mt_FuncSubDecC_Dec
      varcode->Functype$ = varcode->AsToken$ + PTH$ + CB$
      CASE mt_FuncSubDecC_Dec2
      varcode->Header$ = varcode->Header$  +  varcode->AsToken$ + PTH$ +  Clean$(varcode->Token$) + ", "
      varcode->Proto$  = varcode->Proto$   +  varcode->AsToken$ + RF$ + PT$ + ", "
      CASE mt_Opts
      varcode->Functype$ = varcode->AsToken$ + PTH$
      CASE mt_Opts2
      varcode->Header$ = varcode->Header$ + Clean$(varcode->AsToken$) + PTH$ + " " + Clean$(varcode->Token$)
      varcode->Proto$ = varcode->Proto$   + Clean$(varcode->AsToken$) + RF$ + PT$
      CASE mt_OverLoad
      varcode->Functype$ = VAR$ + " "
      CASE mt_OverLoad2
      varcode->Header$ = varcode->Header$ + varcode->AsToken$ + PTH$ + Clean$(varcode->Token$) + ", "
    END SELECT
    '************************************************************************
    CASE ELSE
    '************************************************************************
    SELECT CASE varcode->Method%
      CASE mt_FuncSubDecC_Dec
      varcode->Functype$ = varcode->AsToken$ + PTH$ + CB$
      CASE mt_FuncSubDecC_Dec2
      varcode->Header$ = varcode->Header$  +  varcode->AsToken$ + PTH$ +  Clean$(varcode->Token$) + ", "
      varcode->Proto$ = varcode->Proto$    +  varcode->AsToken$ + RF$ + PT$ + ", "
      CASE mt_Opts
      varcode->Functype$ = varcode->AsToken$ + PTH$
      CASE mt_Opts2
      varcode->Header$ = varcode->Header$ + Clean$(varcode->AsToken$) + " " + Clean$(varcode->Token$)
      varcode->Proto$  = varcode->Proto$  + Clean$(varcode->AsToken$)
    END SELECT
  END SELECT
END SUB ' GetVarCode
SUB AddProtos
  DIM RAW SaveMain$
  DIM RAW ZZ$
  DIM RAW A
  SaveMain$  = ""
  OPEN FileOut$ FOR INPUT  AS FP1
  OPEN "$t$e$m$p" FOR OUTPUT AS Outfile
  WHILE NOT EOF(FP1)
    LINE INPUT FP1,ZZ$
    IF INSTR(ZZ$,"int main") THEN
      SaveMain$ = ZZ$
      EXIT LOOP
    END IF
    FPRINT Outfile, ZZ$
  WEND

$INCLUDE "std_macros.bas"

  FPRINT Outfile,""

$INCLUDE "std_prototypes.bas"

  IF ProtoCnt THEN
    FPRINT Outfile,""
    FPRINT Outfile,"// *************************************************"
    FPRINT Outfile,"//               " + $BCX_STR_USR_PROTOS
    FPRINT Outfile,"// *************************************************"
    FPRINT Outfile,""
    DIM RAW LastDef$
    DIM RAW LastLevel
    LastDef$ = ""
    LastLevel = 1
    FOR A = 1 TO ProtoCnt
      IF LastDef$ = "" THEN
        LastDef$ = ProtoType[A].Condition$
        LastLevel = ProtoType[A].CondLevel
        IF Use_SingleFile = FALSE THEN
          IF LastDef$ > "" THEN FPRINT fpHFile, LastDef$
        END IF
        IF LastDef$ > "" THEN FPRINT Outfile, LastDef$
      END IF
      IF LastDef$ <> ProtoType[A].Condition$ THEN
        IF ProtoType[A].Condition$ = "#else" THEN
          WHILE LastLevel > ProtoType[A].CondLevel
            IF Use_SingleFile = FALSE THEN
              FPRINT fpHFile, "#endif"
            END IF
            FPRINT Outfile,"#endif"
            LastLevel--
          WEND
          IF Use_SingleFile = FALSE THEN
            FPRINT fpHFile, "#else"
          END IF
          FPRINT Outfile,"#else"
          LastDef$ = ProtoType[A].Condition$
          LastLevel = ProtoType[A].CondLevel
        ELSE
          WHILE LastLevel > ProtoType[A].CondLevel
            IF Use_SingleFile = FALSE THEN
              FPRINT fpHFile, "#endif"
            END IF
            FPRINT Outfile,"#endif"
            LastLevel--
          WEND
          LastDef$ = ProtoType[A].Condition$
          LastLevel = ProtoType[A].CondLevel
          IF Use_SingleFile = FALSE THEN
            IF LastDef$ > "" THEN FPRINT fpHFile, LastDef$
          END IF
          IF LastDef$ > "" THEN FPRINT Outfile, LastDef$
        END IF
      END IF
      IF UseStdCall AND UseCpp THEN
        IF LEFT$(ProtoType[A].Prototype$, 9) = "C_EXPORT " THEN
          EmitExportDef(ProtoType[A].Prototype$)
        END IF
      END IF
      T$ = EXTRACT$(ProtoType[A].Prototype$, SPC$)
      T$ = RPAD$(T$, 7) + SPC$
      ProtoType[A].Prototype$ = T$ + REMAIN$(ProtoType[A].Prototype$, SPC$)
      IF Use_SingleFile = FALSE THEN
        FPRINT fpHFile, ProtoType[A].Prototype$
      END IF
      IF UseCpp=False AND NOT INSTR(ProtoType[A].Prototype$,"::") THEN
        FPRINT Outfile,ProtoType[A].Prototype$
      END IF
      'print ProtoType[A].Prototype$
    NEXT A 'ProtoCnt
    IF *LastDef$ THEN
      WHILE LastLevel > 0
        IF Use_SingleFile = FALSE THEN
          FPRINT fpHFile, "#endif"
        END IF
        FPRINT Outfile,"#endif"
        LastLevel--
      WEND
    END IF
  END IF
  FPRINT Outfile,""
  ' begin for initialized global arrays
  DIM RAW P$, i
  DIM RAW VarName$
  DIM RAW VarDim$
  DIM RAW Storage$
  DIM RAW VAR$
  IF GlobalVarCnt > 0 THEN
    FPRINT Outfile,""
    FPRINT Outfile,"// *************************************************"
    FPRINT Outfile,"//            User Global Initialized Arrays"
    FPRINT Outfile,"// *************************************************"
    FPRINT Outfile,""
    FOR i = 1 TO GlobalVarCnt
      IF GlobalVars[i].VarEmitFlag THEN ITERATE
      IF "" <> GlobalVars[i].VarDim$ AND GlobalVars[i].VarCondLevel = 0 THEN
        IF INSTR(GlobalVars[i].VarDim,"{") THEN
          P$ = ""
          IF GlobalVars[i].VarPntr THEN P$ = STRING$(GlobalVars[i].VarPntr,42)
          A = GlobalVars[i].VarType
          IF GlobalVars[i].VarSF THEN
            VarName$ = "(*" + GlobalVars[i].VarName$ + EXTRACT$(GlobalVars[i].VarDim,"(") + ")"
            VarDim$ = MID$(GlobalVars[i].VarDim, INSTR(GlobalVars[i].VarDim,"("))
          ELSE
            VarName$ = GlobalVars[i].VarName$
            VarDim$ = GlobalVars[i].VarDim
          END IF
          Storage$ = VarStorage$[GlobalVars[i].VarExtn] & VarConst$[GlobalVars[i].VarConstant]
          SELECT CASE A
            ' handle exceptions
            CASE vt_STRVAR
            FPRINT Outfile,Storage$;"char    ";VarName$;VarDim$;";"
            CASE vt_FILEPTR
            REMOVE "@" FROM GlobalVars[i].VarName$
            FPRINT Outfile,Storage$;"FILE   *";VarName$;VarDim$;";"
            CASE vt_BOOL
            FPRINT Outfile,Storage$;"bool    ";VarName$;VarDim$;";"
            ' handle normal
            CASE vt_UDT, vt_STRUCT, vt_UNION
            VAR$ = TypeDefs[GlobalVars[i].VarDef].VarName$
            VAR$ = RPAD$(VAR$, 7)
            FPRINT Outfile,Storage$;VAR$;" ";P$;VarName$;VarDim$;";"
            CASE vt_VarMin TO vt_VarMax
            VAR$ = GetVarTypeName$(GlobalVars[i].VarType)
            VAR$ = RPAD$(VAR$, 7)
            FPRINT Outfile,Storage$;VAR$;" ";P$;VarName$;VarDim$;";"
          END SELECT
        END IF
      END IF
    NEXT
    FPRINT Outfile,""
  END IF ' end of initialized global arrays
  IF Use_Overloaded THEN
    FPRINT Outfile,"// *************************************************"
    FPRINT Outfile,"//        User's Overloaded Subs/Functions          "
    FPRINT Outfile,"// *************************************************"
    OPEN ovrFile$ FOR INPUT AS FP8
    WHILE NOT EOF(FP8)
      LINE INPUT FP8,ZZ$
      IF INSTR(ZZ$,"overloaded") THEN
        FPRINT Outfile,"\n"
      END IF
      FPRINT Outfile,ZZ$
    WEND
    CLOSE FP8
    FPRINT Outfile,"\n\n"
  END IF
  OPEN setFile$ FOR INPUT AS FP5
  IF LOF(setFile$) > 0 THEN
    FPRINT Outfile,"// *************************************************"
    FPRINT Outfile,"//              User GLOBAL SET Statements"
    FPRINT Outfile,"// *************************************************"
    FPRINT Outfile,""
    WHILE NOT EOF(FP5)
      LINE INPUT FP5,Z$
      FPRINT Outfile,Z$
    WEND
    FPRINT Outfile,""
  END IF
  CLOSE FP5
  IF Use_SingleFile = FALSE THEN
    CLOSE fpHFile
  END IF
  IF NoMain = 0 THEN
    FPRINT Outfile,"// *************************************************"
    FPRINT Outfile,"//                  " + $BCX_STR_MAIN_PROG
    FPRINT Outfile,"// *************************************************"
    FPRINT Outfile,""
  END IF
  '**********************************************************************
  IF NoMain = FALSE THEN
    FPRINT Outfile,SaveMain$ ' add the >> void main() back to the stream
    FPRINT Outfile,"{" ' AND OPEN the main FUNCTION
    FPRINT Outfile,"  G_argc = argc;"
    FPRINT Outfile,"  G_argv = argv;"
    CALL BumpUp
  END IF
  '**********************************************************************
  WHILE NOT EOF(FP1)
    LINE INPUT FP1,ZZ$
    FPRINT Outfile,Scoot$,ZZ$
  WEND
  IF Use_SingleFile = TRUE THEN
    CALL RunTimeFunctions
  END IF
  FLUSH(Outfile)
  CALL  CloseAll
  KILL  FileOut$
  RENAME "$t$e$m$p", FileOut$
END SUB ' AddProtos

' ***** RUNTIME FUNCTIONS *****
$INCLUDE "runtime.bas"
' *****************************

FUNCTION JoinLines(Arg$)
  IF iMatchRgt(Arg$, " _") THEN
    Arg[LEN(Arg)-1] = 0
    CurLine$ = CurLine$ & Arg$
    FUNCTION = 1
  END IF
  IF *CurLine <> 0 THEN
    Arg$ = CurLine$ & Arg$
    CurLine$ = ""
  END IF
  UmQt = FALSE
  FUNCTION = 0
END FUNCTION
SUB StripCode( Arg$ )
  RAW p AS PCHAR
  RAW p2 = Arg AS PCHAR
  RAW asmFlag = 0
  RAW eStr = 0
  RAW sub_$
  WHILE (*p2 >8 AND *p2 < 14) OR *p2 = 32 'Trim leading space
    INCR p2
  WEND
  IF *p2 = ASC("!") THEN asmFlag = NOT UmQt 'Handle "!" Asm lines
  p = p2
  WHILE *p
    IF *p = 9 THEN *p = 32
    IF *p = 34 THEN ' ignore anything in string literal
      IF *(p-1) = 69 THEN ' we're in an extended string: E"\qABCD\n"
        *(p-1) = 1 ' chr$(1) will be deleted
        eStr = TRUE
      END IF
      WHILE *(++p) <> 34
        IF *p = 92 AND eStr THEN ' look for a \0, \t, \n, \r, \q, \\
          *p = 2
          SELECT CASE *(p+1)
            CASE 48
            *(p+1) = 3
            CASE 116
            *(p+1) = 4
            CASE 110
            *(p+1) = 5
            CASE 114
            *(p+1) = 6
            CASE 113
            *(p+1) = 7
            CASE 92
            *(p+1) = 8
          END SELECT
          p++
        END IF
        IF *p = 0 THEN UmQt = NOT UmQt : EXIT WHILE
      WEND
    END IF
    ' If we're in a quoted continuation line then ignore comments
    IF NOT UmQt AND NOT asmFlag THEN
      'Remove REM's
      IF (*p BOR 32) = ASC("r") THEN
        IF _
          (*(p+1) BOR 32) = ASC("e") AND _
          (*(p+2) BOR 32) = ASC("m") AND _
          (*(p+3) = 32 OR *(p+3) = 0) THEN
          IF p = p2 OR *(p-1) = ASC(":") OR *(p-1) = 32 THEN
            *p = 0 : EXIT WHILE
          END IF
        END IF
      END IF
      ' check for single quote comment marker and //C++ style comments
      IF *p = ASC("'") OR (*p = ASC("/") AND *(p+1) = ASC("/")) THEN
        *p = 0 : EXIT WHILE
      END IF
    END IF
    p++
  WEND
  WHILE p2 < p
    'Trim trailing space
    WHILE (*(p-1) >8 AND *(p-1) < 14) OR *(p-1) = 32
      *(--p) = 0
    WEND
    IF UmQt OR asmFlag THEN EXIT WHILE
    'Strip dangling colons
    IF *(p-1) = ASC(":") AND *(p-2) = 32 THEN
      DECR p
    ELSE
      EXIT WHILE
    END IF
  WEND
  IF eStr THEN
    REPLACE CHR$(1) WITH "" IN p2$ ' E
    REPLACE CHR$(2) WITH "" IN p2$ ' \ first backslash
    '---
    sub_$ = DQ$+"+CHR$(0)+"+DQ$
    REPLACE CHR$(3) WITH sub_$ IN p2$ ' 0
    sub_$ = DQ$+"+CHR$(9)+"+DQ$
    REPLACE CHR$(4) WITH sub_$ IN p2$ ' t
    sub_$ = DQ$+"+CHR$(10)+"+DQ$
    REPLACE CHR$(5) WITH sub_$ IN p2$ ' n
    sub_$ = DQ$+"+CHR$(13)+"+DQ$
    REPLACE CHR$(6) WITH sub_$ IN p2$ ' r
    sub_$ = DQ$+"+CHR$(34)+"+DQ$
    REPLACE CHR$(7) WITH sub_$ IN p2$ ' q
    sub_$ = DQ$+"+CHR$(92)+"+DQ$
    REPLACE CHR$(8) WITH sub_$ IN p2$ ' \
    '---
    REPLACE (CHR$(34)+CHR$(34)+CHR$(43)) WITH "" IN p2$
    REPLACE (CHR$(43)+CHR$(34)+CHR$(34)) WITH "" IN p2$
    '---
  END IF
  '/***** 2010/11/24 Changed to avoid overflow on 64bit Ubuntu -AIR *****/
  ' Arg$ = p2$
  memcpy(Arg$, p2$, LEN(p2$)+1)
END SUB

SUB ProcSingleLineIf(BYREF ifFlag)
  DIM RAW Tmp$, ifp, NdIfs
  DIM STATIC EFlag
  IF ifFlag = 0 THEN EFlag = 0
  REDO:
  IF SplitCnt > 120 THEN Abort("Stack Overflow - Too many statements on one line")
  Tmp$ = SplitStk$[SplitCnt] & SPC$
  IF iMatchLft(Tmp$, "if ") THEN
    ifp = iMatchNQ(Tmp$, " then ")
    IF ifp THEN
      SplitStk$[SplitCnt++] = LEFT$(Tmp$,ifp+4)
      SplitStk$[SplitCnt] = LTRIM$(Tmp+ifp+4)
      EFlag = MAX(0,EFlag-1) : INCR (ifFlag)
      GOTO REDO
    END IF
  ELSEIF (ifFlag) THEN
    IF iMatchLft(Tmp$, "else ") THEN '"else xxx"
      LftLse:
      IF ++EFlag > 1 THEN
        NdIfs = MAX(1,(ifFlag)-1) : (ifFlag) = 1 : EFlag = 0
        IF iMatchWrd(SplitStk$[SplitCnt-1],"else") THEN DECR SplitCnt
        REPEAT NdIfs : SplitStk$[SplitCnt++] = "END IF" : END REPEAT
      END IF
      SplitStk$[SplitCnt++] = "ELSE"
      SplitStk$[SplitCnt] = TRIM$(Tmp+4)
      GOTO REDO
    ELSE
      ifp = iMatchNQ(Tmp$, " else ")
      IF ifp THEN '"xxx else xxx"
        SplitStk$[SplitCnt++] = RTRIM$(LEFT$(Tmp$, ifp-1))
        Tmp$ = MID$(Tmp$, ifp+1)
        GOTO LftLse
      END IF
    END IF
  END IF 'process "if/then/else"
END SUB

'Split statements separated by a colon or a single line IF...THEN
FUNCTION SplitLines(Arg$)
  DIM RAW p  = Arg AS PCHAR
  DIM RAW st = Arg AS PCHAR
  DIM RAW i = 0, IfFlag = 0, SpcolonFlag = 0
  DIM RAW ParaCnt = 0
  IF *p = ASC("!") OR *p = ASC("$") THEN EXIT FUNCTION
  WHILE *p
    IF *p = 32 THEN SpcolonFlag = 1
    IF *p = 34 THEN ' ignore anything in string literal
      WHILE *(++p) <> 34
        IF *p = 0 THEN FUNCTION = SplitCnt
      WEND
    END IF
    IF *p = 40 THEN ParaCnt++
    IF *p = 41 THEN ParaCnt--
    IF *p = ASC(":") AND *(p+1) <> ASC("=") THEN
      '--------- BEGIN INSERT ----------------
      IF *(p+1) = ASC(":") THEN
        *p = -15
        *(p+1) = -15
        '--------- END INSERT ----------------
      ELSE
        IF *(p+1) <> 0 OR SpcolonFlag THEN
          WHILE *st = 32
            st++
          WEND 'Forward past leading spaces
          SplitCnt++
          WHILE st < p 'Copy new string
            SplitStk[SplitCnt][i++] = *(st++)
          WEND
          WHILE SplitStk[SplitCnt][i-1] = 32 'Trim trailing spaces
            i--
          WEND
          SplitStk[SplitCnt][i] = 0 'Add a string terminator
          IF ParaCnt = 0 THEN
            i=0
            st++ 'advance to next start position
            ProcSingleLineIf(&IfFlag)
          ELSE
            SplitCnt--
          END IF
        END IF 'if NOT End of line
      END IF
    END IF 'if :
    p++
  WEND
  'Add the last string
  IF SplitCnt > 0 THEN
    WHILE *st = 32
      st++
    WEND 'Forward past leading spaces
    SplitCnt++
    WHILE *st
      SplitStk[SplitCnt][i++] = *(st++)
    WEND
    SplitStk[SplitCnt][i] = 0
    ProcSingleLineIf(&IfFlag)
    'Process single line if/thens that don't contain colon separated statements
  ELSEIF iMatchLft(Arg$,"if ") AND NOT iMatchRgt(Arg$," then") THEN
    SplitStk$[++SplitCnt] = Arg$
    ProcSingleLineIf(&IfFlag)
  END IF
  'If we processed single line "if/then" then close it up
  IF IfFlag THEN
    WHILE IfFlag
      SplitStk$[++SplitCnt] = "END IF"
      IfFlag--
    WEND
  END IF
  FUNCTION = SplitCnt
END FUNCTION
'----------------------------------------------
'Case insensitive comparison - MatchStr$ to Arg$
' mt = 0, 1 or 2 Match left, whole word, right
'----------------------------------------------
CONST iMatchLft(A,B) = iMatch(A,B,0)
CONST iMatchWrd(A,B) = iMatch(A,B,1)
CONST iMatchRgt(A,B) = iMatch(A,B,2)
FUNCTION iMatch(Arg$, MatchStr$, mt)
  IF mt = 2 THEN
    DIM RAW L1, L2
    L1 = LEN(Arg$) : L2 = LEN(MatchStr$)
    IF L1 < L2 THEN EXIT FUNCTION
    Arg = (Arg + L1) - L2
  END IF
  WHILE *MatchStr
    'If we run out string to match against then return no match
    IF *Arg = 0 THEN EXIT FUNCTION
    'bit ORing a character with 0x20 produces the lower case of it
    IF (*Arg BOR 32) <> (*MatchStr BOR 32) THEN EXIT FUNCTION
    INCR Arg
    INCR MatchStr
  WEND
  IF mt AND *Arg <> 0 THEN EXIT FUNCTION
  FUNCTION = 1
END FUNCTION
'----------------------------------------------
'Returns the position of the first occurrence
'of MatchStr$ in Arg$ that isn't in quotes.
'----------------------------------------------
FUNCTION iMatchNQ(Arg$, MatchStr$)
  DIM RAW mi=0
  DIM RAW a = Arg AS PCHAR
  WHILE MatchStr[mi]
    IF *a = 34 THEN
      mi=0
      WHILE *(++a) <> 34
        IF *a = 0 THEN EXIT FUNCTION
      WEND
    END IF
    IF a[mi] = 0 THEN EXIT FUNCTION
    'If we run out string to match against then return no match
    'bit ORing a character with 0x20 produces the lower case of it
    IF (a[mi] BOR 32) <> (MatchStr[mi] BOR 32) THEN
      INCR a : mi= -1
    END IF
    INCR mi
  WEND
  FUNCTION = (a-Arg) + 1 ' We have a match
END FUNCTION

FUNCTION SpecialCaseHandler(Arg$)
  DIM RAW i,j
  DIM RAW lsz$
  IF iMatchNQ(Arg$," sub ") OR iMatchNQ(Arg$," function ") THEN EXIT FUNCTION
  IF iMatchNQ(Arg$,"function main(") THEN
    SrcStk$[++SrcCnt] = Arg$
    SrcStk$[++SrcCnt] = "G_argc = argc"
    SrcStk$[++SrcCnt] = "G_argv = argv"
    GOTO ProcessNew
  END IF
  '**************************************************
  ' Handle Multiple Dim's, Locals, Globals, Shared's
  ' Example: DIM a, b!, c$, d$*1000, q[100] AS DWORD
  '**************************************************
  lsz$ =  SPC$ & EXTRACT$(Arg$," ") & SPC$
  IF iMatchNQ(" dim , local , global , raw , static , shared , dynamic , auto , register , extern ", lsz$) THEN
    CALL FastLexer(Arg$," ",",(){}")
    ' tolerate nonsense like DIM A% as double
    FOR i = 1 TO Ndx
      IF iMatchWrd(Stk$[i],"as") THEN
        Stk$[i-1] = Clean$(Stk$[i-1])
      END IF
    NEXT
    Stk$[2] = SPC$ & Stk$[2] & SPC$
    IF iMatchNQ(" raw local dynamic register static shared auto ",Stk$[2]) THEN
      Stk$[1] = Stk$[1] & Stk$[2]
      Stk$[2] = ""
    END IF
    INCR SrcCnt
    j=0
    FOR i = 1 TO Ndx
      IF Stk[i][0] = ASC("(") THEN INCR j
      IF Stk[i][0] = ASC("{") THEN INCR j
      IF Stk[i][0] = ASC(")") THEN DECR j
      IF Stk[i][0] = ASC("}") THEN DECR j
      IF Stk[i][0] = ASC(",") AND NOT j THEN
        Stk$[i]  = Stk$[1]
        INCR SrcCnt
      END IF
      SrcStk$[SrcCnt] = SrcStk$[SrcCnt] + Stk$[i] + " "
    NEXT
    GOTO ProcessNew
  END IF

  SELECT CASE TRUE
    '******************************
    CASE iMatchLft(Arg$,"on ")
    '******************************
    DIM RAW Target
    j = 0
    CALL FastLexer(Arg$," ",",")
    FOR i = 1 TO Ndx
      IF iMatchLft(Stk$[i],"gosub") OR _
        iMatchLft(Stk$[i],"goto")  OR _
        iMatchLft(Stk$[i],"call")  THEN
        Target = i+1
        EXIT FOR
      END IF
    NEXT
    SrcStk$[++SrcCnt] = "select case " 'Assemble our expression
    FOR i = 2 TO Target - 2
      SrcStk$[SrcCnt] = SrcStk$[SrcCnt]+" "+ Stk$[i]
    NEXT
    FOR i = Target TO Ndx
      IF Stk$[i] = "," THEN ITERATE
      INCR j
      SrcStk$[++SrcCnt] = "case"  +  STR$(j)
      SrcStk$[++SrcCnt] = Stk$[Target-1]  +  " "  +  Stk$[i]
    NEXT
    SrcStk$[++SrcCnt] = "end select"
    GOTO ProcessNew
    '******************************
    CASE iMatchLft(Arg$,"loop ")
    '******************************
    CALL FastLexer(Arg$," ",",()")
    IF iMatchLft(Stk$[2],"until") THEN
      SrcStk$[++SrcCnt] = "if "
      FOR i = 3 TO Ndx
        SrcStk$[SrcCnt] = SrcStk$[SrcCnt] + Stk$[i] + " "
      NEXT
      SrcStk$[SrcCnt] = SrcStk$[SrcCnt] + " then"
      SrcStk$[++SrcCnt] = "exit loop"
      SrcStk$[++SrcCnt] = "end if"
      SrcStk$[++SrcCnt] = "loop"
      GOTO ProcessNew
    ELSEIF iMatchLft(Stk$[2],"while") THEN
      SrcStk$[++SrcCnt] = "if NOT ("
      FOR i = 3 TO Ndx
        SrcStk$[SrcCnt] = SrcStk$[SrcCnt] + Stk$[i] + " "
      NEXT
      SrcStk$[SrcCnt] = SrcStk$[SrcCnt] + ") then"
      SrcStk$[++SrcCnt] = "exit loop"
      SrcStk$[++SrcCnt] = "end if"
      SrcStk$[++SrcCnt] = "loop"
      GOTO ProcessNew
    ELSE
      IF Ndx > 1 THEN
        Abort("UNKNOWN Word " + Stk$[2] + " After LOOP")
      END IF
    END IF
    '******************************
    CASE iMatchLft(Arg$,"do ")
    '******************************
    CALL FastLexer(Arg$," ",",()")
    IF iMatchLft(Stk$[2],"until") THEN
      SrcStk$[++SrcCnt] = "do"
      SrcStk$[++SrcCnt] = "if "
      FOR i = 3 TO Ndx
        SrcStk$[SrcCnt] = SrcStk$[SrcCnt] + Stk$[i] + " "
      NEXT
      SrcStk$[SrcCnt] = SrcStk$[SrcCnt] + "then"
      SrcStk$[++SrcCnt] = "exit loop"
      SrcStk$[++SrcCnt] = "end if"
      GOTO ProcessNew
    ELSEIF iMatchLft(Stk$[2],"while") THEN
      SrcStk$[++SrcCnt] = "while "
      FOR i = 3 TO Ndx
        SrcStk$[SrcCnt] = SrcStk$[SrcCnt] + Stk$[i] + " "
      NEXT
      GOTO ProcessNew
    ELSE
      IF Ndx > 1 THEN
        Abort("UNKNOWN Word " + Stk$[2] + " After DO")
      END IF
    END IF
  END SELECT
  EXIT FUNCTION
  ProcessNew:
  Ndx = i = 0
  WHILE SrcCnt
    Arg$ = SrcStk$[++i]
    SrcStk$[i] = ""
    DECR SrcCnt
    CALL Parse(Arg$)
    IF Ndx THEN CALL Emit
  WEND
  FUNCTION = TRUE
END FUNCTION
'*************************************************************
'delim1$ = delimiters to be removed
'delim2$ = delimiters to keep
'Stk$ and Ndx are Global
'As long as Ndx is honored Stk does not need to be initialized
'*************************************************************
SUB FastLexer OPTIONAL(Arg$, delim1$, delim2$, TokQuote = 1)
  DIM RAW cnt1=0, cnt2=0
  DIM RAW pd1 AS PCHAR, pd2 AS PCHAR
  Ndx=1
  WHILE Arg[cnt1]
    IF Arg[cnt1] = 34 THEN 'quotes - string literals
      IF cnt2 AND TokQuote THEN Stk[Ndx++][cnt2]=0 : cnt2=0
      Stk[Ndx][cnt2] = 34
      WHILE Arg[++cnt1] <> 34
        Stk[Ndx][++cnt2] = Arg[cnt1]
        IF Arg[cnt1] = 0 THEN EXIT SUB
      WEND
      Stk[Ndx][++cnt2] = Arg[cnt1]
      IF TokQuote THEN
        Stk[Ndx++][++cnt2]=0
        cnt2=0
        GOTO again
      END IF
    END IF
    pd1 = delim1
    WHILE *pd1
      IF *(pd1++) = Arg[cnt1] THEN
        IF cnt2 THEN Stk[Ndx++][cnt2]=0 : cnt2=0
        GOTO again
      END IF
    WEND
    pd2 = delim2
    WHILE *pd2
      IF *(pd2++) = Arg[cnt1] THEN
        IF cnt2 THEN Stk[Ndx++][cnt2]=0
        Stk[Ndx][0] = Arg[cnt1]
        Stk[Ndx++][1]=0 : cnt2 = 0
        GOTO again
      END IF
    WEND
    Stk[Ndx][cnt2++]=Arg[cnt1]
    again:
    INCR cnt1
  WEND
  Stk[Ndx][cnt2]=0
  IF cnt2 = 0 THEN DECR Ndx
END SUB

SUB InsertTokens(PosAfter, NumTokens, ...)
  DIM RAW ap AS va_list, i
  FOR i = Ndx TO PosAfter+1 STEP -1
    Stk$[i+NumTokens] = Stk$[i]
  NEXT i
  va_start(ap,NumTokens)
  FOR i = PosAfter+1 TO PosAfter+NumTokens
    Stk$[i] = va_arg(ap, char*)
  NEXT i
  va_end(ap)
  INCR Ndx,NumTokens
END SUB

SUB EmitExportDef(fs$)
  STATIC beenhere
  DIM RAW fname$, funcname$
  DIM RAW i, st=1, sz=0
  fname$ = EXTRACT$(FileIn$,".") + ".def"
  IF NOT beenhere THEN
    OPEN fname$ FOR OUTPUT AS fpdef
    _splitpath_(FileIn$, NULL, NULL, fname$, NULL)
    FPRINT fpdef,"LIBRARY ", ENC$(fname$)
    FPRINT fpdef, "EXPORTS"
    beenhere = TRUE
  END IF
  FastLexer(fs$, "", "(,)")
  WHILE *Stk$[st] <> ASC("(")
    INCR st
  WEND
  FOR i = st+1 TO Ndx
    IF *Stk$[i] = ASC(")") THEN EXIT
    IF *Stk$[i] <> ASC(",") THEN
      IF INCHR(Stk$[i],"*") THEN INCR sz,4 : ITERATE
      IF INSTR(Stk$[i],"longlong",1,1) OR _
        INSTR(Stk$[i],"double",1,1)    OR _
        INSTR(Stk$[i],"long long") THEN
        INCR sz,8
        ITERATE
      END IF
      IF NOT INCHR(Stk$[i],"void") THEN INCR sz,4
    END IF
  NEXT
  Stk$[1] = TRIM$(Stk$[1])
  funcname$ = MID$(Stk$[1],INSTRREV(Stk$[1]," ") + 1)
  FPRINT fpdef,funcname$," = _",funcname$,"@",LTRIM$(STR$(sz))
  'CloseAll is called at the end of AddProtos
END SUB

FUNCTION GetArg$(ArgNum, fp AS functionParse PTR)
  DIM RAW RetArg$
  DIM RAW ArgEnd   = fp->CommaPos[ArgNum] - 1
  DIM RAW ArgStart = fp->CommaPos[ArgNum - 1] + 1
  RetArg$ = ""
  IF ArgNum >= fp->NumArgs THEN ArgEnd = Ndx
  FOR ArgStart = ArgStart TO ArgEnd
    CONCAT(RetArg$, Stk$[ArgStart])
  NEXT ArgStart
  FUNCTION = RetArg$
END FUNCTION

FUNCTION SepFuncArgs(Strt, fp AS functionParse PTR, functionflag AS INTEGER)
  DIM RAW CountR = 0 '()[] counter
  DIM RAW i = Strt 'loop counter
  IF functionflag THEN
    WHILE i <= Ndx
      IF Stk[i][0] = ASC("(") THEN EXIT WHILE
      INCR i
    WEND
    Strt = i + 1
    fp->NumArgs = 0 'comma counter
    fp->CommaPos[0] = i 'Strt-1
    IF Strt > Ndx THEN
      FUNCTION = 0
    END IF
  ELSE
    Strt = 2
    fp->CommaPos[0] = 1
  END IF
  IF *Stk$[Strt] = ASC(")") THEN
    fp->CommaPos[1] = Strt
    FUNCTION = 0
  END IF
  fp->NumArgs = 1
  FOR i = Strt TO Ndx
    IF *Stk$[i] = ASC("(") OR *Stk$[i] = ASC("[") THEN
      CountR++
    ELSEIF *Stk$[i] = ASC(")") OR *Stk$[i] = ASC("]") THEN
      IF CountR = 0 THEN
        fp->CommaPos[fp->NumArgs] = i
        EXIT FOR
      END IF
      CountR--
    ELSEIF *Stk$[i] = ASC(",") AND CountR = 0 THEN
      fp->CommaPos[fp->NumArgs] = i
      INCR fp->NumArgs
    END IF
  NEXT
  IF functionflag = 0 THEN fp->CommaPos[fp->NumArgs] = Ndx
  FUNCTION = fp->NumArgs 'Number of commas + 1 = Number of arguments
END FUNCTION ' SepFuncArgs

FUNCTION MakeDecProto(fp AS functionParse PTR) AS PCHAR
  DIM RAW fpp AS functionParse
  DIM RAW FunType$
  DIM RAW AsType$
  DIM RAW AsArrys$
  DIM RAW FoundAs
  DIM RAW pointer   = 0
  DIM RAW i,ii
  DIM RAW OptValue$
  DIM RAW OptFlag   = 0
  STATIC Proto$
  STATIC SubFunPtr
  IF SubFunPtr THEN GOTO argparse
  Proto$   = ""
  FunType$ = ""
  'Determine function type
  '-----------------------------------------------------

  '/***** 2010-11-15 Added check for constructor/destructor -AIR
  IF iMatchWrd(Stk$[2], "sub") OR iMatchWrd(Stk$[2], "constructor") OR iMatchWrd(Stk$[2], "destructor") THEN
    FunType$ = "void"
  ELSEIF *Stk$[Ndx] = ASC(")") THEN
    'check for type identifier suffix
    'if unknown, then integer will default
    FunType$ = VarTypeLookup$[ INCHR(VarTypes$, RIGHT$(Stk$[3],1)) ]
  ELSE
    FOR i = Ndx TO fp->CommaPos[fp->NumArgs]+1 STEP -1
      IF iMatchWrd(Stk$[i], "ptr") THEN
        INCR pointer
      ELSEIF iMatchWrd(Stk$[i], "as") THEN
        EXIT FOR
      ELSE
        FunType$ = Stk$[i] + SPC$ + FunType$
      END IF
    NEXT
  END IF
  'INCR pointer, TALLY(FunType$, "*")
  'RemoveAll(FunType$, "*", 1)
  IF InTypeDef THEN
    '/***** 2010-11-15 Added code for constructor/destructor WITHIN CLASS DECLARATION *****/
    '/***** also changed Proto$ to get rid of (__atribute__cdecl)(*variable) -AIR *****/
    '    Proto$ = FunType$ + "  " + STRING$(pointer, ASC("*")) + " (" + CallType$ + "*" + Clean$(Stk$[3]) + ")("
    IF iMatchWrd(Stk$[2], "constructor") THEN
      Proto$ = Clean$(Stk$[3]) + "("
    ELSEIF iMatchWrd(Stk$[2], "destructor") THEN
      Proto$ = "~" + Clean$(Stk$[3]) + "("
    ELSE
      Proto$ = FunType$ + " " + Clean$(Stk$[3]) + "("
    END IF


    DIM RAW Var$, w, id, vt
    Var$ = FunType$ + STRING$(pointer, ASC("*"))
    GetTypeInfo(Var$, &w, &id, &vt)
    AddTypedefElement(BaseTypeDefsCnt[InTypeDef],vt, Clean$(Stk$[3]), FunType$, 0)
  ELSEIF SFPOINTER THEN
    Proto$ = "typedef " + FunType$ + " (" + CallType$ + "*" + Clean$(Stk$[3]) + "_TYPE)("
  ELSEIF NOT NoTypeDeclare THEN
    Proto$ = "typedef " + FunType$ + " (" + CallType$ + "*BCXFPROT" + LTRIM$(STR$(DllCnt)) + ")("
  ELSE
    IF UseCProto THEN
      UseCProto = FALSE
      Proto$ = FunType$ + "  " + STRING$(pointer, ASC("*")) + SPC$ + CallType$ + Clean$(Stk$[3]) + "("
    ELSE
      Proto$ = "C_IMPORT " + FunType$ + "  " + STRING$(pointer, ASC("*")) + SPC$ + CallType$ + Clean$(Stk$[3]) + "("
    END IF
  END IF
  '-----------------------------------------------------
  argparse:
  '-----------------------------------------------------
  'Determine argument types
  '-----------------------------------------------------
  IF fp->NumArgs = 0 THEN
    '/***** 2010-11-15 Added code for constructor/destructor to remove VOID in CLASS DECLARATION -AIR *****/
    '/***** 2010-12-01 Added Use_VirtualUse_Virtual to support Abstract Classes -AIR *****/
    IF iMatchWrd(Stk$[2], "destructor") OR iMatchWrd(Stk$[2], "constructor") OR Use_Virtual THEN
      Proto$ = Proto$ + ")"
    ELSE
      Proto$ = Proto$ + "void)"
    END IF
  ELSE
    FOR ii = 0 TO fp->NumArgs - 1
      OptValue$ = ""
      AsType$   = ""
      AsArrys$  = ""
      pointer   = 0
      FoundAs   = 0
      DIM RAW FirstToken  = fp->CommaPos[ii] + 1
      DIM RAW LastToken   = fp->CommaPos[ii+1] - 1
      DIM RAW NumOfTokens = (LastToken - FirstToken) + 1
      i = INCHR(Stk$[FirstToken], "[")
      IF i THEN
        AsArrys$ = MID$(Stk$[FirstToken], i)
        Stk[FirstToken][i-1] = 0
      END IF
      IF NumOfTokens = 1 THEN
        '--------------------------------------------------------
        ' The bracket handling should be handled better.
        ' currently using the preprocessing of FunSubDecs1
        ' which converts A![] to *A! and A$[] to *A$[][2048]
        ' and A[] as xxx to A as xxx*
        '--------------------------------------------------------
        AsType$ = VarTypeLookup$[ INCHR(VarTypes$, RIGHT$(Stk$[FirstToken],1)) ]
        IF *AsArrys$ THEN
          REMOVE "*" FROM AsType$
        ELSE
          pointer = TALLY(Stk$[FirstToken], "*")
        END IF
        '--------------------------------------------------------
        FoundAs = TRUE
      ELSE
        FOR i = LastToken TO FirstToken STEP -1
          IF iMatchWrd(Stk$[i], "ptr") OR *Stk$[i] = ASC("*") THEN
            INCR pointer
          ELSEIF iMatchWrd(Stk$[i], "sub") THEN
            SepFuncArgs(fp->CommaPos[ii]+2, &fpp, TRUE)
            Proto$ = Proto$ + "void (*)("
            SubFunPtr = FoundAs = TRUE
            MakeDecProto(&fpp)
            SubFunPtr = FALSE
            EXIT FOR
          ELSEIF iMatchWrd(Stk$[i], "function") THEN
            SepFuncArgs(fp->CommaPos[ii]+2, &fpp, TRUE)
            IF AsType$ = "" THEN
              AsType$ = VarTypeLookup$[ INCHR( VarTypes$, RIGHT$(Stk$[FirstToken],1)) ]
            END IF
            Proto$ = Proto$ + RTRIM$(AsType$) + STRING$(pointer,ASC("*")) + " (*)("
            pointer = 0
            AsType$ = ""
            SubFunPtr = FoundAs = TRUE
            MakeDecProto(&fpp)
            SubFunPtr = FALSE
            EXIT FOR
          ELSEIF iMatchWrd(Stk$[i], "as") THEN
            IF AsType$ = "" THEN Abort("No type specified for argument" + STR$(ii+1))
            FoundAs = TRUE
            EXIT FOR
          ELSEIF *Stk$[i] = ASC("=") THEN
            OptFlag = FoundAs = TRUE
            OptValue$ = " =" + AsType$
            AsType$ = ""
            IF i = FirstToken + 1 THEN
              AsType$ = VarTypeLookup$[ INCHR( VarTypes$, RIGHT$(Stk$[FirstToken],1)) ]
              IF *AsArrys$ THEN
                REMOVE "*" FROM AsType$
              ELSE
                pointer = TALLY(Stk$[FirstToken], "*")
              END IF
              EXIT FOR
            END IF
          ELSE
            IF *Stk$[i] <> ASC(".") THEN
              AsType$ = Stk$[i] + SPC$ + AsType$
            ELSE
              IF *Stk$[i-1] = ASC(".") THEN
                IF OptFlag THEN Abort("Default value not allowed when using variable arguments")
                IF ii <> (fp->NumArgs-1) THEN Abort("Variable argument must be the last parameter")
                IF fp->NumArgs = 1 THEN Abort("Variable argument must be preceded by at least one other parameter")
                FoundAs = TRUE
              END IF
              AsType$ = Stk$[i] + AsType$
            END IF
          END IF
        NEXT i
      END IF
      IF NOT FoundAs THEN Abort("Malformed argument type in parameter" + STR$(ii + 1))
      IF ii <> fp->NumArgs AND OptFlag AND OptValue$ = "" THEN Warning("No default value specified for parameter" + STR$(ii + 1), 1)
      Proto$ = Proto$ + RTRIM$(AsType$) + AsArrys$ + STRING$(pointer,ASC("*")) + OptValue$ + Stk$[fp->CommaPos[ii+1]]
    NEXT ii
    '-----------------------------------------------------
  END IF
  FUNCTION = Proto
END SUB

SUB AsmUnknownStructs(CompArrays)
  DIM RAW InBrace  = 0
  DIM RAW InStruct = 0, i
  DIM RAW sztemp$
  FOR i = 2 TO Ndx
    ' --------------------------------
    ' Complete arrays
    ' --------------------------------
    IF CompArrays THEN
      IF Stk$[i] = "[" THEN
        sztemp$ = Stk$[i-1] : Stk$[i-1] = ""
        DO
          sztemp$ = sztemp$ + Stk[i]
          IF Stk$[i] = "]" THEN DECR InBrace
          IF Stk$[i] = "[" THEN INCR InBrace
          Stk$[i] = ""
          INCR i
        LOOP WHILE InBrace AND i <= Ndx
        Stk$[--i] = sztemp$
      END IF
    END IF
    ' --------------------------------
    ' Complete unknown struct members
    ' --------------------------------
    IF LEN(Stk$[i]) > 1 AND NOT IsNumber(Stk$[i]+1) THEN
      IF *Stk$[i] = ASC(".") OR iMatchLft(Stk$[i], "->") THEN
        IF InStruct = 0 THEN
          Stk$[i] = Stk$[i-1] + Stk$[i]
          Stk$[i-1] = ""
          InStruct = i
        ELSE
          CONCAT(Stk$[InStruct], Stk$[i])
          Stk$[i] = ""
        END IF
        ITERATE
      END IF
    END IF
    IF *Stk$[i] AND InStruct > 0 THEN
      '? STR$(ModuleLineNos[ModuleNdx]), Stk$[InStruct] , STR$(CompArrays)
      InStruct = 0
    END IF
  NEXT i
  CALL RemEmptyTokens
END SUB

SUB EmitIfCond(CondType$)
  '*********************************************************************
  ' Speedup/Optimize for statements like --->  if a$    = ""  THEN
  '               AND                    --->  if a$[1] = ""  THEN
  '*********************************************************************
  DIM RAW TestString, A, B, ParCnt, Tmp
  DIM RAW IsWhile = FALSE
  DIM RAW szTest$
  TestString = DataType(Stk$[2])
  IF TestString = vt_STRVAR THEN
    IF Stk$[4] = DDQ$ THEN
      Stk$[2] = Clean$(Stk$[2]) + "[0]"
      Stk$[4] = "0"
    ELSEIF Stk$[3] = "[" AND Stk$[7] = DDQ$ THEN
      Stk$[2] = Clean$(Stk$[2])
      CONCAT (Stk$[5],"[0]")
      Stk$[7] = "0"
    END IF
  END IF
  IF CondType$ = "while" THEN IsWhile = TRUE
  '********************   If, ElseIf, & While Handler   *********************
  FPRINT Outfile, Scoot$, CondType$, "(";
  Tmp = 2
  WHILE Stk$[Tmp] = "(" OR Stk$[Tmp] = "!"
    FPRINT Outfile, Stk$[Tmp];
    Tmp++
  WEND
  TestString = FALSE
  A = DataType(Stk$[Tmp])
  IF A = vt_STRLIT OR A = vt_STRVAR THEN
    IF Stk$[Tmp + 1] <> ")" AND NOT iMatchWrd(Stk$[Tmp+1], "then") THEN
      TestString  = TRUE
      Use_Str_Cmp = TRUE
      FPRINT Outfile, "str_cmp(";
    END IF
  END IF
  szTest$ = ""
  ParCnt  = 0
  DO
    IF TestString THEN
      IF Stk$[Tmp] = "=" THEN
        Stk$[Tmp] = ","
        szTest$   = ")==0"
        ParCnt    =  0
      ELSEIF Stk$[Tmp] = "!=" THEN
        Stk$[Tmp] = ","
        szTest$   = ")!=0"
        ParCnt    = 0
      ELSEIF Stk$[Tmp] = ">" THEN
        IF Stk$[Tmp + 1] = "=" THEN
          Stk$[Tmp] = ","
          szTest$   = ")>=0"
          Stk$[Tmp + 1] = ""
        ELSE
          Stk$[Tmp] = ","
          szTest$   = ")==1"
        END IF
        ParCnt = 0
      ELSEIF Stk$[Tmp] = "<" THEN
        IF Stk$[Tmp + 1] = "=" THEN
          Stk$[Tmp] = ","
          szTest$   = ")<=0"
          Stk$[Tmp + 1] = ""
        ELSE
          Stk$[Tmp] = ","
          szTest$   = ")==-1"
        END IF
        ParCnt = 0
      ELSEIF Stk$[Tmp] = "(" THEN
        ParCnt++
      ELSEIF Stk$[Tmp] = ")" THEN
        ParCnt--
      END IF
      IF Stk$[Tmp] = ")" AND szTest$ <> "" AND ParCnt < 0 THEN
        FPRINT Outfile, szTest$, Stk$[Tmp];
        szTest$ = ""
      ELSE
        IF Stk$[Tmp] = "||" OR Stk$[Tmp] = "&&" THEN
          Stk$[Tmp] = szTest$ + " " + Stk$[Tmp] + " "
          szTest$ = ""
          B = 1
          WHILE Stk$[Tmp + B] = "("
            CONCAT (Stk$[Tmp],"(")
            Stk$[Tmp + B] = ""
            B++
          WEND
          A = DataType(Stk$[Tmp+B]) ' look ahead
          IF (A = vt_STRLIT OR A = vt_STRVAR) AND Stk$[Tmp+B+1] <> ")" THEN
            CONCAT (Stk$[Tmp]," str_cmp(")
            Use_Str_Cmp = TRUE
          ELSE
            FPRINT Outfile,Clean$(Stk$[Tmp]);
            TestString = FALSE
            GOTO NxtToken
          END IF
        END IF
        FPRINT Outfile, Clean$(Stk$[Tmp]);
      END IF
    ELSE 'Not TestString
      IF Stk$[Tmp] = "||" OR Stk$[Tmp] = "&&" THEN
        B = 1
        WHILE Stk$[Tmp + B] = "("
          CONCAT (Stk$[Tmp], "(")
          Stk$[Tmp + B] = ""
          B++
        WEND
        A = DataType(Stk$[Tmp+B]) ' look ahead
        IF (A = vt_STRLIT OR A = vt_STRVAR) AND Stk$[Tmp+B+1] <> ")" THEN
          CONCAT (Stk$[Tmp],"str_cmp(" )
          TestString  = TRUE
          Use_Str_Cmp = TRUE
          szTest$     = ""
          ParCnt      = 0
          FPRINT Outfile, Clean$(Stk$[Tmp]);
          GOTO NxtToken
        END IF
      END IF
      IF Stk$[Tmp]= "!" THEN
        FPRINT Outfile,Stk$[Tmp];
      ELSE
        FPRINT Outfile,Clean$(Stk$[Tmp]);
      END IF
      IF Stk$[Tmp] = "=" THEN
        IF Stk$[Tmp-1] <> "<" AND Stk$[Tmp-1] <> ">" THEN
          IF Stk$[Tmp+1] <> ">" AND Stk$[Tmp+1] <> "<" THEN
            FPRINT Outfile,"=";
          END IF
        END IF
      END IF
    END IF
    NxtToken:
    INCR Tmp
    IF NOT IsWhile THEN
      IF iMatchWrd(Stk$[Tmp], "then") THEN
        EXIT LOOP
      ELSEIF Tmp > Ndx THEN
        Abort("If Without THEN")
      END IF
    END IF
  LOOP UNTIL Tmp > Ndx
  FPRINT Outfile, szTest$, ")"
  CALL BumpUp
  FPRINT Outfile, Scoot$, "{"
  CALL BumpUp
END SUB

SUB PrintGlobal(A, idx, Storage$, P$, VarName$, VarDim$)
  DIM RAW VAR$
  SELECT CASE A
    ' handle exceptions
    CASE vt_FILEPTR
    REMOVE "@" FROM VarName$
    FPRINT Outfile,Storage$;"FILE   *";P$;VarName$;VarDim$;";"
    CASE vt_UDT, vt_STRUCT, vt_UNION
    VAR$ = TypeDefs[GlobalVars[idx].VarDef].VarName$
    VAR$ = RPAD$(VAR$, 7)
    FPRINT Outfile,Storage$;VAR$;" ";P$;VarName$;VarDim$;";"
    CASE vt_BOOL
    FPRINT Outfile,Storage$;"bool    ";VarName$;VarDim$;";"
    CASE vt_STRVAR
    IF VarDim$ = "" THEN VarDim$ = "[65535]"
    FPRINT Outfile,Storage$;"char    ";P$;VarName$;VarDim$;";"
    ' handle normal
    CASE vt_VarMin TO vt_VarMax
    VAR$ = GetVarTypeName$(GlobalVars[idx].VarType)
    VAR$ = RPAD$(VAR$, 7)
    FPRINT Outfile,Storage$;VAR$;" ";P$;VarName$;VarDim$;";"
  END SELECT
END SUB

SUB ReDirectFPrint(TgtFile@, pat$, ...) 'Used primarily to bump gLinesWritten
  DIM RAW ap AS va_list
  IF DoCountLines AND TgtFile = FP3 THEN
    INCR gLinesWritten
  END IF
  va_start(ap, pat$)
  vfprintf(TgtFile, pat$, ap)
  va_end(ap)
END SUB

SET ReservedWord[] AS CHAR PTR
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
END SET

FUNCTION IsReservedWord(match$)
  DIM RAW mat$
  mat$ = UCASE$(match$)
  IF CONTAINEDIN(mat$,ReservedWord) = 0 THEN FUNCTION = 1
  FUNCTION = 0
END FUNCTION

FUNCTION GetAsPos()
  RAW i
  FOR i = Ndx TO 2 STEP -1
    IF iMatchWrd(Stk$[i],"as") THEN
      FUNCTION = i
    END IF
  NEXT
  FUNCTION = 0
END FUNCTION ' GetAsPos
