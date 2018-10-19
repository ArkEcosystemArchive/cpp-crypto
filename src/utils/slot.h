/**
 * This file is part of Ark Cpp Crypto.
 *
 * (c) Ark Ecosystem <info@ark.io>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 **/

#ifndef SLOT_H
#define SLOT_H

#include "configuration/network.h"
#include <chrono>
#include <time.h>

namespace Ark {
namespace Crypto {
namespace Utils {
/**
 * This is the slot class.
 *
 * @author Simon Downey <simon@ark.io>
 **/
class Slot
{
    public:

#ifdef USE_IOT

#include <Arduino.h>

        /**
         * @brief Get the time diff between now and network start.
         *
         * @return time_t
         */
        static time_t time(Ark::Crypto::Networks::AbstractNetwork network) {
            /* FIXME: Returning -epoch on Arduino Platform */
            /* chrono is returning 0 */
            // return std::chrono::duration_cast<std::chrono::milliseconds>(
            //     std::chrono::system_clock::now()
            //     .time_since_epoch()
            // ).count()
            // - epoch(network);
            return 0;
        };
        /**/

        /**
         * @brief Get the network start epoch.
         *
         * @return time_t
         */
        static time_t epoch(Ark::Crypto::Networks::AbstractNetwork network)
        {
            const char* humanString = network.epoch();
            if(humanString) {
                char format[]="%Y-%m-%dT%H:%M:%S.%3d";
                int year,month,day,hour,minute,second,ms,timezone;

                sscanf(
                    humanString,
                    format,
                    &year,&month,&day,&hour,&minute,&second,&ms
                );
                timezone = 0;

                if (year<100) year+=2000;

                long epoch = 0;
                for (int yr=1970;yr<year;yr++)
                if (isLeapYear(yr)) epoch+=366*86400L;
                else epoch+=365*86400L;
                for(int m=1;m<month;m++) epoch+=daysInMonth(year,m)*86400L;

                epoch += (day-1)*86400L;
                epoch += hour*3600L;
                epoch += minute*60;
                epoch += second;
                epoch -= timezone*3600L;  

                return epoch;
            } else {
                return 0;
            };
        };
        /**/
        static inline bool isLeapYear(int yr) {
            return (yr % 4) == 0
            && ((yr % 100) != 0 || (yr % 400) == 0);
        }
        /**/
        static inline byte daysInMonth(int yr,int m) {
            byte days[12]={31,28,31,30,31,30,31,31,30,31,30,31};
            if (m==2 && isLeapYear(yr)) return 29;
            else return days[m-1];
        }
        /**/

#else /// OS Builds 

        /**
         * @brief Get the time diff between now and network start.
         *
         * @return time_t
         */
        static time_t time(Ark::Crypto::Networks::AbstractNetwork network) {
            return
            std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now()
                .time_since_epoch()
            ).count()
            - epoch(network);
        };
        /**/

        /**
         * @brief Get the network start epoch.
         *
         * @return time_t
         */
        static time_t epoch(Ark::Crypto::Networks::AbstractNetwork network) {
            const char* humanString = network.epoch();
            if(humanString) {
                /* create a time buffer */
                struct tm t;
                memset(&t, 0, sizeof(t));

                /* parse the humanString */
                strptime(humanString, "%Y-%m-%dT%H:%M:%S.%3d%z", &t);

                /* get the local time-zone offset */
                time_t offsetT = 0;
                struct tm offsetR;
                memset(&offsetR, 0, sizeof(offsetR));
                localtime_r(&offsetT, &offsetR);

                /* current time-zone - offset */
                int ofs = t.tm_gmtoff + offsetR.tm_gmtoff;
                time_t r = mktime(&t);

                /* return milliseconds (seconds x 1000) */
                return  (r + ofs) * 1000;
            } else {
                return 0;
            };
        };
        /**/
#endif /// IOT || OS Build
};
/**/
};
};
};

#endif
