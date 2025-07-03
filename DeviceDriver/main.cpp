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

	// read 5번 수행해야 해.
	// EXPECT CALL + TIMES 

	// 사용 후 delete hardware; 필요
}

TEST(TS, TC2) {
	// stub
	// 1회 read 0xDD
	// 2회 read 0xDD
	// 3회 read 0xDD
	// 4회 read 0xDD
	// 5회 read 0xDA

	// exception 발생되어야 해
}


int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}