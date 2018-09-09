#include "stdafx.h"
#include "CppUnitTest.h"
#include"../ConsoleApplication1/iostream.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int testwc=WordCount("W:\\GITrepository\\software\\ConsoleApplication1\\UnitTest1\\TestFile\\empty.txt");
			Assert::AreEqual(testwc, 0);
		}

	};
}