#pragma once

#include <tchar.h>
#include <windows.h>
#include <atlbase.h>
#include <atlstr.h>


#include <sstream>

#include <boost/program_options.hpp>
#include <iostream>
using namespace boost::program_options;

namespace SmartLib
{
	class TestBoostOption
	{
	public:


		static void on_age(int age)
		{
			std::cout << "On age: " << age << '\n';
		}
		static int Case0(int argc, TCHAR* argv[])
		{
			try
			{
				options_description desc{ "Options΢�����ĸ����ͻ��Ƿ�ɽ��ܺͽ�ɫ���ֵľ���Options" };
				desc.add_options()
					("help,h", "�ǿ��˷�����ɫ����ռ䷢����\n��������ݿ�ָ�������\n���·���ʮһ����Ŷ��ٽ�\n�η�������ص��ǻᷢ������\n�ָ���������ɫ��\n�����Ľ���");
				std::stringstream ss;
				ss << desc;
				std::cout << ss.str() << std::endl;
				
			}
			catch (const error & ex)
			{
				std::cerr << ex.what() << '\n';
			}

			return 0;
		}
	};
}