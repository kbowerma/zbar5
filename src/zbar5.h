#define FILENAME "zbar5.cpp"
#define MYVERSION "from zbar2"
#define BUILD_DATE "8/15/23"
#define CONFIGADDR 10
#define MYFIRMWARE "argon_4.10"

struct MyConfig {
    bool D2Armed;
    bool gestureArmed;
    char version[16];
    int awayHoldTMR;
};

// Prototypes for local build, ok to leave in for Build IDE
  int setConfig1(String command);
  void juiceLeds1(int ured, int ugreen,int ublue, int uwhite); 
  int setConfig2(String command);
  void juiceLeds2(int ured, int ugreen,int ublue, int uwhite); 
  void juiceSection(int startled, int endled, int ured, int ugreen,int ublue, int uwhite);
  void myHandler(const char *event, const char *data);