#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../include/student.h"
using ::testing::Return;
using ::testing::SetErrnoAndReturn;
using ::testing::Throw;
using ::testing::ThrowsMessage;


class StudentMock : public Student, public testing::Mock
{
public:
    StudentMock(int id, string name, string pwd) : Student(id, name, pwd)
    {
        cout << "Create StudentMock" << endl;
    }
    MOCK_METHOD(void, logout, (), (override));
};

class StudentTests : public testing::Test
{
public:
    Student *s;
    void SetUp() override
    {
        s = new Student(34, "Hailin", "123456");
        cout << "Create a student: [" << s->m_StuID << " : " << s->m_Name << " ]" << endl;
    }

    void TearDown() override
    {
        if (s != nullptr)
        {
            cout << "Delete a student: [" << s->m_StuID << " : " << s->m_Name << "  ]" << endl;
            delete s;
        }
    }
};

class InvalidValueException:public virtual std::exception
{
    public:
    const char* what() const noexcept override 
    {
        return "Invalid value";
    }
};

TEST_F(StudentTests, Get)
{
    EXPECT_EQ("Hailin", s->m_Name);
    EXPECT_EQ(34, 34);
    EXPECT_EQ("123456", s->m_Password);
}

TEST_F(StudentTests, set)
{
    s->m_Name = "Huahua";
    s->m_Password = "999999";
    s->m_StuID = 123;
    EXPECT_EQ("Huahua", s->m_Name);
    EXPECT_EQ(123, s->m_StuID);
    EXPECT_EQ("999999", s->m_Password);
}

TEST_F(StudentTests, logout)
{
    StudentMock sm(111, "HHH", "123");
    EXPECT_CALL(sm, logout())
        .Times(2)
        .WillOnce(Return())
        .WillRepeatedly(Throw(InvalidValueException()));
    sm.logout();
    EXPECT_THROW(sm.logout(),InvalidValueException);
}