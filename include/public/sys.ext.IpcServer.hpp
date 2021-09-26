/**
 * @file      sys.ext.IpcServer.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020-2021, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_EXT_IPCSERVER_HPP_
#define SYS_EXT_IPCSERVER_HPP_

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
 * @class IpcServer
 * @brief Class implements the transport level of OSI model.
 */
class IpcServer final : public IpcBase
{
    
public:
    
    /**
     * @brief Constructor.
     *
     * @param dbPath Path to a dir contains FIFO files.
     */
    explicit IpcServer(const String& dbPath) : IpcBase(dbPath)
    {
        setConstructed( construct() );
    }
    
    /**        
     * @brief Destructor.
     */
    ~IpcServer() override = default;

    /**
     * @brief Sends data to a client.
     *
     * @param clientId An IPC Identifier.
     * @param data     Pointer to data.
     * @param size     Size of data in Bytes.
     * @return True if the data sent.
     */
    bool_t send(const IpcId& clientId, const void* const data, std::size_t const size) noexcept try
    {
        if( not isConstructed() )
        {
            return false;
        }
        if( data == NULLPTR || size == 0 )
        {
            return false;
        }
        // Open TX FIFO for transmiting to a client.
        String const txPath {getFilePath(clientId)};
        Fifo txFifo {txPath,
            Fifo::Flag(Fifo::Flag::WRITE
            | Fifo::Flag::BLOCK)
        };
        if( not txFifo.isConstructed() )
        {
            return false;
        }
        // Prepare the packet
        IpcPacket packet {serverId_, clientId};
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
        // Send the packet
        const void* const packetData {packet.getPacket()};
        std::size_t const packetSize {packet.getPacketSize()};
        std::size_t const sentSize { txFifo.write(packetData, packetSize) };
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
        return serverId_;
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
            if( rxFifo_.isConstructed() )
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
    IpcServer(const IpcServer&) = delete;

    /**
     * @brief Move constructor.
     */
    IpcServer(IpcServer&&) = delete;

    /**
     * @brief Copy assignment operator.
     */
    IpcServer& operator=(const IpcServer&) = delete;

    /**
     * @brief Move assignment operator.
     */
    IpcServer& operator=(IpcServer&&) = delete;    

    /**
     * @brief The server IPC Identifier
     */
    IpcId serverId_ {IpcId::getServerId()};
    
    /**
     * @brief RX FIFO for receiving a server response.
     */
    Fifo rxFifo_ {getFilePath(serverId_),
        Fifo::Flag(Fifo::Flag::READ
                 | Fifo::Flag::BLOCK
                 | Fifo::Flag::REMOVE
                 | Fifo::Flag::CREATE)
    };
};

} // namespace ext
} // namespace sys
} // namespace eoos
#endif // SYS_EXT_IPCSERVER_HPP_
