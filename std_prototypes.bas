  FPRINT Outfile,""
  FPRINT Outfile,"// *************************************************"
  FPRINT Outfile,"//               " + $BCX_STR_STD_PROTOS
  FPRINT Outfile,"// *************************************************"
  FPRINT Outfile,""
IF NoRT=FALSE THEN

  IF Use_Clng THEN
    FPRINT Outfile,"long    CLNG(double);"
  END IF
  IF Use_Cint THEN
    FPRINT Outfile,"int     Cint(double);"
  END IF
  IF Use_StartupCode THEN
    FPRINT Outfile,"int     BCX_StartupCode_(void);"
  END IF
  IF Use_ExitCode THEN
    FPRINT Outfile,"int     BCX_ExitCode_(void);"
  END IF
  IF Use_Str_Cmp THEN
    FPRINT Outfile,"int     str_cmp(char*, char*);"
  END IF
  IF Use_Eof THEN
    FPRINT Outfile,"int     EoF (FILE*);"
  END IF
  IF Use_CopyFile THEN
    FPRINT Outfile,"void    CopyFile (char *,char *,int=FALSE);"
  END IF

  IF Use_QBColor THEN
    FPRINT Outfile,"int     qbcolor (int);"
  END IF
  IF Use_Cls THEN
    FPRINT Outfile,"void    cls(void);"
  END IF
  IF Use_Color THEN
    FPRINT Outfile,"void    color (int,int);"
  END IF
  IF Use_Locate THEN
    FPRINT Outfile,"void    locate (int,int,int=1,int=12);"
  END IF
  IF Use_Run THEN
    FPRINT Outfile,"int     Run (char*, int =1, int =0);"
  END IF
  IF Use_Randomize THEN
    FPRINT Outfile,"void    randomize (unsigned int);"
  END IF
  IF Use_Midstr THEN
    FPRINT Outfile,"void    midstr (char*, int, int, char *);"
  END IF
  IF Use_Swap THEN
    FPRINT Outfile,"void    swap (UCHAR*,UCHAR*,int);"
  END IF

  IF UseFlag THEN
    FPRINT Outfile,"char*   BCX_TmpStr(size_t);"
  END IF

  IF Use_sziif THEN
    FPRINT Outfile,"char*   sziif (bool,char*,char*);"
  END IF
  IF Use_Using THEN
    FPRINT Outfile,"char*   Using (char*,double);"
  END IF
  IF Use_TempFileName THEN
    FPRINT Outfile,"char*   TempFileName (char*,char*);"
  END IF
  IF Use_AppExePath THEN
    FPRINT Outfile,"char*   AppExePath (void);"
  END IF
  IF Use_AppExeName THEN
    FPRINT Outfile,"char*   AppExeName (void);"
  END IF
  IF Use_Lcase THEN
    FPRINT Outfile,"char*   lcase (char*);"
  END IF
  IF Use_Ucase THEN
    FPRINT Outfile,"char*   ucase (char*);"
  END IF
  IF Use_Mid THEN
    FPRINT Outfile,"char*   mid (char*, int, int=-1);"
  END IF
  IF Use_Ltrim THEN
    FPRINT Outfile,"char*   ltrim (char*,char=32);"
  END IF
  IF Use_Rtrim THEN
    FPRINT Outfile,"char*   rtrim (char*,char=32);"
  END IF
  IF Use_Trim THEN
    FPRINT Outfile,"char*   trim (char*);"
  END IF
  IF Use_Strim THEN
    FPRINT Outfile,"char*   strim   (char*);"
  END IF
  IF Use_Left THEN
    FPRINT Outfile,"char*   left (char*,int);"
  END IF
  IF Use_Right THEN
    FPRINT Outfile,"char*   right (char*,int);"
  END IF
  IF Use_Rpad THEN
    FPRINT Outfile,"char*   rpad (char*,int,int=32);"
  END IF
  IF Use_Lpad THEN
    FPRINT Outfile,"char*   lpad (char*,int,int=32);"
  END IF
  IF Use_String THEN
    FPRINT Outfile,"char*   stringx (int,int);"
  END IF
  IF Use_Repeat THEN
    FPRINT Outfile,"char*   repeat (int,char*);"
  END IF
  IF Use_Extract THEN
    FPRINT Outfile,"char*   extract (char*,char*);"
  END IF
  IF Use_Remain THEN
    FPRINT Outfile,"char*   remain (char*,char*);"
  END IF
  IF Use_Reverse THEN
    FPRINT Outfile,"char*   reverse (char*);"
  END IF
  IF Use_Command THEN
    FPRINT Outfile,"char*   command (int=-1);"
  END IF
  IF Use_Mcase THEN
    FPRINT Outfile,"char*   mcase (char*);"
  END IF
  IF Use_Replace THEN
    FPRINT Outfile,"char*   replace (char*,char*,char*);"
  END IF
  IF Use_iReplace THEN
    FPRINT Outfile,"char*   iReplace (char*,char*,char*);"
  END IF
  IF Use_Shell THEN
    FPRINT Outfile,"void    Shell (char *);"
  END IF
  IF Use_Space THEN
    FPRINT Outfile,"char*   space (int a);"
  END IF
  IF Use_Str THEN
    FPRINT Outfile,"char*   str (double);"
  END IF
  IF Use_Strl THEN
    FPRINT Outfile,"char*   strl (long double);"
  END IF
  IF Use_Findfirst THEN
    FPRINT Outfile,"char*   findfirst (char*, FILE_FIND_DATA*);"
  END IF
  IF Use_Findnext THEN
    FPRINT Outfile,"char*   findnext (FILE_FIND_DATA*);"
  END IF
  IF Use_Curdir THEN
    FPRINT Outfile,"char*   curdir (void);"
  END IF

  IF Use_Sysdir THEN
    FPRINT Outfile,"char*   sysdir (void);"
  END IF
  IF Use_Tempdir THEN
    FPRINT Outfile,"char*   tempdir (void);"
  END IF
  IF Use_Environ THEN
    FPRINT Outfile,"char*   Environ (char*);"
  END IF
  IF Use_Boolstr THEN
    FPRINT Outfile,"char*   BoolStr (int);"
  END IF
  IF Use_Hex THEN
    FPRINT Outfile,"char*   hex (int);"
  END IF
  IF Use_Bin THEN
    FPRINT Outfile,"char*   Bin (int);"
  END IF
  IF Use_Oct THEN
    FPRINT Outfile,"char*   oct (int);"
  END IF
  IF Use_Now THEN
    FPRINT Outfile,"char*   now (void);"
  END IF
  IF Use_SearchPath THEN
    FPRINT Outfile,"char*   SEARCHPATH (char *);"
  END IF
  IF Use_StrUpLow THEN
    FPRINT Outfile,"char*   _strupr_(char *);"
    FPRINT Outfile,"char*   _strlwr_(char *);"
  END IF
  IF Use_BcxSplitPath THEN
    FPRINT Outfile,"char*   BcxSplitPath (char *, int);"
    FPRINT Outfile,"void    _splitpath_(const char* path, char* drv, char* dir, char* name, char* ext);"
  END IF

  IF Use_Strtoken THEN
    FPRINT Outfile,"char*   StrToken (char*,char*,int);"
  END IF
  IF Use_FileLocked THEN
    FPRINT Outfile,"int    FileLocked (char*);"
  END IF
  IF Use_FillArray THEN
    FPRINT Outfile,"int     fillarray (char *, int, int, void *);"
  END IF
  IF Use_Remove THEN
    FPRINT Outfile,"char*   RemoveStr (char*,char*);"
  END IF
  IF Use_IRemove THEN
    FPRINT Outfile,"char*   IRemoveStr (char*,char*);"
  END IF
  IF Use_Time THEN
    FPRINT Outfile,"char*   timef (int i=0);"
  END IF
  IF Use_Join THEN
    FPRINT Outfile,"char*   join (int, ... );"
  END IF
  IF Use_Enclose THEN
    FPRINT Outfile,"char*   enc (char*, int=0, int=0);"
  END IF
  IF Use_Chr THEN
    FPRINT Outfile,"char*   chr";
    FPRINT Outfile,"(int,int=0,int=0,int=0,int=0,int=0,int=0,int=0,int=0,int=0);"
  END IF
  IF Use_VChr THEN
    FPRINT Outfile,"char*   vchr (int,...);"
  END IF
  IF Use_Freefile THEN
    FPRINT Outfile,"FILE*   FreeFile (void);"
  END IF
  IF Use_PeekStr THEN
    FPRINT Outfile,"char*   peekstr (LPVOID,int);"
  END IF
  IF Use_Asc THEN
    FPRINT Outfile,"int     asc (char*,int=0);"
  END IF
  IF Use_Instrrev THEN
    FPRINT Outfile,"int     InstrRev (char*,char*,int=0,int=0);"
  END IF
  IF Use_Instr THEN
    FPRINT Outfile,"int     instr_b(char*,char*,int=0,int=0);"
  END IF
  IF UseLCaseTbl THEN
    FPRINT Outfile,"char    *MakeLCaseTbl(void);"
  END IF
  IF Use_Stristr THEN
    FPRINT Outfile,"char    *_stristr_(char*,char*);"
  END IF
  IF Use_StrStr THEN
    FPRINT Outfile,"char    *_strstr_(char*,char*);"
  END IF
  IF Use_Verify THEN
    FPRINT Outfile,"int     Verify (char *, char *);"
    FPRINT Outfile,"int     VerifyInstr(char*,char*,int=0);"
  END IF
  IF Use_Retain THEN
    FPRINT Outfile,"char*   Retain (char*,char *);"
  END IF
  IF Use_LoadFile THEN
    FPRINT Outfile,"char*   LoadFile (char*);"
  END IF
  IF Use_Inchr THEN
    FPRINT Outfile,"int     inchr (char*,char*);"
  END IF
  IF Use_Idxqsort THEN
    FPRINT Outfile,"int     IdxCompare (const void *,const void *);"
  END IF
  IF Use_IdxqsortSt THEN
    FPRINT Outfile,"int     IdxCompareSt (const void *,const void *);"
  END IF
  IF Use_PtrqsortSt THEN
    FPRINT Outfile,"int     PtrCompareSt (const void *,const void *);"
  END IF
  IF Use_Strqsorta THEN
    FPRINT Outfile,"int     StrCompareA (const void *,const void *);"
  END IF
  IF Use_Strqsortd THEN
    FPRINT Outfile,"int     StrCompareD (const void *,const void *);"
  END IF
  IF Use_DynStrqsorta THEN
    FPRINT Outfile,"int     DynStrCompareA (const void *,const void *);"
  END IF
  IF Use_DynStrqsortd THEN
    FPRINT Outfile,"int     DynStrCompareD (const void *,const void *);"
  END IF
  IF Use_Numqsortaint THEN
    FPRINT Outfile,"int     NumCompareAint (const void *,const void *);"
  END IF
  IF Use_Numqsortdint THEN
    FPRINT Outfile,"int     NumCompareDint (const void *,const void *);"
  END IF
  IF Use_Numqsortafloat THEN
    FPRINT Outfile,"int     NumCompareAfloat (const void *,const void *);"
  END IF
  IF Use_Numqsortdfloat THEN
    FPRINT Outfile,"int     NumCompareDfloat (const void *,const void *);"
  END IF
  IF Use_Numqsortadouble THEN
    FPRINT Outfile,"int     NumCompareAdouble (const void *,const void *);"
  END IF
  IF Use_Numqsortddouble THEN
    FPRINT Outfile,"int     NumCompareDdouble (const void *,const void *);"
  END IF
  IF Use_Like THEN
    FPRINT Outfile,"int     like (char*,char*);"
  END IF
  IF Use_Tally THEN
    FPRINT Outfile,"int     tally (char*,char*,int=0);"
  END IF
  IF Use_Inkey THEN
    FPRINT Outfile,"char*   inkey (void);"
  END IF
  IF Use_InkeyD THEN
    FPRINT Outfile,"int     inkeyd (void);"
  END IF
  '/***** 2010-12-08  Added to support INSTAT-AIR *****/
  IF Use_Instat THEN
    FPRINT Outfile,"int		kbhit(void);"
  END IF
  IF Use_GetCh THEN
    FPRINT Outfile,"int     _getch_(int);"
  END IF
  IF Use_Bin2dec THEN
    FPRINT Outfile,"int     Bin2Dec (char*);"
  END IF
  IF Use_Hex2Dec THEN
    FPRINT Outfile,"int     Hex2Dec (char*);"
  END IF
  IF Use_Download THEN
    FPRINT Outfile,"int     Download (char*,char*);"
  END IF

  IF Use_Embed THEN
    FPRINT Outfile,"char*   GetResource (int* );"
  END IF

  IF Use_Exist THEN
    IF Use_Osx THEN
        FPRINT Outfile,"bool    Exist   (char*);"
    ELSE
        FPRINT Outfile,"BOOL    Exist   (char*);"
    END IF

  END IF
  IF Use_Ins THEN
    FPRINT Outfile,"char*   ins (char *S, int i, char *a);"
  END IF
  IF Use_Del THEN
    FPRINT Outfile,"char*   del (char*,int,int);"
  END IF
  IF Use_Pause THEN
    FPRINT Outfile,"void    Pause (void);"
  END IF
  IF Use_Keypress THEN
    FPRINT Outfile,"int     keypress (void);"
  END IF
  IF Use_Lof THEN
    FPRINT Outfile,"DWORD   lof (char*);"
  END IF
  IF Use_Sgn THEN
    FPRINT Outfile,"double  sgn (double);"
  END IF
  IF Use_Round THEN
    FPRINT Outfile,"double  Round (double,int);"
  END IF
  IF Use_Rnd THEN
    FPRINT Outfile,"float   rnd (void);"
  END IF
  IF Use_Exp THEN
    FPRINT Outfile,"double  Exp (double);"
  END IF
  IF Use_Min THEN
    FPRINT Outfile,"double  _MIN_ (double,double);"
  END IF
  IF Use_Max THEN
    FPRINT Outfile,"double  _MAX_ (double,double);"
  END IF
  IF Use_Timer THEN
    FPRINT Outfile,"float   timer (void);"
  END IF
  IF Use_Iif THEN
    FPRINT Outfile,"double  iif (bool,double,double);"
  END IF
  IF Use_Loc THEN
    FPRINT Outfile,"int     loc (FILE *fp, int fplen);"
  END IF
  IF Use_Rec THEN
    FPRINT Outfile,"int     rec (FILE *fp, int fplen);"
  END IF
  IF Use_RecCount THEN
    FPRINT Outfile,"int     reccount (FILE *fp, int fplen);"
  END IF
  IF Use_Scan THEN
    FPRINT Outfile,"int     scan (char *input, char *format, ... );"
  END IF
  IF Use_Split THEN
    FPRINT Outfile,"int     Split (char [][65535], char*, char*, int=0);"
  END IF
  IF Use_DSplit THEN
    FPRINT Outfile,"int     DSplit (PCHAR *, char*, char*, int=0);"
  END IF
  IF Use_SysStr THEN
    FPRINT Outfile,"BSTR    SysStr (char * szIn, int=0, int=0);"
  END IF
  IF Use_WideToAnsi THEN
    FPRINT Outfile,"char*   WideToAnsi (wchar_t *, UINT=0, DWORD=0);"
  END IF
  IF Use_AnsiToWide THEN
    FPRINT Outfile,"wchar_t* AnsiToWide (char*,UINT=0,DWORD=0);"
  END IF
  IF Use_Cvi THEN
    FPRINT Outfile,"short   CVI (char*);"
  END IF
  IF Use_Mki THEN
    FPRINT Outfile,"char*   MKI (short);"
  END IF
  IF Use_Cvl THEN
    FPRINT Outfile,"long    CVL (char*);"
  END IF
  IF Use_Mkl THEN
    FPRINT Outfile,"char*   MKL (int);"
  END IF
  IF Use_Cvs THEN
    FPRINT Outfile,"float   CVS (char*);"
  END IF
  IF Use_Mks THEN
    FPRINT Outfile,"char*   MKS (float);"
  END IF
  IF Use_Cvd THEN
    FPRINT Outfile,"double  CVD (char*);"
  END IF
  IF Use_Cvld THEN
    FPRINT Outfile,"long double  CVLD (char*);"
  END IF
  IF Use_Mkd THEN
    FPRINT Outfile,"char*   MKD (double);"
  END IF
  IF Use_Mkld THEN
    FPRINT Outfile,"char*   MKLD (long double);"
  END IF
  IF Use_OSVersion THEN
    FPRINT Outfile,"int     OSVersion (void);"
  END IF
  IF Use_Dynacall THEN
    FPRINT Outfile,"HINSTANCE BCX_LoadDll(char *);"
    FPRINT Outfile,"void    BCX_UnloadDll(void);"
    FPRINT Outfile,"typedef int (CALLBACK *DYNACALL1)(void);"
    FPRINT Outfile,"int     BCX_DynaCall(char *, char *, int, ...);"
  END IF
  IF Use_DynamicA THEN
    FPRINT Outfile,"void*   CreateArr (void*,int,int,int,...);"
    FPRINT Outfile,"void*   CreateArr_internal(void*, int, int, int, va_list);"
    FPRINT Outfile,"void    DestroyArr (void**,int,int);"
  END IF
  IF Use_ContainedIn THEN
    FPRINT Outfile,"int     containedin(char * ,char **,int=0);"
  END IF
  IF Use_FindInType THEN
    FPRINT Outfile,"int     FindInType(char *,char *,int,int,int,int=0,int* =0);"
  END IF
  IF Use_SingleFile = FALSE THEN
    OPEN HFile$ FOR OUTPUT AS fpHFile
  END IF

  '/***** 2010-11-10 emit wxApp Class Definition - AIR *****/
  /***** 2010-11-24 Change TO NOT emit wxApp CLASS Definition FOR WX CONSOLE Apps -AIR *****/
  '/***** 2010-12-01  Switched to using BCXSPLITPATH$ per James Fuller's suggestion -AIR *****/
  IF Use_Wx THEN
    FPRINT Outfile,""
    FPRINT Outfile,"class ";bcxsplitpath$(FileIn$, FNAME);": public wxApp {"
    FPRINT Outfile,"  public:"
    FPRINT Outfile,"	virtual bool OnInit();"
    FPRINT Outfile,"};"
    FPRINT Outfile,""
    FPRINT Outfile,"IMPLEMENT_APP(";bcxsplitpath$(FileIn$, FNAME);")"
    FPRINT Outfile,""
  END IF

	'/***** 2010-12-10  Socket Support -AIR *****/
	if Use_Socket then
		FPRINT Outfile,""
		FPRINT Outfile,"sockaddr_in sock_addr (char* ,int=80);"
		FPRINT Outfile,"int     connect_socket (sockaddr_in);"
		FPRINT Outfile,"int     BcxSocket (char* ,int=80);"
		FPRINT Outfile,"int     BcxSocketSend (int, char *);"
		FPRINT Outfile,"int     BcxSocketRead (int, char *);"
		FPRINT Outfile,"void    BcxSocketClose(int);"
		FPRINT Outfile,""
	end if

    '/***** 2013-06-26 New REGEX Keywords -AIR *****/
    IF Use_RegEx then
        FPRINT Outfile,"bool    regmatch (char *, char *, REGEX* );"
    END IF

END IF 'IF NoRT=FALSE