std::string prettify(std::string in, std::string indent = "    ") {
    
    std::string out;
    out.reserve(in.size());
    
    char cur, prev = '';
    bool in_quote = false;
    int depth = 0;
    
    std::string::iterator it;
    for(it=in.begin(); it<in.end(); ++it ) {
        
        cur = *it;
        
        if ((cur == '}' || cur == ']') && !in_quote)
            depth--;
        
        if (prev == '\n' && !in_quote) {
            int j=depth;
            while(j-- !=0 ) {
                out.append(indent);
            }
        }
        
        if ((cur == '{' || cur == '[') && !in_quote)
            depth++;
        
        if (cur == '"' && prev != '\\')
            in_quote = !in_quote;
        
        out.push_back(cur);
        
        prev = cur;
    }
    
    return out;
}
 