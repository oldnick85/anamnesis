#ifndef CTERMINALSTATEMASHINE_MAIN_H
#define CTERMINALSTATEMASHINE_MAIN_H

#include <stdio.h>

#include "common.h"
#include "io/ctrmio.h"
#include "encode/ctrmencode.h"
#include "decode/ctrmdecode.h"


/*! *****************************************************************
 * \brief CTerminalMain - основной терминал программы
 *
 * Машина состояний основного терминала:
 * \dot
 * digraph state_machine_main {
 *   start	[label="Start"];
 *	 end	[label="End"];
 *	 query	[label="Query"];
 *	 enc	[label="Encode"];
 *	 dec	[label="Decode"];
 *
 *   start	->	query
 *   query	->	end
 *   query	->	enc
 *   enc	->	query
 *   query	->	dec
 *   dec	->	query
 * }
 * \enddot
 ******************************************************************/

class CTrmMain
        : public IStateMashine
        , private CTrmIO
{
public:
    CTrmMain() = default;
    virtual ~CTrmMain() override = default;

	virtual void Begin() override final;
};

#endif // CTERMINALSTATEMASHINE_MAIN_H
