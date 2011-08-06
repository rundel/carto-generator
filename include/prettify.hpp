#ifndef PRETTIFY_HPP
#define PRETTIFY_HPP

std::string prettify(std::string in, std::string base_indent = "", std::string indent = "    ") {
    
    std::string out(base_indent);
    out.reserve(in.size());
    
    char cur, prev = ' ';
    bool in_quote = false;
    int depth = 0;
    
    std::string::iterator it;
    for(it=in.begin(); it<in.end(); ++it ) {
        
        cur = *it;
        
        if ((cur == '}' || cur == ']') )//&& !in_quote)
            depth--;
        
        if (prev == '\n') {
            //out.append(base_indent);
            //if (!in_quote) {
                int j=depth;
                while (j-- != 0) {
                    out.append(indent);
                }
            //}
        }
        
        if ((cur == '{' || cur == '[') )//&& !in_quote)
            depth++;
        
        if (cur == '"' && prev != '\\')
            in_quote = !in_quote;
        
        out.push_back(cur);
        
        prev = cur;
    }
    
    return out;
}

#endif