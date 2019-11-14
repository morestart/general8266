#include <Arduino.h>
#include "mqtt.h"
#include "processdata.h"


void subscribeTopic_()
{
  // 在这里订阅主题
  subscribeTopic("equipment_lease");
}

void processData(const char *topic, const char *data)
{
  // 数据处理
  Serial.println(data);
  Serial.println(topic);
  if (strcmp(data, "1") == 0)
  {
    sendOpenLockOrder(0x01);
  }
  else if (strcmp(data, "2") == 0)
  {
    sendOpenLockOrder(0x02);
  }
  
}

// 求校检位
int verify(int header, int borderAddress, int lockAddress, int status)
{
  int verifyCode;
  verifyCode = header ^ borderAddress;
  verifyCode = verifyCode ^ lockAddress;
  verifyCode = verifyCode ^ status;
  return verifyCode;
}

void sendOpenLockOrder(int lockAddress)
{
  // 发送开锁指令
  Serial.write(OPEN_LOCK_HEADER);
  Serial.write(BOARD_ADDRESS);
  Serial.write(lockAddress);
  Serial.write(OPEN_LOCK_STATUS);
  Serial.write(verify(OPEN_LOCK_HEADER, BOARD_ADDRESS, lockAddress, OPEN_LOCK_STATUS));
  Serial.println("发送数据完成");

  getSerialData(lockAddress);
  while(Serial.read() >= 0);
}

// // 查询当前锁状态
// void sendQueryLockStatusOrder(int lockAddress)
// {
//   Serial.write(LOCK_STATUS_HEADER);
//   Serial.write(BOARD_ADDRESS);
//   Serial.write(lockAddress);
//   Serial.write(QUERY_LOCK_STATUS);
//   Serial.write(verify(LOCK_STATUS_HEADER, BOARD_ADDRESS, lockAddress, QUERY_LOCK_STATUS));
// }

void getSerialData(int lockAddress)
{
  int buffer[4] = {0, 0, 0, 0};
  char buff[3];
  if (Serial.available())
  {
    if (Serial.read() == 0x8A)
    {
      // 板地址
      buffer[0] = Serial.read();
      // 锁地址
      buffer[1] = Serial.read();
      // 状态
      buffer[2] = Serial.read();
      // 校检
      buffer[3] = Serial.read();

      // 0x11 开 0x00 关
      if (buffer[2] == 0x11)
      {
        publishMessage(itoa(lockAddress, buff, 10), "isOpen");
      }
      else if (buffer[2] == 0x00)
      {
        publishMessage(itoa(lockAddress, buff, 10), "isClose");
      }
    }
  }
}
