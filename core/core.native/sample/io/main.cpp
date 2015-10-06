//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#include <stdio.h>
#include <tchar.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>

#include "core.native/io.h"

using namespace useless;

int _tmain( int /*argc*/, _TCHAR* /*argv[]*/ )
{
	binary_writer br( "test.txt", std::ios_base::out );

	br << "123";

	string str = L"sdfkasdf";
	br << str;

	std::vector<int> vec;
	vec.push_back( 10 );
	vec.push_back( 20 );
	vec.push_back( 30 );
	br << vec;

	std::deque<int> deq;
	deq.push_back( 11 );
	deq.push_back( 12 );
	deq.push_back( 13 );
	br << deq;

	std::array<char, 5> ary;
	ary.fill( '3' );
	br << ary;

	std::list<char> list;
	list.push_front( '2' );
	list.push_front( '4' );
	list.push_front( '8' );
	br << list;

	std::forward_list<char> frdlist;
	frdlist.push_front( '5' );
	frdlist.push_front( '7' );
	frdlist.push_front( '9' );
	br << frdlist;

	std::pair<int, char> pair;
	pair.first = 10;
	pair.second = 'S';
	br << pair;

	std::set<int> set;
	set.insert( 33 );
	set.insert( 23 );
	set.insert( 13 );
	br << set;

	std::multiset<int> multiset;
	multiset.insert( 330 );
	multiset.insert( 230 );
	multiset.insert( 130 );
	br << multiset;

	std::unordered_set<int> uset;
	uset.insert( 3 );
	uset.insert( 2 );
	uset.insert( 1 );
	br << uset;

	std::map<int, char> map;
	map.insert( std::make_pair( 5, 'A' ) );
	map.insert( std::make_pair( 10, 'B' ) );
	map.insert( std::make_pair( 15, 'C' ) );
	br << map;
	
	std::multimap<int, char> multimap;
	multimap.insert( std::make_pair( 5, 'a' ) );
	multimap.insert( std::make_pair( 5, 'b' ) );
	multimap.insert( std::make_pair( 5, 'c' ) );
	br << multimap;

	std::unordered_map<int, int> umap;
	umap.insert( std::make_pair( 2, 100 ) );
	umap.insert( std::make_pair( 3, 200 ) );
	umap.insert( std::make_pair( 4, 300 ) );
	br << umap;

	return 0;
}