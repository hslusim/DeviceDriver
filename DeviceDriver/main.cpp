#include "gmock/gmock.h"
#include "device_driver.h"

using namespace testing;

class MockFlashMemoryDevice : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};


TEST(TS, TC1) {
	MockFlashMemoryDevice mockHW;
	DeviceDriver dd{ &mockHW }; // mock injection

	EXPECT_CALL(mockHW, read(0xA))
		.Times(5)
		.WillRepeatedly(Return(0x77));

	int result = dd.read(0xA);

	// read 5�� �����ؾ� ��.
	// EXPECT CALL + TIMES 

	// ��� �� delete hardware; �ʿ�
}

TEST(TS, TC2) {
	// stub
	// 1ȸ read 0xDD
	// 2ȸ read 0xDD
	// 3ȸ read 0xDD
	// 4ȸ read 0xDD
	// 5ȸ read 0xDA

	// exception �߻��Ǿ�� ��
}


int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}