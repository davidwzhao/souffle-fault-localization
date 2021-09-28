
#include "souffle/CompiledSouffle.h"
#include <mutex>
#include "souffle/Incremental.h"

extern "C" {
}

namespace souffle {
using namespace ram;
struct t_btree_4__2_0_1_3__0_1_2_3__3__4__15_diff {
using t_tuple = Tuple<RamDomain, 4>;
struct updater_t_btree_4__2_0_1_3__0_1_2_3__3__4__15_diff {
bool update(t_tuple& old_t, const t_tuple& new_t) {
old_t[3] += new_t[3];
return true;
}
};
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<2,0,1,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<2,0,1>, updater_t_btree_4__2_0_1_3__0_1_2_3__3__4__15_diff>;
t_ind_0 ind_0;
using t_ind_1 = btree_set<t_tuple, index_utils::comparator<0,1,2,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,1,2>, updater_t_btree_4__2_0_1_3__0_1_2_3__3__4__15_diff>;
t_ind_1 ind_1;
using iterator = t_ind_1::iterator;
size_t approximate_size = 0;
struct context {
t_ind_0::operation_hints hints_0;
t_ind_1::operation_hints hints_1;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_1.insert(t, h.hints_1)) {
ind_0.insert(t, h.hints_0);
approximate_size++;
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[4];
std::copy(ramDomain, ramDomain + 4, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3) {
RamDomain data[4] = {a0,a1,a2,a3};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
if (other.empty()) return;
context h;
for (auto const& cur : other) {
insert(cur, h);
}
}
void relationLoad(const t_btree_4__2_0_1_3__0_1_2_3__3__4__15_diff& other) {
ind_0.clear();
ind_0 = other.ind_0;
ind_1.clear();
ind_1 = other.ind_1;
approximate_size = other.approximate_size;
}
bool contains(const t_tuple& t, context& h) const {
return ind_1.contains(t, h.hints_1);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_1.size();
}
size_t approx_size() const {
return approximate_size;
}
iterator find(const t_tuple& t, context& h) const {
return ind_1.find(t, h.hints_1);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_1.begin(),ind_1.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_1.begin(),ind_1.end());
}
range<t_ind_1::iterator> equalRange_3(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_1.lower_bound(low, h.hints_1), ind_1.upper_bound(high, h.hints_1));
}
range<t_ind_1::iterator> equalRange_3(const t_tuple& t) const {
context h;
return equalRange_3(t, h);
}
range<t_ind_0::iterator> equalRange_4(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_4(const t_tuple& t) const {
context h;
return equalRange_4(t, h);
}
range<t_ind_1::iterator> equalRange_15(const t_tuple& t, context& h) const {
auto pos = ind_1.find(t, h.hints_1);
auto fin = ind_1.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_1::iterator> equalRange_15(const t_tuple& t) const {
context h;
return equalRange_15(t, h);
}
bool empty() const {
return ind_1.empty();
}
std::vector<range<iterator>> partition() const {
return ind_1.getChunks(400);
}
void purge() {
ind_0.clear();
ind_1.clear();
approximate_size = 0;
}
iterator begin() const {
return ind_1.begin();
}
iterator end() const {
return ind_1.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
}
};
struct t_btree_4__0_1_2_3__3__15_diff {
using t_tuple = Tuple<RamDomain, 4>;
struct updater_t_btree_4__0_1_2_3__3__15_diff {
bool update(t_tuple& old_t, const t_tuple& new_t) {
old_t[3] += new_t[3];
return true;
}
};
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,1,2>, updater_t_btree_4__0_1_2_3__3__15_diff>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
size_t approximate_size = 0;
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
approximate_size++;
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[4];
std::copy(ramDomain, ramDomain + 4, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3) {
RamDomain data[4] = {a0,a1,a2,a3};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
if (other.empty()) return;
context h;
for (auto const& cur : other) {
insert(cur, h);
}
}
void relationLoad(const t_btree_4__0_1_2_3__3__15_diff& other) {
ind_0.clear();
ind_0 = other.ind_0;
approximate_size = other.approximate_size;
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
size_t approx_size() const {
return approximate_size;
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_3(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_3(const t_tuple& t) const {
context h;
return equalRange_3(t, h);
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t) const {
context h;
return equalRange_15(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
approximate_size = 0;
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
}
};
struct t_btree_4__2_0_1_3__1_0_2_3__0_1_2_3__1__2__3__4__7__15_diff_applied {
using t_tuple = Tuple<RamDomain, 4>;
struct updater_t_btree_4__2_0_1_3__1_0_2_3__0_1_2_3__1__2__3__4__7__15_diff_applied {
bool update(t_tuple& old_t, const t_tuple& new_t) {
if (new_t[3] == 0) {
old_t[3] = 0;
return true;
}
old_t[3] += new_t[3];
return true;
}
};
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<2,0,1,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<2,0,1>, updater_t_btree_4__2_0_1_3__1_0_2_3__0_1_2_3__1__2__3__4__7__15_diff_applied>;
t_ind_0 ind_0;
using t_ind_1 = btree_set<t_tuple, index_utils::comparator<1,0,2,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<1,0,2>, updater_t_btree_4__2_0_1_3__1_0_2_3__0_1_2_3__1__2__3__4__7__15_diff_applied>;
t_ind_1 ind_1;
using t_ind_2 = btree_set<t_tuple, index_utils::comparator<0,1,2,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,1,2>, updater_t_btree_4__2_0_1_3__1_0_2_3__0_1_2_3__1__2__3__4__7__15_diff_applied>;
t_ind_2 ind_2;
using iterator = t_ind_2::iterator;
size_t approximate_size = 0;
size_t approximate_size_per_iteration[50000] = {0};
struct context {
t_ind_0::operation_hints hints_0;
t_ind_1::operation_hints hints_1;
t_ind_2::operation_hints hints_2;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_2.insert(t, h.hints_2)) {
ind_0.insert(t, h.hints_0);
ind_1.insert(t, h.hints_1);
approximate_size++;
approximate_size_per_iteration[t[2]]++;
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[4];
std::copy(ramDomain, ramDomain + 4, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3) {
RamDomain data[4] = {a0,a1,a2,a3};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
if (other.empty()) return;
context h;
for (auto const& cur : other) {
insert(cur, h);
}
}
void relationLoad(const t_btree_4__2_0_1_3__1_0_2_3__0_1_2_3__1__2__3__4__7__15_diff_applied& other) {
ind_0.clear();
ind_0 = other.ind_0;
ind_1.clear();
ind_1 = other.ind_1;
ind_2.clear();
ind_2 = other.ind_2;
approximate_size = other.approximate_size;
for (size_t i = 0; i < 50000; i++) approximate_size_per_iteration[i] = other.approximate_size_per_iteration[i];
}
bool contains(const t_tuple& t, context& h) const {
return ind_2.contains(t, h.hints_2);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_2.size();
}
size_t approx_size() const {
return approximate_size;
}
size_t approx_size(size_t iter) const {
return approximate_size_per_iteration[iter];
}
iterator find(const t_tuple& t, context& h) const {
return ind_2.find(t, h.hints_2);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_2.begin(),ind_2.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_2.begin(),ind_2.end());
}
range<t_ind_2::iterator> equalRange_1(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_2.lower_bound(low, h.hints_2), ind_2.upper_bound(high, h.hints_2));
}
range<t_ind_2::iterator> equalRange_1(const t_tuple& t) const {
context h;
return equalRange_1(t, h);
}
range<t_ind_1::iterator> equalRange_2(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_1.lower_bound(low, h.hints_1), ind_1.upper_bound(high, h.hints_1));
}
range<t_ind_1::iterator> equalRange_2(const t_tuple& t) const {
context h;
return equalRange_2(t, h);
}
range<t_ind_2::iterator> equalRange_3(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_2.lower_bound(low, h.hints_2), ind_2.upper_bound(high, h.hints_2));
}
range<t_ind_2::iterator> equalRange_3(const t_tuple& t) const {
context h;
return equalRange_3(t, h);
}
range<t_ind_0::iterator> equalRange_4(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_4(const t_tuple& t) const {
context h;
return equalRange_4(t, h);
}
range<t_ind_1::iterator> equalRange_7(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_1.lower_bound(low, h.hints_1), ind_1.upper_bound(high, h.hints_1));
}
range<t_ind_1::iterator> equalRange_7(const t_tuple& t) const {
context h;
return equalRange_7(t, h);
}
range<t_ind_2::iterator> equalRange_15(const t_tuple& t, context& h) const {
auto pos = ind_2.find(t, h.hints_2);
auto fin = ind_2.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_2::iterator> equalRange_15(const t_tuple& t) const {
context h;
return equalRange_15(t, h);
}
bool empty() const {
return ind_2.empty();
}
std::vector<range<iterator>> partition() const {
return ind_2.getChunks(400);
}
void purge() {
ind_0.clear();
ind_1.clear();
ind_2.clear();
approximate_size = 0;
for (size_t i = 0; i < 50000; i++) approximate_size_per_iteration[i] = 0;
}
iterator begin() const {
return ind_2.begin();
}
iterator end() const {
return ind_2.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
}
};
struct t_btree_4__2_0_1_3__1_0_2_3__0_1_2_3__1__2__3__4__7__15 {
using t_tuple = Tuple<RamDomain, 4>;
struct updater_t_btree_4__2_0_1_3__1_0_2_3__0_1_2_3__1__2__3__4__7__15 {
bool update(t_tuple& old_t, const t_tuple& new_t) {
if (new_t[3] == 0) {
old_t[3] = 0;
return true;
}
old_t[3] += new_t[3];
return true;
}
};
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<2,0,1,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<2,0,1>, updater_t_btree_4__2_0_1_3__1_0_2_3__0_1_2_3__1__2__3__4__7__15>;
t_ind_0 ind_0;
using t_ind_1 = btree_set<t_tuple, index_utils::comparator<1,0,2,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<1,0,2>, updater_t_btree_4__2_0_1_3__1_0_2_3__0_1_2_3__1__2__3__4__7__15>;
t_ind_1 ind_1;
using t_ind_2 = btree_set<t_tuple, index_utils::comparator<0,1,2,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,1,2>, updater_t_btree_4__2_0_1_3__1_0_2_3__0_1_2_3__1__2__3__4__7__15>;
t_ind_2 ind_2;
using iterator = t_ind_2::iterator;
size_t approximate_size = 0;
size_t approximate_size_per_iteration[50000] = {0};
struct context {
t_ind_0::operation_hints hints_0;
t_ind_1::operation_hints hints_1;
t_ind_2::operation_hints hints_2;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_2.insert(t, h.hints_2)) {
ind_0.insert(t, h.hints_0);
ind_1.insert(t, h.hints_1);
approximate_size++;
approximate_size_per_iteration[t[2]]++;
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[4];
std::copy(ramDomain, ramDomain + 4, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3) {
RamDomain data[4] = {a0,a1,a2,a3};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
if (other.empty()) return;
context h;
for (auto const& cur : other) {
insert(cur, h);
}
}
void relationLoad(const t_btree_4__2_0_1_3__1_0_2_3__0_1_2_3__1__2__3__4__7__15& other) {
ind_0.clear();
ind_0 = other.ind_0;
ind_1.clear();
ind_1 = other.ind_1;
ind_2.clear();
ind_2 = other.ind_2;
approximate_size = other.approximate_size;
for (size_t i = 0; i < 50000; i++) approximate_size_per_iteration[i] = other.approximate_size_per_iteration[i];
}
bool contains(const t_tuple& t, context& h) const {
return ind_2.contains(t, h.hints_2);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_2.size();
}
size_t approx_size() const {
return approximate_size;
}
size_t approx_size(size_t iter) const {
return approximate_size_per_iteration[iter];
}
iterator find(const t_tuple& t, context& h) const {
return ind_2.find(t, h.hints_2);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_2.begin(),ind_2.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_2.begin(),ind_2.end());
}
range<t_ind_2::iterator> equalRange_1(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_2.lower_bound(low, h.hints_2), ind_2.upper_bound(high, h.hints_2));
}
range<t_ind_2::iterator> equalRange_1(const t_tuple& t) const {
context h;
return equalRange_1(t, h);
}
range<t_ind_1::iterator> equalRange_2(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_1.lower_bound(low, h.hints_1), ind_1.upper_bound(high, h.hints_1));
}
range<t_ind_1::iterator> equalRange_2(const t_tuple& t) const {
context h;
return equalRange_2(t, h);
}
range<t_ind_2::iterator> equalRange_3(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_2.lower_bound(low, h.hints_2), ind_2.upper_bound(high, h.hints_2));
}
range<t_ind_2::iterator> equalRange_3(const t_tuple& t) const {
context h;
return equalRange_3(t, h);
}
range<t_ind_0::iterator> equalRange_4(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_4(const t_tuple& t) const {
context h;
return equalRange_4(t, h);
}
range<t_ind_1::iterator> equalRange_7(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_1.lower_bound(low, h.hints_1), ind_1.upper_bound(high, h.hints_1));
}
range<t_ind_1::iterator> equalRange_7(const t_tuple& t) const {
context h;
return equalRange_7(t, h);
}
range<t_ind_2::iterator> equalRange_15(const t_tuple& t, context& h) const {
auto pos = ind_2.find(t, h.hints_2);
auto fin = ind_2.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_2::iterator> equalRange_15(const t_tuple& t) const {
context h;
return equalRange_15(t, h);
}
bool empty() const {
return ind_2.empty();
}
std::vector<range<iterator>> partition() const {
return ind_2.getChunks(400);
}
void purge() {
ind_0.clear();
ind_1.clear();
ind_2.clear();
approximate_size = 0;
for (size_t i = 0; i < 50000; i++) approximate_size_per_iteration[i] = 0;
}
iterator begin() const {
return ind_2.begin();
}
iterator end() const {
return ind_2.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
}
};
struct t_btree_4__1_2_0_3__0_1_2_3__2_0_1_3__3__4__5__6__7__15_diff_applied {
using t_tuple = Tuple<RamDomain, 4>;
struct updater_t_btree_4__1_2_0_3__0_1_2_3__2_0_1_3__3__4__5__6__7__15_diff_applied {
bool update(t_tuple& old_t, const t_tuple& new_t) {
if (new_t[3] == 0) {
old_t[3] = 0;
return true;
}
old_t[3] += new_t[3];
return true;
}
};
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<1,2,0,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<1,2,0>, updater_t_btree_4__1_2_0_3__0_1_2_3__2_0_1_3__3__4__5__6__7__15_diff_applied>;
t_ind_0 ind_0;
using t_ind_1 = btree_set<t_tuple, index_utils::comparator<0,1,2,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,1,2>, updater_t_btree_4__1_2_0_3__0_1_2_3__2_0_1_3__3__4__5__6__7__15_diff_applied>;
t_ind_1 ind_1;
using t_ind_2 = btree_set<t_tuple, index_utils::comparator<2,0,1,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<2,0,1>, updater_t_btree_4__1_2_0_3__0_1_2_3__2_0_1_3__3__4__5__6__7__15_diff_applied>;
t_ind_2 ind_2;
using iterator = t_ind_1::iterator;
size_t approximate_size = 0;
size_t approximate_size_per_iteration[50000] = {0};
struct context {
t_ind_0::operation_hints hints_0;
t_ind_1::operation_hints hints_1;
t_ind_2::operation_hints hints_2;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_1.insert(t, h.hints_1)) {
ind_0.insert(t, h.hints_0);
ind_2.insert(t, h.hints_2);
approximate_size++;
approximate_size_per_iteration[t[2]]++;
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[4];
std::copy(ramDomain, ramDomain + 4, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3) {
RamDomain data[4] = {a0,a1,a2,a3};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
if (other.empty()) return;
context h;
for (auto const& cur : other) {
insert(cur, h);
}
}
void relationLoad(const t_btree_4__1_2_0_3__0_1_2_3__2_0_1_3__3__4__5__6__7__15_diff_applied& other) {
ind_0.clear();
ind_0 = other.ind_0;
ind_1.clear();
ind_1 = other.ind_1;
ind_2.clear();
ind_2 = other.ind_2;
approximate_size = other.approximate_size;
for (size_t i = 0; i < 50000; i++) approximate_size_per_iteration[i] = other.approximate_size_per_iteration[i];
}
bool contains(const t_tuple& t, context& h) const {
return ind_1.contains(t, h.hints_1);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_1.size();
}
size_t approx_size() const {
return approximate_size;
}
size_t approx_size(size_t iter) const {
return approximate_size_per_iteration[iter];
}
iterator find(const t_tuple& t, context& h) const {
return ind_1.find(t, h.hints_1);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_1.begin(),ind_1.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_1.begin(),ind_1.end());
}
range<t_ind_1::iterator> equalRange_3(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_1.lower_bound(low, h.hints_1), ind_1.upper_bound(high, h.hints_1));
}
range<t_ind_1::iterator> equalRange_3(const t_tuple& t) const {
context h;
return equalRange_3(t, h);
}
range<t_ind_2::iterator> equalRange_4(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_2.lower_bound(low, h.hints_2), ind_2.upper_bound(high, h.hints_2));
}
range<t_ind_2::iterator> equalRange_4(const t_tuple& t) const {
context h;
return equalRange_4(t, h);
}
range<t_ind_2::iterator> equalRange_5(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_2.lower_bound(low, h.hints_2), ind_2.upper_bound(high, h.hints_2));
}
range<t_ind_2::iterator> equalRange_5(const t_tuple& t) const {
context h;
return equalRange_5(t, h);
}
range<t_ind_0::iterator> equalRange_6(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_6(const t_tuple& t) const {
context h;
return equalRange_6(t, h);
}
range<t_ind_1::iterator> equalRange_7(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_1.lower_bound(low, h.hints_1), ind_1.upper_bound(high, h.hints_1));
}
range<t_ind_1::iterator> equalRange_7(const t_tuple& t) const {
context h;
return equalRange_7(t, h);
}
range<t_ind_2::iterator> equalRange_15(const t_tuple& t, context& h) const {
auto pos = ind_2.find(t, h.hints_2);
auto fin = ind_2.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_2::iterator> equalRange_15(const t_tuple& t) const {
context h;
return equalRange_15(t, h);
}
bool empty() const {
return ind_1.empty();
}
std::vector<range<iterator>> partition() const {
return ind_1.getChunks(400);
}
void purge() {
ind_0.clear();
ind_1.clear();
ind_2.clear();
approximate_size = 0;
for (size_t i = 0; i < 50000; i++) approximate_size_per_iteration[i] = 0;
}
iterator begin() const {
return ind_1.begin();
}
iterator end() const {
return ind_1.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
}
};
struct t_btree_4__1_2_0_3__0_1_2_3__2_0_1_3__3__4__5__6__7__15 {
using t_tuple = Tuple<RamDomain, 4>;
struct updater_t_btree_4__1_2_0_3__0_1_2_3__2_0_1_3__3__4__5__6__7__15 {
bool update(t_tuple& old_t, const t_tuple& new_t) {
if (new_t[3] == 0) {
old_t[3] = 0;
return true;
}
old_t[3] += new_t[3];
return true;
}
};
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<1,2,0,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<1,2,0>, updater_t_btree_4__1_2_0_3__0_1_2_3__2_0_1_3__3__4__5__6__7__15>;
t_ind_0 ind_0;
using t_ind_1 = btree_set<t_tuple, index_utils::comparator<0,1,2,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,1,2>, updater_t_btree_4__1_2_0_3__0_1_2_3__2_0_1_3__3__4__5__6__7__15>;
t_ind_1 ind_1;
using t_ind_2 = btree_set<t_tuple, index_utils::comparator<2,0,1,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<2,0,1>, updater_t_btree_4__1_2_0_3__0_1_2_3__2_0_1_3__3__4__5__6__7__15>;
t_ind_2 ind_2;
using iterator = t_ind_1::iterator;
size_t approximate_size = 0;
size_t approximate_size_per_iteration[50000] = {0};
struct context {
t_ind_0::operation_hints hints_0;
t_ind_1::operation_hints hints_1;
t_ind_2::operation_hints hints_2;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_1.insert(t, h.hints_1)) {
ind_0.insert(t, h.hints_0);
ind_2.insert(t, h.hints_2);
approximate_size++;
approximate_size_per_iteration[t[2]]++;
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[4];
std::copy(ramDomain, ramDomain + 4, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3) {
RamDomain data[4] = {a0,a1,a2,a3};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
if (other.empty()) return;
context h;
for (auto const& cur : other) {
insert(cur, h);
}
}
void relationLoad(const t_btree_4__1_2_0_3__0_1_2_3__2_0_1_3__3__4__5__6__7__15& other) {
ind_0.clear();
ind_0 = other.ind_0;
ind_1.clear();
ind_1 = other.ind_1;
ind_2.clear();
ind_2 = other.ind_2;
approximate_size = other.approximate_size;
for (size_t i = 0; i < 50000; i++) approximate_size_per_iteration[i] = other.approximate_size_per_iteration[i];
}
bool contains(const t_tuple& t, context& h) const {
return ind_1.contains(t, h.hints_1);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_1.size();
}
size_t approx_size() const {
return approximate_size;
}
size_t approx_size(size_t iter) const {
return approximate_size_per_iteration[iter];
}
iterator find(const t_tuple& t, context& h) const {
return ind_1.find(t, h.hints_1);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_1.begin(),ind_1.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_1.begin(),ind_1.end());
}
range<t_ind_1::iterator> equalRange_3(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_1.lower_bound(low, h.hints_1), ind_1.upper_bound(high, h.hints_1));
}
range<t_ind_1::iterator> equalRange_3(const t_tuple& t) const {
context h;
return equalRange_3(t, h);
}
range<t_ind_2::iterator> equalRange_4(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_2.lower_bound(low, h.hints_2), ind_2.upper_bound(high, h.hints_2));
}
range<t_ind_2::iterator> equalRange_4(const t_tuple& t) const {
context h;
return equalRange_4(t, h);
}
range<t_ind_2::iterator> equalRange_5(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_2.lower_bound(low, h.hints_2), ind_2.upper_bound(high, h.hints_2));
}
range<t_ind_2::iterator> equalRange_5(const t_tuple& t) const {
context h;
return equalRange_5(t, h);
}
range<t_ind_0::iterator> equalRange_6(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_6(const t_tuple& t) const {
context h;
return equalRange_6(t, h);
}
range<t_ind_1::iterator> equalRange_7(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_1.lower_bound(low, h.hints_1), ind_1.upper_bound(high, h.hints_1));
}
range<t_ind_1::iterator> equalRange_7(const t_tuple& t) const {
context h;
return equalRange_7(t, h);
}
range<t_ind_2::iterator> equalRange_15(const t_tuple& t, context& h) const {
auto pos = ind_2.find(t, h.hints_2);
auto fin = ind_2.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_2::iterator> equalRange_15(const t_tuple& t) const {
context h;
return equalRange_15(t, h);
}
bool empty() const {
return ind_1.empty();
}
std::vector<range<iterator>> partition() const {
return ind_1.getChunks(400);
}
void purge() {
ind_0.clear();
ind_1.clear();
ind_2.clear();
approximate_size = 0;
for (size_t i = 0; i < 50000; i++) approximate_size_per_iteration[i] = 0;
}
iterator begin() const {
return ind_1.begin();
}
iterator end() const {
return ind_1.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
}
};
struct t_btree_4__0_1_2_3__1__15_temp_diff_applied {
using t_tuple = Tuple<RamDomain, 4>;
struct updater_t_btree_4__0_1_2_3__1__15_temp_diff_applied {
bool update(t_tuple& old_t, const t_tuple& new_t) {
if (new_t[3] == 0) {
old_t[3] = 0;
return true;
}
old_t[3] += new_t[3];
return true;
}
};
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,1,2>, updater_t_btree_4__0_1_2_3__1__15_temp_diff_applied>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
size_t approximate_size = 0;
size_t approximate_size_per_iteration[50000] = {0};
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
approximate_size++;
approximate_size_per_iteration[t[2]]++;
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[4];
std::copy(ramDomain, ramDomain + 4, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3) {
RamDomain data[4] = {a0,a1,a2,a3};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
if (other.empty()) return;
context h;
for (auto const& cur : other) {
insert(cur, h);
}
}
void relationLoad(const t_btree_4__0_1_2_3__1__15_temp_diff_applied& other) {
ind_0.clear();
ind_0 = other.ind_0;
approximate_size = other.approximate_size;
for (size_t i = 0; i < 50000; i++) approximate_size_per_iteration[i] = other.approximate_size_per_iteration[i];
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
size_t approx_size() const {
return approximate_size;
}
size_t approx_size(size_t iter) const {
return approximate_size_per_iteration[iter];
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_1(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_1(const t_tuple& t) const {
context h;
return equalRange_1(t, h);
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t) const {
context h;
return equalRange_15(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
approximate_size = 0;
for (size_t i = 0; i < 50000; i++) approximate_size_per_iteration[i] = 0;
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
}
};
struct t_btree_4__0_1_2_3__15_temp_diff {
using t_tuple = Tuple<RamDomain, 4>;
struct updater_t_btree_4__0_1_2_3__15_temp_diff {
bool update(t_tuple& old_t, const t_tuple& new_t) {
old_t[3] += new_t[3];
return true;
}
};
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,1,2>, updater_t_btree_4__0_1_2_3__15_temp_diff>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
size_t approximate_size = 0;
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
approximate_size++;
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[4];
std::copy(ramDomain, ramDomain + 4, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3) {
RamDomain data[4] = {a0,a1,a2,a3};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
if (other.empty()) return;
context h;
for (auto const& cur : other) {
insert(cur, h);
}
}
void relationLoad(const t_btree_4__0_1_2_3__15_temp_diff& other) {
ind_0.clear();
ind_0 = other.ind_0;
approximate_size = other.approximate_size;
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
size_t approx_size() const {
return approximate_size;
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t) const {
context h;
return equalRange_15(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
approximate_size = 0;
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
}
};
struct t_btree_4__0_1_2_3__15_temp {
using t_tuple = Tuple<RamDomain, 4>;
struct updater_t_btree_4__0_1_2_3__15_temp {
bool update(t_tuple& old_t, const t_tuple& new_t) {
old_t[3] += new_t[3];
return true;
}
};
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,1,2>, updater_t_btree_4__0_1_2_3__15_temp>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
size_t approximate_size = 0;
size_t approximate_size_per_iteration[50000] = {0};
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
approximate_size++;
approximate_size_per_iteration[t[2]]++;
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[4];
std::copy(ramDomain, ramDomain + 4, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3) {
RamDomain data[4] = {a0,a1,a2,a3};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
if (other.empty()) return;
context h;
for (auto const& cur : other) {
insert(cur, h);
}
}
void relationLoad(const t_btree_4__0_1_2_3__15_temp& other) {
ind_0.clear();
ind_0 = other.ind_0;
approximate_size = other.approximate_size;
for (size_t i = 0; i < 50000; i++) approximate_size_per_iteration[i] = other.approximate_size_per_iteration[i];
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
size_t approx_size() const {
return approximate_size;
}
size_t approx_size(size_t iter) const {
return approximate_size_per_iteration[iter];
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t) const {
context h;
return equalRange_15(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
approximate_size = 0;
for (size_t i = 0; i < 50000; i++) approximate_size_per_iteration[i] = 0;
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
}
};
struct t_btree_1__0 {
using t_tuple = Tuple<RamDomain, 1>;
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0>>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
size_t approximate_size = 0;
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
approximate_size++;
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[1];
std::copy(ramDomain, ramDomain + 1, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0) {
RamDomain data[1] = {a0};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
if (other.empty()) return;
context h;
for (auto const& cur : other) {
insert(cur, h);
}
}
void relationLoad(const t_btree_1__0& other) {
ind_0.clear();
ind_0 = other.ind_0;
approximate_size = other.approximate_size;
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
size_t approx_size() const {
return approximate_size;
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
approximate_size = 0;
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
}
};
struct t_btree_4__2_0_1_3__4__15_diff {
using t_tuple = Tuple<RamDomain, 4>;
struct updater_t_btree_4__2_0_1_3__4__15_diff {
bool update(t_tuple& old_t, const t_tuple& new_t) {
old_t[3] += new_t[3];
return true;
}
};
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<2,0,1,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<2,0,1>, updater_t_btree_4__2_0_1_3__4__15_diff>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
size_t approximate_size = 0;
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
approximate_size++;
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[4];
std::copy(ramDomain, ramDomain + 4, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3) {
RamDomain data[4] = {a0,a1,a2,a3};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
if (other.empty()) return;
context h;
for (auto const& cur : other) {
insert(cur, h);
}
}
void relationLoad(const t_btree_4__2_0_1_3__4__15_diff& other) {
ind_0.clear();
ind_0 = other.ind_0;
approximate_size = other.approximate_size;
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
size_t approx_size() const {
return approximate_size;
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_4(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_4(const t_tuple& t) const {
context h;
return equalRange_4(t, h);
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t) const {
context h;
return equalRange_15(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
approximate_size = 0;
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
}
};
struct t_btree_4__0_1_2_3__2_0_1_3__3__4__7__15_diff_applied {
using t_tuple = Tuple<RamDomain, 4>;
struct updater_t_btree_4__0_1_2_3__2_0_1_3__3__4__7__15_diff_applied {
bool update(t_tuple& old_t, const t_tuple& new_t) {
if (new_t[3] == 0) {
old_t[3] = 0;
return true;
}
old_t[3] += new_t[3];
return true;
}
};
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,1,2>, updater_t_btree_4__0_1_2_3__2_0_1_3__3__4__7__15_diff_applied>;
t_ind_0 ind_0;
using t_ind_1 = btree_set<t_tuple, index_utils::comparator<2,0,1,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<2,0,1>, updater_t_btree_4__0_1_2_3__2_0_1_3__3__4__7__15_diff_applied>;
t_ind_1 ind_1;
using iterator = t_ind_0::iterator;
size_t approximate_size = 0;
size_t approximate_size_per_iteration[50000] = {0};
struct context {
t_ind_0::operation_hints hints_0;
t_ind_1::operation_hints hints_1;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
ind_1.insert(t, h.hints_1);
approximate_size++;
approximate_size_per_iteration[t[2]]++;
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[4];
std::copy(ramDomain, ramDomain + 4, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3) {
RamDomain data[4] = {a0,a1,a2,a3};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
if (other.empty()) return;
context h;
for (auto const& cur : other) {
insert(cur, h);
}
}
void relationLoad(const t_btree_4__0_1_2_3__2_0_1_3__3__4__7__15_diff_applied& other) {
ind_0.clear();
ind_0 = other.ind_0;
ind_1.clear();
ind_1 = other.ind_1;
approximate_size = other.approximate_size;
for (size_t i = 0; i < 50000; i++) approximate_size_per_iteration[i] = other.approximate_size_per_iteration[i];
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
size_t approx_size() const {
return approximate_size;
}
size_t approx_size(size_t iter) const {
return approximate_size_per_iteration[iter];
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_3(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_3(const t_tuple& t) const {
context h;
return equalRange_3(t, h);
}
range<t_ind_1::iterator> equalRange_4(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_1.lower_bound(low, h.hints_1), ind_1.upper_bound(high, h.hints_1));
}
range<t_ind_1::iterator> equalRange_4(const t_tuple& t) const {
context h;
return equalRange_4(t, h);
}
range<t_ind_0::iterator> equalRange_7(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_7(const t_tuple& t) const {
context h;
return equalRange_7(t, h);
}
range<t_ind_1::iterator> equalRange_15(const t_tuple& t, context& h) const {
auto pos = ind_1.find(t, h.hints_1);
auto fin = ind_1.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_1::iterator> equalRange_15(const t_tuple& t) const {
context h;
return equalRange_15(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
ind_1.clear();
approximate_size = 0;
for (size_t i = 0; i < 50000; i++) approximate_size_per_iteration[i] = 0;
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
}
};
struct t_btree_4__0_1_2_3__2_0_1_3__3__4__7__15 {
using t_tuple = Tuple<RamDomain, 4>;
struct updater_t_btree_4__0_1_2_3__2_0_1_3__3__4__7__15 {
bool update(t_tuple& old_t, const t_tuple& new_t) {
if (new_t[3] == 0) {
old_t[3] = 0;
return true;
}
old_t[3] += new_t[3];
return true;
}
};
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,1,2>, updater_t_btree_4__0_1_2_3__2_0_1_3__3__4__7__15>;
t_ind_0 ind_0;
using t_ind_1 = btree_set<t_tuple, index_utils::comparator<2,0,1,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<2,0,1>, updater_t_btree_4__0_1_2_3__2_0_1_3__3__4__7__15>;
t_ind_1 ind_1;
using iterator = t_ind_0::iterator;
size_t approximate_size = 0;
size_t approximate_size_per_iteration[50000] = {0};
struct context {
t_ind_0::operation_hints hints_0;
t_ind_1::operation_hints hints_1;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
ind_1.insert(t, h.hints_1);
approximate_size++;
approximate_size_per_iteration[t[2]]++;
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[4];
std::copy(ramDomain, ramDomain + 4, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3) {
RamDomain data[4] = {a0,a1,a2,a3};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
if (other.empty()) return;
context h;
for (auto const& cur : other) {
insert(cur, h);
}
}
void relationLoad(const t_btree_4__0_1_2_3__2_0_1_3__3__4__7__15& other) {
ind_0.clear();
ind_0 = other.ind_0;
ind_1.clear();
ind_1 = other.ind_1;
approximate_size = other.approximate_size;
for (size_t i = 0; i < 50000; i++) approximate_size_per_iteration[i] = other.approximate_size_per_iteration[i];
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
size_t approx_size() const {
return approximate_size;
}
size_t approx_size(size_t iter) const {
return approximate_size_per_iteration[iter];
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_3(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_3(const t_tuple& t) const {
context h;
return equalRange_3(t, h);
}
range<t_ind_1::iterator> equalRange_4(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_1.lower_bound(low, h.hints_1), ind_1.upper_bound(high, h.hints_1));
}
range<t_ind_1::iterator> equalRange_4(const t_tuple& t) const {
context h;
return equalRange_4(t, h);
}
range<t_ind_0::iterator> equalRange_7(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_7(const t_tuple& t) const {
context h;
return equalRange_7(t, h);
}
range<t_ind_1::iterator> equalRange_15(const t_tuple& t, context& h) const {
auto pos = ind_1.find(t, h.hints_1);
auto fin = ind_1.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_1::iterator> equalRange_15(const t_tuple& t) const {
context h;
return equalRange_15(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
ind_1.clear();
approximate_size = 0;
for (size_t i = 0; i < 50000; i++) approximate_size_per_iteration[i] = 0;
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
}
};
struct t_btree_4__0_1_2_3__15_diff {
using t_tuple = Tuple<RamDomain, 4>;
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2,3>>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
size_t approximate_size = 0;
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
approximate_size++;
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[4];
std::copy(ramDomain, ramDomain + 4, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3) {
RamDomain data[4] = {a0,a1,a2,a3};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
if (other.empty()) return;
context h;
for (auto const& cur : other) {
insert(cur, h);
}
}
void relationLoad(const t_btree_4__0_1_2_3__15_diff& other) {
ind_0.clear();
ind_0 = other.ind_0;
approximate_size = other.approximate_size;
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
size_t approx_size() const {
return approximate_size;
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t) const {
context h;
return equalRange_15(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
approximate_size = 0;
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
}
};
struct t_btree_4__0_1_2_3__15_diff_applied {
using t_tuple = Tuple<RamDomain, 4>;
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2,3>>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
size_t approximate_size = 0;
size_t approximate_size_per_iteration[50000] = {0};
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
approximate_size++;
approximate_size_per_iteration[t[2]]++;
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[4];
std::copy(ramDomain, ramDomain + 4, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3) {
RamDomain data[4] = {a0,a1,a2,a3};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
if (other.empty()) return;
context h;
for (auto const& cur : other) {
insert(cur, h);
}
}
void relationLoad(const t_btree_4__0_1_2_3__15_diff_applied& other) {
ind_0.clear();
ind_0 = other.ind_0;
approximate_size = other.approximate_size;
for (size_t i = 0; i < 50000; i++) approximate_size_per_iteration[i] = other.approximate_size_per_iteration[i];
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
size_t approx_size() const {
return approximate_size;
}
size_t approx_size(size_t iter) const {
return approximate_size_per_iteration[iter];
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t) const {
context h;
return equalRange_15(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
approximate_size = 0;
for (size_t i = 0; i < 50000; i++) approximate_size_per_iteration[i] = 0;
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
}
};
struct t_btree_4__0_1_2_3__15 {
using t_tuple = Tuple<RamDomain, 4>;
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2,3>>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
size_t approximate_size = 0;
size_t approximate_size_per_iteration[50000] = {0};
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
approximate_size++;
approximate_size_per_iteration[t[2]]++;
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[4];
std::copy(ramDomain, ramDomain + 4, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3) {
RamDomain data[4] = {a0,a1,a2,a3};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
if (other.empty()) return;
context h;
for (auto const& cur : other) {
insert(cur, h);
}
}
void relationLoad(const t_btree_4__0_1_2_3__15& other) {
ind_0.clear();
ind_0 = other.ind_0;
approximate_size = other.approximate_size;
for (size_t i = 0; i < 50000; i++) approximate_size_per_iteration[i] = other.approximate_size_per_iteration[i];
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
size_t approx_size() const {
return approximate_size;
}
size_t approx_size(size_t iter) const {
return approximate_size_per_iteration[iter];
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t) const {
context h;
return equalRange_15(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
approximate_size = 0;
for (size_t i = 0; i < 50000; i++) approximate_size_per_iteration[i] = 0;
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
}
};
struct t_btree_5__0_1_2_3_4__31_diff {
using t_tuple = Tuple<RamDomain, 5>;
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2,3,4>>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
size_t approximate_size = 0;
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
approximate_size++;
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[5];
std::copy(ramDomain, ramDomain + 5, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3,RamDomain a4) {
RamDomain data[5] = {a0,a1,a2,a3,a4};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
if (other.empty()) return;
context h;
for (auto const& cur : other) {
insert(cur, h);
}
}
void relationLoad(const t_btree_5__0_1_2_3_4__31_diff& other) {
ind_0.clear();
ind_0 = other.ind_0;
approximate_size = other.approximate_size;
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
size_t approx_size() const {
return approximate_size;
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_31(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_31(const t_tuple& t) const {
context h;
return equalRange_31(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
approximate_size = 0;
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
}
};
struct t_btree_5__0_1_2_3_4__31_diff_applied {
using t_tuple = Tuple<RamDomain, 5>;
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2,3,4>>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
size_t approximate_size = 0;
size_t approximate_size_per_iteration[50000] = {0};
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
approximate_size++;
approximate_size_per_iteration[t[3]]++;
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[5];
std::copy(ramDomain, ramDomain + 5, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3,RamDomain a4) {
RamDomain data[5] = {a0,a1,a2,a3,a4};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
if (other.empty()) return;
context h;
for (auto const& cur : other) {
insert(cur, h);
}
}
void relationLoad(const t_btree_5__0_1_2_3_4__31_diff_applied& other) {
ind_0.clear();
ind_0 = other.ind_0;
approximate_size = other.approximate_size;
for (size_t i = 0; i < 50000; i++) approximate_size_per_iteration[i] = other.approximate_size_per_iteration[i];
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
size_t approx_size() const {
return approximate_size;
}
size_t approx_size(size_t iter) const {
return approximate_size_per_iteration[iter];
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_31(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_31(const t_tuple& t) const {
context h;
return equalRange_31(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
approximate_size = 0;
for (size_t i = 0; i < 50000; i++) approximate_size_per_iteration[i] = 0;
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
}
};
struct t_btree_5__0_1_2_3_4__31 {
using t_tuple = Tuple<RamDomain, 5>;
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2,3,4>>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
size_t approximate_size = 0;
size_t approximate_size_per_iteration[50000] = {0};
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
approximate_size++;
approximate_size_per_iteration[t[3]]++;
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[5];
std::copy(ramDomain, ramDomain + 5, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3,RamDomain a4) {
RamDomain data[5] = {a0,a1,a2,a3,a4};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
if (other.empty()) return;
context h;
for (auto const& cur : other) {
insert(cur, h);
}
}
void relationLoad(const t_btree_5__0_1_2_3_4__31& other) {
ind_0.clear();
ind_0 = other.ind_0;
approximate_size = other.approximate_size;
for (size_t i = 0; i < 50000; i++) approximate_size_per_iteration[i] = other.approximate_size_per_iteration[i];
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
size_t approx_size() const {
return approximate_size;
}
size_t approx_size(size_t iter) const {
return approximate_size_per_iteration[iter];
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_31(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_31(const t_tuple& t) const {
context h;
return equalRange_31(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
approximate_size = 0;
for (size_t i = 0; i < 50000; i++) approximate_size_per_iteration[i] = 0;
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
}
};
struct t_btree_1__0__1 {
using t_tuple = Tuple<RamDomain, 1>;
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0>>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
size_t approximate_size = 0;
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
approximate_size++;
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[1];
std::copy(ramDomain, ramDomain + 1, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0) {
RamDomain data[1] = {a0};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
if (other.empty()) return;
context h;
for (auto const& cur : other) {
insert(cur, h);
}
}
void relationLoad(const t_btree_1__0__1& other) {
ind_0.clear();
ind_0 = other.ind_0;
approximate_size = other.approximate_size;
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
size_t approx_size() const {
return approximate_size;
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_1(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_1(const t_tuple& t) const {
context h;
return equalRange_1(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
approximate_size = 0;
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
}
};

class Sf_query : public SouffleProgram {
private:
static inline bool regex_wrapper(const std::string& pattern, const std::string& text) {
   bool result = false; 
   try { result = std::regex_match(text, std::regex(pattern)); } catch(...) { 
     std::cerr << "warning: wrong pattern provided for match(\"" << pattern << "\",\"" << text << "\").\n";
}
   return result;
}
private:
static inline std::string substr_wrapper(const std::string& str, size_t idx, size_t len) {
   std::string result; 
   try { result = str.substr(idx,len); } catch(...) { 
     std::cerr << "warning: wrong index position provided by substr(\"";
     std::cerr << str << "\"," << (int32_t)idx << "," << (int32_t)len << ") functor.\n";
   } return result;
}
private:
static inline RamDomain wrapper_tonumber(const std::string& str) {
   RamDomain result=0; 
   try { result = stord(str); } catch(...) { 
     std::cerr << "error: wrong string provided by to_number(\"";
     std::cerr << str << "\") functor.\n";
     raise(SIGFPE);
   } return result;
}
public:
// -- initialize symbol table --
SymbolTable symTable
{
	R"_(x,y)_",
	R"_(edge,x,y)_",
	R"_(path(x,y) :- 
   edge(x,y).)_",
	R"_(edge,x,z)_",
	R"_(path,z,y)_",
	R"_(path(x,y) :- 
   edge(x,z),
   path(z,y).)_",
	R"_(path,x,y)_",
	R"_(!edge)_",
	R"_(path2(x,y) :- 
   path(x,y),
   !edge(x,y).)_",
};// -- Table: diff_minus@_edge
std::unique_ptr<t_btree_4__2_0_1_3__0_1_2_3__3__4__15_diff> rel_1_diff_minus_edge = std::make_unique<t_btree_4__2_0_1_3__0_1_2_3__3__4__15_diff>();
souffle::RelationWrapper<0,t_btree_4__2_0_1_3__0_1_2_3__3__4__15_diff,Tuple<RamDomain,4>,4,1> wrapper_rel_1_diff_minus_edge;
// -- Table: diff_plus@_edge
std::unique_ptr<t_btree_4__2_0_1_3__0_1_2_3__3__4__15_diff> rel_2_diff_plus_edge = std::make_unique<t_btree_4__2_0_1_3__0_1_2_3__3__4__15_diff>();
souffle::RelationWrapper<1,t_btree_4__2_0_1_3__0_1_2_3__3__4__15_diff,Tuple<RamDomain,4>,4,1> wrapper_rel_2_diff_plus_edge;
// -- Table: actual_diff_plus@_edge
std::unique_ptr<t_btree_4__0_1_2_3__3__15_diff> rel_3_actual_diff_plus_edge = std::make_unique<t_btree_4__0_1_2_3__3__15_diff>();
souffle::RelationWrapper<2,t_btree_4__0_1_2_3__3__15_diff,Tuple<RamDomain,4>,4,1> wrapper_rel_3_actual_diff_plus_edge;
// -- Table: actual_diff_minus@_edge
std::unique_ptr<t_btree_4__0_1_2_3__3__15_diff> rel_4_actual_diff_minus_edge = std::make_unique<t_btree_4__0_1_2_3__3__15_diff>();
souffle::RelationWrapper<3,t_btree_4__0_1_2_3__3__15_diff,Tuple<RamDomain,4>,4,1> wrapper_rel_4_actual_diff_minus_edge;
// -- Table: diff_applied@_edge
std::unique_ptr<t_btree_4__2_0_1_3__1_0_2_3__0_1_2_3__1__2__3__4__7__15_diff_applied> rel_5_diff_applied_edge = std::make_unique<t_btree_4__2_0_1_3__1_0_2_3__0_1_2_3__1__2__3__4__7__15_diff_applied>();
souffle::RelationWrapper<4,t_btree_4__2_0_1_3__1_0_2_3__0_1_2_3__1__2__3__4__7__15_diff_applied,Tuple<RamDomain,4>,4,1> wrapper_rel_5_diff_applied_edge;
// -- Table: edge
std::unique_ptr<t_btree_4__2_0_1_3__1_0_2_3__0_1_2_3__1__2__3__4__7__15_diff_applied> rel_6_edge = std::make_unique<t_btree_4__2_0_1_3__1_0_2_3__0_1_2_3__1__2__3__4__7__15_diff_applied>();
souffle::RelationWrapper<5,t_btree_4__2_0_1_3__1_0_2_3__0_1_2_3__1__2__3__4__7__15_diff_applied,Tuple<RamDomain,4>,4,1> wrapper_rel_6_edge;
// -- Table: diff_minus@_path
std::unique_ptr<t_btree_4__2_0_1_3__0_1_2_3__3__4__15_diff> rel_7_diff_minus_path = std::make_unique<t_btree_4__2_0_1_3__0_1_2_3__3__4__15_diff>();
souffle::RelationWrapper<6,t_btree_4__2_0_1_3__0_1_2_3__3__4__15_diff,Tuple<RamDomain,4>,4,1> wrapper_rel_7_diff_minus_path;
// -- Table: diff_plus@_path
std::unique_ptr<t_btree_4__2_0_1_3__0_1_2_3__3__4__15_diff> rel_8_diff_plus_path = std::make_unique<t_btree_4__2_0_1_3__0_1_2_3__3__4__15_diff>();
souffle::RelationWrapper<7,t_btree_4__2_0_1_3__0_1_2_3__3__4__15_diff,Tuple<RamDomain,4>,4,1> wrapper_rel_8_diff_plus_path;
// -- Table: actual_diff_plus@_path
std::unique_ptr<t_btree_4__2_0_1_3__0_1_2_3__3__4__15_diff> rel_9_actual_diff_plus_path = std::make_unique<t_btree_4__2_0_1_3__0_1_2_3__3__4__15_diff>();
souffle::RelationWrapper<8,t_btree_4__2_0_1_3__0_1_2_3__3__4__15_diff,Tuple<RamDomain,4>,4,1> wrapper_rel_9_actual_diff_plus_path;
// -- Table: actual_diff_minus@_path
std::unique_ptr<t_btree_4__2_0_1_3__0_1_2_3__3__4__15_diff> rel_10_actual_diff_minus_path = std::make_unique<t_btree_4__2_0_1_3__0_1_2_3__3__4__15_diff>();
souffle::RelationWrapper<9,t_btree_4__2_0_1_3__0_1_2_3__3__4__15_diff,Tuple<RamDomain,4>,4,1> wrapper_rel_10_actual_diff_minus_path;
// -- Table: diff_applied@_path
std::unique_ptr<t_btree_4__1_2_0_3__0_1_2_3__2_0_1_3__3__4__5__6__7__15_diff_applied> rel_11_diff_applied_path = std::make_unique<t_btree_4__1_2_0_3__0_1_2_3__2_0_1_3__3__4__5__6__7__15_diff_applied>();
souffle::RelationWrapper<10,t_btree_4__1_2_0_3__0_1_2_3__2_0_1_3__3__4__5__6__7__15_diff_applied,Tuple<RamDomain,4>,4,1> wrapper_rel_11_diff_applied_path;
// -- Table: path
std::unique_ptr<t_btree_4__1_2_0_3__0_1_2_3__2_0_1_3__3__4__5__6__7__15_diff_applied> rel_12_path = std::make_unique<t_btree_4__1_2_0_3__0_1_2_3__2_0_1_3__3__4__5__6__7__15_diff_applied>();
souffle::RelationWrapper<11,t_btree_4__1_2_0_3__0_1_2_3__2_0_1_3__3__4__5__6__7__15_diff_applied,Tuple<RamDomain,4>,4,1> wrapper_rel_12_path;
// -- Table: @new_diff_applied@_path
std::unique_ptr<t_btree_4__0_1_2_3__1__15_temp_diff_applied> rel_13_new_diff_applied_path = std::make_unique<t_btree_4__0_1_2_3__1__15_temp_diff_applied>();
// -- Table: @delta_diff_applied@_path
std::unique_ptr<t_btree_4__0_1_2_3__1__15_temp_diff_applied> rel_14_delta_diff_applied_path = std::make_unique<t_btree_4__0_1_2_3__1__15_temp_diff_applied>();
// -- Table: @new_diff_plus@_path
std::unique_ptr<t_btree_4__0_1_2_3__15_temp_diff> rel_15_new_diff_plus_path = std::make_unique<t_btree_4__0_1_2_3__15_temp_diff>();
// -- Table: @new_diff_minus@_path
std::unique_ptr<t_btree_4__0_1_2_3__15_temp_diff> rel_16_new_diff_minus_path = std::make_unique<t_btree_4__0_1_2_3__15_temp_diff>();
// -- Table: @delta_path
std::unique_ptr<t_btree_4__0_1_2_3__1__15_temp_diff_applied> rel_17_delta_path = std::make_unique<t_btree_4__0_1_2_3__1__15_temp_diff_applied>();
// -- Table: @new_path
std::unique_ptr<t_btree_4__0_1_2_3__1__15_temp_diff_applied> rel_18_new_path = std::make_unique<t_btree_4__0_1_2_3__1__15_temp_diff_applied>();
// -- Table: scc_1_@max_iter
std::unique_ptr<t_btree_1__0> rel_19_scc_1_max_iter = std::make_unique<t_btree_1__0>();
souffle::RelationWrapper<12,t_btree_1__0,Tuple<RamDomain,1>,1,1> wrapper_rel_19_scc_1_max_iter;
// -- Table: diff_minus@_path2
std::unique_ptr<t_btree_4__2_0_1_3__4__15_diff> rel_20_diff_minus_path2 = std::make_unique<t_btree_4__2_0_1_3__4__15_diff>();
souffle::RelationWrapper<13,t_btree_4__2_0_1_3__4__15_diff,Tuple<RamDomain,4>,4,1> wrapper_rel_20_diff_minus_path2;
// -- Table: diff_plus@_path2
std::unique_ptr<t_btree_4__2_0_1_3__4__15_diff> rel_21_diff_plus_path2 = std::make_unique<t_btree_4__2_0_1_3__4__15_diff>();
souffle::RelationWrapper<14,t_btree_4__2_0_1_3__4__15_diff,Tuple<RamDomain,4>,4,1> wrapper_rel_21_diff_plus_path2;
// -- Table: actual_diff_plus@_path2
std::unique_ptr<t_btree_4__0_1_2_3__3__15_diff> rel_22_actual_diff_plus_path2 = std::make_unique<t_btree_4__0_1_2_3__3__15_diff>();
souffle::RelationWrapper<15,t_btree_4__0_1_2_3__3__15_diff,Tuple<RamDomain,4>,4,1> wrapper_rel_22_actual_diff_plus_path2;
// -- Table: actual_diff_minus@_path2
std::unique_ptr<t_btree_4__0_1_2_3__3__15_diff> rel_23_actual_diff_minus_path2 = std::make_unique<t_btree_4__0_1_2_3__3__15_diff>();
souffle::RelationWrapper<16,t_btree_4__0_1_2_3__3__15_diff,Tuple<RamDomain,4>,4,1> wrapper_rel_23_actual_diff_minus_path2;
// -- Table: diff_applied@_path2
std::unique_ptr<t_btree_4__0_1_2_3__2_0_1_3__3__4__7__15_diff_applied> rel_24_diff_applied_path2 = std::make_unique<t_btree_4__0_1_2_3__2_0_1_3__3__4__7__15_diff_applied>();
souffle::RelationWrapper<17,t_btree_4__0_1_2_3__2_0_1_3__3__4__7__15_diff_applied,Tuple<RamDomain,4>,4,1> wrapper_rel_24_diff_applied_path2;
// -- Table: path2
std::unique_ptr<t_btree_4__0_1_2_3__2_0_1_3__3__4__7__15_diff_applied> rel_25_path2 = std::make_unique<t_btree_4__0_1_2_3__2_0_1_3__3__4__7__15_diff_applied>();
souffle::RelationWrapper<18,t_btree_4__0_1_2_3__2_0_1_3__3__4__7__15_diff_applied,Tuple<RamDomain,4>,4,1> wrapper_rel_25_path2;
// -- Table: diff_minus@_path.@info.1
std::unique_ptr<t_btree_4__0_1_2_3__15_diff> rel_26_diff_minus_path_info_1 = std::make_unique<t_btree_4__0_1_2_3__15_diff>();
souffle::RelationWrapper<19,t_btree_4__0_1_2_3__15_diff,Tuple<RamDomain,4>,4,1> wrapper_rel_26_diff_minus_path_info_1;
// -- Table: diff_plus@_path.@info.1
std::unique_ptr<t_btree_4__0_1_2_3__15_diff> rel_27_diff_plus_path_info_1 = std::make_unique<t_btree_4__0_1_2_3__15_diff>();
souffle::RelationWrapper<20,t_btree_4__0_1_2_3__15_diff,Tuple<RamDomain,4>,4,1> wrapper_rel_27_diff_plus_path_info_1;
// -- Table: actual_diff_plus@_path.@info.1
std::unique_ptr<t_btree_4__0_1_2_3__15_diff> rel_28_actual_diff_plus_path_info_1 = std::make_unique<t_btree_4__0_1_2_3__15_diff>();
souffle::RelationWrapper<21,t_btree_4__0_1_2_3__15_diff,Tuple<RamDomain,4>,4,1> wrapper_rel_28_actual_diff_plus_path_info_1;
// -- Table: actual_diff_minus@_path.@info.1
std::unique_ptr<t_btree_4__0_1_2_3__15_diff> rel_29_actual_diff_minus_path_info_1 = std::make_unique<t_btree_4__0_1_2_3__15_diff>();
souffle::RelationWrapper<22,t_btree_4__0_1_2_3__15_diff,Tuple<RamDomain,4>,4,1> wrapper_rel_29_actual_diff_minus_path_info_1;
// -- Table: diff_applied@_path.@info.1
std::unique_ptr<t_btree_4__0_1_2_3__15_diff_applied> rel_30_diff_applied_path_info_1 = std::make_unique<t_btree_4__0_1_2_3__15_diff_applied>();
souffle::RelationWrapper<23,t_btree_4__0_1_2_3__15_diff_applied,Tuple<RamDomain,4>,4,1> wrapper_rel_30_diff_applied_path_info_1;
// -- Table: path.@info.1
std::unique_ptr<t_btree_4__0_1_2_3__15> rel_31_path_info_1 = std::make_unique<t_btree_4__0_1_2_3__15>();
souffle::RelationWrapper<24,t_btree_4__0_1_2_3__15,Tuple<RamDomain,4>,4,1> wrapper_rel_31_path_info_1;
// -- Table: diff_minus@_path.@info.2
std::unique_ptr<t_btree_5__0_1_2_3_4__31_diff> rel_32_diff_minus_path_info_2 = std::make_unique<t_btree_5__0_1_2_3_4__31_diff>();
souffle::RelationWrapper<25,t_btree_5__0_1_2_3_4__31_diff,Tuple<RamDomain,5>,5,1> wrapper_rel_32_diff_minus_path_info_2;
// -- Table: diff_plus@_path.@info.2
std::unique_ptr<t_btree_5__0_1_2_3_4__31_diff> rel_33_diff_plus_path_info_2 = std::make_unique<t_btree_5__0_1_2_3_4__31_diff>();
souffle::RelationWrapper<26,t_btree_5__0_1_2_3_4__31_diff,Tuple<RamDomain,5>,5,1> wrapper_rel_33_diff_plus_path_info_2;
// -- Table: actual_diff_plus@_path.@info.2
std::unique_ptr<t_btree_5__0_1_2_3_4__31_diff> rel_34_actual_diff_plus_path_info_2 = std::make_unique<t_btree_5__0_1_2_3_4__31_diff>();
souffle::RelationWrapper<27,t_btree_5__0_1_2_3_4__31_diff,Tuple<RamDomain,5>,5,1> wrapper_rel_34_actual_diff_plus_path_info_2;
// -- Table: actual_diff_minus@_path.@info.2
std::unique_ptr<t_btree_5__0_1_2_3_4__31_diff> rel_35_actual_diff_minus_path_info_2 = std::make_unique<t_btree_5__0_1_2_3_4__31_diff>();
souffle::RelationWrapper<28,t_btree_5__0_1_2_3_4__31_diff,Tuple<RamDomain,5>,5,1> wrapper_rel_35_actual_diff_minus_path_info_2;
// -- Table: diff_applied@_path.@info.2
std::unique_ptr<t_btree_5__0_1_2_3_4__31_diff_applied> rel_36_diff_applied_path_info_2 = std::make_unique<t_btree_5__0_1_2_3_4__31_diff_applied>();
souffle::RelationWrapper<29,t_btree_5__0_1_2_3_4__31_diff_applied,Tuple<RamDomain,5>,5,1> wrapper_rel_36_diff_applied_path_info_2;
// -- Table: path.@info.2
std::unique_ptr<t_btree_5__0_1_2_3_4__31> rel_37_path_info_2 = std::make_unique<t_btree_5__0_1_2_3_4__31>();
souffle::RelationWrapper<30,t_btree_5__0_1_2_3_4__31,Tuple<RamDomain,5>,5,1> wrapper_rel_37_path_info_2;
// -- Table: diff_minus@_path2.@info.1
std::unique_ptr<t_btree_5__0_1_2_3_4__31_diff> rel_38_diff_minus_path2_info_1 = std::make_unique<t_btree_5__0_1_2_3_4__31_diff>();
souffle::RelationWrapper<31,t_btree_5__0_1_2_3_4__31_diff,Tuple<RamDomain,5>,5,1> wrapper_rel_38_diff_minus_path2_info_1;
// -- Table: diff_plus@_path2.@info.1
std::unique_ptr<t_btree_5__0_1_2_3_4__31_diff> rel_39_diff_plus_path2_info_1 = std::make_unique<t_btree_5__0_1_2_3_4__31_diff>();
souffle::RelationWrapper<32,t_btree_5__0_1_2_3_4__31_diff,Tuple<RamDomain,5>,5,1> wrapper_rel_39_diff_plus_path2_info_1;
// -- Table: actual_diff_plus@_path2.@info.1
std::unique_ptr<t_btree_5__0_1_2_3_4__31_diff> rel_40_actual_diff_plus_path2_info_1 = std::make_unique<t_btree_5__0_1_2_3_4__31_diff>();
souffle::RelationWrapper<33,t_btree_5__0_1_2_3_4__31_diff,Tuple<RamDomain,5>,5,1> wrapper_rel_40_actual_diff_plus_path2_info_1;
// -- Table: actual_diff_minus@_path2.@info.1
std::unique_ptr<t_btree_5__0_1_2_3_4__31_diff> rel_41_actual_diff_minus_path2_info_1 = std::make_unique<t_btree_5__0_1_2_3_4__31_diff>();
souffle::RelationWrapper<34,t_btree_5__0_1_2_3_4__31_diff,Tuple<RamDomain,5>,5,1> wrapper_rel_41_actual_diff_minus_path2_info_1;
// -- Table: diff_applied@_path2.@info.1
std::unique_ptr<t_btree_5__0_1_2_3_4__31_diff_applied> rel_42_diff_applied_path2_info_1 = std::make_unique<t_btree_5__0_1_2_3_4__31_diff_applied>();
souffle::RelationWrapper<35,t_btree_5__0_1_2_3_4__31_diff_applied,Tuple<RamDomain,5>,5,1> wrapper_rel_42_diff_applied_path2_info_1;
// -- Table: path2.@info.1
std::unique_ptr<t_btree_5__0_1_2_3_4__31> rel_43_path2_info_1 = std::make_unique<t_btree_5__0_1_2_3_4__31>();
souffle::RelationWrapper<36,t_btree_5__0_1_2_3_4__31,Tuple<RamDomain,5>,5,1> wrapper_rel_43_path2_info_1;
// -- Table: path_@restricted_1
std::unique_ptr<t_btree_1__0__1> rel_44_path_restricted_1 = std::make_unique<t_btree_1__0__1>();
souffle::RelationWrapper<37,t_btree_1__0__1,Tuple<RamDomain,1>,1,1> wrapper_rel_44_path_restricted_1;
// -- Table: path_@restricted_0
std::unique_ptr<t_btree_1__0__1> rel_45_path_restricted_0 = std::make_unique<t_btree_1__0__1>();
souffle::RelationWrapper<38,t_btree_1__0__1,Tuple<RamDomain,1>,1,1> wrapper_rel_45_path_restricted_0;
public:
Sf_query() : 
wrapper_rel_1_diff_minus_edge(*rel_1_diff_minus_edge,symTable,"diff_minus@_edge",std::array<const char *,4>{{"i:number","i:number","i:number","i:number"}},std::array<const char *,4>{{"x","y","@iteration","@current_count"}}),

wrapper_rel_2_diff_plus_edge(*rel_2_diff_plus_edge,symTable,"diff_plus@_edge",std::array<const char *,4>{{"i:number","i:number","i:number","i:number"}},std::array<const char *,4>{{"x","y","@iteration","@current_count"}}),

wrapper_rel_3_actual_diff_plus_edge(*rel_3_actual_diff_plus_edge,symTable,"actual_diff_plus@_edge",std::array<const char *,4>{{"i:number","i:number","i:number","i:number"}},std::array<const char *,4>{{"x","y","@iteration","@current_count"}}),

wrapper_rel_4_actual_diff_minus_edge(*rel_4_actual_diff_minus_edge,symTable,"actual_diff_minus@_edge",std::array<const char *,4>{{"i:number","i:number","i:number","i:number"}},std::array<const char *,4>{{"x","y","@iteration","@current_count"}}),

wrapper_rel_5_diff_applied_edge(*rel_5_diff_applied_edge,symTable,"diff_applied@_edge",std::array<const char *,4>{{"i:number","i:number","i:number","i:number"}},std::array<const char *,4>{{"x","y","@iteration","@current_count"}}),

wrapper_rel_6_edge(*rel_6_edge,symTable,"edge",std::array<const char *,4>{{"i:number","i:number","i:number","i:number"}},std::array<const char *,4>{{"x","y","@iteration","@current_count"}}),

wrapper_rel_7_diff_minus_path(*rel_7_diff_minus_path,symTable,"diff_minus@_path",std::array<const char *,4>{{"i:number","i:number","i:number","i:number"}},std::array<const char *,4>{{"x","y","@iteration","@current_count"}}),

wrapper_rel_8_diff_plus_path(*rel_8_diff_plus_path,symTable,"diff_plus@_path",std::array<const char *,4>{{"i:number","i:number","i:number","i:number"}},std::array<const char *,4>{{"x","y","@iteration","@current_count"}}),

wrapper_rel_9_actual_diff_plus_path(*rel_9_actual_diff_plus_path,symTable,"actual_diff_plus@_path",std::array<const char *,4>{{"i:number","i:number","i:number","i:number"}},std::array<const char *,4>{{"x","y","@iteration","@current_count"}}),

wrapper_rel_10_actual_diff_minus_path(*rel_10_actual_diff_minus_path,symTable,"actual_diff_minus@_path",std::array<const char *,4>{{"i:number","i:number","i:number","i:number"}},std::array<const char *,4>{{"x","y","@iteration","@current_count"}}),

wrapper_rel_11_diff_applied_path(*rel_11_diff_applied_path,symTable,"diff_applied@_path",std::array<const char *,4>{{"i:number","i:number","i:number","i:number"}},std::array<const char *,4>{{"x","y","@iteration","@current_count"}}),

wrapper_rel_12_path(*rel_12_path,symTable,"path",std::array<const char *,4>{{"i:number","i:number","i:number","i:number"}},std::array<const char *,4>{{"x","y","@iteration","@current_count"}}),

wrapper_rel_19_scc_1_max_iter(*rel_19_scc_1_max_iter,symTable,"scc_1_@max_iter",std::array<const char *,1>{{"s"}},std::array<const char *,1>{{"max_iter"}}),

wrapper_rel_20_diff_minus_path2(*rel_20_diff_minus_path2,symTable,"diff_minus@_path2",std::array<const char *,4>{{"i:number","i:number","i:number","i:number"}},std::array<const char *,4>{{"x","y","@iteration","@current_count"}}),

wrapper_rel_21_diff_plus_path2(*rel_21_diff_plus_path2,symTable,"diff_plus@_path2",std::array<const char *,4>{{"i:number","i:number","i:number","i:number"}},std::array<const char *,4>{{"x","y","@iteration","@current_count"}}),

wrapper_rel_22_actual_diff_plus_path2(*rel_22_actual_diff_plus_path2,symTable,"actual_diff_plus@_path2",std::array<const char *,4>{{"i:number","i:number","i:number","i:number"}},std::array<const char *,4>{{"x","y","@iteration","@current_count"}}),

wrapper_rel_23_actual_diff_minus_path2(*rel_23_actual_diff_minus_path2,symTable,"actual_diff_minus@_path2",std::array<const char *,4>{{"i:number","i:number","i:number","i:number"}},std::array<const char *,4>{{"x","y","@iteration","@current_count"}}),

wrapper_rel_24_diff_applied_path2(*rel_24_diff_applied_path2,symTable,"diff_applied@_path2",std::array<const char *,4>{{"i:number","i:number","i:number","i:number"}},std::array<const char *,4>{{"x","y","@iteration","@current_count"}}),

wrapper_rel_25_path2(*rel_25_path2,symTable,"path2",std::array<const char *,4>{{"i:number","i:number","i:number","i:number"}},std::array<const char *,4>{{"x","y","@iteration","@current_count"}}),

wrapper_rel_26_diff_minus_path_info_1(*rel_26_diff_minus_path_info_1,symTable,"diff_minus@_path.@info.1",std::array<const char *,4>{{"i:number","s:symbol","s:symbol","s:symbol"}},std::array<const char *,4>{{"clause_num","head_vars","rel_0","clause_repr"}}),

wrapper_rel_27_diff_plus_path_info_1(*rel_27_diff_plus_path_info_1,symTable,"diff_plus@_path.@info.1",std::array<const char *,4>{{"i:number","s:symbol","s:symbol","s:symbol"}},std::array<const char *,4>{{"clause_num","head_vars","rel_0","clause_repr"}}),

wrapper_rel_28_actual_diff_plus_path_info_1(*rel_28_actual_diff_plus_path_info_1,symTable,"actual_diff_plus@_path.@info.1",std::array<const char *,4>{{"i:number","s:symbol","s:symbol","s:symbol"}},std::array<const char *,4>{{"clause_num","head_vars","rel_0","clause_repr"}}),

wrapper_rel_29_actual_diff_minus_path_info_1(*rel_29_actual_diff_minus_path_info_1,symTable,"actual_diff_minus@_path.@info.1",std::array<const char *,4>{{"i:number","s:symbol","s:symbol","s:symbol"}},std::array<const char *,4>{{"clause_num","head_vars","rel_0","clause_repr"}}),

wrapper_rel_30_diff_applied_path_info_1(*rel_30_diff_applied_path_info_1,symTable,"diff_applied@_path.@info.1",std::array<const char *,4>{{"i:number","s:symbol","s:symbol","s:symbol"}},std::array<const char *,4>{{"clause_num","head_vars","rel_0","clause_repr"}}),

wrapper_rel_31_path_info_1(*rel_31_path_info_1,symTable,"path.@info.1",std::array<const char *,4>{{"i:number","s:symbol","s:symbol","s:symbol"}},std::array<const char *,4>{{"clause_num","head_vars","rel_0","clause_repr"}}),

wrapper_rel_32_diff_minus_path_info_2(*rel_32_diff_minus_path_info_2,symTable,"diff_minus@_path.@info.2",std::array<const char *,5>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,5>{{"clause_num","head_vars","rel_0","rel_1","clause_repr"}}),

wrapper_rel_33_diff_plus_path_info_2(*rel_33_diff_plus_path_info_2,symTable,"diff_plus@_path.@info.2",std::array<const char *,5>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,5>{{"clause_num","head_vars","rel_0","rel_1","clause_repr"}}),

wrapper_rel_34_actual_diff_plus_path_info_2(*rel_34_actual_diff_plus_path_info_2,symTable,"actual_diff_plus@_path.@info.2",std::array<const char *,5>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,5>{{"clause_num","head_vars","rel_0","rel_1","clause_repr"}}),

wrapper_rel_35_actual_diff_minus_path_info_2(*rel_35_actual_diff_minus_path_info_2,symTable,"actual_diff_minus@_path.@info.2",std::array<const char *,5>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,5>{{"clause_num","head_vars","rel_0","rel_1","clause_repr"}}),

wrapper_rel_36_diff_applied_path_info_2(*rel_36_diff_applied_path_info_2,symTable,"diff_applied@_path.@info.2",std::array<const char *,5>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,5>{{"clause_num","head_vars","rel_0","rel_1","clause_repr"}}),

wrapper_rel_37_path_info_2(*rel_37_path_info_2,symTable,"path.@info.2",std::array<const char *,5>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,5>{{"clause_num","head_vars","rel_0","rel_1","clause_repr"}}),

wrapper_rel_38_diff_minus_path2_info_1(*rel_38_diff_minus_path2_info_1,symTable,"diff_minus@_path2.@info.1",std::array<const char *,5>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,5>{{"clause_num","head_vars","rel_0","rel_1","clause_repr"}}),

wrapper_rel_39_diff_plus_path2_info_1(*rel_39_diff_plus_path2_info_1,symTable,"diff_plus@_path2.@info.1",std::array<const char *,5>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,5>{{"clause_num","head_vars","rel_0","rel_1","clause_repr"}}),

wrapper_rel_40_actual_diff_plus_path2_info_1(*rel_40_actual_diff_plus_path2_info_1,symTable,"actual_diff_plus@_path2.@info.1",std::array<const char *,5>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,5>{{"clause_num","head_vars","rel_0","rel_1","clause_repr"}}),

wrapper_rel_41_actual_diff_minus_path2_info_1(*rel_41_actual_diff_minus_path2_info_1,symTable,"actual_diff_minus@_path2.@info.1",std::array<const char *,5>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,5>{{"clause_num","head_vars","rel_0","rel_1","clause_repr"}}),

wrapper_rel_42_diff_applied_path2_info_1(*rel_42_diff_applied_path2_info_1,symTable,"diff_applied@_path2.@info.1",std::array<const char *,5>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,5>{{"clause_num","head_vars","rel_0","rel_1","clause_repr"}}),

wrapper_rel_43_path2_info_1(*rel_43_path2_info_1,symTable,"path2.@info.1",std::array<const char *,5>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,5>{{"clause_num","head_vars","rel_0","rel_1","clause_repr"}}),

wrapper_rel_44_path_restricted_1(*rel_44_path_restricted_1,symTable,"path_@restricted_1",std::array<const char *,1>{{"i:number"}},std::array<const char *,1>{{"x"}}),

wrapper_rel_45_path_restricted_0(*rel_45_path_restricted_0,symTable,"path_@restricted_0",std::array<const char *,1>{{"i:number"}},std::array<const char *,1>{{"x"}}){
addRelation("diff_minus@_edge",&wrapper_rel_1_diff_minus_edge,false,false);
addRelation("diff_plus@_edge",&wrapper_rel_2_diff_plus_edge,false,false);
addRelation("actual_diff_plus@_edge",&wrapper_rel_3_actual_diff_plus_edge,false,false);
addRelation("actual_diff_minus@_edge",&wrapper_rel_4_actual_diff_minus_edge,false,false);
addRelation("diff_applied@_edge",&wrapper_rel_5_diff_applied_edge,true,false);
addRelation("edge",&wrapper_rel_6_edge,false,false);
addRelation("diff_minus@_path",&wrapper_rel_7_diff_minus_path,false,false);
addRelation("diff_plus@_path",&wrapper_rel_8_diff_plus_path,false,false);
addRelation("actual_diff_plus@_path",&wrapper_rel_9_actual_diff_plus_path,false,false);
addRelation("actual_diff_minus@_path",&wrapper_rel_10_actual_diff_minus_path,false,false);
addRelation("diff_applied@_path",&wrapper_rel_11_diff_applied_path,false,false);
addRelation("path",&wrapper_rel_12_path,false,true);
addRelation("scc_1_@max_iter",&wrapper_rel_19_scc_1_max_iter,false,false);
addRelation("diff_minus@_path2",&wrapper_rel_20_diff_minus_path2,false,false);
addRelation("diff_plus@_path2",&wrapper_rel_21_diff_plus_path2,false,false);
addRelation("actual_diff_plus@_path2",&wrapper_rel_22_actual_diff_plus_path2,false,false);
addRelation("actual_diff_minus@_path2",&wrapper_rel_23_actual_diff_minus_path2,false,false);
addRelation("diff_applied@_path2",&wrapper_rel_24_diff_applied_path2,false,false);
addRelation("path2",&wrapper_rel_25_path2,false,true);
addRelation("diff_minus@_path.@info.1",&wrapper_rel_26_diff_minus_path_info_1,false,false);
addRelation("diff_plus@_path.@info.1",&wrapper_rel_27_diff_plus_path_info_1,false,false);
addRelation("actual_diff_plus@_path.@info.1",&wrapper_rel_28_actual_diff_plus_path_info_1,false,false);
addRelation("actual_diff_minus@_path.@info.1",&wrapper_rel_29_actual_diff_minus_path_info_1,false,false);
addRelation("diff_applied@_path.@info.1",&wrapper_rel_30_diff_applied_path_info_1,false,false);
addRelation("path.@info.1",&wrapper_rel_31_path_info_1,false,false);
addRelation("diff_minus@_path.@info.2",&wrapper_rel_32_diff_minus_path_info_2,false,false);
addRelation("diff_plus@_path.@info.2",&wrapper_rel_33_diff_plus_path_info_2,false,false);
addRelation("actual_diff_plus@_path.@info.2",&wrapper_rel_34_actual_diff_plus_path_info_2,false,false);
addRelation("actual_diff_minus@_path.@info.2",&wrapper_rel_35_actual_diff_minus_path_info_2,false,false);
addRelation("diff_applied@_path.@info.2",&wrapper_rel_36_diff_applied_path_info_2,false,false);
addRelation("path.@info.2",&wrapper_rel_37_path_info_2,false,false);
addRelation("diff_minus@_path2.@info.1",&wrapper_rel_38_diff_minus_path2_info_1,false,false);
addRelation("diff_plus@_path2.@info.1",&wrapper_rel_39_diff_plus_path2_info_1,false,false);
addRelation("actual_diff_plus@_path2.@info.1",&wrapper_rel_40_actual_diff_plus_path2_info_1,false,false);
addRelation("actual_diff_minus@_path2.@info.1",&wrapper_rel_41_actual_diff_minus_path2_info_1,false,false);
addRelation("diff_applied@_path2.@info.1",&wrapper_rel_42_diff_applied_path2_info_1,false,false);
addRelation("path2.@info.1",&wrapper_rel_43_path2_info_1,false,false);
addRelation("path_@restricted_1",&wrapper_rel_44_path_restricted_1,false,false);
addRelation("path_@restricted_0",&wrapper_rel_45_path_restricted_0,false,false);
}
~Sf_query() {
}
int epochNumber = 0;
private:
std::string inputDirectory;
std::string outputDirectory;
bool performIO;
std::atomic<RamDomain> ctr{};

std::atomic<size_t> iter{};
std::chrono::microseconds ioTime;
private:
void runFunction(std::string inputDirectory = ".", std::string outputDirectory = ".", size_t stratumIndex = (size_t) -1, bool performIO = false) {
this->inputDirectory = inputDirectory;
this->outputDirectory = outputDirectory;
this->performIO = performIO;
ioTime = std::chrono::microseconds::zero();
auto evalStart = std::chrono::high_resolution_clock::now();
SignalHandler::instance()->set();
#if defined(_OPENMP)
if (getNumThreads() > 0) {omp_set_num_threads(getNumThreads());}
#endif

// -- query evaluation --
/* BEGIN STRATUM 0 */
[&]() {
if (performIO) {
auto ioStart = std::chrono::high_resolution_clock::now();
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./edge.facts"},{"name","edge"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<bool>({0,0,0,0}), symTable, ioDirectives, true, 1)->readAll(*rel_5_diff_applied_edge);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
auto ioEnd = std::chrono::high_resolution_clock::now();
ioTime += std::chrono::duration_cast<std::chrono::microseconds>(ioEnd - ioStart);
}
}();
/* END STRATUM 0 */
/* BEGIN STRATUM 1 */
[&]() {
SignalHandler::instance()->setMsg(R"_(diff_applied@_path(x,y,0,1) :- 
   diff_applied@_edge(x,y,@iteration_0,@current_count_0),
   @current_count_0 > 0.
in file /home/david/docs/souffle-fault-localization/tests/path/path.dl [6:1-6:26])_");
if(!(rel_5_diff_applied_edge->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_5_diff_applied_edge_op_ctxt,rel_5_diff_applied_edge->createContext());
CREATE_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt,rel_11_diff_applied_path->createContext());
for(const auto& env0 : *rel_5_diff_applied_edge) {
if( ((env0[3]) > (RamDomain(0)))) {
Tuple<RamDomain,4> tuple{{static_cast<RamDomain>(env0[0]),static_cast<RamDomain>(env0[1]),static_cast<RamDomain>(RamDomain(0)),static_cast<RamDomain>(RamDomain(1))}};
rel_11_diff_applied_path->insert(tuple,READ_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt));
}
}
}
();}
rel_14_delta_diff_applied_path->insertAll(*rel_11_diff_applied_path);
[&](){
CREATE_OP_CONTEXT(rel_12_path_op_ctxt,rel_12_path->createContext());
CREATE_OP_CONTEXT(rel_19_scc_1_max_iter_op_ctxt,rel_19_scc_1_max_iter->createContext());
ram::Tuple<RamDomain,1> env0;
RamDomain res0 = MIN_RAM_DOMAIN;
for(const auto& env0 : *rel_12_path) {
if( true) {
res0 = std::max(res0,env0[2]);
}
}
env0[0] = res0;
Tuple<RamDomain,1> tuple{{static_cast<RamDomain>(std::max({env0[0], }))}};
rel_19_scc_1_max_iter->insert(tuple,READ_OP_CONTEXT(rel_19_scc_1_max_iter_op_ctxt));
}
();iter = 1;
for(;;) {
SignalHandler::instance()->setMsg(R"_(@new_diff_applied@_path(x,y,iternum(),1) :- 
   diff_applied@_edge(x,z,@iteration_0,@current_count_0),
   @delta_diff_applied@_path(z,y,@iteration_1,@current_count_1),
   subsump!diff_applied@_path(x,y,iternum(),1),
   @current_count_0 > 0.
in file /home/david/docs/souffle-fault-localization/tests/path/path.dl [7:1-7:38])_");
if(!(rel_5_diff_applied_edge->empty()) && !(rel_14_delta_diff_applied_path->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_5_diff_applied_edge_op_ctxt,rel_5_diff_applied_edge->createContext());
CREATE_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt,rel_11_diff_applied_path->createContext());
CREATE_OP_CONTEXT(rel_13_new_diff_applied_path_op_ctxt,rel_13_new_diff_applied_path->createContext());
CREATE_OP_CONTEXT(rel_14_delta_diff_applied_path_op_ctxt,rel_14_delta_diff_applied_path->createContext());
for(const auto& env0 : *rel_5_diff_applied_edge) {
if( ((env0[3]) > (RamDomain(0)))) {
const Tuple<RamDomain,4> key{{env0[1],0,0,0}};
auto range = rel_14_delta_diff_applied_path->equalRange_1(key,READ_OP_CONTEXT(rel_14_delta_diff_applied_path_op_ctxt));
for(const auto& env1 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_11_diff_applied_path->equalRange_3(Tuple<RamDomain,4>{{env0[0],env1[1],0,0}}, READ_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt));
if (RamDomain(1) <= 0) {
if (existenceCheck.empty()) return true;
for (auto& tup : existenceCheck) {
if (tup[2] == (iter) && tup[3] > 0) return false;
}
return true;
} else {
if (existenceCheck.empty()) return false;
for (auto& tup : existenceCheck) {
if (tup[2] < (iter) && tup[3] > 0) return true;
}
if (RamDomain(1) == 2) {
for (auto& tup : existenceCheck) {
if (tup[2] == (iter) && tup[3] > 0) return true;
}
return false;
}
return false;
}
;}()
)) {
Tuple<RamDomain,4> tuple{{static_cast<RamDomain>(env0[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>((iter)),static_cast<RamDomain>(RamDomain(1))}};
rel_13_new_diff_applied_path->insert(tuple,READ_OP_CONTEXT(rel_13_new_diff_applied_path_op_ctxt));
}
}
}
}
}
();}
if(rel_13_new_diff_applied_path->empty()) break;
rel_11_diff_applied_path->insertAll(*rel_13_new_diff_applied_path);
std::swap(rel_14_delta_diff_applied_path, rel_13_new_diff_applied_path);
rel_13_new_diff_applied_path->purge();
iter++;
}
iter = 0;
if (!isHintsProfilingEnabled()) rel_13_new_diff_applied_path->purge();
if (!isHintsProfilingEnabled()) rel_14_delta_diff_applied_path->purge();
}();
/* END STRATUM 1 */
/* BEGIN STRATUM 2 */
[&]() {
SignalHandler::instance()->setMsg(R"_(diff_applied@_path2(x,y,0,1) :- 
   diff_applied@_path(x,y,@iteration_0,@current_count_0),
   pos!diff_applied@_edge(x,y,-1,0),
   @current_count_0 > 0.
in file /home/david/docs/souffle-fault-localization/tests/path/path.dl [9:1-9:40])_");
if(!(rel_11_diff_applied_path->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_5_diff_applied_edge_op_ctxt,rel_5_diff_applied_edge->createContext());
CREATE_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt,rel_11_diff_applied_path->createContext());
CREATE_OP_CONTEXT(rel_24_diff_applied_path2_op_ctxt,rel_24_diff_applied_path2->createContext());
for(const auto& env0 : *rel_11_diff_applied_path) {
if( ((env0[3]) > (RamDomain(0))) && !([&]() -> bool {
auto existenceCheck = rel_5_diff_applied_edge->equalRange_3(Tuple<RamDomain,4>{{env0[0],env0[1],0,0}},READ_OP_CONTEXT(rel_5_diff_applied_edge_op_ctxt));
for (const auto& tup : existenceCheck) {
if (RamDomain(0) == 1) {
if (tup[3] > 0) {
if (RamDomain(-1) == -1 || (RamDomain(-1) <= (iter-1) && tup[2] <= (iter - 1))) return true;
}
}
else if (RamDomain(0) == 0) {
if (tup[3] > 0 && (RamDomain(-1) == -1 || iter == 0 || tup[2] <= (iter-1))) {
return true;
}
}
else if (RamDomain(0) == -1) {
if (tup[3] <= 0) {
return true;
}
}
}
return false;
}()
)) {
Tuple<RamDomain,4> tuple{{static_cast<RamDomain>(env0[0]),static_cast<RamDomain>(env0[1]),static_cast<RamDomain>(RamDomain(0)),static_cast<RamDomain>(RamDomain(1))}};
rel_24_diff_applied_path2->insert(tuple,READ_OP_CONTEXT(rel_24_diff_applied_path2_op_ctxt));
}
}
}
();}
}();
/* END STRATUM 2 */
/* BEGIN STRATUM 3 */
[&]() {
SignalHandler::instance()->setMsg(R"_(path.@info.1(1,"x,y","edge,x,y","path(x,y) :- 
   edge(x,y).").
in file  [0:0-0:0])_");
rel_31_path_info_1->insert(RamDomain(1),RamDomain(0),RamDomain(1),RamDomain(2));
}();
/* END STRATUM 3 */
/* BEGIN STRATUM 4 */
[&]() {
SignalHandler::instance()->setMsg(R"_(path.@info.2(2,"x,y","edge,x,z","path,z,y","path(x,y) :- 
   edge(x,z),
   path(z,y).").
in file  [0:0-0:0])_");
rel_37_path_info_2->insert(RamDomain(2),RamDomain(0),RamDomain(3),RamDomain(4),RamDomain(5));
}();
/* END STRATUM 4 */
/* BEGIN STRATUM 5 */
[&]() {
SignalHandler::instance()->setMsg(R"_(path2.@info.1(1,"x,y","path,x,y","!edge","path2(x,y) :- 
   path(x,y),
   !edge(x,y).").
in file  [0:0-0:0])_");
rel_43_path2_info_1->insert(RamDomain(1),RamDomain(0),RamDomain(6),RamDomain(7),RamDomain(8));
[&]() -> bool {
std::vector<RamDomain> args;
std::vector<RamDomain> ret;
std::vector<bool> err;
executeSubroutine("incremental_cleanup", args, ret, err);
if (ret.size() == 0) return false;
if (ret[0] == 0) return false; else return true;
}()
;
if (performIO) {
auto ioStart = std::chrono::high_resolution_clock::now();
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","x\ty\t@iteration\t@current_count"},{"filename","./path.csv"},{"name","path"}});
if (!outputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getWriter(std::vector<bool>({0,0,0,0}), symTable, ioDirectives, true, 1)->writeAll(*rel_12_path);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
auto ioEnd = std::chrono::high_resolution_clock::now();
ioTime += std::chrono::duration_cast<std::chrono::microseconds>(ioEnd - ioStart);
}
if (performIO) {
auto ioStart = std::chrono::high_resolution_clock::now();
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","x\ty\t@iteration\t@current_count"},{"filename","./path2.csv"},{"name","path2"}});
if (!outputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getWriter(std::vector<bool>({0,0,0,0}), symTable, ioDirectives, true, 1)->writeAll(*rel_25_path2);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
auto ioEnd = std::chrono::high_resolution_clock::now();
ioTime += std::chrono::duration_cast<std::chrono::microseconds>(ioEnd - ioStart);
}
}();
/* END STRATUM 5 */

// -- relation hint statistics --
if(isHintsProfilingEnabled()) {
std::cout << " -- Operation Hint Statistics --\n";
}
SignalHandler::instance()->reset();
auto evalEnd = std::chrono::high_resolution_clock::now();
auto evalTime = std::chrono::duration_cast<std::chrono::microseconds>(evalEnd - evalStart) - ioTime;
if (isRuntimePrintingEnabled()) std::cout << "eval-time:" << evalTime.count() << std::endl;
ioTime = std::chrono::microseconds::zero();
}
public:
void run(size_t stratumIndex = (size_t) -1) override { runFunction(".", ".", stratumIndex, false); }
public:
void runAll(std::string inputDirectory = ".", std::string outputDirectory = ".", size_t stratumIndex = (size_t) -1) override { runFunction(inputDirectory, outputDirectory, stratumIndex, true);
}
public:
void printAll(std::string outputDirectory = ".") override {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","x\ty\t@iteration\t@current_count"},{"filename","./path.csv"},{"name","path"}});
if (!outputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getWriter(std::vector<bool>({0,0,0,0}), symTable, ioDirectives, true, 1)->writeAll(*rel_12_path);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","x\ty\t@iteration\t@current_count"},{"filename","./path2.csv"},{"name","path2"}});
if (!outputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getWriter(std::vector<bool>({0,0,0,0}), symTable, ioDirectives, true, 1)->writeAll(*rel_25_path2);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
public:
void loadAll(std::string inputDirectory = ".") override {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./edge.facts"},{"name","edge"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<bool>({0,0,0,0}), symTable, ioDirectives, true, 1)->readAll(*rel_5_diff_applied_edge);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
public:
void dumpInputs(std::ostream& out = std::cout) override {
try {IODirectives ioDirectives;
ioDirectives.setIOType("stdout");
ioDirectives.setRelationName("rel_5_diff_applied_edge");
IOSystem::getInstance().getWriter(std::vector<bool>({0,0,0,0}), symTable, ioDirectives, true, 1)->writeAll(*rel_5_diff_applied_edge);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
public:
void dumpOutputs(std::ostream& out = std::cout) override {
try {IODirectives ioDirectives;
ioDirectives.setIOType("stdout");
ioDirectives.setRelationName("rel_12_path");
IOSystem::getInstance().getWriter(std::vector<bool>({0,0,0,0}), symTable, ioDirectives, true, 1)->writeAll(*rel_12_path);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {IODirectives ioDirectives;
ioDirectives.setIOType("stdout");
ioDirectives.setRelationName("rel_25_path2");
IOSystem::getInstance().getWriter(std::vector<bool>({0,0,0,0}), symTable, ioDirectives, true, 1)->writeAll(*rel_25_path2);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
public:
SymbolTable& getSymbolTable() override {
return symTable;
}
void executeSubroutine(std::string name, const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) override {
if (name == "diff_minus_edge_search") {
subproof_0(args, ret, err);
}
if (name == "diff_minus_path2_search") {
subproof_1(args, ret, err);
}
if (name == "diff_minus_path_search") {
subproof_2(args, ret, err);
}
if (name == "diff_plus_edge_search") {
subproof_3(args, ret, err);
}
if (name == "diff_plus_path2_search") {
subproof_4(args, ret, err);
}
if (name == "diff_plus_path_search") {
subproof_5(args, ret, err);
}
if (name == "edge_search") {
subproof_6(args, ret, err);
}
if (name == "incremental_cleanup") {
subproof_7(args, ret, err);
}
if (name == "incremental_update_cleanup") {
subproof_8(args, ret, err);
}
if (name == "incremental_update_clear_diffs") {
subproof_9(args, ret, err);
}
if (name == "path2_search") {
subproof_10(args, ret, err);
}
if (name == "path2_subproof") {
subproof_11(args, ret, err);
}
if (name == "path_search") {
subproof_12(args, ret, err);
}
if (name == "path_subproof") {
subproof_13(args, ret, err);
}
if (name == "scc_1_exit") {
subproof_14(args, ret, err);
}
if (name == "update") {
ioTime = std::chrono::microseconds::zero();
auto updateStart = std::chrono::high_resolution_clock::now();
subproof_15(args, ret, err);
auto updateEnd = std::chrono::high_resolution_clock::now();
auto updateTime = std::chrono::duration_cast<std::chrono::microseconds>(updateEnd - updateStart) - ioTime;
if (isRuntimePrintingEnabled()) std::cout << "update-time:" << updateTime.count() << std::endl;
ioTime = std::chrono::microseconds::zero();
}
}
void subproof_0(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
[&](){
CREATE_OP_CONTEXT(rel_4_actual_diff_minus_edge_op_ctxt,rel_4_actual_diff_minus_edge->createContext());
const Tuple<RamDomain,4> key{{(args)[0],(args)[1],0,0}};
auto range = rel_4_actual_diff_minus_edge->equalRange_3(key,READ_OP_CONTEXT(rel_4_actual_diff_minus_edge_op_ctxt));
for(const auto& env0 : range) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(env0[0]);
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env0[3]);
err.push_back(false);
return;
}
}
();return;
}
void subproof_1(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
[&](){
CREATE_OP_CONTEXT(rel_23_actual_diff_minus_path2_op_ctxt,rel_23_actual_diff_minus_path2->createContext());
const Tuple<RamDomain,4> key{{(args)[0],(args)[1],0,0}};
auto range = rel_23_actual_diff_minus_path2->equalRange_3(key,READ_OP_CONTEXT(rel_23_actual_diff_minus_path2_op_ctxt));
for(const auto& env0 : range) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(env0[0]);
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env0[3]);
err.push_back(false);
return;
}
}
();return;
}
void subproof_2(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
[&](){
CREATE_OP_CONTEXT(rel_10_actual_diff_minus_path_op_ctxt,rel_10_actual_diff_minus_path->createContext());
const Tuple<RamDomain,4> key{{(args)[0],(args)[1],0,0}};
auto range = rel_10_actual_diff_minus_path->equalRange_3(key,READ_OP_CONTEXT(rel_10_actual_diff_minus_path_op_ctxt));
for(const auto& env0 : range) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(env0[0]);
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env0[3]);
err.push_back(false);
return;
}
}
();return;
}
void subproof_3(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
[&](){
CREATE_OP_CONTEXT(rel_3_actual_diff_plus_edge_op_ctxt,rel_3_actual_diff_plus_edge->createContext());
const Tuple<RamDomain,4> key{{(args)[0],(args)[1],0,0}};
auto range = rel_3_actual_diff_plus_edge->equalRange_3(key,READ_OP_CONTEXT(rel_3_actual_diff_plus_edge_op_ctxt));
for(const auto& env0 : range) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(env0[0]);
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env0[3]);
err.push_back(false);
return;
}
}
();return;
}
void subproof_4(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
[&](){
CREATE_OP_CONTEXT(rel_22_actual_diff_plus_path2_op_ctxt,rel_22_actual_diff_plus_path2->createContext());
const Tuple<RamDomain,4> key{{(args)[0],(args)[1],0,0}};
auto range = rel_22_actual_diff_plus_path2->equalRange_3(key,READ_OP_CONTEXT(rel_22_actual_diff_plus_path2_op_ctxt));
for(const auto& env0 : range) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(env0[0]);
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env0[3]);
err.push_back(false);
return;
}
}
();return;
}
void subproof_5(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
[&](){
CREATE_OP_CONTEXT(rel_9_actual_diff_plus_path_op_ctxt,rel_9_actual_diff_plus_path->createContext());
const Tuple<RamDomain,4> key{{(args)[0],(args)[1],0,0}};
auto range = rel_9_actual_diff_plus_path->equalRange_3(key,READ_OP_CONTEXT(rel_9_actual_diff_plus_path_op_ctxt));
for(const auto& env0 : range) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(env0[0]);
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env0[3]);
err.push_back(false);
return;
}
}
();return;
}
void subproof_6(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
[&](){
CREATE_OP_CONTEXT(rel_6_edge_op_ctxt,rel_6_edge->createContext());
const Tuple<RamDomain,4> key{{(args)[0],(args)[1],0,0}};
auto range = rel_6_edge->equalRange_3(key,READ_OP_CONTEXT(rel_6_edge_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[3]) > (RamDomain(0)))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(env0[0]);
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env0[3]);
err.push_back(false);
return;
}
}
}
();return;
}
void subproof_7(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
rel_6_edge->relationLoad(*rel_5_diff_applied_edge);
rel_12_path->relationLoad(*rel_11_diff_applied_path);
rel_25_path2->relationLoad(*rel_24_diff_applied_path2);
return;
}
void subproof_8(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
rel_6_edge->insertAll(*rel_1_diff_minus_edge);
{
CREATE_OP_CONTEXT(rel_6_edge_op_ctxt,rel_6_edge->createContext());
for (const auto& tup : *rel_2_diff_plus_edge) {
auto existenceCheck = rel_6_edge->equalRange_3(Tuple<RamDomain,4>{{tup[0],tup[1],0,0}}, READ_OP_CONTEXT(rel_6_edge_op_ctxt));
for (const auto& existingTup : existenceCheck) {
if (existingTup[2] > tup[2]) {
auto updateTuple = existingTup;
updateTuple[3] = 0;
rel_6_edge->insert(updateTuple,READ_OP_CONTEXT(rel_6_edge_op_ctxt));
}
}
rel_6_edge->insert(tup,READ_OP_CONTEXT(rel_6_edge_op_ctxt));
}
}
rel_12_path->insertAll(*rel_7_diff_minus_path);
{
CREATE_OP_CONTEXT(rel_12_path_op_ctxt,rel_12_path->createContext());
for (const auto& tup : *rel_8_diff_plus_path) {
auto existenceCheck = rel_12_path->equalRange_3(Tuple<RamDomain,4>{{tup[0],tup[1],0,0}}, READ_OP_CONTEXT(rel_12_path_op_ctxt));
for (const auto& existingTup : existenceCheck) {
if (existingTup[2] > tup[2]) {
auto updateTuple = existingTup;
updateTuple[3] = 0;
rel_12_path->insert(updateTuple,READ_OP_CONTEXT(rel_12_path_op_ctxt));
}
}
rel_12_path->insert(tup,READ_OP_CONTEXT(rel_12_path_op_ctxt));
}
}
rel_25_path2->insertAll(*rel_20_diff_minus_path2);
{
CREATE_OP_CONTEXT(rel_25_path2_op_ctxt,rel_25_path2->createContext());
for (const auto& tup : *rel_21_diff_plus_path2) {
auto existenceCheck = rel_25_path2->equalRange_3(Tuple<RamDomain,4>{{tup[0],tup[1],0,0}}, READ_OP_CONTEXT(rel_25_path2_op_ctxt));
for (const auto& existingTup : existenceCheck) {
if (existingTup[2] > tup[2]) {
auto updateTuple = existingTup;
updateTuple[3] = 0;
rel_25_path2->insert(updateTuple,READ_OP_CONTEXT(rel_25_path2_op_ctxt));
}
}
rel_25_path2->insert(tup,READ_OP_CONTEXT(rel_25_path2_op_ctxt));
}
}
return;
}
void subproof_9(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
rel_3_actual_diff_plus_edge->purge();
rel_4_actual_diff_minus_edge->purge();
rel_2_diff_plus_edge->purge();
rel_1_diff_minus_edge->purge();
rel_9_actual_diff_plus_path->purge();
rel_10_actual_diff_minus_path->purge();
rel_8_diff_plus_path->purge();
rel_7_diff_minus_path->purge();
rel_22_actual_diff_plus_path2->purge();
rel_23_actual_diff_minus_path2->purge();
rel_21_diff_plus_path2->purge();
rel_20_diff_minus_path2->purge();
return;
}
void subproof_10(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
[&](){
CREATE_OP_CONTEXT(rel_25_path2_op_ctxt,rel_25_path2->createContext());
const Tuple<RamDomain,4> key{{(args)[0],(args)[1],0,0}};
auto range = rel_25_path2->equalRange_3(key,READ_OP_CONTEXT(rel_25_path2_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[3]) > (RamDomain(0)))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(env0[0]);
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env0[3]);
err.push_back(false);
return;
}
}
}
();return;
}
void subproof_11(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(!(rel_12_path->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_6_edge_op_ctxt,rel_6_edge->createContext());
CREATE_OP_CONTEXT(rel_12_path_op_ctxt,rel_12_path->createContext());
const Tuple<RamDomain,4> key{{(args)[0],(args)[1],0,0}};
auto range = rel_12_path->equalRange_3(key,READ_OP_CONTEXT(rel_12_path_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[3]) > (RamDomain(0))) && !(rel_6_edge->contains(Tuple<RamDomain,4>{{env0[0],env0[1],RamDomain(-1),RamDomain(0)}},READ_OP_CONTEXT(rel_6_edge_op_ctxt)))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
ret.push_back(env0[0]);
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env0[3]);
err.push_back(false);
ret.push_back(env0[0]);
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(RamDomain(-1));
err.push_back(false);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
}
();}
return;
}
void subproof_12(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
[&](){
CREATE_OP_CONTEXT(rel_12_path_op_ctxt,rel_12_path->createContext());
const Tuple<RamDomain,4> key{{(args)[0],(args)[1],0,0}};
auto range = rel_12_path->equalRange_3(key,READ_OP_CONTEXT(rel_12_path_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[3]) > (RamDomain(0)))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(env0[0]);
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env0[3]);
err.push_back(false);
return;
}
}
}
();return;
}
void subproof_13(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(!(rel_6_edge->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_6_edge_op_ctxt,rel_6_edge->createContext());
const Tuple<RamDomain,4> key{{(args)[0],(args)[1],0,0}};
auto range = rel_6_edge->equalRange_3(key,READ_OP_CONTEXT(rel_6_edge_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[3]) > (RamDomain(0)))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
ret.push_back(env0[0]);
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env0[3]);
err.push_back(false);
}
}
}
();}
if(!(rel_6_edge->empty()) && !(rel_12_path->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_6_edge_op_ctxt,rel_6_edge->createContext());
CREATE_OP_CONTEXT(rel_12_path_op_ctxt,rel_12_path->createContext());
const Tuple<RamDomain,4> key{{(args)[0],0,0,0}};
auto range = rel_6_edge->equalRange_1(key,READ_OP_CONTEXT(rel_6_edge_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[3]) > (RamDomain(0)))) {
const Tuple<RamDomain,4> key{{env0[1],(args)[1],0,0}};
auto range = rel_12_path->equalRange_3(key,READ_OP_CONTEXT(rel_12_path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[2]) < ((args)[2])) && ((env1[3]) > (RamDomain(0)))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
ret.push_back(env0[0]);
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env0[3]);
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
}
}
}
}
}
();}
return;
}
void subproof_14(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
[&](){
CREATE_OP_CONTEXT(rel_19_scc_1_max_iter_op_ctxt,rel_19_scc_1_max_iter->createContext());
for(const auto& env0 : *rel_19_scc_1_max_iter) {
if( ((env0[0]) >= ((args)[0]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
return;
}
}
}
();[&](){
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
();return;
}
void subproof_15(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
/* BEGIN STRATUM 0 */
[&]() {
rel_5_diff_applied_edge->insertAll(*rel_1_diff_minus_edge);
{
CREATE_OP_CONTEXT(rel_5_diff_applied_edge_op_ctxt,rel_5_diff_applied_edge->createContext());
for (const auto& tup : *rel_2_diff_plus_edge) {
auto existenceCheck = rel_5_diff_applied_edge->equalRange_3(Tuple<RamDomain,4>{{tup[0],tup[1],0,0}}, READ_OP_CONTEXT(rel_5_diff_applied_edge_op_ctxt));
for (const auto& existingTup : existenceCheck) {
if (existingTup[2] > tup[2]) {
auto updateTuple = existingTup;
updateTuple[3] = 0;
rel_5_diff_applied_edge->insert(updateTuple,READ_OP_CONTEXT(rel_5_diff_applied_edge_op_ctxt));
}
}
rel_5_diff_applied_edge->insert(tup,READ_OP_CONTEXT(rel_5_diff_applied_edge_op_ctxt));
}
}
{
CREATE_OP_CONTEXT(rel_5_diff_applied_edge_op_ctxt,rel_5_diff_applied_edge->createContext());
CREATE_OP_CONTEXT(rel_4_actual_diff_minus_edge_op_ctxt,rel_4_actual_diff_minus_edge->createContext());
CREATE_OP_CONTEXT(rel_1_diff_minus_edge_op_ctxt,rel_1_diff_minus_edge->createContext());
auto deltaSource = rel_1_diff_minus_edge->equalRange_4(Tuple<RamDomain,4>{{0,0,iter,0}}, READ_OP_CONTEXT(rel_1_diff_minus_edge_op_ctxt));
for (const auto& tup : deltaSource) {
auto restrictionExistenceCheck = rel_5_diff_applied_edge->equalRange_3(Tuple<RamDomain,4>{{tup[0],tup[1],0,0}}, READ_OP_CONTEXT(rel_5_diff_applied_edge_op_ctxt));
bool insert = true;
for (const auto& t : restrictionExistenceCheck) {
if (t[2] <= tup[2] && t[3] > 0) {
insert = false;
break;
}
}
if (insert) {
auto tuple = tup;
tuple[3] = tup[3] < 0 ? -1 : 1;
rel_4_actual_diff_minus_edge->insert(tuple, READ_OP_CONTEXT(rel_4_actual_diff_minus_edge_op_ctxt));
}
}
if (iter > 0) {
if (rel_4_actual_diff_minus_edge->approx_size() < rel_5_diff_applied_edge->approx_size(iter)) {
for (const auto& tup : *rel_4_actual_diff_minus_edge) {
if (tup[2] == iter || tup[3] == 0) continue;
auto deltaExistenceCheck = rel_5_diff_applied_edge->equalRange_7(Tuple<RamDomain,4>{{tup[0],tup[1],iter,0}}, READ_OP_CONTEXT(rel_5_diff_applied_edge_op_ctxt));
if (deltaExistenceCheck.empty()) continue;
if ((*deltaExistenceCheck.begin())[3] > 0) {
auto tuple = tup;
tuple[3] = tup[3] == -1 ? 1 : -1;
rel_4_actual_diff_minus_edge->insert(tuple, READ_OP_CONTEXT(rel_4_actual_diff_minus_edge_op_ctxt));
}
}
} else {
auto deltaRestriction = rel_5_diff_applied_edge->equalRange_4(Tuple<RamDomain,4>{{0,0,iter,0}}, READ_OP_CONTEXT(rel_5_diff_applied_edge_op_ctxt));
for (const auto& tup : deltaRestriction) {
if (tup[3] <= 0) {
continue;
}
auto existenceCheck = rel_4_actual_diff_minus_edge->equalRange_3(Tuple<RamDomain,4>{{tup[0],tup[1],0,0}}, READ_OP_CONTEXT(rel_4_actual_diff_minus_edge_op_ctxt));
for (const auto& t : existenceCheck) {
if (t[2] == iter || t[3] == 0) continue;
auto tuple = t;
tuple[3] = t[3] == -1 ? 1 : -1;
rel_4_actual_diff_minus_edge->insert(tuple, READ_OP_CONTEXT(rel_4_actual_diff_minus_edge_op_ctxt));
}
}
}
}
}
{
CREATE_OP_CONTEXT(rel_6_edge_op_ctxt,rel_6_edge->createContext());
CREATE_OP_CONTEXT(rel_3_actual_diff_plus_edge_op_ctxt,rel_3_actual_diff_plus_edge->createContext());
CREATE_OP_CONTEXT(rel_2_diff_plus_edge_op_ctxt,rel_2_diff_plus_edge->createContext());
auto deltaSource = rel_2_diff_plus_edge->equalRange_4(Tuple<RamDomain,4>{{0,0,iter,0}}, READ_OP_CONTEXT(rel_2_diff_plus_edge_op_ctxt));
for (const auto& tup : deltaSource) {
auto restrictionExistenceCheck = rel_6_edge->equalRange_3(Tuple<RamDomain,4>{{tup[0],tup[1],0,0}}, READ_OP_CONTEXT(rel_6_edge_op_ctxt));
bool insert = true;
for (const auto& t : restrictionExistenceCheck) {
if (t[2] <= tup[2] && t[3] > 0) {
insert = false;
break;
}
}
if (insert) {
auto tuple = tup;
tuple[3] = tup[3] < 0 ? -1 : 1;
rel_3_actual_diff_plus_edge->insert(tuple, READ_OP_CONTEXT(rel_3_actual_diff_plus_edge_op_ctxt));
}
}
if (iter > 0) {
if (rel_3_actual_diff_plus_edge->approx_size() < rel_6_edge->approx_size(iter)) {
for (const auto& tup : *rel_3_actual_diff_plus_edge) {
if (tup[2] == iter || tup[3] == 0) continue;
auto deltaExistenceCheck = rel_6_edge->equalRange_7(Tuple<RamDomain,4>{{tup[0],tup[1],iter,0}}, READ_OP_CONTEXT(rel_6_edge_op_ctxt));
if (deltaExistenceCheck.empty()) continue;
if ((*deltaExistenceCheck.begin())[3] > 0) {
auto tuple = tup;
tuple[3] = tup[3] == -1 ? 1 : -1;
rel_3_actual_diff_plus_edge->insert(tuple, READ_OP_CONTEXT(rel_3_actual_diff_plus_edge_op_ctxt));
}
}
} else {
auto deltaRestriction = rel_6_edge->equalRange_4(Tuple<RamDomain,4>{{0,0,iter,0}}, READ_OP_CONTEXT(rel_6_edge_op_ctxt));
for (const auto& tup : deltaRestriction) {
if (tup[3] <= 0) {
continue;
}
auto existenceCheck = rel_3_actual_diff_plus_edge->equalRange_3(Tuple<RamDomain,4>{{tup[0],tup[1],0,0}}, READ_OP_CONTEXT(rel_3_actual_diff_plus_edge_op_ctxt));
for (const auto& t : existenceCheck) {
if (t[2] == iter || t[3] == 0) continue;
auto tuple = t;
tuple[3] = t[3] == -1 ? 1 : -1;
rel_3_actual_diff_plus_edge->insert(tuple, READ_OP_CONTEXT(rel_3_actual_diff_plus_edge_op_ctxt));
}
}
}
}
}
}();
/* END STRATUM 0 */
/* BEGIN STRATUM 1 */
[&]() {
SignalHandler::instance()->setMsg(R"_(diff_minus@_path(x,y,0,-1) :- 
   actual_diff_minus@_edge(x,y,@iteration_0,@current_count_0),
   @current_count_0 < 0.

   .plan (0,1):(1)
in file /home/david/docs/souffle-fault-localization/tests/path/path.dl [6:1-6:26])_");
if(!(rel_4_actual_diff_minus_edge->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_4_actual_diff_minus_edge_op_ctxt,rel_4_actual_diff_minus_edge->createContext());
CREATE_OP_CONTEXT(rel_7_diff_minus_path_op_ctxt,rel_7_diff_minus_path->createContext());
for(const auto& env0 : *rel_4_actual_diff_minus_edge) {
if( ((env0[3]) < (RamDomain(0)))) {
Tuple<RamDomain,4> tuple{{static_cast<RamDomain>(env0[0]),static_cast<RamDomain>(env0[1]),static_cast<RamDomain>(RamDomain(0)),static_cast<RamDomain>(RamDomain(-1))}};
rel_7_diff_minus_path->insert(tuple,READ_OP_CONTEXT(rel_7_diff_minus_path_op_ctxt));
}
}
}
();}
SignalHandler::instance()->setMsg(R"_(diff_plus@_path(x,y,0,1) :- 
   actual_diff_plus@_edge(x,y,@iteration_0,@current_count_0),
   @current_count_0 > 0,
   @current_count_0 > 0.

   .plan (0,1):(1)
in file /home/david/docs/souffle-fault-localization/tests/path/path.dl [6:1-6:26])_");
if(!(rel_3_actual_diff_plus_edge->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_3_actual_diff_plus_edge_op_ctxt,rel_3_actual_diff_plus_edge->createContext());
CREATE_OP_CONTEXT(rel_8_diff_plus_path_op_ctxt,rel_8_diff_plus_path->createContext());
for(const auto& env0 : *rel_3_actual_diff_plus_edge) {
if( ((env0[3]) > (RamDomain(0)))) {
Tuple<RamDomain,4> tuple{{static_cast<RamDomain>(env0[0]),static_cast<RamDomain>(env0[1]),static_cast<RamDomain>(RamDomain(0)),static_cast<RamDomain>(RamDomain(1))}};
rel_8_diff_plus_path->insert(tuple,READ_OP_CONTEXT(rel_8_diff_plus_path_op_ctxt));
}
}
}
();}
rel_11_diff_applied_path->insertAll(*rel_7_diff_minus_path);
{
CREATE_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt,rel_11_diff_applied_path->createContext());
for (const auto& tup : *rel_8_diff_plus_path) {
auto existenceCheck = rel_11_diff_applied_path->equalRange_3(Tuple<RamDomain,4>{{tup[0],tup[1],0,0}}, READ_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt));
for (const auto& existingTup : existenceCheck) {
if (existingTup[2] > tup[2]) {
auto updateTuple = existingTup;
updateTuple[3] = 0;
rel_11_diff_applied_path->insert(updateTuple,READ_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt));
}
}
rel_11_diff_applied_path->insert(tup,READ_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt));
}
}
{
CREATE_OP_CONTEXT(rel_12_path_op_ctxt,rel_12_path->createContext());
CREATE_OP_CONTEXT(rel_9_actual_diff_plus_path_op_ctxt,rel_9_actual_diff_plus_path->createContext());
CREATE_OP_CONTEXT(rel_8_diff_plus_path_op_ctxt,rel_8_diff_plus_path->createContext());
auto deltaSource = rel_8_diff_plus_path->equalRange_4(Tuple<RamDomain,4>{{0,0,iter,0}}, READ_OP_CONTEXT(rel_8_diff_plus_path_op_ctxt));
for (const auto& tup : deltaSource) {
auto restrictionExistenceCheck = rel_12_path->equalRange_3(Tuple<RamDomain,4>{{tup[0],tup[1],0,0}}, READ_OP_CONTEXT(rel_12_path_op_ctxt));
bool insert = true;
for (const auto& t : restrictionExistenceCheck) {
if (t[2] <= tup[2] && t[3] > 0) {
insert = false;
break;
}
}
if (insert) {
auto tuple = tup;
tuple[3] = tup[3] < 0 ? -1 : 1;
rel_9_actual_diff_plus_path->insert(tuple, READ_OP_CONTEXT(rel_9_actual_diff_plus_path_op_ctxt));
}
}
if (iter > 0) {
if (rel_9_actual_diff_plus_path->approx_size() < rel_12_path->approx_size(iter)) {
for (const auto& tup : *rel_9_actual_diff_plus_path) {
if (tup[2] == iter || tup[3] == 0) continue;
auto deltaExistenceCheck = rel_12_path->equalRange_7(Tuple<RamDomain,4>{{tup[0],tup[1],iter,0}}, READ_OP_CONTEXT(rel_12_path_op_ctxt));
if (deltaExistenceCheck.empty()) continue;
if ((*deltaExistenceCheck.begin())[3] > 0) {
auto tuple = tup;
tuple[3] = tup[3] == -1 ? 1 : -1;
rel_9_actual_diff_plus_path->insert(tuple, READ_OP_CONTEXT(rel_9_actual_diff_plus_path_op_ctxt));
}
}
} else {
auto deltaRestriction = rel_12_path->equalRange_4(Tuple<RamDomain,4>{{0,0,iter,0}}, READ_OP_CONTEXT(rel_12_path_op_ctxt));
for (const auto& tup : deltaRestriction) {
if (tup[3] <= 0) {
continue;
}
auto existenceCheck = rel_9_actual_diff_plus_path->equalRange_3(Tuple<RamDomain,4>{{tup[0],tup[1],0,0}}, READ_OP_CONTEXT(rel_9_actual_diff_plus_path_op_ctxt));
for (const auto& t : existenceCheck) {
if (t[2] == iter || t[3] == 0) continue;
auto tuple = t;
tuple[3] = t[3] == -1 ? 1 : -1;
rel_9_actual_diff_plus_path->insert(tuple, READ_OP_CONTEXT(rel_9_actual_diff_plus_path_op_ctxt));
}
}
}
}
}
{
CREATE_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt,rel_11_diff_applied_path->createContext());
CREATE_OP_CONTEXT(rel_10_actual_diff_minus_path_op_ctxt,rel_10_actual_diff_minus_path->createContext());
CREATE_OP_CONTEXT(rel_7_diff_minus_path_op_ctxt,rel_7_diff_minus_path->createContext());
auto deltaSource = rel_7_diff_minus_path->equalRange_4(Tuple<RamDomain,4>{{0,0,iter,0}}, READ_OP_CONTEXT(rel_7_diff_minus_path_op_ctxt));
for (const auto& tup : deltaSource) {
auto restrictionExistenceCheck = rel_11_diff_applied_path->equalRange_3(Tuple<RamDomain,4>{{tup[0],tup[1],0,0}}, READ_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt));
bool insert = true;
for (const auto& t : restrictionExistenceCheck) {
if (t[2] <= tup[2] && t[3] > 0) {
insert = false;
break;
}
}
if (insert) {
auto tuple = tup;
tuple[3] = tup[3] < 0 ? -1 : 1;
rel_10_actual_diff_minus_path->insert(tuple, READ_OP_CONTEXT(rel_10_actual_diff_minus_path_op_ctxt));
}
}
if (iter > 0) {
if (rel_10_actual_diff_minus_path->approx_size() < rel_11_diff_applied_path->approx_size(iter)) {
for (const auto& tup : *rel_10_actual_diff_minus_path) {
if (tup[2] == iter || tup[3] == 0) continue;
auto deltaExistenceCheck = rel_11_diff_applied_path->equalRange_7(Tuple<RamDomain,4>{{tup[0],tup[1],iter,0}}, READ_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt));
if (deltaExistenceCheck.empty()) continue;
if ((*deltaExistenceCheck.begin())[3] > 0) {
auto tuple = tup;
tuple[3] = tup[3] == -1 ? 1 : -1;
rel_10_actual_diff_minus_path->insert(tuple, READ_OP_CONTEXT(rel_10_actual_diff_minus_path_op_ctxt));
}
}
} else {
auto deltaRestriction = rel_11_diff_applied_path->equalRange_4(Tuple<RamDomain,4>{{0,0,iter,0}}, READ_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt));
for (const auto& tup : deltaRestriction) {
if (tup[3] <= 0) {
continue;
}
auto existenceCheck = rel_10_actual_diff_minus_path->equalRange_3(Tuple<RamDomain,4>{{tup[0],tup[1],0,0}}, READ_OP_CONTEXT(rel_10_actual_diff_minus_path_op_ctxt));
for (const auto& t : existenceCheck) {
if (t[2] == iter || t[3] == 0) continue;
auto tuple = t;
tuple[3] = t[3] == -1 ? 1 : -1;
rel_10_actual_diff_minus_path->insert(tuple, READ_OP_CONTEXT(rel_10_actual_diff_minus_path_op_ctxt));
}
}
}
}
}
[&](){
CREATE_OP_CONTEXT(rel_12_path_op_ctxt,rel_12_path->createContext());
CREATE_OP_CONTEXT(rel_19_scc_1_max_iter_op_ctxt,rel_19_scc_1_max_iter->createContext());
ram::Tuple<RamDomain,1> env0;
RamDomain res0 = MIN_RAM_DOMAIN;
for(const auto& env0 : *rel_12_path) {
if( true) {
res0 = std::max(res0,env0[2]);
}
}
env0[0] = res0;
Tuple<RamDomain,1> tuple{{static_cast<RamDomain>(std::max({env0[0], }))}};
rel_19_scc_1_max_iter->insert(tuple,READ_OP_CONTEXT(rel_19_scc_1_max_iter_op_ctxt));
}
();if(!(rel_10_actual_diff_minus_path->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_10_actual_diff_minus_path_op_ctxt,rel_10_actual_diff_minus_path->createContext());
CREATE_OP_CONTEXT(rel_44_path_restricted_1_op_ctxt,rel_44_path_restricted_1->createContext());
for(const auto& env0 : *rel_10_actual_diff_minus_path) {
Tuple<RamDomain,1> tuple{{static_cast<RamDomain>(env0[1])}};
rel_44_path_restricted_1->insert(tuple,READ_OP_CONTEXT(rel_44_path_restricted_1_op_ctxt));
}
}
();}
if(!(rel_10_actual_diff_minus_path->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_10_actual_diff_minus_path_op_ctxt,rel_10_actual_diff_minus_path->createContext());
CREATE_OP_CONTEXT(rel_45_path_restricted_0_op_ctxt,rel_45_path_restricted_0->createContext());
for(const auto& env0 : *rel_10_actual_diff_minus_path) {
Tuple<RamDomain,1> tuple{{static_cast<RamDomain>(env0[0])}};
rel_45_path_restricted_0->insert(tuple,READ_OP_CONTEXT(rel_45_path_restricted_0_op_ctxt));
}
}
();}
iter = 1;
for(;;) {
SignalHandler::instance()->setMsg(R"_(@new_diff_minus@_path(x,y,iternum(),-1) :- 
   actual_diff_minus@_edge(x,z,@iteration_0,@current_count_0),
   path(z,y,@iteration_1,@current_count_1),
   subsump!diff_applied@_path(x,y,iternum(),-1),
   @current_count_0 < 0,
   @current_count_1 > 0,
   @iteration_1 = (iternum()-1).

   .plan (0,1):(1,2)
in file /home/david/docs/souffle-fault-localization/tests/path/path.dl [7:1-7:38])_");
if(!(rel_4_actual_diff_minus_edge->empty()) && !(rel_12_path->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_4_actual_diff_minus_edge_op_ctxt,rel_4_actual_diff_minus_edge->createContext());
CREATE_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt,rel_11_diff_applied_path->createContext());
CREATE_OP_CONTEXT(rel_12_path_op_ctxt,rel_12_path->createContext());
CREATE_OP_CONTEXT(rel_16_new_diff_minus_path_op_ctxt,rel_16_new_diff_minus_path->createContext());
for(const auto& env0 : *rel_4_actual_diff_minus_edge) {
if( ((env0[3]) < (RamDomain(0)))) {
const Tuple<RamDomain,4> key{{env0[1],0,((iter)) - (RamDomain(1)),0}};
auto range = rel_12_path->equalRange_5(key,READ_OP_CONTEXT(rel_12_path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) > (RamDomain(0))) && !([&]() -> bool {
auto existenceCheck = rel_11_diff_applied_path->equalRange_3(Tuple<RamDomain,4>{{env0[0],env1[1],0,0}}, READ_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt));
if (RamDomain(-1) <= 0) {
if (existenceCheck.empty()) return true;
for (auto& tup : existenceCheck) {
if (tup[2] == (iter) && tup[3] > 0) return false;
}
return true;
} else {
if (existenceCheck.empty()) return false;
for (auto& tup : existenceCheck) {
if (tup[2] < (iter) && tup[3] > 0) return true;
}
if (RamDomain(-1) == 2) {
for (auto& tup : existenceCheck) {
if (tup[2] == (iter) && tup[3] > 0) return true;
}
return false;
}
return false;
}
;}()
)) {
Tuple<RamDomain,4> tuple{{static_cast<RamDomain>(env0[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>((iter)),static_cast<RamDomain>(RamDomain(-1))}};
rel_16_new_diff_minus_path->insert(tuple,READ_OP_CONTEXT(rel_16_new_diff_minus_path_op_ctxt));
}
}
}
}
}
();}
SignalHandler::instance()->setMsg(R"_(@new_diff_minus@_path(x,y,iternum(),-1) :- 
   edge(x,z,@iteration_0,@current_count_0),
   actual_diff_minus@_path(z,y,@iteration_1,@current_count_1),
   subsump!diff_applied@_path(x,y,iternum(),-1),
   @current_count_1 < 0,
   pos!diff_minus@_edge(x,z,@iteration_0,-1) || exists diff_applied@_edge(x,z,@iteration_0,1),
   @current_count_0 > 0,
   @iteration_1 = (iternum()-1).

   .plan (0,2):(2,1)
in file /home/david/docs/souffle-fault-localization/tests/path/path.dl [7:1-7:38])_");
if(!(rel_10_actual_diff_minus_path->empty()) && !(rel_6_edge->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_1_diff_minus_edge_op_ctxt,rel_1_diff_minus_edge->createContext());
CREATE_OP_CONTEXT(rel_5_diff_applied_edge_op_ctxt,rel_5_diff_applied_edge->createContext());
CREATE_OP_CONTEXT(rel_6_edge_op_ctxt,rel_6_edge->createContext());
CREATE_OP_CONTEXT(rel_10_actual_diff_minus_path_op_ctxt,rel_10_actual_diff_minus_path->createContext());
CREATE_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt,rel_11_diff_applied_path->createContext());
CREATE_OP_CONTEXT(rel_16_new_diff_minus_path_op_ctxt,rel_16_new_diff_minus_path->createContext());
const Tuple<RamDomain,4> key{{0,0,((iter)) - (RamDomain(1)),0}};
auto range = rel_10_actual_diff_minus_path->equalRange_4(key,READ_OP_CONTEXT(rel_10_actual_diff_minus_path_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[3]) < (RamDomain(0)))) {
const Tuple<RamDomain,4> key{{0,env0[0],0,0}};
auto range = rel_6_edge->equalRange_2(key,READ_OP_CONTEXT(rel_6_edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) > (RamDomain(0))) && !([&]() -> bool {
auto existenceCheck = rel_11_diff_applied_path->equalRange_3(Tuple<RamDomain,4>{{env1[0],env0[1],0,0}}, READ_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt));
if (RamDomain(-1) <= 0) {
if (existenceCheck.empty()) return true;
for (auto& tup : existenceCheck) {
if (tup[2] == (iter) && tup[3] > 0) return false;
}
return true;
} else {
if (existenceCheck.empty()) return false;
for (auto& tup : existenceCheck) {
if (tup[2] < (iter) && tup[3] > 0) return true;
}
if (RamDomain(-1) == 2) {
for (auto& tup : existenceCheck) {
if (tup[2] == (iter) && tup[3] > 0) return true;
}
return false;
}
return false;
}
;}()
) && ((!([&]() -> bool {
auto existenceCheck = rel_1_diff_minus_edge->equalRange_3(Tuple<RamDomain,4>{{env1[0],env0[0],0,0}},READ_OP_CONTEXT(rel_1_diff_minus_edge_op_ctxt));
for (const auto& tup : existenceCheck) {
if (RamDomain(-1) == 1) {
if (tup[3] > 0) {
if (env1[2] == -1 || (env1[2] <= (iter-1) && tup[2] <= (iter - 1))) return true;
}
}
else if (RamDomain(-1) == 0) {
if (tup[3] > 0 && (env1[2] == -1 || iter == 0 || tup[2] <= (iter-1))) {
return true;
}
}
else if (RamDomain(-1) == -1) {
if (tup[3] <= 0) {
return true;
}
}
}
return false;
}()
)) || ([&]() -> bool {
auto existenceCheck = rel_5_diff_applied_edge->equalRange_3(Tuple<RamDomain,4>{{env1[0],env0[0],0,0}},READ_OP_CONTEXT(rel_5_diff_applied_edge_op_ctxt));
for (const auto& tup : existenceCheck) {
if (RamDomain(1) == 1) {
if (tup[3] > 0) {
if (env1[2] == -1 || (env1[2] <= (iter-1) && tup[2] <= (iter - 1))) return true;
}
}
else if (RamDomain(1) == 0) {
if (tup[3] > 0 && (env1[2] == -1 || iter == 0 || tup[2] <= (iter-1))) {
return true;
}
}
else if (RamDomain(1) == -1) {
if (tup[3] <= 0) {
return true;
}
}
}
return false;
}()
))) {
Tuple<RamDomain,4> tuple{{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env0[1]),static_cast<RamDomain>((iter)),static_cast<RamDomain>(RamDomain(-1))}};
rel_16_new_diff_minus_path->insert(tuple,READ_OP_CONTEXT(rel_16_new_diff_minus_path_op_ctxt));
}
}
}
}
}
();}
SignalHandler::instance()->setMsg(R"_(@new_diff_plus@_path(x,y,iternum(),1) :- 
   actual_diff_plus@_edge(x,z,@iteration_0,@current_count_0),
   diff_applied@_path(z,y,@iteration_1,@current_count_1),
   subsump!diff_applied@_path(x,y,iternum(),1),
   @current_count_0 > 0,
   @current_count_0 > 0,
   @current_count_1 > 0,
   @iteration_1 = (iternum()-1).

   .plan (0,1):(1,2)
in file /home/david/docs/souffle-fault-localization/tests/path/path.dl [7:1-7:38])_");
if(!(rel_3_actual_diff_plus_edge->empty()) && !(rel_11_diff_applied_path->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_3_actual_diff_plus_edge_op_ctxt,rel_3_actual_diff_plus_edge->createContext());
CREATE_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt,rel_11_diff_applied_path->createContext());
CREATE_OP_CONTEXT(rel_15_new_diff_plus_path_op_ctxt,rel_15_new_diff_plus_path->createContext());
for(const auto& env0 : *rel_3_actual_diff_plus_edge) {
if( ((env0[3]) > (RamDomain(0)))) {
const Tuple<RamDomain,4> key{{env0[1],0,((iter)) - (RamDomain(1)),0}};
auto range = rel_11_diff_applied_path->equalRange_5(key,READ_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) > (RamDomain(0))) && !([&]() -> bool {
auto existenceCheck = rel_11_diff_applied_path->equalRange_3(Tuple<RamDomain,4>{{env0[0],env1[1],0,0}}, READ_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt));
if (RamDomain(1) <= 0) {
if (existenceCheck.empty()) return true;
for (auto& tup : existenceCheck) {
if (tup[2] == (iter) && tup[3] > 0) return false;
}
return true;
} else {
if (existenceCheck.empty()) return false;
for (auto& tup : existenceCheck) {
if (tup[2] < (iter) && tup[3] > 0) return true;
}
if (RamDomain(1) == 2) {
for (auto& tup : existenceCheck) {
if (tup[2] == (iter) && tup[3] > 0) return true;
}
return false;
}
return false;
}
;}()
)) {
Tuple<RamDomain,4> tuple{{static_cast<RamDomain>(env0[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>((iter)),static_cast<RamDomain>(RamDomain(1))}};
rel_15_new_diff_plus_path->insert(tuple,READ_OP_CONTEXT(rel_15_new_diff_plus_path_op_ctxt));
}
}
}
}
}
();}
SignalHandler::instance()->setMsg(R"_(@new_diff_plus@_path(x,y,iternum(),1) :- 
   diff_applied@_edge(x,z,@iteration_0,@current_count_0),
   actual_diff_plus@_path(z,y,@iteration_1,@current_count_1),
   subsump!diff_applied@_path(x,y,iternum(),1),
   @current_count_1 > 0,
   pos!diff_plus@_edge(x,z,@iteration_0,0) || exists edge(x,z,@iteration_0,1),
   @current_count_0 > 0,
   @current_count_1 > 0,
   @iteration_1 = (iternum()-1).

   .plan (0,2):(2,1)
in file /home/david/docs/souffle-fault-localization/tests/path/path.dl [7:1-7:38])_");
if(!(rel_9_actual_diff_plus_path->empty()) && !(rel_5_diff_applied_edge->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_2_diff_plus_edge_op_ctxt,rel_2_diff_plus_edge->createContext());
CREATE_OP_CONTEXT(rel_5_diff_applied_edge_op_ctxt,rel_5_diff_applied_edge->createContext());
CREATE_OP_CONTEXT(rel_6_edge_op_ctxt,rel_6_edge->createContext());
CREATE_OP_CONTEXT(rel_9_actual_diff_plus_path_op_ctxt,rel_9_actual_diff_plus_path->createContext());
CREATE_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt,rel_11_diff_applied_path->createContext());
CREATE_OP_CONTEXT(rel_15_new_diff_plus_path_op_ctxt,rel_15_new_diff_plus_path->createContext());
const Tuple<RamDomain,4> key{{0,0,((iter)) - (RamDomain(1)),0}};
auto range = rel_9_actual_diff_plus_path->equalRange_4(key,READ_OP_CONTEXT(rel_9_actual_diff_plus_path_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[3]) > (RamDomain(0)))) {
const Tuple<RamDomain,4> key{{0,env0[0],0,0}};
auto range = rel_5_diff_applied_edge->equalRange_2(key,READ_OP_CONTEXT(rel_5_diff_applied_edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) > (RamDomain(0))) && !([&]() -> bool {
auto existenceCheck = rel_11_diff_applied_path->equalRange_3(Tuple<RamDomain,4>{{env1[0],env0[1],0,0}}, READ_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt));
if (RamDomain(1) <= 0) {
if (existenceCheck.empty()) return true;
for (auto& tup : existenceCheck) {
if (tup[2] == (iter) && tup[3] > 0) return false;
}
return true;
} else {
if (existenceCheck.empty()) return false;
for (auto& tup : existenceCheck) {
if (tup[2] < (iter) && tup[3] > 0) return true;
}
if (RamDomain(1) == 2) {
for (auto& tup : existenceCheck) {
if (tup[2] == (iter) && tup[3] > 0) return true;
}
return false;
}
return false;
}
;}()
) && ((!([&]() -> bool {
auto existenceCheck = rel_2_diff_plus_edge->equalRange_3(Tuple<RamDomain,4>{{env1[0],env0[0],0,0}},READ_OP_CONTEXT(rel_2_diff_plus_edge_op_ctxt));
for (const auto& tup : existenceCheck) {
if (RamDomain(0) == 1) {
if (tup[3] > 0) {
if (env1[2] == -1 || (env1[2] <= (iter-1) && tup[2] <= (iter - 1))) return true;
}
}
else if (RamDomain(0) == 0) {
if (tup[3] > 0 && (env1[2] == -1 || iter == 0 || tup[2] <= (iter-1))) {
return true;
}
}
else if (RamDomain(0) == -1) {
if (tup[3] <= 0) {
return true;
}
}
}
return false;
}()
)) || ([&]() -> bool {
auto existenceCheck = rel_6_edge->equalRange_3(Tuple<RamDomain,4>{{env1[0],env0[0],0,0}},READ_OP_CONTEXT(rel_6_edge_op_ctxt));
for (const auto& tup : existenceCheck) {
if (RamDomain(1) == 1) {
if (tup[3] > 0) {
if (env1[2] == -1 || (env1[2] <= (iter-1) && tup[2] <= (iter - 1))) return true;
}
}
else if (RamDomain(1) == 0) {
if (tup[3] > 0 && (env1[2] == -1 || iter == 0 || tup[2] <= (iter-1))) {
return true;
}
}
else if (RamDomain(1) == -1) {
if (tup[3] <= 0) {
return true;
}
}
}
return false;
}()
))) {
Tuple<RamDomain,4> tuple{{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env0[1]),static_cast<RamDomain>((iter)),static_cast<RamDomain>(RamDomain(1))}};
rel_15_new_diff_plus_path->insert(tuple,READ_OP_CONTEXT(rel_15_new_diff_plus_path_op_ctxt));
}
}
}
}
}
();}
SignalHandler::instance()->setMsg(R"_(@new_diff_plus@_path(x,y,iternum(),1) :- 
   diff_applied@_edge(x,z,@iteration_0,@current_count_0),
   diff_applied@_path(z,y,@iteration_1,@current_count_1),
   path_@restricted_1(y),
   path_@restricted_0(x),
   subsump!diff_applied@_path(x,y,iternum(),2),
   min(@current_count_0,@current_count_1) > 0,
   exists edge(x,z,@iteration_0,0),
   exists path(z,y,@iteration_1,0),
   @iteration_1 = (iternum()-1).

   .plan (0,3):(3,2,1,4)
in file /home/david/docs/souffle-fault-localization/tests/path/path.dl [7:1-7:38])_");
if(!(rel_45_path_restricted_0->empty()) && !(rel_5_diff_applied_edge->empty()) && !(rel_44_path_restricted_1->empty()) && !(rel_11_diff_applied_path->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_5_diff_applied_edge_op_ctxt,rel_5_diff_applied_edge->createContext());
CREATE_OP_CONTEXT(rel_6_edge_op_ctxt,rel_6_edge->createContext());
CREATE_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt,rel_11_diff_applied_path->createContext());
CREATE_OP_CONTEXT(rel_12_path_op_ctxt,rel_12_path->createContext());
CREATE_OP_CONTEXT(rel_15_new_diff_plus_path_op_ctxt,rel_15_new_diff_plus_path->createContext());
CREATE_OP_CONTEXT(rel_45_path_restricted_0_op_ctxt,rel_45_path_restricted_0->createContext());
CREATE_OP_CONTEXT(rel_44_path_restricted_1_op_ctxt,rel_44_path_restricted_1->createContext());
for(const auto& env0 : *rel_44_path_restricted_1) {
const Tuple<RamDomain,4> key{{0,env0[0],((iter)) - (RamDomain(1)),0}};
auto range = rel_11_diff_applied_path->equalRange_6(key,READ_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) > (RamDomain(0))) && [&]() -> bool {
auto existenceCheck = rel_12_path->equalRange_3(Tuple<RamDomain,4>{{env1[0],env0[0],0,0}},READ_OP_CONTEXT(rel_12_path_op_ctxt));
for (const auto& tup : existenceCheck) {
if (RamDomain(0) == 1) {
if (tup[3] > 0) {
if (env1[2] == -1 || (env1[2] <= (iter-1) && tup[2] <= (iter - 1))) return true;
}
}
else if (RamDomain(0) == 0) {
if (tup[3] > 0 && (env1[2] == -1 || iter == 0 || tup[2] <= (iter-1))) {
return true;
}
}
else if (RamDomain(0) == -1) {
if (tup[3] <= 0) {
return true;
}
}
}
return false;
}()
) {
const Tuple<RamDomain,4> key{{0,env1[0],0,0}};
auto range = rel_5_diff_applied_edge->equalRange_2(key,READ_OP_CONTEXT(rel_5_diff_applied_edge_op_ctxt));
for(const auto& env2 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_11_diff_applied_path->equalRange_3(Tuple<RamDomain,4>{{env2[0],env0[0],0,0}}, READ_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt));
if (RamDomain(2) <= 0) {
if (existenceCheck.empty()) return true;
for (auto& tup : existenceCheck) {
if (tup[2] == (iter) && tup[3] > 0) return false;
}
return true;
} else {
if (existenceCheck.empty()) return false;
for (auto& tup : existenceCheck) {
if (tup[2] < (iter) && tup[3] > 0) return true;
}
if (RamDomain(2) == 2) {
for (auto& tup : existenceCheck) {
if (tup[2] == (iter) && tup[3] > 0) return true;
}
return false;
}
return false;
}
;}()
) && [&]() -> bool {
auto existenceCheck = rel_6_edge->equalRange_3(Tuple<RamDomain,4>{{env2[0],env1[0],0,0}},READ_OP_CONTEXT(rel_6_edge_op_ctxt));
for (const auto& tup : existenceCheck) {
if (RamDomain(0) == 1) {
if (tup[3] > 0) {
if (env2[2] == -1 || (env2[2] <= (iter-1) && tup[2] <= (iter - 1))) return true;
}
}
else if (RamDomain(0) == 0) {
if (tup[3] > 0 && (env2[2] == -1 || iter == 0 || tup[2] <= (iter-1))) {
return true;
}
}
else if (RamDomain(0) == -1) {
if (tup[3] <= 0) {
return true;
}
}
}
return false;
}()
 && ((env2[3]) > (RamDomain(0)))) {
for(const auto& env3 : *rel_45_path_restricted_0) {
if( ((env2[0]) == (env3[0]))) {
Tuple<RamDomain,4> tuple{{static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env0[0]),static_cast<RamDomain>((iter)),static_cast<RamDomain>(RamDomain(1))}};
rel_15_new_diff_plus_path->insert(tuple,READ_OP_CONTEXT(rel_15_new_diff_plus_path_op_ctxt));
}
}
}
}
}
}
}
}
();}
if(rel_15_new_diff_plus_path->empty() && rel_16_new_diff_minus_path->empty() && [&]() -> bool {
std::vector<RamDomain> args;
std::vector<RamDomain> ret;
std::vector<bool> err;
args.push_back((iter));
executeSubroutine("scc_1_exit", args, ret, err);
if (ret.size() == 0) return false;
if (ret[0] == 0) return false; else return true;
}()
) break;
rel_7_diff_minus_path->insertAll(*rel_16_new_diff_minus_path);
rel_8_diff_plus_path->insertAll(*rel_15_new_diff_plus_path);
rel_11_diff_applied_path->insertAll(*rel_16_new_diff_minus_path);
{
CREATE_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt,rel_11_diff_applied_path->createContext());
for (const auto& tup : *rel_15_new_diff_plus_path) {
auto existenceCheck = rel_11_diff_applied_path->equalRange_3(Tuple<RamDomain,4>{{tup[0],tup[1],0,0}}, READ_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt));
for (const auto& existingTup : existenceCheck) {
if (existingTup[2] > tup[2]) {
auto updateTuple = existingTup;
updateTuple[3] = 0;
rel_11_diff_applied_path->insert(updateTuple,READ_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt));
}
}
rel_11_diff_applied_path->insert(tup,READ_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt));
}
}
{
CREATE_OP_CONTEXT(rel_12_path_op_ctxt,rel_12_path->createContext());
CREATE_OP_CONTEXT(rel_9_actual_diff_plus_path_op_ctxt,rel_9_actual_diff_plus_path->createContext());
CREATE_OP_CONTEXT(rel_8_diff_plus_path_op_ctxt,rel_8_diff_plus_path->createContext());
auto deltaSource = rel_8_diff_plus_path->equalRange_4(Tuple<RamDomain,4>{{0,0,iter,0}}, READ_OP_CONTEXT(rel_8_diff_plus_path_op_ctxt));
for (const auto& tup : deltaSource) {
auto restrictionExistenceCheck = rel_12_path->equalRange_3(Tuple<RamDomain,4>{{tup[0],tup[1],0,0}}, READ_OP_CONTEXT(rel_12_path_op_ctxt));
bool insert = true;
for (const auto& t : restrictionExistenceCheck) {
if (t[2] <= tup[2] && t[3] > 0) {
insert = false;
break;
}
}
if (insert) {
auto tuple = tup;
tuple[3] = tup[3] < 0 ? -1 : 1;
rel_9_actual_diff_plus_path->insert(tuple, READ_OP_CONTEXT(rel_9_actual_diff_plus_path_op_ctxt));
}
}
if (iter > 0) {
if (rel_9_actual_diff_plus_path->approx_size() < rel_12_path->approx_size(iter)) {
for (const auto& tup : *rel_9_actual_diff_plus_path) {
if (tup[2] == iter || tup[3] == 0) continue;
auto deltaExistenceCheck = rel_12_path->equalRange_7(Tuple<RamDomain,4>{{tup[0],tup[1],iter,0}}, READ_OP_CONTEXT(rel_12_path_op_ctxt));
if (deltaExistenceCheck.empty()) continue;
if ((*deltaExistenceCheck.begin())[3] > 0) {
auto tuple = tup;
tuple[3] = tup[3] == -1 ? 1 : -1;
rel_9_actual_diff_plus_path->insert(tuple, READ_OP_CONTEXT(rel_9_actual_diff_plus_path_op_ctxt));
}
}
} else {
auto deltaRestriction = rel_12_path->equalRange_4(Tuple<RamDomain,4>{{0,0,iter,0}}, READ_OP_CONTEXT(rel_12_path_op_ctxt));
for (const auto& tup : deltaRestriction) {
if (tup[3] <= 0) {
continue;
}
auto existenceCheck = rel_9_actual_diff_plus_path->equalRange_3(Tuple<RamDomain,4>{{tup[0],tup[1],0,0}}, READ_OP_CONTEXT(rel_9_actual_diff_plus_path_op_ctxt));
for (const auto& t : existenceCheck) {
if (t[2] == iter || t[3] == 0) continue;
auto tuple = t;
tuple[3] = t[3] == -1 ? 1 : -1;
rel_9_actual_diff_plus_path->insert(tuple, READ_OP_CONTEXT(rel_9_actual_diff_plus_path_op_ctxt));
}
}
}
}
}
{
CREATE_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt,rel_11_diff_applied_path->createContext());
CREATE_OP_CONTEXT(rel_10_actual_diff_minus_path_op_ctxt,rel_10_actual_diff_minus_path->createContext());
CREATE_OP_CONTEXT(rel_7_diff_minus_path_op_ctxt,rel_7_diff_minus_path->createContext());
auto deltaSource = rel_7_diff_minus_path->equalRange_4(Tuple<RamDomain,4>{{0,0,iter,0}}, READ_OP_CONTEXT(rel_7_diff_minus_path_op_ctxt));
for (const auto& tup : deltaSource) {
auto restrictionExistenceCheck = rel_11_diff_applied_path->equalRange_3(Tuple<RamDomain,4>{{tup[0],tup[1],0,0}}, READ_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt));
bool insert = true;
for (const auto& t : restrictionExistenceCheck) {
if (t[2] <= tup[2] && t[3] > 0) {
insert = false;
break;
}
}
if (insert) {
auto tuple = tup;
tuple[3] = tup[3] < 0 ? -1 : 1;
rel_10_actual_diff_minus_path->insert(tuple, READ_OP_CONTEXT(rel_10_actual_diff_minus_path_op_ctxt));
}
}
if (iter > 0) {
if (rel_10_actual_diff_minus_path->approx_size() < rel_11_diff_applied_path->approx_size(iter)) {
for (const auto& tup : *rel_10_actual_diff_minus_path) {
if (tup[2] == iter || tup[3] == 0) continue;
auto deltaExistenceCheck = rel_11_diff_applied_path->equalRange_7(Tuple<RamDomain,4>{{tup[0],tup[1],iter,0}}, READ_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt));
if (deltaExistenceCheck.empty()) continue;
if ((*deltaExistenceCheck.begin())[3] > 0) {
auto tuple = tup;
tuple[3] = tup[3] == -1 ? 1 : -1;
rel_10_actual_diff_minus_path->insert(tuple, READ_OP_CONTEXT(rel_10_actual_diff_minus_path_op_ctxt));
}
}
} else {
auto deltaRestriction = rel_11_diff_applied_path->equalRange_4(Tuple<RamDomain,4>{{0,0,iter,0}}, READ_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt));
for (const auto& tup : deltaRestriction) {
if (tup[3] <= 0) {
continue;
}
auto existenceCheck = rel_10_actual_diff_minus_path->equalRange_3(Tuple<RamDomain,4>{{tup[0],tup[1],0,0}}, READ_OP_CONTEXT(rel_10_actual_diff_minus_path_op_ctxt));
for (const auto& t : existenceCheck) {
if (t[2] == iter || t[3] == 0) continue;
auto tuple = t;
tuple[3] = t[3] == -1 ? 1 : -1;
rel_10_actual_diff_minus_path->insert(tuple, READ_OP_CONTEXT(rel_10_actual_diff_minus_path_op_ctxt));
}
}
}
}
}
if(!(rel_10_actual_diff_minus_path->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_10_actual_diff_minus_path_op_ctxt,rel_10_actual_diff_minus_path->createContext());
CREATE_OP_CONTEXT(rel_44_path_restricted_1_op_ctxt,rel_44_path_restricted_1->createContext());
const Tuple<RamDomain,4> key{{0,0,(iter),0}};
auto range = rel_10_actual_diff_minus_path->equalRange_4(key,READ_OP_CONTEXT(rel_10_actual_diff_minus_path_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[3]) == (RamDomain(-1)))) {
Tuple<RamDomain,1> tuple{{static_cast<RamDomain>(env0[1])}};
rel_44_path_restricted_1->insert(tuple,READ_OP_CONTEXT(rel_44_path_restricted_1_op_ctxt));
}
}
}
();}
if(!(rel_10_actual_diff_minus_path->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_10_actual_diff_minus_path_op_ctxt,rel_10_actual_diff_minus_path->createContext());
CREATE_OP_CONTEXT(rel_45_path_restricted_0_op_ctxt,rel_45_path_restricted_0->createContext());
const Tuple<RamDomain,4> key{{0,0,(iter),0}};
auto range = rel_10_actual_diff_minus_path->equalRange_4(key,READ_OP_CONTEXT(rel_10_actual_diff_minus_path_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[3]) == (RamDomain(-1)))) {
Tuple<RamDomain,1> tuple{{static_cast<RamDomain>(env0[0])}};
rel_45_path_restricted_0->insert(tuple,READ_OP_CONTEXT(rel_45_path_restricted_0_op_ctxt));
}
}
}
();}
rel_16_new_diff_minus_path->purge();
rel_15_new_diff_plus_path->purge();
iter++;
}
iter = 0;
if (!isHintsProfilingEnabled()) rel_15_new_diff_plus_path->purge();
if (!isHintsProfilingEnabled()) rel_16_new_diff_minus_path->purge();
if (!isHintsProfilingEnabled()&& performIO) rel_44_path_restricted_1->purge();
if (!isHintsProfilingEnabled()&& performIO) rel_45_path_restricted_0->purge();
}();
/* END STRATUM 1 */
/* BEGIN STRATUM 2 */
[&]() {
SignalHandler::instance()->setMsg(R"_(diff_minus@_path2(x,y,0,-1) :- 
   actual_diff_minus@_path(x,y,@iteration_0,@current_count_0),
   pos!edge(x,y,-1,0),
   @current_count_0 < 0.

   .plan (0,1):(1)
in file /home/david/docs/souffle-fault-localization/tests/path/path.dl [9:1-9:40])_");
if(!(rel_10_actual_diff_minus_path->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_6_edge_op_ctxt,rel_6_edge->createContext());
CREATE_OP_CONTEXT(rel_10_actual_diff_minus_path_op_ctxt,rel_10_actual_diff_minus_path->createContext());
CREATE_OP_CONTEXT(rel_20_diff_minus_path2_op_ctxt,rel_20_diff_minus_path2->createContext());
for(const auto& env0 : *rel_10_actual_diff_minus_path) {
if( ((env0[3]) < (RamDomain(0))) && !([&]() -> bool {
auto existenceCheck = rel_6_edge->equalRange_3(Tuple<RamDomain,4>{{env0[0],env0[1],0,0}},READ_OP_CONTEXT(rel_6_edge_op_ctxt));
for (const auto& tup : existenceCheck) {
if (RamDomain(0) == 1) {
if (tup[3] > 0) {
if (RamDomain(-1) == -1 || (RamDomain(-1) <= (iter-1) && tup[2] <= (iter - 1))) return true;
}
}
else if (RamDomain(0) == 0) {
if (tup[3] > 0 && (RamDomain(-1) == -1 || iter == 0 || tup[2] <= (iter-1))) {
return true;
}
}
else if (RamDomain(0) == -1) {
if (tup[3] <= 0) {
return true;
}
}
}
return false;
}()
)) {
Tuple<RamDomain,4> tuple{{static_cast<RamDomain>(env0[0]),static_cast<RamDomain>(env0[1]),static_cast<RamDomain>(RamDomain(0)),static_cast<RamDomain>(RamDomain(-1))}};
rel_20_diff_minus_path2->insert(tuple,READ_OP_CONTEXT(rel_20_diff_minus_path2_op_ctxt));
}
}
}
();}
SignalHandler::instance()->setMsg(R"_(diff_minus@_path2(x,y,0,-1) :- 
   path(x,y,@iteration_0,@current_count_0),
   actual_diff_plus@_edge(x,y,_,@negation_count),
   pos!edge(x,y,-1,0),
   @negation_count > 0,
   pos!diff_minus@_path(x,y,@iteration_0,-1) || exists diff_applied@_path(x,y,@iteration_0,1),
   @current_count_0 > 0.

   .plan (0,1):(1,2)
in file /home/david/docs/souffle-fault-localization/tests/path/path.dl [9:1-9:40])_");
if(!(rel_12_path->empty()) && !(rel_3_actual_diff_plus_edge->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_3_actual_diff_plus_edge_op_ctxt,rel_3_actual_diff_plus_edge->createContext());
CREATE_OP_CONTEXT(rel_6_edge_op_ctxt,rel_6_edge->createContext());
CREATE_OP_CONTEXT(rel_7_diff_minus_path_op_ctxt,rel_7_diff_minus_path->createContext());
CREATE_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt,rel_11_diff_applied_path->createContext());
CREATE_OP_CONTEXT(rel_12_path_op_ctxt,rel_12_path->createContext());
CREATE_OP_CONTEXT(rel_20_diff_minus_path2_op_ctxt,rel_20_diff_minus_path2->createContext());
for(const auto& env0 : *rel_12_path) {
if( ((env0[3]) > (RamDomain(0))) && !([&]() -> bool {
auto existenceCheck = rel_6_edge->equalRange_3(Tuple<RamDomain,4>{{env0[0],env0[1],0,0}},READ_OP_CONTEXT(rel_6_edge_op_ctxt));
for (const auto& tup : existenceCheck) {
if (RamDomain(0) == 1) {
if (tup[3] > 0) {
if (RamDomain(-1) == -1 || (RamDomain(-1) <= (iter-1) && tup[2] <= (iter - 1))) return true;
}
}
else if (RamDomain(0) == 0) {
if (tup[3] > 0 && (RamDomain(-1) == -1 || iter == 0 || tup[2] <= (iter-1))) {
return true;
}
}
else if (RamDomain(0) == -1) {
if (tup[3] <= 0) {
return true;
}
}
}
return false;
}()
) && ((!([&]() -> bool {
auto existenceCheck = rel_7_diff_minus_path->equalRange_3(Tuple<RamDomain,4>{{env0[0],env0[1],0,0}},READ_OP_CONTEXT(rel_7_diff_minus_path_op_ctxt));
for (const auto& tup : existenceCheck) {
if (RamDomain(-1) == 1) {
if (tup[3] > 0) {
if (env0[2] == -1 || (env0[2] <= (iter-1) && tup[2] <= (iter - 1))) return true;
}
}
else if (RamDomain(-1) == 0) {
if (tup[3] > 0 && (env0[2] == -1 || iter == 0 || tup[2] <= (iter-1))) {
return true;
}
}
else if (RamDomain(-1) == -1) {
if (tup[3] <= 0) {
return true;
}
}
}
return false;
}()
)) || ([&]() -> bool {
auto existenceCheck = rel_11_diff_applied_path->equalRange_3(Tuple<RamDomain,4>{{env0[0],env0[1],0,0}},READ_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt));
for (const auto& tup : existenceCheck) {
if (RamDomain(1) == 1) {
if (tup[3] > 0) {
if (env0[2] == -1 || (env0[2] <= (iter-1) && tup[2] <= (iter - 1))) return true;
}
}
else if (RamDomain(1) == 0) {
if (tup[3] > 0 && (env0[2] == -1 || iter == 0 || tup[2] <= (iter-1))) {
return true;
}
}
else if (RamDomain(1) == -1) {
if (tup[3] <= 0) {
return true;
}
}
}
return false;
}()
))) {
const Tuple<RamDomain,4> key{{env0[0],env0[1],0,0}};
auto range = rel_3_actual_diff_plus_edge->equalRange_3(key,READ_OP_CONTEXT(rel_3_actual_diff_plus_edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) > (RamDomain(0)))) {
Tuple<RamDomain,4> tuple{{static_cast<RamDomain>(env0[0]),static_cast<RamDomain>(env0[1]),static_cast<RamDomain>(RamDomain(0)),static_cast<RamDomain>(RamDomain(-1))}};
rel_20_diff_minus_path2->insert(tuple,READ_OP_CONTEXT(rel_20_diff_minus_path2_op_ctxt));
}
}
}
}
}
();}
SignalHandler::instance()->setMsg(R"_(diff_plus@_path2(x,y,0,1) :- 
   actual_diff_plus@_path(x,y,@iteration_0,@current_count_0),
   pos!diff_applied@_edge(x,y,-1,0),
   @current_count_0 > 0,
   @current_count_0 > 0.

   .plan (0,1):(1)
in file /home/david/docs/souffle-fault-localization/tests/path/path.dl [9:1-9:40])_");
if(!(rel_9_actual_diff_plus_path->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_5_diff_applied_edge_op_ctxt,rel_5_diff_applied_edge->createContext());
CREATE_OP_CONTEXT(rel_9_actual_diff_plus_path_op_ctxt,rel_9_actual_diff_plus_path->createContext());
CREATE_OP_CONTEXT(rel_21_diff_plus_path2_op_ctxt,rel_21_diff_plus_path2->createContext());
for(const auto& env0 : *rel_9_actual_diff_plus_path) {
if( ((env0[3]) > (RamDomain(0))) && !([&]() -> bool {
auto existenceCheck = rel_5_diff_applied_edge->equalRange_3(Tuple<RamDomain,4>{{env0[0],env0[1],0,0}},READ_OP_CONTEXT(rel_5_diff_applied_edge_op_ctxt));
for (const auto& tup : existenceCheck) {
if (RamDomain(0) == 1) {
if (tup[3] > 0) {
if (RamDomain(-1) == -1 || (RamDomain(-1) <= (iter-1) && tup[2] <= (iter - 1))) return true;
}
}
else if (RamDomain(0) == 0) {
if (tup[3] > 0 && (RamDomain(-1) == -1 || iter == 0 || tup[2] <= (iter-1))) {
return true;
}
}
else if (RamDomain(0) == -1) {
if (tup[3] <= 0) {
return true;
}
}
}
return false;
}()
)) {
Tuple<RamDomain,4> tuple{{static_cast<RamDomain>(env0[0]),static_cast<RamDomain>(env0[1]),static_cast<RamDomain>(RamDomain(0)),static_cast<RamDomain>(RamDomain(1))}};
rel_21_diff_plus_path2->insert(tuple,READ_OP_CONTEXT(rel_21_diff_plus_path2_op_ctxt));
}
}
}
();}
SignalHandler::instance()->setMsg(R"_(diff_plus@_path2(x,y,0,1) :- 
   diff_applied@_path(x,y,@iteration_0,@current_count_0),
   actual_diff_minus@_edge(x,y,_,@negation_count),
   pos!diff_applied@_edge(x,y,-1,0),
   @negation_count < 0,
   pos!diff_plus@_path(x,y,@iteration_0,0) || exists path(x,y,@iteration_0,1),
   @current_count_0 > 0.

   .plan (0,1):(1,2)
in file /home/david/docs/souffle-fault-localization/tests/path/path.dl [9:1-9:40])_");
if(!(rel_11_diff_applied_path->empty()) && !(rel_4_actual_diff_minus_edge->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_4_actual_diff_minus_edge_op_ctxt,rel_4_actual_diff_minus_edge->createContext());
CREATE_OP_CONTEXT(rel_5_diff_applied_edge_op_ctxt,rel_5_diff_applied_edge->createContext());
CREATE_OP_CONTEXT(rel_8_diff_plus_path_op_ctxt,rel_8_diff_plus_path->createContext());
CREATE_OP_CONTEXT(rel_11_diff_applied_path_op_ctxt,rel_11_diff_applied_path->createContext());
CREATE_OP_CONTEXT(rel_12_path_op_ctxt,rel_12_path->createContext());
CREATE_OP_CONTEXT(rel_21_diff_plus_path2_op_ctxt,rel_21_diff_plus_path2->createContext());
for(const auto& env0 : *rel_11_diff_applied_path) {
if( ((env0[3]) > (RamDomain(0))) && !([&]() -> bool {
auto existenceCheck = rel_5_diff_applied_edge->equalRange_3(Tuple<RamDomain,4>{{env0[0],env0[1],0,0}},READ_OP_CONTEXT(rel_5_diff_applied_edge_op_ctxt));
for (const auto& tup : existenceCheck) {
if (RamDomain(0) == 1) {
if (tup[3] > 0) {
if (RamDomain(-1) == -1 || (RamDomain(-1) <= (iter-1) && tup[2] <= (iter - 1))) return true;
}
}
else if (RamDomain(0) == 0) {
if (tup[3] > 0 && (RamDomain(-1) == -1 || iter == 0 || tup[2] <= (iter-1))) {
return true;
}
}
else if (RamDomain(0) == -1) {
if (tup[3] <= 0) {
return true;
}
}
}
return false;
}()
) && ((!([&]() -> bool {
auto existenceCheck = rel_8_diff_plus_path->equalRange_3(Tuple<RamDomain,4>{{env0[0],env0[1],0,0}},READ_OP_CONTEXT(rel_8_diff_plus_path_op_ctxt));
for (const auto& tup : existenceCheck) {
if (RamDomain(0) == 1) {
if (tup[3] > 0) {
if (env0[2] == -1 || (env0[2] <= (iter-1) && tup[2] <= (iter - 1))) return true;
}
}
else if (RamDomain(0) == 0) {
if (tup[3] > 0 && (env0[2] == -1 || iter == 0 || tup[2] <= (iter-1))) {
return true;
}
}
else if (RamDomain(0) == -1) {
if (tup[3] <= 0) {
return true;
}
}
}
return false;
}()
)) || ([&]() -> bool {
auto existenceCheck = rel_12_path->equalRange_3(Tuple<RamDomain,4>{{env0[0],env0[1],0,0}},READ_OP_CONTEXT(rel_12_path_op_ctxt));
for (const auto& tup : existenceCheck) {
if (RamDomain(1) == 1) {
if (tup[3] > 0) {
if (env0[2] == -1 || (env0[2] <= (iter-1) && tup[2] <= (iter - 1))) return true;
}
}
else if (RamDomain(1) == 0) {
if (tup[3] > 0 && (env0[2] == -1 || iter == 0 || tup[2] <= (iter-1))) {
return true;
}
}
else if (RamDomain(1) == -1) {
if (tup[3] <= 0) {
return true;
}
}
}
return false;
}()
))) {
const Tuple<RamDomain,4> key{{env0[0],env0[1],0,0}};
auto range = rel_4_actual_diff_minus_edge->equalRange_3(key,READ_OP_CONTEXT(rel_4_actual_diff_minus_edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < (RamDomain(0)))) {
Tuple<RamDomain,4> tuple{{static_cast<RamDomain>(env0[0]),static_cast<RamDomain>(env0[1]),static_cast<RamDomain>(RamDomain(0)),static_cast<RamDomain>(RamDomain(1))}};
rel_21_diff_plus_path2->insert(tuple,READ_OP_CONTEXT(rel_21_diff_plus_path2_op_ctxt));
}
}
}
}
}
();}
rel_24_diff_applied_path2->insertAll(*rel_20_diff_minus_path2);
{
CREATE_OP_CONTEXT(rel_24_diff_applied_path2_op_ctxt,rel_24_diff_applied_path2->createContext());
for (const auto& tup : *rel_21_diff_plus_path2) {
auto existenceCheck = rel_24_diff_applied_path2->equalRange_3(Tuple<RamDomain,4>{{tup[0],tup[1],0,0}}, READ_OP_CONTEXT(rel_24_diff_applied_path2_op_ctxt));
for (const auto& existingTup : existenceCheck) {
if (existingTup[2] > tup[2]) {
auto updateTuple = existingTup;
updateTuple[3] = 0;
rel_24_diff_applied_path2->insert(updateTuple,READ_OP_CONTEXT(rel_24_diff_applied_path2_op_ctxt));
}
}
rel_24_diff_applied_path2->insert(tup,READ_OP_CONTEXT(rel_24_diff_applied_path2_op_ctxt));
}
}
{
CREATE_OP_CONTEXT(rel_24_diff_applied_path2_op_ctxt,rel_24_diff_applied_path2->createContext());
CREATE_OP_CONTEXT(rel_23_actual_diff_minus_path2_op_ctxt,rel_23_actual_diff_minus_path2->createContext());
CREATE_OP_CONTEXT(rel_20_diff_minus_path2_op_ctxt,rel_20_diff_minus_path2->createContext());
auto deltaSource = rel_20_diff_minus_path2->equalRange_4(Tuple<RamDomain,4>{{0,0,iter,0}}, READ_OP_CONTEXT(rel_20_diff_minus_path2_op_ctxt));
for (const auto& tup : deltaSource) {
auto restrictionExistenceCheck = rel_24_diff_applied_path2->equalRange_3(Tuple<RamDomain,4>{{tup[0],tup[1],0,0}}, READ_OP_CONTEXT(rel_24_diff_applied_path2_op_ctxt));
bool insert = true;
for (const auto& t : restrictionExistenceCheck) {
if (t[2] <= tup[2] && t[3] > 0) {
insert = false;
break;
}
}
if (insert) {
auto tuple = tup;
tuple[3] = tup[3] < 0 ? -1 : 1;
rel_23_actual_diff_minus_path2->insert(tuple, READ_OP_CONTEXT(rel_23_actual_diff_minus_path2_op_ctxt));
}
}
if (iter > 0) {
if (rel_23_actual_diff_minus_path2->approx_size() < rel_24_diff_applied_path2->approx_size(iter)) {
for (const auto& tup : *rel_23_actual_diff_minus_path2) {
if (tup[2] == iter || tup[3] == 0) continue;
auto deltaExistenceCheck = rel_24_diff_applied_path2->equalRange_7(Tuple<RamDomain,4>{{tup[0],tup[1],iter,0}}, READ_OP_CONTEXT(rel_24_diff_applied_path2_op_ctxt));
if (deltaExistenceCheck.empty()) continue;
if ((*deltaExistenceCheck.begin())[3] > 0) {
auto tuple = tup;
tuple[3] = tup[3] == -1 ? 1 : -1;
rel_23_actual_diff_minus_path2->insert(tuple, READ_OP_CONTEXT(rel_23_actual_diff_minus_path2_op_ctxt));
}
}
} else {
auto deltaRestriction = rel_24_diff_applied_path2->equalRange_4(Tuple<RamDomain,4>{{0,0,iter,0}}, READ_OP_CONTEXT(rel_24_diff_applied_path2_op_ctxt));
for (const auto& tup : deltaRestriction) {
if (tup[3] <= 0) {
continue;
}
auto existenceCheck = rel_23_actual_diff_minus_path2->equalRange_3(Tuple<RamDomain,4>{{tup[0],tup[1],0,0}}, READ_OP_CONTEXT(rel_23_actual_diff_minus_path2_op_ctxt));
for (const auto& t : existenceCheck) {
if (t[2] == iter || t[3] == 0) continue;
auto tuple = t;
tuple[3] = t[3] == -1 ? 1 : -1;
rel_23_actual_diff_minus_path2->insert(tuple, READ_OP_CONTEXT(rel_23_actual_diff_minus_path2_op_ctxt));
}
}
}
}
}
{
CREATE_OP_CONTEXT(rel_25_path2_op_ctxt,rel_25_path2->createContext());
CREATE_OP_CONTEXT(rel_22_actual_diff_plus_path2_op_ctxt,rel_22_actual_diff_plus_path2->createContext());
CREATE_OP_CONTEXT(rel_21_diff_plus_path2_op_ctxt,rel_21_diff_plus_path2->createContext());
auto deltaSource = rel_21_diff_plus_path2->equalRange_4(Tuple<RamDomain,4>{{0,0,iter,0}}, READ_OP_CONTEXT(rel_21_diff_plus_path2_op_ctxt));
for (const auto& tup : deltaSource) {
auto restrictionExistenceCheck = rel_25_path2->equalRange_3(Tuple<RamDomain,4>{{tup[0],tup[1],0,0}}, READ_OP_CONTEXT(rel_25_path2_op_ctxt));
bool insert = true;
for (const auto& t : restrictionExistenceCheck) {
if (t[2] <= tup[2] && t[3] > 0) {
insert = false;
break;
}
}
if (insert) {
auto tuple = tup;
tuple[3] = tup[3] < 0 ? -1 : 1;
rel_22_actual_diff_plus_path2->insert(tuple, READ_OP_CONTEXT(rel_22_actual_diff_plus_path2_op_ctxt));
}
}
if (iter > 0) {
if (rel_22_actual_diff_plus_path2->approx_size() < rel_25_path2->approx_size(iter)) {
for (const auto& tup : *rel_22_actual_diff_plus_path2) {
if (tup[2] == iter || tup[3] == 0) continue;
auto deltaExistenceCheck = rel_25_path2->equalRange_7(Tuple<RamDomain,4>{{tup[0],tup[1],iter,0}}, READ_OP_CONTEXT(rel_25_path2_op_ctxt));
if (deltaExistenceCheck.empty()) continue;
if ((*deltaExistenceCheck.begin())[3] > 0) {
auto tuple = tup;
tuple[3] = tup[3] == -1 ? 1 : -1;
rel_22_actual_diff_plus_path2->insert(tuple, READ_OP_CONTEXT(rel_22_actual_diff_plus_path2_op_ctxt));
}
}
} else {
auto deltaRestriction = rel_25_path2->equalRange_4(Tuple<RamDomain,4>{{0,0,iter,0}}, READ_OP_CONTEXT(rel_25_path2_op_ctxt));
for (const auto& tup : deltaRestriction) {
if (tup[3] <= 0) {
continue;
}
auto existenceCheck = rel_22_actual_diff_plus_path2->equalRange_3(Tuple<RamDomain,4>{{tup[0],tup[1],0,0}}, READ_OP_CONTEXT(rel_22_actual_diff_plus_path2_op_ctxt));
for (const auto& t : existenceCheck) {
if (t[2] == iter || t[3] == 0) continue;
auto tuple = t;
tuple[3] = t[3] == -1 ? 1 : -1;
rel_22_actual_diff_plus_path2->insert(tuple, READ_OP_CONTEXT(rel_22_actual_diff_plus_path2_op_ctxt));
}
}
}
}
}
}();
/* END STRATUM 2 */
/* BEGIN STRATUM 5 */
[&]() {
[&]() -> bool {
std::vector<RamDomain> args;
std::vector<RamDomain> ret;
std::vector<bool> err;
executeSubroutine("incremental_update_cleanup", args, ret, err);
if (ret.size() == 0) return false;
if (ret[0] == 0) return false; else return true;
}()
;
if (performIO) {
auto ioStart = std::chrono::high_resolution_clock::now();
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","x\ty\t@iteration\t@current_count"},{"filename","./path.csv"},{"name","path"}});
if (!outputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getWriter(std::vector<bool>({0,0,0,0}), symTable, ioDirectives, true, 1)->writeAll(*rel_12_path);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
auto ioEnd = std::chrono::high_resolution_clock::now();
ioTime += std::chrono::duration_cast<std::chrono::microseconds>(ioEnd - ioStart);
}
if (performIO) {
auto ioStart = std::chrono::high_resolution_clock::now();
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","x\ty\t@iteration\t@current_count"},{"filename","./path2.csv"},{"name","path2"}});
if (!outputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getWriter(std::vector<bool>({0,0,0,0}), symTable, ioDirectives, true, 1)->writeAll(*rel_25_path2);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
auto ioEnd = std::chrono::high_resolution_clock::now();
ioTime += std::chrono::duration_cast<std::chrono::microseconds>(ioEnd - ioStart);
}
}();
/* END STRATUM 5 */
return;
}
};
SouffleProgram *newInstance_query(){return new Sf_query;}
SymbolTable *getST_query(SouffleProgram *p){return &reinterpret_cast<Sf_query*>(p)->symTable;}

#ifdef __EMBEDDED_SOUFFLE__
class factory_Sf_query: public souffle::ProgramFactory {
SouffleProgram *newInstance() {
return new Sf_query();
};
public:
factory_Sf_query() : ProgramFactory("query"){}
};
static factory_Sf_query __factory_Sf_query_instance;
}
#else
}
int main(int argc, char** argv)
{
try{
souffle::CmdOptions opt(R"(path.dl)",
R"(.)",
R"(.)",
false,
R"()",
1,
-1);
if (!opt.parse(argc,argv)) return 1;
souffle::Sf_query obj;
#if defined(_OPENMP) 
obj.setNumThreads(opt.getNumJobs());

#endif
obj.runAll(opt.getInputFileDir(), opt.getOutputFileDir(), opt.getStratumIndex());
startIncremental(obj, opt);
return 0;
} catch(std::exception &e) { souffle::SignalHandler::instance()->error(e.what());}
}

#endif
