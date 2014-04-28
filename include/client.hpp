/**
 * \file client.hpp
 * \brief Client.
 * \author RAZANAJATO RANAIVOARIVONY Harenome
 * \author MEYER Jérémy
 * \date 2014
 * \copyright WTFPL version 2
 */
/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details.
 */
#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include <iostream>
#include <fstream>
#include <map>

#include "omnithread.h"

#include "corbatur.hh"
#include "parser.hpp"
#include "server.hpp"
#include "contact_manager.hpp"

/**
 * \brief Client.
 */
class client : public omni_thread
{
public:
    client (void);
    client (void (*fn)(void*), void* arg = NULL, priority_t pri = omni_thread::PRIORITY_NORMAL);
    client (void * (*fn)(void*), void* arg = NULL, priority_t pri = omni_thread::PRIORITY_NORMAL);
    client (const client & c);
    client (const char * program_name, const std::string & name, const std::string & address);
    client (const char * program_name, const std::string & name, const std::string & address, contact_manager * contacts);
    ~client (void);
    void set_self_address (const std::string & address);
    void run (void * arg);
    void swap (client & c);
    client & operator= (client c);
    int send_message_to_contact (const char * name, const char * m);
    int send_message_to_contact (const std::string & name, const char * m);

private:
    std::map<std::string, bool> _contacted;
    corbatur::sender _client_infos;
    contact_manager * _contacts;
    const char * _program_name;
    std::string _self_address;

    void _print_prompt (void);
    int _send_message_to_address (const char * address, const char * m);
    int _send_message_to_contact (const char * name, const char * m);
    int _send_message_to_contact (const contact & c, const char * m);
    int _send_message_to_contact (const std::string & name, const char * m);

    void _reset_contacted (void);

    static const char _ORBINITREF[];
    static CORBA::Object_ptr _get_object_reference (CORBA::ORB_ptr orb);
};

#endif /* __CLIENT_HPP__ */
