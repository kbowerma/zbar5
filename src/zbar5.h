#define FILENAME "zbar5.cpp"
#define MYVERSION "2.2"
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
  int ledConfig(String command);
  int setConfig1(String command);
  int setConfig2(String command);
  void juiceLeds(int stripId, int ured, int ugreen,int ublue, int uwhite); 
  void juiceLeds1(int ured, int ugreen,int ublue, int uwhite); 
  void juiceLeds2(int ured, int ugreen,int ublue, int uwhite); 
  void juiceSection(int startled, int endled, int ured, int ugreen,int ublue, int uwhite);
  void myHandler(const char *event, const char *data);