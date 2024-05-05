#ifndef MENU_H
#define MENU_H
#include <iostream>

namespace seneca
{
    /**
     * @class Menu
     * @brief Represents a menu with options and content.
     *
     * The Menu class provides functionality to create and display a menu with options and content.
     * It also allows reading user input to select an option from the menu.
     */
    class Menu
    {
        char *m_content;
        int m_numOptions;
        int m_indetationTabs;

    public:
        /**
         * @brief Constructs a Menu object with the given content and number of indentation tabs.
         *
         * @param menuContent The content of the menu.
         * @param numberOfTabs The number of indentation tabs for the menu (default is 0).
         */
        Menu(const char *menuContent, int numberOfTabs = 0);

        /**
         * @brief Destructor for the Menu object.
         */
        ~Menu();

        /**
         * @brief Deleted copy assignment operator.
         *
         * @param other The Menu object to be assigned.
         * @return Menu& A reference to the assigned Menu object.
         */
        Menu &operator=(const Menu &other) = delete;

        /**
         * @brief Deleted copy constructor.
         *
         * @param other The Menu object to be copied.
         */
        Menu(const Menu &other) = delete;

        /**
         * @brief Displays the menu content.
         *
         * @param ostr The output stream to display the menu content (default is std::cout).
         * @return std::ostream& The output stream used for displaying the menu content.
         */
        std::ostream &display(std::ostream &ostr = std::cout) const;

        /**
         * @brief Reads user input to select an option from the menu.
         *
         * @param Selection The selected option from the menu.
         * @return int& A reference to the selected option.
         */
        int &operator>>(int &Selection);
    };
}
#endif