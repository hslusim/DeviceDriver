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
}

TEST(TS, TC2) {
	MockFlashMemoryDevice mockHW;
	DeviceDriver dd{ &mockHW };

	// stub
	// 1ȸ read 0xDD
	// 2ȸ read 0xDD
	// 3ȸ read 0xDD
	// 4ȸ read 0xDD
	// 5ȸ read 0xDA

	// exception �߻��Ǿ�� ��

	EXPECT_CALL(mockHW, read((long)0xA))
		.WillOnce(Return((int)0xDD))
		.WillOnce(Return((int)0xDD))
		.WillOnce(Return((int)0xDD))
		.WillOnce(Return((int)0xDD))
		.WillOnce(Return((int)0xDA));

	EXPECT_THROW(dd.read(0xA), std::exception);
}

TEST(TS, TC3_write) {
	NiceMock<MockFlashMemoryDevice> mockHW;
	DeviceDriver dd{ &mockHW };

	EXPECT_CALL(mockHW, read((long)0xA))
		.Times(1)
		.WillOnce(Return(0xFF));

	dd.write((long)0xA, 0x33);
}

TEST(TS, TC4_write) {
	NiceMock<MockFlashMemoryDevice> mockHW;
	DeviceDriver dd{ &mockHW };

	// read 1���ؼ� 0xFF�� �ƴϸ� exception �߻��ؾ���
	EXPECT_CALL(mockHW, read(0xA))
		.Times(1)
		.WillOnce(Return(0xFA));

	EXPECT_THROW(dd.write(0xA, 0x33), std::exception);

}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}