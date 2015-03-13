#include "stdafx.h"
#include "CppUnitTest.h"
#include "../search/dfs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_test
{
	TEST_CLASS(test_dfs)
	{
	public:
		
		TEST_METHOD(ctor)
		{
			ai::search::DFS dfs("102345678", "012345678");

			Assert::AreEqual(9u, dfs.action_dictionary.size());
			std::string path = "RDLLDRRULLDRRULLDRRULLDRRULLDRURDLLURRDLLURRDLLURRDLLURRDLLUURRDLLDRRULLDRRULLDRRULLDRRULLDRURDLLURRDLLURRDLLURRDLLURRDLLUURRDLLDRRULLDRRULLDRRULLDRRULLDRURDLLURRDLLURRDLLURRDLLURRDLLUURRDLLDRRULLDRRULLDRRULLDRRULLDRURDLLURRDLLURRDLLURRDLLURRDLLUURRDLLDRRULLDRRULLDRRULLDRRULLDRURDLLURRDLLURRDLLURRDLLURRDLLUURRDLLDRRULLDRRULLDRRULLDRRULLDRURDLLURRDLLURRDLLURRDLLURRDLLUURRDLLDRRULLDRRULLDRRULLDRRULLDRURDLLURRDLLURRDLLURRDLLURRDLLUU";
			Assert::AreEqual(path, dfs.path_to_goal());
			Assert::AreEqual(337u, dfs.queue().size());
			Assert::AreEqual(440u, dfs.visited_set().size());
		}

	};
}