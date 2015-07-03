//
//  XmlDictionary.h
//  SAPIDemo
//
//  Created by guomeisong on 13-4-3.
//
//

#import <Foundation/Foundation.h>


#define COLLAPSE_TEXT_NODES		YES
#define TRIM_WHITE_SPACE		YES

#define XML_TEXT_KEY			@"text"
#define XML_NAME_KEY			@"bodyName"

@interface NSDictionary (XMLDictionary)

+ (NSDictionary *)dictionaryWithXMLData:(NSData *)data;
+ (NSDictionary *)dictionaryWithXMLString:(NSString *)string;

- (NSDictionary *)childNodes;
- (NSString *)nodeName;
- (NSString *)innerText;

@end
