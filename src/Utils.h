#ifndef SENECA_UTILS_H_
#define SENECA_UTILS_H_
#include <iostream>
namespace seneca
{
   class Utils
   {
      /// <summary>
      /// Start point for the simulated time
      /// Set to 8 AM
      /// </summary>
      unsigned int m_testMins = 480;
      /// <summary>
      /// index for the time addition intervals ({ 3,5,9,20,30 });
      /// </summary>
      unsigned int m_testIndex = 0;

   public:
      /// <summary>
      /// Set the debug global variable to true and sets the m_testMins attribute to
      ///  hour x 60 + min. This value will be the intial starting time for debugging
      ///  and testing.
      /// </summary>
      /// <param name="hour">hours</param>
      /// <param name="min">minutes</param>
      void setDebugTime(int hour, int min);
      /// <summary>
      /// If not in debugging mode, returns the current minute value of the system hour
      ///  and minute. If debugging is active it will first return the value of m_testMins
      ///  then adds the following values in these intervals (3,5,9,20,30) to simulate passage
      ///  of time.
      /// </summary>
      /// <returns>the current time in minutes</returns>
      int getTime(); // returns the time of day in minutes

      /// <summary>
      /// compares s1 to s2
      /// </summary>
      /// <param name="s1">Cstring</param>
      /// <param name="s2">Cstring</param>
      /// <returns> &gt;0 if s1 &gt; s2  OR  &lt;0 if s1 &lt; s2 OR 0 if s1 = s2</returns>
      int strcmp(const char *s1, const char *s2) const;
      int getInt(int min, int max);

      /** Displays the prompt and reads an integer from the console. If the integer is not within the
        range of min and max, it will display an error message and prompt the user again.
       @param min minimum value
       @param max maximum value
       @param prompt prompt message
       @return the integer value within the range
      **/
      int getIntRange(int min, int max, const char *prompt = nullptr);

      /**Count the number of lines in the text
       @param text the string to count the lines
       @return number of lines if text is not null, otherwise 0
      **/
      int countLines(const char *text);
   };

   /// <summary>
   /// making seneca::debug variable global to all the files
   /// which include "Utils.h"
   /// </summary>
   extern bool debug;
   /// <summary>
   /// making seneca::U "Utils" object global to all the files which include "Utils.h"
   /// </summary>
   extern Utils U;

   template <typename type>
   void removeDynamicElement(type *array[], int index, int &size)
   {
      delete array[index];
      for (int j = index; j < size; j++)
      {
         array[j] = array[j + 1];
      }
      size--;
   }
}
#endif // !SENECA_UTILS_H_
