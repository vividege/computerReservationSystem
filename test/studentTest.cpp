#include <gtest/gtest.h>

#include "../include/student.h"

class StudentTests : public testing::Test
{
public:
    Student *s;
    virtual void SetUp()
    {
        s = new Student(34,"Hailin","123456");
        cout << "Create a student: [" << s->m_StuID<< " : " << s->m_Name << " ]" << endl;
    }

    virtual void TearDown()
    {
        cout << "Delete a student: ["  << s->m_StuID<< " : " << s->m_Name << "  ]" << endl;
          delete s;
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