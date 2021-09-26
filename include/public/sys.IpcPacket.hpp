/**
 * @file      sys.IpcPacket.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020-2021, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_IPC_PACKET_HPP_
#define SYS_IPC_PACKET_HPP_

#include <vector>
#include "Object.hpp"
#include "sys.IpcId.hpp"
#include "api.Read.hpp"
#include "lib.Align.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class IpcPacket
 * @brief Class implements IPC packet.
 */
class IpcPacket final : public Object<>
{
    typedef ::eoos::Object<> Parent;            
    
public:

    /**
     * @brief Constructor a packet.
     *
     * @param sourceId      An IPC Identifier.
     * @param destinationId An IPC Identifier.
     */
    IpcPacket(const IpcId& sourceId, const IpcId& destinationId) : Object(),
        header_ {sourceId, destinationId}
    {
        setConstructed( construct() );
    }

    /**
     * @brief Constructor a packet.
     *
     * @param stream An input stream.
     */
    explicit IpcPacket(const api::Read& stream) : Object(),
        header_ {stream}
    {
        setConstructed( construct(&stream) );
    }

    /**
     * @brief Destructor.
     */
    ~IpcPacket() override = default;
    
    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const override
    {
        return Parent::isConstructed();
    }               

    /**
     * @brief Returns source IPC Identifier of this packet.
     *
     * @return IPC Identifier.
     */
    IpcId getSource()
    {
        IpcId::Type const srcId {header_.srcId};
        return IpcId(srcId);
    }

    /**
     * @brief Returns destination IPC Identifier of this packet.
     *
     * @return IPC Identifier.
     */
    IpcId getDestination()
    {
        IpcId::Type const dstId {header_.dstId};
        return IpcId(dstId);
    }

    /**
     * @brief Returns the packet payload data.
     *
     * @return Pointer to the first byte of the data.
     */
    void* getPayload()
    {
        if( not isConstructed() || not isReady() ) 
        {
            return NULLPTR;
        }
        return payload_.data() + sizeof(header_);
    }

    /**
     * @brief Returns the packet payload data size.
     *
     * @return Size of the packet in Bytes.
     */
    size_t getPayloadSize() const
    {
        if( not isConstructed() || not isReady() ) 
        {
            return 0;
        }
        return size_.emplaced - sizeof(header_);
    }

    /**
     * @brief Returns the protocol data unit.
     *
     * @return Pointer to the first byte of the packet.
     */
    const void* getPacket() const
    {
        if( not isConstructed() || not isReady() ) 
        {
            return NULLPTR;
        }
        return payload_.data();
    }

    /**
     * @brief Returns the protocol data unit size.
     *
     * @return Size of the packet in Bytes.
     */
    size_t getPacketSize() const
    {
        if( not isConstructed() || not isReady() ) 
        {
            return 0;
        }
        return size_.emplaced;
    }

    /**
     * @brief Reserves space in the packet payload.
     *
     * @note This function will return false if emplace() called.
     *
     * @param size Size in Bytes for reserving.
     * @return True if the requested size is reserved.
     */
    bool_t reserve(size_t const size) noexcept try
    {
        if( not isConstructed() ) 
        {
            return false;
        }
        if( not isReserving_ ) 
        {
            return false;
        }
        size_.reserved += size;
        return true;
    } catch (...) {
        return false;
    }

    /**
     * @brief Emplaces data into the payload.
     *
     * @note If this function called, reserve() will return false.
     *
     * @param stream An input stream.
     * @return True if the data from the stream is emplaced.
     */
    bool_t emplace(const api::Read& stream) noexcept try
    {
        if( not isConstructed() ) 
        {
            return false;
        }
        bool_t res {false};
        do{
            bool_t const isPrepared = preparePayload();
            if( not isPrepared )
            {
                break;
            }
            // Read all data from stream
            size_t const sizeNeed {size_.reserved - size_.emplaced};
            size_t const sizeRead {stream.read(&payload_[size_.emplaced], sizeNeed)};
            size_.emplaced += sizeRead;
            if(sizeRead != sizeNeed)
            {
                break;
            }
            res = true;
        } while (false);
        // Set the packet not to be constructed if the emplacing faild
        if(res == false) 
        {
            setConstructed(false);
        }
        return res;
    } catch (...) {
        return false;
    }

    /**
     * @brief Emplaces data into the payload.
     *
     * @note If this function called, rserve() will return false.
     *
     * @param data Pointer to data.
     * @param size Size of data in Bytes.
     * @return True if the data is emplaced.
     */
    bool_t emplace(const void* const data, size_t const size) noexcept try
    {
        if( not isConstructed() ) 
        {
            return false;
        }
        bool_t res {false};
        do{
            bool_t const isPrepared = preparePayload();
            if( not isPrepared )
            {
                break;
            }
            // Check avalible size in the payload
            size_t const sizeLeft = size_.reserved - size_.emplaced;
            if(size > sizeLeft)
            {
                break;
            }
            // Push data into the payload
            for(size_t i=0; i<size; i++)
            {
                const uint8_t* const buf = reinterpret_cast<const uint8_t*>(data);
                payload_.push_back(buf[i]);
            }
            size_.emplaced += size;
            res = true;
        } while (false);
        // Set the packet not to be constructed if the emplacing faild
        if(res == false) 
        {
            setConstructed(false);
        }
        return res;
    } catch (...) {
        return false;
    }

private:

    /**
     * @brief Prepares the payload for loading data.
     *
     * @note If this function called, reserve() will return false.
     *
     * @return True if the payload is prepared.
     */
    bool_t preparePayload()
    {
        if( not isReserving_ )
        {
            return true;
        }
        // Prepare the payload, emplace the header, and close the reserving
        bool_t res {false};
        bool_t const isReserved {reserve(sizeof(header_))};
        if( isReserved ) 
        {
            isReserving_ = false;
            payload_.resize(size_.reserved);
            header_.size = size_.reserved - sizeof(header_);
            bool_t const isEmplaced {emplace(&header_, sizeof(header_))};
            if(isEmplaced)
            {
                res = true;
            }
        }
        return res;
    }

    /**
     * @brief Tests if this packet is ready.
     *
     * @return True if the reserving is closed and all the reserved size is emplaced.
     */
    bool_t isReady() const
    {
        if( isReserving_ ) 
        {
            return false;
        }
        else if( size_.reserved != size_.emplaced )
        {
            return false;
        }
        else 
        {
            return true;
        }
    }

    /**
     * @brief Constructs this object.
     *
     * @param stream An input stream.
     * @return True if this object has been constructed successfully.
     */             
    bool_t construct(const api::Read* const stream = NULLPTR)
    {
        bool_t res {false};
        do{
            if( not isConstructed() )
            {
                break;
            }
            // Reserve size in this packet set in the header
            bool_t const isReserved {reserve(header_.size)};
            if( not isReserved )
            {
                break;
            }
            // Emplace data in this packet from a given stream
            if( stream != NULLPTR )
            {
                bool_t const isEmplaced {emplace(*stream)};
                if( not isEmplaced )
                {
                    break;
                }
            }
            res = true;
        }while(false);
        return res;
    }

    /**
     * @struct Header
     * @brief This packet header.
     */
    struct Header
    {
        /**
         * @brief Constructor.
         *
         * @param sourceId      An IPC Identifier.
         * @param destinationId An IPC Identifier.
         */
        Header(const IpcId& sourceId, const IpcId& destinationId) :
            srcId { sourceId },
            dstId { destinationId }
        {

        }

        /**
         * @brief Constructor.
         *
         * @param stream An input stream.
         */
        explicit Header(const api::Read& stream)
        {
            stream.read(this, sizeof(Header));
        }

        /**
         * @brief Synchronization value of this packet header.
         */
        static const uint32_t SYNC {0x55AAAA55};

        /**
         * @brief Synchronization value of the packet.
         */
        lib::Align<uint32_t> sync {SYNC};
        
        /**
         * @brief Source ID.
         */
        lib::Align<IpcId::Type> srcId {0};
        
        /**
         * @brief Destination ID.
         */
        lib::Align<IpcId::Type> dstId {0};
        
        /**
         * @brief Data size of user data of the packet.
         */
        lib::Align<size_t> size {0};
    };
    
    /**
     * @brief Copy constructor.
     */
    IpcPacket(const IpcPacket&) = delete;

    /**
     * @brief Move constructor.
     */
    IpcPacket(IpcPacket&&) = default;

    /**
     * @brief Copy assignment operator.
     */
    IpcPacket& operator=(const IpcPacket&) = delete;

    /**
     * @brief Move assignment operator.
     */
    IpcPacket& operator=(IpcPacket&&) = delete;    
    
    /**
     * @struct ReservationSize
     * @brief Reservation size.
     */
    struct ReservationSize
    {
        size_t reserved {0};
        size_t emplaced {0};
    };

    /**
     * @brief This packet header.
     */
    Header header_;
    
    /**
     * @brief Packet data.
     * @todo Replace with eoos::lib::Vector
     */
    std::vector<uint8_t> payload_ {};
    
    /**
     * @brief Reservation size.
     */
    ReservationSize size_;
    
    /**
     * @brief Size reserving stage in process.
     */
    bool_t isReserving_ {true};
};

} // namespace sys
} // namespace eoos
#endif // SYS_IPC_PACKET_HPP_
