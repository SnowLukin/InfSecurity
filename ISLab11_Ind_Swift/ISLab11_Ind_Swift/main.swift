//
//  main.swift
//  ISLab11_Ind_Swift
//
//  Created by Snow Lukin on 08.12.2022.
//

import Foundation

struct DESConfig {
    static let shared = DESConfig()
    var key: String = "DyfmgL9p"
    var iVValue: String = "nzug8FrX"
    private init() {}
}

public class EncryptionUtitlity: NSObject {
    public func methodToCallEncryption( stringToEncrypt : String ) -> String {
        let iVValue: String = DESConfig.shared.iVValue
        let keyValue = DESConfig.shared.key
        let encoded = stringToEncrypt.desEncrypt(key: keyValue, iv: iVValue)
        return encoded!
    }
    
    public func methodToCallDecryption( stringToDecrypt : String ) -> String {
        let iVValue: String = DESConfig.shared.iVValue
        let keyValue = DESConfig.shared.key
        let decoded = stringToDecrypt.desDecrypt(key: keyValue, iv: iVValue)
        return decoded!
    }
}

let enc = EncryptionUtitlity().methodToCallEncryption(stringToEncrypt: "something")
let dec = EncryptionUtitlity().methodToCallDecryption(stringToDecrypt: enc)
print(enc)
print(dec)
