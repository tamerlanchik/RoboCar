package com.tamerlanchik.robocar;

import android.app.Activity;
import android.view.LayoutInflater;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;

public class Logger {
    private RecyclerView mLogRecyclerView;
    private LogAdapter mAdapter;
    private LogStorage mLogMessagesList;
    private Activity mContext;

    public Logger(Activity context){
        mContext = context;
        mLogRecyclerView = (RecyclerView) mContext.findViewById(R.id.log_recycle_view);
        mLogRecyclerView.setLayoutManager(new LinearLayoutManager(mContext));
        mLogMessagesList = LogStorage.get(context);
        mAdapter = new LogAdapter(mLogMessagesList.getLog());
        mLogRecyclerView.setAdapter(mAdapter);
    }

    public void write(String message){
        write(new LogItem(message));
    }

    public void write(final LogItem message){
        mContext.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                mLogMessagesList.add(message);
                mAdapter.notifyItemInserted(mAdapter.getItemCount()-1);
                mLogRecyclerView.scrollToPosition(mAdapter.getItemCount()-1);
                mLogRecyclerView.getItemAnimator().setMoveDuration(0);
            }
        });
    }

    private class LogHolder extends RecyclerView.ViewHolder{
        private TextView mMessageTextView;
        private TextView mTimeTextView;
        private ImageView mMarkImageView;
        private SimpleDateFormat mDateFormat;

        public LogHolder(LayoutInflater inflater, ViewGroup parent) {
            super(inflater.inflate(R.layout.log_item, parent, false));

            mMarkImageView = (ImageView) itemView.findViewById(R.id.color_mark_log_mage_view);
            mMessageTextView = (TextView) itemView.findViewById(R.id.log_message_text_view);
            mTimeTextView = (TextView) itemView.findViewById(R.id.log_time_text_view);
            mDateFormat = new SimpleDateFormat("HH:mm:ss.SSS");
        }

        public void bind(LogItem logItem){
            int mark;
            if(logItem.isInternalMessage()){
                if(logItem.isError()){
                    mark = R.drawable.log_mark_error;
                }else{
                    mark = R.drawable.log_mark;
                }
            }else{
                if(logItem.isError()){
                    mark = R.drawable.log_mark_incoming_error;
                }else{
                    mark = R.drawable.log_mark_incoming;
                }
            }
            mMarkImageView.setImageDrawable(mContext.getResources().getDrawable(mark));
            mMessageTextView.setText(logItem.getMessage());
            mTimeTextView.setText(mDateFormat.format(logItem.getTime()));
        }
    }

    private class LogAdapter extends RecyclerView.Adapter<LogHolder>{
        List<LogItem> mLogItems;

        public LogAdapter(List<LogItem> logItems){
            mLogItems = logItems;
        }

        @NonNull
        @Override
        public LogHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
            LayoutInflater inflater = LayoutInflater.from(mContext);
            return new LogHolder(inflater, parent);
        }

        @Override
        public void onBindViewHolder(@NonNull LogHolder holder, int position) {
            LogItem logItem = mLogItems.get(position);
            holder.bind(logItem);

        }

        @Override
        public int getItemCount() {
            return mLogItems.size();
        }

        public void appendItem(LogItem item){
            mLogItems.add(item);
        }
    }
}