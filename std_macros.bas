  FPRINT Outfile,""
  FPRINT Outfile,"// *************************************************"
  FPRINT Outfile,"//               " + $BCX_STR_STD_MACROS
  FPRINT Outfile,"// *************************************************"
  FPRINT Outfile,""

  IF Use_BcxSplitPath THEN
    FPRINT Outfile,"#define FDRV   2"
    FPRINT Outfile,"#define FPATH  4"
    FPRINT Outfile,"#define FNAME  8"
    FPRINT Outfile,"#define FEXT  16"
  END IF

  IF Use_Cbool THEN
    FPRINT Outfile,"#define CBOOL(A)(A!=0)?1:0"
  END IF

  IF Use_Isptr THEN
    FPRINT Outfile,"#define IsPtr(a)((DWORD)a)"
  END IF

  IF Use_Band THEN
    FPRINT Outfile,"#define BAND &"
  END IF

  IF Use_Bor THEN
    FPRINT Outfile,"#define BOR |"
  END IF

  IF Use_Bnot THEN
    FPRINT Outfile,"#define BNOT ~(int)"
  END IF

  IF Use_Ubound THEN
    FPRINT Outfile,"#define ubound(T)(sizeof((T))/sizeof((T[0]))-1)"
  END IF

  IF Use_Clear THEN
    FPRINT Outfile,"#define Clear(arg)memset(&arg,0,sizeof(arg))"
  END IF

  IF Use_Imod THEN
    FPRINT Outfile,"#define imod(a,b)((a)%(b))"
  END IF

  IF Use_Get THEN
    FPRINT Outfile,"#define GET(A,B,C) F_GetVal=fread(B,1,C,A)"
    CALL AddGlobal("F_GetVal", vt_INTEGER , 0,"",0,0,0,0)
  END IF

  IF Use_Put THEN
    FPRINT Outfile,"#define PUT(A,B,C) F_PutVal=fwrite(B,1,C,A)"
    CALL AddGlobal("F_PutVal", vt_INTEGER , 0,"",0,0,0,0)
  END IF

  IF Use_Strptr THEN
    FPRINT Outfile,"#define STRPTR(A)((char*)&(A))"
  END IF

  IF Use_Val THEN
    FPRINT Outfile,"#define VAL(a)(double)atof(a)"
  END IF

  IF Use_Vall THEN
    FPRINT Outfile,"#define VALL(a) (long double)strtold(a,(char**)NULL)"
  END IF

  IF Use_Fint THEN
    FPRINT Outfile,"#define FINT(a)floor(a)"
  END IF

  IF Use_Frac THEN
    FPRINT Outfile,"#define FRAC(a)(double)(a-FIX(a))"
    Use_Fix = TRUE
  END IF

  IF Use_Fracl THEN
    FPRINT Outfile,"#define FRACL(a)(long double)(a-FIX(a))"
    Use_Fix = TRUE
  END IF

  IF Use_Fix THEN
    FPRINT Outfile,"#define FIX(a)(int)((a))"
  END IF

  IF Use_Csng THEN
    FPRINT Outfile,"#define CSNG(a)((float)(a))"
  END IF

  IF Use_Cdbl THEN
    FPRINT Outfile,"#define CDBL(a)((double)(a))"
  END IF

  IF Use_Cldbl THEN
    FPRINT Outfile,"#define CLDBL(a)((long double)(a))"
  END IF

  IF Use_Threads THEN
    FPRINT Outfile,"#define BCX_THREAD(fn,arg)   ({ pthread_t tid; pthread_create(&tid, NULL, (void*(*)(void*))fn, arg); tid;})"
    FPRINT Outfile,"#define BCX_THREADWAIT(a)    pthread_join(a, NULL)"
    FPRINT Outfile,"#define BCX_INITLOCK(a)      pthread_mutex_init(a, NULL)"
    FPRINT Outfile,"#define BCX_THREADLOCK(a)    pthread_mutex_lock (a)"
    FPRINT Outfile,"#define BCX_THREADUNLOCK(a)  pthread_mutex_unlock (a)"
    FPRINT Outfile,"#define BCX_THREADKILL(t)    pthread_cancel(t)"
    FPRINT Outfile,"#define BCX_THREADEND        pthread_exit(0)"
  END IF
