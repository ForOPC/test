bool elasticsearch_plugin_impl::update_account_histories( const signed_block& b )
{
   checkState(b.timestamp);
   index_name = graphene::utilities::generateIndexName(b.timestamp, _elasticsearch_index_prefix);

   graphene::chain::database& db = database();
   const vector<optional< operation_history_object > >& hist = db.get_applied_operations();

   for( const optional< operation_history_object >& o_op : hist ) {
      if(!add_elasticsearch( o_op->op->fee_payer(), o_op, b.block_num() ))
         return false;
   }

   return true;
}
