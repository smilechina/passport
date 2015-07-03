//
//  SAPIXmlDictionary.m
//  SAPIDemo
//
//  Created by guomeisong on 13-4-3.
//
//

#import "XmlDictionary.h"

@interface XmlDictionaryParser : NSObject<NSXMLParserDelegate>

@property (nonatomic, strong) NSMutableDictionary *root;
@property (nonatomic, strong) NSMutableArray *stack;
@property (nonatomic, strong, readonly) NSMutableDictionary *top;
@property (nonatomic, strong) NSMutableString *text;

@end

@implementation XmlDictionaryParser

- (XmlDictionaryParser *)initWithXMLData:(NSData *)data
{
    self = [super init];
    if (self) {
        NSXMLParser * parser = [[NSXMLParser alloc] initWithData:data];
        [parser setDelegate:self];
		[parser parse];
    }
    return self;
}

- (NSMutableDictionary *)top
{
	return [_stack lastObject];
}

- (void)endText
{
    //替换空格    
	if (TRIM_WHITE_SPACE)
	{
		_text = (NSMutableString *)[_text stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
	}
    //获取元素中的text
	if (_text && ![_text isEqualToString:@""] && [XML_TEXT_KEY length])
	{
		id existing = [self.top objectForKey:XML_TEXT_KEY];
		if (existing)
		{
			if ([existing isKindOfClass:[NSMutableArray class]])
			{
				[(NSMutableArray *)existing addObject:_text];
			}
			else
			{
				[self.top setObject:[NSMutableArray arrayWithObjects:existing, _text, nil] forKey:XML_TEXT_KEY];
			}
		}
		else
		{
			[self.top setObject:_text forKey:XML_TEXT_KEY];
		}
	}
	self.text = nil;
}

//遍历数据节点，获取元素属性
- (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName attributes:(NSDictionary *)attributeDict
{
	[self endText];
	
	NSMutableDictionary *node = [NSMutableDictionary dictionary];
	if ([XML_NAME_KEY length])
	{
        //存储节点名
		[node setObject:elementName forKey:XML_NAME_KEY];
	}
	
    //判断是否存在数据，没有则存储首个元素
	if (!self.top)
	{
		self.root = node;
		self.stack = [NSMutableArray arrayWithObject:node];
	}
	else
	{
		id existing = [self.top objectForKey:elementName];
		if (existing)
		{
            //存在元素 添加到已有数组或lastobject
			if ([existing isKindOfClass:[NSMutableArray class]])
			{
				[(NSMutableArray *)existing addObject:node];
			}
			else
			{
				[self.top setObject:[NSMutableArray arrayWithObjects:existing, node, nil] forKey:elementName];
			}
		}
		else
		{
			[self.top setObject:node forKey:elementName];
		}
		[_stack addObject:node];
	}
}

//从元素节点获取元素节点名
- (NSString *)nameForNode:(NSDictionary *)node inDictionary:(NSDictionary *)dict
{
	if (node.nodeName)
	{
		return node.nodeName;
	}
	else
	{
		for (NSString *name in dict)
		{
			id object = [dict objectForKey:name];
			if (object == node)
			{
				return name;
			}
			else if ([object isKindOfClass:[NSArray class]])
			{
				if ([(NSArray *)object containsObject:node])
				{
					return name;
				}
			}
		}
	}
	return nil;
}

//遍历结束处理函数，保存元素数据
- (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName
{
	[self endText];
	if (COLLAPSE_TEXT_NODES && !self.top.childNodes && self.top.innerText)
	{
		NSDictionary *node = self.top;
		[_stack removeLastObject];
		NSString *nodeName = [self nameForNode:node inDictionary:self.top];
		if (nodeName)
		{
			id parentNode = [self.top objectForKey:nodeName];
			if ([parentNode isKindOfClass:[NSMutableArray class]])
			{
				[parentNode replaceObjectAtIndex:[parentNode count] - 1 withObject:node.innerText];
			}
			else
			{
				[self.top setObject:node.innerText forKey:nodeName];
			}
		}
	}
	else
	{
		[_stack removeLastObject];
	}
}

//获取元素节点包含内容字符
- (void)parser:(NSXMLParser *)parser foundCharacters:(NSString *)string
{
    if (!_text)
	{
		_text = [NSMutableString stringWithString:string];
	}
	else
	{
		[_text appendString:string];
	}
}

@end


@implementation NSDictionary(SAPIXmlDictionary)

+ (NSDictionary *)dictionaryWithXMLData:(NSData *)data
{
    XmlDictionaryParser * tmpObj = [[XmlDictionaryParser alloc] initWithXMLData :data];
	return [tmpObj root];
}

+ (NSDictionary *)dictionaryWithXMLString:(NSString *)string
{
    
	NSData *data = [string dataUsingEncoding:NSUTF8StringEncoding];
	return [NSDictionary dictionaryWithXMLData:data];
}


- (NSDictionary *)childNodes
{
	NSMutableDictionary *filteredDict = [NSMutableDictionary dictionaryWithDictionary:self];
	[filteredDict removeObjectsForKeys:[NSArray arrayWithObjects: XML_TEXT_KEY, XML_NAME_KEY, nil]];
    return [filteredDict count]? filteredDict: nil;
}

//获取节点名
- (NSString *)nodeName
{
	return [self objectForKey:XML_NAME_KEY];
}

//获取属性内容
- (id)innerText
{
	id text = [self objectForKey:XML_TEXT_KEY];
    //如果是数组转换为string
	if ([text isKindOfClass:[NSArray class]])
	{
		return [text componentsJoinedByString:@"\n"];
	}
	else
	{
		return text? text : @"";
	}
}

@end


