#include "pch.h"
#include "CppUnitTest.h"

extern "C" {
#include"../TP4_S2_TU/TP4_TU.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TP4S2TUtest
{
	TEST_CLASS(TP4S2TUtest)
	{
	public:
		
		TEST_METHOD(TestEstPair)
		{
			Assert::AreEqual(estPair(6), 1);
		}
		TEST_METHOD(TestEstPair2)
		{
			Assert::AreEqual(estPair(7), 0);
		}
	};
}
