#include <iostream> 
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;
 
////////////////////////////////////////////////////////////////// Record class used to print the values - not need at all  /////////////////////////////////////////////////////////////////////////////////////////////
class Record{
    string r_class_order_id,r_instrument;
    int r_side,r_quantity;
    double r_price;

    public:

        Record (string a , string b, int c, int d, double e){
            r_class_order_id = a;
            r_instrument = b;
            r_side = c;
            r_quantity = d;
            r_price = e;
        } 
        void print(){
            cout << "r_class_order_id: " << r_class_order_id << endl;
            cout << "r_instrument: " << r_instrument << endl;
            cout << "r_side: " << r_side  << endl;
            cout << "r_quantity: " << r_quantity << endl;
            cout << "r_price: " << r_price << endl;
            cout << "//////DONE/////" << endl;

        }

};
///////////////////////////////////////////////////////function that will display the values - not need at all/////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////Get time//////////////////////////////////////////////////////////////////////////
string get_time(){

    // Get the current time point
    auto now = std::chrono::system_clock::now();
    
    // Convert to time_t (C-style time representation)
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    
    // Get milliseconds part
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    // Format the time as "YYYYMMDD-HHMMSS.sss"
    std::tm* tm_struct = std::localtime(&now_time_t);
    char time_str[20];
    std::strftime(time_str, sizeof(time_str), "%Y%m%d-%H%M%S", tm_struct);
    
    // Construct the final timestamp string
    std::ostringstream oss;
    oss << time_str << "." << std::setw(3) << std::setfill('0') << ms.count();

    //std::cout << "Timestamp: " << oss.str() << std::endl;
    return oss.str();
}
///////////////////////////////////////////////////////////Order Book Buy////////////////////////////////////////////////////////////////////////////

struct Order_book_buy{

    int o_side;
    string o_id;
    double o_price;
    int o_quantity;
    int o_given_id;
    
     Order_book_buy(int given_id,int side,string id ,double price,int quantity ){ // initialize the values on the buy side ofthe order book
        o_side=side;
        o_id = id;
        o_price=price;
        o_quantity=quantity;
        o_given_id = given_id;
    }
    void print_ob(){
        cout << "o_side: " << o_side << "  ";
        cout << "o_id: " << o_id << "  ";
        cout << "o_price: " << o_price << "  ";
        cout << "o_quantity: " << o_quantity << "  ";
    }
    bool operator <(Order_book_buy obj) const {     // logic of the sorting 
        return (o_price >  obj.o_price);
    }
};

/// Order Book sell  /////////////////////////////////////////////Order Book Sell/////////////////////////////////////////////////////////////////////////
struct Order_book_sell{

    int o_side;
    string o_id;
    double o_price;
    int o_quantity;
    int o_given_id;
    
     Order_book_sell(int given_id,int side,string id ,double price,int quantity ){   // initialize the values on the sell side of the order book
        o_side=side;
        o_id = id;
        o_price=price;
        o_quantity=quantity;
        o_given_id = given_id;
    }
    void print_ob(){
        cout << "o_side: " << o_side << "  ";
        cout << "o_id: " << o_id << "  ";
        cout << "o_price: " << o_price << "  ";
        cout << "o_quantity: " << o_quantity << "  ";
    }
    bool operator <(Order_book_sell obj) const {    // logic of the sorting
        return (o_price <  obj.o_price);
    }


};
//////////////////////////////////////////////////Logic of filling the order book for buy is the new arrive order////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////logic of book filling deleted as it added to the main function//////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////Order class still constructing/////////////////////////////////////////////////////////
class Order{

    string e_client_order_id;
    string e_order_id;
    string e_instrument;
    int e_side;
    double e_price;
    int e_quantity;
    int e_status;
    string e_reason;
    string e_transaction_time;

    Order(){

    }

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{   
    ifstream inputfile; // a variable to have the input file
    inputfile.open("C:\\Users\\User\\Desktop\\lseg_proj\\order_l.csv"); // location of the input file
    
    ofstream outputfile;
    outputfile.open("C:\\Users\\User\\Desktop\\lseg_proj\\execution_rep.csv");
    outputfile << "client_order_id " << "," << "order_id  "<< ","  << "instrument"<< " , "  << "side"<< " , "  << "price"<< " , "  << "quantity"<< " , "  << "status"<< " , "  << "reason"<< " , "  << "transaction_time" << " , " << endl  ;
    
    string line="";

    vector <Record> students;
    vector <Order_book_buy> OB_buy;
    vector <Order_book_sell> OB_sell;

    vector <Order_book_buy> OB_buy_rose;
    vector <Order_book_sell> OB_sell_rose;

    vector <Order_book_buy> OB_buy_lavender;
    vector <Order_book_sell> OB_sell_lavender;

    vector <Order_book_buy> OB_buy_tulip;
    vector <Order_book_sell> OB_sell_tulip;

    vector <Order_book_buy> OB_buy_orchid;
    vector <Order_book_sell> OB_sell_orchid;

    vector <Order_book_buy> OB_buy_lotus;
    vector <Order_book_sell> OB_sell_lotus;


    int count = -1;

    while(getline(inputfile,line)){  // with in a while loop reading the input file by line by line
       


        if(count<0){count++;continue;} // to ignore the first line which is just the header file of the input file
        count++;
        string class_order_id;
        string instrument;
        int side;
        int quantity;
        double price;
        string tempString;

        stringstream inputString(line);

        getline(inputString, class_order_id, ',');

        getline(inputString, instrument, ',');
        
        getline(inputString, tempString, ',');
        side = atoi(tempString.c_str());

        getline(inputString, tempString, ',');
        quantity = atoi(tempString.c_str());

        getline(inputString, tempString, ',');
        price = stod(tempString.c_str());

        Record rec_student(class_order_id,instrument,side,quantity,price);
        students.push_back(rec_student);

        string reason ;
        bool is_valid=true;
        
        if(quantity>1000 || quantity<10 ){
            reason = "quantity is outside the range";
             is_valid=false;
        }else if(quantity%10!=0){
            reason = "quantity is not a multiple of 10";
             is_valid=false;
        }else if(price<=0){
            reason = "Price is not greater than 0";
             is_valid=false;

        }else if(instrument != "Rose" && instrument != "Lavender" && instrument != "Tulip" && instrument != "Orchid" && instrument != "Lotus" ){
            reason = "Not a valid instrument";
             is_valid=false;
        }else if(side!=1 && side!=2){
            reason = "Not a valid side";
             is_valid=false;
        }
        
        if(!is_valid){
            outputfile << "Order" << count << " ," << class_order_id << " ," << instrument << " ," <<side << ", " << price << " ," << quantity << " ," << "Reject" << " ," << reason << " ," << get_time() << endl;
            continue;
        }else{
        /*Record rec(class_order_id,instrument,side,quantity,price);
        rec.print();
        cout << "//////////////////////////////\n" ;*/
        if(instrument=="Rose"){
            OB_buy = OB_buy_rose;
            OB_sell = OB_sell_rose;
        }
        if(instrument=="Lavender"){
            OB_buy = OB_buy_lavender;
            OB_sell = OB_sell_lavender;
        }
        if(instrument=="Tulip"){
            OB_buy = OB_buy_tulip;
            OB_sell = OB_sell_tulip;
        }
        if(instrument=="Orchid"){
            OB_buy = OB_buy_orchid;
            OB_sell = OB_sell_orchid;
        }
        if(instrument=="Lotus"){
            OB_buy = OB_buy_lotus;
            OB_sell = OB_sell_lotus;
        }

        vector <Order_book_buy> vb ;
        vector <Order_book_sell> vs;


        if(side==1){    // check whether the order is in the buy side
            Order_book_buy book(count,side,class_order_id,price,quantity);
            OB_buy.push_back(book);
            sort(OB_buy.begin(), OB_buy.end());
            bool need_loop_buy = true;      // Erase this code will work fine
            bool is_new=true;
            
             //////////////////////////////////////////
            if(OB_sell.size()==0){
                outputfile << "Order"<< count << ", " << class_order_id << ", " << instrument << ", " <<side << ", " << price << "," << quantity << ", " << "New"<< " ," << " ," << get_time() << endl;
            }


            while(need_loop_buy){
                if(OB_buy.size()>0 && OB_sell.size()>0){    
                    vb=OB_buy;
                    vs=OB_sell;
                    if(vb[0].o_price < vs[0].o_price  ){      // can not buy the order -- seling prices are too high
                        need_loop_buy = false;
                        if(is_new){
                            outputfile << "Order" << count << " ," << class_order_id << ", " << instrument << ", " <<side << ", " << price << " ," << quantity << " ," << "New" << " ,"<< " ," << " ," << get_time() << endl;
                        }
                    }
                    else if(vb[0].o_quantity <= vs[0].o_quantity){    // can completly buy the order from the top most seller
                        outputfile << "Order" << count << ", " << class_order_id << ", " << instrument << ", " <<side << ", " << vs[0].o_price << " ," << quantity << ", " << "Fill" << " ," << " ," << get_time() << endl;
                        
                        if(vs[0].o_quantity == vb[0].o_quantity){
                            outputfile <<  "Order " << vs[0].o_given_id << ", " << vs[0].o_id << " ," << instrument << " ," << vs[0].o_side<< " ," << vs[0].o_price << " ," << vb[0].o_quantity << " ," << "Fill"<< " ," << " ," << get_time() << endl;
                            vs.erase(vs.begin());
                        }else {
                            outputfile <<  "Order " << vs[0].o_given_id << ", " << vs[0].o_id << ", " << instrument << ", " << vs[0].o_side<< ", " << vs[0].o_price << " ," << vb[0].o_quantity << ", " << "pFill" << " ,"<< " ," << get_time() << endl;
                            vs[0].o_quantity = vs[0].o_quantity - vb[0].o_quantity;
                        }
                        vb.erase(vb.begin());
                        need_loop_buy = false;
                    }
                    else{    // need several sellers to thhink about what happens with the order
                        outputfile << "Order" << count << ", " << class_order_id << " ," << instrument << " ," <<side << ", " << vs[0].o_price << ", " << vs[0].o_quantity << ", " << "Pfill"<< " ," << ", "<< get_time() << endl;
                        outputfile << "Order" <<  vs[0].o_given_id << ", " << vs[0].o_id << " ," << instrument << " ," <<vs[0].o_side << " ," << vs[0].o_price << " ," << vs[0].o_quantity << ", " << "Fill"<< " ," << ", "  << get_time() << endl;
                        
                        vb[0].o_quantity = vb[0].o_quantity - vs[0].o_quantity;
                        quantity=vb[0].o_quantity;
                        vs.erase(vs.begin());        
                        is_new = false;            
                        }
                    OB_buy=vb;
                    OB_sell=vs;
                }else{
                    need_loop_buy = false;
                }
            }
               ///////////////////////////////////////////
             //logic

        }else if(side==2){  // check whether the order is on the sell side
            Order_book_sell book(count,side,class_order_id,price,quantity);
            OB_sell.push_back(book);
            sort(OB_sell.begin(), OB_sell.end());
            bool need_loop_sell=true;
            bool is_new=true;
            if(OB_buy.size()==0){
                outputfile << "Order" << count << " ," << class_order_id << ", " << instrument << ", " <<side << " ," << price << " ," << quantity << " ," << "New" << " ,"<< " ," << get_time() << endl;
            }
            while(need_loop_sell){
                /////////////////////////////////////////////////////
                
                if(OB_buy.size()>0 && OB_sell.size()>0){
                    
                    vb=OB_buy;
                    vs=OB_sell;
                    
                    if(vb[0].o_price < vs[0].o_price || vb.size()==0  ){      // can not buy the order -- seling pricesare too high
                        need_loop_sell=false;
                        if(is_new){
                            outputfile << "Order" << count << " ," << class_order_id << ", " << instrument << ", " <<side << ", " << price << " ," << quantity << " ," << "New" << " ,"<< ", " << get_time() << endl;
                        }
                    }
                    else if(vb[0].o_quantity >= vs[0].o_quantity){    // can completly buy the order from the top most seller
                        outputfile << "Order" << count << ", " << class_order_id << ", " << instrument << " ," <<side << " ," << vb[0].o_price << " ," << quantity << ", " << "Fill"<< " ," << ", " << get_time() << endl;
                        
                        
                        if(vb[0].o_quantity == vs[0].o_quantity){
                            outputfile <<  "Order" << vb[0].o_given_id << "," << vb[0].o_id << " ," << instrument << " ," <<vb[0].o_side << " ," << vb[0].o_price << ", " << vb[0].o_quantity << " ," << "Fill"<< " ," << " ," << get_time() << endl;
                            vb.erase(vb.begin());
                            
                        }else{
                            outputfile <<  "Order" << vb[0].o_given_id << " ," << vb[0].o_id << ", " << instrument << ", " <<vb[0].o_side << " ," << vb[0].o_price << " ," << vs[0].o_quantity << " ," << "Fill" << " ,"<< ", " << get_time() << endl;
                            vb[0].o_quantity = vb[0].o_quantity - vs[0].o_quantity;
                        }
                        vs.erase(vs.begin());
                        need_loop_sell=false;
                    }
                    else{    // need several sellers to think about what happens with the order
                        //outputfile need to be written
                        outputfile << "Order" << count << ", " << class_order_id << ", " << instrument << " ," <<side << " ," << vb[0].o_price << " ," << vb[0].o_quantity << ", " << "Pfill" << " ,"<< " ," << get_time() << endl;
                        outputfile << "Order" << vb[0].o_given_id << " ," << vb[0].o_id << ", " << instrument << " ," <<vb[0].o_side << " ," << vb[0].o_price << " ," << vb[0].o_quantity << " ," << "Fill"<< " ," << " ," << get_time() << endl;
                         
                        vs[0].o_quantity = vs[0].o_quantity - vb[0].o_quantity;
                        quantity=vs[0].o_quantity;
                        vb.erase(vb.begin());
                         is_new = false;
                       
                    }
                    OB_buy=vb;
                    OB_sell=vs;
                }else{
                    need_loop_sell = false;
                }
            }
                //////////////////////////////////////////////s///////
        }
        if(instrument=="Rose"){
            OB_buy_rose = OB_buy;
            OB_sell_rose = OB_sell;
        }
        if(instrument=="Lavender"){
            OB_buy_lavender = OB_buy;
            OB_sell_lavender = OB_sell;
        }
        if(instrument=="Tulip"){
            OB_buy_tulip = OB_buy;
            OB_sell_tulip = OB_sell;
        }
        if(instrument=="Orchid"){
            OB_buy_orchid = OB_buy;
            OB_sell_orchid = OB_sell;
        }
        if(instrument=="Lotus"){
            OB_buy_lotus = OB_buy;
            OB_sell_lotus = OB_sell;
        }
       

        }
    }   
 /*       
        cout << "Order Book Buy Rose is: " << endl;
        for (Order_book_buy num : OB_buy_rose) {
            num.print_ob() ;
            cout << "order book dum dum" << endl;
        }
        cout << "\n" << endl;
        cout << "Order Book Sell Rose is: " << endl;
        for (Order_book_sell num : OB_sell_rose) {
            num.print_ob() ;
            cout << "order book dum dum" << endl;
        }
        cout << "////////////////////////////////////////////" << endl;
         cout << "Order Book Buy lavender is: " << endl;
        for (Order_book_buy num : OB_buy_lavender) {
            num.print_ob() ;
            cout << "order book dum dum" << endl;
        }
        cout << "\n" << endl;
        cout << "Order Book Sell lavender is: " << endl;
        for (Order_book_sell num : OB_sell_lavender) {
            num.print_ob() ;
            cout << "order book dum dum" << endl;
        }
        cout << "////////////////////////////////////////////" << endl;
         cout << "Order Book Buy tulip is: " << endl;
        for (Order_book_buy num : OB_buy_tulip) {
            num.print_ob() ;
            cout << "order book dum dum" << endl;
        }
        cout << "\n" << endl;
        cout << "Order Book Sell tulip is: " << endl;
        for (Order_book_sell num : OB_sell_tulip) {
            num.print_ob() ;
            cout << "order book dum dum" << endl;
        }
        cout << "////////////////////////////////////////////" << endl;
         cout << "Order Book Buy orchid is: " << endl;
        for (Order_book_buy num : OB_buy_orchid) {
            num.print_ob() ;
            cout << "order book dum dum" << endl;
        }
        cout << "\n" << endl;
        cout << "Order Book Sell orchid is: " << endl;
        for (Order_book_sell num : OB_sell_orchid) {
            num.print_ob() ;
            cout << "order book dum dum" << endl;
        }
        cout << "////////////////////////////////////////////" << endl;
         cout << "Order Book Buy lotus is: " << endl;
        for (Order_book_buy num : OB_buy_lotus) {
            num.print_ob() ;
            cout << "order book dum dum" << endl;
        }
        cout << "\n" << endl;
        cout << "Order Book Sell lotus is: " << endl;
        for (Order_book_sell num : OB_sell_lotus) {
            num.print_ob() ;
            cout << "order book dum dum" << endl;
        }
        cout << "////////////////////////////////////////////" << endl;

*/




        //outputfile << "Order" << count << " " << class_order_id << " " << instrument << " " <<side << " " << price << " " << quantity << " " << "New" << " " << "reason??" << " " << get_time() << endl;

    //display_all(students);

}