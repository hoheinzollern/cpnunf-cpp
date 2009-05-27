<?xml version='1.0' encoding='ISO-8859-1' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>common.c</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>common_8c</filename>
    <includes id="common_8h" name="common.h" local="yes" imported="no">common.h</includes>
    <member kind="function">
      <type>void</type>
      <name>nc_error</name>
      <anchorfile>common_8c.html</anchorfile>
      <anchor>91feed4dcf5050c510b1e6e1b66fad9b</anchor>
      <arglist>(const char *msg,...)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>nc_warning</name>
      <anchorfile>common_8c.html</anchorfile>
      <anchor>eb79a2ad068519f5522c87d69826e5e5</anchor>
      <arglist>(const char *msg,...)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>MYmalloc</name>
      <anchorfile>common_8c.html</anchorfile>
      <anchor>bebace53894ceca292942b006376a466</anchor>
      <arglist>(size_t size)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>MYcalloc</name>
      <anchorfile>common_8c.html</anchorfile>
      <anchor>3cc35224d16c8f4786a5d475d9d47aac</anchor>
      <arglist>(size_t size)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>MYrealloc</name>
      <anchorfile>common_8c.html</anchorfile>
      <anchor>872d86457275417344e7faeffec9f90d</anchor>
      <arglist>(void *ptr, size_t size)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>MYstrdup</name>
      <anchorfile>common_8c.html</anchorfile>
      <anchor>9815f4462106e20370c0e1c648438b68</anchor>
      <arglist>(char *string)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>common.d</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>common_8d</filename>
  </compound>
  <compound kind="file">
    <name>common.h</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>common_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>PROGRAM_NAME</name>
      <anchorfile>common_8h.html</anchorfile>
      <anchor>3b6a35b8be8405a9db72cc5dea97954b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>MYmalloc</name>
      <anchorfile>common_8h.html</anchorfile>
      <anchor>8d7108909ca791358ac94033d9c8b954</anchor>
      <arglist>(size_t)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>MYcalloc</name>
      <anchorfile>common_8h.html</anchorfile>
      <anchor>c53342911094713022341a6482321b47</anchor>
      <arglist>(size_t)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>MYrealloc</name>
      <anchorfile>common_8h.html</anchorfile>
      <anchor>48d46313999231bf70e4f1206738def3</anchor>
      <arglist>(void *, size_t)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>MYstrdup</name>
      <anchorfile>common_8h.html</anchorfile>
      <anchor>0cabe1bca0afbf4e4cff6ac1f5cc0d44</anchor>
      <arglist>(char *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>nc_error</name>
      <anchorfile>common_8h.html</anchorfile>
      <anchor>a4bfe881904f8e357085545f09aa64ec</anchor>
      <arglist>(const char *,...)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>nc_warning</name>
      <anchorfile>common_8h.html</anchorfile>
      <anchor>e6d8bd882da5dfc33a7c149c386f27c6</anchor>
      <arglist>(const char *,...)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>compress.c</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>compress_8c</filename>
    <includes id="common_8h" name="common.h" local="yes" imported="no">common.h</includes>
    <includes id="netconv_8h" name="netconv.h" local="yes" imported="no">netconv.h</includes>
    <includes id="unfold_8h" name="unfold.h" local="yes" imported="no">unfold.h</includes>
    <member kind="function">
      <type>void</type>
      <name>compress_unfolding</name>
      <anchorfile>compress_8c.html</anchorfile>
      <anchor>03e6a8de9e0cb687ba0579c87b4539b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>unf_t *</type>
      <name>c_unf</name>
      <anchorfile>compress_8c.html</anchorfile>
      <anchor>536997e1d8a586c145f6862a7af68d9f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>nodelist_t *</type>
      <name>c_cutoffs</name>
      <anchorfile>compress_8c.html</anchorfile>
      <anchor>521e1e5b0f0591faeb7f4faf5b8b78c6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>compress.d</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>compress_8d</filename>
  </compound>
  <compound kind="file">
    <name>dot.c</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>dot_8c</filename>
    <includes id="common_8h" name="common.h" local="yes" imported="no">common.h</includes>
    <includes id="netconv_8h" name="netconv.h" local="yes" imported="no">netconv.h</includes>
    <includes id="unfold_8h" name="unfold.h" local="yes" imported="no">unfold.h</includes>
    <member kind="function">
      <type>void *</type>
      <name>reverse_list</name>
      <anchorfile>dot_8c.html</anchorfile>
      <anchor>4bbf234721e04dde537f5acf8af9f9c7</anchor>
      <arglist>(void *ptr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>write_dot_output</name>
      <anchorfile>dot_8c.html</anchorfile>
      <anchor>fb089d346ade2cfc72985ddd35b968f6</anchor>
      <arglist>(unf_t *u, nodelist_t *cutoffs, char compressed)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>dot.d</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>dot_8d</filename>
  </compound>
  <compound kind="file">
    <name>main.c</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>main_8c</filename>
    <includes id="common_8h" name="common.h" local="yes" imported="no">common.h</includes>
    <includes id="netconv_8h" name="netconv.h" local="yes" imported="no">netconv.h</includes>
    <includes id="unfold_8h" name="unfold.h" local="yes" imported="no">unfold.h</includes>
    <member kind="function">
      <type>void</type>
      <name>usage</name>
      <anchorfile>main_8c.html</anchorfile>
      <anchor>bc9a1525018da38e567dfb48be4c8b5c</anchor>
      <arglist>(char *myname)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchorfile>main_8c.html</anchorfile>
      <anchor>3c04138a5bfe5d72780bb7e82a18e627</anchor>
      <arglist>(int argc, char **argv)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>main.d</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>main_8d</filename>
  </compound>
  <compound kind="file">
    <name>marking.c</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>marking_8c</filename>
    <includes id="common_8h" name="common.h" local="yes" imported="no">common.h</includes>
    <includes id="netconv_8h" name="netconv.h" local="yes" imported="no">netconv.h</includes>
    <includes id="unfold_8h" name="unfold.h" local="yes" imported="no">unfold.h</includes>
    <class kind="struct">hashcell_t</class>
    <member kind="function">
      <type>void</type>
      <name>marking_init</name>
      <anchorfile>marking_8c.html</anchorfile>
      <anchor>d3172b5b0aff7a322eb5a99f9dbe103b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>marking_hash</name>
      <anchorfile>marking_8c.html</anchorfile>
      <anchor>75ab9191fdf7c66ddfd6cd6f2fc1b036</anchor>
      <arglist>(nodelist_t *marking)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>add_marking</name>
      <anchorfile>marking_8c.html</anchorfile>
      <anchor>a40f8902251932fb9e3a21e973aea52a</anchor>
      <arglist>(nodelist_t *marking, event_t *ev)</arglist>
    </member>
    <member kind="function">
      <type>nodelist_t *</type>
      <name>marking_initial</name>
      <anchorfile>marking_8c.html</anchorfile>
      <anchor>77d5d66b38022de142d5aa8fab7dbe1e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>hashcell_t **</type>
      <name>hash</name>
      <anchorfile>marking_8c.html</anchorfile>
      <anchor>991f00dec5afd6c8c82325497d08b60a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>hash_buckets</name>
      <anchorfile>marking_8c.html</anchorfile>
      <anchor>ec2a7a969da57e681d64819544f188d9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>marking.d</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>marking_8d</filename>
  </compound>
  <compound kind="file">
    <name>netconv.c</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>netconv_8c</filename>
    <includes id="common_8h" name="common.h" local="yes" imported="no">common.h</includes>
    <includes id="netconv_8h" name="netconv.h" local="yes" imported="no">netconv.h</includes>
    <includes id="unfold_8h" name="unfold.h" local="yes" imported="no">unfold.h</includes>
    <member kind="function">
      <type>net_t *</type>
      <name>nc_create_net</name>
      <anchorfile>netconv_8c.html</anchorfile>
      <anchor>b1a7a25c3b58f2fea266880989865d13</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unf_t *</type>
      <name>nc_create_unfolding</name>
      <anchorfile>netconv_8c.html</anchorfile>
      <anchor>bab1d72ed79144e5635c0f2b2263dcc7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>place_t *</type>
      <name>nc_create_place</name>
      <anchorfile>netconv_8c.html</anchorfile>
      <anchor>f009bc3674332c760e290d5fe1f4c067</anchor>
      <arglist>(net_t *net)</arglist>
    </member>
    <member kind="function">
      <type>trans_t *</type>
      <name>nc_create_transition</name>
      <anchorfile>netconv_8c.html</anchorfile>
      <anchor>4a59964993e189a00e512e4294685d50</anchor>
      <arglist>(net_t *net)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>nc_create_arc</name>
      <anchorfile>netconv_8c.html</anchorfile>
      <anchor>31a3389201eea4d6c46c5cf42ab34dd6</anchor>
      <arglist>(nodelist_t **fromlist, nodelist_t **tolist, void *from, void *to)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>nc_compute_sizes</name>
      <anchorfile>netconv_8c.html</anchorfile>
      <anchor>500ded60a4cf5619f0700a262f14c012</anchor>
      <arglist>(net_t *net)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>nc_static_checks</name>
      <anchorfile>netconv_8c.html</anchorfile>
      <anchor>400bce7ef31900b529fbf90dc00ddd7f</anchor>
      <arglist>(net_t *net, char *stoptr_name)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>netconv.d</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>netconv_8d</filename>
  </compound>
  <compound kind="file">
    <name>netconv.h</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>netconv_8h</filename>
    <class kind="struct">place_t</class>
    <class kind="struct">trans_t</class>
    <class kind="struct">cond_t</class>
    <class kind="struct">event_t</class>
    <class kind="struct">net_t</class>
    <class kind="struct">unf_t</class>
    <class kind="struct">nodelist_t</class>
    <member kind="define">
      <type>#define</type>
      <name>COARRAY_TYPE</name>
      <anchorfile>netconv_8h.html</anchorfile>
      <anchor>7a28ccd886ee75296f85560eaa2269f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned char</type>
      <name>uchar</name>
      <anchorfile>netconv_8h.html</anchorfile>
      <anchor>65f85814a8290f9797005d3b28e7e5fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>net_t *</type>
      <name>nc_create_net</name>
      <anchorfile>netconv_8h.html</anchorfile>
      <anchor>b1a7a25c3b58f2fea266880989865d13</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unf_t *</type>
      <name>nc_create_unfolding</name>
      <anchorfile>netconv_8h.html</anchorfile>
      <anchor>bab1d72ed79144e5635c0f2b2263dcc7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>place_t *</type>
      <name>nc_create_place</name>
      <anchorfile>netconv_8h.html</anchorfile>
      <anchor>fcdc6bb5f5926dd20caaef1099371d49</anchor>
      <arglist>(net_t *)</arglist>
    </member>
    <member kind="function">
      <type>trans_t *</type>
      <name>nc_create_transition</name>
      <anchorfile>netconv_8h.html</anchorfile>
      <anchor>2d0cede4ea82b0ee06be924dc2755212</anchor>
      <arglist>(net_t *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>nc_create_arc</name>
      <anchorfile>netconv_8h.html</anchorfile>
      <anchor>5b6941b6c9a453386ebbdc9b833b86c3</anchor>
      <arglist>(struct nodelist_t **, struct nodelist_t **, void *, void *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>nc_compute_sizes</name>
      <anchorfile>netconv_8h.html</anchorfile>
      <anchor>57e557e003488aa1d451c45003ff3502</anchor>
      <arglist>(net_t *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>nc_static_checks</name>
      <anchorfile>netconv_8h.html</anchorfile>
      <anchor>365c36c368233067468ab35089c84df0</anchor>
      <arglist>(net_t *, char *)</arglist>
    </member>
    <member kind="function">
      <type>nodelist_t *</type>
      <name>nodelist_alloc</name>
      <anchorfile>netconv_8h.html</anchorfile>
      <anchor>b7977f993fe27b8bf844103a17b7c44a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>nodelist_t *</type>
      <name>nodelist_push</name>
      <anchorfile>netconv_8h.html</anchorfile>
      <anchor>3e8386443f94280b79b317ca7c6bb8b9</anchor>
      <arglist>(nodelist_t **list, void *)</arglist>
    </member>
    <member kind="function">
      <type>nodelist_t *</type>
      <name>nodelist_insert</name>
      <anchorfile>netconv_8h.html</anchorfile>
      <anchor>34da1f390c8ecd814d77e19448d30020</anchor>
      <arglist>(nodelist_t **, void *e)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>nodelist_delete</name>
      <anchorfile>netconv_8h.html</anchorfile>
      <anchor>6717df89ac38bcc9ff77b61d8574bc3e</anchor>
      <arglist>(nodelist_t *)</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>nodelist_compare</name>
      <anchorfile>netconv_8h.html</anchorfile>
      <anchor>9ec1d08da5ac8cb0b8a1352b5dacb50e</anchor>
      <arglist>(nodelist_t *, nodelist_t *)</arglist>
    </member>
    <member kind="function">
      <type>net_t *</type>
      <name>read_pep_net</name>
      <anchorfile>netconv_8h.html</anchorfile>
      <anchor>de8d990ff8cfa16cdae9c02de3cb8976</anchor>
      <arglist>(char *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>write_dot_output</name>
      <anchorfile>netconv_8h.html</anchorfile>
      <anchor>f0fdb74175db9f1d63596d93c961b137</anchor>
      <arglist>(unf_t *, nodelist_t *, char)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>reverse_list</name>
      <anchorfile>netconv_8h.html</anchorfile>
      <anchor>4b0b22b2c3c208e0614f5293461b39eb</anchor>
      <arglist>(void *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>compress_unfolding</name>
      <anchorfile>netconv_8h.html</anchorfile>
      <anchor>03e6a8de9e0cb687ba0579c87b4539b4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>nodelist.c</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>nodelist_8c</filename>
    <includes id="common_8h" name="common.h" local="yes" imported="no">common.h</includes>
    <includes id="netconv_8h" name="netconv.h" local="yes" imported="no">netconv.h</includes>
    <class kind="struct">contingent_t</class>
    <member kind="define">
      <type>#define</type>
      <name>LI_ALLOC_STEP</name>
      <anchorfile>nodelist_8c.html</anchorfile>
      <anchor>28659274c60e2bdd000758f25aad0ee7</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>nodelist_t *</type>
      <name>nodelist_alloc</name>
      <anchorfile>nodelist_8c.html</anchorfile>
      <anchor>b7977f993fe27b8bf844103a17b7c44a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>nodelist_t *</type>
      <name>nodelist_push</name>
      <anchorfile>nodelist_8c.html</anchorfile>
      <anchor>51f50ed36702b363de11dc6f17aca217</anchor>
      <arglist>(nodelist_t **list, void *node)</arglist>
    </member>
    <member kind="function">
      <type>nodelist_t *</type>
      <name>nodelist_insert</name>
      <anchorfile>nodelist_8c.html</anchorfile>
      <anchor>3842d07f3e0d19967ced7fe3f571bf53</anchor>
      <arglist>(nodelist_t **list, void *node)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>nodelist_delete</name>
      <anchorfile>nodelist_8c.html</anchorfile>
      <anchor>3588aec1ab5d6420e213077ac5d4f607</anchor>
      <arglist>(nodelist_t *list)</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>nodelist_compare</name>
      <anchorfile>nodelist_8c.html</anchorfile>
      <anchor>c47ae83f28d6d74ac4ee1eec104836af</anchor>
      <arglist>(nodelist_t *list1, nodelist_t *list2)</arglist>
    </member>
    <member kind="variable">
      <type>nodelist_t *</type>
      <name>li_freelist</name>
      <anchorfile>nodelist_8c.html</anchorfile>
      <anchor>76ac3768f95f9b09f5831f2d9a59a572</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>contingent_t *</type>
      <name>li_contlist</name>
      <anchorfile>nodelist_8c.html</anchorfile>
      <anchor>a5637b2481d6ace9c89006d544f44cfe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>li_counter</name>
      <anchorfile>nodelist_8c.html</anchorfile>
      <anchor>13df3f51951f35cc6f52b5e4ffe22c90</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>nodelist.d</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>nodelist_8d</filename>
  </compound>
  <compound kind="file">
    <name>order.c</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>order_8c</filename>
    <includes id="common_8h" name="common.h" local="yes" imported="no">common.h</includes>
    <includes id="netconv_8h" name="netconv.h" local="yes" imported="no">netconv.h</includes>
    <includes id="unfold_8h" name="unfold.h" local="yes" imported="no">unfold.h</includes>
    <member kind="function">
      <type>void</type>
      <name>parikh_init</name>
      <anchorfile>order_8c.html</anchorfile>
      <anchor>af2b012f529e81b8146c3814bf063c49</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>parikh_finish</name>
      <anchorfile>order_8c.html</anchorfile>
      <anchor>a87848fb3cf9c3abc87bc660736aadac</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>parikh_reset</name>
      <anchorfile>order_8c.html</anchorfile>
      <anchor>e718aed4c529cadf3e274b8bc7878cf5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>parikh_add</name>
      <anchorfile>order_8c.html</anchorfile>
      <anchor>d28a86f427f6c715c9023aaee6221df6</anchor>
      <arglist>(int tr_num)</arglist>
    </member>
    <member kind="function">
      <type>parikh_t *</type>
      <name>parikh_save</name>
      <anchorfile>order_8c.html</anchorfile>
      <anchor>e7f1494421599b2bafea2e3861003210</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>parikh_compare</name>
      <anchorfile>order_8c.html</anchorfile>
      <anchor>ee7df623df0510b3db34a04bdae3517e</anchor>
      <arglist>(parikh_t *pv1, parikh_t *pv2)</arglist>
    </member>
    <member kind="function">
      <type>pe_queue_t *</type>
      <name>create_queue_entry</name>
      <anchorfile>order_8c.html</anchorfile>
      <anchor>15f9a63cbc9e0896405135e6948c5b70</anchor>
      <arglist>(trans_t *tr)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>find_foata_level</name>
      <anchorfile>order_8c.html</anchorfile>
      <anchor>33f5bbfac4ef092853481b483ca45852</anchor>
      <arglist>(pe_queue_t *pe)</arglist>
    </member>
    <member kind="function">
      <type>nodelist_t **</type>
      <name>create_foata_lists</name>
      <anchorfile>order_8c.html</anchorfile>
      <anchor>d8259c53c40ecc09449dbea08e9d0c16</anchor>
      <arglist>(pe_queue_t *pe)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>foata_compare</name>
      <anchorfile>order_8c.html</anchorfile>
      <anchor>c08c3b7ddb1e837ac275a68d286db898</anchor>
      <arglist>(pe_queue_t *pe1, pe_queue_t *pe2)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>pe_compare</name>
      <anchorfile>order_8c.html</anchorfile>
      <anchor>22e112748505f71bf12fccba5578449b</anchor>
      <arglist>(pe_queue_t *pe1, pe_queue_t *pe2)</arglist>
    </member>
    <member kind="variable">
      <type>parikh_t *</type>
      <name>parikh</name>
      <anchorfile>order_8c.html</anchorfile>
      <anchor>d795b72a539ee690f24f95b0d8d3a1e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>parikh_t *</type>
      <name>pa_last</name>
      <anchorfile>order_8c.html</anchorfile>
      <anchor>f1055120529635fc61efa6a5b7675bf6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>parikh_count</name>
      <anchorfile>order_8c.html</anchorfile>
      <anchor>8843c89f58dde65b102d5ea14c171b65</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>parikh_size</name>
      <anchorfile>order_8c.html</anchorfile>
      <anchor>3a4ad98aefbaae2dd603574323bb7ed0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>order.d</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>order_8d</filename>
  </compound>
  <compound kind="file">
    <name>pe.c</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>pe_8c</filename>
    <includes id="common_8h" name="common.h" local="yes" imported="no">common.h</includes>
    <includes id="unfold_8h" name="unfold.h" local="yes" imported="no">unfold.h</includes>
    <class kind="struct">pe_comb_t</class>
    <member kind="define">
      <type>#define</type>
      <name>PE_ALLOC_STEP</name>
      <anchorfile>pe_8c.html</anchorfile>
      <anchor>97c04125022dc802161b4c50825791ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pe_init</name>
      <anchorfile>pe_8c.html</anchorfile>
      <anchor>30de00a737b7f8863fa2a7475785b802</anchor>
      <arglist>(nodelist_t *m0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pe_free</name>
      <anchorfile>pe_8c.html</anchorfile>
      <anchor>8ff0883af0a6616b3af32abd9ccad07b</anchor>
      <arglist>(pe_queue_t *qu)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pe_finish</name>
      <anchorfile>pe_8c.html</anchorfile>
      <anchor>1b096b54a9afc939bbd61399b00545ff</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pe_insert</name>
      <anchorfile>pe_8c.html</anchorfile>
      <anchor>a1b2079dde07b8c32ee94ba4f993a61e</anchor>
      <arglist>(trans_t *tr)</arglist>
    </member>
    <member kind="function">
      <type>pe_queue_t *</type>
      <name>pe_pop</name>
      <anchorfile>pe_8c.html</anchorfile>
      <anchor>3239501b59cde7ac3e944ed31c95768f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>pe_conflict</name>
      <anchorfile>pe_8c.html</anchorfile>
      <anchor>1cc6755066fd3524e8b940b264fa4fd3</anchor>
      <arglist>(pe_comb_t *curr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pe</name>
      <anchorfile>pe_8c.html</anchorfile>
      <anchor>a1ac12d85cd32c9fa6c97d85e4ecd30a</anchor>
      <arglist>(cond_t *co)</arglist>
    </member>
    <member kind="variable">
      <type>pe_queue_t **</type>
      <name>pe_queue</name>
      <anchorfile>pe_8c.html</anchorfile>
      <anchor>ee009c1089e81f58af35baea110ea608</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>pe_qsize</name>
      <anchorfile>pe_8c.html</anchorfile>
      <anchor>62cbcade4607afd2743bf24364333a97</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>pe_qalloc</name>
      <anchorfile>pe_8c.html</anchorfile>
      <anchor>a73ede1fb7952a0752526c3b4425fda8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>pe_comb_t *</type>
      <name>pe_combs</name>
      <anchorfile>pe_8c.html</anchorfile>
      <anchor>0b55f663d0dbd996cdb2d19f0c112431</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>cond_t **</type>
      <name>pe_conds</name>
      <anchorfile>pe_8c.html</anchorfile>
      <anchor>89ad48fe439058302c8bc7c5146e4720</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uchar *</type>
      <name>pe0_conflicts</name>
      <anchorfile>pe_8c.html</anchorfile>
      <anchor>4245ae68002df8a81979eedc15dcfcf2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>pe.d</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>pe_8d</filename>
  </compound>
  <compound kind="file">
    <name>readlib.c</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>readlib_8c</filename>
    <includes id="common_8h" name="common.h" local="yes" imported="no">common.h</includes>
    <member kind="function">
      <type>char</type>
      <name>ReadCharComment</name>
      <anchorfile>readlib_8c.html</anchorfile>
      <anchor>e27b5cdfe33be74bc62d6dd5326e4743</anchor>
      <arglist>(FILE *file)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ReadCmdToken</name>
      <anchorfile>readlib_8c.html</anchorfile>
      <anchor>8e9b696997dea2a46883576e9a65650a</anchor>
      <arglist>(FILE *file)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ReadNewline</name>
      <anchorfile>readlib_8c.html</anchorfile>
      <anchor>da087de3ea61b74b8a97badaf2cc02bf</anchor>
      <arglist>(FILE *file)</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>ReadWhiteSpace</name>
      <anchorfile>readlib_8c.html</anchorfile>
      <anchor>99b766bba3577486795326ddc47a9486</anchor>
      <arglist>(FILE *file)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ReadNumber</name>
      <anchorfile>readlib_8c.html</anchorfile>
      <anchor>d76a204b462dad4275fa7f171127324f</anchor>
      <arglist>(FILE *file, int *result)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ReadEnclString</name>
      <anchorfile>readlib_8c.html</anchorfile>
      <anchor>eaf65b05705d364ec20ca5f4d3ca32f8</anchor>
      <arglist>(FILE *file)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ReadCoordinates</name>
      <anchorfile>readlib_8c.html</anchorfile>
      <anchor>063a3d0b50d75f54fbe1327787c99543</anchor>
      <arglist>(FILE *file, int *x, int *y)</arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>HLinput_file</name>
      <anchorfile>readlib_8c.html</anchorfile>
      <anchor>764bb080d020f9f2ef1001bb7c73f05d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>HLinput_line</name>
      <anchorfile>readlib_8c.html</anchorfile>
      <anchor>8be057b2e5d391c01209880dad3a6a1f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>sbuf</name>
      <anchorfile>readlib_8c.html</anchorfile>
      <anchor>612a4d3e95e5d4f14ae7b87fc4673530</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>sballoc</name>
      <anchorfile>readlib_8c.html</anchorfile>
      <anchor>2599b2b1fac08731c62edb057e514746</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>readlib.d</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>readlib_8d</filename>
  </compound>
  <compound kind="file">
    <name>readlib.h</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>readlib_8h</filename>
    <member kind="function">
      <type>char</type>
      <name>ReadCharComment</name>
      <anchorfile>readlib_8h.html</anchorfile>
      <anchor>e27b5cdfe33be74bc62d6dd5326e4743</anchor>
      <arglist>(FILE *file)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ReadCmdToken</name>
      <anchorfile>readlib_8h.html</anchorfile>
      <anchor>8e9b696997dea2a46883576e9a65650a</anchor>
      <arglist>(FILE *file)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ReadNewline</name>
      <anchorfile>readlib_8h.html</anchorfile>
      <anchor>da087de3ea61b74b8a97badaf2cc02bf</anchor>
      <arglist>(FILE *file)</arglist>
    </member>
    <member kind="function">
      <type>char</type>
      <name>ReadWhiteSpace</name>
      <anchorfile>readlib_8h.html</anchorfile>
      <anchor>99b766bba3577486795326ddc47a9486</anchor>
      <arglist>(FILE *file)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ReadNumber</name>
      <anchorfile>readlib_8h.html</anchorfile>
      <anchor>ce5c7aeb52044fdb8a719c6df694a16f</anchor>
      <arglist>(FILE *file, int *x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ReadEnclString</name>
      <anchorfile>readlib_8h.html</anchorfile>
      <anchor>eaf65b05705d364ec20ca5f4d3ca32f8</anchor>
      <arglist>(FILE *file)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ReadCoordinates</name>
      <anchorfile>readlib_8h.html</anchorfile>
      <anchor>063a3d0b50d75f54fbe1327787c99543</anchor>
      <arglist>(FILE *file, int *x, int *y)</arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>HLinput_file</name>
      <anchorfile>readlib_8h.html</anchorfile>
      <anchor>764bb080d020f9f2ef1001bb7c73f05d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>HLinput_line</name>
      <anchorfile>readlib_8h.html</anchorfile>
      <anchor>8be057b2e5d391c01209880dad3a6a1f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>sbuf</name>
      <anchorfile>readlib_8h.html</anchorfile>
      <anchor>612a4d3e95e5d4f14ae7b87fc4673530</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>sballoc</name>
      <anchorfile>readlib_8h.html</anchorfile>
      <anchor>2599b2b1fac08731c62edb057e514746</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>readpep.c</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>readpep_8c</filename>
    <includes id="readlib_8h" name="readlib.h" local="yes" imported="no">readlib.h</includes>
    <includes id="netconv_8h" name="netconv.h" local="yes" imported="no">netconv.h</includes>
    <includes id="common_8h" name="common.h" local="yes" imported="no">common.h</includes>
    <class kind="struct">t_dest</class>
    <class kind="struct">t_blockdest</class>
    <class kind="struct">t_coords</class>
    <class kind="struct">t_fieldinfo</class>
    <class kind="struct">t_blockinfo</class>
    <class kind="struct">t_lookup</class>
    <member kind="define">
      <type>#define</type>
      <name>MBSIZE</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>fea32302177fb2c816547017ef130d82</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>NAMES_START</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>54ee5247efa9f1baf7750b0e30c18d3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>NAMES_OFFSET</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>91a1f8c614e36f2710768ef49dacc409</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FT_STRING</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>06fc87d81c62e9abb8790b6e5713c55b424189c585691c2ce732ea69a88f4f29</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FT_COORDS</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>06fc87d81c62e9abb8790b6e5713c55be29b90eacfbbcc6b0389a25888f54113</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FT_NUMBER</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>06fc87d81c62e9abb8790b6e5713c55b19c9277860ad0382b6b3c1df578b0197</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FT_FLAG</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>06fc87d81c62e9abb8790b6e5713c55bf00ae10b3c9e391c6d543d7a80446773</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TB_MANDATORY</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>df764cbdea00d65edcd07bb9953ad2b7bacb2ae450f156f3c6ab7871243f537e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TB_OPTIONAL</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>df764cbdea00d65edcd07bb9953ad2b70a586977c377dd13cf1676fe0411ef8e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TB_BLOCK</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>99fb83031ce9923c84392b4e92f956b531574ccf37a08f34ad1229782c82ca32</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TB_LINE</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>99fb83031ce9923c84392b4e92f956b5cc21577fd400c14b17a446afcbbdefd6</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>read_PEP_file</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>bffbba931d5637467e8dac70f3dc0674</anchor>
      <arglist>(char *filename, char **types, t_blockinfo *blocks, t_blockdest *dest)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>insert_place</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>b39e818ed7248b4e369b11e6356b3656</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>insert_trans</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>2cbc9fa632a64194dab104732aaa3b3f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>insert_arc</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>f3b81740d5179c176feb4fcb2ed06a48</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>insert_ra</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>8a91be4d8a45a46db937e7bc9cf49393</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>net_t *</type>
      <name>read_pep_net</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>9ee94a761977839368e16ffcfdef0bac</anchor>
      <arglist>(char *PEPfilename)</arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>filetype</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>3629568490682b208244f17fb2aa00f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>blocktype</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>a3168fbe10df214f4c7516e4bfd11c99</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>type_llnet</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>a40b1f86b968f5a72c6604f42d235e74</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>t_fieldinfo</type>
      <name>nodedefs</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>88d981a70c22993919faa954435c774d</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>t_fieldinfo</type>
      <name>arcdefs</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>429ecaa87343e219715e1b7136768e19</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>t_fieldinfo</type>
      <name>blockfields</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>47cd0f97cadb1b11c3740b1c7781c378</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>t_fieldinfo</type>
      <name>placefields</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>72a1b9ac717ad2dd836dfed3a6fbea8e</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>t_fieldinfo</type>
      <name>transfields</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>cbbfffdc21f32fe676b27b54eb0d3958</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>t_fieldinfo</type>
      <name>arcfields</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>f51ad4fc4735fb1b290f112bc8af6abe</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>t_fieldinfo</type>
      <name>textfields</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>eac698e9a597bb9aa891a5e93d267de8</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>t_blockinfo</type>
      <name>netblocks</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>eb4c3c83964c8c0b0ef6c7b8734de78d</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable">
      <type>net_t *</type>
      <name>rd_net</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>adc6c631f29712afdcc3d4ce2ff647aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>t_coords *</type>
      <name>rd_co</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>4ab73fe20106004c67d86d390f2f3f21</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>place_t **</type>
      <name>PlArray</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>2eb9cf9beced0ed7bed555acc7564b4e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>trans_t **</type>
      <name>TrArray</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>e1cd6013bd7b24c27dcf7b915b186eb9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>AnzPlNamen</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>ef02b8dff7ab762a71d3f651d3518d3d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>MaxPlNamen</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>5eeab1c1da7384a6b917202deb944866</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>AnzTrNamen</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>e1e262b946392bb2613001bdd372b07c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>MaxTrNamen</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>55e3f3aafa273cc9a5008d1cd736b554</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>placecount</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>8161f480fa51bcd5551e3c1b6b5a6d2b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>transcount</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>f262a30127becc6c32d92545a4169cc3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>rd_ident</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>e9c1a03c4e6b860ca0236002a720168f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>rd_marked</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>86b3f6e3725f5241990a0d555898957b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>autonumbering</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>26d54ffbdad41a3a5434cb9d49c803c2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>rd_name</name>
      <anchorfile>readpep_8c.html</anchorfile>
      <anchor>add7ee752023d96c4e79407917d69f16</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>readpep.d</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>readpep_8d</filename>
  </compound>
  <compound kind="file">
    <name>unfold.c</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>unfold_8c</filename>
    <includes id="common_8h" name="common.h" local="yes" imported="no">common.h</includes>
    <includes id="netconv_8h" name="netconv.h" local="yes" imported="no">netconv.h</includes>
    <includes id="unfold_8h" name="unfold.h" local="yes" imported="no">unfold.h</includes>
    <class kind="struct">cqentry_t</class>
    <member kind="enumvalue">
      <name>CUTOFF_NO</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>bc6126af1d45847bc59afa0aa3216b04d6b5522effe5267432f92de5fec8ea89</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CUTOFF_YES</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>bc6126af1d45847bc59afa0aa3216b04d75ab361aaf18dfd639d55434b8a8623</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>COARRAY_TYPE *</type>
      <name>alloc_coarray</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>c968d360bc4af99032c15e0317615430</anchor>
      <arglist>(int size)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addto_coarray</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>8a42384872189247df0b0cfb0efcd7b4</anchor>
      <arglist>(COARRAY_TYPE **array, cond_t *co)</arglist>
    </member>
    <member kind="function">
      <type>COARRAY_TYPE *</type>
      <name>coarray_copy</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>627dd61e83abc107e19256fe45415b07</anchor>
      <arglist>(COARRAY_TYPE *array)</arglist>
    </member>
    <member kind="function">
      <type>cond_t *</type>
      <name>insert_condition</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>86d311dca945d3483d74b5c64aba5c9f</anchor>
      <arglist>(place_t *pl, event_t *ev)</arglist>
    </member>
    <member kind="function">
      <type>event_t *</type>
      <name>insert_event</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>8a919e1be3817241dc07ee5c33aebbb8</anchor>
      <arglist>(pe_queue_t *qu)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_post_conditions</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>b4b4d4c9770115b4338a7bd24df47bc5</anchor>
      <arglist>(event_t *ev, char cutoff)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>insert_to_queue</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>9c7adfcdaea5122c9349fc2664f6b813</anchor>
      <arglist>(cqentry_t **queue, cqentry_t *newentry, cond_t *co, int index)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>co_relation</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>73c635cf068fe50af1ad8cf4f4690b23</anchor>
      <arglist>(event_t *ev)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>recursive_add</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>df7315696e6d3eadf00decfc55b88b28</anchor>
      <arglist>(nodelist_t *pre, nodelist_t *current)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>recursive_pe</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>6ec2bc33e13eef423ca95675bb679a9d</anchor>
      <arglist>(nodelist_t *list)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unfold</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>d61bcb2c993aeb9511d7813df10b68c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>net_t *</type>
      <name>net</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>cec5365aa7cf94c08c42f58e435ffd35</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unf_t *</type>
      <name>unf</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>4564c559e5af0d34f455f416c87b17d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>exitcode</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>fb5e4c1ad38fd7cdbebdf723fe0b362b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>conditions_size</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>3e7bc3281bfb6dd90a746ef840fd2c1e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>events_size</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>a07ff13f4952ddfae3213b2b14a81dbe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>ce_alloc_step</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>6bbd7d2da4b1c4621a03cffa4d02843a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>ev_mark</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>429d2433fc575abf904ec4f8456c41ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>cond_t **</type>
      <name>conditions</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>c20f0647041802bcb366f7ad8bde13a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>event_t **</type>
      <name>events</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>a70c13383d9237b4c16f46a8722cfed1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>trans_t *</type>
      <name>stoptr</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>124111b50feac1cd9535baded5fb6339</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>nodelist_t *</type>
      <name>cutoff_list</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>fb24a0e1008ef600c8d4546471b7e937</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>nodelist_t *</type>
      <name>corr_list</name>
      <anchorfile>unfold_8c.html</anchorfile>
      <anchor>bd9c0dfb16fffaf430b8c34fa4c3df27</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>unfold.d</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>unfold_8d</filename>
  </compound>
  <compound kind="file">
    <name>unfold.h</name>
    <path>/home/alessandro/Documents/Tesi/mora-070321/</path>
    <filename>unfold_8h</filename>
    <includes id="netconv_8h" name="netconv.h" local="yes" imported="no">netconv.h</includes>
    <class kind="struct">pe_queue_t</class>
    <class kind="struct">parikh_t</class>
    <member kind="function">
      <type>void</type>
      <name>unfold</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>d61bcb2c993aeb9511d7813df10b68c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>marking_init</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>d3172b5b0aff7a322eb5a99f9dbe103b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>add_marking</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>4df87c1a9f8e27fde31d52295299e768</anchor>
      <arglist>(nodelist_t *, event_t *)</arglist>
    </member>
    <member kind="function">
      <type>nodelist_t *</type>
      <name>marking_initial</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>77d5d66b38022de142d5aa8fab7dbe1e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pe_init</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>12a29a561513a492bd1c66343d7b662a</anchor>
      <arglist>(nodelist_t *)</arglist>
    </member>
    <member kind="function">
      <type>pe_queue_t *</type>
      <name>pe_pop</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>3239501b59cde7ac3e944ed31c95768f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pe_free</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>df69057675f1a7e7688d74562872fc43</anchor>
      <arglist>(pe_queue_t *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pe_finish</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>1b096b54a9afc939bbd61399b00545ff</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pe</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>49ca1a6e26fef4eabc73c23af7f70203</anchor>
      <arglist>(cond_t *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>parikh_init</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>af2b012f529e81b8146c3814bf063c49</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>parikh_finish</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>a87848fb3cf9c3abc87bc660736aadac</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>pe_queue_t *</type>
      <name>create_queue_entry</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>0214606cf7e5f3742b62dc00bfeb95de</anchor>
      <arglist>(trans_t *)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>pe_compare</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>76d0ad1921eba1bb915a0ea61e13c3e5</anchor>
      <arglist>(pe_queue_t *, pe_queue_t *)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>find_foata_level</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>26dc47159ca1e2720bb8a8df19171c52</anchor>
      <arglist>(pe_queue_t *)</arglist>
    </member>
    <member kind="variable">
      <type>net_t *</type>
      <name>net</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>cec5365aa7cf94c08c42f58e435ffd35</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unf_t *</type>
      <name>unf</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>4564c559e5af0d34f455f416c87b17d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unf_t *</type>
      <name>c_unf</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>536997e1d8a586c145f6862a7af68d9f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>conditions_size</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>3e7bc3281bfb6dd90a746ef840fd2c1e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>events_size</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>a07ff13f4952ddfae3213b2b14a81dbe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>ev_mark</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>429d2433fc575abf904ec4f8456c41ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>event_t **</type>
      <name>events</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>a70c13383d9237b4c16f46a8722cfed1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>exitcode</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>fb5e4c1ad38fd7cdbebdf723fe0b362b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>trans_t *</type>
      <name>stoptr</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>124111b50feac1cd9535baded5fb6339</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>nodelist_t *</type>
      <name>cutoff_list</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>fb24a0e1008ef600c8d4546471b7e937</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>nodelist_t *</type>
      <name>corr_list</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>bd9c0dfb16fffaf430b8c34fa4c3df27</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>nodelist_t *</type>
      <name>c_cutoffs</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>521e1e5b0f0591faeb7f4faf5b8b78c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>cond_t **</type>
      <name>pe_conds</name>
      <anchorfile>unfold_8h.html</anchorfile>
      <anchor>89ad48fe439058302c8bc7c5146e4720</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>cond_t</name>
    <filename>structcond__t.html</filename>
    <member kind="variable">
      <type>struct cond_t *</type>
      <name>next</name>
      <anchorfile>structcond__t.html</anchorfile>
      <anchor>3e3be351a9c4e71c61c78cc2989ce6d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct event_t *</type>
      <name>pre_ev</name>
      <anchorfile>structcond__t.html</anchorfile>
      <anchor>d12b24a40ddf43fa8e84c6082ad1c40c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct nodelist_t *</type>
      <name>postset</name>
      <anchorfile>structcond__t.html</anchorfile>
      <anchor>0615fe2f8d9e0437c6ce404a9982e884</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct place_t *</type>
      <name>origin</name>
      <anchorfile>structcond__t.html</anchorfile>
      <anchor>c9133c5caa3212b0f8211cb5ec291fe5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>num</name>
      <anchorfile>structcond__t.html</anchorfile>
      <anchor>f2bae9cd04270894865cadda98e0cd0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>mark</name>
      <anchorfile>structcond__t.html</anchorfile>
      <anchor>b52cd21464c95e2596b623d222bb22b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>COARRAY_TYPE *</type>
      <name>coarray_common</name>
      <anchorfile>structcond__t.html</anchorfile>
      <anchor>8f43b058767b46e05b756e9bb94fea7b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>COARRAY_TYPE *</type>
      <name>coarray_private</name>
      <anchorfile>structcond__t.html</anchorfile>
      <anchor>b16c962c1f9bddd6ad403409f6f67d1b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct cond_t *</type>
      <name>phantom</name>
      <anchorfile>structcond__t.html</anchorfile>
      <anchor>e213716addc7c4395e60b741ae5715e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct cond_t *</type>
      <name>compressed</name>
      <anchorfile>structcond__t.html</anchorfile>
      <anchor>ce7ba5031f959fac4397b8a4aed846dd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>contingent_t</name>
    <filename>structcontingent__t.html</filename>
    <member kind="variable">
      <type>nodelist_t *</type>
      <name>nodes</name>
      <anchorfile>structcontingent__t.html</anchorfile>
      <anchor>c75ea2fec684bbb5f56d7eec198a744c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct contingent_t *</type>
      <name>next</name>
      <anchorfile>structcontingent__t.html</anchorfile>
      <anchor>c400785b6d7e96ecc2f9273c1ede038a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>cqentry_t</name>
    <filename>structcqentry__t.html</filename>
    <member kind="variable">
      <type>cond_t *</type>
      <name>co</name>
      <anchorfile>structcqentry__t.html</anchorfile>
      <anchor>f3597cd9e533f65e555d704e6e3ff163</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>index</name>
      <anchorfile>structcqentry__t.html</anchorfile>
      <anchor>689baf31e6819d11e25bc1acfec8eaeb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct cqentry_t *</type>
      <name>next</name>
      <anchorfile>structcqentry__t.html</anchorfile>
      <anchor>1efdc838c9411c395e81cc383fac63b7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>event_t</name>
    <filename>structevent__t.html</filename>
    <member kind="variable">
      <type>struct event_t *</type>
      <name>next</name>
      <anchorfile>structevent__t.html</anchorfile>
      <anchor>ab3dd22d49a597904f2cac53299efae9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct cond_t **</type>
      <name>preset</name>
      <anchorfile>structevent__t.html</anchorfile>
      <anchor>8ba7dc592724bb21e662c9a34fae0a1b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct cond_t **</type>
      <name>postset</name>
      <anchorfile>structevent__t.html</anchorfile>
      <anchor>82cfea08769b5a9a5d1622c6dff793e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct trans_t *</type>
      <name>origin</name>
      <anchorfile>structevent__t.html</anchorfile>
      <anchor>661b9c86c2ec34df71836cd6822e0b23</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>mark</name>
      <anchorfile>structevent__t.html</anchorfile>
      <anchor>b3798b354c2c7ea70a968136014670ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>COARRAY_TYPE *</type>
      <name>coarray</name>
      <anchorfile>structevent__t.html</anchorfile>
      <anchor>60003beae07e864bb16062d6ed6a70d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>foata_level</name>
      <anchorfile>structevent__t.html</anchorfile>
      <anchor>3bf414059961d92cc7227f4c3525ac21</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>preset_size</name>
      <anchorfile>structevent__t.html</anchorfile>
      <anchor>fef1d8b03359518908899ef8e7167552</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>postset_size</name>
      <anchorfile>structevent__t.html</anchorfile>
      <anchor>27368a3a9cc1d145169906b71d8c58ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct event_t *</type>
      <name>phantom</name>
      <anchorfile>structevent__t.html</anchorfile>
      <anchor>c5e9f0466f5ad0543e8bb429c0c47c4e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct event_t *</type>
      <name>compressed</name>
      <anchorfile>structevent__t.html</anchorfile>
      <anchor>f98601803da4c314be1434b5768ddcfd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>hashcell_t</name>
    <filename>structhashcell__t.html</filename>
    <member kind="variable">
      <type>nodelist_t *</type>
      <name>marking</name>
      <anchorfile>structhashcell__t.html</anchorfile>
      <anchor>6815a57df0e68449345e0233c332f0e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>event_t *</type>
      <name>event</name>
      <anchorfile>structhashcell__t.html</anchorfile>
      <anchor>fdec1a9167183cd7bfff93c81c80f268</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct hashcell_t *</type>
      <name>next</name>
      <anchorfile>structhashcell__t.html</anchorfile>
      <anchor>4cf501fd8dd05bedf9947792d1b3f7fc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>net_t</name>
    <filename>structnet__t.html</filename>
    <member kind="variable">
      <type>place_t *</type>
      <name>places</name>
      <anchorfile>structnet__t.html</anchorfile>
      <anchor>9609a61b9d57b385c7b080084ce40d61</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>trans_t *</type>
      <name>transitions</name>
      <anchorfile>structnet__t.html</anchorfile>
      <anchor>30bb68f3678fd5fb117acf9a2c1bfa5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>numpl</name>
      <anchorfile>structnet__t.html</anchorfile>
      <anchor>d63b1e320203c45f1f5c41a21ef07db8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>numtr</name>
      <anchorfile>structnet__t.html</anchorfile>
      <anchor>023277a205a729dd3c69dc1546813e9a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>maxpre</name>
      <anchorfile>structnet__t.html</anchorfile>
      <anchor>f9411b9f64d45beaf071efe90d34f70a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>maxpost</name>
      <anchorfile>structnet__t.html</anchorfile>
      <anchor>90e41162c544eb5b9f4623214f542d2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>maxra</name>
      <anchorfile>structnet__t.html</anchorfile>
      <anchor>9deeeb26600eb87d2ac1b597cdbdfe77</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>nodelist_t</name>
    <filename>structnodelist__t.html</filename>
    <member kind="variable">
      <type>void *</type>
      <name>node</name>
      <anchorfile>structnodelist__t.html</anchorfile>
      <anchor>d1bec5a662074667f953775c45fa99e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct nodelist_t *</type>
      <name>next</name>
      <anchorfile>structnodelist__t.html</anchorfile>
      <anchor>308fcad302474a5c3e613b49b9a13a7b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>parikh_t</name>
    <filename>structparikh__t.html</filename>
    <member kind="variable">
      <type>unsigned short int</type>
      <name>tr_num</name>
      <anchorfile>structparikh__t.html</anchorfile>
      <anchor>949627aa663f71287abefbcc7dbf2fdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short int</type>
      <name>appearances</name>
      <anchorfile>structparikh__t.html</anchorfile>
      <anchor>ea7624a15fba73a81a2af410483f100e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>pe_comb_t</name>
    <filename>structpe__comb__t.html</filename>
    <member kind="variable">
      <type>nodelist_t *</type>
      <name>current</name>
      <anchorfile>structpe__comb__t.html</anchorfile>
      <anchor>94a8f8feae20207fc46adaccd1d7ed65</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>nodelist_t *</type>
      <name>start</name>
      <anchorfile>structpe__comb__t.html</anchorfile>
      <anchor>e5547a2e4ace851fababd70c47fa2ff6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>pe_queue_t</name>
    <filename>structpe__queue__t.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>lc_size</name>
      <anchorfile>structpe__queue__t.html</anchorfile>
      <anchor>1bdb85daef7be8e94acae7b1613a6f10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct parikh_t *</type>
      <name>p_vector</name>
      <anchorfile>structpe__queue__t.html</anchorfile>
      <anchor>757397f0689b50f934b686568e9c44d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>trans_t *</type>
      <name>trans</name>
      <anchorfile>structpe__queue__t.html</anchorfile>
      <anchor>e2faaa0742e52deafe3719278435dc47</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>cond_t **</type>
      <name>conds</name>
      <anchorfile>structpe__queue__t.html</anchorfile>
      <anchor>703f4fdee7a66e9ddc6c9366af084f1e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>nodelist_t *</type>
      <name>marking</name>
      <anchorfile>structpe__queue__t.html</anchorfile>
      <anchor>6e1469cd08bcd7b52219044436e1ddc0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>place_t</name>
    <filename>structplace__t.html</filename>
    <member kind="variable">
      <type>struct place_t *</type>
      <name>next</name>
      <anchorfile>structplace__t.html</anchorfile>
      <anchor>d5f8736cc7ec1cb5d6ff53f6b92e8034</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>name</name>
      <anchorfile>structplace__t.html</anchorfile>
      <anchor>517ca5fc93243193eabcf49b4ccf1ee8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>num</name>
      <anchorfile>structplace__t.html</anchorfile>
      <anchor>e15bfd3189adfed569beb3102bbf1d66</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct nodelist_t *</type>
      <name>preset</name>
      <anchorfile>structplace__t.html</anchorfile>
      <anchor>c921c23865dae5e30c15edf883355735</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct nodelist_t *</type>
      <name>postset</name>
      <anchorfile>structplace__t.html</anchorfile>
      <anchor>94f4713719a1252637f0cf75326987a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct nodelist_t *</type>
      <name>readarcs</name>
      <anchorfile>structplace__t.html</anchorfile>
      <anchor>f420801dc661dc02368b03f8cc5e9a9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct nodelist_t *</type>
      <name>conds</name>
      <anchorfile>structplace__t.html</anchorfile>
      <anchor>1f457499d852b1411a39346ca0243137</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>marked</name>
      <anchorfile>structplace__t.html</anchorfile>
      <anchor>c8d3a2d8c64747e5edc67836965aa02c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>t_blockdest</name>
    <filename>structt__blockdest.html</filename>
    <member kind="variable">
      <type>char *</type>
      <name>name</name>
      <anchorfile>structt__blockdest.html</anchorfile>
      <anchor>7559e58c7a56b8e35f4d8b9eee48b5ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int(*</type>
      <name>hookfunc</name>
      <anchorfile>structt__blockdest.html</anchorfile>
      <anchor>eb62fc8c3eb8d015b0f1d637ab695e60</anchor>
      <arglist>)()</arglist>
    </member>
    <member kind="variable">
      <type>char **</type>
      <name>restptr</name>
      <anchorfile>structt__blockdest.html</anchorfile>
      <anchor>d1cc098fd4b50f83bed3acc4a25b4442</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>t_dest *</type>
      <name>destarray</name>
      <anchorfile>structt__blockdest.html</anchorfile>
      <anchor>b676603905e68dfab317c0c5cb48a0e5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>t_blockinfo</name>
    <filename>structt__blockinfo.html</filename>
    <member kind="variable">
      <type>char *</type>
      <name>name</name>
      <anchorfile>structt__blockinfo.html</anchorfile>
      <anchor>4802e6e666cd0c90160e9d2c9eb3f995</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>optional</name>
      <anchorfile>structt__blockinfo.html</anchorfile>
      <anchor>2bdc28c5dcf17320676af5b375c8acf0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>line</name>
      <anchorfile>structt__blockinfo.html</anchorfile>
      <anchor>631c0ef2ebf0ed973b229f6b2c558317</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>t_fieldinfo *</type>
      <name>field</name>
      <anchorfile>structt__blockinfo.html</anchorfile>
      <anchor>657444ebd2d0bb96138bdcab1fc85315</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>t_coords</name>
    <filename>structt__coords.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>x</name>
      <anchorfile>structt__coords.html</anchorfile>
      <anchor>b1a8d08368bbc05a5d64f48e5692da05</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>y</name>
      <anchorfile>structt__coords.html</anchorfile>
      <anchor>71b1e3554f5d216c784d18a4b7ef4565</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>t_dest</name>
    <filename>structt__dest.html</filename>
    <member kind="variable">
      <type>char</type>
      <name>c</name>
      <anchorfile>structt__dest.html</anchorfile>
      <anchor>027f7c3341dcf3405d8bce543eb3a02a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>void *</type>
      <name>ptr</name>
      <anchorfile>structt__dest.html</anchorfile>
      <anchor>52aaa87640fd9a370b4ace536ec5f56e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>t_fieldinfo</name>
    <filename>structt__fieldinfo.html</filename>
    <member kind="variable">
      <type>char</type>
      <name>c</name>
      <anchorfile>structt__fieldinfo.html</anchorfile>
      <anchor>c142640355d79a763072aa2118c994eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>type</name>
      <anchorfile>structt__fieldinfo.html</anchorfile>
      <anchor>d65dc557df3ec2c1f3ed5885416688e9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>t_lookup</name>
    <filename>structt__lookup.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>type</name>
      <anchorfile>structt__lookup.html</anchorfile>
      <anchor>cb62931046ca500fff8d9dd22dccc35e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>void *</type>
      <name>ptr</name>
      <anchorfile>structt__lookup.html</anchorfile>
      <anchor>3be0507fc7292e7bd34b5d0aa8e8a812</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>trans_t</name>
    <filename>structtrans__t.html</filename>
    <member kind="variable">
      <type>struct trans_t *</type>
      <name>next</name>
      <anchorfile>structtrans__t.html</anchorfile>
      <anchor>a67a705a964bbefdcb9be4befc1ae585</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>name</name>
      <anchorfile>structtrans__t.html</anchorfile>
      <anchor>0a7b6db7d1b673ebc959c80a0ace9c95</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>num</name>
      <anchorfile>structtrans__t.html</anchorfile>
      <anchor>42a9c177f2d6ffe8c0d490f88be6f3da</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct nodelist_t *</type>
      <name>preset</name>
      <anchorfile>structtrans__t.html</anchorfile>
      <anchor>ec31c9046342d23275a76d8d6e0f2cb5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct nodelist_t *</type>
      <name>postset</name>
      <anchorfile>structtrans__t.html</anchorfile>
      <anchor>9852509eacdcaf7ee444e0647c5a152b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct nodelist_t *</type>
      <name>readarcs</name>
      <anchorfile>structtrans__t.html</anchorfile>
      <anchor>241ebf13bdaba4f22282d0dc019e30f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>preset_size</name>
      <anchorfile>structtrans__t.html</anchorfile>
      <anchor>91ef354140b09bbf7db46a956575b477</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>postset_size</name>
      <anchorfile>structtrans__t.html</anchorfile>
      <anchor>c9516054343d7d25676bb28a28fda9b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>short</type>
      <name>readarc_size</name>
      <anchorfile>structtrans__t.html</anchorfile>
      <anchor>e23c5ec48737a55227b6d82580a38e81</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>unf_t</name>
    <filename>structunf__t.html</filename>
    <member kind="variable">
      <type>cond_t *</type>
      <name>conditions</name>
      <anchorfile>structunf__t.html</anchorfile>
      <anchor>479d6733bf843360c18d482d585a8dcb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>event_t *</type>
      <name>events</name>
      <anchorfile>structunf__t.html</anchorfile>
      <anchor>d9ef03804644d5a4d1ca051fc831b1e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>numco</name>
      <anchorfile>structunf__t.html</anchorfile>
      <anchor>7715435dbec2c3d1edbdb2e0e79d1fcd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>numev</name>
      <anchorfile>structunf__t.html</anchorfile>
      <anchor>0aa99c051fc839987e544daf76627a7f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct nodelist_t *</type>
      <name>m0</name>
      <anchorfile>structunf__t.html</anchorfile>
      <anchor>2545cfdb66c1f3b416cca448db5567b1</anchor>
      <arglist></arglist>
    </member>
  </compound>
</tagfile>
