#include "absmsgobj.h"
#include "intermodulemsgmgr.h"

AbsMsgObj::AbsMsgObj(const QString &key)
    : m_key(key)
{
    g_msgq->msgObjRegister(key, this);
}

AbsMsgObj::~AbsMsgObj()
{
    g_msgq->msgObjUnregister(m_key, this);
}
