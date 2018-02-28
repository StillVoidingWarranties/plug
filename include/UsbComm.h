/*
 * PLUG - software to operate Fender Mustang amplifier
 *        Linux replacement for Fender FUSE software
 *
 * Copyright (C) 2017-2018  offa
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <vector>
#include <initializer_list>
#include <cstdint>

struct libusb_device_handle;

namespace plug
{
    class UsbComm
    {
    public:
        void open(std::uint16_t vid, std::uint16_t pid);
        void openFirst(std::uint16_t vid, std::initializer_list<std::uint16_t> pids);
        void close();

        bool isOpen() const;

        template<class Container>
        std::int32_t interruptWrite(std::uint8_t endpoint, Container c)
        {
            return interruptWriteImpl(endpoint, c.data(), c.size());
        }

        std::vector<std::uint8_t> interruptReceive(std::uint8_t endpoint, std::size_t recvSize);

    private:

        std::int32_t interruptWriteImpl(std::uint8_t endpoint, std::uint8_t* data, std::size_t size);

        void initInterface();


        libusb_device_handle* handle{nullptr};
    };
}
