#include <eosiolib/eosio.hpp>
#include <eosiolib/currency.hpp>
#include <eosio.token.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

using namespace eosio;
using std::string;

class proxytoken : contract {
private:

    string getAccountNameFromMemo(const string& str){
        std::vector<std::string> words;
        boost::split(words, str, boost::is_any_of(" "), boost::token_compress_on);
        return words[0];
    }

public:
    using contract::contract;
    proxytoken( name self ) : contract(self){}

    void empty(){}

    void receivedTokens( const currency::transfer& t, account_name code ) {
        if( t.to == _self ) {
            if (code == N(eosio.token)) {
                string cMemo = t.memo;
                string stringName(getAccountNameFromMemo(cMemo));
                account_name to = string_to_name(stringName.c_str());
                string memo = cMemo.replace(0, cMemo.size() > stringName.size() ? stringName.size()+1 : stringName.size(), "");
                INLINE_ACTION_SENDER(eosio::token::token, transfer)( N(eosio.token), {{_self,N(active)}}, {_self, to, t.quantity, memo} );
            }
            else eosio_assert(false, "This contract only accepts EOS tokens");
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
            EOSIO_API( proxytoken, (empty) )
        };
    }
};

extern "C" {
[[noreturn]] void apply( uint64_t receiver, uint64_t code, uint64_t action ) {
    proxytoken c( receiver );
    c.apply( code, action );
    eosio_exit(0);
}
}