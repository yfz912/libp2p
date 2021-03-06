#include <catch.hpp>

#define GSL_THROW_ON_CONTRACT_VIOLATION
#include <p2p/peer.h>
#include <p2p/utils/json.h>

using namespace p2p;
using namespace multiformats;


const auto sid = "QmRiBKAqtyHBZ6JXmSPouxmTitTWuufftiGU6dsEZ6DZUy";

const auto jwk_pubkey = R"({
    "kty":"RSA",
    "n":"zd58dyV0ZSJQSq_r0Nkkd27qQ-7citEn7uNWk0Qygo6sRv3rutaCKh0iqurapAQd6okPrlrOtIsXTDd7JA3HD2ypgX2qZ4IEyA_2UT-n_dmhUvt4vxqCfalRlV2N187kHQ4ZxVvNLDg3BZgJvEp4xJM-O_2RaHG3CqyCKCqX-sioW2Z-OE26V37aY0i-qGKbgihwkjdivf-h-dRbOSrWgVGcW-Z9dJsFYvx5MkpBX6--K5dw_tLiqw7ra4590EqsgsRd2um41DK7H33D_WWAjgDE9zpL2fee7_vpnMh8sLY0Zgvnq53ZlpcwfEiHj09C2hy1-2bfX7EHLyu60k_egQ",
    "e":"AQAB"
})";
const auto invalid_pubkey = R"({
    "kty":"RSA",
    "n":"nnnn",
    "e":"eeee"
})";

const auto jwk_prvkey = R"({ 
    "kty":"RSA", 
    "n":"zd58dyV0ZSJQSq_r0Nkkd27qQ-7citEn7uNWk0Qygo6sRv3rutaCKh0iqurapAQd6okPrlrOtIsXTDd7JA3HD2ypgX2qZ4IEyA_2UT-n_dmhUvt4vxqCfalRlV2N187kHQ4ZxVvNLDg3BZgJvEp4xJM-O_2RaHG3CqyCKCqX-sioW2Z-OE26V37aY0i-qGKbgihwkjdivf-h-dRbOSrWgVGcW-Z9dJsFYvx5MkpBX6--K5dw_tLiqw7ra4590EqsgsRd2um41DK7H33D_WWAjgDE9zpL2fee7_vpnMh8sLY0Zgvnq53ZlpcwfEiHj09C2hy1-2bfX7EHLyu60k_egQ", 
    "e":"AQAB", 
    "d":"Dv1KiyiJbpggVkUlvxGT-CY81jCHr6hGEhIT5v9UZ_EmjvIL2soXmJZItlteYHwtJB7DjqN7xJAuudvvZ5ovbj_a9s2adng7fchJ-JAKMivz9RcI8ooQtOteeRrGDc_kJIiMTLRqrJ6t4SMOXtsanN5jtPoOlIjmpBAYV1TLfkpCNtHHg6FG_Jr7COZENaV4ubH-sTennO7YmigFB-vik4Qb0RG8a8UJC75TLx1Fq5tjbs4tb3UXjW9tJTG_tJYmhf4gEOf3BsoznO069U9NBkHc6sKDrWZrkYLlKkmc5mx-rudyq5egXgMPmrTIyKXUMD557Mea-MMq1dZDBRUB", 
    "p":"8s9ZSaakrML_fqFAXxlXGS86Msw45EB4wDK_ZrbnExsO9A-UoqWnmm7izBmJaeot_fPG23Il77wUnPslyg_C-_QkTlVKnkhcO97_otghplxIuJ_-PWLwYQXzVkNLENfcwmyTVzjFMyoHbFSAZ2z1ncBp_f4dYgl-6jApc4BpI4E", 
    "q":"2Q1qwDsEUXhNyE1CSktw1m4oUPBAL-rBRtiJufy2rRPzROnF6A5tup8zvEeR9UzYCKhFhowlhWPkODshKHAi2pkhIuxZ7Jsy8S1ZNp-whtwSXZE91VDTO-o8MnS_27JiyUmOObVUvGRLahj6SODLVeAIIWIyH73ZgdBY3pK4OwE", 
    "dp":"NU2FiWCW2AI6ul7F1dqnPzUZ7prchmcM2wyI7hCK66vN_ZAKDiaVg5aCHVIh02mATTad2gDWCSnd0JRluFT7dfojmjqpFdRGwzHyJpqR0IaDxFwDIRC-Ol5nC_Hb4cexg9D4C3a_-7pnRMXMJmhKByZ9Xi_R3Xq-LMUD5II1EoE", 
    "dq":"vhLYy_QiqPGQM_ssNQFxk-Ytmgt6Ojv6-35-xYd_tXuGCnAppjiUcNwfox6Nu-GKQbKSB-xMo05BudhWBiKE8ycr9HhDm0ahysAqowIexUqNLrEVE-vOv2Y1Rv4kUVEa3yhxyyl3Re8Sd5vd-doZVl903z8to8xOYDbCzE5x1QE", 
    "qi":"68jRQiBJmQITigDPQQ-M7FP7xmFRlDorG6ORdkqimAPZDln8EmNLsczH3b_WwaAxn9Js8jbp1TrcNcxoKTxriGMR9geG_0gxihZS8KwUgean8kxi42bfLcTiafs1zGbp-QtDVmIhF5weaCRH8fs0PgPxvuW3g6wBhzK5XYC7OkA", 
    "alg":"RS256", 
    "kid":"2011-04-29" 
})";
const auto invalid_prvkey = R"({
    "kty":"RSA",
    "n":"nnnn",
    "e":"eeee",
    "d":"dddd",
    "p":"pppp",
    "q":"qqqq",
    "dp":"dpdp",
    "dq":"dqdq",
    "qi":"qiqi",
    "alg":"RS256",
    "kid":"2011-04-29"
})";


const auto json_peerid = R"({
    "id": "Qma3GsJmB47xYuyahPZPSadh1avvxfyYQwk8R3UnFrQ6aP",
    "privKey" : "CAASpwkwggSjAgEAAoIBAQCaNSDOjPz6T8HZsf7LDpxiQRiN2OjeyIHUS05p8QWOr3EFUCFsC31R4moihE5HN+FxNalUyyFZU//yjf1pdnlMJqrVByJSMa+y2y4x2FucpoCAO97Tx+iWzwlZ2UXEUXM1Y81mhPbeWXy+wP2xElTgIER0Tsn/thoA0SD2u9wJuVvM7dB7cBcHYmqV6JH+KWCedRTum6O1BssqP/4Lbm2+rkrbZ4+oVRoU2DRLoFhKqwqLtylrbuj4XOI3XykMXV5+uQXz1JzubNOB9lsc6K+eRC+w8hhhDuFMgzkZ4qomCnx3uhO67KaICd8yqqBa6PJ/+fBM5Xk4hjyR40bwcf41AgMBAAECggEAZnrCJ6IYiLyyRdr9SbKXCNDb4YByGYPEi/HT1aHgIJfFE1PSMjxcdytxfyjP4JJpVtPjiT9JFVU2ddoYu5qJN6tGwjVwgJEWg1UXmPaAw1T/drjS94kVsAs82qICtFmwp52Apg3dBZ0Qwq/8qE1XbG7lLyohIbfCBiL0tiPYMfkcsN9gnFT/kFCX0LVs2pa9fHCRMY9rqCc4/rWJa1w8sMuQ23y4lDaxKF9OZVvOHFQkbBDrkquWHE4r55fchCz/rJklkPJUNENuncBRu0/2X+p4IKFD1DnttXNwb8j4LPiSlLro1T0hiUr5gO2QmdYwXFF63Q3mjQy0+5I4eNbjjQKBgQDZvZy3gUKS/nQNkYfq9za80uLbIj/cWbO+ZZjXCsj0fNIcQFJcKMBoA7DjJvu2S/lf86/41YHkPdmrLAEQAkJ+5BBNOycjYK9minTEjIMMmZDTXXugZ62wnU6F46uLkgEChTqEP57Y6xwwV+JaEDFEsW5N1eE9lEVX9nGIr4phMwKBgQC1TazLuEt1WBx/iUT83ita7obXqoKNzwsS/MWfY2innzYZKDOqeSYZzLtt9uTtp4X4uLyPbYs0qFYhXLsUYMoGHNN8+NdjoyxCjQRJRBkMtaNR0lc5lVDWl3bTuJovjFCgAr9uqJrmI5OHcCIk/cDpdWb3nWaMihVlePmiTcTy9wKBgQCU0u7c1jKkudqks4XM6a+2HAYGdUBk4cLjLhnrUWnNAcuyl5wzdX8dGPi8KZb+IKuQE8WBNJ2VXVj7kBYh1QmSJVunDflQSvNYCOaKuOeRoxzD+y9Wkca74qkbBmPn/6FFEb7PSZTO+tPHjyodGNgz9XpJJRjQuBk1aDJtlF3m1QKBgE5SAr5ym65SZOU3UGUIOKRsfDW4Q/OsqDUImvpywCgBICaX9lHDShFFHwau7FA52ScL7vDquoMB4UtCOtLfyQYA9995w9oYCCurrVlVIJkb8jSLcADBHw3EmqF1kq3NqJqm9TmBfoDCh52vdCCUufxgKh33kfBOSlXuf7B8dgMbAoGAZ3r0/mBQX6S+s5+xCETMTSNv7TQzxgtURIpVs+ZVr2cMhWhiv+n0Omab9X9Z50se8cWl5lkvx8vn3D/XHHIPrMF6qk7RAXtvReb+PeitNvm0odqjFv0J2qki6fDs0HKwq4kojAXI1Md8Th0eobNjsy21fEEJT7uKMJdovI/SErI=",
    "pubKey" : "CAASpgIwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCaNSDOjPz6T8HZsf7LDpxiQRiN2OjeyIHUS05p8QWOr3EFUCFsC31R4moihE5HN+FxNalUyyFZU//yjf1pdnlMJqrVByJSMa+y2y4x2FucpoCAO97Tx+iWzwlZ2UXEUXM1Y81mhPbeWXy+wP2xElTgIER0Tsn/thoA0SD2u9wJuVvM7dB7cBcHYmqV6JH+KWCedRTum6O1BssqP/4Lbm2+rkrbZ4+oVRoU2DRLoFhKqwqLtylrbuj4XOI3XykMXV5+uQXz1JzubNOB9lsc6K+eRC+w8hhhDuFMgzkZ4qomCnx3uhO67KaICd8yqqBa6PJ/+fBM5Xk4hjyR40bwcf41AgMBAAE="
})";


const auto p1 = make_peerinfo(0, { "/tcp/1000", "/tcp/1001" });
const auto p2 = make_peerinfo(0, { "/tcp/2000", "/tcp/2001" });
const auto p3 = make_peerinfo(0, { "/tcp/3000", "/tcp/3001" });
const auto p4 = make_peerinfo(0, { "/tcp/4000", "/tcp/4001" });


TEST_CASE("PeerId")
{
    SECTION("Construct a new peerid from scratch") {
        auto pid = peerid::create(0);
        REQUIRE_FALSE(pid.sid().empty());
        REQUIRE_FALSE(pid.pubkey().empty());
        REQUIRE_FALSE(pid.privkey().empty());

        auto prv_ = pid.privkey().to_jwk();
        auto pub_ = pid.pubkey().to_jwk();
        auto sid = pid.sid();
    }

    SECTION("Construct a new peerid from a private key (keypair)") {
        auto pid = peerid{ crypto::rsa_private_key::from_jwk(jwk_prvkey) };
        REQUIRE(json::is_same(pid.privkey().to_jwk(), jwk_prvkey));
        REQUIRE(json::is_same(pid.pubkey().to_jwk(), jwk_pubkey));
        REQUIRE(pid.sid() == sid);
    }

    SECTION("Construct a new peerid from a public key") {
        auto pid = peerid{ crypto::rsa_public_key::from_jwk(jwk_pubkey) };
        REQUIRE(pid.privkey().empty());
        REQUIRE(json::is_same(pid.pubkey().to_jwk(), jwk_pubkey));
        REQUIRE(pid.sid() == sid);
    }

    SECTION("Construct a new peerid from an id string") {
        auto pid = peerid{ sid };
        REQUIRE(pid.privkey().empty());
        REQUIRE(pid.pubkey().empty());
        REQUIRE(pid.sid() == sid);
    }

    SECTION("Construct a new peerid from another peerid") {
        auto pid_src = peerid::create(0);
        auto pid = peerid{ pid_src };
        REQUIRE(pid == pid_src);
    }

    SECTION("Set the private key of a peerid") {
        auto pid = peerid{ sid };

        // "The provided private key is empty"
        REQUIRE_THROWS(pid.set(crypto::rsa_private_key{}));

        // OK
        REQUIRE_NOTHROW(pid.set(crypto::rsa_private_key::from_jwk(jwk_prvkey)));

        // "Cannot change the private key of a peerid"
        REQUIRE_THROWS(pid.set(crypto::rsa_private_key::from_jwk(jwk_prvkey)));

        // "The provided private key does not match with the peer's id"
        REQUIRE_THROWS(pid.set(crypto::rsa_private_key::from_jwk(invalid_prvkey)));
    }

    SECTION("Set the public key of a peerid") {
        auto pid = peerid{ sid };

        // "The provided public key is empty"
        REQUIRE_THROWS(pid.set(crypto::rsa_public_key{}));

        // OK
        REQUIRE_NOTHROW(pid.set(crypto::rsa_public_key::from_jwk(jwk_pubkey)));

        // "Cannot change the public key of a peerid"
        REQUIRE_THROWS(pid.set(crypto::rsa_public_key::from_jwk(jwk_pubkey)));

        // "The provided public key does not match with the peer's id"
        REQUIRE_THROWS(pid.set(crypto::rsa_public_key::from_jwk(invalid_pubkey)));
    }

    SECTION("Compare peerid") {
        auto pid1 = peerid::create(0);
        auto pid2 = peerid::create(0);
        auto pid3 = peerid{ pid2 };

        REQUIRE(pid1 != pid2);
        REQUIRE(pid2 == pid3);
        REQUIRE((pid1 < pid3 || pid3 < pid1));
    }

    SECTION("JSON conversions") {
        auto pid = peerid::create(0);

        REQUIRE(peerid::from_json(pid.to_json()) == pid);
    }
}

TEST_CASE("PeerInfo")
{
    auto peer = make_peerinfo(0);

    // TCP port 5001
    auto addr = multiaddr{ "/ip4/1.2.3.4/tcp/5001" };
    REQUIRE_NOTHROW(peer.add(addr));

    // UDP port 8001
    REQUIRE_NOTHROW(peer.add("/ip4/1.2.3.4/udp/8001"));

    // mic/speaker soundwaves using frequencies 697 and 1209
    REQUIRE_THROWS(peer.add("/sonic/bfsk/697/1209"));
}


TEST_CASE("PeerStore")
{
    SECTION("Create an empty store and insert items") {
        auto store = peerstore{};
        REQUIRE(store.size() == 0);
        REQUIRE(store.insert(p1) == p1);
        REQUIRE(store.insert(p2) == p2);
        REQUIRE(store.insert(p3) == p3);
        REQUIRE(store.size() == 3);
    }

    SECTION("Initialize a new store with a list of items") {
        auto store = peerstore{p1, p2, p3};
        REQUIRE(store.size() == 3);
    }

    SECTION("Check the presence of a peer") {
        auto store = peerstore{ p1, p2 };

        REQUIRE(store.has(p1)); // with peerinfo
        REQUIRE(store.has(p2.id())); // with peerid
        REQUIRE(store.has(p2.id().sid())); // with encoded_string
        //REQUIRE(store.has(p2.id().id().str())); // with std::string
        REQUIRE_FALSE(store.has(p3));
    }

    SECTION("insert existing id and merge") {
        auto store = peerstore{p1};

        auto id = p1.id();
        auto pa = peerinfo(id, { "/tcp/1002" });

        auto pb = store.insert(pa, peerstore::merge);
        auto pc = store.at(id);

        REQUIRE(pb == pc);
        REQUIRE(pb.addrs().size() == 3);
    }

    SECTION("insert existing id and replace") {
        auto store = peerstore{p2};

        auto id = p2.id();
        auto pa = peerinfo(id, { "/tcp/2002" });

        auto pb = store.insert(pa, peerstore::replace);
        auto pc = store.at(id);

        REQUIRE(pb == pc);
        REQUIRE(pb == pa);
    }

    SECTION("try to insert existing id, but do nothing") {
        auto store = peerstore{ p3 };

        auto id = p3.id();
        auto pa = peerinfo(id, { "/tcp/3002" });

        auto pb = store.insert(pa, peerstore::nothing);
        auto pc = store.at(id);

        REQUIRE(pb == pc);
        REQUIRE(pb == p3);
    }

}