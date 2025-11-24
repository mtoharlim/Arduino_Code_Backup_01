int LEDD0 = D0; // ขา D0
int LEDD1 = D1; // ขา D1
int LEDD2 = D2; // ขา D2
int LEDD3 = D3; // ขา D3
int LEDD4 = D4; // ขา D4
void setup() {
  Serial.begin(115200);
  pinMode(LEDD0, OUTPUT); // กำหนดการทำงานของขา D0 ให้เป็น Output
  pinMode(LEDD1, OUTPUT);
  pinMode(LEDD2, OUTPUT);
  pinMode(LEDD3, OUTPUT);
  pinMode(LEDD4, OUTPUT);

  digitalWrite(LEDD0, LOW);
  digitalWrite(LEDD1, LOW);
  digitalWrite(LEDD2, LOW);
  digitalWrite(LEDD3, LOW);
  digitalWrite(LEDD4, LOW);

}
void loop()
{
  digitalWrite(LEDD0, HIGH); // สั่งให้ ขา D0 ปล่อยลอจิก 1 ไฟ LED ติด
  delay(50); // หน่วงเวลา 50mS
  Serial.println("Setting readyForDHTUpdate to true");
  digitalWrite(LEDD1, HIGH); // สั่งให้ ขา D1 ปล่อยลอจิก 1 ไฟ LED ติด
  delay(50);
  digitalWrite(LEDD2, HIGH); // สั่งให้ ขา D2 ปล่อยลอจิก 1 ไฟ LED ติด
  delay(50);
  digitalWrite(LEDD3, HIGH); // สั่งให้ ขา D3 ปล่อยลอจิก 1 ไฟ LED ติด
  delay(50);
  digitalWrite(LEDD4, HIGH); // สั่งให้ ขา D4 ปล่อยลอจิก 1 ไฟ LED ติด
  delay(50);

}
