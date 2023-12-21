// Serial Interface
bool init();
string read();
bool write(string s);

// Sensor Interface
bool init();
float readTemperatureC();
float readHumidity();

// Display Interface
bool init();
bool setTemperatureValue(float f);
bool setHumidityValue(float f);
bool setDatetimeValue(string s);

// Time Interface
bool init();
bool setCurrentTime(uint32_t unixtime);
uint32_t getCurrentTime();

// Storage Interface
bool init();
bool writeFile(string filename, string dataJson);
string readFile(string filename);
bool deleteFile(string filename);
bool exists(string filename);

// Settings module
bool load(string settingFile);
bool store(string settingFile);
bool setInterval(uint32_t milliseconds);
uint32_t getInterval();
bool setTimezone(int8_t timezone);
int8_t getTimezone();

// Configurator module
string processCfgInput(string input);
