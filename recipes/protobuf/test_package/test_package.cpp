#include <cstdlib>
#include <iostream>

#include "addressbook.pb.h"

int main()
{
	tutorial::Person p;
	p.set_id(21);
	p.set_name("Jane Doe");
	p.set_email("jane.doe@example.com");

	std::cout << p.SerializeAsString() << std::endl;

	return EXIT_SUCCESS;
}
