#include <vector>
#include <string>
#include <cmath>
#include <iostream>
using namespace std;

#include "PStack.hpp"
#include "BBracket.h"

int main()
{
    BBracket* bracket_manager = new BBracket();
    bracket_manager -> m_GenerateBrackets();
    bracket_manager -> m_EliminateRepeat();
    int answer = bracket_manager -> m_GetValidNumber();
    cout << answer;
    delete(bracket_manager);
    return 0;
}