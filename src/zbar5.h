#define FILENAME "zbar5.cpp"
#define MYVERSION "4.0"
#define BUILD_DATE "9/1/23"
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
  void juiceLeds(int stripId, int ured, int ugreen,int ublue, int uwhite); 
  void myHandler(const char *event, const char *data);
  void ledhandler(const char *event, const char *data);