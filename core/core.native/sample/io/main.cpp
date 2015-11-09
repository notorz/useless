//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>

#include "core.native/io.h"

using namespace useless;

int main()
{
	{
		dynamic_stream ds( 100 );
		binary_writer bw( ds );
		bw << 12;
		bw << 14;
	}

	{
		binary_writer bw( "test.txt", openmode::out );
		//bw << 12;

		bw << "12345";

		string str = L"sdfkasdf";
		bw << str;

		std::vector<int> vec;
		vec.push_back( 10 );
		vec.push_back( 20 );
		vec.push_back( 30 );
		bw << vec;

		std::deque<int> deq;
		deq.push_back( 11 );
		deq.push_back( 12 );
		deq.push_back( 13 );
		bw << deq;

		std::array<char, 5> ary;
		ary.fill( '3' );
		bw << ary;

		std::list<char> list;
		list.push_front( '2' );
		list.push_front( '4' );
		list.push_front( '8' );
		bw << list;

		std::forward_list<char> frdlist;
		frdlist.push_front( '5' );
		frdlist.push_front( '7' );
		frdlist.push_front( '9' );
		bw << frdlist;

		std::pair<int, char> pair;
		pair.first = 10;
		pair.second = 'S';
		bw << pair;

		std::set<int> set;
		set.insert( 33 );
		set.insert( 23 );
		set.insert( 13 );
		bw << set;

		std::multiset<int> multiset;
		multiset.insert( 330 );
		multiset.insert( 230 );
		multiset.insert( 130 );
		bw << multiset;

		std::unordered_set<int> uset;
		uset.insert( 3 );
		uset.insert( 2 );
		uset.insert( 1 );
		bw << uset;

		std::map<int, char> map;
		map.insert( std::make_pair( 5, 'A' ) );
		map.insert( std::make_pair( 10, 'B' ) );
		map.insert( std::make_pair( 15, 'C' ) );
		bw << map;

		std::multimap<int, char> multimap;
		multimap.insert( std::make_pair( 5, 'a' ) );
		multimap.insert( std::make_pair( 5, 'b' ) );
		multimap.insert( std::make_pair( 5, 'c' ) );
		bw << multimap;

		std::unordered_map<int, int> umap;
		umap.insert( std::make_pair( 2, 100 ) );
		umap.insert( std::make_pair( 3, 200 ) );
		umap.insert( std::make_pair( 4, 300 ) );
		bw << umap;

		std::vector<bool> test;
		test.resize( 8 );
		size_t size = sizeof( test );
		bw << test;
		bw << size;
	}

	{
		binary_reader br( "test.txt", openmode::in );

		char s[ 3 ] = { 0, };
		br >> s;
	}

	return 0;
}