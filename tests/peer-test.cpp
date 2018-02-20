#include <catch.hpp>

#define GSL_THROW_ON_CONTRACT_VIOLATION
#include <p2p/peer.h>
#include <p2p/utils/json.h>

using namespace p2p;
using namespace multiformats;


const auto sid = "QmbvS8dBukqY6MvEUfDXUTn6id9CYKNs9T15FY72Yj4VFW";

const auto jwk_pubkey = R"({
    "kty":"RSA",
    "n":"nyneL7UQoxFFpTtjf3qsBbLU8MUQFoRcfCFLh94X49Qs4i8rozZnrrRulKFOGXBi3ySijLfgnB-rRlAK5x9R5dIPZzTtItXbABZTBZQyVj6F9JcDbINnPP1_PlX3TVvt5GVXSupYJwZjo29bhVmhLT2eqoNc89Yz0vmp3NTKBlMUgaGDoaf5_SMY_5XrnNar68Ys0w115igkhXPmPgA0ClFZ2Xx4kl18ed9ktmop7oyHN2qWBrQyiWDc5B2aEOgCRodDLCfDupHkM4xCTJ_UaxYLjeUiaYDmNVITCp2TcZ-FgRGzZNAEozM1a27aXbJ6kqTGJ-AI1GQbxM6O7OfGWw",
    "e":"AQAB"
})";
const auto invalid_pubkey = R"({
    "kty":"RSA",
    "n":"nnnn",
    "e":"eeee"
})";

const auto jwk_prvkey = R"({
    "kty":"RSA",
    "n":"nyneL7UQoxFFpTtjf3qsBbLU8MUQFoRcfCFLh94X49Qs4i8rozZnrrRulKFOGXBi3ySijLfgnB-rRlAK5x9R5dIPZzTtItXbABZTBZQyVj6F9JcDbINnPP1_PlX3TVvt5GVXSupYJwZjo29bhVmhLT2eqoNc89Yz0vmp3NTKBlMUgaGDoaf5_SMY_5XrnNar68Ys0w115igkhXPmPgA0ClFZ2Xx4kl18ed9ktmop7oyHN2qWBrQyiWDc5B2aEOgCRodDLCfDupHkM4xCTJ_UaxYLjeUiaYDmNVITCp2TcZ-FgRGzZNAEozM1a27aXbJ6kqTGJ-AI1GQbxM6O7OfGWw",
    "e":"AQAB",
    "d":"CI9DXDR0HxjsMm0ltjLeMnZCHmqyqUtX__L4cWefyEheW5Gm2qGv5MTeV47vOM4C-zYoqcGvyiWn2-GtHG3iRSZNXsMJZ8CxhOkucNPd-yZkpNlEPV85u510bOFJqfbiLdDHZ4d_0yV0UVNJTDwcP2cbc9cZtiFUaymzGWW2Ma3LaOjNT1H76ThuWUECisMJwlCB-PNENYnTsj5hILDw6YxuolwWSYr4-bO6QvwGnJoNdQ-ygcSmHnD2h8dbLflYJF_mnJx1LGdWu921eZOuxE-R7nLI2yzP6uycOKVLF1lYytbxIn6hmAcQjxKFZqJ5X4oj61RVLgAZ0fb-kNXuxQ",
    "p":"0JOKQF85MSe2gkIGe-HRxOUWkcbyNOvsVMMcJxpZoYbUGEFw6W8a9dgqJXOlh_Amr47iIg9JwpZDFRJOBWhhql7lL0H6934y_vN3ASyQrFIO4mpiGtc4_1ji8mnglBIrIW2BL4ucYjHeZ2pOPSXJQwAElmDn_NR1BRL_0VYBp4c",
    "q":"w1oxGssStB43H_hCWY6rhjcT0f-PRpWh4dcJvyJWmCS_vWDKZTfegcnuxrVmkHF5oYmUXC5jgkiHSLpk_iLESsdFeEtta_gOn96cnsQ85C9f-ZkgqRO0AurHASiZkjFor795IOzLLgjVzBHT12xvTLVYEEraz5R8vSGtlKwbt40",
    "dp":"A33EvakaYvlAM9P5Gc_A3CPdidkjqsEcNpsBeKIXR_3ixPkrc6zZba4NnozeA3WAoEWrAVjyKiCrxMmGps6Fe_2UpoLbOZNSNTRMFKfzT_8boqyXMc3SdWu-eMJO8QuQz0Fu_SXAG2CsUVzVLG7afJWefgnnODMyNkCIKa_f3Tc",
    "dq":"aBPRPZkbqeK_M8UsdFJSh_soECW7y7tEt_G9O5urzvslPFwo-Kw_W56eHDfhIOuUBcAqzsHYOj0x9kl4LP2Q3tYz6NcmwPMzt3D-uIeMeXXUCELQ58ObkEJNLAzZZM32HExC2IvP5ALJBSQqXQdkdNXYyTVYRmex3YHn3OGlErE",
    "qi":"NtRZLkz4LBQzEMzyuyUzgBGjXQd4H9HxUIh6R7DMyIzL7wcppvA2tjnjf7w66lXUvxklak-wAD_dpLGRvsjb1PR3zHLW3YWspYXuKMm5LMgOQojKx_Q7DNqk7QEDVJy8aZhxTS0-TSev5RTkMV1RDszxKCq4Nv7eXtffSjNqrjk",
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