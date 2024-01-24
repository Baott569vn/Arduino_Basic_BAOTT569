#include <Servo.h>

const int servoPin1 = 18;
const int servoPin2 = 17;
const int servoPin3 = 16;

Servo servo1;
Servo servo2;
Servo servo3;

void setup()
{
    Serial.begin(115200);
    servo1.attach(servoPin1, 500, 2400);
    servo2.attach(servoPin2, 500, 2400);
    servo3.attach(servoPin3, 500, 2400);
}

int pos = 0;

struct RobotArm
{
    double jointStatic[3] = {};
    double jointLast[3] = {};

    // Hàm khởi tạo
    RobotArm(double x, double y, double z) : jointStatic{x, y, z} {}

    void moveArm(double newX, double newY, double newZ)
    {
        if (isValidAngle(newX) && isValidAngle(newY) && isValidAngle(newZ))
        {
            jointLast[0] = newX;
            jointLast[1] = newY;
            jointLast[2] = newZ;
            angle_Arm();
        }
        else
        {
            Serial.println("Invalid joint angles. Please provide angles within the range (-180 to 180) degrees.");
        }
    }

    // kiểm tra xem có trong khoảng -180 đến 180 không
    bool isValidAngle(double angle)
    {
        return (angle >= 0 && angle <= 180.0);
    }

    void printInfo()
    {
        Serial.print("Truc_X : ");
        Serial.print(jointStatic[0]);
        Serial.print(" Do");
        Serial.print("Truc_Y : ");
        Serial.print(jointStatic[1]);
        Serial.print(" Do");
        Serial.print("Truc_Z : ");
        Serial.print(jointStatic[2]);
        Serial.print(" Do");
        Serial.println("\n");
    }

    // Hàm xử lý khi cánh tay di chuyển
    void angle_Arm()
    {
        Serial.println("DANG DI CHUYEN...");

        // Độ trễ 100 giây
        // delay(100);

        const double epsilon = 0.1; // Ngưỡng chấp nhận được

        while (true)
        {
            bool allClose = true;

            for (int i = 0; i < sizeof(jointLast) / sizeof(jointLast[0]); ++i)
            {
                jointLast[i] <= jointStatic[i] ? jointStatic[i] -= 0.1 : 0;
                jointLast[i] >= jointStatic[i] ? jointStatic[i] += 0.1 : 0;

                servo1.write(jointStatic[0]);
                servo2.write(jointStatic[1]);
                servo3.write(jointStatic[2]);
                // Kiểm tra xem giá trị có gần bằng nhau không
                if (abs(jointStatic[i] - jointLast[i]) > epsilon)
                { // VD:jointStatic = 5.1 - jointLast = 5.0 = 0.1 thi thoat
                    allClose = false;
                }
                // delay(2);
            }
            // Nếu tất cả các giá trị đều gần bằng nhau, thoát khỏi vòng lặp
            if (allClose)
            {
                break;
            }

            // In thông tin về vị trí cánh tay sau mỗi bước di chuyển
            // printInfo();

            // // Độ trễ 2 mili giây giữa các bước di chuyển
            // this_thread::sleep_for(chrono::milliseconds(1));
        }
        printInfo();
        Serial.println("VI TRI MOI.");
    }
};

void loop()
{
    RobotArm robotArm(0.0, 0.0, 0.0);
    robotArm.printInfo();
    // Di chuyển cánh tay đến một vị trí mới
    robotArm.moveArm(180.0, 60.0, 80.0);
    robotArm.printInfo();
    // Di chuyển cánh tay đến một vị trí mới
    robotArm.moveArm(60.0, 60.0, 60.0);
    robotArm.printInfo();
    // Di chuyển cánh tay đến một vị trí mới
    robotArm.moveArm(180.0, 180.0, 180.0);
    robotArm.printInfo();
}
 