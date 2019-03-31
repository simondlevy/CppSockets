/*
 * SocketClient.h: class for general socket clients in Goshawk project
 *
 * Copyright (C) 2019 Simon D. Levy
 *
 * MIT License
 */

#pragma once

#include "SocketCompat.h"

class SocketClient : public SocketCompat {

    public:

        SocketClient(const char * host, const short port);

        void openConnection(void);
};
