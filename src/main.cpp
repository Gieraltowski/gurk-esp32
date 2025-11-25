#include <Arduino.h>
#include <SPIFFS.h>
#include <stdio.h>

void execute(File);

bool programExecuted = false;

void setup()
{
  Serial.begin(115200);
  
  if (!SPIFFS.begin(true))
  {
    Serial.println("SPIFFS not initialized");
    return;
  }

  if (!programExecuted) {
    File programFile = SPIFFS.open("/main.bin");
    if (programFile)
    {
      execute(programFile);
      programFile.close();
      programExecuted = true;
    }
  }
}

void loop()
{
}

void execute(File file)
{
  size_t fileSize = file.size();
  if (fileSize == 0)
  {
    return;
  }

  uint8_t *code = new uint8_t[fileSize];

  if (file.read(code, fileSize) != fileSize)
  {
    delete[] code;
    return;
  }

  uint32_t memory[1024] = {0};
  uint32_t registers[16] = {0};
  bool carry = false;
  bool overflow = false;

  size_t instructionCount = fileSize / 8;

  for (size_t i = 0; i < instructionCount * 8; i += 8)
  {
    uint16_t operation = (code[i + 1] << 8) | code[i];
    uint16_t first_value = (code[i + 3] << 8) | code[i + 2];
    uint16_t second_value = (code[i + 5] << 8) | code[i + 4];
    uint16_t third_value = (code[i + 7] << 8) | code[i + 6];

    switch (operation)
    {
    case 0x0000:
      delete[] code;
      return;
      break;

    case 0x0001:
    {
      int rdest = first_value & 0xF;
      int rsrc = second_value & 0xF;
      registers[rdest] = registers[rsrc];
      break;
    }

    case 0x0002:
    {
      int rdest = first_value & 0xF;
      uint32_t value = ((uint32_t)second_value << 16) | third_value;
      registers[rdest] = value;
      break;
    }

    case 0x0003:
    {
      int rdest = first_value & 0xF;
      int memaddress = second_value;
      if (memaddress < 1024)
      {
        registers[rdest] = memory[memaddress];
      }
      break;
    }

    case 0x0004:
    {
      int memaddress = first_value;
      uint32_t value = ((uint32_t)second_value << 16) | third_value;
      if (memaddress < 1024)
      {
        memory[memaddress] = value;
      }
      break;
    }

    case 0x0005:
    {
      int rdest = first_value & 0xF;
      int rsrc0 = second_value & 0xF;
      int rsrc1 = third_value & 0xF;
      uint32_t result = registers[rsrc0] + registers[rsrc1];
      overflow = (result < registers[rsrc0]);
      carry = overflow;
      registers[rdest] = result;
      break;
    }

    case 0x0006:
    {
      int rdest = first_value & 0xF;
      int rsrc0 = second_value & 0xF;
      int rsrc1 = third_value & 0xF;
      uint32_t result = registers[rsrc0] - registers[rsrc1];
      overflow = (result > registers[rsrc0]);
      carry = overflow;
      registers[rdest] = result;
      break;
    }

    case 0x0007:
    {
      int rdest = first_value & 0xF;
      int rsrc0 = second_value & 0xF;
      int rsrc1 = third_value & 0xF;
      uint64_t result = (uint64_t)registers[rsrc0] * (uint64_t)registers[rsrc1];
      overflow = (result > 0xFFFFFFFF);
      carry = overflow;
      registers[rdest] = (uint32_t)result;
      break;
    }

    case 0x0008:
    {
      int rdest = first_value & 0xF;
      int rsrc0 = second_value & 0xF;
      int rsrc1 = third_value & 0xF;
      if (registers[rsrc1] != 0) {
        uint32_t result = registers[rsrc0] / registers[rsrc1];
        registers[rdest] = result;
        carry = false;
        overflow = false;
      }
      break;
    }

    case 0x0009:
    {
      int rdest = first_value & 0xF;
      int rsrc0 = second_value & 0xF;
      int rsrc1 = third_value & 0xF;
      registers[rdest] = registers[rsrc0] & registers[rsrc1];
      carry = false;
      overflow = false;
      break;
    }

    case 0x000A:
    {
      int rdest = first_value & 0xF;
      int rsrc0 = second_value & 0xF;
      int rsrc1 = third_value & 0xF;
      registers[rdest] = registers[rsrc0] | registers[rsrc1];
      carry = false;
      overflow = false;
      break;
    }

    case 0x000B:
    {
      int rdest = first_value & 0xF;
      int rsrc0 = second_value & 0xF;
      int rsrc1 = third_value & 0xF;
      registers[rdest] = registers[rsrc0] ^ registers[rsrc1];
      carry = false;
      overflow = false;
      break;
    }

    case 0x0022:
    {
      switch (registers[7])
      {
        case 0x0048:
        {
          long baud = registers[8];
          uint8_t rxpin = registers[9];
          uint8_t txpin = registers[10];

          delay(1000);
          break;
        }
        case 0x0049:
        {
          int ptr = registers[8];
          int len = registers[9];

          for(int j = 0; j < len; j++)
          {
            int word_index = ptr / 4;
            int byte_offset = ptr % 4;
            uint32_t word = memory[word_index];
            uint8_t data = (word >> (byte_offset * 8)) & 0xFF;
            Serial.write(data);
            ptr++;
          }

          Serial.flush();

          registers[0] = len;
          break;
        }
      }
      break;
    }

    default:
      break;
    }
  }

  delete[] code;
}