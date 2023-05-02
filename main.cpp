#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>

#include "User.h"
#include "Message.h"

namespace fs = std::filesystem;

void demo_perms(fs::perms p)
{
    std::cout << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
        << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
        << ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
        << ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
        << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
        << ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
        << ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
        << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
        << ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-")
        << '\n';
}
int main()
{
    std::vector<User> users;
    std::vector<Message> messages;

    std::fstream users_file = std::fstream("Users.txt", std::ios::in | std::ios::out);

    if (!users_file)
    {
        users_file = std::fstream("Users.txt", std::ios::in | std::ios::out | std::ios::trunc);
    }
    if (!users_file.is_open())
    {
        std::cout << "Could not open file Users.txt" << std::endl;
        return -1;
    }
    else
    {
        
        users.emplace_back("User1", "user1", "user1pass");
        users.emplace_back("User3", "user3", "user3pass");
        users.emplace_back("User4", "user4", "user4pass");
        users.emplace_back("User5", "user5", "user5pass");

        
        for (auto& user : users)
        {
            users_file << user << std::endl;
        }

       
        std::cout << "*** All users from file Users.txt: ***" << std::endl;
        
        users_file.seekg(0, std::ios::beg);
        
        std::string userName, userLogin, userPassword;
        std::string line;
        
        while (getline(users_file, line))
        {
            std::istringstream input{line};
            getline(input, userName, ';');
            getline(input, userLogin, ';');
            getline(input, userPassword);
            std::cout << "Name: " << userName << "   Login: " << userLogin << "   Password: " << userPassword << std::endl;
        }
        
        
        std::cout << "\nCreated file with permissions: ";
        demo_perms(fs::status("Users.txt").permissions());
        fs::permissions("Users.txt",
            fs::perms::group_all | fs::perms::others_all,
            fs::perm_options::remove);

        std::cout << "After removing g-all and o-all:  ";
        demo_perms(fs::status("Users.txt").permissions());
    }

    std::fstream messages_file = std::fstream("Messages.txt", std::ios::in | std::ios::out);
    
    if (!messages_file)
    {
        messages_file = std::fstream("Messages.txt", std::ios::in | std::ios::out | std::ios::trunc);
    }
    if (!messages_file.is_open())
    {
        std::cout << "Could not open file Messages.txt" << std::endl;
        return -1;
    }
    else
    {
        
        messages.emplace_back("Hello", "user1", "user2");
        messages.emplace_back("Hello!!!", "user2", "user1");
        messages.emplace_back("Hi", "user3", "user4");
        messages.emplace_back("Hello all", "user4", "user1");

        
        for (auto& message : messages)
        {
            messages_file << message << std::endl;
        }

        
        std::cout << "\n*** All messages from file Messages.txt: ***" << std::endl;
        messages_file.seekg(0, std::ios::beg);
        std::string messageText, messageSender, messageReceiver;
        std::string line;

        while (getline(messages_file, line))
        {
            std::istringstream input{ line };
            getline(input, messageText, ';');
            getline(input, messageSender, ';');
            getline(input, messageReceiver);
            std::cout << "Text: " << messageText << "\t\tSender: " << messageSender << "\t\tReceiver: " << messageReceiver << std::endl;
        }

       
        std::cout << "\nCreated file with permissions: ";
        demo_perms(fs::status("Messages.txt").permissions());
        fs::permissions("Messages.txt",
            fs::perms::group_all | fs::perms::others_all,
            fs::perm_options::remove);

        std::cout << "After removing g-all and o-all:  ";
        demo_perms(fs::status("Messages.txt").permissions());
    }

    return 0;
}
