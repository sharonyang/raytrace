#ifndef INPUTPARSE_HPP
#define INPUTPARSE_HPP

using namespace std;

char* get_cmd_option(char ** begin, char ** end, const string & option)
{
    char ** itr = find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    char * output;
    output[0] = '*';
    return output;
}

bool cmd_option_exists(char** begin, char** end, const string& option)
{
    return find(begin, end, option) != end;
}

void usage(char * argv)
{
    cout << "Usage: " << argv << " " << \
        "[-o s | m] [-l s | m] [-v l | r | c]" << endl;
    cout << "-o: num of objects, can be 's' for single and" \
        " 'm' for multiple. It is defaulted to single." << endl;
    cout << "-l: num of light source, can be 's' for single and" \
        " 'm' for multiple. It is defaulted to single." << endl;
    cout << "-v: view angle, can be 'l' for left, 'r'" \
        " for right, and 'c' for center. It is defaulted to" \
        " center." << endl;
}

#endif
