#ifndef PROCESSDATA_H
#define PROCESSDATA_H

/*公共参数*/
#define BOARD_ADDRESS 0x01

/*查询锁状态指令*/ 
#define LOCK_STATUS_HEADER 0x80
#define QUERY_LOCK_STATUS 0x33


/*开锁指令*/ 
#define OPEN_LOCK_HEADER 0x8A
#define OPEN_LOCK_STATUS 0x11


void processData(const char* topic, const char* data);
int verify(int header, int borderAddress, int lockAddress, int status);
void sendOpenLockOrder(int lockAddress);
// void sendQueryLockStatusOrder(int lockAddress);
void getSerialData(int lockAddress);
void subscribeTopic_();

#endif