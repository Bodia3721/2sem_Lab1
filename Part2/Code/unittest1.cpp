#include "stdafx.h"
#include "CppUnitTest.h"

#include <string>
#include <utility>
#include <vector>
#include <fstream>

#include <Windows.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTestProject
{		
	TEST_CLASS(UnitTest1)
	{
		pair<int, string> UnitTest1::execute(const string& args);

	public:
		
		// new test
		TEST_METHOD(TestLayersNumber)
		{
			auto result = execute("19 -1 -3 3 -2 1 -2 -1 -2 3 -1 1 -1 -1 0 7 1 0 1 2 1 1 1 5 2 2 2 -1 2 3 3 -2 3 2 4 1 5 5 6");
			Assert::AreEqual(result.first, 0);
			string::size_type pos = 0;
			int count = 0;
			static const string LAYER_DELIM = "---";
			while ((pos = result.second.find(LAYER_DELIM, pos)) != string::npos) {
				pos += LAYER_DELIM.size();
				count++;
			}
			Assert::AreEqual(count, 3);
		}

		TEST_METHOD(TestLayerPointsNumber) {
			auto result = execute("19 -1 -3 3 -2 1 -2 -1 -2 3 -1 1 -1 -1 0 7 1 0 1 2 1 1 1 5 2 2 2 -1 2 3 3 -2 3 2 4 1 5 5 6");
			Assert::AreEqual(result.first, 0);
			string::size_type pos = 0;
			int count = 0;
			static const string POINT_DELIM = ";";
			while ((pos = result.second.find(POINT_DELIM, pos)) != string::npos) {
				pos += POINT_DELIM.size();
				count++;
			}
			//Assert::AreEqual(count, 6);
			Assert::AreEqual(count, 17);
		}

		TEST_METHOD(TestEmptyInput) {
			auto result = execute("");
			Assert::AreEqual(result.first, 0);
			Assert::IsTrue(result.second.empty());
		}

		TEST_METHOD(TestZeroPointsInput) {
			auto result = execute("0");
			Assert::AreEqual(result.first, 0);
			Assert::IsTrue(result.second.empty());
		}

		TEST_METHOD(TestIncorrectArgsNumber) {
			auto result = execute("1 1");
			Assert::AreEqual(result.first, 1);
			Assert::AreEqual(result.second, string("Input error.\r\n"));
		}

		TEST_METHOD(TestInvalidPointsNumber) {
			auto result = execute("-1");
			Assert::AreEqual(result.first, 1);
			Assert::AreEqual(result.second, string("Input error.\r\n"));
		}
	};

	pair<int, string> UnitTest1::execute(const string& args) {
		static const string OUT_FILE = "test1.out";
		int ret = system(("ConvexLayersApp.exe " + args + " 1> " + OUT_FILE).c_str());
		std::ifstream input(OUT_FILE, std::ios::binary);
		string data(std::istreambuf_iterator<char>(input),
			(std::istreambuf_iterator<char>()));
		input.close();
		system(("del " + OUT_FILE).c_str());
		return { ret, move(data) };
	}
}
