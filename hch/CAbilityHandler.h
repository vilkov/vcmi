#ifndef __CABILITYHANDLER_H__
#define __CABILITYHANDLER_H__

#include <string>
#include <vector>

class CDefHandler;

class CAbility
{
public:
	int idNumber;
	bool isAllowed; //true if we can use this hero's ability (map information)
};

class CAbilityHandler
{
public:
	std::vector<CAbility *> abilities;
	CDefHandler * abils32, * abils44, * abils82;
	void loadAbilities();
};


#endif // __CABILITYHANDLER_H__
