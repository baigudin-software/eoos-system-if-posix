/**
 * @file      sys.ext.IpcClient.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020-2021, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_EXT_IPCCLIENT_HPP_
#define SYS_EXT_IPCCLIENT_HPP_

#include "sys.IpcBase.hpp"
#include "sys.Fifo.hpp"

#if EOOS_CPP_STANDARD < 2011
#error "C++ language standard less than C++11 is not supported"
#endif

namespace eoos
{
namespace sys
{
namespace ext
{

/**
 * @class IpcClient
 * @brief Class implements the transport level of OSI model.
 */
class IpcClient final : public IpcBase
{
    
public:

    /**
     * @brief Constructor.
     *
     * @param id     A unique IPC Identifier of the client for the Database.
     * @param dbPath Database path to a dir contains FIFO files.
     */
    IpcClient(IpcId id, const String& dbPath) noexcept try : IpcBase(dbPath),
        clientId_ {id}
    {
        setConstructed( construct() );
    } catch (...) {
        setConstructed( false );
    }

    /**
     * @brief Destructor.
     */
    ~IpcClient() override = default;
    
    /**
     * @brief Sends data to the server.
     *
     * @param data Pointer to data.
     * @param size Size of data in Bytes.
     * @return True if the data sent.
     */
    bool_t send(const void* const data, size_t const size) noexcept try
    {
        if( not isConstructed() )
        {
            return false;
        }
        if( data == NULLPTR || size == 0 )
        {
            return false;
        }
        IpcPacket packet {clientId_, serverId_};
        bool_t isDone {false};
        isDone = packet.reserve(size);
        if( not isDone )
        {
            return false;
        }
        isDone = packet.emplace(data, size);
        if( not isDone )
        {
            return false;
        }
        const void* const packetData {packet.getPacket()};
        size_t const packetSize {packet.getPacketSize()};
        size_t const sentSize { txFifo_.write(packetData, packetSize) };
        return sentSize == packetSize;
    } catch (...) {
        return false;
    }

private:

    /**
     * @copydoc eoos::sys::IpcBase::getReedSrteam()
     */
    api::Read& getReedSrteam() override
    {
        return rxFifo_;
    }

    /**
     * @copydoc eoos::sys::IpcBase::getIpcId()
     */
    IpcId getIpcId() const override
    {
        return clientId_;
    }

    /**
     * @brief Constructs this object.
     *
     * @return True if this object has been constructed successfully.
     */
    bool_t construct()
    {
        bool_t res {false};
        do{
            if( not isConstructed() )
            {
                break;
            }
            if( not rxFifo_.isConstructed() )
            {
                break;
            }
            if( not txFifo_.isConstructed() )
            {
                break;
            }
            res = true;
        }while(false);
        return res;
    }

    /**
     * @brief Copy constructor.
     */
    IpcClient(const IpcClient&) = delete;

    /**
     * @brief Move constructor.
     */
    IpcClient(IpcClient&&) = delete;

    /**
     * @brief Copy assignment operator.
     */
    IpcClient& operator=(const IpcClient&) = delete;

    /**
     * @brief Move assignment operator.
     */
    IpcClient& operator=(IpcClient&&) = delete;    

    /**
     * @brief This client IPC Identifier
     */
    IpcId clientId_;
    
    /**
     * @brief The server IPC Identifier
     */
    IpcId serverId_ {IpcId::getServerId()};
    
    /**
     * @brief RX FIFO for receiving a server response.
     */
    Fifo rxFifo_ {getFilePath(clientId_),
        Fifo::Flag(Fifo::Flag::READ
                 | Fifo::Flag::BLOCK
                 | Fifo::Flag::REMOVE
                 | Fifo::Flag::CREATE )
    };
    
    /**
     * @brief TX FIFO for transmiting to a server.
     */
    Fifo txFifo_ {getFilePath(serverId_),
        Fifo::Flag(Fifo::Flag::WRITE
                 | Fifo::Flag::BLOCK)
    };
};

} // namespace ext
} // namespace sys
} // namespace eoos
#endif // SYS_EXT_IPCCLIENT_HPP_
